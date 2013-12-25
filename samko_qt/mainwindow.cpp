#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Calibration_triggered()
{
    _delegate.calibrate();
}

void MainWindow::on_actionEllipseTargetRefiner_triggered()
{
    _delegate.toolEllipseTargetRefiner();
}
