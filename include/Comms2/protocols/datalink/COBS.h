#pragma once

#include "etl/vector.h"
#include "Comms2/Error.h"
#include "Comms2/Comms2Config.h"

namespace Comms2
{
    class COBS
    {
    public:
        static Comms2::Error encode(etl::ivector<uint8_t>& data);
        static Comms2::Error decode(etl::ivector<uint8_t>& data);
        static Comms2::Error decode(etl::ivector<uint8_t>& data, size_t& readBytes);
        static Comms2::Error decodeIterative(etl::ivector<uint8_t>& data);
    };
}