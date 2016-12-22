#if defined(__APPLE__)

#include <imebra/imebra.h>
#include <memory>
#import "../include/imebra/objectivec/imebra_image.h"
#import <Foundation/Foundation.h>

void CGDataProviderCallbackFunc(void *info, const void *data, size_t size)
{
    // Release the shared pointer holding the memory
    ////////////////////////////////////////////////
    delete (imebra::ReadWriteMemory*)info;
}

#ifdef TARGET_OS_IPHONE
UIImage* getImebraImage(const imebra::Image& image, const imebra::Transform& transform)
#else
NSImage* getImebraImage(const imebra::Image& image, const imebra::Transform& transform)
#endif
{

    // Allocate the drawBitmap class
    ////////////////////////////////
    imebra::DrawBitmap drawBitmap(transform);

    // Get the amount of memory needed for the conversion
    /////////////////////////////////////////////////////
    std::uint32_t width(image.getWidth());
    std::uint32_t height(image.getHeight());

    // Get the result raw data
    //////////////////////////
    std::unique_ptr<imebra::ReadWriteMemory> pMemory(drawBitmap.getBitmap(image, imebra::drawBitmapType_t::drawBitmapRGBA, 4));
    size_t dataSize;
    char* pData = pMemory->data(&dataSize);

    // Create a CGImage, then convert it to NSImage or UIImage
    //////////////////////////////////////////////////////////
    CGDataProviderRef dataProviderRef = CGDataProviderCreateWithData(pMemory.release(),
                                                                pData,
                                                                dataSize,
                                                                CGDataProviderCallbackFunc);

    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrder32Big | kCGImageAlphaPremultipliedLast;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;

    CGImageRef imageRef = CGImageCreate(
                width, height,
                8, 32,
                width * 4,
                colorSpaceRef, bitmapInfo, dataProviderRef, NULL, YES, renderingIntent);


#ifdef TARGET_OS_IPHONE
    UIImage* returnImage = [[UIImage alloc] initWithCGImage:imageRef];
#else
    NSImage* returnImage = [[NSImage alloc] initWithCGImage:imageRef];
#endif
    CGDataProviderRelease(dataProviderRef);
    CGImageRelease(imageRef);
    CGColorSpaceRelease(colorSpaceRef);
    return returnImage;
}

#endif
