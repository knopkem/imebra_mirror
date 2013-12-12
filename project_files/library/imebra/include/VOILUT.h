/*
$fileHeader$
*/

/*! \file VOILUT.h
    \brief Declaration of the class VOILUT.

*/

#if !defined(imebraVOILUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
#define imebraVOILUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_

#include "image.h"
#include "LUT.h"
#include "transform.h"



///////////////////////////////////////////////////////////
//
// Everything is in the namespace puntoexe::imebra
//
///////////////////////////////////////////////////////////
namespace puntoexe
{

namespace imebra
{

class lut;

namespace transforms
{

/// \addtogroup group_transforms
///
/// @{

///////////////////////////////////////////////////////////
/// \brief Transforms the value of the input image's pixels
///         by using the presentation VOI/LUT defined in
///         the dataSet.
///
/// The dataSet could define more than one VOI/LUT: by
///  default the transform uses the first VOI or LUT
///  defined in the dataset.
///
/// To control which VOI/LUT is used for the
///  transformation the application must use the functions
///  getVOILUTId(), getVOILUTDescription(), setVOILUT() or
///  set the VOI or the LUT directly by calling
///  setCenterWidth() or setLUT().
///
///////////////////////////////////////////////////////////
class VOILUT: public transforms::transformHandlers
{
public:
    /// \brief Constructor.
    ///
    /// @param pDataSet the dataset from which the input image
    ///        comes from
    ///
    ///////////////////////////////////////////////////////////
	VOILUT(ptr<dataSet> pDataSet): m_pDataSet(pDataSet), m_windowCenter(0), m_windowWidth(0){}

	/// \brief Retrieve an ID for a VOI or a LUT.
	///
	/// The returned ID can be used with the functions
	///  getVOILUTDescription() and setVOILUT().
	///
	/// The function returns 0 when the requested VOI/LUT
	///  doesn't exist.
	///
	/// The parameter VOILUTNumber is a zero based index used
	///  to scan all the available VOIs first and then all the
	///  LUTs.
	/// For instance, if VOILUTNumber is 3 and the dataSet
	///  contains 2 VOIs and 3 LUTs, then the function will
	///  return the ID for the second LUT.
	///
	/// @param VOILUTNumber  a number that identifies the
	///                       VOI or the LUT for which the
	///                       ID is requested.
	///                      The value 0 refers to the first
	///                       VOI in the dataSet or to the
	///                       first LUT if there isn't any
	///                       defined VOI. Bigger values refer
	///                       to the following VOIs or LUTs
	///                       when all the VOIs have been
	///                       scanned
	/// @return an ID that can be used with
	///          getVOILUTDescription() and setVOILUT(), or 0
	///                       if the requested VOI/LUT doesn't
	///                       exist
	///
	///////////////////////////////////////////////////////////
	imbxUint32 getVOILUTId(imbxUint32 VOILUTNumber);

	/// \brief Return a description for the VOI or LUT with
	///         the specified ID.
	///
	/// The VOI/LUT ID can be obtained by calling
	///  getVOILUTId().
	///
	/// @param VOILUTId the id of the VOI/LUT for which the
	///                  description is required
	/// @return         the VOI/LUT description
	///
	///////////////////////////////////////////////////////////
	std::wstring getVOILUTDescription(imbxUint32 VOILUTId);

	/// \brief Define the VOI/LUT to use for the
	///         transformation.
	///
	/// The VOI/LUT ID can be obtained by calling
	///  getVOILUTId().
	///
	/// Disable the VOI/LUT transform if the parameter is 0.
	///
	/// @param VOILUTId the ID of the VOI/LUT to use for the
	///                  transformation, or 0 to disable the
	///                  transformation
	///
	///////////////////////////////////////////////////////////
	void setVOILUT(imbxUint32 VOILUTId);

	/// \brief Define the LUT to use for the transformation.
	///
	/// @param pLut the lut that will be used for the
	///              transformation
	///
	///////////////////////////////////////////////////////////
	void setLUT(ptr<lut> pLut);

	/// \brief Define the VOI width/center to use for the
	///         transformation.
	///
	/// @param center   the center value of the VOI
	/// @param width    the width value of the VOI
	///
	///////////////////////////////////////////////////////////
	void setCenterWidth(imbxInt32 center, imbxInt32 width);

