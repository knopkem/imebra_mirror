/*
$fileHeader$
*/

/*! \file colorTransform.h
    \brief Declaration of the base class used by all the color transforms.

*/


#if !defined(imebraColorTransform_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
#define imebraColorTransform_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_

#include "transformImpl.h"


namespace imebra
{

namespace implementation
{

namespace transforms
{

/// \namespace colorTransforms
/// \brief This namespace contains all the classes
///         involved in the transformation between several
///         color spaces.
///
/// The color transformation is performed on images (see
///  imebra::implementation::image).
///
///////////////////////////////////////////////////////////
namespace colorTransforms
{

/// \addtogroup group_transforms
///
/// @{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This is the base class used by the color
///         transforms classes.
///
/// Each color transform class can handle a color space
///  conversion from one color space to another.
///
/// The class colorTransformsFactory can select the
///  right transform automatically when queried with
///  the initial and the final color spaces as parameters.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class colorTransform: public transform
{
public:
	/// \brief Return the name of the color space that this 
	///         colorTransform can convert.
	///
	/// @return a string with the name of the color space that
	///          can be converted by the colorTransform
	///
	///////////////////////////////////////////////////////////
    virtual std::string getInitialColorSpace() const = 0;

	/// \brief Return the name of the color space that this
	///         colorTransform can generate.
	///
	/// @return a string with the name of the color space that
	///          can be generated by the colorTransform
	///
	///////////////////////////////////////////////////////////
    virtual std::string getFinalColorSpace() const = 0;

	/// \brief Create another instance of the colorTransform
	///         class.
	///
	/// The new instance will have the same type of the 
	///  instance on which this function is called.
	///
	/// @return a new instance of the colorTransform. The new
	///          instance will have the same class of the
	///          instance on which the function is called
	///
	///////////////////////////////////////////////////////////
	virtual std::shared_ptr<colorTransform> createColorTransform()=0;

    virtual std::shared_ptr<image> allocateOutputImage(
            bitDepth_t inputDepth,
            const std::string& inputColorSpace,
            std::uint32_t inputHighBit,
            std::shared_ptr<palette> inputPalette,
            std::uint32_t outputWidth, std::uint32_t outputHeight) const;

protected:
    // Check the color space of the input and output images
	///////////////////////////////////////////////////////////
    void checkColorSpaces(const std::string& inputHandlerColorSpace, const std::string& outputHandlerColorSpace) const;

    void checkHighBit(std::uint32_t inputHighBit, std::uint32_t outputHighBit) const;

};



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \internal
/// \brief This class is used by the colorTransform derived
///         classes to register themself.
///
/// Each colorTransform derived class statically allocate
///  a registerColorTransform class that register the
///  color transforms in the colorTransformsFactory.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class registerColorTransform
{
public:
	/// \brief Register the specified color transform
	///
	/// @param newColorTransform the color transform to be
	///                           registered
	///
	///////////////////////////////////////////////////////////
	registerColorTransform(std::shared_ptr<colorTransform> newColorTransform);
};

/// @}

} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra


#endif // !defined(imebraColorTransform_E27C63E7_A907_4899_9BD3_8026AD7D110C__INCLUDED_)
