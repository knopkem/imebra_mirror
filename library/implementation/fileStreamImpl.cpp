/*
$fileHeader$
*/

/*! \file stream.cpp
    \brief Implementation of the stream class.

*/

#include "exceptionImpl.h"
#include "fileStreamImpl.h"
#include "charsetConversionImpl.h"
#include "../include/imebra/exceptions.h"

#include <sstream>
#include <errno.h>

namespace puntoexe
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// Stream
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Open a file (unicode)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void fileStream::openFile(const std::wstring& fileName, std::ios_base::openmode mode)
{
    IMEBRA_FUNCTION_START(L"stream::openFile (unicode)");

    close();

    std::wstring strMode;

    int tempMode = mode & (~std::ios::binary);

    if(tempMode == (int)(std::ios::in | std::ios::out))
    {
        strMode = L"r+";
    }

    if(tempMode == (int)(std::ios::in | std::ios::out | std::ios::app))
    {
        strMode = L"a+";
    }

    if(tempMode == (int)(std::ios::in | std::ios::out | std::ios::trunc))
    {
        strMode = L"w+";
    }

    if(tempMode == (int)(std::ios::out) || tempMode == (int)(std::ios::out | std::ios::trunc))
    {
        strMode = L"w";
    }

    if(tempMode == (int)(std::ios::out | std::ios::app))
    {
        strMode = L"a";
    }

    if(tempMode == (int)(std::ios::in))
    {
        strMode = L"r";
    }

    strMode += L"b";

#if defined(IMEBRA_WINDOWS)
     errno_t errorCode = ::_wfopen_s(&m_openFile, fileName.c_str(), strMode.c_str());
     if (errorCode != 0)
     {
         m_openFile = 0;
     }
#else
    // Convert the filename to UTF8
    defaultCharsetConversion toUtf8("ISO-IR 192");
    std::string utf8FileName(toUtf8.fromUnicode(fileName));

    // Convert the filemode to UTF8
    std::string utf8Mode(toUtf8.fromUnicode(strMode));

    m_openFile = ::fopen(utf8FileName.c_str(), utf8Mode.c_str());
    int errorCode = errno;
#endif
    if(m_openFile == 0)
    {
        std::ostringstream errorMessage;
        errorMessage << "stream::openFile failure - error code: " << errorCode;
        IMEBRA_THROW(::imebra::streamExceptionOpen, errorMessage.str());
    }

    IMEBRA_FUNCTION_END();
}

void fileStream::close()
{
    IMEBRA_FUNCTION_START(L"stream::close");

    if(m_openFile != 0)
    {
        if(::fclose(m_openFile) != 0)
        {
            IMEBRA_THROW(::imebra::streamExceptionClose, "Error while closing the file");
        }
        m_openFile = 0;
    }

    IMEBRA_FUNCTION_END();
}




///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Destructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
fileStream::~fileStream()
{
    if(m_openFile != 0)
    {
        ::fclose(m_openFile);
        m_openFile = 0;
    }
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Open a file (ansi)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void fileStreamInput::openFile(const std::string& fileName)
{
	IMEBRA_FUNCTION_START(L"stream::openFile (ansi)");

	std::wstring wFileName;
	size_t fileNameSize(fileName.size());
	wFileName.resize(fileNameSize);
	for(size_t copyChars = 0; copyChars != fileNameSize; ++copyChars)
	{
		wFileName[copyChars] = (wchar_t)fileName[copyChars];
	}
    fileStream::openFile(wFileName, std::ios::in);

	IMEBRA_FUNCTION_END();
}

void fileStreamInput::openFile(const std::wstring& fileName)
{
    fileStream::openFile(fileName, std::ios::in);
}

void fileStreamOutput::openFile(const std::string& fileName)
{
    IMEBRA_FUNCTION_START(L"stream::openFile (ansi)");

    std::wstring wFileName;
    size_t fileNameSize(fileName.size());
    wFileName.resize(fileNameSize);
    for(size_t copyChars = 0; copyChars != fileNameSize; ++copyChars)
    {
        wFileName[copyChars] = (wchar_t)fileName[copyChars];
    }
    fileStream::openFile(wFileName, std::ios::out);

    IMEBRA_FUNCTION_END();
}

void fileStreamOutput::openFile(const std::wstring &fileName)
{
    fileStream::openFile(fileName, std::ios::out);
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Write raw data into the stream
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void fileStreamOutput::write(size_t startPosition, const std::uint8_t* pBuffer, size_t bufferLength)
{
	IMEBRA_FUNCTION_START(L"stream::write");

	::fseek(m_openFile, startPosition, SEEK_SET);
	if(ferror(m_openFile) != 0)
	{
        IMEBRA_THROW(::imebra::streamExceptionWrite, "stream::seek failure");
	}

	if(::fwrite(pBuffer, 1, bufferLength, m_openFile) != bufferLength)
	{
        IMEBRA_THROW(::imebra::streamExceptionWrite, "stream::write failure");
	}

	IMEBRA_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Read raw data from the stream
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
size_t fileStreamInput::read(size_t startPosition, std::uint8_t* pBuffer, size_t bufferLength)
{
	IMEBRA_FUNCTION_START(L"stream::read");

	::fseek(m_openFile, startPosition, SEEK_SET);
	if(ferror(m_openFile) != 0)
	{
		return 0;
	}

    size_t readBytes = (size_t)::fread(pBuffer, 1, bufferLength, m_openFile);
	if(ferror(m_openFile) != 0)
	{
        IMEBRA_THROW(::imebra::streamExceptionRead, "stream::read failure");
	}
	return readBytes;

	IMEBRA_FUNCTION_END();
}


} // namespace puntoexe
