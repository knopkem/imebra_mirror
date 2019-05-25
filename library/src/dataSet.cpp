/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "../include/imebra/dataSet.h"
#include "../include/imebra/tag.h"
#include "../include/imebra/lut.h"
#include "../include/imebra/date.h"
#include "../implementation/dataSetImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include "../implementation/charsetConversionBaseImpl.h"
#include <typeinfo>
#include <memory>

namespace imebra
{

DataSet::DataSet(const DataSet& source): m_pDataSet(getDataSetImplementation(source))
{
}

DataSet::DataSet(const std::shared_ptr<imebra::implementation::dataSet>& pDataSet): m_pDataSet(pDataSet)
{
    if(pDataSet == 0)
    {
        m_pDataSet = std::make_shared<imebra::implementation::dataSet>();
    }
}

DataSet& DataSet::operator=(const DataSet& source)
{
    m_pDataSet = getDataSetImplementation(source);
    return *this;
}

DataSet::~DataSet()
{
}

const std::shared_ptr<implementation::dataSet>& getDataSetImplementation(const DataSet& dataSet)
{
    return dataSet.m_pDataSet;
}

tagsIds_t DataSet::getTags() const
{
    tagsIds_t returnTags;

    implementation::dataSet::tGroupsIds groups = m_pDataSet->getGroups();
    for(implementation::dataSet::tGroupsIds::const_iterator scanGroups(groups.begin()), endGroups(groups.end());
        scanGroups != endGroups;
        ++scanGroups)
    {
        std::uint32_t orders = m_pDataSet->getGroupsNumber(*scanGroups);
        for(std::uint32_t scanOrders(0); scanOrders != orders; ++scanOrders)
        {
            const implementation::dataSet::tTags tags = m_pDataSet->getGroupTags(*scanGroups, scanOrders);
            for(implementation::dataSet::tTags::const_iterator scanTags(tags.begin()), endTags(tags.end());
                scanTags != endTags;
                ++scanTags)
            {
                returnTags.push_back(TagId(*scanGroups, scanOrders, scanTags->first));
            }
        }
    }

    return returnTags;
}

const Tag DataSet::getTag(const TagId& tagId) const
{
    return Tag(m_pDataSet->getTag(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId()));
}

const Image DataSet::getImage(size_t frameNumber) const
{
    return Image(m_pDataSet->getImage((std::uint32_t)frameNumber));
}

const Image DataSet::getImageApplyModalityTransform(size_t frameNumber) const
{
    return Image(m_pDataSet->getModalityImage((std::uint32_t)frameNumber));
}

const DataSet DataSet::getSequenceItem(const TagId& tagId, size_t itemId) const
{
    return DataSet(m_pDataSet->getSequenceItem(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), itemId));
}

const LUT DataSet::getLUT(const TagId &tagId, size_t itemId) const
{
    return LUT(m_pDataSet->getLut(tagId.getGroupId(), tagId.getTagId(), itemId));
}

vois_t DataSet::getVOIs() const
{
    return m_pDataSet->getVOIs();
}

ReadingDataHandler DataSet::getReadingDataHandler(const TagId& tagId, size_t bufferId) const
{
    return ReadingDataHandler(m_pDataSet->getReadingDataHandler(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId));
}

ReadingDataHandlerNumeric DataSet::getReadingDataHandlerNumeric(const TagId& tagId, size_t bufferId) const
{
    return ReadingDataHandlerNumeric(m_pDataSet->getReadingDataHandlerNumeric(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId));
}

ReadingDataHandlerNumeric DataSet::getReadingDataHandlerRaw(const TagId& tagId, size_t bufferId) const
{
    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericHandler = m_pDataSet->getReadingDataHandlerRaw(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId);
    return ReadingDataHandlerNumeric(numericHandler);
}

bool DataSet::bufferExists(const TagId& tagId, size_t bufferId) const
{
    return m_pDataSet->bufferExists(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId);
}

std::int32_t DataSet::getSignedLong(const TagId& tagId, size_t elementNumber) const
{
    return m_pDataSet->getSignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);
}

std::int32_t DataSet::getSignedLong(const TagId& tagId, size_t elementNumber, std::int32_t defaultValue) const
{
    return m_pDataSet->getSignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);
}

