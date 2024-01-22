#pragma once

#include <stdint.h>

#include "etl/array.h"
#include "etl/vector.h"
#include "Comms2/Error.h"
#include "../../Comms2Config.h"

namespace Comms2 {
    typedef struct {
        uint8_t address: 3;
        uint8_t port:    5;
    } NodeAddress;

    enum class FTPFrameDeliveryType: uint8_t {
        NOT_GUARANTEED = 0,
        ACK_NORMAL = 1,
        ACK_URGENT = 2,
    };

    class FTPFrame {
    public:
        struct Header {
            NodeAddress destinationNode = {.address = 0, .port = 0};
            NodeAddress sourceNode = {.address = 0, .port = 0};
            FTPFrameDeliveryType deliveryType = FTPFrameDeliveryType::NOT_GUARANTEED;
            uint8_t protocolId = 0;
            uint8_t payloadLength = 0;
        };

        Header header;        
        
        static constexpr const size_t MAX_PAYLOAD_SIZE = Comms2::FRAME_MTU - sizeof(Header) - sizeof(uint16_t);
        etl::array<uint8_t, MAX_PAYLOAD_SIZE> payload;
        uint16_t crc = 0;

        FTPFrame() {};
        
        /*
            Calculate the CRC of the frame
            \param setFrameCRC should the calculated CRC be set as the frame's CRC
            \return CRC
        */
        uint16_t calculateCRC(bool setFrameCRC = false);

        /*
            Check if the CRC of the frame is valid
            \return boolean indicating if the CRC is valid
        */
        bool isCRCValid();

        /*
            Check if the frame header is valid
            \return boolean indicating if the frame header is valid
        */
        bool isFrameHeaderValid() const;

        /*
            Check if the frame header and CRC is valid
            \return boolean indicating if the frame is valid
        */
        bool isFrameValid();

        /*
            Serialize the frame
            \param out The data to serialize the frame to
            \return OK if the frame is valid. Otherwise PROTOCOL_FRAME_ERROR on invalid frame or BUFFER_ERROR if the output buffer is too small.
        */
        Comms2::Error serialize(etl::ivector<uint8_t>& out);

        /*
            Deserialize the frame
            \param in The data to deserialize the frame from
            \return OK if the frame is valid. Otherwise PROTOCOL_FRAME_ERROR on invalid frame or PROTOCOL_FRAME_CRC_ERROR if the CRC is invalid.
        */
        Comms2::Error deserialize(etl::ivector<uint8_t>& in);

    private:
        void _serializeHeader(etl::ivector<uint8_t>& out) const;
    };
}
