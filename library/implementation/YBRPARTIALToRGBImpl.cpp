/*
$fileHeader$
*/

/*! \file YBRPARTIALToRGB.cpp
    \brief Implementation of the class YBRPARTIALToRGB.

*/

#include "exceptionImpl.h"
#include "YBRPARTIALToRGBImpl.h"
#include "dataHandlerImpl.h"
#include "dataSetImpl.h"
#include "imageImpl.h"


namespace imebra
{

namespace implementation
{

namespace transforms
{

namespace colorTransforms
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string YBRPARTIALToRGB::getInitialColorSpace()
{
    return "YBR_PARTIAL";
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the final color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string YBRPARTIALToRGB::getFinalColorSpace()
{
    return "RGB";
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Create a new YBRPARTIALToRGB object
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<colorTransform> YBRPARTIALToRGB::createColorTransform()
{
    return std::shared_ptr<colorTransform>(std::make_shared<YBRPARTIALToRGB>());
}




} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace imebra
