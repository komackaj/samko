#include "ellipsetargetrefinerdialog.h"
#include "ui_ellipsetargetrefinerdialog.h"

#include "utils.h"
#include <opencv2/highgui/highgui.hpp>

EllipseTargetRefinerDialog::EllipseTargetRefinerDialog(cv::Mat image, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EllipseTargetRefinerDialog),
    _image(image),
    refiner(50)
{
    ui->setupUi(this);
    setLayout(ui->mainLayout);

    cv::Mat rgb;
    QImage img = Utils::imageFromMat(image, rgb);
    ui->image->addImage(img);
}

EllipseTargetRefinerDialog::~EllipseTargetRefinerDialog()
{
    delete ui;
}

void EllipseTargetRefinerDialog::on_image_mousePressed(QMouseEvent *e)
{
    if (e->button() != Qt::MouseButton::LeftButton)
        return;

    cv::Point approxPt(e->pos().x(), e->pos().y());
    cv::Point2f refinedPt = refiner.refine(_image, approxPt);
    qDebug("refined to %f, %f", refinedPt.x, refinedPt.y);
    cv::imwrite("work.png", *refiner.getLastMeasImage());
    ui->image->addMarker( QPoint(refinedPt.x, refinedPt.y) );
}
