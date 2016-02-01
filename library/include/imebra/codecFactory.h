/*
$fileHeader$
*/

/*! \file codecFactory_swig.h
    \brief Declaration of the class used to retrieve the codec able to
		handle the requested transfer syntax (SWIG).

*/

#if !defined(imebraCodecFactory_SWIG_82307D4A_6490_4202_BF86_93399D32721E__INCLUDED_)
#define imebraCodecFactory_SWIG_82307D4A_6490_4202_BF86_93399D32721E__INCLUDED_

#include <string>
#include "dataSet.h"
#include "streamReader.h"
#include "streamWriter.h"
#include "definitions.h"

namespace imebra
{

///
/// \brief The CodecFactory class contains a collections of
///         codecs and select the right one when loading
///         or writing data from/to a stream.
///
///////////////////////////////////////////////////////////
class IMEBRA_API CodecFactory
{
public:
    ///
    /// \brief Tries to parse the
    /// \param reader
    /// \param maxSizeBufferLoad
    /// \return
    ///
    static DataSet load(StreamReader& reader, size_t maxSizeBufferLoad);
    static DataSet load(const std::wstring& fileName, size_t maxSizeBufferLoad);
    static DataSet load(const std::string& fileName, size_t maxSizeBufferLoad);

    enum codecType
    {
        dicom,
        jpeg
    };

    static void save(const DataSet& dataSet, StreamWriter& writer, codecType codecType);
    static void save(const DataSet& dataSet, const std::wstring& fileName, codecType codecType);
    static void save(const DataSet& dataSet, const std::string& fileName, codecType codecType);
};

}
#endif // !defined(imebraCodecFactory_SWIG_82307D4A_6490_4202_BF86_93399D32721E__INCLUDED_)