#include "Comms2/protocols/application/LinkControlProtocol.h"

namespace Comms2
{
    Error LinkControlProtocol::parse(FTPFrame& frame)
    {
        if (frame.payload.size() < 1)
        {
            return Error::PROTOCOL_DATA_ERROR;
        }

        header.type = static_cast<LinkControlProtocolType>(frame.payload[0]);
        header.command = frame.payload[1];
        header.length = frame.header.payloadLength - 2;
        data.assign(frame.payload.begin() + 2, frame.payload.begin() + frame.header.payloadLength);

        return Error::OK;
    }

    Error LinkControlProtocol::encode(FTPFrame& frame)
    {
        frame.header.protocolId = 2;
        frame.header.payloadLength = 2 + header.length;;
        frame.payload[0] = static_cast<uint8_t>(header.command);
        frame.payload.assign(data.begin(), data.begin() + header.length);

        return Error::OK;
    }
}