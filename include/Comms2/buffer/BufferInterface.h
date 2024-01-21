#pragma once

#include "stdint.h"
#include "etl/vector.h"
#include "etl/array_view.h"

#include "../Comms2Config.h"
#include "../Error.h"

namespace Comms2
{
    class InputBufferInterface
    {
    public:
        virtual bool hasNewData() = 0;
        virtual uint8_t read() = 0;
    };

    class OutputBufferInterface
    {
    public:
        virtual Comms2::Error append(etl::array_view<uint8_t> data) = 0;
    };
}
