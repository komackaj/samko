#ifndef QTUIFACTORY_H
#define QTUIFACTORY_H

#include <QWidget>
#include <libsamko/ui/uifactory.h>

class QtUIFactory : public samko::UIFactory
{
public:
    QtUIFactory();

    virtual UIGridDetectorPtr getGridDetector() const;
};

#endif // QTUIFACTORY_H