	/// \brief Returns the VOI width/center used for the
	///         transformation.
	///
	/// @param pCenter  pointer to the recipient for the VOI
	///                  center
	/// @param pWidth    pointer to the recipient for the VOI
	///                  width
	///
	///////////////////////////////////////////////////////////
	void getCenterWidth(imbxInt32* pCenter, imbxInt32* pWidth);

    /// \brief Finds and apply the optimal VOI values.
    ///
    /// @param inputImage    the image for which the optimal
    ///                      VOI must be found
    /// @param inputTopLeftX the horizontal coordinate of the
    ///                       top-left corner of the area for
    ///                       which the optimal VOI must be
    ///                       found
    /// @param inputTopLeftY the vertical coordinate of the
    ///                       top-left corner of the area for
    ///                       which the optimal VOI must be
    ///                       found
    /// @param inputWidth    the width of the area for which
    ///                       the optimal VOI must be found
    /// @param inputHeight   the height of the area for which
    ///                       the optimal VOI must be found
    ///
    ///////////////////////////////////////////////////////////
    void applyOptimalVOI(const ptr<puntoexe::imebra::image>& inputImage, imbxUint32 inputTopLeftX, imbxUint32 inputTopLeftY, imbxUint32 inputWidth, imbxUint32 inputHeight);


	DEFINE_RUN_TEMPLATE_TRANSFORM;

    // The actual transformation is done here
    //
    ///////////////////////////////////////////////////////////
	template <class inputType, class outputType>
			void templateTransform(
					inputType* inputHandlerData, size_t /* inputHandlerSize */, imbxUint32 inputHandlerWidth, const std::wstring& /* inputHandlerColorSpace */,
					ptr<palette> /* inputPalette */,
                    imbxInt32 inputHandlerMinValue, imbxUint32 inputHighBit,
					imbxInt32 inputTopLeftX, imbxInt32 inputTopLeftY, imbxInt32 inputWidth, imbxInt32 inputHeight,
					outputType* outputHandlerData, size_t /* outputHandlerSize */, imbxInt32 outputHandlerWidth, const std::wstring& /* outputHandlerColorSpace */,
					ptr<palette> /* outputPalette */,
                    imbxInt32 outputHandlerMinValue, imbxUint32 outputHighBit,
					imbxInt32 outputTopLeftX, imbxInt32 outputTopLeftY)

