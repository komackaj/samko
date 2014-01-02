#ifndef ELLIPSETARGETREFINER_H
#define ELLIPSETARGETREFINER_H

#include "targetrefiner.h"
#include <vector>
#include <map>
#include <memory>

namespace samko {

/**
 * @brief The EllipseTargetRefiner class
 */
class EllipseTargetRefiner : public TargetRefiner
{
public:

    /** @brief Standard constructor.
     *  @param targetRadius  maximal target radius in pixels */
    EllipseTargetRefiner(uint targetRadius);

    virtual cv::Point2f refine(const cv::Mat& image, const cv::Point2f& approxPt);

    /** @brief get last image used for target center measurement
     *  @return nullptr if measurement was not yet performed, image otherwise */
    const cv::Mat* getLastMeasImage() const;

private:
    uint _targetRadius;

    std::shared_ptr<cv::Mat>    _measImg;

    /**
     * @brief find on image edge detected pixels of target (via Laplacian)
     * @param img       image to work with
     * @param innerPt   image point inside target
     * @return image coordinates of border pixels
     */
    std::vector<cv::Point> findEllipseContour(cv::Mat& img) const;
};

} //namespace samko
#endif // ELLIPSETARGETREFINER_H
