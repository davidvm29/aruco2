// PRISMarker detection and printing.
#include "opencv2/objdetect/aruco2.hpp"
#include "aruco2_prisma_dict.hpp"
#include "aruco2_dictionary.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/core/hal/intrin.hpp>
#include <opencv2/flann.hpp>
// OpenCV 5
#if CV_VERSION_MAJOR >= 5
#include <opencv2/features.hpp>
#include <opencv2/3d.hpp>
// OpenCV 4
#elif CV_VERSION_MAJOR >= 4
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#endif
#include <map>
#include <vector>
#include <cassert>
#include <cstdint>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <set>
#include <array>
#include <limits>
#include <utility>
#include <unordered_map>


namespace {
namespace prisma {
struct Homographer{
    Homographer(const std::vector<cv::Point2f> & out ){
        CV_Assert(out.size() == 4);

        // Homography from the unit square without the generic 8x8 solve.
        const double x0 = static_cast<double>(out[0].x);
        const double y0 = static_cast<double>(out[0].y);
        const double x1 = static_cast<double>(out[1].x);
        const double y1 = static_cast<double>(out[1].y);
        const double x2 = static_cast<double>(out[2].x);
        const double y2 = static_cast<double>(out[2].y);
        const double x3 = static_cast<double>(out[3].x);
        const double y3 = static_cast<double>(out[3].y);

        const double dx1 = x1 - x2;
        const double dx2 = x3 - x2;
        const double dx3 = x0 - x1 + x2 - x3;

        const double dy1 = y1 - y2;
        const double dy2 = y3 - y2;
        const double dy3 = y0 - y1 + y2 - y3;

        const double denominator =
            dx1 * dy2 -
            dx2 * dy1;

        // Fall back to OpenCV for degenerate quadrilaterals.
        if (std::abs(denominator) <=
            std::numeric_limits<double>::epsilon())
        {
            static const std::vector<cv::Point2f> unitSquare = {
                cv::Point2f(0.f, 0.f),
                cv::Point2f(1.f, 0.f),
                cv::Point2f(1.f, 1.f),
                cv::Point2f(0.f, 1.f)
            };

            H = cv::getPerspectiveTransform(
                unitSquare,
                out
            );

            return;
        }

        const double g =
            (dx3 * dy2 - dx2 * dy3) /
            denominator;

        const double h =
            (dx1 * dy3 - dx3 * dy1) /
            denominator;

        H = cv::Mat(3, 3, CV_64F);

        double* m = H.ptr<double>(0);

        m[0] = x1 - x0 + g * x1;
        m[1] = x3 - x0 + h * x3;
        m[2] = x0;

        m[3] = y1 - y0 + g * y1;
        m[4] = y3 - y0 + h * y3;
        m[5] = y0;

        m[6] = g;
        m[7] = h;
        m[8] = 1.0;
    }

    cv::Point2f operator()(const cv::Point2f &p) const {
        const double *m=H.ptr<double>(0);
        double a=m[0]*p.x+m[1]*p.y+m[2];
        double b=m[3]*p.x+m[4]*p.y+m[5];
        double c=m[6]*p.x+m[7]*p.y+m[8];
        return cv::Point2f(a/c,b/c);
    }
    cv::Mat H;
};

/* Classify corners. */
void assignClass(const cv::Mat &im, std::vector<cv::KeyPoint>& kpoints, float sizeNorm=0.f, int wsize=5)
{
    if(im.type()!=CV_8UC1)
        throw std::runtime_error("assignClass Input image must be 8UC1");
    int wsizeFull=wsize*2+1;

    cv::Mat labels = cv::Mat::zeros(wsize*2+1,wsize*2+1,CV_8UC1);
    cv::Mat thresIm=cv::Mat(wsize*2+1,wsize*2+1,CV_8UC1);

    for(auto &kp:kpoints)
    {
        float x = kp.pt.x;
        float y = kp.pt.y;

        // Convert model coordinates to pixels.
        if(sizeNorm>0){
            x = im.cols * (x/sizeNorm + 0.5f);
            y = im.rows * (-y/sizeNorm + 0.5f);
        }

        x= int(x+0.5f);
        y= int(y+0.5f);

        cv::Rect r= cv::Rect(x-wsize,y-wsize,wsize*2+1,wsize*2+1);
        // Skip image borders.
        if(r.x<0 || r.x+r.width>im.cols || r.y<0 ||
            r.y+r.height>im.rows) continue;

        int endX=r.x+r.width;
        int endY=r.y+r.height;
        uchar minV=255,maxV=0;
        for(int row=r.y; row<endY; row++){
            const uchar *ptr=im.ptr<uchar>(row);
            for(int col=r.x; col<endX; col++)
            {
                if(minV>ptr[col]) minV=ptr[col];
                if(maxV<ptr[col]) maxV=ptr[col];
            }
        }

        if ((maxV-minV) < 25) {
            kp.class_id=0;
            continue;
        }

        double thres=(maxV+minV)/2.0;

        unsigned int nZ=0;
        for(int row=0; row<wsizeFull; row++){
            const uchar *ptr=im.ptr<uchar>( r.y+row)+r.x;
            uchar *thresPtr= thresIm.ptr<uchar>(row);
            for(int col=0; col<wsizeFull; col++){
                if( ptr[col]>thres) {
                    nZ++;
                    thresPtr[col]=255;
                }
                else thresPtr[col]=0;
            }
        }
        // Clear labels.
        for(int row=0; row<thresIm.rows; row++){
            uchar *labelsPtr=labels.ptr<uchar>(row);
            for(int col=0; col<thresIm.cols; col++) labelsPtr[col]=0;
        }

        uchar newLab = 1;
        std::map<uchar, uchar> unions;
        for(int row=0; row<thresIm.rows; row++){
            uchar *thresPtr=thresIm.ptr<uchar>(row);
            uchar *labelsPtr=labels.ptr<uchar>(row);
            for(int col=0; col<thresIm.cols; col++)
            {
                uchar reg = thresPtr[col];
                uchar lleft_px = 0;
                uchar ltop_px = 0;

                if(col-1>-1 && reg==thresPtr[col-1])
                    lleft_px =labelsPtr[col-1];

                if(row-1>-1 && reg==thresIm.ptr<uchar>(row-1)[col])
                    ltop_px =  labels.at<uchar>(row-1, col);

                if(lleft_px==0 && ltop_px==0)
                    labelsPtr[col] = newLab++;

                else if(lleft_px!=0 && ltop_px!=0)
                {
                    if(lleft_px < ltop_px)
                    {
                        labelsPtr[col]  = lleft_px;
                        unions[ltop_px] = lleft_px;
                    }
                    else if(lleft_px > ltop_px)
                    {
                        labelsPtr[col]  = ltop_px;
                        unions[lleft_px] = ltop_px;
                    }
                    // Same label.
                    else labelsPtr[col]  = ltop_px;
                }
                else
                    if(lleft_px!=0) labelsPtr[col]  = lleft_px;
                    else labelsPtr[col]  = ltop_px;
            }
        }

        int nc= newLab-1 - unions.size();
        if(nc==2)
            if(nZ > thresIm.total()-nZ) kp.class_id = 0;
            else kp.class_id = 1;
        else if (nc > 2)
            kp.class_id = 2;
    }
}

// Binary pattern of one PRISMarker level.
class Marker : public std::vector<cv::Point2f>
{
public:
    Marker(int id, cv::Mat m, std::vector<cv::Point3f> corners, std::vector<int> id_submarkers);
    Marker(){};

    inline int nBits() const { return static_cast<int>(_M.total()); }
    inline cv::Mat mat() const { return _M; }
    inline cv::Mat mask() const { return _mask; }
    inline const std::vector<int>& subMarkers() const { return _submarkers; }
    void addInner(Marker submarker);
    // Marker side length.
    inline float getMarkerSize() const
    {
        return static_cast<float>(cv::norm(keypts[0].pt  - keypts[1].pt));
    }
    inline std::vector<cv::KeyPoint> getKeypts();
    inline const std::vector<cv::KeyPoint>& getKeyptsRef() const { return keypts; }
    void applyMask(const cv::Mat& extraMask);

    int id;
    std::vector<cv::KeyPoint> keypts; // First 4 points are outer corners.
private:
    cv::Mat _M;
    cv::Mat _mask;
    std::vector<int> _submarkers;
};


Marker::Marker(int _id, cv::Mat m, std::vector<cv::Point3f> corners, std::vector<int> id_submarkers)
{
    this->id = _id;
    this->_M = m;
    for(auto pt:corners)
        keypts.push_back(cv::KeyPoint(pt.x,pt.y,-1,-1,-1,-1,0));
    _submarkers = id_submarkers;
    _mask = cv::Mat::ones(m.size(), CV_8UC1);
}

// Extract internal corners from the marker bit pattern
std::vector<cv::KeyPoint> Marker::getKeypts()
{
    if(keypts.size() > 4) return keypts;

    int nBitsSquared = int(sqrt(mat().total()));
    float bitSize =  getMarkerSize() / (nBitsSquared+2);

    // Add the marker border.
    cv::Mat marker;
    mat().copyTo(marker);
    marker +=  -1 * (mask()-1);
    cv::Mat markerBorder;
    copyMakeBorder(marker, markerBorder, 1,1,1,1,cv::BORDER_CONSTANT,0);

    // Find inner corners.
    for(int y=0; y< markerBorder.rows-1; y++)
    {
        for(int x=0; x< markerBorder.cols-1; x++)
        {
            int sum = markerBorder.at<uchar>(y, x) + markerBorder.at<uchar>(y, x+1) +
                      markerBorder.at<uchar>(y+1, x) + markerBorder.at<uchar>(y+1, x+1);

            if(sum==1)
                keypts.push_back(cv::KeyPoint(cv::Point2f(x-nBitsSquared/2.f,-(y-nBitsSquared/2.f))*bitSize,-1,-1,-1,-1,1));
            else if(sum==3)
                keypts.push_back(cv::KeyPoint(cv::Point2f(x-nBitsSquared/2.f,-(y-nBitsSquared/2.f))*bitSize,-1,-1,-1,-1,0));
            else if(sum==2)
            {
                if((markerBorder.at<uchar>(y, x) == markerBorder.at<uchar>(y+1, x+1)) && (markerBorder.at<uchar>(y, x+1) == markerBorder.at<uchar>(y+1, x)))
                    keypts.push_back(cv::KeyPoint(cv::Point2f(x-nBitsSquared/2.f,-(y-nBitsSquared/2.f))*bitSize,-1,-1,-1,-1,2));
            }
        }
    }

    return keypts;
}
// Mask the area occupied by an inner level
void Marker::addInner(Marker submarker)
{
    int nBitsSqrt= sqrt(nBits());
    float bitSize = getMarkerSize() / (nBitsSqrt+2.0f);
    float nsubBits = submarker.getMarkerSize() / bitSize;

    int x_min = int(round(submarker.keypts[0].pt.x / bitSize + nBitsSqrt/2));
    int x_max = x_min + nsubBits;
    int y_min = int(round(-submarker.keypts[0].pt.y / bitSize + nBitsSqrt/2));
    int y_max = y_min + nsubBits;

    for(int y=y_min; y<y_max; y++){
        for(int x=x_min; x<x_max; x++){
            _mask.at<uchar>(y,x)=0;
        }
    }
}

void Marker::applyMask(const cv::Mat& extraMask)
{
    if (extraMask.empty() || extraMask.size() != _mask.size())
        return;

    cv::bitwise_and(_mask, extraMask, _mask);

    if (keypts.size() > 4)
        keypts.resize(4);
}

// Geometry and auxiliary ArUcos of a PRISMarker.
class MarkerSet
{
public:
    struct ArucoInfo
    {
        std::string dictName = "DICT_ARUCO_MIP_36h12";
        int dictId = -1;
        std::vector<cv::Point3f> corners;
    };
    MarkerSet()
    {
        mInfoType = 2;   // NORM
        idExternal = 0;
    }
    // Levels by id.
    std::map<int, Marker> levels;
    // Marker ids grouped by bit count.
    std::map<int, std::vector<int>> bits_ids;
    // Auxiliary ArUco data.
    std::map<int, ArucoInfo> innerAruco;          // marker id
    std::map<int, ArucoInfo> cornerAruco;         // corner id
    // Per-level layout.
    std::vector<std::array<int, 4>> cornerIds;             // per level
    std::vector<int> cornerBits;                    // cells per level
    std::vector<cv::aruco2::PrismaLayout> cornerLayouts;
    std::string cornerDictName = "DICT_ARUCO_MIP_36h12";
    // Coordinate units.
    int mInfoType;/* -1:NONE, 0:PIX, 1:METERS, 2:NORMALIZE*/
    int idExternal;
private:
};
struct ArucoBlock
{
    int markerId = -1;
    int id = -1;
    int slot = 0;
    int cells = 0;
    int dictCells = 0;
    cv::aruco2::PrismaLayout layout =
        cv::aruco2::PRISMA_LAYOUT_CORNERS;
    std::string dictName;
    cv::Point2i cell;
    double x1 = 0.0;
    double y1 = 0.0;
    double x2 = 0.0;
    double y2 = 0.0;
};
// Position auxiliary ArUcos according to the level layout
static cv::Point2i arucoCell(
    cv::aruco2::PrismaLayout layout,
    int sideBits,
    int arucoCells,
    int slot
)
{
    int cellsPerSide = sideBits + 2;
    if (cellsPerSide <= 0 || arucoCells <= 0)
        return cv::Point2i(0, 0);
    if (layout == cv::aruco2::PRISMA_LAYOUT_CARDINAL)
    {
        int sideInset = 1;
        int sideMax = cellsPerSide - sideInset - arucoCells;
        if (sideMax < sideInset)
        {
            sideMax = std::max(0, cellsPerSide - arucoCells);
            sideInset = std::max(0, std::min(sideInset, sideMax));
        }
        int centerStart =
            static_cast<int>(
                std::round(
                    static_cast<double>(cellsPerSide - arucoCells) / 2.0
                )
            );
        centerStart =
            std::max(
                sideInset,
                std::min(centerStart, sideMax)
            );
        switch (slot)
        {
            case 0: // Norte
                return cv::Point2i(centerStart, sideInset);
            case 1: // Este
                return cv::Point2i(sideMax, centerStart);
            case 2: // Sur
                return cv::Point2i(centerStart, sideMax);
            case 3: // Oeste
                return cv::Point2i(sideInset, centerStart);
            default:
                return cv::Point2i(sideInset, sideInset);
        }
    }
    int cornerInset = 1;
    int cornerMax = cellsPerSide - cornerInset - arucoCells;
    if (cornerMax < cornerInset)
    {
        cornerMax = std::max(0, cellsPerSide - arucoCells);
        cornerInset = std::max(0, std::min(cornerInset, cornerMax));
    }
    switch (slot)
    {
        case 0: // TL
            return cv::Point2i(cornerInset, cornerInset);
        case 1: // TR
            return cv::Point2i(cornerMax, cornerInset);
        case 2: // BR
            return cv::Point2i(cornerMax, cornerMax);
        case 3: // BL
            return cv::Point2i(cornerInset, cornerMax);
        default:
            return cv::Point2i(cornerInset, cornerInset);
    }
}
static cv::Point3f pointFromCell(
    const cv::Point3f& origin,
    const cv::Point3f& ux,
    const cv::Point3f& uy,
    float col,
    float row
)
{
    return cv::Point3f(
        origin.x + ux.x * col + uy.x * row,
        origin.y + ux.y * col + uy.y * row,
        origin.z + ux.z * col + uy.z * row
    );
}
static int dictCells(
    const std::string& dictName,
    int dictId
)
{
    if (dictId < 0)
        return 0;

    if (dictName.empty())
        return 0;

    const cv::aruco2::DictInfo& info =
        cv::aruco2::getDictInfo(
            cv::String(dictName)
        );

    // Add border and margin cells.
    return info.bits + 4;
}
static cv::Point2d outBit(
    cv::aruco2::PrismaLayout layout,
    const std::string& dictName,
    int slot,
    int arucoId,
    int arucoCells
)
{
    int logicalCells =
        dictCells(
            dictName,
            arucoId
        );
    if (logicalCells <= 0 || arucoCells <= 0)
        return cv::Point2d(0.0, 0.0);
    double ownBitInGridCells =
        static_cast<double>(arucoCells) /
        static_cast<double>(logicalCells);
    if (layout == cv::aruco2::PRISMA_LAYOUT_CARDINAL)
    {
        switch (slot)
        {
            case 0: // Norte
                return cv::Point2d(0.0, -ownBitInGridCells);
            case 1: // Este
                return cv::Point2d(ownBitInGridCells, 0.0);
            case 2: // Sur
                return cv::Point2d(0.0, ownBitInGridCells);
            case 3: // Oeste
                return cv::Point2d(-ownBitInGridCells, 0.0);
            default:
                return cv::Point2d(0.0, 0.0);
        }
    }
    switch (slot)
    {
        case 0: // TL
            return cv::Point2d(-ownBitInGridCells, 0.0);
        case 1: // TR
            return cv::Point2d(ownBitInGridCells, 0.0);
        case 2: // BR
            return cv::Point2d(ownBitInGridCells, 0.0);
        case 3: // BL
            return cv::Point2d(-ownBitInGridCells, 0.0);
        default:
            return cv::Point2d(0.0, 0.0);
    }
}
static ArucoBlock makeBlock(
    int markerId,
    cv::aruco2::PrismaLayout layout,
    const std::string& dictName,
    int sideBits,
    int arucoCells,
    int slot,
    int arucoId
)
{
    ArucoBlock b;
    b.markerId = markerId;
    b.id = arucoId;
    b.slot = slot;
    b.cells = arucoCells;
    b.layout = layout;
    b.dictName = dictName;
    b.dictCells = dictCells(dictName, arucoId);
    b.cell = arucoCell(layout, sideBits, arucoCells, slot);

    cv::Point2d d = outBit(
        layout,
        dictName,
        slot,
        arucoId,
        arucoCells
    );
    b.x1 = static_cast<double>(b.cell.x) + d.x;
    b.y1 = static_cast<double>(b.cell.y) + d.y;
    b.x2 = b.x1 + static_cast<double>(arucoCells);
    b.y2 = b.y1 + static_cast<double>(arucoCells);
    return b;
}
static bool hitsCell(
    const ArucoBlock& b,
    double x1,
    double y1,
    double x2,
    double y2
)
{
    return x1 < b.x2 && x2 > b.x1 &&
           y1 < b.y2 && y2 > b.y1;
}
static std::array<cv::Point3f, 4> blockCorners(
    const Marker& marker,
    const ArucoBlock& b
)
{
    int fullCells = marker.mat().cols + 2;
    cv::Point3f tl(marker.keypts[0].pt.x, marker.keypts[0].pt.y, 0.f);
    cv::Point3f tr(marker.keypts[1].pt.x, marker.keypts[1].pt.y, 0.f);
    cv::Point3f bl(marker.keypts[3].pt.x, marker.keypts[3].pt.y, 0.f);

    cv::Point3f ux((tr.x - tl.x) / fullCells, (tr.y - tl.y) / fullCells, 0.f);
    cv::Point3f uy((bl.x - tl.x) / fullCells, (bl.y - tl.y) / fullCells, 0.f);

    return {
        pointFromCell(tl, ux, uy, static_cast<float>(b.x1), static_cast<float>(b.y1)),
        pointFromCell(tl, ux, uy, static_cast<float>(b.x2), static_cast<float>(b.y1)),
        pointFromCell(tl, ux, uy, static_cast<float>(b.x2), static_cast<float>(b.y2)),
        pointFromCell(tl, ux, uy, static_cast<float>(b.x1), static_cast<float>(b.y2))
    };
}

struct DetectedAruco
{
    // Search id; PData maps it to the owning PRISMarker.
    int searchId = -1;

    // Image corners returned by the low-level detector.
    std::vector<cv::Point2f> imgCorners;
};

struct ArucoHit
{
    int internalId = -1;
    int fullCells = 0;
    cv::Mat bits;
    std::vector<cv::Point2f> imgCorners;
    std::vector<cv::Point3f> objCorners;
    std::vector<cv::Point3f> reserveObjCorners;
};

struct LevelHit
{
    int id = -1;
    bool canStart = false;
    std::vector<cv::Point2f> imgCorners;
};

struct ArucoRef
{
    int internalId = -1;
    int dictId = -1;
    int fullCells = 0;
    cv::aruco2::DictionaryType dictionary =
        static_cast<cv::aruco2::DictionaryType>(-1);
    cv::Mat bits;
    std::vector<cv::Point3f> objCorners;
    std::vector<cv::Point3f> reserveObjCorners;
};

// ArUco entry for low-level search.
struct ArucoSearchTarget
{
    int dictId = -1;
    cv::aruco2::DictionaryType dictionary =
        static_cast<cv::aruco2::DictionaryType>(-1);
};


struct SquareCandidate
{
    SquareCandidate(
        std::vector<cv::Point2f> value,
        bool canBeLevel
    )
        : corners(std::move(value)),
          homography(corners),
          levelCandidate(canBeLevel)
    {
    }

