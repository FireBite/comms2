#include <gtest/gtest.h>

#include "Comms2/protocols/datalink/FTPFrame.h"

using namespace Comms2;

// Demonstrate some basic assertions.
TEST(FTPFrameTests, ShouldValidateHeader) {
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

    EXPECT_EQ(frame.isFrameHeaderValid(), true);
}
