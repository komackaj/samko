#ifndef TARGETREFINERCOMMONTEST_H
#define TARGETREFINERCOMMONTEST_H

#include <gtest/gtest.h>
#include <libsamko/targets/targetrefiner.h>

#include <vector>
#include "../common.h"

#include <opencv2/highgui/highgui.hpp>

using namespace samko;
using namespace cv;
using namespace std;

Mat generatePreciseCircle(Point center, int radius) {
    Mat ret(100, 100, CV_8UC3, Scalar(255, 255, 255) );
    ellipse(ret, center, Size(radius, radius), 0., 0., 360., 0, -1);
    return ret;
}

void preciseCircleTest(TargetRefiner& refiner, int radius) {
    ASSERT_LE(radius, 30);
    Point2i center(40,40);
    Mat img = generatePreciseCircle(center, radius);

    //first diff must be zero for relative target refiners to work properly
    vector<Point> diffs{{0,0}, {2, 2}, {1,3}, {7, 6}, {4,8}};
    for (const Point& diff : diffs) {
        ASSERT_LT(diff.dot(diff), radius*radius);  // point lies within ellipse
        ExpectPoints2fNear(center, refiner.refine(img, center + diff), 0.2);
    }
}

#endif // TARGETREFINERCOMMONTEST_H
