/*
$fileHeader$
*/

/*! \file RGBToMONOCHROME2.h
    \brief Declaration of the class RGBToMONOCHROME2.

*/

#if !defined(imebraRGBToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraRGBToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

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
///         RGB into the color space MONOCHROME2.
///
/// The input image has to have the colorspace RGB,
///  while the output image is created by the transform
///  and will have the colorspace MONOCHROME2.
///
///////////////////////////////////////////////////////////
class RGBToMONOCHROME2: public colorTransform
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
            pOutputMemory += outputTopLeftY * outputHandlerWidth + outputTopLeftX;

            imbxInt32 sourceR, sourceG, sourceB;
            if(inputHighBit > outputHighBit)
            {
                imbxUint32 rightShift = inputHighBit - outputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        sourceR = (imbxInt32) (*(pInputMemory++)) - inputHandlerMinValue;
                        sourceG = (imbxInt32) (*(pInputMemory++)) - inputHandlerMinValue;
                        sourceB = (imbxInt32) (*(pInputMemory++)) - inputHandlerMinValue;
                        *(pOutputMemory++) = (outputType) ( ((((imbxInt32)4899 * sourceR+(imbxInt32)9617 * sourceG+(imbxInt32)1868 * sourceB) >> 14) >> rightShift) + outputHandlerMinValue );
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += outputHandlerWidth - inputWidth;
                }
            }
            else
            {
                imbxUint32 leftShift = outputHighBit - inputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        sourceR = (imbxInt32) (*(pInputMemory++)) - inputHandlerMinValue;
                        sourceG = (imbxInt32) (*(pInputMemory++)) - inputHandlerMinValue;
                        sourceB = (imbxInt32) (*(pInputMemory++)) - inputHandlerMinValue;
                        *(pOutputMemory++) = (outputType) ( ((((imbxInt32)4899 * sourceR+(imbxInt32)9617 * sourceG+(imbxInt32)1868 * sourceB) >> 14) << leftShift) + outputHandlerMinValue );
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth) * 3;
                    pOutputMemory += outputHandlerWidth - inputWidth;
                }
            }
        }
};

/// @}

} // namespace colorTransforms

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraRGBToMONOCHROME2_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
