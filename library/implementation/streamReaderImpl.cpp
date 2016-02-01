/*
$fileHeader$
*/

/*! \file streamReader.cpp
    \brief Implementation of the streamReader class.

*/

#include "streamReaderImpl.h"
#include <string.h>

namespace imebra
{

namespace implementation
{

///////////////////////////////////////////////////////////
//
// Constructor
//
///////////////////////////////////////////////////////////
streamReader::streamReader(std::shared_ptr<baseStreamInput> pControlledStream):
    streamController(0, 0),
    m_pControlledStream(pControlledStream),
    m_inBitsBuffer(0),
    m_inBitsNum(0)
{
}

streamReader::streamReader(std::shared_ptr<baseStreamInput> pControlledStream, size_t virtualStart, size_t virtualLength):
    streamController(virtualStart, virtualLength),
    m_pControlledStream(pControlledStream),
	m_inBitsBuffer(0),
	m_inBitsNum(0)
{
    if(virtualLength == 0)
    {
        throw(StreamEOFError("Virtual stream with zero length"));
    }
}


std::shared_ptr<baseStreamInput> streamReader::getControlledStream()
{
    return m_pControlledStream;
}

std::shared_ptr<streamReader> streamReader::getReader(size_t virtualLength)
{
    if(virtualLength == 0)
    {
        throw(StreamEOFError("Virtual stream with zero length"));
    }
    size_t currentPosition = position();
    if(currentPosition + virtualLength > m_virtualLength && m_virtualLength != 0)
    {
        virtualLength = m_virtualLength - currentPosition;
    }
    seekRelative((std::int32_t)virtualLength);
    return std::make_shared<streamReader>(m_pControlledStream, currentPosition + m_virtualStart, virtualLength);
}

///////////////////////////////////////////////////////////
//
// Returns true if the last byte has been read
//
///////////////////////////////////////////////////////////
bool streamReader::endReached()
{
    return (m_dataBufferCurrent == m_dataBufferEnd && fillDataBuffer() == 0);
}


///////////////////////////////////////////////////////////
//
// Refill the data buffer
//
///////////////////////////////////////////////////////////
size_t streamReader::fillDataBuffer()
{
    IMEBRA_FUNCTION_START();

    size_t readBytes = fillDataBuffer(&(m_dataBuffer[0]), m_dataBuffer.size());
	if(readBytes == 0)
	{
        m_dataBufferCurrent = m_dataBufferEnd = 0;
		return 0;
	}
    m_dataBufferEnd = readBytes;
    m_dataBufferCurrent = 0;
	return readBytes;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Read data from the stream into the specified buffer
//
///////////////////////////////////////////////////////////
size_t streamReader::fillDataBuffer(std::uint8_t* pDestinationBuffer, size_t readLength)
{
    m_dataBufferStreamPosition = position();
	if(m_virtualLength != 0)
	{
        if(m_dataBufferStreamPosition >= m_virtualLength)
		{
			m_dataBufferStreamPosition = m_virtualLength;
			return 0;
		}
        if(m_dataBufferStreamPosition + readLength > m_virtualLength)
		{
            readLength = m_virtualLength - m_dataBufferStreamPosition;
		}
	}
    return m_pControlledStream->read(m_dataBufferStreamPosition + m_virtualStart, pDestinationBuffer, readLength);
}



///////////////////////////////////////////////////////////
//
// Return the specified number of bytes from the stream
//
///////////////////////////////////////////////////////////
void streamReader::read(std::uint8_t* pBuffer, size_t bufferLength)
{
	while(bufferLength != 0)
	{
		// Update the data buffer if it is empty
		///////////////////////////////////////////////////////////
        if(m_dataBufferCurrent == m_dataBufferEnd)
		{
            if(bufferLength >= m_dataBuffer.size())
			{
				// read the data directly into the destination buffer
				///////////////////////////////////////////////////////////
                size_t readBytes(fillDataBuffer(pBuffer, bufferLength));

                m_dataBufferCurrent = m_dataBufferEnd = 0;
				m_dataBufferStreamPosition += readBytes;
				pBuffer += readBytes;
				bufferLength -= readBytes;
				if(readBytes == 0)
				{
                    throw(StreamEOFError("Attempt to read past the end of the file"));
				}
				continue;
			}

			if(fillDataBuffer() == 0)
			{
                throw(StreamEOFError("Attempt to read past the end of the file"));
			}
		}

		// Copy the available data into the return buffer
		///////////////////////////////////////////////////////////
        size_t copySize = bufferLength;
        size_t maxSize = (size_t)(m_dataBufferEnd - m_dataBufferCurrent);
		if(copySize > maxSize)
		{
			copySize = maxSize;
		}
        ::memcpy(pBuffer, &(m_dataBuffer[m_dataBufferCurrent]), copySize);
		bufferLength -= copySize;
		pBuffer += copySize;
        m_dataBufferCurrent += copySize;
	}
}


///////////////////////////////////////////////////////////
//
// Seek the read position
//
///////////////////////////////////////////////////////////
void streamReader::seek(size_t newPosition)
{
	// The requested position is already in the data buffer?
	///////////////////////////////////////////////////////////
    size_t bufferEndPosition = m_dataBufferStreamPosition + m_dataBufferEnd;
    if(newPosition >= m_dataBufferStreamPosition && newPosition < bufferEndPosition)
	{
        m_dataBufferCurrent = newPosition - m_dataBufferStreamPosition;
		return;
	}

	// The requested position is not in the data buffer
	///////////////////////////////////////////////////////////
    m_dataBufferCurrent = m_dataBufferEnd = 0;
    m_dataBufferStreamPosition = newPosition;

}

void streamReader::seekRelative(int32_t newPosition)
{
    size_t finalPosition = position() + newPosition;

    seek(finalPosition);
}

} // namespace implementation

} // namespace imebra