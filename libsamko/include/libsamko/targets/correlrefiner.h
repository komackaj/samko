#ifndef CORRELREFINER_H
#define CORRELREFINER_H

#include "targetrefiner.h"

namespace  samko {

class CorrelRefiner : public TargetRefiner {

public:

    /**
     * @brief Standartd constructor
     * @param windowSize    size of correlation window in pixels (should be grater than marker size)
     */
    CorrelRefiner(size_t windowSize);

    virtual cv::Point2f refine(const cv::Mat& image, const cv::Point2f& approxPt);

private:

    size_t _winsize;
};

} //namespace

#endif // CORRELREFINER_H
