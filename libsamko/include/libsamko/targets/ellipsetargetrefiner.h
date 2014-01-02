#ifndef ELLIPSETARGETREFINER_H
#define ELLIPSETARGETREFINER_H

#include "targetrefiner.h"

namespace samko {

/**
 * @brief The EllipseTargetRefiner class
 */
class EllipseTargetRefiner : public TargetRefiner
{
public:
    EllipseTargetRefiner();

    virtual cv::Point2f refine(const cv::Point2f& approxPt);
};

} //namespace samko
#endif // ELLIPSETARGETREFINER_H