std::uint32_t DataSet::getUnsignedLong(const TagId& tagId, size_t elementNumber) const
{
    return m_pDataSet->getUnsignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);
}

std::uint32_t DataSet::getUnsignedLong(const TagId& tagId, size_t elementNumber, std::uint32_t defaultValue) const
{
    return m_pDataSet->getUnsignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);
}

double DataSet::getDouble(const TagId& tagId, size_t elementNumber) const
{
    return m_pDataSet->getDouble(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);
}

double DataSet::getDouble(const TagId& tagId, size_t elementNumber, double defaultValue) const
{
    return m_pDataSet->getDouble(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);
}

std::string DataSet::getString(const TagId& tagId, size_t elementNumber) const
{
    return m_pDataSet->getString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);
}

std::string DataSet::getString(const TagId& tagId, size_t elementNumber, const std::string& defaultValue) const
{
    return m_pDataSet->getString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);
}

std::wstring DataSet::getUnicodeString(const TagId& tagId, size_t elementNumber) const
{
    return m_pDataSet->getUnicodeString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber);
}

std::wstring DataSet::getUnicodeString(const TagId& tagId, size_t elementNumber, const std::wstring& defaultValue) const
{
    return m_pDataSet->getUnicodeString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, defaultValue);
}

const Age DataSet::getAge(const TagId& tagId, size_t elementNumber) const
{
    imebra::ageUnit_t units;
    std::uint32_t age = m_pDataSet->getAge(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, &units);
    return Age(age, units);
}

const Age DataSet::getAge(const TagId& tagId, size_t elementNumber, const Age& defaultValue) const
{
    imebra::ageUnit_t units;
    std::uint32_t age = m_pDataSet->getAge(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, &units, defaultValue.age, defaultValue.units);
    return Age(age, units);
}

const Date DataSet::getDate(const TagId& tagId, size_t elementNumber) const
{
    return Date(m_pDataSet->getDate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber));
}

const Date DataSet::getDate(const TagId& tagId, size_t elementNumber, const Date& defaultValue) const
{
    return Date(m_pDataSet->getDate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, elementNumber, getDateImplementation(defaultValue)));
}


tagVR_t DataSet::getDataType(const TagId& tagId) const
{
    return m_pDataSet->getDataType(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId());
}

MutableDataSet::MutableDataSet(const MutableDataSet &source): DataSet(source)
{
}

MutableDataSet::MutableDataSet(): DataSet(std::make_shared<imebra::implementation::dataSet>())
{
    implementation::charsetsList::tCharsetsList list;
    list.push_back("ISO 2022 IR 6");
    getDataSetImplementation(*this)->setCharsetsList(list);
}

MutableDataSet::MutableDataSet(const std::shared_ptr<implementation::dataSet>& pDataSet): DataSet(pDataSet)
{
}

MutableDataSet::MutableDataSet(const std::string &transferSyntax): DataSet(std::make_shared<imebra::implementation::dataSet>(transferSyntax))
{
    implementation::charsetsList::tCharsetsList list;
    list.push_back("ISO 2022 IR 6");
    getDataSetImplementation(*this)->setCharsetsList(list);
}

MutableDataSet::MutableDataSet(const std::string &transferSyntax, const charsetsList_t &charsets): DataSet(std::make_shared<imebra::implementation::dataSet>(transferSyntax))
{
    implementation::charsetsList::tCharsetsList list;
    for(charsetsList_t::const_iterator scanCharsets(charsets.begin()), endCharsets(charsets.end()); scanCharsets != endCharsets; ++scanCharsets)
    {
        list.push_back(*scanCharsets);
    }
    getDataSetImplementation(*this)->setCharsetsList(list);
}

MutableDataSet& MutableDataSet::operator=(const MutableDataSet& source)
{
    DataSet::operator =(source);
    return *this;
}

MutableTag MutableDataSet::getTagCreate(const TagId& tagId, tagVR_t tagVR)
{
    return MutableTag(getDataSetImplementation(*this)->getTagCreate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), tagVR));
}

MutableTag MutableDataSet::getTagCreate(const TagId& tagId)
{
    return MutableTag(getDataSetImplementation(*this)->getTagCreate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId()));
}

WritingDataHandler MutableDataSet::getWritingDataHandler(const TagId& tagId, size_t bufferId, tagVR_t tagVR)
{
    return WritingDataHandler(getDataSetImplementation(*this)->getWritingDataHandler(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, tagVR));
}

