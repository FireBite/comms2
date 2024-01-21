#pragma once

#include "stdint.h"
#include "etl/flat_map.h"
#include "etl/utility.h"
#include "etl/delegate.h"

#include "Comms2/protocols/application/Protocol.h"
#include "Comms2/Error.h"
#include "Comms2/protocols/datalink/FTPFrame.h"

namespace Comms2
{
    using ProtocolCallback = etl::delegate<Comms2::Error(FTPFrame&)>;

    class ProtocolEntry
    {
    public:
        Protocol* protocol;
        ProtocolCallback handler;
    };

    class ProtocolDispatcher
    {
    private:
        etl::flat_map<uint8_t, ProtocolEntry, 8> protocols;
        ProtocolCallback catchAllHandler;
    public:
        ProtocolDispatcher() {};
        Comms2::Error registerProtocol(Protocol& protocol, uint8_t protocolId, ProtocolCallback handler);
        Comms2::Error registerCatchAllHandler(ProtocolCallback handler);
        Comms2::Error dispatchFrame(FTPFrame& frame);
    };
}