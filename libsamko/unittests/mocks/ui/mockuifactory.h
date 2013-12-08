#ifndef MOCKUIFACTORY_H_INCLUDED
#define MOCKUIFACTORY_H_INCLUDED

#include <gmock/gmock.h>
#include <libsamko/ui/uifactory.h>
#include <libsamko/ui/uigriddetector.h>
#include "mockuigriddetector.h"

class MockUIFactory : public samko::UIFactory {
public:

    /// using proxy for mocking method returning non-copyable class
    virtual UIGridDetectorPtr getGridDetector() const {
        return UIGridDetectorPtr(getGridDetectorProxy());
    }

    MockUIGridDetector* mockDetector(unsigned int cols, unsigned int rows, std::vector<cv::Point2f> mockData) {
        ::testing::StrictMock<MockUIGridDetector> *detector = new ::testing::StrictMock<MockUIGridDetector>();

        EXPECT_CALL(*detector, getCornersFromUser(::testing::_))
            .WillOnce(::testing::Return(mockData));

        return detector;
    }

    MOCK_CONST_METHOD0(getGridDetectorProxy, samko::UIGridDetector*(void));
};

#endif // MOCKUIFACTORY_H_INCLUDED
