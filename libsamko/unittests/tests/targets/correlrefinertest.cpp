#include "targetrefinercommontest.h"
#include <libsamko/targets/correlrefiner.h>

TEST(CorrelRefinerTest, PreciseCircle) {
    constexpr size_t RADIUS = 10;
    CorrelRefiner refiner(2 * RADIUS * 1.2);
    preciseCircleTest(refiner, RADIUS);
}

TEST(CorrelRefinerTest, staticTargetTest) {
    constexpr size_t RADIUS = 5;
    CorrelRefiner refiner(RADIUS);
    staticTargetTest(refiner);
}
