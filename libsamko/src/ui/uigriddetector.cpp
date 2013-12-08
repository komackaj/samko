#include <libsamko/ui/uigriddetector.h>
#include <stdexcept>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

namespace samko {

UIGridDetector::~UIGridDetector() {
}
vector<Point2f> UIGridDetector::getGrid(const cv::Mat& image, unsigned int cols, unsigned int rows) {
    auto corners = getCornersFromUser(image);
    return generateGrid(corners, cols, rows);
}

vector<Point2f> UIGridDetector::generateGrid(vector<Point2f> corners,
                                             unsigned int cols, unsigned int rows) const {
    if (corners.size() != 3){
        std::stringstream stream;
        stream << "UIGridDetector::generateGrid - generating from " << corners.size() << " corners is not supported";
        throw std::runtime_error(stream.str());
    }

    unsigned int _cols = (cols-1),
                 _rows = (rows-1),
                 gridSize =  cols * rows;

    // Compute affine transformation between image and fictive grid
    vector<Point2f> gridCorners {{Point2f(0.f, 0.f), Point2f(1.f, 0.f), Point2f(0.f, 1.f)}};
    Mat warpMat = getAffineTransform(gridCorners, corners);

    // Generate fictive grid
    vector<Point2f> grid(gridSize);
    float dCol = 1.f / _cols,
          dRow = 1.f / _rows;

    for (unsigned int iRow = 0; iRow < rows; iRow++)
        for (unsigned int iCol = 0; iCol < cols; iCol++)
            grid[iRow * cols + iCol] = Point2f(iCol * dCol, iRow * dRow);

    // Transform it to image coordinates
    vector<Point2f> result(gridSize);
    transform(grid, result, warpMat);
    return result;
}

}// namespace samko
