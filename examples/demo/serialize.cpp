#include <iostream>

#include "Comms2/Encoder.h"
#include "Comms2/Parser.h"

using std::cout, std::cin, std::endl;

using namespace Comms2;

int main() {
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

    Error res = Encoder::encode(frame, out);

    if (res != Error::OK)
    {
        cout << "Error encoding frame: " << ErrorStatusToString(res) << endl;
        return 1;
    }

    cout << "Encoded frame: ";
    for (auto& byte : out)
    {
        cout << std::hex << (int)byte << " ";
    }
    cout << endl;

    // Decode frame
    FTPFrame decodedFrame = FTPFrame();

    res = Parser::parse(decodedFrame, out);

    if (res != Error::OK)
    {
        cout << "Error decoding frame: " << ErrorStatusToString(res) << endl;
        return 1;
    }

    // Compare frames
    cout << "Received frame header is " << (decodedFrame.isFrameHeaderValid() ? "valid" : "invalid") << endl;
    cout << "Received frame CRC is " << (decodedFrame.isCRCValid() ? "valid" : "invalid") << endl;

    // Print received frame fields
    cout << "Received frame header:" << endl;
    cout << "    Destination node: " << (int)decodedFrame.header.destinationNode.address << ":" << (int)decodedFrame.header.destinationNode.port << endl;
    cout << "    Source node: " << (int)decodedFrame.header.sourceNode.address << ":" << (int)decodedFrame.header.sourceNode.port << endl;
    cout << "    Delivery type: " << (int)decodedFrame.header.deliveryType << endl;
    cout << "    Protocol ID: " << (int)decodedFrame.header.protocolId << endl;
    cout << "    Payload length: " << (int)decodedFrame.header.payloadLength << endl;
    cout << "    CRC: " << (int)decodedFrame.crc << endl;

    cout << "Received frame payload: " << decodedFrame.payload.data() << endl;

    return 0;
}