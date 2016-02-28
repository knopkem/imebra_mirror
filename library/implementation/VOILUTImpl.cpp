/*
$fileHeader$
*/

/*! \file VOILUT.cpp
    \brief Implementation of the class VOILUT.

*/

#include "exceptionImpl.h"
#include "VOILUTImpl.h"
#include "dataSetImpl.h"
#include "../include/imebra/exceptions.h"

namespace imebra
{

namespace implementation
{

namespace transforms
{


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve an ID for a VOI LUT module.
// Returns NULL if the requested VOI LUT module doesn't
//  exist
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::uint32_t VOILUT::getVOILUTId(std::uint32_t VOILUTNumber)
{
    IMEBRA_FUNCTION_START();

	// reset the LUT's ID
	///////////////////////////////////////////////////////////
	std::uint32_t VOILUTId = 0;

	// Reset the window's center and width
	///////////////////////////////////////////////////////////
	std::int32_t windowWidth = 0;

	// Scan all the window's centers and widths.
	///////////////////////////////////////////////////////////
	std::uint32_t scanWindow;
    for(scanWindow = VOILUTNumber; (windowWidth == 0) && (scanWindow != 0xffffffff); --scanWindow)
	{
        windowWidth  = m_pDataSet->getSignedLong(0x0028, 0, 0x1051, 0, scanWindow, 0);
	}
	++scanWindow;

	// If the window's center/width has not been found or it
	//  is not inside the VOILUTNumber parameter, then
	//  look in the LUTs
	///////////////////////////////////////////////////////////
	if(windowWidth == 0 || scanWindow != VOILUTNumber)
	{
		// Find the LUT's ID
		///////////////////////////////////////////////////////////
        VOILUTNumber -= scanWindow;
        try
        {
            m_pDataSet->getSequenceItemThrow(0x0028, 0, 0x3010, VOILUTNumber);
            VOILUTId = VOILUTNumber | 0x00100000;
		}
        catch(const MissingDataElementError&)
        {
            // Nothing to do. The lut does not exist
        }
	}

	// The window's center/width has been found
	///////////////////////////////////////////////////////////
	else
	{
		// Set the VOILUTId
		///////////////////////////////////////////////////////////
        VOILUTId = VOILUTNumber | 0x00200000;
	}

	// Return the VOILUT's ID
	///////////////////////////////////////////////////////////
	return VOILUTId;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve a lisz of IDs of the available VOIs and LUTs.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
VOILUT::voilutIds_t VOILUT::getVOILUTIds()
{
    IMEBRA_FUNCTION_START();

    voilutIds_t returnList;
    for(std::uint32_t scanIds(0); ; ++scanIds)
    {
        std::uint32_t id(getVOILUTId(scanIds));
        if(id == 0)
        {
            return returnList;
        }
        returnList.push_back(id);
    }

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns the VOILUT description
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::wstring VOILUT::getVOILUTDescription(std::uint32_t VOILUTId)
{
    IMEBRA_FUNCTION_START();

	std::wstring VOILUTDescription;

	// If the dataset has not been, then return NULL
	///////////////////////////////////////////////////////////
	if(m_pDataSet == 0)
	{
		return VOILUTDescription;
	}

	std::uint32_t VOILUTNumber=VOILUTId & 0x0000ffff;

	// Window's center/width
	///////////////////////////////////////////////////////////
	if((VOILUTId & 0x00200000))
	{
        VOILUTDescription = m_pDataSet->getUnicodeString(0x0028, 0, 0x1055, 0, VOILUTNumber, L"");
	}

	// LUT
	///////////////////////////////////////////////////////////
	if((VOILUTId & 0x00100000))
	{
        std::shared_ptr<lut> voiLut = m_pDataSet->getLutThrow(0x0028, 0x3010, VOILUTNumber);
		if(voiLut != 0)
		{
			VOILUTDescription=voiLut->getDescription();
		}
	}

	return VOILUTDescription;

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the VOI/LUT module to use for the transformation.
// You can retrieve the VOILUTId using the function
//  GetVOILUTId().
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VOILUT::setVOILUT(std::uint32_t VOILUTId)
{
    IMEBRA_FUNCTION_START();

	// If the dataset has not been set, then return NULL
	///////////////////////////////////////////////////////////
	if(m_pDataSet == 0)
	{
		return;
	}

	std::uint32_t VOILUTNumber=VOILUTId & 0x0000ffff;

	// Window's center/width
	///////////////////////////////////////////////////////////
	if((VOILUTId & 0x00200000))
	{
		setCenterWidth(
            m_pDataSet->getDoubleThrow(0x0028, 0, 0x1050, 0, VOILUTNumber),
            m_pDataSet->getDoubleThrow(0x0028, 0, 0x1051, 0, VOILUTNumber));
		return;
	}

	// LUT
	///////////////////////////////////////////////////////////
	if((VOILUTId & 0x00100000))
	{
        setLUT(m_pDataSet->getLutThrow(0x0028, 0x3010, VOILUTNumber));
		return;
	}

	setCenterWidth(0, 0);

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the lut
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VOILUT::setLUT(std::shared_ptr<lut> pLut)
{
	m_pLUT = pLut;
	m_windowCenter = 0;
	m_windowWidth = 0;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the center/width
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VOILUT::setCenterWidth(double center, double width)
{
	m_windowCenter = center;
	m_windowWidth = width;
    m_pLUT.reset();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get the center/width
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VOILUT::getCenterWidth(double* pCenter, double* pWidth)
{
	*pCenter = m_windowCenter;
	*pWidth = m_windowWidth;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Returns true if the transform is empty
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool VOILUT::isEmpty() const
{
	return m_windowWidth <= 1 && (m_pLUT == 0 || m_pLUT->getSize() == 0);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Allocate the output image
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<image> VOILUT::allocateOutputImage(
        bitDepth_t inputDepth,
        const std::string& inputColorSpace,
        std::uint32_t inputHighBit,
        std::shared_ptr<palette> /* inputPalette */,
        std::uint32_t outputWidth, std::uint32_t outputHeight) const
{
    IMEBRA_FUNCTION_START();

    if(isEmpty())
	{
        return std::make_shared<image>(outputWidth, outputHeight, inputDepth, inputColorSpace, inputHighBit);
	}

	if(m_pLUT != 0 && m_pLUT->getSize() != 0)
	{
		std::uint8_t bits = m_pLUT->getBits();

		bool bNegative(false);
        for(std::int32_t index(m_pLUT->getFirstMapped()), size((std::int32_t)m_pLUT->getSize()); !bNegative && size != 0; --size, ++index)
		{
			bNegative = (m_pLUT->mappedValue(index) < 0);
		}

		if(bNegative)
		{
            inputDepth = bits > 8 ? bitDepth_t::depthS16 : bitDepth_t::depthS8;
		}
		else
		{
            inputDepth = bits > 8 ? bitDepth_t::depthU16 : bitDepth_t::depthU8;
		}
        return std::make_shared<image>(outputWidth, outputHeight, inputDepth, inputColorSpace, bits - 1);
	}

	//
	// LUT not found.
	// Use the window's center/width
	//
	///////////////////////////////////////////////////////////
	if(m_windowWidth <= 1)
	{
        return std::make_shared<image>(outputWidth, outputHeight, inputDepth, inputColorSpace, inputHighBit);
	}

    if(inputDepth == bitDepth_t::depthS8)
        inputDepth = bitDepth_t::depthU8;
    if(inputDepth == bitDepth_t::depthS16 || inputDepth == bitDepth_t::depthU32 || inputDepth == bitDepth_t::depthS32)
        inputDepth = bitDepth_t::depthU16;

    return std::make_shared<image>(outputWidth, outputHeight, inputDepth, inputColorSpace, inputHighBit);

    IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Finds and applies the optimal VOI.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void VOILUT::applyOptimalVOI(const std::shared_ptr<imebra::implementation::image>& inputImage, std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight)
{
    IMEBRA_FUNCTION_START();

    std::uint32_t width, height;
    inputImage->getSize(&width, &height);

    if(inputTopLeftX + inputWidth > width || inputTopLeftY + inputHeight > height)
    {
        IMEBRA_THROW(TransformInvalidAreaError, "The input and/or output areas are invalid");
    }

    std::shared_ptr<handlers::readingDataHandlerNumericBase> handler(inputImage->getReadingDataHandler());
    HANDLER_CALL_TEMPLATE_FUNCTION_WITH_PARAMS(templateFindOptimalVOI, handler, width, inputTopLeftX, inputTopLeftY, inputWidth, inputHeight);

    IMEBRA_FUNCTION_END();
}




} // namespace transforms

} // namespace implementation

} // namespace imebra
