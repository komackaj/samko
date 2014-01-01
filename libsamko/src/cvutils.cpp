#include <libsamko/cvutils.h>

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


} //namespace samko
