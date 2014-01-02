#include "targetrefinercommontest.h"
#include <libsamko/targets/ellipsetargetrefiner.h>

TEST(EllipseTargetRefinerTest, PreciseCircleTest) {
    constexpr int radius = 10;
    EllipseTargetRefiner refiner(radius * 1.2);
    preciseCircleTest(refiner, radius);
}

TEST(EllipseTargetRefinerTest, StaticTarget) {
    constexpr int radius = 10;
    EllipseTargetRefiner refiner(radius);
    staticTargetTest(refiner);
}
