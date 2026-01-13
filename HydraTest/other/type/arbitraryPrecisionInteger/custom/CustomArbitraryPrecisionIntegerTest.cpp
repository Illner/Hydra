#include <cassert>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/other/type/arbitraryPrecisionInteger/custom/CustomArbitraryPrecisionIntegerTestResult.hpp"

#include "Hydra/other/type/arbitraryPrecisionInteger/custom/CustomArbitraryPrecisionInteger.hpp"

namespace HydraTest::Type::ArbitraryPrecisionInteger::Custom {

    //region Types
    using StringVectorType = std::vector<std::string>;

    using CustomArbitraryPrecisionIntegerType = Hydra::Type::ArbitraryPrecisionInteger::Custom::CustomArbitraryPrecisionInteger;

    using PositionType = typename CustomArbitraryPrecisionIntegerType::PositionType;
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[Type::ArbitraryPrecisionInteger::Custom] constructor", "[Type::ArbitraryPrecisionInteger::Custom]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          customArbitraryPrecisionIntegerConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            CustomArbitraryPrecisionIntegerType number;
            actualResult << number << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Constructor (string)
     */
    TEST_CASE("[Type::ArbitraryPrecisionInteger::Custom] constructor (string)", "[Type::ArbitraryPrecisionInteger::Custom]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          customArbitraryPrecisionIntegerConstructorStringResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StringVectorType numberStringVector { "0", "1", "9", "10", "99", "100", "12345",
                                                  "354224848179261915075", "896519947090131496687170070074100632420837521538745909320",
                                                  "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000" };

