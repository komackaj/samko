#include "common.h"
#include <libsamko/serialization/jsonwriter.h>
#include <libsamko/serialization/jsonreader.h>

using namespace std;
using namespace samko;
using ::testing::StrictMock;
using ::testing::Return;

/* HELPERS */

std::pair<string, MockSerializable::Data> getTestData() {
    MockSerializable::Data data1 = {"jsontest", 15, 7.5, 1500.1f};

    const string expected1 = "{ \
        \"simple\": { \
            \"string\": \"jsontest\", \
            \"int\": 15, \
            \"float\": 1500.0999755859375, \
            \"dbl\": 7.5 \
        } \
    }";

    return make_pair(expected1, data1);
}

string normalizeJson(const string& data) {
    string ret(data);
    ret.erase( std::remove_if( ret.begin(), ret.end(), ::isspace), ret.end() );
    return ret;
}

void jsonStringEquals(const string& data, const string& expected) {
    EXPECT_EQ(normalizeJson(expected), normalizeJson(data));
}

/* TESTS */
TEST(JsonTest, SimpleWrite) {
    auto testData = getTestData();
    StrictMock<MockSerializable> mock;
    EXPECT_CALL(mock, defineData())
        .WillOnce(Return(testData.second));

    JsonWriter writer;
    writer.write("simple", mock);
    jsonStringEquals(writer.data(), testData.first);
}

TEST(JsonTest, SimpleRead) {
    auto testData = getTestData();
    JsonReader reader;
    StrictMock<MockSerializable> mock;

    reader.parse(testData.first);
    reader.readObject("simple", mock);
    dataEquals(testData.second, mock.getReadData());
}