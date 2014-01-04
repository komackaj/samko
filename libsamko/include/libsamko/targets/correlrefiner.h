#ifndef CORRELREFINER_H
#define CORRELREFINER_H

#include "targetrefiner.h"

namespace  samko {

class CorrelRefiner : public TargetRefiner {

public:

    /**
     * @brief Standartd constructor
     * @param windowSize    correlation window size in pixels (should be grater than marker size)
     */
    CorrelRefiner(size_t windowSize);

    virtual cv::Point2f refine(const cv::Mat& image, const cv::Point2f& approxPt);

private:

    size_t      _winsize;
    cv::Point   _max;
    cv::Mat     _lastImage;

    float imgDiff(const cv::Mat& img1, const cv::Point& pinpoint1, const cv::Mat& img2, const cv::Point& pinpoint2, int winSize) const;
    cv::Mat genSimilarityMatrix(const cv::Mat& img1, const cv::Mat& img2, int compWinSize);
    cv::Point2f similarityMax(const cv::Mat& sim, const cv::Point& approxMax) const;
};

} //namespace

#endif // CORRELREFINER_H
