TEMPLATE = app

QT -= core gui

CONFIG += warn_on

unix:LIBS = -lgcov
windows:DEFINES += _WIN32_WINNT=0x0501 WINVER=0x0501 NTDDI_VERSION=0x05010000
LIBS += -lgtest -lpthread

QMAKE_CXXFLAGS += -std=c++0x -Wall -Wextra -pedantic --coverage

OTHER_FILES += \
    ReadMe.txt \
    CImbx_tests.vcproj \
    CImbx_tests.rc \
    CImbx_tests.cbp \
    ../../build.xml \
    ../DoxyfileHTML \
    ../DoxyfilePDF \
    ../docs/html_header.html \
    ../docs/html_footer.html \
    ../docs/commercial_license_perpetual.txt \
    ../docs/commercial_license.txt \
    ../docs/gpl.txt

HEADERS += \
    ../library/imebra/include/YBRPARTIALToRGB.h \
    ../library/imebra/include/YBRFULLToRGB.h \
    ../library/imebra/include/YBRFULLToMONOCHROME2.h \
    ../library/imebra/include/waveform.h \
    ../library/imebra/include/VOILUT.h \
    ../library/imebra/include/viewHelper.h \
    ../library/imebra/include/transformsChain.h \
    ../library/imebra/include/transformHighBit.h \
    ../library/imebra/include/transaction.h \
    ../library/imebra/include/RGBToYBRPARTIAL.h \
    ../library/imebra/include/RGBToYBRFULL.h \
    ../library/imebra/include/RGBToMONOCHROME2.h \
    ../library/imebra/include/PALETTECOLORToRGB.h \
    ../library/imebra/include/MONOCHROME2ToYBRFULL.h \
    ../library/imebra/include/MONOCHROME2ToRGB.h \
    ../library/imebra/include/MONOCHROME1ToRGB.h \
    ../library/imebra/include/MONOCHROME1ToMONOCHROME2.h \
    ../library/imebra/include/modalityVOILUT.h \
    ../library/imebra/include/LUT.h \
    ../library/imebra/include/jpegCodec.h \
    ../library/imebra/include/imebraDoc.h \
    ../library/imebra/include/imebra.h \
    ../library/imebra/include/image.h \
    ../library/imebra/include/drawBitmap.h \
    ../library/imebra/include/dicomDir.h \
    ../library/imebra/include/dicomDict.h \
    ../library/imebra/include/dicomCodec.h \
    ../library/imebra/include/dataSet.h \
    ../library/imebra/include/dataHandlerTime.h \
    ../library/imebra/include/dataHandlerStringUT.h \
    ../library/imebra/include/dataHandlerStringUnicode.h \
    ../library/imebra/include/dataHandlerStringUI.h \
    ../library/imebra/include/dataHandlerStringST.h \
    ../library/imebra/include/dataHandlerStringSH.h \
    ../library/imebra/include/dataHandlerStringPN.h \
    ../library/imebra/include/dataHandlerStringLT.h \
    ../library/imebra/include/dataHandlerStringLO.h \
    ../library/imebra/include/dataHandlerStringIS.h \
    ../library/imebra/include/dataHandlerStringDS.h \
    ../library/imebra/include/dataHandlerStringCS.h \
    ../library/imebra/include/dataHandlerStringAS.h \
    ../library/imebra/include/dataHandlerStringAE.h \
    ../library/imebra/include/dataHandlerString.h \
    ../library/imebra/include/dataHandlerNumeric.h \
    ../library/imebra/include/dataHandlerDateTimeBase.h \
    ../library/imebra/include/dataHandlerDateTime.h \
    ../library/imebra/include/dataHandlerDate.h \
    ../library/imebra/include/dataHandler.h \
    ../library/imebra/include/dataGroup.h \
    ../library/imebra/include/dataCollection.h \
    ../library/imebra/include/data.h \
    ../library/imebra/include/colorTransformsFactory.h \
    ../library/imebra/include/colorTransform.h \
    ../library/imebra/include/codecFactory.h \
    ../library/imebra/include/codec.h \
    ../library/imebra/include/charsetsList.h \
    ../library/imebra/include/bufferStream.h \
    ../library/imebra/include/buffer.h \
	../library/imebra/include/transform.h \
    ../library/base/include/streamWriter.h \
    ../library/base/include/streamReader.h \
    ../library/base/include/streamController.h \
    ../library/base/include/stream.h \
    ../library/base/include/nullStream.h \
    ../library/base/include/memoryStream.h \
    ../library/base/include/memory.h \
    ../library/base/include/huffmanTable.h \
    ../library/base/include/exception.h \
    ../library/base/include/criticalSection.h \
    ../library/base/include/configuration.h \
    ../library/base/include/charsetConversion.h \
    ../library/base/include/baseStream.h \
    ../library/base/include/baseObject.h \
    ../docs/mainPage.h \
    ../docs/g_examples.h \
    ../docs/f_transactions_locks.h \
    ../docs/e_unicode.h \
    ../docs/d_addToProject.h \
    ../docs/c_quick_tour.h \
    ../docs/b_imebra_structure.h \
    ../docs/a_license.h \
    ../library/base/include/charsetConversionIconv.h \
    ../library/base/include/charsetConversionICU.h \
    ../library/base/include/charsetConversionWindows.h

