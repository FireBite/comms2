#pragma once

#include "Protocol.h"

namespace Comms2
{
    enum class KalmanBinaryProtocolCmd: uint8_t
    {
        SetWheelSpeed = 0x01,
        SetWheelPosition = 0x02,
        GetWheelSpeed = 0x03,
        GetWheelPosition = 0x04,
        SetArmJointPosition = 0x05,
    };

    class KalmanBinaryProtocol: public Protocol
    {
    public:
        struct Header
        {
            KalmanBinaryProtocolCmd command;
            uint8_t length;
        };

        Header header;
        etl::array<uint8_t, FTPFrame::MAX_PAYLOAD_SIZE> data;
        
        Error parse(FTPFrame& frame);
        Error encode(FTPFrame& frame);
    };

} 