    std::vector<cv::Point2f> corners;
    Homographer homography;
    bool levelCandidate = false;
};

struct DetectionContext
{
    cv::Mat gray;
    std::vector<SquareCandidate> squares;
};

static constexpr int kMinLevelContourPoints = 120;

struct DetectionEvidence
{
    std::vector<LevelHit> levels;
    std::vector<DetectedAruco> arucos;
};

static cv::aruco2::DictionaryType getDictionary(
    const std::string& dictName
)
{
    if (dictName.empty())
        return static_cast<cv::aruco2::DictionaryType>(-1);

    return cv::aruco2::getDictInfo(
        cv::String(dictName)
    ).type;
}

static cv::Mat rotateBits(
    const cv::Mat& in
)
{
    cv::Mat out(in.size(), in.type());
    for (int y = 0; y < in.rows; y++)
        for (int x = 0; x < in.cols; x++)
            out.at<uchar>(y, x) = in.at<uchar>(in.cols - x - 1, y);
    return out;
}

// Hamming distance with early exit.
static int hammingFast(
    const cv::Mat& a,
    const cv::Mat& b,
    const cv::Mat& validMask,
    int stopAfter = std::numeric_limits<int>::max()
)
{
    if (a.empty() || b.empty())
        return 1000000;

    if (a.rows != b.rows ||
        a.cols != b.cols ||
        a.type() != CV_8UC1 ||
        b.type() != CV_8UC1)
        return 1000000;

    const bool useMask = !validMask.empty();
    int errors = 0;

    for (int y = 0; y < a.rows; y++)
    {
        const uchar* rowA = a.ptr<uchar>(y);
        const uchar* rowB = b.ptr<uchar>(y);
        const uchar* rowMask =
            useMask ? validMask.ptr<uchar>(y) : nullptr;

        for (int x = 0; x < a.cols; x++)
        {
            if (rowMask && rowMask[x] == 0)
                continue;

            if (rowA[x] != rowB[x])
            {
                errors++;
                if (errors > stopAfter)
                    return errors;
            }
        }
    }

    return errors;
}

static cv::Point3f bilinearPoint(
    const std::vector<cv::Point3f>& corners,
    float u,
    float v
)
{
    const cv::Point3f& tl = corners[0];
    const cv::Point3f& tr = corners[1];
    const cv::Point3f& br = corners[2];
    const cv::Point3f& bl = corners[3];

    float a = (1.f - u) * (1.f - v);
    float b = u * (1.f - v);
    float c = u * v;
    float d = (1.f - u) * v;

    return cv::Point3f(
        a * tl.x + b * tr.x + c * br.x + d * bl.x,
        a * tl.y + b * tr.y + c * br.y + d * bl.y,
        a * tl.z + b * tr.z + c * br.z + d * bl.z
    );
}

static std::vector<cv::Point3f> removeOuterBorder(
    const std::vector<cv::Point3f>& corners,
    int outerCells
)
{
    if (corners.size() != 4 || outerCells <= 2)
        return corners;

    float t = 1.f / static_cast<float>(outerCells);

    return {
        bilinearPoint(corners, t,      t),
        bilinearPoint(corners, 1.f-t,  t),
        bilinearPoint(corners, 1.f-t,  1.f-t),
        bilinearPoint(corners, t,      1.f-t)
    };
}

static bool cellHasAruco(
    int markerId,
    int nVal,
    int row,
    int col,
    const MarkerSet& markerSet
)
{
    if (markerId < 0 ||
        markerId >= static_cast<int>(markerSet.cornerBits.size()) ||
        markerId >= static_cast<int>(markerSet.cornerIds.size()))
        return false;

    int arucoCells = markerSet.cornerBits[markerId];
    if (arucoCells <= 0)
        return false;

    double x1 = static_cast<double>(col);
    double y1 = static_cast<double>(row);

    for (int slot = 0; slot < 4; slot++)
    {
        int arucoId = markerSet.cornerIds[markerId][slot];
        if (arucoId < 0)
            continue;

        const cv::aruco2::PrismaLayout layout =
            markerId < static_cast<int>(markerSet.cornerLayouts.size())
                ? markerSet.cornerLayouts[markerId]
                : cv::aruco2::PRISMA_LAYOUT_CORNERS;

        ArucoBlock b =
            makeBlock(
                markerId,
                layout,
                markerSet.cornerDictName,
                nVal,
                arucoCells,
                slot,
                arucoId
            );

        if (hitsCell(b, x1, y1, x1 + 1.0, y1 + 1.0))
            return true;
    }

    return false;
}

// Ignore ArUco cells in the mask.
static bool toMarkerGrid(
    const Marker& marker,
    int fullCells,
    const cv::Point3f& p,
    double& gx,
    double& gy
)
{
    if (marker.keypts.size() < 4 || fullCells <= 0)
        return false;

    const cv::Point2f tl = marker.keypts[0].pt;
    const cv::Point2f tr = marker.keypts[1].pt;
    const cv::Point2f bl = marker.keypts[3].pt;

    const double exx = static_cast<double>(tr.x - tl.x);
    const double exy = static_cast<double>(tr.y - tl.y);
    const double eyx = static_cast<double>(bl.x - tl.x);
    const double eyy = static_cast<double>(bl.y - tl.y);

    const double qx = static_cast<double>(p.x - tl.x);
    const double qy = static_cast<double>(p.y - tl.y);

    const double det = exx * eyy - exy * eyx;
    if (std::fabs(det) < 1e-12)
        return false;

    const double u = (qx * eyy - qy * eyx) / det;
    const double v = (exx * qy - exy * qx) / det;

    gx = u * static_cast<double>(fullCells);
    gy = v * static_cast<double>(fullCells);

    return true;
}

static void clearRect(
    cv::Mat& validMask,
    double x1,
    double y1,
    double x2,
    double y2
)
{
    if (validMask.empty())
        return;

    if (x2 < x1)
        std::swap(x1, x2);
    if (y2 < y1)
        std::swap(y1, y2);

    const double eps = 1e-6;

    for (int y = 0; y < validMask.rows; y++)
    {
        const double cy1 = static_cast<double>(y);
        const double cy2 = cy1 + 1.0;

        if (cy1 >= y2 - eps || cy2 <= y1 + eps)
            continue;

        uchar* row = validMask.ptr<uchar>(y);

        for (int x = 0; x < validMask.cols; x++)
        {
            const double cx1 = static_cast<double>(x);
            const double cx2 = cx1 + 1.0;

            if (cx1 < x2 - eps && cx2 > x1 + eps)
                row[x] = 0;
        }
    }
}

static void clearQuad(
    const Marker& marker,
    cv::Mat& validMask,
    const std::array<cv::Point3f, 4>& quad
)
{
    if (validMask.empty())
        return;

    const int fullCells = validMask.cols;

    double minX = 1e100;
    double minY = 1e100;
    double maxX = -1e100;
    double maxY = -1e100;

    for (const auto& p : quad)
    {
        double gx = 0.0;
        double gy = 0.0;

        if (!toMarkerGrid(marker, fullCells, p, gx, gy))
            return;

        minX = std::min(minX, gx);
        minY = std::min(minY, gy);
        maxX = std::max(maxX, gx);
        maxY = std::max(maxY, gy);
    }

    clearRect(
        validMask,
        minX,
        minY,
        maxX,
        maxY
    );
}

static void clearAruco(
    const Marker& marker,
    cv::Mat& validMask,
    const MarkerSet::ArucoInfo& info
)
{
    if (info.corners.size() != 4)
        return;

    std::array<cv::Point3f, 4> quad = {
        info.corners[0],
        info.corners[1],
        info.corners[2],
        info.corners[3]
    };

    clearQuad(
        marker,
        validMask,
        quad
    );
}

static void clearArucoBlock(
    const Marker& marker,
    cv::Mat& validMask,
    const Marker& ownerMarker,
    int ownerMarkerId,
    cv::aruco2::PrismaLayout layout,
    const std::string& dictName,
    int arucoCells,
    int slot,
    int arucoId
)
{
    if (arucoCells <= 0 || arucoId < 0)
        return;

    int ownerSideBits = ownerMarker.mat().cols;
    if (ownerSideBits <= 0 || ownerMarker.keypts.size() < 4)
        return;

    ArucoBlock b =
        makeBlock(
            ownerMarkerId,
            layout,
            dictName,
            ownerSideBits,
            arucoCells,
            slot,
            arucoId
        );

    clearQuad(
        marker,
        validMask,
        blockCorners(ownerMarker, b)
    );
}

static void applyArucoMask(
    const Marker& marker,
    const MarkerSet& markerSet,
    cv::Mat& validMask
)
{
    if (validMask.empty())
        return;

    bool hasCornerLayout = false;

    // Use the compact level geometry when it is available.
    const size_t levels =
        std::min(
            markerSet.cornerIds.size(),
            markerSet.cornerBits.size()
        );

    for (size_t level = 0; level < levels; level++)
    {
        const int ownerMarkerId =
            static_cast<int>(level);

        auto itOwner =
            markerSet.levels.find(ownerMarkerId);

        if (itOwner == markerSet.levels.end())
            continue;

        const int arucoCells =
            markerSet.cornerBits[level];

        if (arucoCells <= 0)
            continue;

        for (int slot = 0; slot < 4; slot++)
        {
            const int arucoId =
                markerSet.cornerIds[level][slot];

            if (arucoId < 0)
                continue;

            const cv::aruco2::PrismaLayout layout =
                level < markerSet.cornerLayouts.size()
                    ? markerSet.cornerLayouts[level]
                    : cv::aruco2::PRISMA_LAYOUT_CORNERS;

            clearArucoBlock(
                marker,
                validMask,
                itOwner->second,
                ownerMarkerId,
                layout,
                markerSet.cornerDictName,
                arucoCells,
                slot,
                arucoId
            );

            hasCornerLayout = true;
        }
    }

    // Support older YAML corner data.
    if (!hasCornerLayout)
    {
        for (const auto& item : markerSet.cornerAruco)
        {
            clearAruco(
                marker,
                validMask,
                item.second
            );
        }
    }

    // Mask inner ArUcos too.
    for (const auto& item : markerSet.innerAruco)
    {
        clearAruco(
            marker,
            validMask,
            item.second
        );
    }
}
// Build the reference pattern, masking nested levels and ArUcos
static void makeRef(
    const Marker& fm,
    const MarkerSet& markerSet,
    cv::Mat& reference,
    cv::Mat& validMask
)
{
    cv::Mat mat = fm.mat();
    cv::Mat mask = fm.mask();

    const int nVal = mat.rows;
    const int fullCells = nVal + 2;

    reference =
        cv::Mat(
            fullCells,
            fullCells,
            CV_8UC1,
            cv::Scalar(0)
        );

    validMask =
        cv::Mat(
            fullCells,
            fullCells,
            CV_8UC1,
            cv::Scalar(255)
        );

    for (int y = 0; y < nVal; y++)
    {
        const uchar* matRow = mat.ptr<uchar>(y);
        const uchar* maskRow = mask.empty() ? nullptr : mask.ptr<uchar>(y);
        uchar* refRow = reference.ptr<uchar>(y + 1);
        uchar* validRow = validMask.ptr<uchar>(y + 1);

        for (int x = 0; x < nVal; x++)
        {
            refRow[x + 1] = matRow[x] ? 255 : 0;

            if (maskRow && maskRow[x] == 0)
                validRow[x + 1] = 0;
        }
    }

    // Ignore cells occupied by ArUcos from this level.
    for (int y = 0; y < fullCells; y++)
    {
        uchar* validRow = validMask.ptr<uchar>(y);

        for (int x = 0; x < fullCells; x++)
        {
            if (cellHasAruco(
                    fm.id,
                    nVal,
                    y,
                    x,
                    markerSet
                ))
            {
                validRow[x] = 0;
            }
        }
    }

    // Ignore ArUcos from the other levels.
    applyArucoMask(
        fm,
        markerSet,
        validMask
    );
}

static int innerKey(int markerId)
{
    // Internal lookup key.
    return -(markerId + 1);
}
// Prepare auxiliary ArUco patterns and their model coordinates
static std::vector<ArucoRef> makeArucoRefs(
    const MarkerSet& markerSet,
    std::map<int, cv::aruco2::Dictionary>& dictionaryCache
)
{
    std::vector<ArucoRef> targets;
    targets.reserve(markerSet.innerAruco.size() + markerSet.cornerAruco.size());

    auto getCachedDictionary =
        [&](cv::aruco2::DictionaryType dictionary)
            -> const cv::aruco2::Dictionary&
        {
            const int key =
                static_cast<int>(dictionary);

            auto it = dictionaryCache.find(key);

            if (it == dictionaryCache.end())
            {
                it = dictionaryCache.emplace(
                    key,
                    cv::aruco2::getPredefinedDictionary(dictionary)
                ).first;
            }

            return it->second;
        };

    auto addTarget =
        [&](int internalId,
            const MarkerSet::ArucoInfo& info,
            bool isCentral)
        {
            if (info.dictId < 0 ||
                info.dictName.empty() ||
                info.corners.size() != 4)
            {
                return;
            }

            const cv::aruco2::DictionaryType dictionary =
                getDictionary(info.dictName);

            const cv::aruco2::Dictionary& dictionaryData =
                getCachedDictionary(dictionary);

            if (info.dictId >= static_cast<int>(dictionaryData.size()))
                return;

            const int markerSize = dictionaryData.markerSize;

            if (markerSize <= 0)
                return;

            const cv::Mat rawBits =
                cv::aruco2::Dictionary::getBitsFromByteList(
                    dictionaryData.bytesList.rowRange(
                        info.dictId,
                        info.dictId + 1
                    ),
                    markerSize,
                    0
                );

            if (rawBits.empty())
                return;

            cv::Mat markerBits(
                markerSize + 2,
                markerSize + 2,
                CV_8UC1,
                cv::Scalar(0)
            );

            rawBits.convertTo(
                markerBits(
                    cv::Rect(
                        1,
                        1,
                        markerSize,
                        markerSize
                    )
                ),
                CV_8UC1,
                255.0
            );

            const int outerCells =
                markerSize + 4;

            ArucoRef target;
            target.internalId = internalId;
            target.dictId = info.dictId;
            target.dictionary = dictionary;
            target.bits = markerBits;

            if (isCentral)
            {
                target.fullCells = markerSize + 2;
                target.objCorners = info.corners;
                target.reserveObjCorners.clear();
            }
            else
            {
                target.fullCells = outerCells;
                target.reserveObjCorners = info.corners;
                target.objCorners =
                    removeOuterBorder(
                        info.corners,
                        outerCells
                    );
            }

            targets.push_back(
                std::move(target)
            );
        };

    for (const auto& item : markerSet.innerAruco)
        addTarget(innerKey(item.first), item.second, true);

    for (const auto& item : markerSet.cornerAruco)
        addTarget(item.first, item.second, false);

    return targets;
}

static int cornerType(const cv::Mat& bits, int y, int x)
{
    auto v = [&](int r, int c) {
        return bits.at<uchar>(r, c) > 127 ? 1 : 0;
    };

    int a = v(y - 1, x - 1);
    int b = v(y - 1, x);
    int c = v(y, x - 1);
    int d = v(y, x);
    int s = a + b + c + d;

    if (s == 1) return 1;
    if (s == 3) return 0;
    if (s == 2 && a == d && b == c && a != b) return 2;
    return -1;
}

static bool findFast(
    const cv::Point2f& pt,
    int cls,
    const std::vector<cv::KeyPoint>& kpoints,
    cv::flann::Index& kdtree,
    cv::Point2f& out
)
{
    cv::Mat q(1, 2, CV_32F);
    q.at<float>(0, 0) = pt.x;
    q.at<float>(0, 1) = pt.y;

    cv::Mat idx, dist;
    int found = kdtree.radiusSearch(q, idx, dist, 16.0, 4);

    for (int i = 0; i < found; i++)
    {
        int k = idx.at<int>(0, i);
        if (k < 0 || k >= static_cast<int>(kpoints.size()))
            continue;
        if (kpoints[k].class_id != cls)
            continue;
        out = kpoints[k].pt;
        return true;
    }
    return false;
}

static bool findFastAny(
    const cv::Point2f& pt,
    const std::vector<cv::KeyPoint>& kpoints,
    cv::flann::Index& kdtree,
    cv::Point2f& out
)
{
    cv::Mat q(1, 2, CV_32F);
    q.at<float>(0, 0) = pt.x;
    q.at<float>(0, 1) = pt.y;

    cv::Mat idx, dist;
    int found = kdtree.radiusSearch(q, idx, dist, 25.0, 4);
    if (found <= 0)
        return false;

    int k = idx.at<int>(0, 0);
    if (k < 0 || k >= static_cast<int>(kpoints.size()))
        return false;

    out = kpoints[k].pt;
    return true;
}

static bool nearImg(
    const std::vector<cv::Point2f>& pts,
    const cv::Point2f& p,
    float minDist
)
{
    const float minDist2 = minDist * minDist;
    for (const auto& q : pts)
        if ((q.x - p.x) * (q.x - p.x) + (q.y - p.y) * (q.y - p.y) < minDist2)
            return true;
    return false;
}

static bool sameObj(
    const std::vector<cv::Point3f>& pts,
    const cv::Point3f& p
)
{
    for (const auto& q : pts)
        if (std::fabs(q.x - p.x) < 1e-5f && std::fabs(q.y - p.y) < 1e-5f)
            return true;
    return false;
}

static constexpr int kMinSubpixHalf = 1;
static constexpr int kMaxSubpixHalf = 8;

static int adaptiveSubpixHalf(double cellExtentPx)
{
    if (!std::isfinite(cellExtentPx) || cellExtentPx <= 0.0)
        return kMinSubpixHalf;

    // Adapt the subpixel window to cell size (at most 0.6 cells).
    const int scaled = std::max(
        kMinSubpixHalf,
        static_cast<int>(std::lround(cellExtentPx * 0.4))
    );

    const int maxSafe = std::max(
        kMinSubpixHalf,
        static_cast<int>(std::floor(cellExtentPx * 0.6))
    );

    return std::clamp(
        std::min(scaled, maxSafe),
        kMinSubpixHalf,
        kMaxSubpixHalf
    );
}

static cv::Size clampSubpixWindow(const cv::Size& window)
{
    return cv::Size(
        std::clamp(window.width, kMinSubpixHalf, kMaxSubpixHalf),
        std::clamp(window.height, kMinSubpixHalf, kMaxSubpixHalf)
    );
}

static cv::Size adaptiveSubpixWindow(
    double cellExtentX,
    double cellExtentY
)
{
    return cv::Size(
        adaptiveSubpixHalf(cellExtentX),
        adaptiveSubpixHalf(cellExtentY)
    );
}

static bool finitePoint(const cv::Point2f& point)
{
    return std::isfinite(point.x) && std::isfinite(point.y);
}

static cv::Size cellSubpixWindow(
    const cv::Point2f& cellX,
    const cv::Point2f& cellY
)
{
    if (!finitePoint(cellX) || !finitePoint(cellY))
        return cv::Size(kMinSubpixHalf, kMinSubpixHalf);

    const double extentX =
        std::fabs(static_cast<double>(cellX.x)) +
        std::fabs(static_cast<double>(cellY.x));
    const double extentY =
        std::fabs(static_cast<double>(cellX.y)) +
        std::fabs(static_cast<double>(cellY.y));

    return adaptiveSubpixWindow(extentX, extentY);
}

static cv::Size localSubpixWindow(
    const Homographer& hom,
    const cv::Point2f& point,
    double cellStepX,
    double cellStepY
)
{
    if (!std::isfinite(cellStepX) || !std::isfinite(cellStepY) ||
        cellStepX <= 0.0 || cellStepY <= 0.0)
    {
        return cv::Size(kMinSubpixHalf, kMinSubpixHalf);
    }

    const float halfX = static_cast<float>(0.5 * cellStepX);
    const float halfY = static_cast<float>(0.5 * cellStepY);

    const cv::Point2f left =
        hom(cv::Point2f(point.x - halfX, point.y));
    const cv::Point2f right =
        hom(cv::Point2f(point.x + halfX, point.y));
    const cv::Point2f top =
        hom(cv::Point2f(point.x, point.y - halfY));
    const cv::Point2f bottom =
        hom(cv::Point2f(point.x, point.y + halfY));

    if (!finitePoint(left) || !finitePoint(right) ||
        !finitePoint(top) || !finitePoint(bottom))
    {
        return cv::Size(kMinSubpixHalf, kMinSubpixHalf);
    }

    return cellSubpixWindow(
        right - left,
        bottom - top
    );
}

static bool projectPoint(
    const cv::Mat& homography,
    const cv::Point2f& point,
    cv::Point2f& projected
)
{
    if (homography.rows != 3 ||
        homography.cols != 3 ||
        homography.channels() != 1)
    {
        return false;
    }

    double h00, h01, h02;
    double h10, h11, h12;
    double h20, h21, h22;

    if (homography.depth() == CV_64F)
    {
        const double* row0 = homography.ptr<double>(0);
        const double* row1 = homography.ptr<double>(1);
        const double* row2 = homography.ptr<double>(2);

        h00 = row0[0]; h01 = row0[1]; h02 = row0[2];
        h10 = row1[0]; h11 = row1[1]; h12 = row1[2];
        h20 = row2[0]; h21 = row2[1]; h22 = row2[2];
    }
    else if (homography.depth() == CV_32F)
    {
        const float* row0 = homography.ptr<float>(0);
        const float* row1 = homography.ptr<float>(1);
        const float* row2 = homography.ptr<float>(2);

        h00 = row0[0]; h01 = row0[1]; h02 = row0[2];
        h10 = row1[0]; h11 = row1[1]; h12 = row1[2];
        h20 = row2[0]; h21 = row2[1]; h22 = row2[2];
    }
    else
    {
        cv::Mat converted;
        homography.convertTo(converted, CV_64F);
        return projectPoint(
            converted,
            point,
            projected
        );
    }

    const double x = static_cast<double>(point.x);
    const double y = static_cast<double>(point.y);
    const double w = h20 * x + h21 * y + h22;

    if (!std::isfinite(w) ||
        std::fabs(w) <= std::numeric_limits<double>::epsilon())
    {
        return false;
    }

    projected.x = static_cast<float>(
        (h00 * x + h01 * y + h02) / w
    );
    projected.y = static_cast<float>(
        (h10 * x + h11 * y + h12) / w
    );

    return finitePoint(projected);
}

static cv::Size localSubpixWindow(
    const cv::Mat& homography,
    const cv::Point2f& point,
    double cellStepX,
    double cellStepY
)
{
    if (homography.empty() ||
        !std::isfinite(cellStepX) || !std::isfinite(cellStepY) ||
        cellStepX <= 0.0 || cellStepY <= 0.0)
    {
        return cv::Size(kMinSubpixHalf, kMinSubpixHalf);
    }

    const float halfX = static_cast<float>(0.5 * cellStepX);
    const float halfY = static_cast<float>(0.5 * cellStepY);

    cv::Point2f left;
    cv::Point2f right;
    cv::Point2f top;
    cv::Point2f bottom;

    if (!projectPoint(
            homography,
            cv::Point2f(point.x - halfX, point.y),
            left) ||
        !projectPoint(
            homography,
            cv::Point2f(point.x + halfX, point.y),
            right) ||
        !projectPoint(
            homography,
            cv::Point2f(point.x, point.y - halfY),
            top) ||
        !projectPoint(
            homography,
            cv::Point2f(point.x, point.y + halfY),
            bottom))
    {
        return cv::Size(kMinSubpixHalf, kMinSubpixHalf);
    }

    return cellSubpixWindow(
        right - left,
        bottom - top
    );
}
// Refine corners in groups with the same subpixel window
static void refineSubpixGrouped(
    const cv::Mat& gray,
    std::vector<cv::Point2f>& points,
    const std::vector<cv::Size>& windows,
    const cv::TermCriteria& criteria
)
{
    if (gray.empty() || points.empty() || points.size() != windows.size())
        return;

    std::map<std::pair<int, int>, std::vector<std::size_t>> groups;

    for (std::size_t index = 0; index < points.size(); ++index)
    {
        const cv::Size window = clampSubpixWindow(windows[index]);

        if (!finitePoint(points[index]) ||
            points[index].x <= window.width + 1 ||
            points[index].y <= window.height + 1 ||
            points[index].x >= gray.cols - window.width - 2 ||
            points[index].y >= gray.rows - window.height - 2)
        {
            continue;
        }

        groups[
            std::make_pair(window.width, window.height)
        ].push_back(index);
    }

    for (const auto& group : groups)
    {
        const cv::Size window(
            group.first.first,
            group.first.second
        );
        const std::vector<std::size_t>& indices = group.second;

        std::vector<cv::Point2f> refined;
        refined.reserve(indices.size());

        for (std::size_t index : indices)
            refined.push_back(points[index]);

        cv::cornerSubPix(
            gray,
            refined,
            window,
            cv::Size(-1, -1),
            criteria
        );

        for (std::size_t i = 0; i < indices.size(); ++i)
            points[indices[i]] = refined[i];
    }
}

static bool addMatch(
    const cv::Point3f& obj,
    const cv::Point2f& img,
    std::vector<cv::Point3f>& p3d,
    std::vector<cv::Point2f>& p2d,
    float minImgDist = 4.f,
    std::vector<cv::Size>* subpixWindows = nullptr,
    cv::Size subpixWindow = cv::Size(1, 1)
)
{
    if (sameObj(p3d, obj))
        return false;
    if (nearImg(p2d, img, minImgDist))
        return false;

    p3d.push_back(obj);
    p2d.push_back(img);

    if (subpixWindows != nullptr)
        subpixWindows->push_back(clampSubpixWindow(subpixWindow));

    return true;
}

static bool same3d(const cv::Point3f& a, const cv::Point3f& b)
{
    return std::fabs(a.x - b.x) < 1e-5f &&
           std::fabs(a.y - b.y) < 1e-5f &&
           std::fabs(a.z - b.z) < 1e-5f;
}

static bool near2d(const cv::Point2f& a, const cv::Point2f& b, float d)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return dx * dx + dy * dy < d * d;
}

static bool isDup(
    const std::vector<cv::Point3f>& p3d,
    const std::vector<cv::Point2f>& p2d,
    const cv::Point3f& obj,
    const cv::Point2f& img,
    float minDist
)
{
    for (size_t i = 0; i < p2d.size(); i++)
        if (same3d(p3d[i], obj) || near2d(p2d[i], img, minDist))
            return true;
    return false;
}

static void removeDup(
    std::vector<cv::Point3f>& p3d,
    std::vector<cv::Point2f>& p2d,
    float minDist = 4.f
)
{
    if (p3d.size() != p2d.size())
        return;

    std::vector<cv::Point3f> out3d;
    std::vector<cv::Point2f> out2d;
    out3d.reserve(p3d.size());
    out2d.reserve(p2d.size());

    for (size_t i = 0; i < p2d.size(); i++)
    {
        if (isDup(out3d, out2d, p3d[i], p2d[i], minDist))
            continue;
        out3d.push_back(p3d[i]);
        out2d.push_back(p2d[i]);
    }

    p3d.swap(out3d);
    p2d.swap(out2d);
}

static float arucoMargin(int fullCells)
{
    if (fullCells <= 2)
        return 0.f;
    float t = 1.f / static_cast<float>(fullCells);
    return t / (1.f - 2.f * t);
}

static std::vector<cv::Point2f> reservePts(
    const ArucoHit& aruco
)
{
    std::vector<cv::Point2f> out;
    if (aruco.imgCorners.size() != 4)
        return out;

    float m = arucoMargin(aruco.fullCells);
    Homographer hom(aruco.imgCorners);

    out.push_back(hom(cv::Point2f(-m,     -m)));
    out.push_back(hom(cv::Point2f(1.f+m,  -m)));
    out.push_back(hom(cv::Point2f(1.f+m, 1.f+m)));
    out.push_back(hom(cv::Point2f(-m,    1.f+m)));
    return out;
}

static cv::Point2f arucoNormalizedCellSize(
    const ArucoHit& aruco
)
{
    if (!aruco.bits.empty() &&
        aruco.bits.cols > 0 &&
        aruco.bits.rows > 0)
    {
        return cv::Point2f(
            1.f / static_cast<float>(aruco.bits.cols),
            1.f / static_cast<float>(aruco.bits.rows)
        );
    }

    int cells = std::max(2, aruco.fullCells);
    if (aruco.reserveObjCorners.size() == 4 && cells > 2)
        cells -= 2;

    const float step = 1.f / static_cast<float>(cells);
    return cv::Point2f(step, step);
}

static void addReservePts(
    const ArucoHit& aruco,
    const std::vector<cv::KeyPoint>& kpoints,
    cv::flann::Index& kdtree,
    std::vector<cv::Point3f>& p3d,
    std::vector<cv::Point2f>& p2d,
    std::vector<cv::Size>* subpixWindows = nullptr
)
{
    if (aruco.reserveObjCorners.size() != 4 ||
        aruco.imgCorners.size() != 4)
    {
        return;
    }

    const float margin = arucoMargin(aruco.fullCells);
    const std::array<cv::Point2f, 4> normalized = {
        cv::Point2f(-margin, -margin),
        cv::Point2f(1.f + margin, -margin),
        cv::Point2f(1.f + margin, 1.f + margin),
        cv::Point2f(-margin, 1.f + margin)
    };

    const cv::Point2f cell = arucoNormalizedCellSize(aruco);
    Homographer hom(aruco.imgCorners);

    for (int i = 0; i < 4; ++i)
    {
        const cv::Point2f predicted = hom(normalized[i]);
        cv::Point2f real;

        if (!findFastAny(predicted, kpoints, kdtree, real))
            continue;

        const cv::Size window =
            subpixWindows != nullptr
                ? localSubpixWindow(
                    hom,
                    normalized[i],
                    cell.x,
                    cell.y
                )
                : cv::Size(1, 1);

        addMatch(
            aruco.reserveObjCorners[i],
            real,
            p3d,
            p2d,
            5.f,
            subpixWindows,
            window
        );
    }
}

static void addAruco4(
    const ArucoHit& aruco,
    std::vector<cv::Point3f>& p3d,
    std::vector<cv::Point2f>& p2d,
    std::vector<cv::Size>* subpixWindows = nullptr
)
{
    if (aruco.imgCorners.size() != 4 ||
        aruco.objCorners.size() != 4)
    {
        return;
    }

    const std::array<cv::Point2f, 4> normalized = {
        cv::Point2f(0.f, 0.f),
        cv::Point2f(1.f, 0.f),
        cv::Point2f(1.f, 1.f),
        cv::Point2f(0.f, 1.f)
    };

    const cv::Point2f cell = arucoNormalizedCellSize(aruco);
    Homographer hom(aruco.imgCorners);

    for (int i = 0; i < 4; ++i)
    {
        const cv::Size window =
            subpixWindows != nullptr
                ? localSubpixWindow(
                    hom,
                    normalized[i],
                    cell.x,
                    cell.y
                )
                : cv::Size(1, 1);

        addMatch(
            aruco.objCorners[i],
            aruco.imgCorners[i],
            p3d,
            p2d,
            5.f,
            subpixWindows,
            window
        );
    }
}

static void addInnerPts(
    const ArucoHit& aruco,
    const std::vector<cv::KeyPoint>& kpoints,
    cv::flann::Index& kdtree,
    std::vector<cv::Point3f>& p3d,
    std::vector<cv::Point2f>& p2d,
    std::vector<cv::Size>* subpixWindows = nullptr
)
{
    if (aruco.bits.empty() ||
        aruco.imgCorners.size() != 4 ||
        aruco.objCorners.size() != 4)
    {
        return;
    }

    Homographer hom(aruco.imgCorners);
    const int rows = aruco.bits.rows;
    const int cols = aruco.bits.cols;
    const cv::Point2f cell = arucoNormalizedCellSize(aruco);

    for (int y = 1; y < rows; ++y)
    {
        for (int x = 1; x < cols; ++x)
        {
            const int cls = cornerType(aruco.bits, y, x);
            if (cls < 0)
                continue;

            const float u =
                static_cast<float>(x) / static_cast<float>(cols);
            const float v =
                static_cast<float>(y) / static_cast<float>(rows);
            const cv::Point2f normalized(u, v);
            const cv::Point2f predicted = hom(normalized);
            cv::Point2f real;

            if (!findFast(
                    predicted,
                    cls,
                    kpoints,
                    kdtree,
                    real))
            {
                continue;
            }

            const cv::Size window =
                subpixWindows != nullptr
                    ? localSubpixWindow(
                        hom,
                        normalized,
                        cell.x,
                        cell.y
                    )
                    : cv::Size(1, 1);

            addMatch(
                bilinearPoint(aruco.objCorners, u, v),
                real,
                p3d,
                p2d,
                4.f,
                subpixWindows,
                window
            );
        }
    }
}

static void addArucoPts(
    const ArucoHit& aruco,
    const std::vector<cv::KeyPoint>& kpoints,
    cv::flann::Index& kdtree,
    std::vector<cv::Point3f>& p3d,
    std::vector<cv::Point2f>& p2d,
    std::vector<cv::Size>* subpixWindows = nullptr
)
{
    if (aruco.imgCorners.size() != 4 ||
        aruco.objCorners.size() != 4)
    {
        return;
    }

    addAruco4(
        aruco,
        p3d,
        p2d,
        subpixWindows
    );
    addReservePts(
        aruco,
        kpoints,
        kdtree,
        p3d,
        p2d,
        subpixWindows
    );
    addInnerPts(
        aruco,
        kpoints,
        kdtree,
        p3d,
        p2d,
        subpixWindows
    );
}

// ArUco reprojection limit.
static double arucoThres(const cv::Size& imageSize)
{
    const int maxSide = std::max(imageSize.width, imageSize.height);
    return std::max(2.5, 0.007 * static_cast<double>(maxSide));
}

static std::vector<cv::Point2f> toPlane(
    const std::vector<cv::Point3f>& points
)
{
    std::vector<cv::Point2f> result;
    result.reserve(points.size());

    for (const cv::Point3f& point : points)
        result.emplace_back(point.x, point.y);

    return result;
}

// Check ArUco position against H.
static bool arucoFits(
    const ArucoHit& aruco,
    const cv::Mat& homography,
    double threshold
)
{
    if (homography.empty() ||
        aruco.objCorners.size() != 4 ||
        aruco.imgCorners.size() != 4)
    {
        return false;
    }

    const std::vector<cv::Point2f> modelCorners =
        toPlane(aruco.objCorners);

    std::vector<cv::Point2f> projectedCorners;
    cv::perspectiveTransform(
        modelCorners,
        projectedCorners,
        homography
    );

    if (projectedCorners.size() != 4)
        return false;

    double meanError = 0.0;
    double maxError = 0.0;

    for (int corner = 0; corner < 4; ++corner)
    {
        const double error = cv::norm(
            projectedCorners[corner] - aruco.imgCorners[corner]
        );

        meanError += error;
        maxError = std::max(maxError, error);
    }

    meanError *= 0.25;

    return meanError <= threshold &&
           maxError <= threshold * 2.0;
}

static double levelThres(const cv::Size& imageSize)
{
    const int maxSide = std::max(imageSize.width, imageSize.height);
    return std::max(3.0, 0.008 * static_cast<double>(maxSide));
}

static bool modelPts(
    const MarkerSet& model,
    int levelId,
    std::vector<cv::Point2f>& corners
)
{
    corners.clear();

    const auto it = model.levels.find(levelId);

    if (it == model.levels.end())
        return false;

    const auto& keypoints = it->second.getKeyptsRef();

    if (keypoints.size() < 4)
        return false;

    corners.reserve(4);

    for (int i = 0; i < 4; ++i)
        corners.push_back(keypoints[i].pt);

    return true;
}

static bool levelPts(
    const Marker& level,
    std::vector<cv::Point2f>& corners
)
{
    corners.clear();

    if (level.size() < 4)
        return false;

    corners.assign(level.begin(), level.begin() + 4);
    return true;
}

static bool levelFits(
    const MarkerSet& model,
    const Marker& detectedLevel,
    const cv::Mat& homography,
    double threshold,
    double* meanErrorOut = nullptr
)
{
    if (homography.empty())
        return false;

    std::vector<cv::Point2f> modelCorners;
    std::vector<cv::Point2f> imageCorners;

    if (!modelPts(model, detectedLevel.id, modelCorners) ||
        !levelPts(detectedLevel, imageCorners))
    {
        return false;
    }

    std::vector<cv::Point2f> projected;

    cv::perspectiveTransform(
        modelCorners,
        projected,
        homography
    );

    if (projected.size() != 4)
        return false;

    double meanError = 0.0;
    double maxError = 0.0;

    for (int i = 0; i < 4; ++i)
    {
        const double error = cv::norm(
            projected[i] - imageCorners[i]
        );

        meanError += error;
        maxError = std::max(maxError, error);
    }

    meanError *= 0.25;

    if (meanErrorOut)
        *meanErrorOut = meanError;

    return meanError <= threshold &&
           maxError <= threshold * 2.0;
}

struct MarkerRef
{
    int id = -1;
    int cells = 0;
    cv::Mat reference;
    cv::Mat validMask;
};

// Per-frame buffers for ArUco decoding.
struct ArucoDecodeWorkspace
{
    cv::Mat bits;
    cv::Mat bitAdaptive;
};

struct HashEntry
{
    std::size_t ordinal = 0;
};

struct HashIndex
{
    cv::Mat hashMask;
    bool exactKey = false;

