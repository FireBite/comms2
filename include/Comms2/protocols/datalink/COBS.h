#pragma once

#include "etl/vector.h"
#include "Comms2/Error.h"
#include "Comms2/Comms2Config.h"

namespace Comms2
{
    class COBS
    {
    public:
        /*
            COBS encoding algorithm.
            \param data The data to encode frame to, must be at least 2 bytes longer than the data. 
            \returns OK if the frame is valid. Otherwise PROTOCOL_FRAME_ERROR on invalid frame or BUFFER_ERROR if the data buffer is too small or empty.
        */
        static Comms2::Error encode(etl::ivector<uint8_t>& data);

        /*
            COBS decoding algorithm.
            This is a more reinforced version of the original algorithm.
            \param data The data to decode, will be modified in-place.
            \returns OK if the frame is valid. Otherwise PROTOCOL_FRAME_ERROR on invalid frame or NOT_ENOUGH_DATA if the frame hasn't been fully received.
        */
        static Comms2::Error decode(etl::ivector<uint8_t>& data);

        /*
            COBS decoding algorithm.
            This is a more reinforced version of the original algorithm.
            \param data The data to decode, will be modified in-place.
            \param readBytes The number of bytes read from the data buffer.
            \returns OK if the frame is valid. Otherwise PROTOCOL_FRAME_ERROR on invalid frame or NOT_ENOUGH_DATA if the frame hasn't been fully received.
        */
        static Comms2::Error decode(etl::ivector<uint8_t>& data, size_t& readBytes);
    };
}