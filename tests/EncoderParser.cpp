#include <gtest/gtest.h>

#include "Comms2/Encoder.h"
#include "Comms2/Parser.h"

using namespace Comms2;

TEST(EncoderParserTests, ShouldExchangeFrame) {

    // Prepare frame to be sent
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

    // Encode frame
    etl::vector<uint8_t, FRAME_MTU> out;

    EXPECT_EQ(Encoder::encode(frame, out), Error::OK);

    // Decode frame
    FTPFrame decodedFrame = FTPFrame();

    EXPECT_EQ(Parser::parse(decodedFrame, out), Error::OK);

    // Compare frames
    EXPECT_EQ(decodedFrame.isFrameHeaderValid(), true);
    EXPECT_EQ(decodedFrame.isCRCValid(), true);
    EXPECT_EQ(decodedFrame.header.destinationNode.address, frame.header.destinationNode.address);
    EXPECT_EQ(decodedFrame.header.destinationNode.port, frame.header.destinationNode.port);
    EXPECT_EQ(decodedFrame.header.sourceNode.address, frame.header.sourceNode.address);
    EXPECT_EQ(decodedFrame.header.sourceNode.port, frame.header.sourceNode.port);
    EXPECT_EQ(decodedFrame.header.deliveryType, frame.header.deliveryType);
    EXPECT_EQ(decodedFrame.header.protocolId, frame.header.protocolId);
    EXPECT_EQ(decodedFrame.header.payloadLength, frame.header.payloadLength);
}