/* THIS TEST MUST BE PASSED BY EVERY READER/WRITER COUPLE */

#include "common.h"
#include <libsamko/serialization/memstorage.h>
#include <libsamko/serialization/jsonwriter.h>
#include <libsamko/serialization/jsonreader.h>

using namespace samko;

using ::testing::StrictMock;
using ::testing::Return;

void TestReaderWriter(Reader& reader, Writer& writer) {
    MockSerializable::Data testData = {"samko", 27, 5.3};

    StrictMock<MockSerializable> storeMock, loadedMock;
    EXPECT_CALL(storeMock, defineData())
        .WillOnce(Return(testData));

    writer.write("testData", storeMock);
    std::string data = writer.data();
    reader.parse(data);
    reader.readObject("testData", loadedMock);
    dataEquals(testData, loadedMock.getReadData());
}

TEST(BaseSerializationTest, MemStorageReadWrite) {
    MemStorage storage;
    TestReaderWriter(storage, storage);
}

TEST(BaseSerializationTest, JsonReadWrite) {
    JsonReader reader;
    JsonWriter writer;
    TestReaderWriter(reader, writer);
}