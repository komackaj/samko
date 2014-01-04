#include <libsamko/targets/correlrefiner.h>

namespace  samko {

using namespace std;
using namespace cv;

CorrelRefiner::CorrelRefiner(size_t windowSize) : _winsize(windowSize)
{}

Point2f CorrelRefiner::refine(const Mat &image, const Point2f &approxPt) {
    return approxPt;
}

} //namespace
