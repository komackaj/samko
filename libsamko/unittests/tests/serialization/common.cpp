#include "common.h"

using namespace std;

template<typename T>
void vectorsEqual(const vector<T>& v1, const vector<T>& v2)
{
    ASSERT_EQ(v1.size(), v2.size());
    auto aktIt1 = begin(v1),
         aktIt2 = begin(v2),
         endIt1 = end(v1);
    for ( ;aktIt1!=endIt1; ++aktIt1, ++aktIt2)
        EXPECT_EQ(*aktIt1, *aktIt2);
}

void dataEquals(MockSerializable::Data expected, MockSerializable::Data actual) {
    EXPECT_EQ(expected.str, actual.str);
    EXPECT_EQ(expected.i, actual.i);
    EXPECT_DOUBLE_EQ(expected.d, actual.d);
    EXPECT_FLOAT_EQ(expected.d, actual.d);
    vectorsEqual<string>(expected.vecStr, actual.vecStr);
    vectorsEqual<int>(expected.vecInt, actual.vecInt);
    vectorsEqual<double>(expected.vecDbl, actual.vecDbl);
}
