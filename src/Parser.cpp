#include "Comms2/Parser.h"

namespace Comms2
{
    Comms2::Error Parser::parse(FTPFrame& outFrame, etl::ivector<uint8_t>& in)
    {
        // Decode COBS
        Comms2::Error res = COBS::decode(in);

        if (res != Comms2::Error::OK)
            return res;

        // Deserialize the frame header
        return outFrame.deserialize(in);
    }

    Comms2::Error Parser::parseFromBuf(FTPFrame& frame)
    {
        // Read new data from the input buffer
        while (!_inputBuffer->hasNewData()) 
            _decodeBuffer.push_back(_inputBuffer->read());

        etl::vector<uint8_t, 2 * Comms2::FRAME_MTU> datagram = _decodeBuffer;

        // Decode COBS
        Comms2::Error res = COBS::decode(datagram);

        switch (res)
        {
            case Comms2::Error::OK:
                break;
            // Discard buffer on invalid frame
            case Comms2::Error::PROTOCOL_FRAME_ERROR:
            default:
                _decodeBuffer.clear();
                return res;
            // Not enough data to decode, wait for more
            case Comms2::Error::NOT_ENOUGH_DATA:
                return res;
        }

        // Deserialize the frame header
        return frame.deserialize(datagram);
    }
}   