    std::unordered_map<
        std::uint64_t,
        std::vector<HashEntry>
    > table;
};

static std::uint64_t packMaskedBits64(
    const cv::Mat& bits,
    const cv::Mat& mask
)
{
    std::uint64_t key = 0;

    for (int y = 0; y < bits.rows; ++y)
    {
        const uchar* bitRow = bits.ptr<uchar>(y);
        const uchar* maskRow = mask.ptr<uchar>(y);

        for (int x = 0; x < bits.cols; ++x)
        {
            if (maskRow[x] == 0)
                continue;

            key =
                (key << 1) |
                static_cast<std::uint64_t>(bitRow[x] != 0);
        }
    }

    return key;
}

// Detect level patterns and auxiliary ArUcos from shared candidates
class Detector
{
public:
    // Prepare search data.
    void setParams(
        const MarkerSet& set,
        const std::vector<ArucoSearchTarget>& arucoTargets
    );

    DetectionContext extractCandidates(const cv::Mat& img) const;
    DetectionEvidence detect(DetectionContext& context);

private:
    std::map<int, std::vector<MarkerRef>> markersBySize;
    std::map<int, HashIndex> hashBySize;

    void rebuildHash();

    std::vector<std::pair<int, int>> findMarkersLinear(
        const cv::Mat& bits
    ) const;

    // Number of entries in the ArUco SEARCH space.
    std::size_t arucoSearchCount = 0;

    // Reuse auxiliary ArUco dictionaries between frames.
    std::vector<cv::aruco2::DictionaryType> arucoDictionaries;
    std::map<int, cv::aruco2::Dictionary> arucoDictionaryData;

    // (dictionary, physical ArUco id) -> SEARCH ids.
    std::map<std::pair<int, int>, std::vector<int>> arucoSearchIdsById;
    cv::aruco2::DetectionParameters arucoParams;

    std::vector<std::pair<int, int>> findMarkers(
        const cv::Mat& bits
    ) const;

    static cv::Mat getBits(
        const SquareCandidate& candidate,
        const cv::Mat& gray,
        int cells
    );

    static std::vector<cv::Point2f> sort(
        const std::vector<cv::Point2f>& marker
    );

    static inline float getSubpixelValue(
        const cv::Mat& im_grey,
        const cv::Point2f& p
    );

    static double perimeter(
        const std::vector<cv::Point2f>& a
    );

    static std::vector<std::vector<cv::Point>> traceContours(
        cv::Mat& binary,
        std::size_t minSize,
        float maxRevisited
    );

    static void thres255Adaptive(
        cv::Mat& in,
        cv::Mat& out,
        int off = 2,
        int thres = 5
    );

    static int getBorderErrors(
        const cv::Mat& bits,
        int markerSize,
        int borderSize = 1
    );

    static inline int isInto(
        const std::vector<cv::Point2f>& a,
        const std::vector<cv::Point2f>& b
    );
    static inline int getMarkerId(
        cv::Mat candidateBits,
        int& idx,
        int& nrotations,
        const cv::aruco2::DetectionParameters& params,
        cv::aruco2::Dictionary& dictionary
    );

