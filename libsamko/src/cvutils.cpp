#include <libsamko/cvutils.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

namespace samko {

float CvUtils::PointDist(const Point2f &p1, const Point2f &p2) {
	float dx = p1.x - p2.x;
	float dy = p1.y - p2.y;
	return sqrt(dx*dx + dy*dy);
}

Rect CvUtils::squareFromCenter(const cv::Point2f& center, float inflateBy) {
    return Rect(
        Point( std::max(0, int(center.x - inflateBy)), std::max(0, int(center.y - inflateBy))),
        Size(2 * inflateBy, 2 * inflateBy)
    );
}

Mat CvUtils::gray2RGB(const cv::Mat& src){
    Mat ret(src.size(), CV_8UC3);
    if (src.channels() == 1)
        cvtColor(src, ret, CV_GRAY2RGB);
    else
        ret = src.clone();
    return ret;
}

Mat CvUtils::toGrayscale(const cv::Mat& src){
    Mat ret(src.size(), CV_8UC1);
    if (src.channels() == 1) {
        if (src.type() == CV_8UC1)
            ret = src.clone();
        else {
            MatConstIterator_<short> srcAkt = src.begin<short>();
            MatIterator_<uchar> dstAkt = ret.begin<uchar>(), dstEnd = ret.end<uchar>();
            for (; dstAkt!=dstEnd; ++srcAkt, ++dstAkt){
                *dstAkt = *srcAkt + 128;
            }
        }
    }
    else
        cvtColor(src, ret, CV_RGB2GRAY);
    return ret;
}

} //namespace samko
