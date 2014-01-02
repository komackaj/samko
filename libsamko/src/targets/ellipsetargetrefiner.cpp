#include <libsamko/targets/ellipsetargetrefiner.h>

#include <libsamko/cvutils.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <numeric>
#include <stdexcept>
#include <opencv2/highgui/highgui.hpp>

//#include <iostream>

using namespace cv;
using namespace std;

namespace samko {


EllipseTargetRefiner::EllipseTargetRefiner(uint targetRadius) : _targetRadius(targetRadius) {
}

Point2f EllipseTargetRefiner::refine(const Mat& image, const Point2f& approxPt) {
    // window of interest - must cover target in all possibilities,
    // therefore we take window radius as 2*_targetRadius
    Rect woi = CvUtils::squareFromCenter(approxPt, 2 * _targetRadius);
    woi.width = min(woi.width, image.cols);
    woi.height = min(woi.height, image.rows);
    Mat img(image, woi);

    Mat lapl(image.size(), CV_8SC1),
        blurred;
    GaussianBlur(CvUtils::toGrayscale(img), blurred, Size(5, 5), 3);
    Laplacian(blurred, lapl, 1, 5);
    adaptiveThreshold(CvUtils::toGrayscale(lapl), img, 255, ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 3, 5);
    _measImg = shared_ptr<Mat>(new Mat(img));

    auto contour = findEllipseContour(*_measImg);
    if (contour.size() < 5)
        throw runtime_error("Cannot detect target marker");

    imwrite("work.png", *_measImg);

    RotatedRect ellipse = fitEllipse(contour);
    return ellipse.center + Point2f(woi.x, woi.y);
}

vector<Point> EllipseTargetRefiner::findEllipseContour(Mat& img) const {
    vector<vector<Point> > contours;
    Mat hierarchy;
    findContours(img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    pair<size_t, size_t> best = make_pair(0, 0); //num points, id
    size_t id = -1;
    //cout << contours.size() << " contours found" << endl;
    for (const auto& contour : contours) {
        id++;
        // HACK - cannot construct Vec4i from hierarchy.col(id) (4-channel matrix with 1x1 dimenstion),
        //        so we construct vector from raw data
        int* p = hierarchy.col(id).ptr<int>();
        vector<int> h(p, p+4);
      //  cout << "Hierarchy for " << id  << ": "<< Mat(h) << endl;

        if (h[3] == -1) // skip first-level hierarchy contours - will be image border
            continue;

        int val = (id + 1) * 255 / (contours.size() + 1);
        drawContours(img, contours, id, Scalar(val, val, val));
        if (contour.size() > best.first){
            best.first = contour.size();
            best.second = id;
        //    cout << "Contour: " << contour << endl;
        }
    }

    return contours[best.second];
}

const Mat* EllipseTargetRefiner::getLastMeasImage() const {
    return _measImg.get();
}

} //namespace samko
