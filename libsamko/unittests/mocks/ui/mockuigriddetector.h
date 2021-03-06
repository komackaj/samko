#ifndef MOCKUIGRIDDETECTOR_H_INCLUDED
#define MOCKUIGRIDDETECTOR_H_INCLUDED

#include <gmock/gmock.h>
#include <libsamko/ui/uigriddetector.h>

class MockUIGridDetector : public samko::UIGridDetector {

public:

  MOCK_METHOD1(getCornersFromUser, std::vector<cv::Point2f> (const cv::Mat&));

};

#endif // MOCKUIGRIDDETECTOR_H_INCLUDED
