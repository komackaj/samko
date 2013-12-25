#include "bussinessdelegate.h"
#include "forms/calib2ddialog.h"
#include "forms/tools/ellipsetargetrefinerdialog.h"

#include <libsamko/calib2d/calibprojective.h>
#include <opencv2/highgui/highgui.hpp>

#include <libsamko/ui/uiexception.h>

using namespace cv;

BussinessDelegate::BussinessDelegate()
{
}

void BussinessDelegate::calibrate()
{
    samko::CalibrationProjective2D calib(2.0, 3.0);
    Mat image = imread("../../bin/data/calibFields/calib010.png");

    try {
        calib.compute(image, 10, 6, &_factory);
    } catch (const samko::UIException&) {
        return;
    }

    //should be cca 297, 179
    auto pt = calib.gridToImage(Point2f(8.f, 4.f));    
    qDebug("Test point is %f, %f", pt.x, pt.y);
}

void BussinessDelegate::toolEllipseTargetRefiner()
{
    Mat image = imread("../../bin/data/calibFields/calib001.jpg");

    EllipseTargetRefinerDialog dlg(image);
    dlg.exec();
}
