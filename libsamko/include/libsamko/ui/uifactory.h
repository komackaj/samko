#ifndef UIFACTORY_H_INCLUDED
#define UIFACTORY_H_INCLUDED

#include <memory>

namespace samko {

class UIGridDetector;

/// Abstract class for accessing UI components. Factory pattern.
class UIFactory {

public:
    typedef std::unique_ptr<UIGridDetector> UIGridDetectorPtr;

    virtual ~UIFactory() {}

    virtual UIGridDetectorPtr getGridDetector() const = 0;
};

} //namespace samko

#endif // UIFACTORY_H_INCLUDED
