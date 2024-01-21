#include "Comms2/Encoder.h"

namespace Comms2
{
    Comms2::Error Encoder::encode(FTPFrame& frame, etl::ivector<uint8_t>& out)
    {
        // Serialize frame
        Comms2::Error res = frame.serialize(out);

        if (res != Comms2::Error::OK)
            return res;

        // Encode with COBS
        return COBS::encode(out);
    }

    Comms2::Error Encoder::encodeToBuf(FTPFrame& frame)
    {
        etl::vector<uint8_t, 2 * Comms2::FRAME_MTU> datagram;

        // Serialize frame
        Comms2::Error res = frame.serialize(datagram);

        if (res != Comms2::Error::OK)
            return res;

        // Encode with COBS
        res = COBS::encode(datagram);

        if (res != Comms2::Error::OK)
            return res;

        // Write to output buffer
        return _outputBuffer->append(datagram);
    }
}