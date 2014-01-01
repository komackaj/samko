#include <libsamko/targets/ellipsetargetrefiner.h>

#include <libsamko/cvutils.h>
#include <opencv2/imgproc/imgproc.hpp>
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

    Point reduced(approxPt.x, approxPt.y);
    reduced.x -= woi.x;
    reduced.y -= woi.y;

    Mat lapl(image.size(), CV_8SC1),
        blurred;
    GaussianBlur(CvUtils::toGrayscale(img), blurred, Size(5, 5), 3);
    Laplacian(blurred, lapl, 1, 5);
    adaptiveThreshold(CvUtils::toGrayscale(lapl), img, 255, ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 3, -5);
    _measImg = shared_ptr<Mat>(new Mat(CvUtils::toGrayscale(img)));
    imwrite("gray.png", *_measImg);

    BorderMap contour = findEllipseContour(*_measImg, reduced);
    imwrite("work.png", *_measImg);

    RotatedRect ellipse = fitEllipseBorder(contour);
    return ellipse.center + Point2f(woi.x, woi.y);
}

EllipseTargetRefiner::BorderMap EllipseTargetRefiner::findEllipseContour(Mat& img, const cv::Point &innerPt) const {
    vector<vector<Point> > contours;
    Mat hierarchy;
    findContours(img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    *_measImg = CvUtils::gray2RGB(*_measImg);

    pair<size_t, size_t> best = make_pair(0, 0); //span, id
    BorderMap bestBorder;
    size_t id = -1;
    //cout << contours.size() << " contours found" << endl;
    for (const auto& contour : contours) {
        id++;
        if ( contour.size() < 0.5 * M_PI * _targetRadius ) {
          //  drawContours(img, contours, id, Scalar(0, 0, 0));
            continue;
        }

        // HACK - cannot construct Vec4i from hierarchy.col(id) (4-channel matrix with 1x1 dimenstion),
        //        so we construct vector from raw data
        int* p = hierarchy.col(id).ptr<int>();
        vector<int> h(p, p+4);
      //  cout << "Hierarchy for " << id  << ": "<< Mat(h) << endl;

        if (h[3] == -1) { // skip first-level hierarchy contours - will be image border
            //drawContours(img, contours, id, Scalar(0, 0, 0));
            continue;
        }

        int val = (id + 1) * 255 / (contours.size() + 1);
        drawContours(img, contours, id, Scalar(val, 0, 0));

        BorderMap bm = generateBorder(contour);
        auto elem = bm.find(innerPt.y);
        if ( elem == bm.end() || (innerPt.x < elem->second.min) || (innerPt.x > elem->second.max))
            continue;   //border doesn't cover inner point

        if (elem->second.span() > best.first) {
            best.first = elem->second.span();
            best.second = id;
            bestBorder = std::move(bm);
        //    cout << "Contour: " << contour << endl;
        }
    }

    drawContours(img, contours, best.second, Scalar(0, 0, 255));
    return bestBorder;
}

EllipseTargetRefiner::BorderMap EllipseTargetRefiner::generateBorder(const std::vector<Point> &pts) const {
    BorderMap borderMap;  // maps x coordinate to minimum and maximum
    for (Point pt : pts) {
       minmax data = {pt.x, pt.x};
       auto item = borderMap.insert(std::make_pair(pt.y, data));
       if (!item.second){
           minmax& cdata = item.first->second;
           cdata.min = min(pt.x, cdata.min);
           cdata.max = max(pt.x, cdata.max);
       }
    }
    return borderMap;
}

RotatedRect EllipseTargetRefiner::fitEllipseBorder(const BorderMap& bordermap) const {
    vector<Point> pts;
    auto akt = bordermap.begin(), end = bordermap.end();
    for(; akt!=end; ++akt) {
        pts.emplace_back(akt->second.min, akt->first);
        pts.emplace_back(akt->second.max, akt->first);
    }
    return fitEllipse(pts);
}

const Mat* EllipseTargetRefiner::getLastMeasImage() const {
    return _measImg.get();
}

} //namespace samko
