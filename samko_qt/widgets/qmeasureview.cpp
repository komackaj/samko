#include "qmeasureview.h"
//#include <QGraphicsPixmapItem>

QMeasureView::QMeasureView(QWidget *parent) :
    QGraphicsView(parent)
{
    _scene = new QGraphicsScene();
    _scene->setSceneRect(rect());
    setScene(_scene);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);

    _pen.setColor("red");
    _brush.setStyle(Qt::SolidPattern);
    _brush.setColor("red");
}

void QMeasureView::mousePressEvent(QMouseEvent * event)
{
    emit mousePressed(event);
}

void QMeasureView::addMarker(QPoint pt)
{
    const int size = 10;
    auto mapped = mapToScene(pt);
    _scene->addEllipse(mapped.x()-size/2, mapped.y()-size/2, size, size, _pen, _brush);
}

void QMeasureView::removeMarker(QPoint pt)
{
    auto item = _scene->itemAt(mapToScene(pt), transform());
    Q_ASSERT(item);
    _scene->removeItem(item);
}

void QMeasureView::addImage(const QImage& img)
{
    QPixmap pixmap(QPixmap::fromImage(img));
    _scene->addPixmap(pixmap);
}
