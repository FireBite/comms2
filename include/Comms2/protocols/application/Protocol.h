#pragma once

#include "../datalink/FTPFrame.h"
namespace Comms2
{    
    class Protocol {
    public:
        virtual Error parse(FTPFrame& frame) = 0;
        virtual Error encode(FTPFrame& frame) = 0;
    };
}