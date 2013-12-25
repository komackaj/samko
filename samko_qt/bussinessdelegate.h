#ifndef BUSSINESSDELEGATE_H
#define BUSSINESSDELEGATE_H

#include "qtuifactory.h"

class BussinessDelegate
{
public:
    BussinessDelegate();
    void calibrate();

    void toolEllipseTargetRefiner();

protected:
    QtUIFactory _factory;
};

#endif // BUSSINESSDELEGATE_H
