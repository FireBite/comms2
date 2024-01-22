#include <gtest/gtest.h>

#include "Comms2/protocols/datalink/FTPFrame.h"

using namespace Comms2;

TEST(FTPFrameTests, ShouldValidateHeader) {
    FTPFrame frame = FTPFrame();
    frame.header =
    {
        .destinationNode = {1, 2},
        .sourceNode = {3, 4},
        .deliveryType = FTPFrameDeliveryType::ACK_NORMAL,
        .protocolId = 5,
        .payloadLength = 6
    };

    frame.payload[0] = 'h';
    frame.payload[1] = 'e';
    frame.payload[2] = 'l';
    frame.payload[3] = 'l';
    frame.payload[4] = 'o';
    frame.payload[5] = '\0';

    EXPECT_EQ(frame.isFrameHeaderValid(), true);
}

TEST(FTPFrameTests, ShouldFailValidateHeader) {
    FTPFrame frame = FTPFrame();
    frame.header =
    {
        .destinationNode = {1, 2},
        .sourceNode = {3, 4},
        .deliveryType = FTPFrameDeliveryType::ACK_NORMAL,
        .protocolId = 5,
        .payloadLength = 255
    };

    EXPECT_EQ(frame.isFrameHeaderValid(), false);
}

TEST(FTPFrameTests, ShouldSerializeFrame) {
    FTPFrame frame = FTPFrame();
    frame.header =
    {
        .destinationNode = {1, 2},
        .sourceNode = {3, 4},
        .deliveryType = FTPFrameDeliveryType::ACK_NORMAL,
        .protocolId = 5,
        .payloadLength = 6
    };

    frame.payload[0] = 'h';
    frame.payload[1] = 'e';
    frame.payload[2] = 'l';
    frame.payload[3] = 'l';
    frame.payload[4] = 'o';
    frame.payload[5] = '\0';

    frame.calculateCRC(true);

    etl::vector<uint8_t, Comms2::FRAME_MTU> buffer;
    EXPECT_EQ(frame.serialize(buffer), Comms2::Error::OK);

    EXPECT_EQ(buffer.size(), 13);
    EXPECT_EQ(buffer[0], 0x22);
    EXPECT_EQ(buffer[1], 0x64);
    EXPECT_EQ(buffer[2], 0x01);
    EXPECT_EQ(buffer[3], 0x05);
    EXPECT_EQ(buffer[4], 0x06);
    EXPECT_EQ(buffer[5], 'h');
    EXPECT_EQ(buffer[6], 'e');
    EXPECT_EQ(buffer[7], 'l');
    EXPECT_EQ(buffer[8], 'l');
    EXPECT_EQ(buffer[9], 'o');
    EXPECT_EQ(buffer[10],  0);
    EXPECT_EQ(buffer[11], 0xE1);
}

TEST(FTPFrameTests, ShouldCalculateCRC) {
    FTPFrame frame = FTPFrame();
    frame.header =
    {
        .destinationNode = {1, 2},
        .sourceNode = {3, 4},
        .deliveryType = FTPFrameDeliveryType::ACK_NORMAL,
        .protocolId = 5,
        .payloadLength = 6
    };

    frame.payload[0] = 'h';
    frame.payload[1] = 'e';
    frame.payload[2] = 'l';
    frame.payload[3] = 'l';
    frame.payload[4] = 'o';
    frame.payload[5] = '\0';

    frame.calculateCRC(true);

    EXPECT_EQ(frame.crc, 57853);
}
