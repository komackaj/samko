#ifndef ELLIPSETARGETREFINERDIALOG_H
#define ELLIPSETARGETREFINERDIALOG_H

#include <QDialog>
#include <libsamko/targets/ellipsetargetrefiner.h>

namespace cv {
  class Mat;
}

namespace Ui {
class EllipseTargetRefinerDialog;
}

class EllipseTargetRefinerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EllipseTargetRefinerDialog(cv::Mat image, QWidget *parent = 0);
    ~EllipseTargetRefinerDialog();

private slots:
    void on_image_mousePressed(QMouseEvent *e);

private:
    Ui::EllipseTargetRefinerDialog *ui;
    cv::Mat _image;
    samko::EllipseTargetRefiner refiner;
};

#endif // ELLIPSETARGETREFINERDIALOG_H