WritingDataHandler MutableDataSet::getWritingDataHandler(const TagId& tagId, size_t bufferId)
{
    return WritingDataHandler(getDataSetImplementation(*this)->getWritingDataHandler(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId));
}

WritingDataHandlerNumeric MutableDataSet::getWritingDataHandlerNumeric(const TagId& tagId, size_t bufferId, tagVR_t tagVR)
{
    return WritingDataHandlerNumeric(getDataSetImplementation(*this)->getWritingDataHandlerNumeric(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, tagVR));
}

WritingDataHandlerNumeric MutableDataSet::getWritingDataHandlerNumeric(const TagId& tagId, size_t bufferId)
{
    return WritingDataHandlerNumeric(getDataSetImplementation(*this)->getWritingDataHandlerNumeric(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId));
}

WritingDataHandlerNumeric MutableDataSet::getWritingDataHandlerRaw(const TagId& tagId, size_t bufferId, tagVR_t tagVR)
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericHandler = getDataSetImplementation(*this)->getWritingDataHandlerRaw(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId, tagVR);
    return WritingDataHandlerNumeric(numericHandler);
}

WritingDataHandlerNumeric MutableDataSet::getWritingDataHandlerRaw(const TagId& tagId, size_t bufferId)
{
    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericHandler = getDataSetImplementation(*this)->getWritingDataHandlerRaw(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), bufferId);
    return WritingDataHandlerNumeric(numericHandler);
}

void MutableDataSet::setImage(size_t frameNumber, const Image& image, imageQuality_t quality)
{
    getDataSetImplementation(*this)->setImage((std::uint32_t)frameNumber, getImageImplementation(image), quality);
}

MutableDataSet MutableDataSet::appendSequenceItem(const TagId &tagId)
{
    return MutableDataSet(getDataSetImplementation(*this)->appendSequenceItem(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId()));
}

void MutableDataSet::setSignedLong(const TagId& tagId, std::int32_t newValue, tagVR_t tagVR)
{
    getDataSetImplementation(*this)->setSignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue, tagVR);
}

void MutableDataSet::setSignedLong(const TagId& tagId, std::int32_t newValue)
{
    getDataSetImplementation(*this)->setSignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue);
}

void MutableDataSet::setUnsignedLong(const TagId& tagId, std::uint32_t newValue, tagVR_t tagVR)
{
    getDataSetImplementation(*this)->setUnsignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue, tagVR);
}

void MutableDataSet::setUnsignedLong(const TagId& tagId, std::uint32_t newValue)
{
    getDataSetImplementation(*this)->setUnsignedLong(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue);
}

void MutableDataSet::setDouble(const TagId& tagId, double newValue, tagVR_t tagVR)
{
    getDataSetImplementation(*this)->setDouble(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue, tagVR);
}

void MutableDataSet::setDouble(const TagId& tagId, double newValue)
{
    getDataSetImplementation(*this)->setDouble(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newValue);
}

void MutableDataSet::setString(const TagId& tagId, const std::string& newString, tagVR_t tagVR)
{
    getDataSetImplementation(*this)->setString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newString, tagVR);
}

void MutableDataSet::setString(const TagId& tagId, const std::string& newString)
{
    getDataSetImplementation(*this)->setString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newString);
}

void MutableDataSet::setUnicodeString(const TagId& tagId, const std::wstring& newString, tagVR_t tagVR)
{
    getDataSetImplementation(*this)->setUnicodeString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newString, tagVR);
}

void MutableDataSet::setUnicodeString(const TagId& tagId, const std::wstring& newString)
{
    getDataSetImplementation(*this)->setUnicodeString(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, newString);
}

void MutableDataSet::setAge(const TagId& tagId, const Age& age)
{
    getDataSetImplementation(*this)->setAge(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, age.age, age.units);
}

void MutableDataSet::setDate(const TagId& tagId, const Date& date, tagVR_t tagVR)
{
    getDataSetImplementation(*this)->setDate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, getDateImplementation(date), tagVR);
}

void MutableDataSet::setDate(const TagId& tagId, const Date& date)
{
    getDataSetImplementation(*this)->setDate(tagId.getGroupId(), tagId.getGroupOrder(), tagId.getTagId(), 0, getDateImplementation(date));
}

}
