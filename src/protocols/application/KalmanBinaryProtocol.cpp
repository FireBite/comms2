#include "Comms2/protocols/application/KalmanBinaryProtocol.h"

namespace Comms2
{
    Error KalmanBinaryProtocol::parse(FTPFrame& frame)
    {
        if (frame.payload.size() < 1)
        {
            return Error::PROTOCOL_DATA_ERROR;
        }

        header.command = static_cast<KalmanBinaryProtocolCmd>(frame.payload[0]);
        header.length = frame.header.payloadLength - 1;
        data.assign(frame.payload.begin() + 1, frame.payload.begin() + frame.header.payloadLength);

        return Error::OK;
    }

    Error KalmanBinaryProtocol::encode(FTPFrame& frame)
    {
        frame.header.protocolId = 1;
        frame.header.payloadLength = 1 + header.length;
        frame.payload[0] = static_cast<uint8_t>(header.command);
        frame.payload.assign(data.begin(), data.begin() + header.length);

        return Error::OK;
    }
}