#include "calib2ddialog.h"
#include "ui_calib2ddialog.h"
#include <QPushButton>

#include <libsamko/ui/uiexception.h>
#include <opencv2/imgproc/imgproc.hpp>

/*
#include <QImageWriter>
#include <QDebug>
*/

Calib2DDialog::Calib2DDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calib2DDialog)
{
    ui->setupUi(this);
    setLayout(ui->mainLayout);
    updateUI();
}

Calib2DDialog::~Calib2DDialog()
{
    delete ui;
}

void Calib2DDialog::updateUI()
{
    //update hintLabel
    const char* hints[4] {
        "Zvolte levý horní roh pole",
        "Zvolte pravý horní roh pole",
        "Zvolte levý dolní roh pole",
        "Stlačte tlačidlo OK pro potvrzení výsledků"};
    ui->hintLabel->setText(hints[pts.size()]);
    //update
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(pts.size() == 3);
}

void Calib2DDialog::on_image_mousePressed(QMouseEvent *e)
{
    if (pts.size() < 3 && e->button() == Qt::MouseButton::LeftButton){
        pts.emplace_back(e->pos().x(), e->pos().y());
        ui->image->addMarker(e->pos());
    }
    else if (!pts.empty() && e->button() == Qt::MouseButton::RightButton){
        auto last = pts.back();
        ui->image->removeMarker(QPoint(last.x, last.y));
        pts.pop_back();
    }
    updateUI();
}

QImage Calib2DDialog::imageFromMat(const cv::Mat& src, cv::Mat& convData)
{
    cvtColor(src, convData, CV_BGR2RGBA);
    QImage img(const_cast<uchar*>(convData.data), convData.cols, convData.rows, convData.step1(), QImage::Format_ARGB32);
    /*QImageWriter writer("/tmp/test.png");
    if (!writer.write(img))
        qDebug() << writer.errorString();*/
    return img;
}

std::vector<cv::Point2f> Calib2DDialog::getCornersFromUser(const cv::Mat& image)
{
    QImage img = imageFromMat(image, _rgb);
    this->ui->image->addImage(img);
    exec();
    if (pts.size() != 3)
        throw samko::UIException("Calibration aborted by user");
    return pts;
}
