#include "Comms2/ProtocolDispatcher.h"

namespace Comms2
{
    Comms2::Error ProtocolDispatcher::registerProtocol(Protocol& protocol, uint8_t protocolId, ProtocolCallback handler)
    {
        // Check if the protocol can be registered
        if (!handler.is_valid())
            return Comms2::Error::INVALID_ARGUMENT;

        if (protocols.contains(protocolId))
            return Comms2::Error::INVALID_ARGUMENT;

        if (protocols.full())
            return Comms2::Error::INTERNAL_ERROR;

        // Register the protocol
        ProtocolEntry entry
        {
            .protocol = &protocol,
            .handler = handler
        };

        protocols.insert(etl::pair<uint8_t, ProtocolEntry>(protocolId, entry));
        return Comms2::Error::OK;
    }

    Comms2::Error ProtocolDispatcher::registerCatchAllHandler(ProtocolCallback handler)
    {
        if (!handler.is_valid())
            return Comms2::Error::INVALID_ARGUMENT;
        
        catchAllHandler = handler;
        return Comms2::Error::OK;
    }

    Comms2::Error ProtocolDispatcher::dispatchFrame(FTPFrame& frame)
    {
        // Find and execute corresponding protocol handler
        auto protocol = protocols.find(frame.header.protocolId);

        if (protocol != protocols.end())
        {
            return protocol->second.handler(frame);
        }

        // If no protocol handler was found, execute the catch-all handler
        return catchAllHandler(frame);
    }

}