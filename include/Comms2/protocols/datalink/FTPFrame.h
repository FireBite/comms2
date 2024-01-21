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
        // TODO: More constructors
        uint16_t calculateCRC(bool setFrameCRC = false);
        bool isCRCValid();
        bool isFrameHeaderValid() const;
        bool isFrameValid();
        Comms2::Error serialize(etl::ivector<uint8_t>& out);
        Comms2::Error deserialize(etl::ivector<uint8_t>& in);

    private:
        void _serializeHeader(etl::ivector<uint8_t>& out) const;
    };
}
