#include "Comms2/protocols/datalink/COBS.h"

namespace Comms2
{
    /*
        COBS encoding algorithm.
        \param data The data to encode frame to, must be at least 2 bytes longer than the data. 
        \returns OK if the frame is valid. Otherwise PROTOCOL_FRAME_ERROR on invalid frame or BUFFER_ERROR if the data buffer is too small or empty.
    */
    Comms2::Error COBS::encode(etl::ivector<uint8_t>& data)
    {
        // Check if the data is valid
        if (data.empty() || data.size() > 255)
            return Comms2::Error::INVALID_ARGUMENT;

        // Check if we have enough space to encode the data
        if (data.size() > data.max_size() - 2)
            return Comms2::Error::BUFFER_ERROR;

        // Encode data
        data.insert(data.begin(), 0); // Insert offset to the next frame separator
        data.push_back(Comms2::FRAME_SEPARATOR_CHAR); // Insert frame separator after the data

        uint8_t distance = 0;
        size_t pos = 0;

        for (size_t i = 1; i < data.size(); i++)
        {
            if (data[i] == Comms2::FRAME_SEPARATOR_CHAR)
            {
                data[pos] = distance + 1;
                pos = i;
                distance = 0;
            }
            else
            {
                distance++;
            }
        }

        return Comms2::Error::OK;
    }


    /*
        COBS decoding algorithm.
        This is a more reinforced version of the original algorithm.
        \param data The data to decode, will be modified in-place.
        \param readBytes The number of bytes read from the data buffer.
        \returns OK if the frame is valid. Otherwise PROTOCOL_FRAME_ERROR on invalid frame or NOT_ENOUGH_DATA if the frame hasn't been fully received.
    */
    Comms2::Error COBS::decode(etl::ivector<uint8_t>& data, size_t& readBytes)
    {
        // Check if we have enough data to decode
        // Offset to next frame separator + 1 data byte + frame separator
        if (data.size() < 3)
            return Comms2::Error::PROTOCOL_FRAME_ERROR;

        // Frame separator should be at the end of the frame, after its' data
        if (data[0] == FRAME_SEPARATOR_CHAR)
            return Comms2::Error::PROTOCOL_FRAME_ERROR;

        // Decode data
        uint8_t distance = data[0] - 1;
        size_t pos = 1;

        while(pos < data.size())
        {
            if (data[pos] == Comms2::FRAME_SEPARATOR_CHAR)
                break;

            if (distance == 0)
            {
                distance = data[pos];
                data[pos] = Comms2::FRAME_SEPARATOR_CHAR;
            }

            pos++;
            distance--;
        }

        readBytes = pos;

        // Remove additional bytes added by the encoding
        data.erase(data.begin()); // Remove first offset to the next frame separator
        data.pop_back();          // Remove frame separator after the data

        // If the frame is valid, the last byte should be the frame separator
        if (data[pos] == Comms2::FRAME_SEPARATOR_CHAR && distance == 0)
            return Comms2::Error::OK;

        // Wait for more data as the received frame hasn't been fully received
        if (data[pos] != Comms2::FRAME_SEPARATOR_CHAR)
            return Comms2::Error::NOT_ENOUGH_DATA;

        // The frame is invalid as the distance is not 0 by the time end of the frame is reached
        return Comms2::Error::PROTOCOL_FRAME_ERROR;
    }

    /*
        COBS decoding algorithm.
        This is a more reinforced version of the original algorithm.
        \param data The data to decode, will be modified in-place.
        \returns OK if the frame is valid. Otherwise PROTOCOL_FRAME_ERROR on invalid frame or NOT_ENOUGH_DATA if the frame hasn't been fully received.
    */
    Comms2::Error COBS::decode(etl::ivector<uint8_t>& data)
    {
        size_t readBytes;
        return decode(data, readBytes);
    }
}