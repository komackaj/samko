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

    /// structure holding minimum and maximum target image coordinate for given row
    struct minmax {
        int min, max;
        size_t span() const { return max - min + 1; }
    };

    /// minimum and maximum target coordinate for given row
    typedef std::map<int, minmax>   BorderMap;

    BorderMap generateBorder(const std::vector<cv::Point>& pts) const;

    /**
     * @brief find largest contour covering inner point (excluding image border contour)
     * @param img       image to work with
     * @param innerPt   image point inside target
     * @return image coordinates of border pixels
     */
    BorderMap findEllipseContour(cv::Mat& img, const cv::Point& innerPt) const;

    cv::RotatedRect fitEllipseBorder(const BorderMap& bordermap) const;
};

} //namespace samko
#endif // ELLIPSETARGETREFINER_H
