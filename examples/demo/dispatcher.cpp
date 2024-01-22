#include <iostream>

#include "Comms2/protocols/datalink/FTPFrame.h"
#include "Comms2/ProtocolDispatcher.h"

using namespace Comms2;

using std::cout, std::cin, std::endl;

int main()
{
    ProtocolDispatcher dispatcher;

    // Register catch-all handler
    dispatcher.registerCatchAllHandler([](FTPFrame& frame) -> Comms2::Error {
        std::cout << "Catch-all handler" << std::endl;

        std::cout << "Payload: ";
        for (int i = 0; i < frame.header.payloadLength; i++)
        {
            std::cout << std::hex << frame.payload[i];
        }

        cout << endl << endl;

        return Comms2::Error::OK;
    });

    // Prepare frame
    FTPFrame frame = FTPFrame();
    frame.header =
    {
        .destinationNode = {1, 2},
        .sourceNode = {3, 4},
        .deliveryType = FTPFrameDeliveryType::ACK_NORMAL,
        .protocolId = 1,
        .payloadLength = 6
    };

    frame.payload[0] = 'i';
    frame.payload[1] = 'd';
    frame.payload[2] = ':';
    frame.payload[3] = ' ';
    frame.payload[4] = '1';
    frame.payload[5] = '\0';

    // Send frame
    cout << "Sending frame..." << endl;
    dispatcher.dispatchFrame(frame);

    // Register protocol handler
    dispatcher.registerProtocol(1, [](FTPFrame& frame) -> Comms2::Error {
        std::cout << "Protocol 1 handler" << std::endl;

        std::cout << "Payload: ";
        for (int i = 0; i < frame.header.payloadLength; i++)
        {
            std::cout << std::hex << frame.payload[i];
        }

        cout << endl << endl;

        return Comms2::Error::OK;
    });

    // Send frame, this time it should be handled by the protocol handler
    cout << "Sending frame..." << endl;
    dispatcher.dispatchFrame(frame);

    return 0;
}