SOURCES += \
    unicodeStringHandlerTest.cpp \
    transactionTest.cpp \
    streamBitsTest.cpp \
    paletteTest.cpp \
    numericHandlerTest.cpp \
    memoryStreamTest.cpp \
    jpegCodecTest.cpp \
    huffmanTest.cpp \
    exceptionsTest.cpp \
    drawBitmapTest.cpp \
    dicomDirTest.cpp \
    dicomCodecTest.cpp \
    decimalStringHandlerTest.cpp \
    dateTimeHandlerTest.cpp \
    dataSetTest.cpp \
    CImbx_tests.cpp \
    buildImageForTest.cpp \
    bufferTest.cpp \
    bitTransformTest.cpp \
    ageStringHandlerTest.cpp \
    ../library/imebra/src/YBRPARTIALToRGB.cpp \
    ../library/imebra/src/YBRFULLToRGB.cpp \
    ../library/imebra/src/YBRFULLToMONOCHROME2.cpp \
    ../library/imebra/src/waveform.cpp \
    ../library/imebra/src/VOILUT.cpp \
    ../library/imebra/src/viewHelper.cpp \
    ../library/imebra/src/transformsChain.cpp \
    ../library/imebra/src/transformHighBit.cpp \
    ../library/imebra/src/transaction.cpp \
    ../library/imebra/src/RGBToYBRPARTIAL.cpp \
    ../library/imebra/src/RGBToYBRFULL.cpp \
    ../library/imebra/src/RGBToMONOCHROME2.cpp \
    ../library/imebra/src/PALETTECOLORToRGB.cpp \
    ../library/imebra/src/MONOCHROME2ToYBRFULL.cpp \
    ../library/imebra/src/MONOCHROME2ToRGB.cpp \
    ../library/imebra/src/MONOCHROME1ToRGB.cpp \
    ../library/imebra/src/MONOCHROME1ToMONOCHROME2.cpp \
    ../library/imebra/src/modalityVOILUT.cpp \
    ../library/imebra/src/LUT.cpp \
    ../library/imebra/src/jpegCodec.cpp \
    ../library/imebra/src/image.cpp \
    ../library/imebra/src/drawBitmap.cpp \
    ../library/imebra/src/dicomDir.cpp \
    ../library/imebra/src/dicomDict.cpp \
    ../library/imebra/src/dicomCodec.cpp \
    ../library/imebra/src/dataSet.cpp \
    ../library/imebra/src/dataHandlerTime.cpp \
    ../library/imebra/src/dataHandlerStringUT.cpp \
    ../library/imebra/src/dataHandlerStringUnicode.cpp \
    ../library/imebra/src/dataHandlerStringUI.cpp \
    ../library/imebra/src/dataHandlerStringST.cpp \
    ../library/imebra/src/dataHandlerStringSH.cpp \
    ../library/imebra/src/dataHandlerStringPN.cpp \
    ../library/imebra/src/dataHandlerStringLT.cpp \
    ../library/imebra/src/dataHandlerStringLO.cpp \
    ../library/imebra/src/dataHandlerStringIS.cpp \
    ../library/imebra/src/dataHandlerStringDS.cpp \
    ../library/imebra/src/dataHandlerStringCS.cpp \
    ../library/imebra/src/dataHandlerStringAS.cpp \
    ../library/imebra/src/dataHandlerStringAE.cpp \
    ../library/imebra/src/dataHandlerString.cpp \
    ../library/imebra/src/dataHandlerDateTimeBase.cpp \
    ../library/imebra/src/dataHandlerDateTime.cpp \
    ../library/imebra/src/dataHandlerDate.cpp \
    ../library/imebra/src/dataHandler.cpp \
    ../library/imebra/src/dataGroup.cpp \
    ../library/imebra/src/data.cpp \
    ../library/imebra/src/colorTransformsFactory.cpp \
    ../library/imebra/src/colorTransform.cpp \
    ../library/imebra/src/codecFactory.cpp \
    ../library/imebra/src/codec.cpp \
    ../library/imebra/src/charsetsList.cpp \
    ../library/imebra/src/buffer.cpp \
	../library/imebra/src/transform.cpp \
    ../library/base/src/streamWriter.cpp \
    ../library/base/src/streamReader.cpp \
    ../library/base/src/streamController.cpp \
    ../library/base/src/stream.cpp \
    ../library/base/src/memoryStream.cpp \
    ../library/base/src/memory.cpp \
    ../library/base/src/huffmanTable.cpp \
    ../library/base/src/exception.cpp \
    ../library/base/src/criticalSection.cpp \
    ../library/base/src/charsetConversion.cpp \
    ../library/base/src/baseStream.cpp \
    ../library/base/src/baseObject.cpp \
    ../library/base/src/charsetConversionIconv.cpp \
    ../library/base/src/charsetConversionICU.cpp \
    ../library/base/src/charsetConversionWindows.cpp \
    streamTest.cpp
