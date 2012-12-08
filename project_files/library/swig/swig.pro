TEMPLATE = lib
CONFIG += dll

unix:INCLUDEPATH += $$quote(/usr/lib/jvm/java-6-openjdk/include)

OTHER_FILES += \
    include/swig.i

HEADERS += \
    ../imebra/include/YBRPARTIALToRGB.h \
    ../imebra/include/YBRFULLToRGB.h \
    ../imebra/include/YBRFULLToMONOCHROME2.h \
    ../imebra/include/waveform.h \
    ../imebra/include/VOILUT.h \
    ../imebra/include/viewHelper.h \
    ../imebra/include/transformsChain.h \
    ../imebra/include/transformHighBit.h \
    ../imebra/include/transform.h \
    ../imebra/include/transaction.h \
    ../imebra/include/RGBToYBRPARTIAL.h \
    ../imebra/include/RGBToYBRFULL.h \
    ../imebra/include/RGBToMONOCHROME2.h \
    ../imebra/include/PALETTECOLORToRGB.h \
    ../imebra/include/MONOCHROME2ToYBRFULL.h \
    ../imebra/include/MONOCHROME2ToRGB.h \
    ../imebra/include/MONOCHROME1ToRGB.h \
    ../imebra/include/MONOCHROME1ToMONOCHROME2.h \
    ../imebra/include/modalityVOILUT.h \
    ../imebra/include/LUT.h \
    ../imebra/include/jpegCodec.h \
    ../imebra/include/imebraDoc.h \
    ../imebra/include/imebra.h \
    ../imebra/include/image.h \
    ../imebra/include/drawBitmap.h \
    ../imebra/include/dicomDir.h \
    ../imebra/include/dicomDict.h \
    ../imebra/include/dicomCodec.h \
    ../imebra/include/dataSet.h \
    ../imebra/include/dataHandlerTime.h \
    ../imebra/include/dataHandlerStringUT.h \
    ../imebra/include/dataHandlerStringUnicode.h \
    ../imebra/include/dataHandlerStringUI.h \
    ../imebra/include/dataHandlerStringST.h \
    ../imebra/include/dataHandlerStringSH.h \
    ../imebra/include/dataHandlerStringPN.h \
    ../imebra/include/dataHandlerStringLT.h \
    ../imebra/include/dataHandlerStringLO.h \
    ../imebra/include/dataHandlerStringIS.h \
    ../imebra/include/dataHandlerStringDS.h \
    ../imebra/include/dataHandlerStringCS.h \
    ../imebra/include/dataHandlerStringAS.h \
    ../imebra/include/dataHandlerStringAE.h \
    ../imebra/include/dataHandlerString.h \
    ../imebra/include/dataHandlerNumeric.h \
    ../imebra/include/dataHandlerDateTimeBase.h \
    ../imebra/include/dataHandlerDateTime.h \
    ../imebra/include/dataHandlerDate.h \
    ../imebra/include/dataHandler.h \
    ../imebra/include/dataGroup.h \
    ../imebra/include/dataCollection.h \
    ../imebra/include/data.h \
    ../imebra/include/colorTransformsFactory.h \
    ../imebra/include/colorTransform.h \
    ../imebra/include/codecFactory.h \
    ../imebra/include/codec.h \
    ../imebra/include/charsetsList.h \
    ../imebra/include/bufferStream.h \
    ../imebra/include/buffer.h \
    ../base/include/thread.h \
    ../base/include/streamWriter.h \
    ../base/include/streamReader.h \
    ../base/include/streamController.h \
    ../base/include/stream.h \
    ../base/include/nullStream.h \
    ../base/include/memoryStream.h \
    ../base/include/memory.h \
    ../base/include/huffmanTable.h \
    ../base/include/exception.h \
    ../base/include/criticalSection.h \
    ../base/include/configuration.h \
    ../base/include/charsetConversion.h \
    ../base/include/baseStream.h \
    ../base/include/baseObject.h \
    include/exceptions_swig.h \
    include/baseStream_swig.h \
    include/codecFactory_swig.h \
    include/dataSet_swig.h \
    include/stream_swig.h \
    include/streamReader_swig.h \
    include/dicomDir_swig.h \
    include/image_swig.h

