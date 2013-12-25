#ifndef UTILS_H
#define UTILS_H

#include <QImage>
#include <opencv2/core/core.hpp>

class Utils
{
public:
    static QImage imageFromMat(const cv::Mat& src, cv::Mat& convData);
};

#endif // UTILS_H
