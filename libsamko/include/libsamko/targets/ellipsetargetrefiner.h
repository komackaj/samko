#ifndef ELLIPSETARGETREFINER_H
#define ELLIPSETARGETREFINER_H

#include "targetrefiner.h"
#include <vector>
#include <map>


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

private:
    uint _targetRadius;

    /// structure holding minimum and maximum target image coordinate for given row
    struct minmax {
        int min, max;
    };

    /// minimum and maximum target coordinate for given row
    typedef std::map<int, minmax>   BorderMap;

    /**
     * @brief find on image edge detected pixels of target (via Laplacian)
     * @param img       image to work with
     * @param innerPt   image point inside target
     * @return image coordinates of border pixels
     */
    std::vector<cv::Point> findThresholdedPixels(cv::Mat& img, const cv::Point& innerPt) const;

    /**
     * @brief generates border map
     * @param img
     * @param innerPt
     * @return
     */
    BorderMap generateBorder(const std::vector<cv::Point>& pts) const;

    /// compute center of target from BorderMap
    cv::Point2f getCenter(const BorderMap& borderMap) const;
};

} //namespace samko
#endif // ELLIPSETARGETREFINER_H