SOURCES += \
    include/swig_wrap.cxx \
    ../imebra/src/YBRPARTIALToRGB.cpp \
    ../imebra/src/YBRFULLToRGB.cpp \
    ../imebra/src/YBRFULLToMONOCHROME2.cpp \
    ../imebra/src/waveform.cpp \
    ../imebra/src/VOILUT.cpp \
    ../imebra/src/viewHelper.cpp \
    ../imebra/src/transformsChain.cpp \
    ../imebra/src/transformHighBit.cpp \
    ../imebra/src/transform.cpp \
    ../imebra/src/transaction.cpp \
    ../imebra/src/RGBToYBRPARTIAL.cpp \
    ../imebra/src/RGBToYBRFULL.cpp \
    ../imebra/src/RGBToMONOCHROME2.cpp \
    ../imebra/src/PALETTECOLORToRGB.cpp \
    ../imebra/src/MONOCHROME2ToYBRFULL.cpp \
    ../imebra/src/MONOCHROME2ToRGB.cpp \
    ../imebra/src/MONOCHROME1ToRGB.cpp \
    ../imebra/src/MONOCHROME1ToMONOCHROME2.cpp \
    ../imebra/src/modalityVOILUT.cpp \
    ../imebra/src/LUT.cpp \
    ../imebra/src/jpegCodec.cpp \
    ../imebra/src/image.cpp \
    ../imebra/src/drawBitmap.cpp \
    ../imebra/src/dicomDir.cpp \
    ../imebra/src/dicomDict.cpp \
    ../imebra/src/dicomCodec.cpp \
    ../imebra/src/dataSet.cpp \
    ../imebra/src/dataHandlerTime.cpp \
    ../imebra/src/dataHandlerStringUT.cpp \
    ../imebra/src/dataHandlerStringUnicode.cpp \
    ../imebra/src/dataHandlerStringUI.cpp \
    ../imebra/src/dataHandlerStringST.cpp \
    ../imebra/src/dataHandlerStringSH.cpp \
    ../imebra/src/dataHandlerStringPN.cpp \
    ../imebra/src/dataHandlerStringLT.cpp \
    ../imebra/src/dataHandlerStringLO.cpp \
    ../imebra/src/dataHandlerStringIS.cpp \
    ../imebra/src/dataHandlerStringDS.cpp \
    ../imebra/src/dataHandlerStringCS.cpp \
    ../imebra/src/dataHandlerStringAS.cpp \
    ../imebra/src/dataHandlerStringAE.cpp \
    ../imebra/src/dataHandlerString.cpp \
    ../imebra/src/dataHandlerDateTimeBase.cpp \
    ../imebra/src/dataHandlerDateTime.cpp \
    ../imebra/src/dataHandlerDate.cpp \
    ../imebra/src/dataHandler.cpp \
    ../imebra/src/dataGroup.cpp \
    ../imebra/src/data.cpp \
    ../imebra/src/colorTransformsFactory.cpp \
    ../imebra/src/colorTransform.cpp \
    ../imebra/src/codecFactory.cpp \
    ../imebra/src/codec.cpp \
    ../imebra/src/charsetsList.cpp \
    ../imebra/src/buffer.cpp \
    ../base/src/thread.cpp \
    ../base/src/streamWriter.cpp \
    ../base/src/streamReader.cpp \
    ../base/src/streamController.cpp \
    ../base/src/stream.cpp \
    ../base/src/memoryStream.cpp \
    ../base/src/memory.cpp \
    ../base/src/huffmanTable.cpp \
    ../base/src/exception.cpp \
    ../base/src/criticalSection.cpp \
    ../base/src/charsetConversion.cpp \
    ../base/src/baseStream.cpp \
    ../base/src/baseObject.cpp \
    src/baseStream_swig.cpp \
    src/codecFactory_swig.cpp \
    src/dataSet_swig.cpp \
    src/stream_swig.cpp \
    src/streamReader_swig.cpp \
    src/exceptions_swig.cpp \
    src/dicomDir_swig.cpp














