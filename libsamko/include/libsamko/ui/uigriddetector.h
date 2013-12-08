#ifndef USERGRIDDETECTOR_H_INCLUDED
#define USERGRIDDETECTOR_H_INCLUDED

#include <vector>
#include <opencv2/core/core.hpp>
#include <memory>

namespace samko {

/// Abstract class for detecting calibration grid on image via user input
class UIGridDetector {
public:

    /// standard destructor
    /// @note virtual for mocking
    virtual ~UIGridDetector();

    /** Generates squared grid of calibration grid from corners coordinates
     *  @param  corners     coordinates of three corners - top-left, top-right, bottom-left
                            (in that order)
     *  @param  cols        number of columns in calibration grid, greater than 0
     *  @param  rows        number of rows in calibration grid, greater than 0
     *  @throws std::runtime error on invalid input parameters
     *  @returns vector grid cols x rows from top-left to bottom-right (per row) */
    std::vector<cv::Point2f> generateGrid(std::vector<cv::Point2f> corners,
                                          unsigned int cols, unsigned int rows) const;

    /** Get calibration grid coordinates from user input
     *  @param  image   image of calibration grid
     *  @param  cols    number of columns in calibration grid
     *  @param  rows    number of rows in calibration grid
     *  @throws samko::UIException on user abort
     *  @returns vector of grid image coordinates sorted from top-left to right-bottom
                 (by meaning in LCS of grid) */
    std::vector<cv::Point2f> getGrid(const cv::Mat& image, unsigned int cols, unsigned int rows);

protected:

    /** Receive corners from user input
     *  @param  image   image of calibration grid
     *  @returns corners as specified in generateGrid method
     *  @throws samko::UIException on user abort */
    virtual std::vector<cv::Point2f> getCornersFromUser(const cv::Mat& image) = 0;
};

} //namespace

#endif // USERGRIDDETECTOR_H_INCLUDED
