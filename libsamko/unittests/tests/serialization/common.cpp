#include "common.h"

void dataEquals(MockSerializable::Data expected, MockSerializable::Data actual) {
    EXPECT_EQ(expected.str, actual.str);
    EXPECT_EQ(expected.i, actual.i);
    EXPECT_DOUBLE_EQ(expected.d, actual.d);
    EXPECT_FLOAT_EQ(expected.d, actual.d);
}
