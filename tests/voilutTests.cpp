#include <imebra/imebra.h>
#include "buildImageForTest.h"
#include <gtest/gtest.h>


namespace imebra
{

namespace tests
{

TEST(voilut, voilutUnsigned8)
{
    MutableImage unsigned8(7, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);
    {
        WritingDataHandler unsigned8Handler = unsigned8.getWritingDataHandler();
        unsigned8Handler.setUnsignedLong(0, 0);
        unsigned8Handler.setUnsignedLong(1, 10);
        unsigned8Handler.setUnsignedLong(2, 20);
        unsigned8Handler.setUnsignedLong(3, 30);
        unsigned8Handler.setUnsignedLong(4, 40);
        unsigned8Handler.setUnsignedLong(5, 50);
        unsigned8Handler.setUnsignedLong(6, 60);
    }

    {
        VOILUT voilut(VOIDescription(0, 50, dicomVOIFunction_t::linear, ""));

        MutableImage unsigned8Out = voilut.allocateOutputImage(unsigned8, 7, 1);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, unsigned8Out, 0, 0);

        ReadingDataHandler unsigned8Handler = unsigned8Out.getReadingDataHandler();

        ASSERT_EQ(130u, unsigned8Handler.getUnsignedLong(0));
        ASSERT_EQ(182u, unsigned8Handler.getUnsignedLong(1));
        ASSERT_EQ(234u, unsigned8Handler.getUnsignedLong(2));
        ASSERT_EQ(255u, unsigned8Handler.getUnsignedLong(3));
        ASSERT_EQ(255u, unsigned8Handler.getUnsignedLong(4));
        ASSERT_EQ(255u, unsigned8Handler.getUnsignedLong(5));
        ASSERT_EQ(255u, unsigned8Handler.getUnsignedLong(6));
    }

    {
        VOILUT voilut(VOIDescription(15, 1, dicomVOIFunction_t::linear, ""));

        MutableImage unsigned8Out = voilut.allocateOutputImage(unsigned8, 7, 1);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, unsigned8Out, 0, 0);

        ReadingDataHandler unsigned8Handler = unsigned8Out.getReadingDataHandler();

        ASSERT_EQ(0u, unsigned8Handler.getUnsignedLong(0));
        ASSERT_EQ(0u, unsigned8Handler.getUnsignedLong(1));
        ASSERT_EQ(255u, unsigned8Handler.getUnsignedLong(2));
        ASSERT_EQ(255u, unsigned8Handler.getUnsignedLong(3));
        ASSERT_EQ(255u, unsigned8Handler.getUnsignedLong(4));
        ASSERT_EQ(255u, unsigned8Handler.getUnsignedLong(5));
        ASSERT_EQ(255u, unsigned8Handler.getUnsignedLong(6));
    }

    {
        VOILUT voilut(VOIDescription(70, 50, dicomVOIFunction_t::linear, ""));

        MutableImage signed16Out(7, 1, bitDepth_t::depthS16, "MONOCHROME2", 15);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, signed16Out, 0, 0);

        ReadingDataHandler signed16Handler = signed16Out.getReadingDataHandler();

