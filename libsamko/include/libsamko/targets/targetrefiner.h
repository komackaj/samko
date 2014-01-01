#ifndef TARGETREFINER_H
#define TARGETREFINER_H

#include <opencv2/core/core.hpp>

namespace samko {

/// @brief Abstract base class for image target (marker) refiner
class TargetRefiner
{
public:

    /**
     * @brief Refines single point
     * @param image     image of target
     * @param approxPt  approximate coordinates of target on image
     * @return refined (subpixel precision) coordinates of target
     */
    virtual cv::Point2f refine(const cv::Mat& image, const cv::Point2f& approxPt) = 0;
};

} //namespace samko
#endif // TARGETREFINER_H
