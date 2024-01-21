#pragma once

#include "BufferInterface.h"
#include "etl/array.h"
#include "etl/iterator.h"

namespace Comms2 
{
    template <size_t SIZE>
    class LinearBuffer: public InputBufferInterface, public OutputBufferInterface
    {
    private:
        etl::array<uint8_t, SIZE> _buffer;
        etl::array<uint8_t, SIZE>::iterator _readIterator;
        etl::array<uint8_t, SIZE>::iterator _writeIterator;
    public:
        LinearBuffer()
        {
            _readIterator = _buffer.begin();
            _writeIterator = _buffer.begin();
        }

        Comms2::Error append(etl::array_view<uint8_t> data)
        {
            // Check if the buffer can accept new data
            if (_writeIterator + data.size() > _buffer.end()) {
                return Comms2::Error::BUFFER_ERROR;
            }

            // Copy the data to the buffer
            _buffer.insert(_writeIterator, data.begin(), data.end());
            _writeIterator += data.size();
            
            return Comms2::Error::OK;
        }

        bool hasNewData()
        {
            return _readIterator != _writeIterator;
        }

        uint8_t read()
        {
            uint8_t data = *_readIterator++;

            // All data has been read, reset the buffer
            if (_readIterator == _writeIterator) {
                _buffer.erase_range(0, _buffer.size() - 1);
                _readIterator = _buffer.begin();
                _writeIterator = _buffer.begin();
            }
            return data;
        }
    };
}