        ASSERT_EQ(-32768, signed16Handler.getSignedLong(0));
        ASSERT_EQ(-32768, signed16Handler.getSignedLong(1));
        ASSERT_EQ(-32768, signed16Handler.getSignedLong(2));
        ASSERT_EQ(-32768, signed16Handler.getSignedLong(3));
        ASSERT_EQ(-32768, signed16Handler.getSignedLong(4));
        ASSERT_EQ(-26080, signed16Handler.getSignedLong(5));
        ASSERT_EQ(-12706, signed16Handler.getSignedLong(6));
    }

    {
        VOILUT voilut(VOIDescription(0, 50, dicomVOIFunction_t::linearExact, ""));

        MutableImage unsigned8Out = voilut.allocateOutputImage(unsigned8, 7, 1);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, unsigned8Out, 0, 0);

        ReadingDataHandler unsigned8Handler = unsigned8Out.getReadingDataHandler();

        ASSERT_EQ(0u, unsigned8Handler.getUnsignedLong(0));
        ASSERT_EQ(51u, unsigned8Handler.getUnsignedLong(1));
        ASSERT_EQ(102u, unsigned8Handler.getUnsignedLong(2));
        ASSERT_EQ(153u, unsigned8Handler.getUnsignedLong(3));
        ASSERT_EQ(204u, unsigned8Handler.getUnsignedLong(4));
        ASSERT_EQ(255u, unsigned8Handler.getUnsignedLong(5));
        ASSERT_EQ(255u, unsigned8Handler.getUnsignedLong(6));
    }

    {
        VOILUT voilut(VOIDescription(70, 50, dicomVOIFunction_t::linearExact, ""));

        MutableImage signed16Out(7, 1, bitDepth_t::depthS16, "MONOCHROME2", 15);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, signed16Out, 0, 0);

        ReadingDataHandler signed16Handler = signed16Out.getReadingDataHandler();

        ASSERT_EQ(-32768, signed16Handler.getSignedLong(0));
        ASSERT_EQ(-32768, signed16Handler.getSignedLong(1));
        ASSERT_EQ(-32768, signed16Handler.getSignedLong(2));
        ASSERT_EQ(-32768, signed16Handler.getSignedLong(3));
        ASSERT_EQ(-32768, signed16Handler.getSignedLong(4));
        ASSERT_EQ(-32768, signed16Handler.getSignedLong(5));
        ASSERT_EQ(-32768, signed16Handler.getSignedLong(6));
    }

    {
        VOILUT voilut(VOIDescription(0, 50, dicomVOIFunction_t::sigmoid, ""));

        MutableImage unsigned8Out = voilut.allocateOutputImage(unsigned8, 7, 1);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, unsigned8Out, 0, 0);

        ReadingDataHandler unsigned8Handler = unsigned8Out.getReadingDataHandler();

        ASSERT_EQ(127u, unsigned8Handler.getUnsignedLong(0));
        ASSERT_EQ(175u, unsigned8Handler.getUnsignedLong(1));
        ASSERT_EQ(212u, unsigned8Handler.getUnsignedLong(2));
        ASSERT_EQ(233u, unsigned8Handler.getUnsignedLong(3));
        ASSERT_EQ(245u, unsigned8Handler.getUnsignedLong(4));
        ASSERT_EQ(250u, unsigned8Handler.getUnsignedLong(5));
        ASSERT_EQ(252u, unsigned8Handler.getUnsignedLong(6));
    }

    {
        VOILUT voilut(VOIDescription(70, 50, dicomVOIFunction_t::sigmoid, ""));

        MutableImage signed16Out(7, 1, bitDepth_t::depthS16, "MONOCHROME2", 15);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, signed16Out, 0, 0);

        ReadingDataHandler signed16Handler = signed16Out.getReadingDataHandler();

        ASSERT_EQ(241, signed16Handler.getSignedLong(0));
        ASSERT_EQ(534, signed16Handler.getSignedLong(1));
        ASSERT_EQ(1178, signed16Handler.getSignedLong(2));
        ASSERT_EQ(2566, signed16Handler.getSignedLong(3));
        ASSERT_EQ(5450, signed16Handler.getSignedLong(4));
        ASSERT_EQ(11008, signed16Handler.getSignedLong(5));
        ASSERT_EQ(20317, signed16Handler.getSignedLong(6));
    }
}


