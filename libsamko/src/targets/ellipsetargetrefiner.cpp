#include <libsamko/targets/ellipsetargetrefiner.h>

#include <libsamko/cvutils.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <numeric>

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
    Mat gradientImg(img.size(), CV_8SC3);

    Laplacian(CvUtils::toGrayscale(img), gradientImg, 1, 5);

    auto pixels = findThresholdedPixels(gradientImg, approxPt);
    BorderMap borderMap = generateBorder(pixels);
    return getCenter(borderMap) + Point2f(woi.x, woi.y);
}

vector<Point> EllipseTargetRefiner::findThresholdedPixels(Mat& img, const Point& innerPt) const {

    //find black pixels - edges by Laplacian
    typedef Vec<char, 3> T;
    vector<Point> black;
    int id = 0;
    int width = img.cols;

    MatIterator_<T> akt = img.begin<T>(), end = img.end<T>();
    for(; akt != end; ++akt, ++id) {
        T val = *akt;
        if (val[0] + val[1] + val[2] > 0) // find white pixels
            black.emplace_back(id % width, id / width);
    }
    return black;
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

Point2f EllipseTargetRefiner::getCenter(const BorderMap &borderMap) const {
    Point2f sum(0.f,0.f);
    int total = 0;
    for (auto akt = borderMap.cbegin(), end = borderMap.cend(); akt!=end; ++akt) {
        int count = akt->second.max - akt->second.min + 1;
        total += count;
        sum.x += count * akt->second.min + (count-1) * count / 2;
        sum.y += akt->first * count;
    }
    return Point2f(sum.x / total, sum.y / total);
}

} //namespace samko