    static bool identifyArucoCandidate(
        const SquareCandidate& square,
        const cv::Mat& gray,
        cv::aruco2::DictionaryType dictionaryType,
        cv::aruco2::Dictionary& dictionary,
        const cv::aruco2::DetectionParameters& params,
        cv::RNG& rng,
        ArucoDecodeWorkspace& workspace,
        cv::aruco2::FiducialMarker& detected
    );
};
// Prepare level references and cache auxiliary ArUco dictionaries
void Detector::setParams(
    const MarkerSet& model,
    const std::vector<ArucoSearchTarget>& arucoTargets
)
{
    markersBySize.clear();
    hashBySize.clear();
    arucoDictionaries.clear();
    arucoDictionaryData.clear();
    arucoSearchIdsById.clear();
    arucoSearchCount = arucoTargets.size();

    // Prepare each auxiliary ArUco dictionary only once.
    std::set<int> preparedDictionaries;

    for (int searchId = 0;
         searchId < static_cast<int>(arucoTargets.size());
         ++searchId)
    {
        const ArucoSearchTarget& target =
            arucoTargets[searchId];

        if (target.dictId < 0)
            continue;

        const int dictionaryId =
            static_cast<int>(target.dictionary);

        arucoSearchIdsById[
            std::make_pair(dictionaryId, target.dictId)
        ].push_back(searchId);

        if (preparedDictionaries.insert(dictionaryId).second)
        {
            arucoDictionaries.push_back(target.dictionary);
            arucoDictionaryData.emplace(
                dictionaryId,
                cv::aruco2::getPredefinedDictionary(target.dictionary)
            );
        }
    }

    auto addLevelRef =
        [&](int markerId, const Marker& marker)
        {
            MarkerRef ref;
            ref.id = markerId;
            ref.cells =
                static_cast<int>(
                    std::sqrt(
                        static_cast<double>(marker.nBits())
                    )
                ) + 2;

            makeRef(
                marker,
                model,
                ref.reference,
                ref.validMask
            );

            if (cv::countNonZero(ref.validMask) > 0)
                markersBySize[ref.cells].push_back(std::move(ref));
        };

    // Reuse indexed marker data when available.
    if (!model.bits_ids.empty())
    {
        for (const auto& group : model.bits_ids)
        {
            for (int markerId : group.second)
            {
                const auto it =
                    model.levels.find(markerId);

                if (it == model.levels.end())
                    continue;

                addLevelRef(markerId, it->second);
            }
        }

    }
    else
    {
        for (const auto& item : model.levels)
            addLevelRef(item.first, item.second);
    }

    rebuildHash();
}
// Build lookup tables using discriminative bits from each level
void Detector::rebuildHash()
{
    hashBySize.clear();

    struct ScoredCell
    {
        int x = 0;
        int y = 0;
        int variation = 0;
        bool inner = false;
    };

    for (const auto& sizeGroup : markersBySize)
    {
        const int cells = sizeGroup.first;
        const std::vector<MarkerRef>& refs = sizeGroup.second;

        if (refs.empty())
            continue;

        cv::Mat commonMask = refs.front().validMask.clone();
        bool masksIdentical = true;

        for (std::size_t i = 1; i < refs.size(); ++i)
        {
            cv::Mat different;
            cv::compare(
                refs.front().validMask,
                refs[i].validMask,
                different,
                cv::CMP_NE
            );

            if (cv::countNonZero(different) != 0)
                masksIdentical = false;

            cv::bitwise_and(
                commonMask,
                refs[i].validMask,
                commonMask
            );
        }

        std::vector<ScoredCell> candidates;
        candidates.reserve(
            static_cast<std::size_t>(cv::countNonZero(commonMask))
        );

        for (int y = 0; y < commonMask.rows; ++y)
        {
            const uchar* maskRow = commonMask.ptr<uchar>(y);

            for (int x = 0; x < commonMask.cols; ++x)
            {
                if (maskRow[x] == 0)
                    continue;

                int ones = 0;

                for (const MarkerRef& ref : refs)
                {
                    if (ref.reference.at<uchar>(y, x) != 0)
                        ++ones;
                }

                const int zeros =
                    static_cast<int>(refs.size()) - ones;

                candidates.push_back(
                    ScoredCell{
                        x,
                        y,
                        std::min(ones, zeros),
                        x > 0 &&
                        y > 0 &&
                        x + 1 < commonMask.cols &&
                        y + 1 < commonMask.rows
                    }
                );
            }
        }

        if (candidates.empty())
            continue;

        // Prefer cells that separate references. For equal scores, payload
        // cells are preferred to the common external border.
        std::sort(
            candidates.begin(),
            candidates.end(),
            [](const ScoredCell& a, const ScoredCell& b)
            {
                if (a.variation != b.variation)
                    return a.variation > b.variation;
                if (a.inner != b.inner)
                    return a.inner && !b.inner;
                if (a.y != b.y)
                    return a.y < b.y;
                return a.x < b.x;
            }
        );

        const int hashBits =
            std::min<int>(
                64,
                static_cast<int>(candidates.size())
            );

        HashIndex index;
        index.hashMask =
            cv::Mat(
                commonMask.size(),
                CV_8UC1,
                cv::Scalar(0)
            );

        for (int i = 0; i < hashBits; ++i)
        {
            const ScoredCell& cell =
                candidates[static_cast<std::size_t>(i)];

            index.hashMask.at<uchar>(cell.y, cell.x) = 255;
        }

        // Hash-only identification is exact when every reference has the same
        // mask and that complete mask fits in the selected 64-bit key.
        index.exactKey =
            masksIdentical &&
            hashBits == cv::countNonZero(refs.front().validMask);

        index.table.reserve(refs.size() * 2 + 1);

        for (std::size_t ordinal = 0;
             ordinal < refs.size();
             ++ordinal)
        {
            const std::uint64_t key =
                packMaskedBits64(
                    refs[ordinal].reference,
                    index.hashMask
                );

            index.table[key].push_back(
                HashEntry{ordinal}
            );
        }

        hashBySize.emplace(
            cells,
            std::move(index)
        );
    }
}

std::vector<std::vector<cv::Point>> Detector::traceContours(cv::Mat &padded_io, size_t minSize, float maxRevisited ) {
    if (padded_io.empty() || padded_io.type() != CV_8UC1) return {};
    // Clear the image border.
    int rows = padded_io.rows;
    int cols = padded_io.cols;
    int32_t step = padded_io.step;
    uchar* data = padded_io.data;
    memset(data, 0, cols);
    memset(data + (rows - 1) * step, 0, cols);
    for (int r = 1; r < rows - 1; ++r) {
        uchar* row_ptr = data + r * step;
        row_ptr[0] = 0;
        row_ptr[cols - 1] = 0;
    }
    // 8-neighborhood offsets.
    const int offsets[16]={-1,-step-1,-step,-step+1,1,step+1,step,step-1, -1,-step-1,-step,-step+1,1,step+1,step,step-1, };
    const int dx[8] = { -1, -1,  0,  1, 1, 1, 0, -1 }, dy[8] = {  0, -1, -1, -1, 0, 1, 1,  1 };
    std::vector<std::vector<cv::Point>> contours;contours.reserve(2048);
    std::vector<cv::Point> buffer;buffer.reserve(2048);
    const uchar FOREGROUND = 255, BACKGROUND = 0,VISITED = 100;
    // Trace contours in-place.
    int rowStep=1;//std::max(1,int(minSize/6));
    for (int r = 1; r < rows - 1; r+=rowStep) {
        uchar* row_ptr = data + r * step;
        for (int c = 1; c < cols - 1;  ) {
            {
#if (CV_SIMD || CV_SIMD_SCALABLE)
                cv::v_uint8 v_zero = cv::vx_setzero_u8();
                for (; c <= cols - cv::VTraits<cv::v_uint8>::vlanes(); c+= cv::VTraits<cv::v_uint8>::vlanes())
                {
                    cv::v_uint8 vmask = (cv::v_ne(cv::vx_load((uchar*)(row_ptr + c)), v_zero));
                    if (v_check_any(vmask))
                    {
                        c += v_scan_forward(vmask);
                        break;
                    }
                }
#endif
                //process last tail
                for (; c < cols && !row_ptr[c]; ++c) ;//last tail
            }
            if( c==cols) break;//reached end of row
            if (row_ptr[c] == FOREGROUND ) {// --- 4. Tracing Loop  if is foreground
                buffer.clear();
                int curr_x = c, curr_y = r,search_idx = 1 ;
                uchar* curr_ptr = row_ptr + c,*start_ptr=curr_ptr;
                size_t ntimesRevisited=0;
                do {
                    buffer.emplace_back(curr_x, curr_y);// Add point
                    *curr_ptr = VISITED;// Mark as visited
                    // Search for next foreground pixel. We search 8 neighbors starting from search_idx
                    for (int i = 0; i < 8; ++i) {
                        int idx = search_idx + i; // index into offsets (0..15)
                        uchar* neighbor = curr_ptr + offsets[idx]; // Fast pointer arithmetic
                        if (*neighbor != BACKGROUND) {
                            // Found next boundary pixel
                            curr_ptr = neighbor;
                            int dir = (idx & 7);                             // Update Integer Coordinates using the small static tables(Use modulo 8 to get the distinct direction 0-7)
                            int next_x=curr_x+dx[dir], next_y=curr_y+dy[dir];
                            ntimesRevisited+= int(*neighbor == VISITED);
                            curr_x = next_x;curr_y = next_y;
                            search_idx = (dir + 5) & 7;
                            break;
                        }
                    }
                } while (curr_ptr != start_ptr );
                size_t bufsize=buffer.size();
                if (ntimesRevisited<= float(bufsize)*maxRevisited && bufsize >= minSize) {
                    contours.push_back(buffer);
                }
            }
            c++;//move to next pixel
            if ( row_ptr[c]){
                {
#if (CV_SIMD || CV_SIMD_SCALABLE)

                    cv::v_uint8 v_zero = cv::vx_setzero_u8();
                    for (; c <=  cols - cv::VTraits<cv::v_uint8>::vlanes(); c += cv::VTraits<cv::v_uint8>::vlanes())
                    {
                        cv::v_uint8 vmask = (cv::v_eq(cv::vx_load((uchar*)(row_ptr + c)), v_zero));
                        if (cv::v_check_any(vmask))
                        {
                            c += cv::v_scan_forward(vmask);
                            break;
                        }
                    }
#endif
                }
                for (; c < cols && row_ptr[c]; ++c) ;//last tail
            }
        }
    }
    return contours;
}

void Detector::thres255Adaptive(cv::Mat &in,cv::Mat &out,int off,int thres){
    cv::boxFilter( in, out, in.type(), cv::Size(off*2+1, off*2+1),
                  cv::Point(-1,-1), true, 4 );

    for(int i = 0; i < in.rows; i++ )
    {
        const uchar* sdata = in.ptr(i);
        uchar* ddata = out.ptr(i);
        for(int j = 0; j < in.cols; j++ )
            ddata[j] = ((ddata[j]-thres  )< sdata[j]) *255;
    }

}

int Detector::getBorderErrors(const cv::Mat &bits, int markerSize, int borderSize) {
    int sizeWithBorders = markerSize + 2 * borderSize;
    int totalErrors = 0;
    for(int y = 0; y < sizeWithBorders; y++) {
        for(int k = 0; k < borderSize; k++) {
            if(bits.ptr<unsigned char>(y)[k] != 0) totalErrors++;
            if(bits.ptr<unsigned char>(y)[sizeWithBorders - 1 - k] != 0) totalErrors++;
        }
    }
    for(int x = borderSize; x < sizeWithBorders - borderSize; x++) {
        for(int k = 0; k < borderSize; k++) {
            if(bits.ptr<unsigned char>(k)[x] != 0) totalErrors++;
            if(bits.ptr<unsigned char>(sizeWithBorders - 1 - k)[x] != 0) totalErrors++;
        }
    }
    return totalErrors;
}

int Detector::getMarkerId(
    cv::Mat candidateBits,
    int& idx,
    int& nrotations,
    const cv::aruco2::DetectionParameters& params,
    cv::aruco2::Dictionary& dictionary
)
{
    uint8_t typ = 1;

    // analyze border bits
    int maximumErrorsInBorder =
        int(dictionary.markerSize * dictionary.markerSize *
            params.maxErroneousBitsInBorderRate);

    int borderErrors =
        getBorderErrors(candidateBits, dictionary.markerSize);

    if (borderErrors > maximumErrorsInBorder)
        return 0; // border is wrong

    // take only inner bits
    cv::Mat onlyBits =
        candidateBits
            .rowRange(1, candidateBits.rows - 1)
            .colRange(1, candidateBits.cols - 1);

    onlyBits /= 255;

    // try to identify the marker
    if (!dictionary.identify(
            onlyBits,
            idx,
            nrotations,
            params.errorCorrectionRate))
    {
        return 0;
    }

    return typ;
}

int Detector::isInto(const std::vector<cv::Point2f> &a, const std::vector<cv::Point2f> &b) {
    // Lambda for point-in-polygon test (Ray Casting)
    auto countInside = [](const std::vector<cv::Point2f>& source, const std::vector<cv::Point2f>& target) -> int {
        int count = 0;
        for (const auto& pt : source) {
            bool inside = false;
            // Fixed 4-side loop logic
            for (int i = 0, j = 3; i < 4; j = i++) {
                if (((target[i].y > pt.y) != (target[j].y > pt.y)) &&
                    (pt.x < (target[j].x - target[i].x) * (pt.y - target[i].y) / (target[j].y - target[i].y) + target[i].x)) {
                    inside = !inside;
                }
            }
            if (inside) count++;
        }
        return count;
    };
    // Count how many corners of A are in B
    int aInB = countInside(a, b);
    // Count how many corners of B are in A
    int bInA = countInside(b, a);
    // Rule 1: Must contain at least one corner
    if (aInB == 0 && bInA == 0) return 0;
    // Rule 2: Compare counts
    if (aInB > bInA) return 1;
    if (bInA > aInB) return 2;
    // Default: Tie or no relative dominance
    return 0;
}

bool Detector::identifyArucoCandidate(
    const SquareCandidate& square,
    const cv::Mat& gray,
    cv::aruco2::DictionaryType dictionaryType,
    cv::aruco2::Dictionary& dictionary,
    const cv::aruco2::DetectionParameters& params,
    cv::RNG& rng,
    ArucoDecodeWorkspace& workspace,
    cv::aruco2::FiducialMarker& detected
)
{
    detected = cv::aruco2::FiducialMarker();

    if (square.corners.size() != 4 ||
        gray.empty() ||
        dictionary.markerSize <= 0)
    {
        return false;
    }

    cv::aruco2::FiducialMarker marker;
    marker.corners = square.corners;

    const int cells = dictionary.markerSize + 2;
    cv::Mat& bits = workspace.bits;
    cv::Mat& bitAdaptive = workspace.bitAdaptive;

    bits.create(cells, cells, CV_8UC1);
    bitAdaptive.create(cells, cells, CV_8UC1);

    for (int attempt = 0;
         attempt < static_cast<int>(params.maxAttemptsPerCandidate) &&
         marker.id == -1;
         ++attempt)
    {
        auto marker2 = marker;

        if (attempt != 0)
        {
            for (int c = 0; c < 4; ++c)
            {
                marker2.corners[c].x +=
                    static_cast<float>(rng.gaussian(0.75));

                marker2.corners[c].y +=
                    static_cast<float>(rng.gaussian(0.75));
            }
        }


        Homographer hom(marker2.corners);
        for (int r = 0; r < bits.rows; ++r)
        {
            for (int c = 0; c < bits.cols; ++c)
            {
                if (params.gridBitSampling == false)
                {
                    bits.at<uchar>(r, c) =
                        uchar(
                            0.5 +
                            getSubpixelValue(
                                gray,
                                hom(
                                    cv::Point2f(
                                        float(c + 0.5) / float(bits.cols),
                                        float(r + 0.5) / float(bits.rows)
                                    )
                                )
                            )
                        );
                }
                else
                {
                    double sum = 0;
                    double intrabitIncR =
                        1. / double(bits.rows * bits.rows);
                    double intrabitIncC =
                        1. / double(bits.cols * bits.cols);

                    for (int sr = 0; sr < bits.rows; ++sr)
                    {
                        for (int sc = 0; sc < bits.cols; ++sc)
                        {
                            if (sr == 0 ||
                                sr == bits.rows - 1 ||
                                sc == 0 ||
                                sc == bits.cols - 1)
                            {
                                auto pix =
                                    hom(
                                        cv::Point2f(
                                            (float(c) / float(bits.cols)) +
                                                (0.5f + float(sc)) *
                                                    static_cast<float>(intrabitIncR),
                                            (float(r) / float(bits.rows)) +
                                                (0.5f + float(sr)) *
                                                    static_cast<float>(intrabitIncC)
                                        )
                                    );

                                sum +=
                                    getSubpixelValue(gray, pix);
                            }
                        }
                    }

                    bits.at<uchar>(r, c) =
                        uchar(
                            0.5 +
                            sum /
                                (2 * bits.rows +
                                 2 * bits.cols -
                                 4)
                        );
                }
            }
        }

        if (attempt == 2)
        {
            thres255Adaptive(bits, bitAdaptive);
            bitAdaptive.copyTo(bits);
        }
        else
        {
            cv::threshold(
                bits,
                bits,
                0,
                255,
                cv::THRESH_OTSU
            );
        }

        int nrotations = 0;
        if (params.detectColorMode == 1)
            bits = ~bits;

        if (getMarkerId(
                bits,
                marker.id,
                nrotations,
                params,
                dictionary) == 0)
        {
            if (params.detectColorMode != 2)
                continue;

            bits = ~bits;

            if (getMarkerId(
                    bits,
                    marker.id,
                    nrotations,
                    params,
                    dictionary) == 0)
            {
                continue;
            }
        }

        std::rotate(
            marker.corners.begin(),
            marker.corners.begin() + 4 - nrotations,
            marker.corners.end()
        );
    }

    if (marker.id < 0)
        return false;

    marker.dictionary = dictionaryType;
    detected = std::move(marker);
    return true;
}
// Extract quadrilaterals shared by level and ArUco detection
DetectionContext Detector::extractCandidates(const cv::Mat& img) const
{
    DetectionContext context;
    if (img.empty())
        return context;

    if (img.channels() == 3)
        cv::cvtColor(img, context.gray, cv::COLOR_BGR2GRAY);
    else
        context.gray = img;

    if (context.gray.type() != CV_8UC1)
    {
        cv::Mat converted;
        context.gray.convertTo(converted, CV_8UC1);
        context.gray = converted;
    }

    cv::Mat thresImage;

    cv::boxFilter(
        context.gray,
        thresImage,
        context.gray.type(),
        cv::Size(
            arucoParams.boxFilterSize,
            arucoParams.boxFilterSize
        ),
        cv::Point(-1, -1),
        true,
        cv::BORDER_REPLICATE |
            cv::BORDER_ISOLATED
    );

    thresImage = thresImage - context.gray;

    cv::threshold(
        thresImage,
        thresImage,
        arucoParams.thres,
        255,
        cv::THRESH_BINARY
    );

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Point> approxCurve;

    const int minSizeSq =
        arucoParams.minSize * arucoParams.minSize;
    const int minSize4 =
        4 * arucoParams.minSize;

    contours =
        traceContours(
            thresImage,
            static_cast<std::size_t>(minSize4),
            arucoParams.maxTimesRevisited
        );


    context.squares.reserve(contours.size());

    for (std::size_t i = 0; i < contours.size(); ++i)
    {
        cv::approxPolyDP(
            contours[i],
            approxCurve,
            static_cast<double>(contours[i].size()) * 0.03,
            true
        );

        if (approxCurve.size() != 4 ||
            !cv::isContourConvex(approxCurve))
        {
            continue;
        }

        if (((approxCurve[0].x - approxCurve[1].x) *
             (approxCurve[0].x - approxCurve[1].x) +
             (approxCurve[0].y - approxCurve[1].y) *
             (approxCurve[0].y - approxCurve[1].y)) < minSizeSq)
        {
            continue;
        }

        if (((approxCurve[1].x - approxCurve[2].x) *
             (approxCurve[1].x - approxCurve[2].x) +
             (approxCurve[1].y - approxCurve[2].y) *
             (approxCurve[1].y - approxCurve[2].y)) < minSizeSq)
        {
            continue;
        }

        if (((approxCurve[2].x - approxCurve[3].x) *
             (approxCurve[2].x - approxCurve[3].x) +
             (approxCurve[2].y - approxCurve[3].y) *
             (approxCurve[2].y - approxCurve[3].y)) < minSizeSq)
        {
            continue;
        }

        if (((approxCurve[3].x - approxCurve[0].x) *
             (approxCurve[3].x - approxCurve[0].x) +
             (approxCurve[3].y - approxCurve[0].y) *
             (approxCurve[3].y - approxCurve[0].y)) < minSizeSq)
        {
            continue;
        }

        std::vector<cv::Point2f> marker;
        marker.reserve(4);

        for (int j = 0; j < 4; ++j)
        {
            marker.emplace_back(
                static_cast<float>(approxCurve[j].x),
                static_cast<float>(approxCurve[j].y)
            );
        }

        // Keep clockwise corner order.
        marker = sort(marker);

        const bool levelCandidate =
            static_cast<int>(contours[i].size()) >=
            kMinLevelContourPoints;

        context.squares.emplace_back(
            std::move(marker),
            levelCandidate
        );
    }


    return context;
}

cv::Mat Detector::getBits(
    const SquareCandidate& candidate,
    const cv::Mat& gray,
    int cells
)
{
    cv::Mat bits(cells, cells, CV_8UC1);
    int sum = 0;

    for (int r = 0; r < bits.rows; ++r)
    {
        for (int c = 0; c < bits.cols; ++c)
        {
            const uchar pixelValue =
                uchar(
                    0.5 +
                    getSubpixelValue(
                        gray,
                        candidate.homography(
                            cv::Point2f(
                                float(c + 0.5) / float(bits.cols),
                                float(r + 0.5) / float(bits.rows)
                            )
                        )
                    )
                );

            bits.at<uchar>(r, c) = pixelValue;
            sum += pixelValue;
        }
    }

    const double mean =
        static_cast<double>(sum) /
        static_cast<double>(cells * cells);

    cv::threshold(
        bits,
        bits,
        mean,
        255,
        cv::THRESH_BINARY
    );

    return bits;
}
// Identify level patterns and auxiliary ArUcos in the candidates
DetectionEvidence Detector::detect(
    DetectionContext& context
)
{
    struct LevelCandidate
    {
        int id = -1;
        bool canStart = false;
        std::vector<cv::Point2f> corners;
    };

    struct ArucoCandidate
    {
        int searchId = -1;
        std::vector<cv::Point2f> corners;
    };

    DetectionEvidence evidence;

    if (context.gray.empty())
        return evidence;

    std::vector<LevelCandidate> levelCandidates;
    std::vector<ArucoCandidate> arucoCandidates;
    std::vector<bool> arucoCandidateAvailable(
        context.squares.size(),
        true
    );


    for (std::size_t candidateIndex = 0;
         candidateIndex < context.squares.size();
         ++candidateIndex)
    {
        SquareCandidate& square =
            context.squares[candidateIndex];

        if (!square.levelCandidate)
            continue;

        for (const auto& group : markersBySize)
        {
            const cv::Mat bits =
                getBits(
                    square,
                    context.gray,
                    group.first
                );

            const std::vector<std::pair<int, int>> matches =
                findMarkers(bits);

            if (matches.empty())
                continue;

            const int firstId =
                matches.front().first;

            arucoCandidateAvailable[candidateIndex] = false;

            // The contour corners are integer pixels on the border of the
            // black region, about half a pixel inside the real corner.
            // Refine them like the ArUco corners, with a window of one level
            // cell in the local perspective.
            {
                const std::array<cv::Point2f, 4> normalizedCorners = {
                    cv::Point2f(0.f, 0.f),
                    cv::Point2f(1.f, 0.f),
                    cv::Point2f(1.f, 1.f),
                    cv::Point2f(0.f, 1.f)
                };

                const double cellStep =
                    1.0 / static_cast<double>(std::max(2, group.first));

                std::vector<cv::Size> windows;
                windows.reserve(4);

                for (int corner = 0; corner < 4; ++corner)
                {
                    windows.push_back(
                        prisma::localSubpixWindow(
                            square.homography,
                            normalizedCorners[corner],
                            cellStep,
                            cellStep
                        )
                    );
                }

                prisma::refineSubpixGrouped(
                    context.gray,
                    square.corners,
                    windows,
                    cv::TermCriteria(
                        cv::TermCriteria::MAX_ITER |
                            cv::TermCriteria::EPS,
                        12,
                        0.005
                    )
                );

                square.homography =
                    prisma::Homographer(square.corners);
            }

            for (const auto& match : matches)
            {
                std::vector<cv::Point2f> corners =
                    square.corners;

                std::rotate(
                    corners.begin(),
                    corners.begin() +
                        4 - match.second,
                    corners.end()
                );

                levelCandidates.push_back(
                    LevelCandidate{
                        match.first,
                        match.first == firstId,
                        std::move(corners)
                    }
                );
            }

            // Keep the first valid marker-size match.
            break;
        }
    }


    std::vector<cv::aruco2::FiducialMarker> detectedArucos;

    cv::RNG rng;
    ArucoDecodeWorkspace arucoWorkspace;

    for (cv::aruco2::DictionaryType dictionaryType :
         arucoDictionaries)
    {
        const int dictionaryId =
            static_cast<int>(dictionaryType);

        const auto dictionaryIt =
            arucoDictionaryData.find(dictionaryId);

        if (dictionaryIt ==
            arucoDictionaryData.end())
        {
            continue;
        }

        cv::aruco2::Dictionary& dictionary =
            dictionaryIt->second;

        std::vector<cv::aruco2::FiducialMarker>
            currentDictionaryDetected;

        for (std::size_t candidateIndex = 0;
             candidateIndex < context.squares.size();
             ++candidateIndex)
        {
            if (!arucoCandidateAvailable[candidateIndex])
                continue;


            cv::aruco2::FiducialMarker detected;

            if (!identifyArucoCandidate(
                    context.squares[candidateIndex],
                    context.gray,
                    dictionaryType,
                    dictionary,
                    arucoParams,
                    rng,
                    arucoWorkspace,
                    detected))
            {
                continue;
            }

            currentDictionaryDetected.push_back(
                std::move(detected)
            );
            arucoCandidateAvailable[candidateIndex] = false;
        }

        std::sort(
            currentDictionaryDetected.begin(),
            currentDictionaryDetected.end(),
            [](const cv::aruco2::FiducialMarker& a,
               const cv::aruco2::FiducialMarker& b)
            {
                return a.id < b.id;
            }
        );

        {
            std::vector<bool> toRemove(
                currentDictionaryDetected.size(),
                false
            );

            for (int i = 0;
                 i < static_cast<int>(currentDictionaryDetected.size()) - 1;
                 ++i)
            {
                for (int j = i + 1;
                     j < static_cast<int>(currentDictionaryDetected.size()) &&
                         !toRemove[i];
                     ++j)
                {
                    if (currentDictionaryDetected[i].id ==
                        currentDictionaryDetected[j].id)
                    {
                        const int res =
                            isInto(
                                currentDictionaryDetected[i].corners,
                                currentDictionaryDetected[j].corners
                            );

                        // Average pixel distance between both detections.
                        int pixDistAvr = 0;
                        for (int c = 0; c < 4; ++c)
                        {
                            pixDistAvr +=
                                cv::norm(
                                    currentDictionaryDetected[i].corners[c] -
                                    currentDictionaryDetected[j].corners[c]
                                );
                        }
                        pixDistAvr /= 4;

                        // Average bit length for this marker.
                        double avrgLen = 0.0;
                        for (int c = 0; c < 4; ++c)
                        {
                            avrgLen +=
                                cv::norm(
                                    currentDictionaryDetected[i].corners[c] -
                                    currentDictionaryDetected[i]
                                        .corners[(c + 1) % 4]
                                );
                        }
                        avrgLen /= 4.0;
                        avrgLen /= dictionary.markerSize;

                        if (pixDistAvr > avrgLen)
                            continue;

                        if (res == 1)
                            toRemove[i] = true;
                        else if (res == 2)
                            toRemove[j] = true;
                    }
                }
            }

            // Move to the final list only the detections not marked for removal.
            for (std::size_t i = 0;
                 i < currentDictionaryDetected.size();
                 ++i)
            {
                if (!toRemove[i])
                {
                    detectedArucos.push_back(
                        std::move(currentDictionaryDetected[i])
                    );
                }
            }
        }
    }

    // Refine each detected ArUco using the local projected size of one
    // marker cell at each corner. This keeps cornerSubPix tied to the real
    // perspective of the marker instead of using one average window.
    if (!detectedArucos.empty())
    {
        std::vector<cv::Point2f> corners;
        std::vector<cv::Size> windows;
        std::vector<std::pair<std::size_t, int>> owners;

        corners.reserve(detectedArucos.size() * 4);
        windows.reserve(detectedArucos.size() * 4);
        owners.reserve(detectedArucos.size() * 4);

        const std::array<cv::Point2f, 4> normalizedCorners = {
            cv::Point2f(0.f, 0.f),
            cv::Point2f(1.f, 0.f),
            cv::Point2f(1.f, 1.f),
            cv::Point2f(0.f, 1.f)
        };

        for (std::size_t markerIndex = 0;
             markerIndex < detectedArucos.size();
             ++markerIndex)
        {
            const cv::aruco2::FiducialMarker& marker =
                detectedArucos[markerIndex];

            if (marker.corners.size() != 4)
                continue;

            int fullCells = 8;
            const auto dictionaryIt =
                arucoDictionaryData.find(
                    static_cast<int>(marker.dictionary)
                );

            if (dictionaryIt != arucoDictionaryData.end() &&
                dictionaryIt->second.markerSize > 0)
            {
                // markerSize excludes the one-cell black border on each side.
                fullCells = dictionaryIt->second.markerSize + 2;
            }

            const double cellStep =
                1.0 / static_cast<double>(std::max(2, fullCells));

            prisma::Homographer hom(marker.corners);

            for (int corner = 0; corner < 4; ++corner)
            {
                corners.push_back(marker.corners[corner]);
                windows.push_back(
                    prisma::localSubpixWindow(
                        hom,
                        normalizedCorners[corner],
                        cellStep,
                        cellStep
                    )
                );
                owners.emplace_back(markerIndex, corner);
            }
        }

        prisma::refineSubpixGrouped(
            context.gray,
            corners,
            windows,
            cv::TermCriteria(
                cv::TermCriteria::MAX_ITER |
                    cv::TermCriteria::EPS,
                12,
                0.005
            )
        );

        for (std::size_t i = 0; i < corners.size(); ++i)
        {
            detectedArucos[owners[i].first]
                .corners[owners[i].second] = corners[i];
        }
    }

    for (const cv::aruco2::FiducialMarker& detected :
         detectedArucos)
    {
        if (detected.id < 0 ||
            detected.corners.size() != 4)
        {
            continue;
        }

        const auto searchIds =
            arucoSearchIdsById.find(
                std::make_pair(
                    static_cast<int>(
                        detected.dictionary
                    ),
                    detected.id
                )
            );

        if (searchIds == arucoSearchIdsById.end())
            continue;

        for (int searchId : searchIds->second)
        {
            arucoCandidates.push_back(
                ArucoCandidate{
                    searchId,
                    detected.corners
                }
            );
        }
    }


    auto samePlace =
        [](const std::vector<cv::Point2f>& a,
           const std::vector<cv::Point2f>& b)
        {
            if (a.size() != 4 || b.size() != 4)
                return false;

            cv::Point2f centerA(0.f, 0.f);
            cv::Point2f centerB(0.f, 0.f);
            double sideA = 0.0;
            double sideB = 0.0;

            for (int i = 0; i < 4; ++i)
            {
                centerA += a[i];
                centerB += b[i];

                sideA +=
                    cv::norm(
                        a[i] -
                        a[(i + 1) % 4]
                    );

                sideB +=
                    cv::norm(
                        b[i] -
                        b[(i + 1) % 4]
                    );
            }

            centerA *= 0.25f;
            centerB *= 0.25f;
            sideA *= 0.25;
            sideB *= 0.25;

            if (sideA <= 0.0 || sideB <= 0.0)
                return false;

            const double smaller =
                std::min(sideA, sideB);

            const double larger =
                std::max(sideA, sideB);

            if (larger / smaller > 1.35)
                return false;

            return cv::norm(centerA - centerB) <=
                   std::max(
                       3.0,
                       smaller * 0.20
                   );
        };
    std::sort(
        levelCandidates.begin(),
        levelCandidates.end(),
        [](const LevelCandidate& a,
           const LevelCandidate& b)
        {
            if (a.id != b.id)
                return a.id < b.id;

            return perimeter(a.corners) >
                   perimeter(b.corners);
        }
    );

    std::vector<LevelCandidate> uniqueLevels;
    uniqueLevels.reserve(
        levelCandidates.size()
    );

    for (LevelCandidate& candidate :
         levelCandidates)
    {
        bool repeated = false;

        for (LevelCandidate& current :
             uniqueLevels)
        {
            if (current.id != candidate.id)
                continue;

            if (!samePlace(
                    current.corners,
                    candidate.corners))
            {
                continue;
            }

            current.canStart =
                current.canStart ||
                candidate.canStart;

            repeated = true;
            break;
        }

        if (!repeated)
        {
            uniqueLevels.push_back(
                std::move(candidate)
            );
        }
    }
    std::sort(
        arucoCandidates.begin(),
        arucoCandidates.end(),
        [](const ArucoCandidate& a,
           const ArucoCandidate& b)
        {
            if (a.searchId != b.searchId)
                return a.searchId < b.searchId;

            return perimeter(a.corners) >
                   perimeter(b.corners);
        }
    );

    std::vector<ArucoCandidate> uniqueArucos;
    uniqueArucos.reserve(
        arucoCandidates.size()
    );

    for (ArucoCandidate& candidate :
         arucoCandidates)
    {
        bool repeated = false;

        for (const ArucoCandidate& current :
             uniqueArucos)
        {
            if (current.searchId !=
                candidate.searchId)
            {
                continue;
            }

            if (samePlace(
                    current.corners,
                    candidate.corners))
            {
                repeated = true;
                break;
            }
        }

        if (!repeated)
        {
            uniqueArucos.push_back(
                std::move(candidate)
            );
        }
    }

    evidence.levels.reserve(
        uniqueLevels.size()
    );

    for (const LevelCandidate& candidate :
         uniqueLevels)
    {
        LevelHit hit;
        hit.id = candidate.id;
        hit.canStart = candidate.canStart;
        hit.imgCorners = candidate.corners;

        evidence.levels.push_back(
            std::move(hit)
        );
    }

    evidence.arucos.reserve(
        uniqueArucos.size()
    );

    for (const ArucoCandidate& candidate :
         uniqueArucos)
    {
        if (candidate.searchId < 0 ||
            candidate.searchId >=
                static_cast<int>(arucoSearchCount))
        {
            continue;
        }

        DetectedAruco detected;
        detected.searchId = candidate.searchId;
        detected.imgCorners = candidate.corners;

        evidence.arucos.push_back(
            std::move(detected)
        );
    }


    return evidence;
}

std::vector<std::pair<int, int>> Detector::findMarkersLinear(
    const cv::Mat& bits
) const
{
    std::vector<std::pair<int, int>> matches;

    if (bits.empty() ||
        bits.rows != bits.cols ||
        bits.type() != CV_8UC1)
    {
        return matches;
    }

    const auto group =
        markersBySize.find(bits.rows);

    if (group == markersBySize.end())
        return matches;

    std::set<int> found;
    cv::Mat rotated = bits;

    for (int rotation = 0; rotation < 4; ++rotation)
    {
        for (const MarkerRef& ref : group->second)
        {
            if (found.count(ref.id) != 0)
                continue;

            if (hammingFast(
                    rotated,
                    ref.reference,
                    ref.validMask,
                    0) != 0)
            {
                continue;
            }

            found.insert(ref.id);
            matches.emplace_back(
                ref.id,
                rotation
            );
        }

        if (rotation < 3)
            rotated = rotateBits(rotated);
    }

    return matches;
}

std::vector<std::pair<int, int>> Detector::findMarkers(
    const cv::Mat& bits
) const
{
    if (bits.empty() ||
        bits.rows != bits.cols ||
        bits.type() != CV_8UC1)
    {
        return {};
    }

    const auto refsIt =
        markersBySize.find(bits.rows);

    if (refsIt == markersBySize.end())
        return {};

    const auto hashIt =
        hashBySize.find(bits.rows);

    // If no common key could be built for this size, keep the original exact
    // linear path as a correctness fallback.
    if (hashIt == hashBySize.end() ||
        hashIt->second.hashMask.empty())
    {
        return findMarkersLinear(bits);
    }

    const std::vector<MarkerRef>& refs = refsIt->second;
    const HashIndex& index = hashIt->second;

    std::vector<std::pair<int, int>> matches;
    std::set<int> found;
    cv::Mat rotated = bits;

    for (int rotation = 0; rotation < 4; ++rotation)
    {
        const std::uint64_t key =
            packMaskedBits64(
                rotated,
                index.hashMask
            );

        const auto bucketIt =
            index.table.find(key);

        if (bucketIt != index.table.end())
        {
            // Entries are stored in the same ordinal order used by the old
            // linear scan, so observable match ordering is preserved.
            for (const HashEntry& entry : bucketIt->second)
            {
                if (entry.ordinal >= refs.size())
                    continue;

                const MarkerRef& ref =
                    refs[entry.ordinal];

                if (found.count(ref.id) != 0)
                    continue;

                // If the compact key is only an index, verify the complete
                // original valid mask with the same zero-error criterion.
                if (!index.exactKey &&
                    hammingFast(
                        rotated,
                        ref.reference,
                        ref.validMask,
                        0) != 0)
                {
                    continue;
                }

                found.insert(ref.id);
                matches.emplace_back(
                    ref.id,
                    rotation
                );
            }
        }

        if (rotation < 3)
            rotated = rotateBits(rotated);
    }

    return matches;
}

float Detector::getSubpixelValue(const cv::Mat &im_grey, const cv::Point2f &p) {
    // Bilinear interpolation.
    const int ix = static_cast<int>(p.x);
    const int iy = static_cast<int>(p.y);


    // A full 2x2 patch is required.
    if (ix < 0 || iy < 0 || ix >= im_grey.cols - 1 || iy >= im_grey.rows - 1) {
        return 0.0f;
    }

    const float dx = p.x - ix;
    const float dy = p.y - iy;
    const uchar* ptr = im_grey.ptr<uchar>(iy) + ix;
    const size_t step = im_grey.step;
    const float p00 = static_cast<float>(ptr[0]);        // Top-Left
    const float p01 = static_cast<float>(ptr[1]);        // Top-Right
    const float p10 = static_cast<float>(ptr[step]);     // Bottom-Left
    const float p11 = static_cast<float>(ptr[step + 1]); // Bottom-Right
    const float top = p00 + dx * (p01 - p00);// Interpolate Top Row Horizontally
    const float bot = p10 + dx * (p11 - p10);    // Interpolate Bottom Row Horizontallys
    return top + dy * (bot - top);
}

std::vector<cv::Point2f> Detector::sort(
    const std::vector<cv::Point2f>& marker
)
{
    std::vector<cv::Point2f> result = marker;

    const double dx1 =
        result[1].x - result[0].x;
    const double dy1 =
        result[1].y - result[0].y;
    const double dx2 =
        result[2].x - result[0].x;
    const double dy2 =
        result[2].y - result[0].y;

    if (dx1 * dy2 - dy1 * dx2 < 0.0)
        std::swap(result[1], result[3]);

    return result;
}

double Detector::perimeter(
    const std::vector<cv::Point2f>& points
)
{
    double sum = 0.0;

    for (std::size_t i = 0;
         i < points.size();
         ++i)
    {
        sum += cv::norm(
            points[i] -
            points[(i + 1) % points.size()]
        );
    }

    return sum;
}

static void addPosePoints(
    const MarkerSet& model,
    const std::vector<Marker>& levels,
    const std::vector<ArucoHit>& arucos,
    const cv::Mat& homography,
    const cv::Mat& gray,
    const std::vector<cv::KeyPoint>& kpoints,
    cv::flann::Index* kdtree,
    std::vector<cv::Point3f>& p3d,
    std::vector<cv::Point2f>& p2d
)
{
    p3d.clear();
    p2d.clear();

    std::vector<cv::Size> subpixWindows;

    if (kdtree && !kpoints.empty())
    {
        if (!homography.empty())
        {
            for (const auto& item :
                 model.levels)
            {
                const Marker& modelMarker = item.second;
                const std::vector<cv::KeyPoint>& modelKeypoints =
                    modelMarker.getKeyptsRef();

                if (modelKeypoints.empty())
                    continue;

                const int bitsPerSide = std::max(
                    1,
                    static_cast<int>(std::lround(std::sqrt(
                        static_cast<double>(modelMarker.nBits()))))
                );

                const double modelCellSize =
                    static_cast<double>(modelMarker.getMarkerSize()) /
                    static_cast<double>(bitsPerSide + 2);

                if (!std::isfinite(modelCellSize) ||
                    modelCellSize <= 0.0)
                {
                    continue;
                }

                std::vector<cv::Point2f> modelPoints;
                modelPoints.reserve(modelKeypoints.size());

                for (const cv::KeyPoint& keypoint : modelKeypoints)
                    modelPoints.push_back(keypoint.pt);

                std::vector<cv::Point2f> projectedPoints;
                cv::perspectiveTransform(
                    modelPoints,
                    projectedPoints,
                    homography
                );

                bool consider = !projectedPoints.empty();

                for (std::size_t i = 0;
                     i + 1 < projectedPoints.size() && consider;
                     ++i)
                {
                    for (std::size_t j = i + 1;
                         j < projectedPoints.size();
                         ++j)
                    {
                        const float dx =
                            projectedPoints[i].x -
                            projectedPoints[j].x;
                        const float dy =
                            projectedPoints[i].y -
                            projectedPoints[j].y;

                        if (dx * dx + dy * dy < 150.f)
                        {
                            consider = false;
                            break;
                        }
                    }
                }

                if (consider)
                {
                    for (std::size_t index = 0;
                         index < projectedPoints.size();
                         ++index)
                    {
                        const cv::Point2f& projected =
                            projectedPoints[index];

                        if (projected.x <= 0.f ||
                            projected.x >= gray.cols ||
                            projected.y <= 0.f ||
                            projected.y >= gray.rows)
                        {
                            continue;
                        }

                        cv::Point2f realPoint;

                        if (!findFast(
                                projected,
                                modelKeypoints[index].class_id,
                                kpoints,
                                *kdtree,
                                realPoint))
                        {
                            continue;
                        }

                        const cv::Size window =
                            localSubpixWindow(
                                homography,
                                modelPoints[index],
                                modelCellSize,
                                modelCellSize
                            );

                        addMatch(
                            cv::Point3f(
                                modelPoints[index].x,
                                modelPoints[index].y,
                                0.f
                            ),
                            realPoint,
                            p3d,
                            p2d,
                            4.f,
                            &subpixWindows,
                            window
                        );
                    }
                }
                else
                {
                    for (const Marker& detected : levels)
                    {
                        if (detected.id != item.first)
                            continue;

                        for (int corner = 0;
                             corner < 4 &&
                             corner < static_cast<int>(detected.size()) &&
                             corner < static_cast<int>(modelKeypoints.size());
                             ++corner)
                        {
                            const cv::Point2f& modelPoint =
                                modelKeypoints[corner].pt;

                            const cv::Size window =
                                localSubpixWindow(
                                    homography,
                                    modelPoint,
                                    modelCellSize,
                                    modelCellSize
                                );

                            addMatch(
                                cv::Point3f(
                                    modelPoint.x,
                                    modelPoint.y,
                                    0.f
                                ),
                                detected[corner],
                                p3d,
                                p2d,
                                5.f,
                                &subpixWindows,
                                window
                            );
                        }

                        break;
                    }
                }
            }
        }

        for (const ArucoHit& aruco : arucos)
        {
            addArucoPts(
                aruco,
                kpoints,
                *kdtree,
                p3d,
                p2d,
                &subpixWindows
            );
        }

        if (!p2d.empty() &&
            subpixWindows.size() == p2d.size())
        {
            refineSubpixGrouped(
                gray,
                p2d,
                subpixWindows,
                cv::TermCriteria(
                    cv::TermCriteria::MAX_ITER |
                        cv::TermCriteria::EPS,
                    12,
                    0.005
                )
            );
        }
    }
    else
    {
        for (const ArucoHit& aruco : arucos)
        {
            if (aruco.imgCorners.size() == 4 &&
                aruco.objCorners.size() == 4)
            {
                addAruco4(
                    aruco,
                    p3d,
                    p2d
                );
            }
        }
    }

    removeDup(
        p3d,
        p2d,
        4.f
    );
}

} // namespace prisma
} // anonymous namespace
// PRISMarker public API.
namespace cv {
namespace aruco2 {
// Predefined PRISMarkers
namespace {

// Cell size in pixels of the innermost level. It must be a multiple of
// kPrismaBitSizeStep: each auxiliary ArUco ((n + 4) = 10 cells with its
// white margin) fills 2 level cells, and the central ArUco (8 cells) fills 4,
// so with other sizes their cells are fractional and nearest-neighbour
// resizing draws them up to one pixel off-center, which the detector, which
// assumes centred markers, turns into a pose bias. The outer levels have
// 3, 9, ... times this size, so they are exact too.
constexpr int kPrismaInnerCellSize = 10;
constexpr int kPrismaBitSizeStep = 10;
constexpr int kPrismaReservationCells = 2;
constexpr int kPrismaChildPaddingCells = 1;

using detail::PDict;
using detail::PMark;
using detail::PLevel;

[[noreturn]] static void prismarkerFail(
    const std::string& message,
    const char* functionName
)
{
    throw cv::Exception(
        cv::Error::StsBadArg,
        message,
        functionName,
        __FILE__,
        __LINE__
    );
}


static const PMark& getPrismaMarker(
    const PDict& dictionary,
    int markerId
)
{
    const auto it = std::find_if(
        dictionary.markers.begin(),
        dictionary.markers.end(),
        [markerId](const PMark& marker)
        {
            return marker.id == markerId;
        }
    );

    if (it == dictionary.markers.end())
    {
        prismarkerFail(
            "PRISMarker id not found: " + std::to_string(markerId),
            "getPrismaMarker"
        );
    }

    return *it;
}

static cv::Mat bitsToMat(const PLevel& level)
{
    cv::Mat bits(level.n, level.n, CV_8UC1);

    for (int y = 0; y < level.n; ++y)
    {
        uchar* row = bits.ptr<uchar>(y);

        for (int x = 0; x < level.n; ++x)
            row[x] = level.bits[static_cast<size_t>(y * level.n + x)];
    }

    return bits;
}

static std::array<cv::Point2i, 4> arucoStarts(
    PrismaLayout layout,
    int n
)
{
    if (layout == PRISMA_LAYOUT_CARDINAL)
    {
        const int center = (n - kPrismaReservationCells) / 2;

        return {
            cv::Point2i(center, 0),
            cv::Point2i(n - kPrismaReservationCells, center),
            cv::Point2i(center, n - kPrismaReservationCells),
            cv::Point2i(0, center)
        };
    }

    return {
        cv::Point2i(0, 0),
        cv::Point2i(n - kPrismaReservationCells, 0),
        cv::Point2i(n - kPrismaReservationCells, n - kPrismaReservationCells),
        cv::Point2i(0, n - kPrismaReservationCells)
    };
}

static void clearMask(
    cv::Mat& mask,
    int x,
    int y,
    int width,
    int height
)
{
    const cv::Rect bounds(0, 0, mask.cols, mask.rows);
    const cv::Rect requested(x, y, width, height);
    const cv::Rect clipped = requested & bounds;

    if (!clipped.empty())
        mask(clipped).setTo(0);
}

static cv::Mat levelMask(
    const PLevel& level,
    bool maskChildRegion
)
{
    cv::Mat mask(level.n, level.n, CV_8UC1, cv::Scalar(255));

    for (const cv::Point2i& start :
         arucoStarts(level.layout, level.n))
    {
        clearMask(
            mask,
            start.x,
            start.y,
            kPrismaReservationCells,
            kPrismaReservationCells
        );
    }

    if (maskChildRegion)
    {
        const int ring = (level.n - level.k) / 2;
        const int childCells = level.k - 2 * kPrismaChildPaddingCells;
        const int childStart = ring + kPrismaChildPaddingCells;

        if (childCells > 0)
            clearMask(mask, childStart, childStart, childCells, childCells);
    }

    return mask;
}

static std::vector<cv::Point3f> squareCorners(float side)
{
    const float half = side * 0.5f;

    return {
        cv::Point3f(-half,  half, 0.f),
        cv::Point3f( half,  half, 0.f),
        cv::Point3f( half, -half, 0.f),
        cv::Point3f(-half, -half, 0.f)
    };
}

static std::array<cv::Point3f, 4> gridCorners(
    const prisma::Marker& marker,
    float x,
    float y,
    float width,
    float height
)
{
    const int fullCells = marker.mat().cols + 2;

    const cv::Point3f tl(marker.keypts[0].pt.x, marker.keypts[0].pt.y, 0.f);
    const cv::Point3f tr(marker.keypts[1].pt.x, marker.keypts[1].pt.y, 0.f);
    const cv::Point3f bl(marker.keypts[3].pt.x, marker.keypts[3].pt.y, 0.f);

    const cv::Point3f ux(
        (tr.x - tl.x) / static_cast<float>(fullCells),
        (tr.y - tl.y) / static_cast<float>(fullCells),
        0.f
    );
    const cv::Point3f uy(
        (bl.x - tl.x) / static_cast<float>(fullCells),
        (bl.y - tl.y) / static_cast<float>(fullCells),
        0.f
    );

    auto point = [&](float col, float row)
    {
        return cv::Point3f(
            tl.x + ux.x * col + uy.x * row,
            tl.y + ux.y * col + uy.y * row,
            0.f
        );
    };

    return {
        point(x, y),
        point(x + width, y),
        point(x + width, y + height),
        point(x, y + height)
    };
}

static std::set<int> getUniqueArucoIds(
    const std::vector<prisma::ArucoRef>& refs
)
{
    std::map<std::pair<int, int>, int> counts;

    for (const prisma::ArucoRef& ref : refs)
    {
        counts[
            std::make_pair(
                static_cast<int>(ref.dictionary),
                ref.dictId
            )
        ]++;
    }

    std::set<int> result;

    for (const prisma::ArucoRef& ref : refs)
    {
        const auto key =
            std::make_pair(
                static_cast<int>(ref.dictionary),
                ref.dictId
            );

        if (counts[key] == 1)
            result.insert(ref.internalId);
    }

    return result;
}

static void putAruco(
    cv::Mat& image,
    DictionaryType dictionary,
    int id,
    const cv::Rect& roi,
    bool externalWhiteBorder
)
{
    const DictInfo& info = getDictInfo(dictionary);

    if (id < 0 || id >= info.count)
    {
        prismarkerFail(
            "The auxiliary dictionary does not contain ArUco id " +
                std::to_string(id),
            "printPrisma"
        );
    }

    cv::Mat fiducial;
    cv::aruco2::getFiducialMarkerImage(
        fiducial,
        dictionary,
        id,
        1,
        externalWhiteBorder
    );

    if (fiducial.empty())
        prismarkerFail("Could not generate auxiliary ArUco", "printPrisma");

    cv::Mat resized;
    cv::resize(fiducial, resized, roi.size(), 0.0, 0.0, cv::INTER_NEAREST);
    resized.copyTo(image(roi));
}
// Render one level with its auxiliary ArUcos.
static cv::Mat drawFLevel(
    const PMark& marker,
    int levelIndex,
    int cellSize,
    DictionaryType dictionary
)
{
    const PLevel& level = marker.levels.at(levelIndex);
    const int fullCells = level.n + 2;
    const int dataOffset = 1;

    cv::Mat image(
        fullCells * cellSize,
        fullCells * cellSize,
        CV_8UC1,
        cv::Scalar(0)
    );

    for (int y = 0; y < level.n; ++y)
    {
        for (int x = 0; x < level.n; ++x)
        {
            if (level.bits[static_cast<size_t>(y * level.n + x)] == 0)
                continue;

            image(
                cv::Rect(
                    (x + dataOffset) * cellSize,
                    (y + dataOffset) * cellSize,
                    cellSize,
                    cellSize
                )
            ).setTo(255);
        }
    }

    const std::array<cv::Point2i, 4> starts =
        arucoStarts(level.layout, level.n);

    for (int slot = 0; slot < 4; ++slot)
    {
        putAruco(
            image,
            dictionary,
            level.aruco[slot],
            cv::Rect(
                (starts[slot].x + dataOffset) * cellSize,
                (starts[slot].y + dataOffset) * cellSize,
                kPrismaReservationCells * cellSize,
                kPrismaReservationCells * cellSize
            ),
            true
        );
    }

    const int ring = (level.n - level.k) / 2;
    const int childCells =
        level.k - 2 * kPrismaChildPaddingCells;
    const int childStart =
        dataOffset + ring + kPrismaChildPaddingCells;
    const cv::Rect childRoi(
        childStart * cellSize,
        childStart * cellSize,
        childCells * cellSize,
        childCells * cellSize
    );

    const bool innermost =
        levelIndex + 1 == static_cast<int>(marker.levels.size());

    if (innermost)
    {
        putAruco(
            image,
            dictionary,
            marker.center,
            childRoi,
            false
        );
    }
    else
    {
        const PLevel& childLevel = marker.levels[levelIndex + 1];
        const int childCellSize = std::max(
            1,
            (childCells * cellSize) / (childLevel.n + 2)
        );

        cv::Mat child = drawFLevel(
            marker,
            levelIndex + 1,
            childCellSize,
            dictionary
        );

        if (child.size() != childRoi.size())
            cv::resize(child, child, childRoi.size(), 0.0, 0.0, cv::INTER_NEAREST);

        child.copyTo(image(childRoi));
    }

    return image;
}
// Combine all levels into the final printable marker
static cv::Mat drawPRISMarker(
    const PMark& marker,
    DictionaryType dictionary,
    int lastLevelBitSize
)
{
    // Calculate the outside cell size from the last level.
    int outerCellSize = lastLevelBitSize;

    for (int levelIndex = static_cast<int>(marker.levels.size()) - 2;
         levelIndex >= 0;
         --levelIndex)
    {
        const PLevel& parent = marker.levels[levelIndex];
        const PLevel& child = marker.levels[levelIndex + 1];
        const int childCells =
            parent.k - 2 * kPrismaChildPaddingCells;

        outerCellSize =
            (outerCellSize * (child.n + 2) + childCells - 1) /
            childCells;
    }

    cv::Mat image = drawFLevel(
        marker,
        0,
        outerCellSize,
        dictionary
    );

    cv::copyMakeBorder(
        image,
        image,
        outerCellSize,
        outerCellSize,
        outerCellSize,
        outerCellSize,
        cv::BORDER_CONSTANT,
        cv::Scalar(255)
    );

    return image;
}

static bool estimateCorners(
    const prisma::MarkerSet& model,
    const std::vector<cv::Point3f>& objectPoints,
    const std::vector<cv::Point2f>& imagePoints,
    std::vector<cv::Point2f>& corners
)
{
    corners.clear();

    if (objectPoints.size() < 4 || objectPoints.size() != imagePoints.size())
        return false;

    const auto outerIt = model.levels.find(model.idExternal);

    if (outerIt == model.levels.end() ||
        outerIt->second.keypts.size() < 4)
    {
        return false;
    }

    std::vector<cv::Point2f> planePoints;
    planePoints.reserve(objectPoints.size());

    for (const cv::Point3f& point : objectPoints)
        planePoints.emplace_back(point.x, point.y);

    const cv::Mat homography = cv::findHomography(
        planePoints,
        imagePoints,
        cv::RANSAC,
        3.0
    );

    if (homography.empty())
        return false;

    std::vector<cv::Point2f> modelCorners;

    for (int i = 0; i < 4; ++i)
        modelCorners.push_back(outerIt->second.keypts[i].pt);

    cv::perspectiveTransform(modelCorners, corners, homography);
    return corners.size() == 4;
}

} // anonymous namespace

// Generate one marker or all markers from a dictionary
static std::vector<cv::Mat> printFData(
    const PDict& dict,
    int markerId,
    int bitSize
)
{
    if (bitSize == 0 || bitSize < -1)
    {
        prismarkerFail(
            "bitSize must be a positive integer or -1 for automatic sizing",
            "printPrisma"
        );
    }

    if (bitSize != -1 && bitSize % kPrismaBitSizeStep != 0)
    {
        prismarkerFail(
            "bitSize must be a multiple of " +
                std::to_string(kPrismaBitSizeStep) +
                " so that the auxiliary and central ArUcos are drawn exactly",
            "printPrisma"
        );
    }

    const int lastLevelBitSize =
        bitSize == -1
            ? kPrismaInnerCellSize
            : bitSize;

    std::vector<cv::Mat> images;

    if (markerId >= 0)
    {
        images.push_back(
            drawPRISMarker(
                getPrismaMarker(dict, markerId),
                dict.arucoDict,
                lastLevelBitSize
            )
        );

        return images;
    }

    images.reserve(dict.markers.size());

    for (const PMark& marker : dict.markers)
    {
        images.push_back(
            drawPRISMarker(
                marker,
                dict.arucoDict,
                lastLevelBitSize
            )
        );
    }

    return images;
}


std::vector<cv::Mat> printPrisma(
    PrismaDict dictionary,
    int markerId,
    int bitSize
)
{
    return printFData(
        detail::loadPDict(dictionary),
        markerId,
        bitSize
    );
}

struct MarkerState
{
    int id = -1;

