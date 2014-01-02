#include <libsamko/targets/ellipsetargetrefiner.h>

namespace samko {


EllipseTargetRefiner::EllipseTargetRefiner()
{
}

cv::Point2f EllipseTargetRefiner::refine(const cv::Point2f& approxPt) {
    return approxPt;
}

} //namespace samko
