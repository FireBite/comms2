#include <gtest/gtest.h>

#include "Comms2/protocols/datalink/COBS.h"

using namespace Comms2;

TEST(COBSTests, ShouldEncodeFrame) {
    etl::vector<uint8_t, 255> data     = {0x00};
    etl::vector<uint8_t, 255> expected = {0x01, 0x01, 0x00};

    EXPECT_EQ(COBS::encode(data), Comms2::Error::OK);
    EXPECT_EQ(data, expected);

    data = {0x00, 0x00};
    expected = {0x01, 0x01, 0x01, 0x00};

    EXPECT_EQ(COBS::encode(data), Comms2::Error::OK);
    EXPECT_EQ(data, expected);

    data = {0x11, 0x22, 0x00, 0x33};
    expected = {0x03, 0x11, 0x22, 0x02, 0x33, 0x00};

    EXPECT_EQ(COBS::encode(data), Comms2::Error::OK);
    EXPECT_EQ(data, expected);
}

TEST(COBSTests, ShouldDecodeFrame) {
    etl::vector<uint8_t, 255> data     = {0x01, 0x01, 0x00};
    etl::vector<uint8_t, 255> expected = {0x00};

    size_t readBytes = 0;
    EXPECT_EQ(COBS::decode(data, readBytes), Comms2::Error::OK);
    EXPECT_EQ(data, expected);
    EXPECT_EQ(readBytes, 3);

    data = {0x01, 0x01, 0x01, 0x00};
    expected = {0x00, 0x00};

    readBytes = 0;
    EXPECT_EQ(COBS::decode(data, readBytes), Comms2::Error::OK);
    EXPECT_EQ(data, expected);
    EXPECT_EQ(readBytes, 4);

    data = {0x03, 0x11, 0x22, 0x02, 0x33, 0x00};
    expected = {0x11, 0x22, 0x00, 0x33};

    readBytes = 0;
    EXPECT_EQ(COBS::decode(data, readBytes), Comms2::Error::OK);
    EXPECT_EQ(data, expected);
    EXPECT_EQ(readBytes, 6);
}

TEST(COBSTests, ShouldFailDecodeFrame) {
    etl::vector<uint8_t, 255> data     = {0x01, 0x01, 0x01};
    etl::vector<uint8_t, 255> expected = {0x00};

    size_t readBytes = 0;
    EXPECT_EQ(COBS::decode(data, readBytes), Comms2::Error::NOT_ENOUGH_DATA);
    EXPECT_EQ(data, expected);
}
