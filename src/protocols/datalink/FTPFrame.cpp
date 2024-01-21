#include "Comms2/protocols/datalink/FTPFrame.h"
#include "etl/crc.h"
#include "etl/vector.h"
#include <algorithm>

namespace Comms2
{
    void FTPFrame::_serializeHeader(etl::ivector<uint8_t>& out) const
    {
        // Serialize the frame header
        out.push_back(header.destinationNode.address << 5 | header.destinationNode.port);
        out.push_back(header.sourceNode.address << 5 | header.sourceNode.port);
        out.push_back(static_cast<uint8_t>(header.deliveryType));
        out.push_back(header.protocolId);
        out.push_back(header.payloadLength);
    }

    Comms2::Error FTPFrame::serialize(etl::ivector<uint8_t>& out)
    {
        // Populate frame's CRC field
        calculateCRC(true);

        // As the CRC has beed recalculated, only the frame header needs to be validated
        if(!isFrameHeaderValid())
            return Comms2::Error::PROTOCOL_FRAME_ERROR;

        // Prepare and validate output buffer size
        if (out.max_size() < Comms2::FRAME_MTU)
            return Comms2::Error::BUFFER_ERROR;

        out.clear();

        // Serialize the frame header
        _serializeHeader(out);

        // Serialize the frame payload if it exists
        if (header.payloadLength > 0)
        {
            out.insert(out.end(), payload.begin(), payload.begin() + header.payloadLength);
        }

        // Serialize the frame CRC
        out.push_back(crc >> 8);
        out.push_back(crc & 0xFF);

        return Comms2::Error::OK;
    }

    Comms2::Error FTPFrame::deserialize(etl::ivector<uint8_t>& in)
    {
        // Check if the frame is valid
        if (in.size() < sizeof(FTPFrame::Header) + sizeof(uint16_t))
            return Comms2::Error::PROTOCOL_FRAME_ERROR;

        // Deserialize the frame header
        header.destinationNode.address = in[0] >> 5;
        header.destinationNode.port    = in[0] & 0x1F;
        header.sourceNode.address      = in[1] >> 5;
        header.sourceNode.port         = in[1] & 0x1F;
        header.deliveryType            = static_cast<FTPFrameDeliveryType>(in[2]);
        header.protocolId              = in[3];
        header.payloadLength           = in[4];
        
        // Deserialize the frame payload if it exists
        if (header.payloadLength > 0)
        {
            if (in.size() < sizeof(FTPFrame::Header) + header.payloadLength + sizeof(uint16_t))
                return Comms2::Error::PROTOCOL_FRAME_ERROR;

            payload.assign(in.begin() + sizeof(FTPFrame::Header), in.begin() + sizeof(FTPFrame::Header) + header.payloadLength);
        }

        // Validate CRC
        crc = in[sizeof(FTPFrame::Header) + header.payloadLength] << 8 | in[sizeof(FTPFrame::Header) + header.payloadLength + 1];
        
        if(!isCRCValid())
            return Comms2::Error::PROTOCOL_FRAME_CRC_ERROR;

        return Comms2::Error::OK;
    }

    uint16_t FTPFrame::calculateCRC(bool setFrameCRC)
    {
        auto crc = etl::crc16();

        // Serialize the frame header
        etl::vector<uint8_t, sizeof(FTPFrame::Header)> serializedHeader;
        _serializeHeader(serializedHeader);

        // Calculate the CRC of the header and payload
        crc.add(serializedHeader.begin(), serializedHeader.end());
        crc.add(payload.begin(), payload.begin() + header.payloadLength);

        if (setFrameCRC)
            this->crc = crc.value();
        return crc.value();
    }

    bool FTPFrame::isCRCValid()
    {
        return calculateCRC() == crc;
    }

    bool FTPFrame::isFrameHeaderValid() const
    {
        return header.payloadLength <= MAX_PAYLOAD_SIZE;
    }

    bool FTPFrame::isFrameValid()
    {
        return isFrameHeaderValid() && isCRCValid();
    }
}