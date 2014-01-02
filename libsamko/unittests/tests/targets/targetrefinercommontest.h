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

void staticTargetTest(TargetRefiner& refiner) {
    Point center(10,10);
    constexpr int NUM_SETS = 6;
    constexpr size_t IMAGES_PER_TARGET = 30;

    vector<Point2f> pts(IMAGES_PER_TARGET);

    for (int setId = 1; setId < NUM_SETS; ++setId) {
        for (size_t i = 0; i < IMAGES_PER_TARGET; ++i) {
            stringstream ss;
            ss << "data/staticTarget/" << setId << "_";
            ss << setfill('0') << setw(4) << i << ".png";
            Mat img = imread(ss.rdbuf()->str());
            pts[i] = refiner.refine(img, center);
        }

        Scalar mean, stdev;
        meanStdDev(pts, mean, stdev);
        float posErr = sqrt(0.5 * stdev.dot(stdev));
        /*
        cout << "Set " << setId << endl;
        cout << "Mean: " << mean[0] << ", " << mean[1] << endl;
        cout << "Stdev: " << stdev[0] << ", " << stdev[1] << endl;
        cout << "Position error: " << posErr << endl;
        //cout << "Points: "<< pts << endl;
        */

        EXPECT_GT(posErr, 0.f);
        EXPECT_LT(posErr, 0.5f);
    }
}

#endif // TARGETREFINERCOMMONTEST_H
