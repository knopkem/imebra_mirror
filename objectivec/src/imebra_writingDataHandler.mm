/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "imebra_bridgeStructures.h"

@implementation ImebraWritingDataHandler

-(id)initWithImebraWritingDataHandler:(imebra::WritingDataHandler*)pWritingDataHandler
{
    self = [super init];
    if(self)
    {
        m_pDataHandler = pWritingDataHandler;
    }
    else
    {
        delete pWritingDataHandler;
    }
    return self;
}

-(void)dealloc
{
    delete m_pDataHandler;
#if !__has_feature(objc_arc)
    [super dealloc];
#endif
}

-(unsigned int)size
{
    return (unsigned int)m_pDataHandler->getSize();
}

-(void)setSize:(unsigned int)size
{
    m_pDataHandler->setSize(size);
}

-(void) setSignedLong:(unsigned int)index withValue:(int)value error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    m_pDataHandler->setSignedLong(index, value);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void) setUnsignedLong:(unsigned int)index withValue:(unsigned int)value error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    m_pDataHandler->setUnsignedLong(index, value);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void) setDouble:(unsigned int)index withValue:(double)value error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    m_pDataHandler->setDouble(index, value);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void) setString:(unsigned int)index withValue:(NSString*)value error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    m_pDataHandler->setString(index, imebra::NSStringToString(value));

    OBJC_IMEBRA_FUNCTION_END();
}

-(void) setDate:(unsigned int)index withValue:(ImebraDate*)value error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    m_pDataHandler->setDate(index, *(imebra::Date*)(value->m_pDate));

    OBJC_IMEBRA_FUNCTION_END();
}

-(void) setAge:(unsigned int)index withValue:(ImebraAge*)value error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    m_pDataHandler->setAge(index, *(imebra::Age*)(value->m_pAge));

    OBJC_IMEBRA_FUNCTION_END();
}

@end

