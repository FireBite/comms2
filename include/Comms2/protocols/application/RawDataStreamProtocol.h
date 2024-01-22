#pragma once

#include "Protocol.h"
#include "etl/array.h"

namespace Comms2
{
    class RawDataStreamProtocol: public Protocol
    {
    public:
        uint8_t length;
        etl::array<uint8_t, FTPFrame::MAX_PAYLOAD_SIZE> data;
        
        Error parse(FTPFrame& frame);
        Error encode(FTPFrame& frame);
    };

} 