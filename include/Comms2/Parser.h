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

        /*
            Parse a frame from the provided input buffer
            \param outFrame Frame to write the parsed frame to
            \param in Input buffer to read the frame from
            \returns OK if the frame was parsed successfully. Otherwise BUFFER_ERROR if the input buffer is too small.
        */
        static Comms2::Error parse(FTPFrame& outFrame, etl::ivector<uint8_t>& in);

        /*
            Parse a frame from the Parser's input buffer
            \param frame Frame to write the parsed frame to
            \returns OK if the frame was parsed successfully. Otherwise BUFFER_ERROR if the input buffer is too small.
        */
        Comms2::Error parseFromBuf(FTPFrame& frame);
    private:
        InputBufferInterface* _inputBuffer;
        etl::vector<uint8_t, 2 * Comms2::FRAME_MTU> _decodeBuffer;
    };
}