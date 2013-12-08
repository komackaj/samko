#include <gtest/gtest.h>
#include <libsamko/stringutils.h>

using namespace std;

TEST(StrUtilsTest, SimpleSplit) {
    string data = "Some text to split";
    auto tokens = split(data, " ");
    EXPECT_EQ(4, tokens.size());
    EXPECT_EQ("Some", tokens[0]);
    EXPECT_EQ("split", tokens[3]);
}

TEST(StrUtilsTest, TrimSplit) {
    string data = " Some text to split ";
    auto tokens = split(data, " ");
    EXPECT_EQ(4, tokens.size());
    EXPECT_EQ("Some", tokens[0]);
    EXPECT_EQ("split", tokens[3]);
}