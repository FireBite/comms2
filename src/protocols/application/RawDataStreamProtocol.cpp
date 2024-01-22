#include "Comms2/protocols/application/RawDataStreamProtocol.h"

namespace Comms2
{
    Error RawDataStreamProtocol::parse(FTPFrame& frame)
    {
        if (frame.payload.size() < 1)
        {
            return Error::PROTOCOL_DATA_ERROR;
        }

        length = frame.header.payloadLength;
        data.assign(frame.payload.begin(), frame.payload.begin() + frame.header.payloadLength);

        return Error::OK;
    }

    Error RawDataStreamProtocol::encode(FTPFrame& frame)
    {
        frame.header.protocolId = 1;
        frame.header.payloadLength = length;
        frame.payload.assign(data.begin(), data.begin() + length);

        return Error::OK;
    }
}