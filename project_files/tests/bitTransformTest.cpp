#include <gtest/gtest.h>
#include "../library/imebra/include/imebra.h"

namespace puntoexe
{

namespace imebra
{

namespace tests
{

// A buffer initialized to a default data type should use the data type OB
void testEmptyTransform(ptr<transforms::transform> pTransform)
{
    imbxUint32 sizeX = 41;
    imbxUint32 sizeY = 13;
    ptr<image> bits8Image(new image);
    ptr<image> bits16Image(new image);
    ptr<image> bits4Image(new image);
    bits8Image->create(sizeX, sizeY, image::depthU8, L"RGB", 7);
    bits16Image->create(sizeX, sizeY, image::depthU16, L"RGB", 15);
    bits4Image->create(sizeX, sizeY, image::depthU8, L"RGB", 3);

    imbxUint32 rowSize, channelsPixelSize, channelsNumber;
    ptr<handlers::dataHandlerNumericBase> imageHandler = bits8Image->getDataHandler(true, &rowSize, &channelsPixelSize, &channelsNumber);

    // Make 3 bands (RGB
    imbxUint32 elementNumber(0);
    for(imbxUint32 y=0; y<sizeY; ++y)
    {
        for(imbxUint32 x=0; x<sizeX; ++x)
        {
            imbxInt32 r, g, b;
            imbxUint32 value = y * 255 / sizeY;
            r = g = 0;
            b = value;
            if(x < sizeX - sizeX/3)
            {
                r = 0;
                g = value;
                b = 0;
            }
            if(x < sizeX / 3)
            {
                r = value;
                g = 0;
                b = 0;
            }
            imageHandler->setUnsignedLong(elementNumber++, r);
            imageHandler->setUnsignedLong(elementNumber++, g);
            imageHandler->setUnsignedLong(elementNumber++, b);
        }
    }
    imageHandler.release();

    pTransform->runTransform(bits8Image, 0, 0, sizeX, sizeY, bits16Image, 0, 0);
    pTransform->runTransform(bits8Image, 0, 0, sizeX, sizeY, bits4Image, 0, 0);


    ptr<handlers::dataHandlerNumericBase> bits8Handler = bits8Image->getDataHandler(false, &rowSize, &channelsPixelSize, &channelsNumber);
    ptr<handlers::dataHandlerNumericBase> bits16Handler = bits16Image->getDataHandler(false, &rowSize, &channelsPixelSize, &channelsNumber);
    ptr<handlers::dataHandlerNumericBase> bits4Handler = bits4Image->getDataHandler(false, &rowSize, &channelsPixelSize, &channelsNumber);
    elementNumber = 0;
    for(imbxUint32 checkY = 0; checkY < sizeY; ++checkY)
    {
        for(imbxUint32 checkX = 0; checkX < sizeX; ++checkX)
        {
            imbxInt32 r, g, b;
            imbxUint32 value = checkY * 255 / sizeY;
            r = g = 0;
            b = value;
            if(checkX < sizeX - sizeX/3)
            {
                r = 0;
                g = value;
                b = 0;
            }
            if(checkX < sizeX / 3)
            {
                r = value;
                g = 0;
                b = 0;
            }

            imbxInt32 value0r = bits8Handler->getUnsignedLong(elementNumber);
            imbxInt32 value1r = bits16Handler->getUnsignedLong(elementNumber);
            imbxInt32 value2r = bits4Handler->getUnsignedLong(elementNumber++);

            imbxInt32 value0g = bits8Handler->getUnsignedLong(elementNumber);
            imbxInt32 value1g = bits16Handler->getUnsignedLong(elementNumber);
            imbxInt32 value2g = bits4Handler->getUnsignedLong(elementNumber++);

            imbxInt32 value0b = bits8Handler->getUnsignedLong(elementNumber);
            imbxInt32 value1b = bits16Handler->getUnsignedLong(elementNumber);
            imbxInt32 value2b = bits4Handler->getUnsignedLong(elementNumber++);

            EXPECT_EQ(value0r, r);
            EXPECT_EQ(value0g, g);
            EXPECT_EQ(value0b, b);

            EXPECT_EQ(value0r, (value1r>>8));
            EXPECT_EQ(value0g, (value1g>>8));
            EXPECT_EQ(value0b, (value1b>>8));

            EXPECT_EQ((value0r >> 4), value2r);
            EXPECT_EQ((value0g >> 4), value2g);
            EXPECT_EQ((value0b >> 4), value2b);

        }
    }
}


TEST(bitTransformTest, testBitTransform)
{
	testEmptyTransform(new transforms::transformHighBit);
}

TEST(bitTransformTest, testEmptyTransformsChain)
{
	testEmptyTransform(new transforms::transformsChain);
}

TEST(bitTransformTest, testEmptyVOILUT)
{
	ptr<dataSet> tempDataSet(new dataSet);
	testEmptyTransform(new transforms::VOILUT(tempDataSet));
}

TEST(bitTransformTest, testEmptyModalityVOILUT)
{
	ptr<dataSet> tempDataSet(new dataSet);
	testEmptyTransform(new transforms::modalityVOILUT(tempDataSet));
}



} // namespace tests

} // namespace imebra

} // namespace puntoexe