	{
		inputType* pInputMemory(inputHandlerData);
		outputType* pOutputMemory(outputHandlerData);

		pInputMemory += inputTopLeftY * inputHandlerWidth + inputTopLeftX;
		pOutputMemory += outputTopLeftY * outputHandlerWidth + outputTopLeftX;

		//
		// LUT found
		//
		///////////////////////////////////////////////////////////
		if(m_pLUT != 0 && m_pLUT->getSize() != 0)
		{
			lut* pLUT = m_pLUT.get();
            inputHighBit = pLUT->getBits();
			inputHandlerMinValue = 0;

            if(inputHighBit > outputHighBit)
			{
                imbxInt32 rightShift = inputHighBit - outputHighBit;
                for(; inputHeight != 0; --inputHeight)
                {
                    for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                    {
                        *(pOutputMemory++) = (outputType)( outputHandlerMinValue + (pLUT->mappedValue((imbxInt32) (*(pInputMemory++))) >> rightShift ));
                    }
                    pInputMemory += (inputHandlerWidth - inputWidth);
                    pOutputMemory += (outputHandlerWidth - inputWidth);
                }
            }
			else
			{
                imbxInt32 leftShift = outputHighBit - inputHighBit;
				for(; inputHeight != 0; --inputHeight)
				{
					for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
					{
                        *(pOutputMemory++) = (outputType)( outputHandlerMinValue + (pLUT->mappedValue((imbxInt32) (*(pInputMemory++))) << leftShift ));
					}
					pInputMemory += (inputHandlerWidth - inputWidth);
					pOutputMemory += (outputHandlerWidth - inputWidth);
				}
			}

			return;
		}

		//
		// LUT not found.
		// Use the window's center/width
		//
        ///////////////////////////////////////////////////////////
        imbxInt64 inputHandlerNumValues = (imbxInt64)1 << (inputHighBit + 1);
        imbxInt64 outputHandlerNumValues = (imbxInt64)1 << (outputHighBit + 1);
        imbxInt64 minValue = (imbxInt64)m_windowCenter- (imbxInt64)(m_windowWidth/2);
        imbxInt64 maxValue = (imbxInt64)m_windowCenter+ (imbxInt64)(m_windowWidth/2);
		if(m_windowWidth <= 1)
		{
			minValue = inputHandlerMinValue ;
			maxValue = inputHandlerMinValue + inputHandlerNumValues;
		}
		else
		{
			inputHandlerNumValues = maxValue - minValue;
		}


        imbxInt64 value;

        if(inputHandlerNumValues > outputHandlerNumValues)
        {
            imbxInt32 ratio = (imbxInt32)(inputHandlerNumValues / outputHandlerNumValues);
            for(; inputHeight != 0; --inputHeight)
            {

                for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                {
                    value = (imbxInt64) *(pInputMemory++);
                    if(value <= minValue)
                    {
                        *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        continue;
                    }
                    if(value >= maxValue)
                    {
                        *(pOutputMemory++) = (outputType)( outputHandlerMinValue + outputHandlerNumValues - 1 );
                        continue;
                    }
                    *(pOutputMemory++) = (outputType)( (value - minValue) / ratio + outputHandlerMinValue );
                }
                pInputMemory += (inputHandlerWidth - inputWidth);
                pOutputMemory += (outputHandlerWidth - inputWidth);
            }
        }
        else
        {
            imbxInt32 ratio = (imbxInt32)(outputHandlerNumValues / inputHandlerNumValues);
            for(; inputHeight != 0; --inputHeight)
            {

                for(int scanPixels(inputWidth); scanPixels != 0; --scanPixels)
                {
                    value = (imbxInt64) *(pInputMemory++);
                    if(value <= minValue)
                    {
                        *(pOutputMemory++) = (outputType)outputHandlerMinValue;
                        continue;
                    }
                    if(value >= maxValue)
                    {
                        *(pOutputMemory++) = (outputType)( outputHandlerMinValue + outputHandlerNumValues - 1 );
                        continue;
                    }
                    *(pOutputMemory++) = (outputType)( (value - minValue) * ratio + outputHandlerMinValue );
                }
                pInputMemory += (inputHandlerWidth - inputWidth);
                pOutputMemory += (outputHandlerWidth - inputWidth);
            }
        }
	}


	virtual bool isEmpty();

	virtual ptr<image> allocateOutputImage(ptr<image> pInputImage, imbxUint32 width, imbxUint32 height);

protected:

    // Find the optimal VOI
    //
    ///////////////////////////////////////////////////////////
    template <class inputType>
            void templateFindOptimalVOI(
                    inputType* inputHandlerData, size_t /* inputHandlerSize */, imbxUint32 inputHandlerWidth,
                    imbxInt32 inputTopLeftX, imbxInt32 inputTopLeftY, imbxInt32 inputWidth, imbxInt32 inputHeight)
    {
        inputType* pInputMemory(inputHandlerData + inputHandlerWidth * inputTopLeftY + inputTopLeftX);
        imbxInt32 minValue(*pInputMemory);
        imbxInt32 maxValue(minValue);
        imbxInt32 value;
        for(imbxInt32 scanY(inputHeight); scanY != 0; --scanY)
        {
            for(imbxInt32 scanX(inputWidth); scanX != 0; --scanX)
            {
                value = *(pInputMemory++);
                if(value < minValue)
                {
                    minValue = value;
                }
                else if(value > maxValue)
                {
                    maxValue = value;
                }
            }
            pInputMemory += inputHandlerWidth - inputWidth;
        }
        imbxInt32 center = (maxValue - minValue) / 2 + minValue;
        imbxInt32 width = maxValue - minValue;
        setCenterWidth(center, width);
    }

    ptr<dataSet> m_pDataSet;
	ptr<lut> m_pLUT;
	imbxInt32 m_windowCenter;
	imbxInt32 m_windowWidth;
};

/// @}

} // namespace transforms

} // namespace imebra

} // namespace puntoexe

#endif // !defined(imebraVOILUT_8347C70F_1FC8_4df8_A887_8DE9E968B2CF__INCLUDED_)
