#pragma once

#include "etl/vector.h"
#include "protocols/datalink/FTPFrame.h"
#include "protocols/datalink/COBS.h"
#include "buffer/BufferInterface.h"

namespace Comms2
{
    class Encoder
    {
    public:
        Encoder(OutputBufferInterface* outputBuffer): _outputBuffer(outputBuffer) {};
        
        static Comms2::Error encode(FTPFrame& frame, etl::ivector<uint8_t>& out);
        Comms2::Error encodeToBuf(FTPFrame& frame);
    private:
        OutputBufferInterface* _outputBuffer;
    };
}