#ifndef COMMON_H
#define COMMON_H

#include <opencv2/core/core.hpp>

void ExpectPoints2fNear(const cv::Point2f& pt1, const cv::Point2f& pt2, float eps);

#endif // COMMON_H
