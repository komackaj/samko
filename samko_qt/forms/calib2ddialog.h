#ifndef CALIB2DDIALOG_H
#define CALIB2DDIALOG_H

#include <QDialog>
#include <libsamko/ui/uigriddetector.h>
#include <opencv2/core/core.hpp>

namespace Ui {
class Calib2DDialog;
}

class Calib2DDialog : public QDialog, public samko::UIGridDetector
{
    Q_OBJECT

public:
    explicit Calib2DDialog(QWidget *parent = 0);
    ~Calib2DDialog();

protected:
    virtual std::vector<cv::Point2f> getCornersFromUser(const cv::Mat& image);

private slots:
    void on_image_mousePressed(QMouseEvent *e);

private:
    Ui::Calib2DDialog *ui;
    std::vector<cv::Point2f> pts;
    cv::Mat _rgb;

    void updateUI();
};

#endif // CALIB2DDIALOG_H
