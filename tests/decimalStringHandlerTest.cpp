#include <imebra/imebra.h>
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

TEST(decimalStringHandlerTest, decimalTest)
{
    DataSet testDataSet;
    {
        testDataSet.setDouble(TagId(0x0028, 0x1051), 0, 0.000001, "DS");
        std::string decimalString = testDataSet.getStringThrow(TagId(0x0028, 0x1051), 0, 0);
        ASSERT_TRUE(decimalString == "1e-006" || decimalString == "1e-06" || decimalString == "1e-6");
        double decimalValue = testDataSet.getDoubleThrow(TagId(0x0028, 0x1051), 0, 0);
        ASSERT_FLOAT_EQ(0.000001, decimalValue);
    }

    {
        testDataSet.setString(TagId(0x0028, 0x1051), 0, "-2e-8", "DS");
        double decimalValue = testDataSet.getDoubleThrow(TagId(0x0028, 0x1051), 0, 0);
        ASSERT_FLOAT_EQ(-0.00000002, decimalValue);
    }
}

TEST(decimalStringHandlerTest, decimalTestFail)
{
    DataSet testDataSet;
    testDataSet.setString(TagId(0x0028, 0x1051), 0, "Hello", "DS");
    ASSERT_THROW(testDataSet.getDoubleThrow(TagId(0x0028, 0x1051), 0, 0), DataHandlerConversionError);
}



} // namespace tests

} // namespace imebra
