#include <libsamko/targets/correlrefiner.h>

#include <libsamko/cvutils.h>


//TODO: remove
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

namespace  samko {

using namespace std;
using namespace cv;

CorrelRefiner::CorrelRefiner(size_t windowSize) : _winsize(windowSize), _lastImage(0,0,CV_8UC1)
{}

Point2f CorrelRefiner::refine(const Mat &image, const Point2f &approxPt) {

    Point center(approxPt.x, approxPt.y);
    Rect woi = CvUtils::squareFromCenter(center, _winsize);
    Mat window(image, woi);
    Mat gray = CvUtils::toGrayscale(window);

    if (!_lastImage.cols) {
        _lastImage = gray;
        return approxPt;
    }

    Mat similarity = genSimilarityMatrix(_lastImage, gray, _winsize / 2);
    Point2f ret = similarityMax(similarity, _max);
    ret.x += woi.x;
    ret.y += woi.y;
    return ret;
}

float CorrelRefiner::imgDiff(const cv::Mat &img1, const cv::Point &pinpoint1, const cv::Mat &img2, const cv::Point &pinpoint2, int winSize) const {
    //cout << pinpoint1 << " on " << pinpoint2 << endl;

    // minimum rect
    Rect shrinkRect(min(0, min(pinpoint1.x - winSize, pinpoint2.x - winSize)),
                    min(0, min(pinpoint1.y - winSize, pinpoint2.y - winSize)),
                    min(0, min(img1.cols - winSize - pinpoint1.x, img2.cols - winSize - pinpoint2.x)),
                    min(0, min(img1.rows - winSize - pinpoint1.y, img2.rows - winSize - pinpoint2.y)));
    Rect r1 = CvUtils::squareFromCenter(pinpoint1, winSize),
         r2 = CvUtils::squareFromCenter(pinpoint2, winSize);
    r1.x += shrinkRect.x;
    r2.x += shrinkRect.x;
    r1.y += shrinkRect.y;
    r2.y += shrinkRect.y;
    r1.height += shrinkRect.height;
    r2.height += shrinkRect.height;
    r1.width += shrinkRect.width;
    r2.width += shrinkRect.width;

    Mat cut1(img1, r1),
        cut2(img2, r2);

    return 100.f - mean(cut1 - cut2).val[0] / 2.55f;
}

Mat CorrelRefiner::genSimilarityMatrix(const cv::Mat& img1, const cv::Mat& img2, int compWinSize) {
    Point pinpointSrc(img1.cols / 2, img2.rows / 2);

    float best = -1.f;
    typedef float tp;
    Rect searchWin = CvUtils::squareFromCenter(pinpointSrc, compWinSize);
    //cout << "Searchwin: " << searchWin.tl() << searchWin.br() << endl;
    Mat ret(searchWin.size(), DataType<tp>::type);
    MatIterator_<tp> akt = ret.begin<tp>();
    for (int row = searchWin.y; row <= searchWin.y + searchWin.height; ++row)
        for (int col = searchWin.x; col <= searchWin.x + searchWin.width; ++col, ++akt) {
            Point pinpointDst(col, row);
            *akt = imgDiff(img1, pinpointSrc, img2, pinpointDst, compWinSize);
            if (*akt > best) {
                best = *akt;
                _max = pinpointDst;
            }
        }
    return ret;
}

Point2f CorrelRefiner::similarityMax(const cv::Mat& sim, const cv::Point& approxMax) const {
    //cout << sim << endl;
    //cout << "Maximum in: " << approxMax << endl;
    return approxMax;
}

} //namespace
