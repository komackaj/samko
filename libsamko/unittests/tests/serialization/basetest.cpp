/* THIS TEST MUST BE PASSED BY EVERY READER/WRITER COUPLE */

#include <gtest/gtest.h>
#include <mocks/serialization/mockserializable.h>
#include <mocks/serialization/mockserializable.h>

#include <libsamko/serialization/memstorage.h>

using ::testing::StrictMock;
using ::testing::Return;

void TestReaderWriter(samko::Reader& reader, samko::Writer& writer) {
    MockSerializable::Data testData = {"samko", 27, 5.3, 2.12f};

    StrictMock<MockSerializable> storeMock, loadedMock;
    EXPECT_CALL(storeMock, defineData())
        .WillOnce(Return(testData));

    writer.writeObject("testData", storeMock);
    reader.readObject("testData", loadedMock);
    MockSerializable::Data endData = loadedMock.getReadData();

    EXPECT_EQ(testData.str, endData.str);
    EXPECT_EQ(testData.i, endData.i);
    EXPECT_DOUBLE_EQ(testData.d, endData.d);
    EXPECT_FLOAT_EQ(testData.d, endData.d);
}

TEST(MemStorageBaseTest, ReadWrite) {
    samko::MemStorage storage;
    TestReaderWriter(storage, storage);
}