TEST(voilut, voilutUnsigned8OptimalVOI)
{
    MutableImage unsigned8(6, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);
    {
        WritingDataHandler unsigned8Handler = unsigned8.getWritingDataHandler();
        unsigned8Handler.setUnsignedLong(0, 10);
        unsigned8Handler.setUnsignedLong(1, 0);
        unsigned8Handler.setUnsignedLong(2, 20);
        unsigned8Handler.setUnsignedLong(3, 30);
        unsigned8Handler.setUnsignedLong(4, 40);
        unsigned8Handler.setUnsignedLong(5, 50);
    }

    VOIDescription voiDescription = VOILUT::getOptimalVOI(unsigned8, 0, 0, 6, 1);
    VOILUT voilut(voiDescription);

    MutableImage unsigned8Out = voilut.allocateOutputImage(unsigned8, 6, 1);
    voilut.runTransform(unsigned8, 0, 0, 6, 1, unsigned8Out, 0, 0);

    ReadingDataHandler unsigned8Handler = unsigned8Out.getReadingDataHandler();

    ASSERT_EQ(51u, unsigned8Handler.getUnsignedLong(0));
    ASSERT_EQ(0u, unsigned8Handler.getUnsignedLong(1));
    ASSERT_EQ(102u, unsigned8Handler.getUnsignedLong(2));
    ASSERT_EQ(153u, unsigned8Handler.getUnsignedLong(3));
    ASSERT_EQ(204u, unsigned8Handler.getUnsignedLong(4));
    ASSERT_EQ(255u, unsigned8Handler.getUnsignedLong(5));

    MutableImage signed16Out(6, 1, bitDepth_t::depthS16, "MONOCHROME2", 15);
    voilut.runTransform(unsigned8, 0, 0, 6, 1, signed16Out, 0, 0);

    ReadingDataHandler signed16Handler = signed16Out.getReadingDataHandler();

    ASSERT_EQ(-19661, signed16Handler.getSignedLong(0));
    ASSERT_EQ(-32768, signed16Handler.getSignedLong(1));
    ASSERT_EQ(-6554, signed16Handler.getSignedLong(2));
    ASSERT_EQ(6553, signed16Handler.getSignedLong(3));
    ASSERT_EQ(19660, signed16Handler.getSignedLong(4));
    ASSERT_EQ(32767, signed16Handler.getSignedLong(5));

}


TEST(voilut, voilutUnsigned8LUT)
{
    MutableImage unsigned8(6, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);
    {
        WritingDataHandler unsigned8Handler = unsigned8.getWritingDataHandler();
        unsigned8Handler.setUnsignedLong(0, 0);
        unsigned8Handler.setUnsignedLong(1, 1);
        unsigned8Handler.setUnsignedLong(2, 2);
        unsigned8Handler.setUnsignedLong(3, 3);
        unsigned8Handler.setUnsignedLong(4, 4);
        unsigned8Handler.setUnsignedLong(5, 5);
    }

    MutableDataSet testDataSet;
    MutableTag sequenceTag = testDataSet.getTagCreate(TagId(tagId_t::VOILUTSequence_0028_3010));
    MutableDataSet lutItem = sequenceTag.appendSequenceItem();
    {
        WritingDataHandlerNumeric descriptor = lutItem.getWritingDataHandlerNumeric(TagId(tagId_t::LUTDescriptor_0028_3002), 0, tagVR_t::US);
        WritingDataHandlerNumeric data = lutItem.getWritingDataHandlerNumeric(TagId(tagId_t::LUTData_0028_3006), 0, tagVR_t::US);
        descriptor.setUnsignedLong(0, 3);
        descriptor.setUnsignedLong(1, 2);
        descriptor.setUnsignedLong(2, 16);

        data.setUnsignedLong(0, 100);
        data.setUnsignedLong(1, 200);
        data.setUnsignedLong(2, 300);
    }
    LUT lut = testDataSet.getLUT(TagId(tagId_t::VOILUTSequence_0028_3010), 0);

    VOILUT voilut(lut);

    MutableImage paletteOut = voilut.allocateOutputImage(unsigned8, 6, 1);
    voilut.runTransform(unsigned8, 0, 0, 6, 1, paletteOut, 0, 0);

    ReadingDataHandler paletteHandler = paletteOut.getReadingDataHandler();

    ASSERT_EQ(100u, paletteHandler.getUnsignedLong(0));
    ASSERT_EQ(100u, paletteHandler.getUnsignedLong(1));
    ASSERT_EQ(100u, paletteHandler.getUnsignedLong(2));
    ASSERT_EQ(200u, paletteHandler.getUnsignedLong(3));
    ASSERT_EQ(300u, paletteHandler.getUnsignedLong(4));
    ASSERT_EQ(300u, paletteHandler.getUnsignedLong(5));

}

}

}

