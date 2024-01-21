#pragma once

namespace Comms2
{
    enum class Error
    {
        OK = 0,
        PROTOCOL_FRAME_ERROR,
        PROTOCOL_FRAME_CRC_ERROR,
        PROTOCOL_DATA_ERROR,
        BUFFER_ERROR,
        NOT_ENOUGH_DATA,
        INVALID_ARGUMENT,
        INTERNAL_ERROR,
    };

    constexpr const char* ErrorStatusToString(Comms2::Error status)
    {
        switch (status)
        {
            case Comms2::Error::OK:
                return "OK";
            case Comms2::Error::PROTOCOL_FRAME_ERROR:
                return "PROTOCOL_FRAME_ERROR";
            case Comms2::Error::PROTOCOL_FRAME_CRC_ERROR:
                return "PROTOCOL_FRAME_CRC_ERROR";
            case Comms2::Error::PROTOCOL_DATA_ERROR:
                return "PROTOCOL_DATA_ERROR";
            case Comms2::Error::BUFFER_ERROR:
                return "BUFFER_ERROR";
            case Comms2::Error::NOT_ENOUGH_DATA:
                return "NOT_ENOUGH_DATA";
            case Comms2::Error::INVALID_ARGUMENT:
                return "INVALID_ARGUMENT";
            case Comms2::Error::INTERNAL_ERROR:
                return "INTERNAL_ERROR";
            default:
                return "UNKNOWN_ERROR";
        }
    }
}