/*
$fileHeader$
*/

/*! \file dataHandlerNumeric.h
    \brief Declaration of the handler for the numeric tags.

*/

#if !defined(imebraDataHandlerNumeric_BD270581_5746_48d1_816E_64B700955A12__INCLUDED_)
#define imebraDataHandlerNumeric_BD270581_5746_48d1_816E_64B700955A12__INCLUDED_

#include <sstream>
#include <iomanip>
#include <type_traits>
#include "../include/imebra/exceptions.h"
#include "exceptionImpl.h"
#include "dataHandlerImpl.h"
#include "memoryImpl.h"
#include "charsetConversionImpl.h"

///////////////////////////////////////////////////////////
//
// Everything is in the namespace imebra::implementation
//
///////////////////////////////////////////////////////////
namespace imebra
{

namespace implementation
{

namespace handlers
{

/// \brief This is the base class for the %data handlers
///         that manage numeric values.
///
///////////////////////////////////////////////////////////
class readingDataHandlerNumericBase: public readingDataHandler
{
public:
    readingDataHandlerNumericBase(const std::shared_ptr<const memory>& pMemory, const std::string& dataType);

    const std::uint8_t* getMemoryBuffer() const;

    size_t getMemorySize() const;

    std::shared_ptr<const memory> getMemory() const;

