#include "qtuifactory.h"
#include "forms/calib2ddialog.h"

using namespace samko;

QtUIFactory::QtUIFactory()
{
}

UIFactory::UIGridDetectorPtr QtUIFactory::getGridDetector() const
{
    return UIGridDetectorPtr(new Calib2DDialog());
}
