#include <libsamko/cvutils.h>

using namespace cv;

namespace samko {

float CvUtils::PointDist(const Point2f &p1, const Point2f &p2) {
	float dx = p1.x - p2.x;
	float dy = p1.y - p2.y;
	return sqrt(dx*dx + dy*dy);
}

} //namespace samko