#include <iostream>

#include "Comms2/Parser.h"
#include "Comms2/Encoder.h"

using std::cout, std::cin, std::endl;
using namespace Comms2;

void printFrame(FTPFrame& frame)
{
    cout << "Frame:" << endl;
    cout << "  Destination node: " << frame.header.destinationNode.address << ":" << frame.header.destinationNode.port << endl;
    cout << "  Source node: " << frame.header.sourceNode.address << ":" << frame.header.sourceNode.port << endl;
    cout << "  Delivery type: " << (int)frame.header.deliveryType << endl;
    cout << "  Protocol ID: " << (int)frame.header.protocolId << endl;
    cout << "  Payload length: " << (int)frame.header.payloadLength << endl;
    cout << "  Payload: ";
    for (int i = 0; i < frame.header.payloadLength; i++)
    {
        cout << frame.payload[i];
    }
    cout << endl;
}

void printHelp()
{
    cout << "Commands:" << endl;
    cout << "  parse <frame>" << endl;
    cout << "  encode <id> <payload>" << endl;
    cout << "  help" << endl;
    cout << "  exit" << endl;
}

void parseFrame(std::string frame)
{
    etl::vector<uint8_t, FRAME_MTU> out;
    for (size_t i = 0; i < frame.length(); i += 2)
    {
        std::string byteString = frame.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoi(byteString, nullptr, 16));
        out.push_back(byte);
    }

    FTPFrame decodedFrame = FTPFrame();

    if (Parser::parse(decodedFrame, out) == Error::OK)
    {
        printFrame(decodedFrame);
    }
    else
    {
        cout << "Failed to parse frame" << endl;
    }
}

void encodeFrame(std::string id, std::string payload)
{
    FTPFrame frame = FTPFrame();
    frame.header =
    {
        .destinationNode = {1, 2},
        .sourceNode = {3, 4},
        .deliveryType = FTPFrameDeliveryType::ACK_NORMAL,
        .protocolId = static_cast<uint8_t>(std::stoi(id)),
        .payloadLength = static_cast<uint8_t>(payload.length())
    };

    for (size_t i = 0; i < payload.length(); i++)
    {
        frame.payload[i] = payload[i];
    }

    frame.calculateCRC(true);

    etl::vector<uint8_t, FRAME_MTU> out;
    if (Encoder::encode(frame, out) == Error::OK)
    {
        cout << "Encoded frame: ";
        for (size_t i = 0; i < out.size(); i++)
        {
            cout << std::hex << (int)out[i];
        }
        cout << endl;
    }
    else
    {
        cout << "Failed to encode frame" << endl;
    }
}

int main()
{
    cout << "Comms2 demo" << endl;
    cout << "Type 'help' for help" << endl;

    while (true)
    {
        std::string command;
        cout << "> ";

        cin >> command;

        if (command == "parse")
        {
            std::string frame;
            cin >> frame;

            parseFrame(frame);
        }
        else if (command == "encode")
        {
            std::string id;
            std::string payload;

            cin >> id;
            cin >> payload;

            encodeFrame(id, payload);
        }
        else if (command == "help")
        {
            printHelp();
        }
        else if (command == "exit")
        {
            break;
        }
        else
        {
            cout << "Unknown command" << endl;
        }
    }

    return 0;
}