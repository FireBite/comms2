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
        
        /*
            Encode a frame and write it to the provided output buffer
            \param frame Frame to encode
            \param out Output buffer to write the encoded frame to
            \returns OK if the frame was encoded successfully. Otherwise BUFFER_ERROR if the output buffer is too small.
        */
        static Comms2::Error encode(FTPFrame& frame, etl::ivector<uint8_t>& out);

        /*
            Encode a frame and write it to the Encoder's output buffer
            \param frame Frame to encode
            \returns OK if the frame was encoded successfully. Otherwise BUFFER_ERROR if the output buffer is too small.
        */
        Comms2::Error encodeToBuf(FTPFrame& frame);
    private:
        OutputBufferInterface* _outputBuffer;
    };
}