#ifndef BUSSINESSDELEGATE_H
#define BUSSINESSDELEGATE_H

#include "qtuifactory.h"

class BussinessDelegate
{
public:
    BussinessDelegate();
    void calibrate();

protected:
    QtUIFactory _factory;
};

#endif // BUSSINESSDELEGATE_H
