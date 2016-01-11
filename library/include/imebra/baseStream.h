/*
$fileHeader$
*/

/*! \file baseStream_swig.h
    \brief Declaration of the the base class for the streams (memory, file, ...)
			for SWIG.
*/

#if !defined(imebraBaseStream_SWIG_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
#define imebraBaseStream_SWIG_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_

#ifndef SWIG

#include <memory>
#include "definitions.h"

namespace puntoexe
{
    class baseStreamInput;
    class baseStreamOutput;
}

#endif

namespace imebra
{

/// \addtogroup group_swig_bindings
/// @{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
/// \brief This class represents a stream.
///
/// Specialized classes derived from this class can
///  read/write from/to files stored on the computer's
///  disks, on the network or in memory.
///
/// The application can read or write into the stream
///  by using the streamReader or the streamWriter.
///
/// While this class can be used across several threads,
///  the streamReader and the streamWriter can be used in
///  one thread only. This is not a big deal, since one
///  stream can be connected to several streamReaders and
///  streamWriters.
///
/// The library supplies the specialized derived
///  class stream, used to read or write into physical
///  files.
///
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class IMEBRA_API BaseStreamInput
{
#ifndef SWIG
	friend class StreamReader;
protected:
    BaseStreamInput(std::shared_ptr<puntoexe::baseStreamInput> pStream);
#endif
public:
    BaseStreamInput(const BaseStreamInput& right);
    BaseStreamInput& operator=(const BaseStreamInput& right);

#ifndef SWIG
protected:
    std::shared_ptr<puntoexe::baseStreamInput> m_pStream;
#endif

public:
    BaseStreamInput();
};


class IMEBRA_API BaseStreamOutput
{
#ifndef SWIG
    friend class StreamWriter;
protected:
    BaseStreamOutput(std::shared_ptr<puntoexe::baseStreamOutput> pStream);
#endif
public:
    BaseStreamOutput(const BaseStreamOutput& right);
    BaseStreamOutput& operator=(const BaseStreamOutput& right);

#ifndef SWIG
protected:
    std::shared_ptr<puntoexe::baseStreamOutput> m_pStream;
#endif

public:
    BaseStreamOutput();
};


///@}

}

#endif // !defined(imebraBaseStream_SWIG_3146DA5A_5276_4804_B9AB_A3D54C6B123A__INCLUDED_)
