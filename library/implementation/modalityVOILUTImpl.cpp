/*
$fileHeader$
*/

/*! \file modalityVOILUT.cpp
    \brief Implementation of the class modalityVOILUT.

*/

#define NOMINMAX

#include "exceptionImpl.h"
#include "modalityVOILUTImpl.h"
#include "dataSetImpl.h"
#include "colorTransformsFactoryImpl.h"
#include <math.h>
#include <limits>

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
// Modality VOILUT transform
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
modalityVOILUT::modalityVOILUT(std::shared_ptr<const dataSet> pDataSet):
        m_pDataSet(pDataSet), m_voiLut(0), m_rescaleIntercept(pDataSet->getDouble(0x0028, 0, 0x1052, 0, 0, 0)), m_rescaleSlope(1.0), m_bEmpty(true)

{
    IMEBRA_FUNCTION_START();

	// Only monochrome images can have the modality voi-lut
	///////////////////////////////////////////////////////
    const std::string colorSpace(pDataSet->getStringThrow(0x0028, 0x0, 0x0004, 0, 0));

	if(!colorTransforms::colorTransformsFactory::isMonochrome(colorSpace))
	{
		return;
	}

    try
    {
        std::shared_ptr<handlers::readingDataHandler> rescaleHandler(m_pDataSet->getReadingDataHandlerThrow(0x0028, 0, 0x1053, 0x0));
        m_rescaleSlope = rescaleHandler->getDouble(0);
        m_bEmpty = false;
    }
    catch(const MissingDataElementError&)
    {
        try
        {
            m_voiLut = pDataSet->getLutThrow(0x0028, 0x3000, 0);
            m_bEmpty = m_voiLut->getSize() != 0;
        }
        catch(const MissingDataElementError&)
        {
            // Nothing to do. Transformis empty
        }

    }

    IMEBRA_FUNCTION_END();
}

bool modalityVOILUT::isEmpty() const
{
	return m_bEmpty;
}


std::shared_ptr<image> modalityVOILUT::allocateOutputImage(
        bitDepth inputDepth,
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

	// LUT
	///////////////////////////////////////////////////////////
	if(m_voiLut != 0 && m_voiLut->getSize() != 0 && m_voiLut->checkValidDataRange())
	{
		std::uint8_t bits(m_voiLut->getBits());

		// Look for negative outputs
		bool bNegative(false);
        for(std::int32_t index(m_voiLut->getFirstMapped()), size((std::int32_t)m_voiLut->getSize()); !bNegative && size != 0; --size, ++index)
		{
			bNegative = (m_voiLut->mappedValue(index) < 0);
		}

        bitDepth depth;
		if(bNegative)
		{
            if(bits > 16)
            {
                depth = bitDepth::depthS32;
            }
            else if(bits > 8)
            {
                depth = bitDepth::depthS16;
            }
            else
            {
                depth = bitDepth::depthS8;
            }
		}
		else
		{
            if(bits > 16)
            {
                depth = bitDepth::depthU32;
            }
            else if(bits > 8)
            {
                depth = bitDepth::depthU16;
            }
            else
            {
                depth = bitDepth::depthU8;
            }
        }

        return std::make_shared<image>(outputWidth, outputHeight, depth, inputColorSpace, bits - 1);
	}

	// Rescale
	///////////////////////////////////////////////////////////
    if(fabs(m_rescaleSlope) <= std::numeric_limits<double>::denorm_min())
	{
        return std::make_shared<image>(outputWidth, outputHeight, inputDepth, inputColorSpace, inputHighBit);
	}

	std::int32_t value0 = 0;
    std::int32_t value1 = ((std::int32_t)1 << (inputHighBit + 1)) - 1;
    if(inputDepth == bitDepth::depthS16 || inputDepth == bitDepth::depthS8)
	{
        value0 = ((std::int32_t)(-1) << inputHighBit);
        value1 = ((std::int32_t)1 << inputHighBit);
	}
	std::int32_t finalValue0((std::int32_t) ((double)value0 * m_rescaleSlope + m_rescaleIntercept + 0.5) );
	std::int32_t finalValue1((std::int32_t) ((double)value1 * m_rescaleSlope + m_rescaleIntercept + 0.5) );

	std::int32_t minValue, maxValue;
	if(finalValue0 < finalValue1)
	{
		minValue = finalValue0;
		maxValue = finalValue1;
	}
	else
	{
		minValue = finalValue1;
		maxValue = finalValue0;
	}

	if(minValue >= 0 && maxValue <= 255)
	{
        return std::make_shared<image>(outputWidth, outputHeight, bitDepth::depthU8, inputColorSpace, 7);
	}
	if(minValue >= -128 && maxValue <= 127)
	{
        return std::make_shared<image>(outputWidth, outputHeight, bitDepth::depthS8, inputColorSpace, 7);
	}
	if(minValue >= 0 && maxValue <= 65535)
	{
        return std::make_shared<image>(outputWidth, outputHeight, bitDepth::depthU16, inputColorSpace, 15);
	}
	if(minValue >= -32768 && maxValue <= 32767)
	{
        return std::make_shared<image>(outputWidth, outputHeight, bitDepth::depthS16, inputColorSpace, 15);
	}

    return std::make_shared<image>(outputWidth, outputHeight, bitDepth::depthS32, inputColorSpace, 31);

    IMEBRA_FUNCTION_END();
}



} // namespace transforms

} // namespace implementation

} // namespace imebra
