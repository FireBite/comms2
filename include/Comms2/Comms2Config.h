#pragma once

#include <cstddef>

namespace Comms2
{
    // Compile time configuration options for the Comms2 library
    constexpr const size_t FRAME_MTU = 255;
    constexpr const size_t MAX_PROTOCOLS_COUNT = 8;
    constexpr const size_t FRAME_SEPARATOR_CHAR = 0;
}