    std::vector<prisma::Marker> levels;
    std::vector<prisma::ArucoHit> arucos;

    cv::Mat homography;
    std::vector<cv::Point3f> objPoints;
    std::vector<cv::Point2f> imgPoints;
};

// Harris pose target.
struct PoseTarget
{
    std::size_t state = 0;
    cv::Point3f obj;
    cv::Point2f pred;
    int cls = -1;
    double cell = 4.0;
    cv::Size subpixWindow = cv::Size(1, 1);

    // Used for predicted levels.
    bool check = false;
    std::array<cv::Point2f, 4> samples{};
    std::uint8_t pattern = 0;
};

struct HarrisHit
{
    std::size_t target = 0;
    cv::Point2f seed;
    cv::Point2f point;
};

namespace pose
{
constexpr double kMinCellSizePx = 3.0;
constexpr double kMaxCellSizePx = 64.0;

// Below these projected cell sizes the refined points are biased by the
// neighbouring corners and degrade the pose instead of improving it.
constexpr double kMinTargetCellPx = 4.0;      // Harris targets
constexpr double kMinArucoCornerCellPx = 3.0; // direct ArUco corners

constexpr double kSearchScale = 0.34;
constexpr int kMinSearch = 3;
constexpr int kMaxSearch = 9;

constexpr double kShiftScale = 0.26;
constexpr double kMinShift = 2.0;
constexpr double kMaxShift = 5.0;

constexpr float kMinDist2 = 150.f;

constexpr double kQuadScale = 0.20;
constexpr double kMinQuadTol = 1.5;
constexpr double kMaxQuadTol = 4.0;

constexpr double kBlockScale = 0.24;
constexpr int kMinBlock = 3;
constexpr int kMaxBlock = 7;
constexpr int kSobel = 3;
constexpr double kHarris = 0.04;

constexpr double kContrastScale = 0.18;
constexpr int kMinContrastRadius = 2;
constexpr int kMaxContrastRadius = 5;
constexpr double kMinContrast = 25.0;

constexpr double kCellOffset = 0.28;
constexpr double kCellPatch = 0.08;
constexpr int kMinCellRadius = 1;
constexpr int kMaxCellRadius = 2;

constexpr int kRefineIters = 15;
constexpr double kRefineEps = 0.003;

constexpr double kRefineShiftScale = 0.14;
constexpr double kMinRefineShift = 1.5;
constexpr double kMaxRefineShift = 3.0;

// Projected size of one ArUco cell, in pixels.
inline double arucoCellPx(const prisma::ArucoHit& aruco)
{
    double sideSum = 0.0;

    for (int edge = 0; edge < 4; ++edge)
    {
        sideSum += cv::norm(
            aruco.imgCorners[edge] -
            aruco.imgCorners[(edge + 1) % 4]
        );
    }

    return sideSum * 0.25 /
        static_cast<double>(std::max(2, aruco.fullCells));
}

inline double cellSize(double cellSizePx)
{
    return std::clamp(cellSizePx, kMinCellSizePx, kMaxCellSizePx);
}

inline int searchRadius(double cellSizePx)
{
    return std::clamp(
        static_cast<int>(std::lround(cellSizePx * kSearchScale)),
        kMinSearch,
        kMaxSearch
    );
}

inline float maxOffset(double cellSizePx)
{
    return static_cast<float>(std::clamp(
        cellSizePx * kShiftScale,
        kMinShift,
        kMaxShift
    ));
}

inline double quadTol(double cellSizePx)
{
    return std::clamp(
        cellSizePx * kQuadScale,
        kMinQuadTol,
        kMaxQuadTol
    );
}

inline int harrisBlock(double cellSizePx)
{
    int block = static_cast<int>(std::lround(cellSizePx * kBlockScale));
    block = std::clamp(block, kMinBlock, kMaxBlock);
    if ((block & 1) == 0)
        ++block;
    return std::min(block, kMaxBlock);
}

inline int contrastRadius(double cellSizePx)
{
    return std::clamp(
        static_cast<int>(std::lround(cellSizePx * kContrastScale)),
        kMinContrastRadius,
        kMaxContrastRadius
    );
}

inline float maxRefineOffset(double cellSizePx)
{
    return static_cast<float>(std::clamp(
        cellSizePx * kRefineShiftScale,
        kMinRefineShift,
        kMaxRefineShift
    ));
}

inline bool wellSeparated(const std::vector<cv::Point2f>& points)
{
    if (points.empty())
        return false;

    for (std::size_t i = 0; i + 1 < points.size(); ++i)
    {
        for (std::size_t j = i + 1; j < points.size(); ++j)
        {
            const cv::Point2f delta = points[i] - points[j];
            if (delta.dot(delta) < kMinDist2)
                return false;
        }
    }
    return true;
}

inline bool addTarget(
    std::vector<PoseTarget>& targets,
    const cv::Size& imageSize,
    std::size_t state,
    const cv::Point3f& objectPoint,
    const cv::Point2f& predicted,
    int expectedClass,
    double cellSizePx,
    const cv::Size& subpixWindow
)
{
    if (!std::isfinite(predicted.x) || !std::isfinite(predicted.y))
        return false;

    cellSizePx = cellSize(cellSizePx);
    const cv::Size safeSubpixWindow =
        prisma::clampSubpixWindow(subpixWindow);

    const int margin = std::max(
        {
            searchRadius(cellSizePx),
            harrisBlock(cellSizePx) + 1,
            safeSubpixWindow.width + 1,
            safeSubpixWindow.height + 1
        }
    );

    if (predicted.x < static_cast<float>(margin) ||
        predicted.y < static_cast<float>(margin) ||
        predicted.x >= static_cast<float>(imageSize.width - margin) ||
        predicted.y >= static_cast<float>(imageSize.height - margin))
    {
        return false;
    }

    for (const PoseTarget& current : targets)
    {
        if (current.state != state)
            continue;

        const bool sameObject =
            std::fabs(current.obj.x - objectPoint.x) < 1e-5f &&
            std::fabs(current.obj.y - objectPoint.y) < 1e-5f &&
            std::fabs(current.obj.z - objectPoint.z) < 1e-5f;

        if (!sameObject)
            continue;

        const cv::Point2f delta = current.pred - predicted;
        if (delta.dot(delta) <= 1.0f)
            return false;
    }

    PoseTarget target;
    target.state = state;
    target.obj = objectPoint;
    target.pred = predicted;
    target.cls = expectedClass;
    target.cell = cellSizePx;
    target.subpixWindow = safeSubpixWindow;
    targets.push_back(target);
    return true;
}

inline bool projectLevel(
    const prisma::Marker& marker,
    const cv::Mat& homography,
    std::vector<cv::Point2f>& modelPoints,
    std::vector<cv::Point2f>& imagePoints,
    double& cellSizePx
)
{
    const auto& keypoints = marker.getKeyptsRef();
    if (keypoints.empty())
        return false;

    modelPoints.clear();
    modelPoints.reserve(keypoints.size());
    for (const cv::KeyPoint& keypoint : keypoints)
        modelPoints.push_back(keypoint.pt);

    cv::perspectiveTransform(modelPoints, imagePoints, homography);

    if (imagePoints.size() != modelPoints.size() ||
        !wellSeparated(imagePoints))
    {
        return false;
    }

    cellSizePx = 6.0;
    if (imagePoints.size() >= 4)
    {
        double sideSum = 0.0;
        bool finite = true;

        for (int edge = 0; edge < 4; ++edge)
        {
            const cv::Point2f& a = imagePoints[edge];
            const cv::Point2f& b = imagePoints[(edge + 1) % 4];
            if (!std::isfinite(a.x) || !std::isfinite(a.y) ||
                !std::isfinite(b.x) || !std::isfinite(b.y))
            {
                finite = false;
                break;
            }
            sideSum += cv::norm(a - b);
        }

        if (finite)
        {
            const int bitsPerSide = std::max(
                1,
                static_cast<int>(std::lround(std::sqrt(
                    static_cast<double>(marker.nBits()))))
            );
            cellSizePx = (sideSum * 0.25) /
                static_cast<double>(bitsPerSide + 2);
        }
    }

    if (cellSizePx < kMinTargetCellPx)
        return false;

    cellSizePx = cellSize(cellSizePx);
    return true;
}

inline bool insideRegion(
    const std::vector<std::vector<cv::Point2f>>& regions,
    const cv::Point2f& point
)
{
    for (const auto& polygon : regions)
    {
        if (polygon.size() == 4 &&
            cv::pointPolygonTest(polygon, point, false) >= 0.0)
        {
            return true;
        }
    }
    return false;
}

inline std::vector<std::vector<cv::Point2f>> modelArucoAreas(
    const std::map<int, prisma::ArucoRef>& arucos
)
{
    std::vector<std::vector<cv::Point2f>> regions;
    regions.reserve(arucos.size());

    for (const auto& item : arucos)
    {
        const prisma::ArucoRef& aruco = item.second;
        const auto& corners = aruco.reserveObjCorners.size() == 4
            ? aruco.reserveObjCorners
            : aruco.objCorners;

        if (corners.size() != 4)
            continue;

        std::vector<cv::Point2f> polygon;
        polygon.reserve(4);
        for (const cv::Point3f& p : corners)
            polygon.emplace_back(p.x, p.y);
        regions.push_back(std::move(polygon));
    }

    return regions;
}

inline std::vector<std::vector<cv::Point2f>> imageArucoAreas(
    const std::vector<prisma::ArucoHit>& arucos
)
{
    std::vector<std::vector<cv::Point2f>> regions;
    regions.reserve(arucos.size());

    for (const prisma::ArucoHit& aruco : arucos)
    {
        if (aruco.imgCorners.size() != 4)
            continue;

        std::vector<cv::Point2f> polygon =
            aruco.reserveObjCorners.size() == 4
                ? prisma::reservePts(aruco)
                : aruco.imgCorners;

        if (polygon.size() == 4)
            regions.push_back(std::move(polygon));
    }

    return regions;
}

inline bool cellsOk(
    const PoseTarget& target,
    const cv::Point2f& point,
    const cv::Mat& gray
)
{
    if (!target.check)
        return true;

    const cv::Point2f correction = point - target.pred;
    const int sampleHalf = std::clamp(
        static_cast<int>(std::lround(
            target.cell * kCellPatch)),
        kMinCellRadius,
        kMaxCellRadius
    );

    std::array<double, 4> means{};
    double low = 255.0;
    double high = 0.0;

    for (int i = 0; i < 4; ++i)
    {
        const cv::Point2f sample = target.samples[i] + correction;
        const int x = static_cast<int>(std::lround(sample.x));
        const int y = static_cast<int>(std::lround(sample.y));
        const int x0 = x - sampleHalf;
        const int y0 = y - sampleHalf;
        const int x1 = x + sampleHalf + 1;
        const int y1 = y + sampleHalf + 1;

        if (x0 < 0 || y0 < 0 || x1 > gray.cols || y1 > gray.rows)
            return false;

        means[i] = cv::mean(gray(cv::Rect(x0, y0, x1 - x0, y1 - y0)))[0];
        low = std::min(low, means[i]);
        high = std::max(high, means[i]);
    }

    if (high - low < kMinContrast)
        return false;

    const double threshold = 0.5 * (low + high);
    std::uint8_t observed = 0;

    for (int i = 0; i < 4; ++i)
    {
        if (means[i] > threshold)
            observed |= static_cast<std::uint8_t>(1u << i);
    }

    return observed == target.pattern;
}

inline bool contrastOk(
    const PoseTarget& target,
    const cv::Point2f& point,
    const cv::Mat& gray
)
{
    const int half = contrastRadius(target.cell);
    const int cx = static_cast<int>(std::lround(point.x));
    const int cy = static_cast<int>(std::lround(point.y));
    const int x0 = std::max(0, cx - half);
    const int y0 = std::max(0, cy - half);
    const int x1 = std::min(gray.cols, cx + half + 1);
    const int y1 = std::min(gray.rows, cy + half + 1);

    if (x1 <= x0 || y1 <= y0)
        return false;

    double minValue = 0.0;
    double maxValue = 0.0;
    cv::minMaxLoc(
        gray(cv::Rect(x0, y0, x1 - x0, y1 - y0)),
        &minValue,
        &maxValue
    );

    return maxValue - minValue >= kMinContrast;
}
} // namespace pose

struct SeenAruco
{
    cv::aruco2::DictionaryType dictionary =
        static_cast<cv::aruco2::DictionaryType>(-1);
    int id = -1;
    std::vector<cv::Point2f> corners;
};

struct LevelObservation
{
    int markerId = -1;
    bool canStart = false;
    prisma::Marker level;
};

struct ArucoObservation
{
    int markerId = -1;
    bool canStart = false;
    prisma::ArucoHit aruco;
};

struct DetectionObservations
{
    std::vector<LevelObservation> levels;
    std::vector<ArucoObservation> arucos;
    std::vector<SeenAruco> seenArucos;
};

struct InstanceSeed
{
    int markerId = -1;
    cv::Mat homography;
    int strength = 0;
};

// Associate detected levels and ArUcos into complete PRISMarkers
struct PrismaDetector::PData
{
    // Search-level id -> complete PRISMarker / local level.
    struct LevelLink
    {
        int markerId = -1;
        int levelId = -1;
    };

