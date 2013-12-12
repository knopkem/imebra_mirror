/*
$fileHeader$
*/

/*! \file YBRFULLToRGB.h
    \brief Declaration of the class YBRFULLToRGB.

*/

#if !defined(imebraYBRFULLToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraYBRFULLToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

#include "colorTransform.h"


///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
{

namespace transforms
{

namespace colorTransforms
{

/// \addtogroup group_transforms
///
/// @{

///////////////////////////////////////////////////////////
/// \brief Transforms an image from the colorspace 
///         YBR_FULL into the color space RGB.
///
/// The input image has to have the colorspace YBR_FULL,
///  while the output image is created by the transform
///  and will have the colorspace RGB.
///
///////////////////////////////////////////////////////////
class YBRFULLToRGB: public colorTransform
{
public:
	virtual std::wstring getInitialColorSpace();
	virtual std::wstring getFinalColorSpace();
	virtual ptr<colorTransform> createColorTransform();

        DEFINE_RUN_TEMPLATE_TRANSFORM;

        template <class inputType, class outputType>
        void templateTransform(
            inputType* inputHandlerData, size_t /* inputHandlerSize */, imbxUint32 inputHandlerWidth, const std::wstring& inputHandlerColorSpace,
            ptr<palette> /* inputPalette */,
            imbxInt32 inputHandlerMinValue, imbxUint32 inputHighBit,
            imbxInt32 inputTopLeftX, imbxInt32 inputTopLeftY, imbxInt32 inputWidth, imbxInt32 inputHeight,
            outputType* outputHandlerData, size_t /* outputHandlerSize */, imbxInt32 outputHandlerWidth, const std::wstring& outputHandlerColorSpace,
            ptr<palette> /* outputPalette */,
            imbxInt32 outputHandlerMinValue, imbxUint32 outputHighBit,
            imbxInt32 outputTopLeftX, imbxInt32 outputTopLeftY)

        {
            checkColorSpaces(inputHandlerColorSpace, outputHandlerColorSpace);

            inputType* pInputMemory(inputHandlerData);
            outputType* pOutputMemory(outputHandlerData);

            pInputMemory += (inputTopLeftY * inputHandlerWidth + inputTopLeftX) * 3;
            pOutputMemory += (outputTopLeftY * outputHandlerWidth + outputTopLeftX) * 3;
            
            imbxInt32 inputMiddleValue(inputHandlerMinValue + ((imbxInt32)1 << inputHighBit));
            imbxInt32 sourceY, sourceB, sourceR, destination;

            imbxInt32 inputHandlerNumValues = (imbxInt32)1 << (inputHighBit + 1);
            imbxInt32 outputHandlerNumValues = (imbxInt32)1 << (outputHighBit + 1);

            if(inputHighBit > outputHighBit)
            {
                imbxUint32 rightShift = inputHighBit - outputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        sourceY = (imbxInt32)( *(pInputMemory++) );
                        sourceB = (imbxInt32)( *(pInputMemory++) ) - inputMiddleValue;
                        sourceR = (imbxInt32)( *(pInputMemory++) ) - inputMiddleValue;

                        destination = sourceY + ((22970 * sourceR + 8192) >> 14);
                        if(destination < 0)
                        {
                            *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        }
                        else if (destination >= (imbxInt32)inputHandlerNumValues)
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + outputHandlerNumValues - 1);
                        }
                        else
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + (destination >> rightShift));
                        }

                        destination = sourceY - ((5638 * sourceB + 11700 * sourceR + 8192) >> 14);
                        if(destination < 0)
                        {
                            *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        }
                        else if (destination >= (imbxInt32)inputHandlerNumValues)
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + outputHandlerNumValues - 1);
                        }
                        else
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + (destination >> rightShift));
                        }

                        destination = sourceY + ((29032 * sourceB + 8192) >> 14);
                        if(destination < 0)
                        {
                            *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        }
                        else if (destination >= (imbxInt32)inputHandlerNumValues)
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + outputHandlerNumValues - 1);
                        }
                        else
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + (destination >> rightShift));
                        }
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * 3;
                }
            }
            else
            {
                imbxUint32 leftShift = outputHighBit - inputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        sourceY = (imbxInt32)( *(pInputMemory++) );
                        sourceB = (imbxInt32)( *(pInputMemory++) ) - inputMiddleValue;
                        sourceR = (imbxInt32)( *(pInputMemory++) ) - inputMiddleValue;

                        destination = sourceY + ((22970 * sourceR + 8192) >> 14);
                        if(destination < 0)
                        {
                            *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        }
                        else if (destination >= (imbxInt32)inputHandlerNumValues)
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + outputHandlerNumValues - 1);
                        }
                        else
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + (destination << leftShift));
                        }

                        destination = sourceY - ((5638 * sourceB + 11700 * sourceR + 8192) >> 14);
                        if(destination < 0)
                        {
                            *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        }
                        else if (destination >= (imbxInt32)inputHandlerNumValues)
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + outputHandlerNumValues - 1);
                        }
                        else
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + (destination << leftShift));
                        }

                        destination = sourceY + ((29032 * sourceB + 8192) >> 14);
                        if(destination < 0)
                        {
                            *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        }
                        else if (destination >= (imbxInt32)inputHandlerNumValues)
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + outputHandlerNumValues - 1);
                        }
                        else
                        {
                            *(pOutputMemory++) = (outputType)(outputHandlerMinValue + (destination << leftShift));
                        }
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += (outputHandlerWidth - inputWidth) * 3;
                }
            }
        }
};

/// @}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraYBRFULLToRGB_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
