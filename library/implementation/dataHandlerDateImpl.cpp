/*
$fileHeader$
*/

/*! \file dataHandlerDate.cpp
    \brief Implementation of the dataHandlerDate class.

*/

#include <sstream>
#include <iomanip>

#include "exceptionImpl.h"
#include "dataHandlerDateImpl.h"


namespace imebra
{

namespace implementation
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// dataHandlerDate
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerDate::readingDataHandlerDate(const memory& parseMemory): readingDataHandlerDateTimeBase(parseMemory, "DA")
{

}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the date
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void readingDataHandlerDate::getDate(const size_t index,
        std::uint32_t* pYear,
        std::uint32_t* pMonth,
        std::uint32_t* pDay,
        std::uint32_t* pHour,
        std::uint32_t* pMinutes,
        std::uint32_t* pSeconds,
        std::uint32_t* pNanoseconds,
		std::int32_t* pOffsetHours,
		std::int32_t* pOffsetMinutes) const
{
    IMEBRA_FUNCTION_START();

	*pYear = 0;
	*pMonth = 0;
	*pDay = 0;
	*pHour = 0;
	*pMinutes = 0;
	*pSeconds = 0;
	*pNanoseconds = 0;
	*pOffsetHours = 0;
	*pOffsetMinutes = 0;

    std::string dateString = getString(index);
	parseDate(dateString, pYear, pMonth, pDay);

	IMEBRA_FUNCTION_END();
}


writingDataHandlerDate::writingDataHandlerDate(const std::shared_ptr<buffer> &pBuffer):
    writingDataHandlerDateTimeBase(pBuffer, "DA", 0, 18)
{
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the date
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void writingDataHandlerDate::setDate(const size_t index,
        std::uint32_t year,
        std::uint32_t month,
        std::uint32_t day,
        std::uint32_t /* hour */,
        std::uint32_t /* minutes */,
        std::uint32_t /* seconds */,
        std::uint32_t /* nanoseconds */,
		std::int32_t /* offsetHours */,
		std::int32_t /* offsetMinutes */)
{
    IMEBRA_FUNCTION_START();

    setString(index, buildDate(year, month, day));

	IMEBRA_FUNCTION_END();
}

} // namespace handlers

} // namespace implementation

} // namespace imebra