            for (const std::string& numberString : numberStringVector) {
                CustomArbitraryPrecisionIntegerType number(numberString);
                actualResult << number << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Size
     */
    TEST_CASE("[Type::ArbitraryPrecisionInteger::Custom] size", "[Type::ArbitraryPrecisionInteger::Custom]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          customArbitraryPrecisionIntegerSizeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StringVectorType numberStringVector { "0", "1", "9", "10", "99", "100", "999",
                                                  "354224848179261915075", "896519947090131496687170070074100632420837521538745909320",
                                                  "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000" };

            for (const std::string& numberString : numberStringVector) {
                CustomArbitraryPrecisionIntegerType number(numberString);
                actualResult << number << ": ";

                PositionType size = number.size();
                actualResult << std::to_string(size) << " digits" << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Is zero
     */
    TEST_CASE("[Type::ArbitraryPrecisionInteger::Custom] is zero", "[Type::ArbitraryPrecisionInteger::Custom]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          customArbitraryPrecisionIntegerIsZeroResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StringVectorType numberStringVector { "0", "10", "99", "100", "999", "1000", "9999" };

            for (const std::string& numberString : numberStringVector) {
                CustomArbitraryPrecisionIntegerType number(numberString);
                actualResult << number << ": ";

                bool isZero = number.isZero();
                actualResult << std::to_string(isZero) << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Increment
     */
    TEST_CASE("[Type::ArbitraryPrecisionInteger::Custom] increment", "[Type::ArbitraryPrecisionInteger::Custom]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          customArbitraryPrecisionIntegerIncrementResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StringVectorType numberStringVector { "0", "1", "9", "10", "89", "98", "99", "199" };

            for (const std::string& numberString : numberStringVector) {
                CustomArbitraryPrecisionIntegerType number(numberString);
                actualResult << number << " -> ";

                ++number;
                actualResult << number << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Addition assignment
     */
    TEST_CASE("[Type::ArbitraryPrecisionInteger::Custom] addition assignment", "[Type::ArbitraryPrecisionInteger::Custom]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          customArbitraryPrecisionIntegerAdditionAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StringVectorType numberStringVector1 { "0", "0", "1", "5", "1", "9", "1", "998", "999", "1", "11998", "2", "12345" };
            StringVectorType numberStringVector2 { "0", "1", "0", "4", "9", "1", "998", "1", "1", "999", "2", "11998", "67890" };

            assert(numberStringVector1.size() == numberStringVector2.size());

            for (StringVectorType::size_type i = 0; i < numberStringVector1.size(); ++i) {
                CustomArbitraryPrecisionIntegerType number1(numberStringVector1[i]);
                CustomArbitraryPrecisionIntegerType number2(numberStringVector2[i]);
                actualResult << number1 << " + " << number2 << " = ";

                number1 += number2;
                actualResult << number1 << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Addition assignment (big numbers)
     */
    TEST_CASE("[Type::ArbitraryPrecisionInteger::Custom] addition assignment (big numbers)", "[Type::ArbitraryPrecisionInteger::Custom]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          customArbitraryPrecisionIntegerAdditionAssignmentBigNumbersResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StringVectorType numberStringVector1 { "354224848179261915075", "1000134600800354781929399250536541864362461089950800",
                                                   "933262154439441526816992388562667004907159682643816214685929638952175999932299156089414639761565182862536979208272237582511852109168640000000000000000000000" };
            StringVectorType numberStringVector2 { "83621143489848422977", "896519947090131496687170070074100632420837521538745909320",
                                                   "991677934870949689209571401541893801158183648651267795444376054838492222809091499987689476037000748982075094738965754305639874560000000000000000000000" };

            assert(numberStringVector1.size() == numberStringVector2.size());

            for (StringVectorType::size_type i = 0; i < numberStringVector1.size(); ++i) {
                CustomArbitraryPrecisionIntegerType number1(numberStringVector1[i]);
                CustomArbitraryPrecisionIntegerType number2(numberStringVector2[i]);

                number1 += number2;
                actualResult << number1 << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Multiplication assignment
     */
    TEST_CASE("[Type::ArbitraryPrecisionInteger::Custom] multiplication assignment", "[Type::ArbitraryPrecisionInteger::Custom]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          customArbitraryPrecisionIntegerMultiplicationAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StringVectorType numberStringVector1 { "0", "0", "1", "5", "12", "6", "15", "7", "999", "9", "12345", "99999" };
            StringVectorType numberStringVector2 { "0", "1", "0", "4", "6", "12", "7", "15", "9", "999", "67890", "99999" };

            assert(numberStringVector1.size() == numberStringVector2.size());

            for (StringVectorType::size_type i = 0; i < numberStringVector1.size(); ++i) {
                CustomArbitraryPrecisionIntegerType number1(numberStringVector1[i]);
                CustomArbitraryPrecisionIntegerType number2(numberStringVector2[i]);
                actualResult << number1 << " * " << number2 << " = ";

                number1 *= number2;
                actualResult << number1 << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Multiplication assignment (big numbers)
     */
    TEST_CASE("[Type::ArbitraryPrecisionInteger::Custom] multiplication assignment (big numbers)", "[Type::ArbitraryPrecisionInteger::Custom]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          customArbitraryPrecisionIntegerMultiplicationAssignmentBigNumbersResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StringVectorType numberStringVector1 { "218922995834555169026", "3721443204405954385563870541379246659709506697378694300",
                                                   "9426890448883247745626185743057242473809693764078951663494238777294707070023223798882976159207729119823605850588608460429412647567360000000000000000000000" };
            StringVectorType numberStringVector2 { "51680708854858323072", "896519947090131496687170070074100632420837521538745909320",
                                                   "96192759682482119853328425949563698712343813919172976158104477319333745612481875498805879175589072651261284189679678167647067832320000000000000000000000" };

            assert(numberStringVector1.size() == numberStringVector2.size());

            for (StringVectorType::size_type i = 0; i < numberStringVector1.size(); ++i) {
                CustomArbitraryPrecisionIntegerType number1(numberStringVector1[i]);
                CustomArbitraryPrecisionIntegerType number2(numberStringVector2[i]);

                number1 *= number2;
                actualResult << number1 << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Type::ArbitraryPrecisionInteger::Custom
