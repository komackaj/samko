#ifndef HEADER_3C9BB971E68CCD0
#define HEADER_3C9BB971E68CCD0

#pragma once
#include <opencv2/core/core.hpp>

namespace samko {

/// Utilities for OpenCV
class CvUtils {

public:

	static float PointDist(const cv::Point2f p1, const cv::Point2f p2);
};

} //namespace samko
#endif // header guard
