/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

/*! \file dataHandlerStringLT.h
    \brief Declaration of the class dataHandlerStringLT.

*/

#if !defined(imebraDataHandlerStringLT_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
#define imebraDataHandlerStringLT_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_

#include "dataHandlerStringUnicodeImpl.h"


namespace imebra
{

namespace implementation
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// dataHandlerStringLT
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
class readingDataHandlerStringLT : public readingDataHandlerStringUnicode
{
public:
    readingDataHandlerStringLT(const memory& parseMemory, const std::shared_ptr<const charsetsList_t>& pCharsets);
};

class writingDataHandlerStringLT: public writingDataHandlerStringUnicode
{
public:
    writingDataHandlerStringLT(const std::shared_ptr<buffer>& pBuffer, const std::shared_ptr<const charsetsList_t>& pCharsets);
};

} // namespace handlers

} // namespace implementation

} // namespace imebra

#endif // !defined(imebraDataHandlerStringLT_367AAE47_6FD7_4107_AB5B_25A355C5CB6E__INCLUDED_)
