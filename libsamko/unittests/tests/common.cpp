#include "common.h"
#include <gtest/gtest.h>

void ExpectPoints2fNear(const cv::Point2f& pt1, const cv::Point2f& pt2, float eps) {
    EXPECT_NEAR(pt1.x, pt2.x, eps);
    EXPECT_NEAR(pt1.y, pt2.y, eps);
}