    // Search-ArUco id -> complete PRISMarker / local ArUco id.
    struct ArucoLink
    {
        int markerId = -1;
        int internalId = -1;
        bool canStart = false;
    };

    // Geometry and semantic data prepared once for one complete PRISMarker.
    struct MarkerModel
    {
        prisma::MarkerSet geometry;
        std::map<int, prisma::ArucoRef> arucosByInternalId;
        std::set<int> uniqueArucoIds;

        // Model-space corners are dictionary data, so compute them only once.
        std::map<int, std::vector<cv::Point2f>> planeCornersByLevel;
    };

    using ArucoKey = std::pair<int, int>;
    using ArucoOwners = std::map<ArucoKey, std::set<int>>;

    // Everything derived from PDict and reused by every detect() call.
    struct PreparedDictionary
    {
        std::vector<LevelLink> levelBySearchId;
        std::vector<ArucoLink> arucoBySearchId;
        std::map<int, MarkerModel> modelsByMarkerId;
    };

    PrismaDict type =
        static_cast<PrismaDict>(-1);

    // Low-level detector, reused between frames.
    prisma::Detector detector;

    // Prepared dictionary.
    PreparedDictionary prepared;

    bool loaded() const
    {
        return type !=
            static_cast<PrismaDict>(-1);
    }

    void load(PrismaDict newType);

    // Per-frame detection pipeline.
    std::vector<PrismaMarker> detectFrame(
        const cv::Mat& image,
        bool pose
    );

private:
    // Map low-level detections to PRISMarker observations.
    DetectionObservations makeObservations(
        const prisma::DetectionEvidence& evidence
    ) const;

    // Internal candidate hypotheses.
    std::vector<InstanceSeed> makeSeeds(
        const DetectionObservations& observations
    ) const;

    std::vector<MarkerState> validateObservations(
        const DetectionObservations& observations,
        const cv::Size& imageSize
    ) const;

    void addPosePoints(
        std::vector<MarkerState>& valid,
        const cv::Mat& gray
    );

    std::vector<PoseTarget> makeTargets(
        const std::vector<MarkerState>& valid,
        const cv::Size& imageSize
    ) const;

    void addLevelTargets(
        std::size_t stateIndex,
        const MarkerState& state,
        const MarkerModel& model,
        const cv::Size& imageSize,
        std::vector<PoseTarget>& targets
    ) const;

    void addArucoTargets(
        std::size_t stateIndex,
        const MarkerState& state,
        const cv::Size& imageSize,
        std::vector<PoseTarget>& targets
    ) const;

    std::vector<HarrisHit> findHarris(
        const std::vector<PoseTarget>& targets,
        const cv::Mat& gray
    ) const;

    void addHarrisPoints(
        const std::vector<PoseTarget>& targets,
        const std::vector<HarrisHit>& hits,
        std::vector<MarkerState>& valid,
        const cv::Mat& gray
    ) const;

    void addDirectPoints(
        std::vector<MarkerState>& valid
    ) const;

    std::vector<PrismaMarker> buildResults(
        const std::vector<MarkerState>& valid,
        const DetectionObservations& observations,
        bool pose
    ) const;

    static prisma::MarkerSet buildModel(
        const PMark& mark,
        DictionaryType arucoDict
    );

    static PreparedDictionary prepareDictionary(
        const PDict& dict,
        prisma::MarkerSet& search,
        std::vector<prisma::ArucoSearchTarget>& arucoSearchTargets
    );

    static void addMarker(
        PreparedDictionary& out,
        prisma::MarkerSet& search,
        std::vector<prisma::ArucoSearchTarget>& arucoSearchTargets,
        std::map<int, cv::aruco2::Dictionary>& arucoDictionaryCache,
        const PMark& mark,
        DictionaryType arucoDict,
        const std::vector<cv::Point3f>& searchCorners,
        ArucoOwners& markersByAruco
    );

    static void resolveStartRules(
        PreparedDictionary& out,
        const ArucoOwners& markersByAruco
    );

    const MarkerModel* findModel(int markerId) const;

    bool sameProjectedInstance(
        int markerId,
        const cv::Mat& first,
        const cv::Mat& second
    ) const;

    void addSeed(
        std::vector<InstanceSeed>& seeds,
        int markerId,
        const cv::Mat& homography,
        int strength
    ) const;

    bool validateSeed(
        const InstanceSeed& seed,
        const DetectionObservations& observations,
        const MarkerModel& model,
        const cv::Size& imageSize,
        double levelThreshold,
        double arucoThreshold,
        MarkerState& state
    ) const;

    void insertBestState(
        std::vector<MarkerState>& valid,
        MarkerState&& state
    ) const;

