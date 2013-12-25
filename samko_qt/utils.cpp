#include "utils.h"

#include <opencv2/imgproc/imgproc.hpp>

QImage Utils::imageFromMat(const cv::Mat& src, cv::Mat& convData)
{
    cvtColor(src, convData, CV_BGR2RGBA);
    QImage img(const_cast<uchar*>(convData.data), convData.cols, convData.rows, convData.step1(), QImage::Format_ARGB32);
    /*QImageWriter writer("/tmp/test.png");
    if (!writer.write(img))
        qDebug() << writer.errorString();*/
    return img;
}