    virtual void copyTo(std::uint8_t* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(std::int8_t* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(std::uint16_t* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(std::int16_t* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(std::uint32_t* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(std::int32_t* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(float* pMemory, size_t memorySize) const = 0;
    virtual void copyTo(double* pMemory, size_t memorySize) const = 0;

	virtual void copyToInt32Interleaved(std::int32_t* pDest,
										std::uint32_t destSubSampleX,
										std::uint32_t destSubSampleY,
										std::uint32_t sourceStartCol,
										std::uint32_t sourceStartRow,
										std::uint32_t sourceEndCol,
										std::uint32_t sourceEndRow,
										std::uint32_t sourceStartChannel,
										std::uint32_t sourceWidth,
										std::uint32_t sourceHeight,
										std::uint32_t sourceNumChannels) const = 0;

	/// \brief Returns truen if the buffer's elements are
	///         signed, false otherwise.
	///
	/// @return true if the buffer's elements are signed,
	///          or false otherwise
	///
	///////////////////////////////////////////////////////////
	virtual bool isSigned() const = 0;

protected:
	// Memory buffer
	///////////////////////////////////////////////////////////
    std::shared_ptr<const memory> m_pMemory;
};

class writingDataHandlerNumericBase: public writingDataHandler
{
public:
    writingDataHandlerNumericBase(const std::shared_ptr<buffer>& pBuffer, const size_t initialSize, const std::string& dataType, size_t unitSize);
    ~writingDataHandlerNumericBase();

    std::uint8_t* getMemoryBuffer() const;

    size_t getMemorySize() const;

    virtual size_t getSize() const;

    std::shared_ptr<memory> getMemory() const;

    // Set the buffer's size, in data elements
    ///////////////////////////////////////////////////////////
    virtual void setSize(const size_t elementsNumber);

    virtual void copyFromInt32Interleaved(const std::int32_t* pSource,
                                          std::uint32_t sourceReplicateX,
                                          std::uint32_t sourceReplicateY,
                                          std::uint32_t destStartCol,
                                          std::uint32_t destStartRow,
                                          std::uint32_t destEndCol,
                                          std::uint32_t destEndRow,
                                          std::uint32_t destStartChannel,
                                          std::uint32_t destWidth,
                                          std::uint32_t destHeight,
                                          std::uint32_t destNumChannels) = 0;

    virtual void copyFrom(std::shared_ptr<readingDataHandlerNumericBase> pSource) = 0;
    virtual void copyFrom(std::uint8_t* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(std::int8_t* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(std::uint16_t* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(std::int16_t* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(std::uint32_t* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(std::int32_t* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(float* pMemory, size_t memorySize) = 0;
    virtual void copyFrom(double* pMemory, size_t memorySize) = 0;

protected:
    // Memory buffer
    ///////////////////////////////////////////////////////////
    std::shared_ptr<memory> m_pMemory;

    size_t m_unitSize;
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This data handler accesses to the numeric data
///         stored in a imebra::implementation::buffer class.
///
/// A special definition of this class
///  (imebra::implementation::handlers::imageHandler) is used
///  to access to the images' raw pixels.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template<class dataHandlerType>
class readingDataHandlerNumeric : public readingDataHandlerNumericBase
{
public:
    typedef dataHandlerType value_type;

    readingDataHandlerNumeric(const std::shared_ptr<const memory>& pMemory, const std::string& dataType): readingDataHandlerNumericBase(pMemory, dataType)
    {

    }

	virtual bool isSigned() const
	{
		dataHandlerType firstValue((dataHandlerType) -1);
		dataHandlerType secondValue((dataHandlerType) 0);
		return firstValue < secondValue;
	}

	// Retrieve the data element as a signed long
	///////////////////////////////////////////////////////////
    virtual std::int32_t getSignedLong(const size_t index) const
	{
        return (std::int32_t) (((const dataHandlerType*)m_pMemory->data())[index]);
	}

	// Retrieve the data element an unsigned long
	///////////////////////////////////////////////////////////
    virtual std::uint32_t getUnsignedLong(const size_t index) const
	{
        return (std::uint32_t) (((const dataHandlerType*)m_pMemory->data())[index]);
	}

	// Retrieve the data element as a double
	///////////////////////////////////////////////////////////
    virtual double getDouble(const size_t index) const
	{
        return (double) (((const dataHandlerType*)m_pMemory->data())[index]);
	}

	// Retrieve the data element as a string
	///////////////////////////////////////////////////////////
    virtual std::string getString(const size_t index) const
	{
        IMEBRA_FUNCTION_START();

		std::ostringstream convStream;

        if(std::is_same<dataHandlerType, std::uint8_t>::value ||
                std::is_same<dataHandlerType, std::int8_t>::value )
        {
            int tempValue = (int) (((const dataHandlerType*)m_pMemory->data())[index]);
            convStream << tempValue;
        }
        else
        {
            convStream << (((const dataHandlerType*)m_pMemory->data())[index]);
        }
		return convStream.str();

		IMEBRA_FUNCTION_END();
	}

	// Retrieve the data element as a unicode string
	///////////////////////////////////////////////////////////
    virtual std::wstring getUnicodeString(const size_t index) const
	{
        IMEBRA_FUNCTION_START();

        std::string ansiString = getString(index);

        charsetsList::tCharsetsList charsets;
        charsets.push_back("ISO_IR 6");

        return dicomConversion::convertToUnicode(ansiString, charsets);

		IMEBRA_FUNCTION_END();
	}

	// Retrieve the buffer's size in elements
	///////////////////////////////////////////////////////////
    virtual size_t getSize() const
	{
        IMEBRA_FUNCTION_START();

        return m_pMemory->size() / sizeof(dataHandlerType);

		IMEBRA_FUNCTION_END();
	}

	template<class destHandlerType>
    void copyToMemory(destHandlerType* pDestination, size_t destSize) const
	{
		if(getSize() < destSize)
		{
			destSize = getSize();
		}
        const dataHandlerType* pSource((const dataHandlerType*)m_pMemory->data());
		while(destSize-- != 0)
		{
			*(pDestination++) = (destHandlerType)*(pSource++);
		}
	}

    virtual void copyTo(std::uint8_t* pMemory, size_t memorySize) const
	{
		copyToMemory(pMemory, memorySize);
	}
    virtual void copyTo(std::int8_t* pMemory, size_t memorySize) const
	{
		copyToMemory(pMemory, memorySize);
	}
    virtual void copyTo(std::uint16_t* pMemory, size_t memorySize) const
	{
		copyToMemory(pMemory, memorySize);
	}
    virtual void copyTo(std::int16_t* pMemory, size_t memorySize) const
	{
		copyToMemory(pMemory, memorySize);
	}
    virtual void copyTo(std::uint32_t* pMemory, size_t memorySize) const
	{
		copyToMemory(pMemory, memorySize);
	}
    virtual void copyTo(std::int32_t* pMemory, size_t memorySize) const
	{
		copyToMemory(pMemory, memorySize);
	}
    virtual void copyTo(float* pMemory, size_t memorySize) const
	{
		copyToMemory(pMemory, memorySize);
	}
    virtual void copyTo(double* pMemory, size_t memorySize) const
	{
		copyToMemory(pMemory, memorySize);
	}


	/// \brief Copy the buffer controlled by the handler into
	///         an array of std::int32_t values, considering that
	///         the destination buffer could be subsampled
	///
	/// The destination buffer is supposed to have the
	///  information related to a single channel.
	/// @param pDest        a pointer to the destination array
	///                      of std::int32_t values
	/// @param destSubSampleX the horizontal subsamplig
	///                      factor of the destination buffer
	///                      (1=not subsampled, 2=subsampled)
	/// @param destSubSampleY the vertical subsamplig
	///                      factor of the destination buffer
	///                      (1=not subsampled, 2=subsampled)
	/// @param sourceStartCol the horizontal coordinate of the
	///                      top left corner of the source
	///                      rectangle
	/// @param sourceStartRow the vertical coordinate of the
	///                      top left corner of the source
	///                      rectangle
	/// @param sourceEndCol   the horizontal coordinate of the
	///                      bottom right corner of the
	///                      source rectangle
	/// @param sourceEndRow   the vertical coordinate of the
	///                      bottom right corner of the
	///                      source rectangle
	/// @param sourceStartChannel the source channel to be
	///                      copied
	/// @param sourceWidth  the source buffer's width in
	///                      pixels
	/// @param sourceHeight the source buffer's height in
	///                      pixels
	/// @param sourceNumChannels the number of channels in the
	///                      source buffer
	///
	///////////////////////////////////////////////////////////
	virtual void copyToInt32Interleaved(std::int32_t* pDest,
										std::uint32_t destSubSampleX,
										std::uint32_t destSubSampleY,
										std::uint32_t sourceStartCol,
										std::uint32_t sourceStartRow,
										std::uint32_t sourceEndCol,
										std::uint32_t sourceEndRow,
										std::uint32_t sourceStartChannel,
										std::uint32_t sourceWidth,
										std::uint32_t sourceHeight,
										std::uint32_t sourceNumChannels) const
	{
		if(sourceStartCol >= sourceWidth || sourceStartRow >= sourceHeight)
		{
			return;
		}
        const dataHandlerType *pSourceRowScan = &(((const dataHandlerType*)m_pMemory->data())[(sourceStartRow*sourceWidth+sourceStartCol)*sourceNumChannels+sourceStartChannel]);
		std::int32_t* pDestRowScan = pDest;

		std::uint32_t subSampleXCount;
		std::uint32_t subSampleYCount = destSubSampleY;
		std::uint32_t subSampleYIncrease = (sourceEndCol - sourceStartCol) / destSubSampleX;

        const dataHandlerType *pSourceColScan;
		std::int32_t* pDestColScan;

		std::int32_t lastValue = (std::int32_t)*pSourceRowScan;

		for(std::uint32_t scanRow = sourceStartRow; scanRow < sourceEndRow; ++scanRow)
		{
            pSourceColScan = pSourceRowScan;
			pDestColScan = pDestRowScan;
			subSampleXCount = destSubSampleX;

			for(std::uint32_t scanCol = sourceStartCol; scanCol < sourceEndCol; ++scanCol)
			{
				if(scanCol < sourceWidth)
				{
					lastValue = (std::int32_t)*pSourceColScan;
					pSourceColScan += sourceNumChannels;
				}
				*pDestColScan += (std::int32_t)lastValue;
				if(--subSampleXCount == 0)
				{
					subSampleXCount = destSubSampleX;
					++pDestColScan;
				}
			}
			if(scanRow < sourceHeight - 1)
			{
				pSourceRowScan += sourceWidth * sourceNumChannels;
			}
			if(--subSampleYCount == 0)
			{
				subSampleYCount = destSubSampleY;
				pDestRowScan += subSampleYIncrease;
			}
		}

		std::int32_t rightShift = 0;
		if(destSubSampleX == 2)
		{
			++rightShift;
		}
		if(destSubSampleY == 2)
		{
			++rightShift;
		}
		if(rightShift == 0)
		{
			return;
		}
		for(std::int32_t* scanDivide = pDest; scanDivide < pDestRowScan; ++scanDivide)
		{
			*scanDivide >>= rightShift;
		}

	}
};

template<class dataHandlerType>
class writingDataHandlerNumeric : public writingDataHandlerNumericBase
{
public:
    typedef dataHandlerType value_type;

    writingDataHandlerNumeric(const std::shared_ptr<buffer> &pBuffer, const size_t initialSize, const std::string &dataType):
        writingDataHandlerNumericBase(pBuffer, initialSize, dataType, sizeof(dataHandlerType))
    {
    }

    // Set the data element as a signed long
    ///////////////////////////////////////////////////////////
    virtual void setSignedLong(const size_t index, const std::int32_t value)
    {
        if(index >= getSize())
        {
            setSize(index + 1);
        }
        ((dataHandlerType*)m_pMemory->data())[index] = (dataHandlerType)value;
    }

    // Set the data element as an unsigned long
    ///////////////////////////////////////////////////////////
    virtual void setUnsignedLong(const size_t index, const std::uint32_t value)
    {
        if(index >= getSize())
        {
            setSize(index + 1);
        }
        ((dataHandlerType*)m_pMemory->data())[index] = (dataHandlerType)value;
    }

    // Set the data element as a double
    ///////////////////////////////////////////////////////////
    virtual void setDouble(const size_t index, const double value)
    {
        if(index >= getSize())
        {
            setSize(index + 1);
        }
        ((dataHandlerType*)m_pMemory->data())[index] = (dataHandlerType)value;
    }

    // Set the data element as a string
    ///////////////////////////////////////////////////////////
    virtual void setString(const size_t index, const std::string& value)
    {
        IMEBRA_FUNCTION_START();

        std::istringstream convStream(value);
        dataHandlerType tempValue;
        if(std::is_same<dataHandlerType, std::uint8_t>::value ||
                std::is_same<dataHandlerType, std::int8_t>::value)
        {
            int tempValue1;
            if(!(convStream >> tempValue1))
            {
                IMEBRA_THROW(DataHandlerConversionError, "Cannot convert " << value << " to a number");
            }
            tempValue = (dataHandlerType)tempValue1;
        }
        else
        {
            if(!(convStream >> tempValue))
            {
                IMEBRA_THROW(DataHandlerConversionError, "Cannot convert " << value << " to a number");
            }
        }

        ((dataHandlerType*)m_pMemory->data())[index] = tempValue;

        IMEBRA_FUNCTION_END();
    }

    // Set the data element as an unicode string
    ///////////////////////////////////////////////////////////
    virtual void setUnicodeString(const size_t index, const std::wstring& value)
    {
        IMEBRA_FUNCTION_START();

        charsetsList::tCharsetsList charsets;
        charsets.push_back("ISO_IR 6");

        setString(index, dicomConversion::convertFromUnicode(value, &charsets));

        IMEBRA_FUNCTION_END();
    }


    /// \brief Copy the values from a memory location to
    ///         the buffer managed by the handler
    ///
    /// @param pSource a pointer to the first byte of the
    ///         memory area to copy
    /// @param sourceSize the number of values to copy
    ///
    ///////////////////////////////////////////////////////////
    template<class sourceHandlerType>
    void copyFromMemory(sourceHandlerType* pSource, size_t sourceSize)
    {
        setSize(sourceSize);
        dataHandlerType* pDest((dataHandlerType*)m_pMemory->data());
        while(sourceSize-- != 0)
        {
            *(pDest++) = (dataHandlerType)*(pSource++);
        }
    }

    // Copy the data from another handler
    ///////////////////////////////////////////////////////////
    virtual void copyFrom(std::shared_ptr<readingDataHandlerNumericBase> pSource)
    {
        IMEBRA_FUNCTION_START();

        imebra::implementation::handlers::readingDataHandlerNumericBase* pHandler(pSource.get());
        if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::uint8_t>) ||
            dynamic_cast<imebra::implementation::handlers::readingDataHandlerNumeric<std::uint8_t>* >(pHandler) != 0)
        {
            copyFromMemory<std::uint8_t> ((std::uint8_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
        }
        else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::int8_t>))
        {
            copyFromMemory<std::int8_t> ((std::int8_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
        }
        else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::uint16_t>))
        {
            copyFromMemory<std::uint16_t> ((std::uint16_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
        }
        else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::int16_t>))
        {
            copyFromMemory<std::int16_t> ((std::int16_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
        }
        else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::uint32_t>))
        {
            copyFromMemory<std::uint32_t> ((std::uint32_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
        }
        else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::int32_t>))
        {
            copyFromMemory<std::int32_t> ((std::int32_t*)pHandler->getMemoryBuffer(), pHandler->getSize());
        }
        else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<float>))
        {
            copyFromMemory<float> ((float*)pHandler->getMemoryBuffer(), pHandler->getSize());
        }
        else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<double>))
        {
            copyFromMemory<double> ((double*)pHandler->getMemoryBuffer(), pHandler->getSize());
        }
        else
        {
            throw std::runtime_error("Data type not valid");
        }

        IMEBRA_FUNCTION_END();

    }


    virtual void copyFrom(std::uint8_t* pMemory, size_t memorySize)
    {
        copyFromMemory(pMemory, memorySize);
    }
    virtual void copyFrom(std::int8_t* pMemory, size_t memorySize)
    {
        copyFromMemory(pMemory, memorySize);
    }
    virtual void copyFrom(std::uint16_t* pMemory, size_t memorySize)
    {
        copyFromMemory(pMemory, memorySize);
    }
    virtual void copyFrom(std::int16_t* pMemory, size_t memorySize)
    {
        copyFromMemory(pMemory, memorySize);
    }
    virtual void copyFrom(std::uint32_t* pMemory, size_t memorySize)
    {
        copyFromMemory(pMemory, memorySize);
    }
    virtual void copyFrom(std::int32_t* pMemory, size_t memorySize)
    {
        copyFromMemory(pMemory, memorySize);
    }
    virtual void copyFrom(float* pMemory, size_t memorySize)
    {
        copyFromMemory(pMemory, memorySize);
    }
    virtual void copyFrom(double* pMemory, size_t memorySize)
    {
        copyFromMemory(pMemory, memorySize);
    }

    template<int subsampleX>
    inline void copyFromInt32Interleaved(
        const std::int32_t* pSource,
        std::uint32_t sourceReplicateY,
        std::uint32_t destStartCol,
        std::uint32_t destStartRow,
        std::uint32_t destEndCol,
        std::uint32_t destEndRow,
        std::uint32_t destStartChannel,
        std::uint32_t destWidth,
        std::uint32_t destHeight,
        std::uint32_t destNumChannels)
    {
        dataHandlerType *pDestRowScan = &(((dataHandlerType*)m_pMemory->data())[(destStartRow*destWidth+destStartCol)*destNumChannels+destStartChannel]);
        const std::int32_t* pSourceRowScan = pSource;

        std::uint32_t replicateYCount = sourceReplicateY;
        std::uint32_t replicateYIncrease = (destEndCol - destStartCol) / subsampleX;

        dataHandlerType *pDestColScan;
        const std::int32_t* pSourceColScan;
        const std::int32_t* pSourceEndColScan;

        if(destHeight < destEndRow)
        {
            destEndRow = destHeight;
        }
        if(destWidth < destEndCol)
        {
            destEndCol = destWidth;
        }

        std::uint32_t numColumns(destEndCol - destStartCol);

        std::uint32_t horizontalCopyOperations = numColumns / subsampleX;
        std::uint32_t horizontalFinalCopyDest = numColumns - horizontalCopyOperations * subsampleX;

        dataHandlerType copyValue;
        std::int32_t scanDest;

        std::uint32_t scanHorizontalFinalCopyDest;

        std::uint32_t destRowScanIncrease(destWidth * destNumChannels);


        for(std::uint32_t numYCopies(destEndRow - destStartRow); numYCopies != 0; --numYCopies)
        {
            pDestColScan = pDestRowScan;
            pSourceColScan = pSourceRowScan;
            pSourceEndColScan = pSourceColScan + horizontalCopyOperations;

            if(subsampleX == 1)
            {
                while(pSourceColScan != pSourceEndColScan)
                {
                    *pDestColScan = (dataHandlerType)(*(pSourceColScan++));
                    pDestColScan += destNumChannels;
                }
            }
            else
            {
                while(pSourceColScan != pSourceEndColScan)
                {
                    copyValue = (dataHandlerType)(*(pSourceColScan++));
                    for(scanDest = subsampleX; scanDest != 0; --scanDest)
                    {
                        *pDestColScan = copyValue;
                        pDestColScan += destNumChannels;
                    }
                }

                for(scanHorizontalFinalCopyDest = horizontalFinalCopyDest; scanHorizontalFinalCopyDest != 0; --scanHorizontalFinalCopyDest)
                {
                    *pDestColScan = (dataHandlerType) *pSourceColScan;
                    pDestColScan += destNumChannels;
                }

            }

            pDestRowScan += destRowScanIncrease;
            if(--replicateYCount == 0)
            {
                replicateYCount = sourceReplicateY;
                pSourceRowScan += replicateYIncrease;
            }
        }
    }


    /// \brief Copy the content of an array of std::int32_t values
    ///         into the buffer controlled by the handler,
    ///         considering that the source buffer could
    ///         have subsampled data.
    ///
    /// The source buffer is supposed to have the information
    ///  related to a single channel.
    /// @param pSource      a pointer to the source array of
    ///                      std::int32_t values
    /// @param sourceReplicateX the horizontal subsamplig
    ///                      factor of the source buffer
    ///                      (1=not subsampled, 2=subsampled)
    /// @param sourceReplicateY the vertical subsamplig
    ///                      factor of the source buffer
    ///                      (1=not subsampled, 2=subsampled)
    /// @param destStartCol the horizontal coordinate of the
    ///                      top left corner of the destination
    ///                      rectangle
    /// @param destStartRow the vertical coordinate of the
    ///                      top left corner of the destination
    ///                      rectangle
    /// @param destEndCol   the horizontal coordinate of the
    ///                      bottom right corner of the
    ///                      destination rectangle
    /// @param destEndRow   the vertical coordinate of the
    ///                      bottom right corner of the
    ///                      destination rectangle
    /// @param destStartChannel the destination channel
    /// @param destWidth    the destination buffer's width in
    ///                      pixels
    /// @param destHeight   the destination buffer's height in
    ///                      pixels
    /// @param destNumChannels the number of channels in the
    ///                      destination buffer
    ///
    ///////////////////////////////////////////////////////////
    virtual void copyFromInt32Interleaved(const std::int32_t* pSource,
                                          std::uint32_t sourceReplicateX,
                                          std::uint32_t sourceReplicateY,
                                          std::uint32_t destStartCol,
                                          std::uint32_t destStartRow,
                                          std::uint32_t destEndCol,
                                          std::uint32_t destEndRow,
                                          std::uint32_t destStartChannel,
                                          std::uint32_t destWidth,
                                          std::uint32_t destHeight,
                                          std::uint32_t destNumChannels)
    {
        if(destStartCol >= destWidth || destStartRow >= destHeight)
        {
            return;
        }

        switch(sourceReplicateX)
        {
        case 1:
            copyFromInt32Interleaved< 1 > (
                        pSource,
                        sourceReplicateY,
                        destStartCol,
                        destStartRow,
                        destEndCol,
                        destEndRow,
                        destStartChannel,
                        destWidth,
                        destHeight,
                        destNumChannels);
            break;
        case 2:
            copyFromInt32Interleaved< 2 > (
                        pSource,
                        sourceReplicateY,
                        destStartCol,
                        destStartRow,
                        destEndCol,
                        destEndRow,
                        destStartChannel,
                        destWidth,
                        destHeight,
                        destNumChannels);
            break;
        case 4:
            copyFromInt32Interleaved< 4 > (
                        pSource,
                        sourceReplicateY,
                        destStartCol,
                        destStartRow,
                        destEndCol,
                        destEndRow,
                        destStartChannel,
                        destWidth,
                        destHeight,
                        destNumChannels);
            break;
        default:
            throw std::logic_error("Invalid subsampling factor");
        }
    }

};


typedef readingDataHandlerNumeric<std::uint8_t> readingDataHandlerRaw;
typedef readingDataHandlerNumeric<std::uint8_t> readingDataHandlerUint8;
typedef readingDataHandlerNumeric<std::int8_t> readingDataHandlerInt8;
typedef readingDataHandlerNumeric<std::uint16_t> readingDataHandlerUint16;
typedef readingDataHandlerNumeric<std::int16_t> readingDataHandlerInt16;
typedef readingDataHandlerNumeric<std::uint32_t> readingDataHandlerUint32;
typedef readingDataHandlerNumeric<std::int32_t> readingDataHandlerInt32;
typedef readingDataHandlerNumeric<float> readingDataHandlerFloat;
typedef readingDataHandlerNumeric<double> readingDataHandlerDouble;

typedef writingDataHandlerNumeric<std::uint8_t> writingDataHandlerRaw;
typedef writingDataHandlerNumeric<std::uint8_t> writingDataHandlerUint8;
typedef writingDataHandlerNumeric<std::int8_t> writingDataHandlerInt8;
typedef writingDataHandlerNumeric<std::uint16_t> writingDataHandlerUint16;
typedef writingDataHandlerNumeric<std::int16_t> writingDataHandlerInt16;
typedef writingDataHandlerNumeric<std::uint32_t> writingDataHandlerUint32;
typedef writingDataHandlerNumeric<std::int32_t> writingDataHandlerInt32;
typedef writingDataHandlerNumeric<float> writingDataHandlerFloat;
typedef writingDataHandlerNumeric<double> writingDataHandlerDouble;

} // namespace handlers

} // namespace implementation

} // namespace imebra

#define HANDLER_CALL_TEMPLATE_FUNCTION_WITH_PARAMS(functionName, handlerPointer, ...)\
{\
    imebra::implementation::handlers::readingDataHandlerNumericBase* pHandler(handlerPointer.get()); \
    if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::uint8_t>)) \
{\
    functionName<std::uint8_t> ((std::uint8_t*)handlerPointer->getMemoryBuffer(), handlerPointer->getSize(), __VA_ARGS__);\
    }\
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::int8_t>))\
{\
    functionName<std::int8_t> ((std::int8_t*)handlerPointer->getMemoryBuffer(), handlerPointer->getSize(), __VA_ARGS__);\
    }\
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::uint16_t>))\
{\
    functionName<std::uint16_t> ((std::uint16_t*)handlerPointer->getMemoryBuffer(), handlerPointer->getSize(), __VA_ARGS__);\
    }\
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::int16_t>))\
{\
    functionName<std::int16_t> ((std::int16_t*)handlerPointer->getMemoryBuffer(), handlerPointer->getSize(), __VA_ARGS__);\
    }\
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::uint32_t>))\
{\
    functionName<std::uint32_t> ((std::uint32_t*)handlerPointer->getMemoryBuffer(), handlerPointer->getSize(), __VA_ARGS__);\
    }\
    else if(typeid(*pHandler) == typeid(imebra::implementation::handlers::readingDataHandlerNumeric<std::int32_t>))\
{\
    functionName<std::int32_t> ((std::int32_t*)handlerPointer->getMemoryBuffer(), handlerPointer->getSize(), __VA_ARGS__);\
    }\
    else\
{\
    throw std::runtime_error("Data type not valid");\
    }\
}


#endif // !defined(imebraDataHandlerNumeric_BD270581_5746_48d1_816E_64B700955A12__INCLUDED_)