    bool buildResult(
        const MarkerState& state,
        const MarkerModel& model,
        const DetectionObservations& observations,
        bool pose,
        PrismaMarker& marker
    ) const;
};
// Build the normalized geometry of a predefined marker
prisma::MarkerSet PrismaDetector::PData::buildModel(
    const PMark& mark,
    DictionaryType arucoDict
)
{
    prisma::MarkerSet markerSet;
    markerSet.mInfoType = 2;
    markerSet.idExternal = 0;

    const std::string arucoName =
        cv::aruco2::getDictInfo(arucoDict).name;
    float markerSide = 2.f;

    for (int levelIndex = 0;
         levelIndex < static_cast<int>(mark.levels.size());
         ++levelIndex)
    {
        const PLevel& level = mark.levels[levelIndex];
        std::vector<int> submarkers;

        if (levelIndex + 1 < static_cast<int>(mark.levels.size()))
            submarkers.push_back(levelIndex + 1);

        prisma::Marker marker(
            levelIndex,
            bitsToMat(level),
            squareCorners(markerSide),
            submarkers
        );

        const bool innermost =
            levelIndex + 1 == static_cast<int>(mark.levels.size());

        marker.applyMask(levelMask(level, innermost));
        markerSet.levels[levelIndex] = std::move(marker);

        if (!innermost)
        {
            const int childCells =
                level.k - 2 * kPrismaChildPaddingCells;

            markerSide *=
                static_cast<float>(childCells) /
                static_cast<float>(level.n + 2);
        }
    }

    for (int levelIndex = 0;
         levelIndex < static_cast<int>(mark.levels.size());
         ++levelIndex)
    {
        const PLevel& level = mark.levels[levelIndex];
        prisma::Marker& marker =
            markerSet.levels.at(levelIndex);

        if (levelIndex + 1 < static_cast<int>(mark.levels.size()))
        {
            marker.addInner(
                markerSet.levels.at(levelIndex + 1)
            );
        }

        const std::array<cv::Point2i, 4> starts =
            arucoStarts(level.layout, level.n);

        for (int slot = 0; slot < 4; ++slot)
        {
            const int internalId = levelIndex * 4 + slot;
            const auto corners = gridCorners(
                marker,
                static_cast<float>(starts[slot].x + 1),
                static_cast<float>(starts[slot].y + 1),
                static_cast<float>(kPrismaReservationCells),
                static_cast<float>(kPrismaReservationCells)
            );

            prisma::MarkerSet::ArucoInfo info;
            info.dictName = arucoName;
            info.dictId = level.aruco[slot];
            info.corners.assign(corners.begin(), corners.end());

            markerSet.cornerAruco[internalId] = info;
        }

        if (levelIndex + 1 == static_cast<int>(mark.levels.size()))
        {
            const int ring = (level.n - level.k) / 2;
            const int centralCells =
                level.k - 2 * kPrismaChildPaddingCells;
            const int centralStart =
                1 + ring + kPrismaChildPaddingCells;
            const auto corners = gridCorners(
                marker,
                static_cast<float>(centralStart),
                static_cast<float>(centralStart),
                static_cast<float>(centralCells),
                static_cast<float>(centralCells)
            );

            prisma::MarkerSet::ArucoInfo info;
            info.dictName = arucoName;
            info.dictId = mark.center;
            info.corners.assign(corners.begin(), corners.end());

            markerSet.innerAruco[levelIndex] = info;
        }

        marker.getKeypts();
        markerSet.bits_ids[marker.nBits()].push_back(levelIndex);
    }

    return markerSet;
}

void PrismaDetector::PData::addMarker(
    PreparedDictionary& out,
    prisma::MarkerSet& search,
    std::vector<prisma::ArucoSearchTarget>& arucoSearchTargets,
    std::map<int, cv::aruco2::Dictionary>& arucoDictionaryCache,
    const PMark& mark,
    DictionaryType arucoDict,
    const std::vector<cv::Point3f>& searchCorners,
    ArucoOwners& markersByAruco
)
{
    if (mark.levels.empty())
        return;


    prisma::MarkerSet full =
        buildModel(mark, arucoDict);


    const std::vector<prisma::ArucoRef> refs =
        prisma::makeArucoRefs(
            full,
            arucoDictionaryCache
        );


    MarkerModel model;
    model.uniqueArucoIds = getUniqueArucoIds(refs);

    for (const prisma::ArucoRef& ref : refs)
        model.arucosByInternalId[ref.internalId] = ref;


    for (const auto& item : full.levels)
    {
        std::vector<cv::Point2f> corners;

        if (prisma::modelPts(full, item.first, corners) &&
            corners.size() == 4)
        {
            model.planeCornersByLevel[item.first] =
                std::move(corners);
        }
    }


    // Each level is an independent candidate in the shared low-level search.
    for (int levelId = 0;
         levelId < static_cast<int>(mark.levels.size());
         ++levelId)
    {
        const PLevel& level = mark.levels[levelId];
        const int searchId =
            static_cast<int>(out.levelBySearchId.size());

        prisma::Marker candidate(
            searchId,
            bitsToMat(level),
            searchCorners,
            {}
        );

        // Ignore child / central regions when identifying this level.
        candidate.applyMask(levelMask(level, true));
        candidate.getKeypts();

        search.levels[
            searchId
        ] = std::move(candidate);

        out.levelBySearchId.push_back(
            LevelLink{
                mark.id,
                levelId
            }
        );
    }


    auto addAruco =
        [&](int internalId,
            const prisma::MarkerSet::ArucoInfo& info)
        {
            const auto ref =
                model.arucosByInternalId.find(internalId);

            if (ref == model.arucosByInternalId.end())
                return;

            const int searchId =
                static_cast<int>(out.arucoBySearchId.size());

            search.cornerAruco[searchId] = info;
            arucoSearchTargets.push_back(
                prisma::ArucoSearchTarget{
                    ref->second.dictId,
                    ref->second.dictionary
                }
            );

            out.arucoBySearchId.push_back(
                ArucoLink{
                    mark.id,
                    internalId,
                    false
                }
            );

            markersByAruco[
                std::make_pair(
                    static_cast<int>(ref->second.dictionary),
                    ref->second.dictId
                )
            ].insert(mark.id);
        };

    for (const auto& item : full.cornerAruco)
        addAruco(item.first, item.second);

    for (const auto& item : full.innerAruco)
    {
        addAruco(
            prisma::innerKey(item.first),
            item.second
        );
    }


    model.geometry = std::move(full);
    out.modelsByMarkerId[mark.id] = std::move(model);
}
// Allow an ArUco to start a hypothesis only if its id is unique
void PrismaDetector::PData::resolveStartRules(
    PreparedDictionary& out,
    const ArucoOwners& markersByAruco
)
{

    for (ArucoLink& link : out.arucoBySearchId)
    {
        const auto model =
            out.modelsByMarkerId.find(link.markerId);

        if (model == out.modelsByMarkerId.end())
            continue;

        const auto ref =
            model->second.arucosByInternalId.find(link.internalId);

        if (ref == model->second.arucosByInternalId.end())
            continue;

        const ArucoKey key =
            std::make_pair(
                static_cast<int>(ref->second.dictionary),
                ref->second.dictId
            );

        const auto owners = markersByAruco.find(key);

        link.canStart =
            owners != markersByAruco.end() &&
            owners->second.size() == 1;
    }
}
// Prepare marker models and their shared search data
PrismaDetector::PData::PreparedDictionary
PrismaDetector::PData::prepareDictionary(
    const PDict& dict,
    prisma::MarkerSet& search,
    std::vector<prisma::ArucoSearchTarget>& arucoSearchTargets
)
{
    PreparedDictionary result;
    arucoSearchTargets.clear();

    std::map<int, cv::aruco2::Dictionary> arucoDictionaryCache;

    search = prisma::MarkerSet();
    search.mInfoType = 2;
    search.idExternal = 0;

    ArucoOwners markersByAruco;

    const std::vector<cv::Point3f> searchCorners =
        squareCorners(2.f);


    for (const PMark& mark : dict.markers)
    {
        addMarker(
            result,
            search,
            arucoSearchTargets,
            arucoDictionaryCache,
            mark,
            dict.arucoDict,
            searchCorners,
            markersByAruco
        );
    }


    resolveStartRules(result, markersByAruco);


    return result;
}

const PrismaDetector::PData::MarkerModel*
PrismaDetector::PData::findModel(int markerId) const
{
    const auto model = prepared.modelsByMarkerId.find(markerId);

    if (model == prepared.modelsByMarkerId.end())
        return nullptr;

    return &model->second;
}

void PrismaDetector::PData::load(
    PrismaDict newType
)
{

    if (type == newType)
    {
        return;
    }


    const PDict source = detail::loadPDict(newType);


    prisma::MarkerSet search;
    std::vector<prisma::ArucoSearchTarget> arucoSearchTargets;

    PreparedDictionary next =
        prepareDictionary(
            source,
            search,
            arucoSearchTargets
        );

    detector.setParams(
        search,
        arucoSearchTargets
    );


    prepared = std::move(next);
    type = newType;

}

PrismaDetector::PrismaDetector(
    PrismaDict dictionary
)
    : data(cv::makePtr<PData>())
{
    data->load(dictionary);
}


PrismaDetector::~PrismaDetector() = default;

void PrismaDetector::setDictionary(
    PrismaDict dictionary
)
{
    if (!data)
        data = cv::makePtr<PData>();

    data->load(dictionary);
}


static cv::Point2f quadCenter(
    const std::vector<cv::Point2f>& corners
)
{
    cv::Point2f center(0.f, 0.f);

    if (corners.size() != 4)
        return center;

    for (const cv::Point2f& corner : corners)
        center += corner;

    return center * 0.25f;
}

// Add one physical ArUco to the visible set, ignoring repeated detections
// of the same dictionary/id at the same image position.
static void addSeenAruco(
    std::vector<SeenAruco>& seen,
    cv::aruco2::DictionaryType dictionary,
    int dictId,
    const std::vector<cv::Point2f>& corners
)
{
    if (dictId < 0 || corners.size() != 4)
        return;

    const cv::Point2f center =
        quadCenter(corners);

    for (const SeenAruco& item : seen)
    {
        if (item.dictionary != dictionary ||
            item.id != dictId)
        {
            continue;
        }

        if (cv::norm(center - quadCenter(item.corners)) <= 2.f)
            return;
    }

    seen.push_back(
        SeenAruco{
            dictionary,
            dictId,
            corners
        }
    );
}

// Check visible ArUco ids and positions.
static bool arucoOrderOk(
    const prisma::MarkerSet& model,
    const std::map<int, prisma::ArucoRef>& refs,
    const std::vector<SeenAruco>& seen,
    const std::vector<prisma::ArucoHit>& support,
    const cv::Mat& homography,
    const cv::Size& imageSize
)
{
    if (refs.empty() || seen.empty() || homography.empty())
        return true;

    struct Expected
    {
        cv::aruco2::DictionaryType dictionary =
            static_cast<cv::aruco2::DictionaryType>(-1);
        int id = -1;
        int internalId = -1;
        std::vector<cv::Point2f> corners;
        cv::Point2f center;
        double size = 0.0;
    };

    auto sideLength =
        [](const std::vector<cv::Point2f>& corners)
        {
            if (corners.size() != 4)
                return 0.0;

            double sum = 0.0;

            for (int i = 0; i < 4; ++i)
            {
                sum += cv::norm(
                    corners[i] - corners[(i + 1) % 4]
                );
            }

            return sum * 0.25;
        };

    const double base =
        prisma::arucoThres(imageSize);

    std::vector<Expected> expected;
    expected.reserve(refs.size());

    for (const auto& item : refs)
    {
        const prisma::ArucoRef& ref = item.second;

        if (ref.objCorners.size() != 4)
            continue;

        std::vector<cv::Point2f> modelCorners;
        modelCorners.reserve(4);

        for (const cv::Point3f& corner : ref.objCorners)
            modelCorners.emplace_back(corner.x, corner.y);

        std::vector<cv::Point2f> projected;

        cv::perspectiveTransform(
            modelCorners,
            projected,
            homography
        );

        if (projected.size() != 4)
            continue;

        expected.push_back(
            Expected{
                ref.dictionary,
                ref.dictId,
                ref.internalId,
                projected,
                quadCenter(projected),
                sideLength(projected)
            }
        );
    }

    if (expected.empty())
        return true;

    // Project the candidate area.
    std::vector<cv::Point2f> outerModel;
    std::vector<cv::Point2f> outerImage;

    if (prisma::modelPts(
            model,
            model.idExternal,
            outerModel))
    {
        cv::perspectiveTransform(
            outerModel,
            outerImage,
            homography
        );
    }

    struct SupportArea
    {
        cv::Point2f center;
        double radius = 0.0;
    };

    std::vector<SupportArea> supportAreas;
    supportAreas.reserve(support.size());

    for (const prisma::ArucoHit& aruco : support)
    {
        if (aruco.imgCorners.size() != 4)
            continue;

        const double side = sideLength(aruco.imgCorners);

        supportAreas.push_back(
            SupportArea{
                quadCenter(aruco.imgCorners),
                std::max(base * 4.0, side * 6.5)
            }
        );
    }

    auto belongsToCandidate =
        [&](const SeenAruco& aruco)
        {
            if (aruco.corners.size() != 4)
                return false;

            const cv::Point2f center =
                quadCenter(aruco.corners);

            if (outerImage.size() == 4)
            {
                const double margin =
                    std::max(
                        base * 3.0,
                        sideLength(aruco.corners) * 0.75
                    );

                if (cv::pointPolygonTest(
                        outerImage,
                        center,
                        true) >= -margin)
                {
                    return true;
                }
            }

            return false;
        };

    auto fitsExpected =
        [&](const SeenAruco& aruco,
            const Expected& ref)
        {
            if (aruco.dictionary != ref.dictionary ||
                aruco.id != ref.id ||
                aruco.corners.size() != 4 ||
                ref.corners.size() != 4)
            {
                return false;
            }

            const double threshold =
                std::max(
                    base * 1.5,
                    ref.size * 0.20
                );

            double meanError = 0.0;
            double maxError = 0.0;

            for (int i = 0; i < 4; ++i)
            {
                const double error = cv::norm(
                    aruco.corners[i] - ref.corners[i]
                );

                meanError += error;
                maxError = std::max(maxError, error);
            }

            meanError *= 0.25;

            return meanError <= threshold &&
                   maxError <= threshold * 2.0;
        };

    std::vector<const SeenAruco*> visible;

    for (const SeenAruco& aruco : seen)
    {
        if (belongsToCandidate(aruco))
            visible.push_back(&aruco);
    }

    // Include nearby ArUcos when needed.
    if (visible.size() <= 1 && !supportAreas.empty())
    {
        for (const SeenAruco& aruco : seen)
        {
            if (aruco.corners.size() != 4)
                continue;

            bool alreadyAdded = false;

            for (const SeenAruco* item : visible)
            {
                if (item == &aruco)
                {
                    alreadyAdded = true;
                    break;
                }
            }

            if (alreadyAdded)
                continue;

            const cv::Point2f center =
                quadCenter(aruco.corners);

            for (const SupportArea& area : supportAreas)
            {
                if (cv::norm(center - area.center) <= area.radius)
                {
                    visible.push_back(&aruco);
                    break;
                }
            }
        }
    }

    if (visible.empty())
        return true;

    std::set<int> usedSlots;

    for (const SeenAruco* aruco : visible)
    {
        const Expected* best = nullptr;
        double bestError =
            std::numeric_limits<double>::infinity();

        for (const Expected& ref : expected)
        {
            if (usedSlots.count(ref.internalId) != 0 ||
                !fitsExpected(*aruco, ref))
            {
                continue;
            }

            const double error = cv::norm(
                quadCenter(aruco->corners) - ref.center
            );

            if (error < bestError)
            {
                bestError = error;
                best = &ref;
            }
        }

        if (best == nullptr)
            return false;

        usedSlots.insert(best->internalId);
    }

    return true;
}

static prisma::ArucoHit makeArucoHit(
    const prisma::DetectedAruco& detected,
    const prisma::ArucoRef& ref
)
{
    prisma::ArucoHit hit;
    hit.internalId = ref.internalId;
    hit.fullCells = ref.fullCells;
    hit.bits = ref.bits;
    hit.imgCorners = detected.imgCorners;
    hit.objCorners = ref.objCorners;
    hit.reserveObjCorners = ref.reserveObjCorners;
    return hit;
}

static bool projectOuterCorners(
    const prisma::MarkerSet& model,
    const cv::Mat& homography,
    std::vector<cv::Point2f>& corners
)
{
    corners.clear();

    if (homography.empty())
        return false;

    std::vector<cv::Point2f> modelCorners;

    if (!prisma::modelPts(
            model,
            model.idExternal,
            modelCorners))
    {
        return false;
    }

    cv::perspectiveTransform(
        modelCorners,
        corners,
        homography
    );

    return corners.size() == 4;
}

bool PrismaDetector::PData::sameProjectedInstance(
    int markerId,
    const cv::Mat& first,
    const cv::Mat& second
) const
{
    if (first.empty() || second.empty())
        return false;

    const MarkerModel* model = findModel(markerId);

    if (model == nullptr)
        return false;

    std::vector<cv::Point2f> cornersA;
    std::vector<cv::Point2f> cornersB;

    if (!projectOuterCorners(
            model->geometry,
            first,
            cornersA) ||
        !projectOuterCorners(
            model->geometry,
            second,
            cornersB) ||
        cornersA.size() != 4 ||
        cornersB.size() != 4)
    {
        return false;
    }

    double sideA = 0.0;
    double sideB = 0.0;
    double cornerError = 0.0;

    for (int i = 0; i < 4; ++i)
    {
        sideA += cv::norm(
            cornersA[i] - cornersA[(i + 1) % 4]
        );

        sideB += cv::norm(
            cornersB[i] - cornersB[(i + 1) % 4]
        );

        cornerError += cv::norm(
            cornersA[i] - cornersB[i]
        );
    }

    sideA *= 0.25;
    sideB *= 0.25;
    cornerError *= 0.25;

    const double smaller = std::min(sideA, sideB);
    const double larger = std::max(sideA, sideB);

    if (smaller <= 0.0 || larger / smaller > 1.35)
        return false;

    const double centerDistance = cv::norm(
        quadCenter(cornersA) - quadCenter(cornersB)
    );

    const double threshold =
        std::max(5.0, smaller * 0.20);

    return centerDistance <= threshold &&
           cornerError <= threshold;
}

void PrismaDetector::PData::addSeed(
    std::vector<InstanceSeed>& seeds,
    int markerId,
    const cv::Mat& homography,
    int strength
) const
{
    if (homography.empty())
        return;

    for (InstanceSeed& current : seeds)
    {
        if (current.markerId != markerId)
            continue;

        if (!sameProjectedInstance(
                markerId,
                current.homography,
                homography))
        {
            continue;
        }

        if (strength > current.strength)
        {
            current.homography = homography.clone();
            current.strength = strength;
        }

        return;
    }

    InstanceSeed seed;
    seed.markerId = markerId;
    seed.homography = homography.clone();
    seed.strength = strength;
    seeds.push_back(std::move(seed));
}
// Map low-level detections to their marker and level
DetectionObservations PrismaDetector::PData::makeObservations(
    const prisma::DetectionEvidence& evidence
) const
{
    DetectionObservations result;
    result.levels.reserve(evidence.levels.size());
    result.arucos.reserve(evidence.arucos.size());
    result.seenArucos.reserve(evidence.arucos.size());

    for (const prisma::LevelHit& detected : evidence.levels)
    {
        if (detected.imgCorners.size() != 4 ||
            detected.id < 0 ||
            detected.id >=
                static_cast<int>(prepared.levelBySearchId.size()))
        {
            continue;
        }

        const LevelLink& owner =
            prepared.levelBySearchId[detected.id];

        const MarkerModel* model = findModel(owner.markerId);

        if (model == nullptr)
            continue;

        const auto level =
            model->geometry.levels.find(
                owner.levelId
            );

        if (level == model->geometry.levels.end())
            continue;

        prisma::Marker fullLevel = level->second;

        for (int corner = 0; corner < 4; ++corner)
            fullLevel.push_back(detected.imgCorners[corner]);

        LevelObservation observation;
        observation.markerId = owner.markerId;
        observation.canStart = detected.canStart;
        observation.level = std::move(fullLevel);
        result.levels.push_back(std::move(observation));
    }

    for (const prisma::DetectedAruco& detected : evidence.arucos)
    {
        if (detected.searchId < 0 ||
            detected.searchId >=
                static_cast<int>(prepared.arucoBySearchId.size()))
        {
            continue;
        }

        const ArucoLink& owner =
            prepared.arucoBySearchId[detected.searchId];

        const MarkerModel* model = findModel(owner.markerId);

        if (model == nullptr)
            continue;

        const auto ref =
            model->arucosByInternalId.find(owner.internalId);

        if (ref == model->arucosByInternalId.end())
            continue;

        addSeenAruco(
            result.seenArucos,
            ref->second.dictionary,
            ref->second.dictId,
            detected.imgCorners
        );

        ArucoObservation observation;
        observation.markerId = owner.markerId;
        observation.canStart = owner.canStart;
        observation.aruco = makeArucoHit(detected, ref->second);
        result.arucos.push_back(std::move(observation));
    }

    return result;
}
// Initialize homographies from detected levels and ArUcos
std::vector<InstanceSeed> PrismaDetector::PData::makeSeeds(
    const DetectionObservations& observations
) const
{
    std::vector<InstanceSeed> result;
    result.reserve(
        observations.levels.size() +
        observations.arucos.size()
    );

    for (const LevelObservation& observation : observations.levels)
    {
        if (!observation.canStart)
            continue;

        std::vector<cv::Point2f> imageCorners;

        if (!prisma::levelPts(
                observation.level,
                imageCorners))
        {
            continue;
        }

        const MarkerModel* model = findModel(observation.markerId);

        if (model == nullptr)
            continue;

        const auto modelCorners =
            model->planeCornersByLevel.find(
                observation.level.id
            );

        if (modelCorners == model->planeCornersByLevel.end() ||
            modelCorners->second.size() != 4)
        {
            continue;
        }

        const int strength =
            observation.level.id == model->geometry.idExternal
                ? 3
                : 2;


        addSeed(
            result,
            observation.markerId,
            cv::getPerspectiveTransform(
                modelCorners->second,
                imageCorners
            ),
            strength
        );
    }

    for (const ArucoObservation& observation : observations.arucos)
    {
        const prisma::ArucoHit& hit = observation.aruco;

        if (!observation.canStart ||
            hit.objCorners.size() != 4 ||
            hit.imgCorners.size() != 4)
        {
            continue;
        }


        addSeed(
            result,
            observation.markerId,
            cv::getPerspectiveTransform(
                prisma::toPlane(hit.objCorners),
                hit.imgCorners
            ),
            1
        );
    }

    return result;
}

static int evidenceScore(const MarkerState& state)
{
    return
        static_cast<int>(state.levels.size()) * 100 +
        static_cast<int>(state.arucos.size()) * 10 +
        (state.levels.empty() ? 0 : 1);
}

static bool sameObservedCorners(
    const std::vector<cv::Point2f>& first,
    const std::vector<cv::Point2f>& second
)
{
    if (first.size() < 4 || second.size() < 4)
        return false;

    double meanError = 0.0;

    for (int corner = 0; corner < 4; ++corner)
    {
        meanError += cv::norm(
            first[corner] - second[corner]
        );
    }

    meanError *= 0.25;
    return meanError <= 0.25;
}

static bool sharesObservedEvidence(
    const MarkerState& first,
    const MarkerState& second
)
{
    if (first.id != second.id)
        return false;

    for (const prisma::Marker& a : first.levels)
    {
        for (const prisma::Marker& b : second.levels)
        {
            if (a.id != b.id)
                continue;

            if (sameObservedCorners(a, b))
                return true;
        }
    }

    for (const prisma::ArucoHit& a : first.arucos)
    {
        for (const prisma::ArucoHit& b : second.arucos)
        {
            if (a.internalId != b.internalId)
                continue;

            if (sameObservedCorners(
                    a.imgCorners,
                    b.imgCorners))
            {
                return true;
            }
        }
    }

    return false;
}
// Check detected levels and ArUcos against the candidate homography
bool PrismaDetector::PData::validateSeed(
    const InstanceSeed& seed,
    const DetectionObservations& observations,
    const MarkerModel& model,
    const cv::Size& imageSize,
    double levelThreshold,
    double arucoThreshold,
    MarkerState& state
) const
{
    if (seed.homography.empty())
        return false;

    state = MarkerState();
    state.id = seed.markerId;
    state.homography = seed.homography;

    for (const LevelObservation& observation : observations.levels)
    {
        if (observation.markerId != seed.markerId)
            continue;

        if (!prisma::levelFits(
                model.geometry,
                observation.level,
                state.homography,
                levelThreshold))
        {
            continue;
        }

        state.levels.push_back(observation.level);
    }

    for (const ArucoObservation& observation : observations.arucos)
    {
        if (observation.markerId != seed.markerId)
            continue;

        if (!prisma::arucoFits(
                observation.aruco,
                state.homography,
                arucoThreshold))
        {
            continue;
        }

        state.arucos.push_back(observation.aruco);
    }

    if (state.levels.empty() && state.arucos.empty())
        return false;

    if (state.levels.empty())
    {
        bool hasUniqueAruco = false;

        for (const prisma::ArucoHit& aruco : state.arucos)
        {
            if (model.uniqueArucoIds.count(aruco.internalId) != 0)
            {
                hasUniqueAruco = true;
                break;
            }
        }

        if (!hasUniqueAruco)
            return false;

        if (!arucoOrderOk(
                model.geometry,
                model.arucosByInternalId,
                observations.seenArucos,
                state.arucos,
                state.homography,
                imageSize))
        {
            return false;
        }
    }

    return true;
}
// Keep the strongest evidence for each detected instance
void PrismaDetector::PData::insertBestState(
    std::vector<MarkerState>& valid,
    MarkerState&& state
) const
{
    for (MarkerState& current : valid)
    {
        if (current.id != state.id)
            continue;

        const bool sameProjection =
            sameProjectedInstance(
                current.id,
                current.homography,
                state.homography
            );

        const bool sameEvidence =
            sharesObservedEvidence(
                current,
                state
            );

        if (!sameProjection && !sameEvidence)
            continue;

        if (evidenceScore(state) > evidenceScore(current))
            current = std::move(state);

        return;
    }

    valid.push_back(std::move(state));
}

std::vector<MarkerState> PrismaDetector::PData::validateObservations(
    const DetectionObservations& observations,
    const cv::Size& imageSize
) const
{

    const std::vector<InstanceSeed> seeds =
        makeSeeds(observations);


    std::vector<MarkerState> valid;
    valid.reserve(seeds.size());

    const double levelThreshold =
        prisma::levelThres(imageSize);

    const double arucoThreshold =
        prisma::arucoThres(imageSize);

    for (const InstanceSeed& seed : seeds)
    {
        const MarkerModel* model = findModel(seed.markerId);

        if (model == nullptr || seed.homography.empty())
            continue;

        MarkerState state;

        if (!validateSeed(
                seed,
                observations,
                *model,
                imageSize,
                levelThreshold,
                arucoThreshold,
                state))
        {
            continue;
        }

        insertBestState(valid, std::move(state));
    }


    return valid;
}
// Collect refined and direct correspondences for pose estimation
void PrismaDetector::PData::addPosePoints(
    std::vector<MarkerState>& valid,
    const cv::Mat& gray
)
{
    if (valid.empty())
        return;

    for (MarkerState& state : valid)
    {
        state.objPoints.clear();
        state.imgPoints.clear();
    }

    const std::vector<PoseTarget> targets = makeTargets(valid, gray.size());
    const std::vector<HarrisHit> hits = findHarris(targets, gray);

    addHarrisPoints(targets, hits, valid, gray);
    addDirectPoints(valid);
}

std::vector<PoseTarget> PrismaDetector::PData::makeTargets(
    const std::vector<MarkerState>& valid,
    const cv::Size& imageSize
) const
{
    std::vector<PoseTarget> targets;

    for (std::size_t stateIndex = 0; stateIndex < valid.size(); ++stateIndex)
    {
        const MarkerState& state = valid[stateIndex];
        const MarkerModel* model = findModel(state.id);
        if (model == nullptr || state.homography.empty())
            continue;

        addLevelTargets(stateIndex, state, *model, imageSize, targets);
        addArucoTargets(stateIndex, state, imageSize, targets);
    }

    return targets;
}

void PrismaDetector::PData::addLevelTargets(
    std::size_t stateIndex,
    const MarkerState& state,
    const MarkerModel& model,
    const cv::Size& imageSize,
    std::vector<PoseTarget>& targets
) const
{
    const auto& modelLevels = model.geometry.levels;
    const auto arucoModelRegions =
        pose::modelArucoAreas(model.arucosByInternalId);
    const auto arucoImageRegions =
        pose::imageArucoAreas(state.arucos);

    std::map<int, const prisma::Marker*> detectedById;
    std::vector<int> levelOrder;
    levelOrder.reserve(modelLevels.size());

    for (const prisma::Marker& detected : state.levels)
    {
        if (modelLevels.find(detected.id) == modelLevels.end())
            continue;
        if (detectedById.emplace(detected.id, &detected).second)
            levelOrder.push_back(detected.id);
    }

    for (const auto& item : modelLevels)
    {
        if (detectedById.count(item.first) == 0)
            levelOrder.push_back(item.first);
    }

    for (int levelId : levelOrder)
    {
        const auto modelItem = modelLevels.find(levelId);
        if (modelItem == modelLevels.end())
            continue;

        const prisma::Marker& modelMarker = modelItem->second;
        const auto detectedItem = detectedById.find(levelId);
        const prisma::Marker* detected =
            detectedItem != detectedById.end() ? detectedItem->second : nullptr;

        if (detected != nullptr && detected->size() < 4)
            continue;

        const auto& modelKeypoints = modelMarker.getKeyptsRef();
        std::vector<cv::Point2f> modelPoints;
        std::vector<cv::Point2f> projectedPoints;
        double cellSizePx = 6.0;

        if (!pose::projectLevel(
                modelMarker,
                state.homography,
                modelPoints,
                projectedPoints,
                cellSizePx))
        {
            continue;
        }

        const int bitsPerSide = static_cast<int>(std::lround(std::sqrt(
            static_cast<double>(modelMarker.nBits()))));

        if (bitsPerSide <= 0 ||
            bitsPerSide * bitsPerSide != modelMarker.nBits())
        {
            continue;
        }

        const float modelCellSize =
            modelMarker.getMarkerSize() /
            static_cast<float>(bitsPerSide + 2);

        if (!(modelCellSize > 0.f) ||
            !std::isfinite(modelCellSize))
        {
            continue;
        }

        std::vector<cv::Point2f> visibleQuad;
        double quadTol = 0.0;

        if (detected != nullptr)
        {
            visibleQuad.reserve(4);
            for (int corner = 0; corner < 4; ++corner)
                visibleQuad.push_back((*detected)[corner]);
            quadTol = pose::quadTol(cellSizePx);
        }

        cv::Mat markerBorder;

        if (detected == nullptr)
        {
            const cv::Mat bits = modelMarker.mat();
            const cv::Mat mask = modelMarker.mask();

            if (bits.empty() || mask.empty() || bits.size() != mask.size())
                continue;

            cv::Mat marker;
            bits.copyTo(marker);
            marker += -1 * (mask - 1);

            cv::copyMakeBorder(
                marker,
                markerBorder,
                1, 1, 1, 1,
                cv::BORDER_CONSTANT,
                0
            );
        }

        // A non-detected level only contributes verifiable internal corners.
        const std::size_t firstPoint = detected != nullptr ? 0u : 4u;

        for (std::size_t index = firstPoint;
             index < projectedPoints.size();
             ++index)
        {
            const cv::Point2f& predicted = projectedPoints[index];
            const cv::Point2f& modelPoint = modelPoints[index];

            if (pose::insideRegion(arucoModelRegions, modelPoint) ||
                pose::insideRegion(arucoImageRegions, predicted))
            {
                continue;
            }

            if (detected != nullptr)
            {
                const double signedDistance = cv::pointPolygonTest(
                    visibleQuad,
                    predicted,
                    true
                );

                if (signedDistance < -quadTol)
                    continue;
            }

            std::uint8_t expectedCells = 0;
            std::array<cv::Point2f, 4> cellSamples{};

            if (detected == nullptr)
            {
                const int gridX = static_cast<int>(std::lround(
                    modelPoint.x / modelCellSize +
                    static_cast<float>(bitsPerSide) * 0.5f));
                const int gridY = static_cast<int>(std::lround(
                    -modelPoint.y / modelCellSize +
                    static_cast<float>(bitsPerSide) * 0.5f));

                if (gridX < 0 || gridY < 0 ||
                    gridX + 1 >= markerBorder.cols ||
                    gridY + 1 >= markerBorder.rows)
                {
                    continue;
                }

                const auto bitAt = [&](int row, int col) -> std::uint8_t
                {
                    return markerBorder.at<uchar>(row, col) > 0
                        ? static_cast<std::uint8_t>(1)
                        : static_cast<std::uint8_t>(0);
                };

                expectedCells = static_cast<std::uint8_t>(
                    (bitAt(gridY,     gridX)     << 0) |
                    (bitAt(gridY,     gridX + 1) << 1) |
                    (bitAt(gridY + 1, gridX)     << 2) |
                    (bitAt(gridY + 1, gridX + 1) << 3)
                );

                const float sampleOffset = static_cast<float>(
                    pose::kCellOffset) * modelCellSize;

                const std::vector<cv::Point2f> modelSamples =
                {
                    {modelPoint.x - sampleOffset, modelPoint.y + sampleOffset},
                    {modelPoint.x + sampleOffset, modelPoint.y + sampleOffset},
                    {modelPoint.x - sampleOffset, modelPoint.y - sampleOffset},
                    {modelPoint.x + sampleOffset, modelPoint.y - sampleOffset}
                };

                std::vector<cv::Point2f> imageSamples;
                cv::perspectiveTransform(
                    modelSamples,
                    imageSamples,
                    state.homography
                );

                if (imageSamples.size() != 4)
                    continue;

                bool finite = true;

                for (int sample = 0; sample < 4; ++sample)
                {
                    if (!std::isfinite(imageSamples[sample].x) ||
                        !std::isfinite(imageSamples[sample].y))
                    {
                        finite = false;
                        break;
                    }

                    cellSamples[sample] = imageSamples[sample];
                }

                if (!finite)
                    continue;
            }

            const cv::Size subpixWindow =
                prisma::localSubpixWindow(
                    state.homography,
                    modelPoint,
                    modelCellSize,
                    modelCellSize
                );

            if (!pose::addTarget(
                    targets,
                    imageSize,
                    stateIndex,
                    cv::Point3f(modelPoint.x, modelPoint.y, 0.f),
                    predicted,
                    modelKeypoints[index].class_id,
                    cellSizePx,
                    subpixWindow))
            {
                continue;
            }

            if (detected == nullptr)
            {
                PoseTarget& target = targets.back();
                target.check = true;
                target.samples = cellSamples;
                target.pattern = expectedCells;
            }
        }
    }
}

void PrismaDetector::PData::addArucoTargets(
    std::size_t stateIndex,
    const MarkerState& state,
    const cv::Size& imageSize,
    std::vector<PoseTarget>& targets
) const
{
    for (const prisma::ArucoHit& aruco : state.arucos)
    {
        if (aruco.imgCorners.size() != 4 ||
            aruco.objCorners.size() != 4)
        {
            continue;
        }

        if (aruco.bits.empty())
            continue;

        const double rawCellSizePx = pose::arucoCellPx(aruco);

        if (rawCellSizePx < pose::kMinTargetCellPx)
            continue;

        const double cellSizePx = pose::cellSize(rawCellSizePx);

        prisma::Homographer hom(aruco.imgCorners);
        const int rows = aruco.bits.rows;
        const int cols = aruco.bits.cols;

        if (rows <= 0 || cols <= 0)
            continue;

        const double cellStepX =
            1.0 / static_cast<double>(cols);
        const double cellStepY =
            1.0 / static_cast<double>(rows);

        for (int y = 1; y < rows; ++y)
        {
            for (int x = 1; x < cols; ++x)
            {
                const int cls =
                    prisma::cornerType(
                        aruco.bits,
                        y,
                        x
                    );

                if (cls < 0)
                    continue;

                const float u =
                    static_cast<float>(x) /
                    static_cast<float>(cols);
                const float v =
                    static_cast<float>(y) /
                    static_cast<float>(rows);
                const cv::Point2f normalized(u, v);

                const cv::Size subpixWindow =
                    prisma::localSubpixWindow(
                        hom,
                        normalized,
                        cellStepX,
                        cellStepY
                    );

                pose::addTarget(
                    targets,
                    imageSize,
                    stateIndex,
                    prisma::bilinearPoint(
                        aruco.objCorners,
                        u,
                        v
                    ),
                    hom(normalized),
                    cls,
                    cellSizePx,
                    subpixWindow
                );
            }
        }
    }
}
// Search Harris corners near the projected model points
std::vector<HarrisHit> PrismaDetector::PData::findHarris(
    const std::vector<PoseTarget>& targets,
    const cv::Mat& gray
) const
{
    std::vector<HarrisHit> hits;
    hits.reserve(targets.size());

    cv::Mat response;

    for (std::size_t targetIndex = 0;
         targetIndex < targets.size();
         ++targetIndex)
    {
        const PoseTarget& target = targets[targetIndex];
        const int block = pose::harrisBlock(target.cell);
        const int half = std::max(
            pose::searchRadius(target.cell),
            block + 1
        );

        const int x0 = std::max(
            0,
            static_cast<int>(std::floor(target.pred.x)) - half
        );
        const int y0 = std::max(
            0,
            static_cast<int>(std::floor(target.pred.y)) - half
        );
        const int x1 = std::min(
            gray.cols,
            static_cast<int>(std::ceil(target.pred.x)) + half + 1
        );
        const int y1 = std::min(
            gray.rows,
            static_cast<int>(std::ceil(target.pred.y)) + half + 1
        );

        const cv::Rect roi(x0, y0, x1 - x0, y1 - y0);
        if (roi.width < block + 2 || roi.height < block + 2)
            continue;

        cv::cornerHarris(
            gray(roi),
            response,
            block,
            pose::kSobel,
            pose::kHarris,
            cv::BORDER_DEFAULT
        );

        const float maxOffset = pose::maxOffset(target.cell);
        const float maxOffset2 = maxOffset * maxOffset;
        cv::Point best(-1, -1);
        float bestScore = 0.f;

        for (int y = 0; y < response.rows; ++y)
        {
            const float* row = response.ptr<float>(y);
            for (int x = 0; x < response.cols; ++x)
            {
                const cv::Point2f point(
                    static_cast<float>(roi.x + x),
                    static_cast<float>(roi.y + y)
                );
                const cv::Point2f delta = point - target.pred;

                if (delta.dot(delta) <= maxOffset2 && row[x] > bestScore)
                {
                    bestScore = row[x];
                    best = cv::Point(x, y);
                }
            }
        }

        if (best.x < 0 || !(bestScore > 0.f))
            continue;

        const cv::Point2f seed(
            static_cast<float>(roi.x + best.x),
            static_cast<float>(roi.y + best.y)
        );

        if (!pose::cellsOk(target, seed, gray) ||
            !pose::contrastOk(target, seed, gray))
        {
            continue;
        }

        HarrisHit hit;
        hit.target = targetIndex;
        hit.seed = seed;
        hit.point = seed;
        hits.push_back(hit);
    }

    std::vector<cv::Point2f> refinedPoints;
    std::vector<cv::Size> refineWindows;
    refinedPoints.reserve(hits.size());
    refineWindows.reserve(hits.size());

    for (const HarrisHit& hit : hits)
    {
        refinedPoints.push_back(hit.seed);
        refineWindows.push_back(
            targets[hit.target].subpixWindow
        );
    }

    prisma::refineSubpixGrouped(
        gray,
        refinedPoints,
        refineWindows,
        cv::TermCriteria(
            cv::TermCriteria::MAX_ITER |
                cv::TermCriteria::EPS,
            pose::kRefineIters,
            pose::kRefineEps
        )
    );

    for (std::size_t i = 0; i < hits.size(); ++i)
        hits[i].point = refinedPoints[i];

    return hits;
}

void PrismaDetector::PData::addHarrisPoints(
    const std::vector<PoseTarget>& targets,
    const std::vector<HarrisHit>& hits,
    std::vector<MarkerState>& valid,
    const cv::Mat& gray
) const
{
    std::vector<cv::KeyPoint> keys;
    std::vector<int> hitIds;
    keys.reserve(hits.size());
    hitIds.reserve(hits.size());

    for (int i = 0; i < static_cast<int>(hits.size()); ++i)
    {
        const HarrisHit& hit = hits[i];
        if (hit.target >= targets.size())
            continue;

        const PoseTarget& target = targets[hit.target];
        if (!std::isfinite(hit.point.x) || !std::isfinite(hit.point.y))
            continue;

        const cv::Point2f fromPrediction = hit.point - target.pred;
        const cv::Point2f fromSeed = hit.point - hit.seed;
        const float maxOffset = pose::maxOffset(target.cell);
        const float maxRefineOffset = pose::maxRefineOffset(target.cell);

        if (fromPrediction.dot(fromPrediction) > maxOffset * maxOffset ||
            fromSeed.dot(fromSeed) > maxRefineOffset * maxRefineOffset)
        {
            continue;
        }

        cv::KeyPoint keypoint;
        keypoint.pt = hit.point;
        keypoint.size = static_cast<float>(
            2 * std::max(
                target.subpixWindow.width,
                target.subpixWindow.height
            ) + 1
        );
        keypoint.class_id = -1;

        keys.push_back(keypoint);
        hitIds.push_back(i);
    }

    if (!keys.empty())
        prisma::assignClass(gray, keys);

    for (int i = 0; i < static_cast<int>(keys.size()); ++i)
    {
        const HarrisHit& hit = hits[hitIds[i]];
        const PoseTarget& target = targets[hit.target];
        const cv::KeyPoint& keypoint = keys[i];

        if (target.cls >= 0 && keypoint.class_id != target.cls)
            continue;
        if (target.state >= valid.size())
            continue;

        prisma::addMatch(
            target.obj,
            keypoint.pt,
            valid[target.state].objPoints,
            valid[target.state].imgPoints,
            4.f
        );
    }
}

void PrismaDetector::PData::addDirectPoints(
    std::vector<MarkerState>& valid
) const
{
    for (MarkerState& state : valid)
    {
        const MarkerModel* model = findModel(state.id);
        if (model == nullptr)
            continue;

        // Direct ArUco corners. Below the minimum cell size their errors are
        // correlated across the four corners and bias the rotation, so they
        // are kept aside and only used when nothing else is available.
        std::vector<const prisma::ArucoHit*> smallArucos;

        for (const prisma::ArucoHit& aruco : state.arucos)
        {
            if (aruco.imgCorners.size() != 4 || aruco.objCorners.size() != 4)
                continue;

            if (pose::arucoCellPx(aruco) < pose::kMinArucoCornerCellPx)
            {
                smallArucos.push_back(&aruco);
                continue;
            }

            prisma::addAruco4(
                aruco,
                state.objPoints,
                state.imgPoints
            );
        }

        if (!state.homography.empty())
        {
            for (const prisma::Marker& detected : state.levels)
            {
                const auto item = model->geometry.levels.find(
                    detected.id);
                if (item == model->geometry.levels.end())
                    continue;

                const auto& modelKeypoints = item->second.getKeyptsRef();
                if (modelKeypoints.size() < 4 || detected.size() < 4)
                    continue;

                // The outer corners of every detected level are always used,
                // also when its internal corners are searched with Harris:
                // Harris often misses the outer corners of the marker, which
                // give the largest lever arm for the rotation. removeDup
                // discards them when Harris has already found them.
                for (int corner = 0; corner < 4; ++corner)
                {
                    const cv::Point2f& modelPoint = modelKeypoints[corner].pt;
                    prisma::addMatch(
                        cv::Point3f(modelPoint.x, modelPoint.y, 0.f),
                        detected[corner],
                        state.objPoints,
                        state.imgPoints,
                        5.f
                    );
                }
            }
        }

        if (state.objPoints.size() < 4)
        {
            for (const prisma::ArucoHit* aruco : smallArucos)
            {
                prisma::addAruco4(
                    *aruco,
                    state.objPoints,
                    state.imgPoints
                );
            }
        }

        prisma::removeDup(
            state.objPoints,
            state.imgPoints,
            4.f
        );
    }
}

// Convert a validated instance into a public PRISMarker result
bool PrismaDetector::PData::buildResult(
    const MarkerState& state,
    const MarkerModel& model,
    const DetectionObservations& observations,
    bool pose,
    PrismaMarker& marker
) const
{
    marker.type = PRISMA_CUSTOM;
    marker.id = state.id;

    std::map<int, std::vector<cv::Point2f>> detectedLevels;

    for (const prisma::Marker& level : state.levels)
    {
        if (level.size() < 4)
            continue;

        detectedLevels[level.id] = {
            level[0],
            level[1],
            level[2],
            level[3]
        };
    }

    // Depth of each level: 1 is the external (largest) level and N the
    // innermost one; the central ArUco is reported as 0.
    std::vector<std::pair<float, int>> levelsBySize;
    levelsBySize.reserve(model.geometry.levels.size());

    for (const auto& item : model.geometry.levels)
        levelsBySize.emplace_back(item.second.getMarkerSize(), item.first);

    std::sort(
        levelsBySize.begin(),
        levelsBySize.end(),
        [](const auto& a, const auto& b) { return a.first > b.first; }
    );

    std::map<int, int> levelDepth;
    for (std::size_t i = 0; i < levelsBySize.size(); ++i)
        levelDepth[levelsBySize[i].second] = static_cast<int>(i) + 1;

    for (const auto& item : model.geometry.levels)
    {
        const auto level = detectedLevels.find(item.first);

        if (level == detectedLevels.end())
            continue;
        marker.levelCorners.push_back(level->second);
        marker.levelIndices.push_back(levelDepth[item.first]);

        if (item.first == model.geometry.idExternal)
            marker.corners = level->second;
    }

    marker.arucoCorners.reserve(observations.arucos.size());

    auto addArucoCorners =
        [&](const std::vector<cv::Point2f>& corners)
        {
            if (corners.size() != 4)
                return;

            const cv::Point2f center = quadCenter(corners);

            for (const auto& current : marker.arucoCorners)
            {
                if (current.size() == 4 &&
                    cv::norm(center - quadCenter(current)) <= 2.f)
                {
                    return;
                }
            }

            marker.arucoCorners.push_back(corners);
        };

    for (const ArucoObservation& observation : observations.arucos)
    {
        if (observation.markerId != state.id)
            continue;

        addArucoCorners(observation.aruco.imgCorners);
    }

    std::vector<cv::Point2f> estimatedCorners;

    if (marker.corners.size() != 4)
    {
        if (pose)
        {
            estimateCorners(
                model.geometry,
                state.objPoints,
                state.imgPoints,
                estimatedCorners
            );
        }
        else
        {
            projectOuterCorners(
                model.geometry,
                state.homography,
                estimatedCorners
            );
        }
    }

    if (!state.levels.empty() &&
        marker.corners.size() != 4 &&
        estimatedCorners.size() == 4)
    {
        marker.corners = estimatedCorners;
    }

    const std::vector<cv::Point2f>& centerCorners =
        marker.corners.size() == 4
            ? marker.corners
            : estimatedCorners;

    if (centerCorners.size() == 4)
    {
        marker.center = cv::Point2f(0.f, 0.f);

        for (const cv::Point2f& corner : centerCorners)
            marker.center += corner;

        marker.center *= 0.25f;
        marker.hasCenter = true;
    }

    if (!state.levels.empty() &&
        marker.corners.size() != 4 &&
        marker.levelCorners.empty())
    {
        return false;
    }

    // The central ArUco is reported as level 0 when it was validated.
    for (const prisma::ArucoHit& aruco : state.arucos)
    {
        if (aruco.internalId >= 0 || aruco.imgCorners.size() != 4)
            continue;

        marker.levelCorners.push_back(aruco.imgCorners);
        marker.levelIndices.push_back(0);
        break;
    }

    // Level of each validated ArUco: internal ids are levelIndex * 4 + slot,
    // with levelIndex 0 the external level (depth 1); negative ids are the
    // central one (depth 0).
    std::set<int> arucoLevels;

    for (const prisma::ArucoHit& aruco : state.arucos)
        arucoLevels.insert(aruco.internalId < 0 ? 0 : aruco.internalId / 4 + 1);

    marker.arucoLevels.assign(arucoLevels.begin(), arucoLevels.end());

    if (!pose)
        return true;

    if (state.objPoints.size() == state.imgPoints.size() &&
        state.objPoints.size() >= 4)
    {
        marker.objPoints = state.objPoints;
        marker.imgPoints = state.imgPoints;
        return true;
    }

    if (state.levels.empty() || marker.corners.size() != 4)
        return false;

    const prisma::Marker& outer =
        model.geometry.levels.at(
            model.geometry.idExternal
        );

    for (int corner = 0; corner < 4; ++corner)
    {
        marker.imgPoints.push_back(marker.corners[corner]);

        marker.objPoints.emplace_back(
            outer.keypts[corner].pt.x,
            outer.keypts[corner].pt.y,
            0.f
        );
    }

    return true;
}

std::vector<PrismaMarker> PrismaDetector::PData::buildResults( const std::vector<MarkerState>& valid, const DetectionObservations& observations,
bool pose
) const
{
    std::vector<PrismaMarker> result;
    result.reserve(valid.size());

    for (const MarkerState& state : valid)
    {
        const MarkerModel* model = findModel(state.id);

        if (model == nullptr)
            continue;

        PrismaMarker marker;

        if (buildResult(
                state,
                *model,
                observations,
                pose,
                marker))
        {
            result.push_back(std::move(marker));
        }
    }

    std::sort(
        result.begin(),
        result.end(),
        [](const PrismaMarker& a,
           const PrismaMarker& b)
        {
            if (a.id != b.id)
                return a.id < b.id;

            const cv::Point2f ca =
                a.corners.size() == 4
                    ? quadCenter(a.corners)
                    : (a.hasCenter ? a.center : cv::Point2f());

            const cv::Point2f cb =
                b.corners.size() == 4
                    ? quadCenter(b.corners)
                    : (b.hasCenter ? b.center : cv::Point2f());

            if (ca.y != cb.y)
                return ca.y < cb.y;

            return ca.x < cb.x;
        }
    );

    return result;
}

std::vector<PrismaMarker> PrismaDetector::PData::detectFrame(const cv::Mat& image, bool pose)
{
    // Extract reusable square candidates from the frame.
    prisma::DetectionContext context =
        detector.extractCandidates(image);

    if (context.gray.empty() || context.squares.empty())
        return {};

    // Recognize low-level pieces.
    const prisma::DetectionEvidence evidence =
        detector.detect(context);


    // Translate low-level evidence to PRISMarker-aware observations.
    const DetectionObservations observations =
        makeObservations(evidence);


    if (observations.levels.empty() &&
        observations.arucos.empty())
    {
        return {};
    }

    // Build hypotheses internally and validate complete PRISMarker instances.
    std::vector<MarkerState> valid =
        validateObservations(
            observations,
            context.gray.size()
        );

    if (valid.empty())
        return {};

    // Pose data optional
    if (pose)
        addPosePoints(valid, context.gray);


    return buildResults(
        valid,
        observations,
        pose
    );
}

std::vector<PrismaMarker> PrismaDetector::detect(InputArray _image, bool pose)
{
    const cv::Mat image = _image.getMat();

    if (image.empty() || !data || !data->loaded())
        return {};


    return data->detectFrame(image, pose);
}

std::vector<PrismaMarker> detectPrisma(InputArray image, PrismaDict dictionary, bool pose)
{
    static thread_local cv::Ptr<PrismaDetector> detector;
    static thread_local PrismaDict current =
        static_cast<PrismaDict>(-1);

    if (!detector)
    {
        detector =
            cv::makePtr<PrismaDetector>(
                dictionary
            );

        current = dictionary;
    }
    else if (current != dictionary)
    {
        detector->setDictionary(dictionary);
        current = dictionary;
    }

    return detector->detect(image, pose);
}


void drawPrisma(InputOutputArray _image, const std::vector<PrismaMarker> &markers,
                          Scalar color, bool drawAllImagePoints) {
    cv::Mat image = _image.getMat();

    float lineWidthF = std::max(1.f, std::min(5.f, float(image.cols) / 500.f));
    int lineWidth = int(std::round(lineWidthF));
    int dotRadius = std::max(2, int(std::round(lineWidthF * 1.2f)));

    for (const auto &m : markers) {
        const bool hasCorners = m.corners.size() >= 4;

        if (m.type == PRISMA_CUSTOM && !m.levelCorners.empty()) {
            for (const auto &level : m.levelCorners) {
                if (level.size() < 4) continue;
                for (int i = 0; i < 4; i++)
                    cv::line(image, level[i], level[(i + 1) % 4], color, lineWidth);
            }
        } else if (hasCorners) {
            for (int i = 0; i < 4; i++)
                cv::line(image, m.corners[i], m.corners[(i + 1) % 4], color, lineWidth);
        }

        if (m.type == PRISMA_CUSTOM) {
            for (const auto &aruco : m.arucoCorners) {
                if (aruco.size() < 4) continue;
                for (int i = 0; i < 4; i++)
                    cv::line(image, aruco[i], aruco[(i + 1) % 4], color, lineWidth);
            }
        }

        if (drawAllImagePoints)
            for (const auto &pt : m.imgPoints)
                cv::circle(image, pt, dotRadius, color, -1);
    }
}

void getSolvePnpPoints(const PrismaMarker &marker, OutputArray objPoints,
                       OutputArray imgPoints, float markerSize) {
    // Scale normalized 3D points.
    float scale = markerSize / 2.0f;
    int n = int(marker.imgPoints.size());

    if (n == 0) {
        imgPoints.assign(cv::Mat());
        objPoints.assign(cv::Mat());
        return;
    }

    cv::Mat imgMat(n, 1, CV_32FC2);
    cv::Mat objMat(n, 1, CV_32FC3);
    for (int i = 0; i < n; i++) {
        imgMat.at<cv::Vec2f>(i) = {marker.imgPoints[i].x, marker.imgPoints[i].y};
        objMat.at<cv::Vec3f>(i) = {marker.objPoints[i].x * scale,
                                   marker.objPoints[i].y * scale,
                                   marker.objPoints[i].z * scale};
    }
    imgPoints.assign(imgMat);
    objPoints.assign(objMat);
}


} // namespace aruco2
} // namespace cv