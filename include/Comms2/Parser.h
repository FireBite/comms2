#pragma once

#include "etl/vector.h"
#include "protocols/datalink/FTPFrame.h"
#include "protocols/datalink/COBS.h"
#include "buffer/BufferInterface.h"

namespace Comms2
{
    class Parser
    {
    public:        
        Parser(InputBufferInterface* inputBuffer): _inputBuffer(inputBuffer) {};

        static Comms2::Error parse(FTPFrame& outFrame, etl::ivector<uint8_t>& in);
        Comms2::Error parseFromBuf(FTPFrame& frame);
    private:
        InputBufferInterface* _inputBuffer;
        etl::vector<uint8_t, 2 * Comms2::FRAME_MTU> _decodeBuffer;
    };
}