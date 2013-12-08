#ifndef QMEASUREVIEW_H
#define QMEASUREVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

class QMeasureView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit QMeasureView(QWidget *parent = 0);

    void addImage(const QImage &img);
    void addMarker(QPoint pt);
    void removeMarker(QPoint pt);

signals:
    void mousePressed(QMouseEvent * e);

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QGraphicsScene* _scene;
    QPen            _pen;
    QBrush          _brush;
};

#endif // QMEASUREVIEW_H
