#include <libsamko/targets/correlrefiner.h>

#include <libsamko/cvutils.h>
#include <stdexcept>

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
    //cout << "Approx " << _max << "refined to " << ret << endl;
    ret.x += woi.x + _simStart.x;
    ret.y += woi.y + _simStart.y;
    return ret;
}

float CorrelRefiner::imgDiff(const cv::Mat &img1, const cv::Point &pinpoint1, const cv::Mat &img2, const cv::Point &pinpoint2, int winSize) const {
    // minimum rect
    Rect shrinkRect(std::min(0, std::min(pinpoint1.x - winSize, pinpoint2.x - winSize)),
                    std::min(0, std::min(pinpoint1.y - winSize, pinpoint2.y - winSize)),
                    std::min(0, std::min(img1.cols - winSize - pinpoint1.x, img2.cols - winSize - pinpoint2.x)),
                    std::min(0, std::min(img1.rows - winSize - pinpoint1.y, img2.rows - winSize - pinpoint2.y)));

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

    return -1.f * norm(cut2 - cut1, NORM_L2) / cut2.size().area();
}

Mat CorrelRefiner::genSimilarityMatrix(const cv::Mat& img1, const cv::Mat& img2, int compWinSize) {
    Point pinpointSrc(img1.cols / 2, img2.rows / 2);

    float best = -1.f;
    typedef float tp;
    Rect searchWin = CvUtils::squareFromCenter(pinpointSrc, compWinSize);
    _simStart = searchWin.tl();
    //cout << "Searchwin: " << searchWin.tl() << searchWin.br() << endl;
    Mat ret(searchWin.width+1, searchWin.height+1, DataType<tp>::type);
    MatIterator_<tp> akt = ret.begin<tp>();
    for (int row = searchWin.y; row <= searchWin.y + searchWin.height; ++row) {
        for (int col = searchWin.x; col <= searchWin.x + searchWin.width; ++col, ++akt) {
            Point pinpointDst(col, row);
            *akt = imgDiff(img1, pinpointSrc, img2, pinpointDst, compWinSize);
            if (*akt > best) {
                best = *akt;
                _max = Point(col - searchWin.x, row - searchWin.y);
            }
        }
    }
    return ret;
}

Point2f CorrelRefiner::similarityMax(const cv::Mat& sim, const cv::Point& approxMax) const {
    constexpr int winDim = 1;
    constexpr int winsize = 2*winDim+1;
    constexpr int n = winsize * winsize;
    constexpr int k = 5;

    if (approxMax.x < winDim || approxMax.y < winDim || approxMax.x > sim.cols - winDim - 1 || approxMax.y > sim.rows - winDim - 1)
        throw std::runtime_error("Similarity matrix maximum too near to border");

    /* We are looking for maximum of continous similarity. So we approximate
     * values around approxMax with paraboloid fit to data via least-mean-squares and find its maximum */
    Rect win = CvUtils::squareFromCenter(approxMax, winDim);
    win.height += 1;
    win.width += 1;
    Mat A(n, k, CV_32F),
        data = Mat(sim, win).clone().reshape(1, n),
        B = -1.f * data,
        coefs(k, 1, CV_32F, Scalar(0.f));

    int row = 0;
    for (int y = win.y; y < win.br().y; ++y)
        for (int x = win.x; x < win.br().x; ++x, ++row) {
            A.at<float>(row, 0) = 1.f;
            A.at<float>(row, 1) = x;
            A.at<float>(row, 2) = y;
            A.at<float>(row, 3) = x * x;
            A.at<float>(row, 4) = y * y;
        }

    Mat N = A.t() * A;
    Mat Q = N.inv();
    coefs = -1.f * Q * A.t() * B;
    /*cout << "Q" << Q << endl << "Coefs1: " << coefs << endl;
    Mat res = A * coefs - data;
    cout << "Residuals1:" << res << endl;*/

    Point2f ret;
    ret.x = -(coefs.at<float>(1)) / (2 * coefs.at<float>(3));
    ret.y = -(coefs.at<float>(2)) / (2 * coefs.at<float>(4));

    vector<float> config {{1.f, ret.x, ret.y, ret.x * ret.x, ret.y * ret.y}};
    return ret;
}

} //namespace
