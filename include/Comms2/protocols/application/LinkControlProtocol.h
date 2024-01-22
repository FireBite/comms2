#pragma once

#include "Protocol.h"

namespace Comms2
{
    enum class LinkControlProtocolType: uint8_t
    {
        GET = 0x01,
        SET = 0x02,
        ACK = 0x03,
        NACK = 0x04,
    };

    class LinkControlProtocol: public Protocol
    {
    public:
        struct Header
        {
            LinkControlProtocolType type;
            uint8_t command;
            uint8_t length;
        };

        Header header;
        etl::array<uint8_t, FTPFrame::MAX_PAYLOAD_SIZE> data;
        
        Error parse(FTPFrame& frame);
        Error encode(FTPFrame& frame);
    };

} 