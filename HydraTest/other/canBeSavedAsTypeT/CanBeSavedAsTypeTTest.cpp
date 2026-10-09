#include <exception>
#include <limits>
#include <sstream>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/external/unitTesting/Catch2/catch.hpp"
#include "HydraTest/other/canBeSavedAsTypeT/CanBeSavedAsTypeTTestResult.hpp"

#include "Hydra/other/Other.hpp"

namespace HydraTest::Other::CanBeSavedAsTypeT {

    //region Types
    using LargeNumberType = Hydra::Other::LargeNumberType;
    //endregion

    //region Constants
    // The maximum value of char8_t, char16_t, and char32_t
    constexpr LargeNumberType MAX_VALUE_CHAR8_T = std::numeric_limits<char8_t>::max();     //           255
    constexpr LargeNumberType MAX_VALUE_CHAR16_T = std::numeric_limits<char16_t>::max();   //        65'535
    constexpr LargeNumberType MAX_VALUE_CHAR32_T = std::numeric_limits<char32_t>::max();   // 4'294'967'295

    // Half of the maximum value of char8_t, char16_t, and char32_t
    constexpr LargeNumberType HALF_OF_MAX_VALUE_CHAR8_T = MAX_VALUE_CHAR8_T / 2;     //           127
    constexpr LargeNumberType HALF_OF_MAX_VALUE_CHAR16_T = MAX_VALUE_CHAR16_T / 2;   //        32'767
    constexpr LargeNumberType HALF_OF_MAX_VALUE_CHAR32_T = MAX_VALUE_CHAR32_T / 2;   // 2'147'483'647
    //endregion

    /**
     * Variables
     */
    TEST_CASE("[Other::CanBeSavedAsTypeT] variables", "[Other::CanBeSavedAsTypeT]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          canBeSavedAsTypeTVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            // char8_t
            actualResult << "char8_t - " << std::to_string(MAX_VALUE_CHAR8_T - 1) << ": "
                         << std::to_string(Hydra::Other::variablesCanBeSavedAsTypeT<char8_t>(MAX_VALUE_CHAR8_T - 1)) << std::endl;
            actualResult << "char8_t - " << std::to_string(MAX_VALUE_CHAR8_T) << ": "
                         << std::to_string(Hydra::Other::variablesCanBeSavedAsTypeT<char8_t>(MAX_VALUE_CHAR8_T)) << std::endl
                         << std::endl;

            // char16_t
            actualResult << "char16_t - " << std::to_string(MAX_VALUE_CHAR16_T - 1) << ": "
                         << std::to_string(Hydra::Other::variablesCanBeSavedAsTypeT<char16_t>(MAX_VALUE_CHAR16_T - 1)) << std::endl;
            actualResult << "char16_t - " << std::to_string(MAX_VALUE_CHAR16_T) << ": "
                         << std::to_string(Hydra::Other::variablesCanBeSavedAsTypeT<char16_t>(MAX_VALUE_CHAR16_T)) << std::endl
                         << std::endl;

            // char32_t
            actualResult << "char32_t - " << std::to_string(MAX_VALUE_CHAR32_T - 1) << ": "
                         << std::to_string(Hydra::Other::variablesCanBeSavedAsTypeT<char32_t>(MAX_VALUE_CHAR32_T - 1)) << std::endl;
            actualResult << "char32_t - " << std::to_string(MAX_VALUE_CHAR32_T) << ": "
                         << std::to_string(Hydra::Other::variablesCanBeSavedAsTypeT<char32_t>(MAX_VALUE_CHAR32_T)) << std::endl
                         << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Variables (cache)
     */
    TEST_CASE("[Other::CanBeSavedAsTypeT] variables (cache)", "[Other::CanBeSavedAsTypeT]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          canBeSavedAsTypeTVariablesForCacheResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            // char8_t
            actualResult << "char8_t - " << std::to_string(MAX_VALUE_CHAR8_T) << ": "
                         << std::to_string(Hydra::Other::variablesCanBeSavedAsTypeTForCache<char8_t>(MAX_VALUE_CHAR8_T)) << std::endl;
            actualResult << "char8_t - " << std::to_string(MAX_VALUE_CHAR8_T + 1) << ": "
                         << std::to_string(Hydra::Other::variablesCanBeSavedAsTypeTForCache<char8_t>(MAX_VALUE_CHAR8_T + 1)) << std::endl
                         << std::endl;

            // char16_t
            actualResult << "char16_t - " << std::to_string(MAX_VALUE_CHAR16_T) << ": "
                         << std::to_string(Hydra::Other::variablesCanBeSavedAsTypeTForCache<char16_t>(MAX_VALUE_CHAR16_T)) << std::endl;
            actualResult << "char16_t - " << std::to_string(MAX_VALUE_CHAR16_T + 1) << ": "
                         << std::to_string(Hydra::Other::variablesCanBeSavedAsTypeTForCache<char16_t>(MAX_VALUE_CHAR16_T + 1)) << std::endl
                         << std::endl;

            // char32_t
            actualResult << "char32_t - " << std::to_string(MAX_VALUE_CHAR32_T) << ": "
                         << std::to_string(Hydra::Other::variablesCanBeSavedAsTypeTForCache<char32_t>(MAX_VALUE_CHAR32_T)) << std::endl;
            actualResult << "char32_t - " << std::to_string(MAX_VALUE_CHAR32_T + 1) << ": "
                         << std::to_string(Hydra::Other::variablesCanBeSavedAsTypeTForCache<char32_t>(MAX_VALUE_CHAR32_T + 1)) << std::endl
                         << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Literals
     */
    TEST_CASE("[Other::CanBeSavedAsTypeT] literals", "[Other::CanBeSavedAsTypeT]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          canBeSavedAsTypeTLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            // char8_t
            actualResult << "char8_t - " << std::to_string(HALF_OF_MAX_VALUE_CHAR8_T - 1) << ": "
                         << std::to_string(Hydra::Other::literalsCanBeSavedAsTypeT<char8_t>(HALF_OF_MAX_VALUE_CHAR8_T - 1)) << std::endl;
            actualResult << "char8_t - " << std::to_string(HALF_OF_MAX_VALUE_CHAR8_T) << ": "
                         << std::to_string(Hydra::Other::literalsCanBeSavedAsTypeT<char8_t>(HALF_OF_MAX_VALUE_CHAR8_T)) << std::endl
                         << std::endl;

            // char16_t
            actualResult << "char16_t - " << std::to_string(HALF_OF_MAX_VALUE_CHAR16_T - 1) << ": "
                         << std::to_string(Hydra::Other::literalsCanBeSavedAsTypeT<char16_t>(HALF_OF_MAX_VALUE_CHAR16_T - 1)) << std::endl;
            actualResult << "char16_t - " << std::to_string(HALF_OF_MAX_VALUE_CHAR16_T) << ": "
                         << std::to_string(Hydra::Other::literalsCanBeSavedAsTypeT<char16_t>(HALF_OF_MAX_VALUE_CHAR16_T)) << std::endl
                         << std::endl;

            // char32_t
            actualResult << "char32_t - " << std::to_string(HALF_OF_MAX_VALUE_CHAR32_T - 1) << ": "
                         << std::to_string(Hydra::Other::literalsCanBeSavedAsTypeT<char32_t>(HALF_OF_MAX_VALUE_CHAR32_T - 1)) << std::endl;
            actualResult << "char32_t - " << std::to_string(HALF_OF_MAX_VALUE_CHAR32_T) << ": "
                         << std::to_string(Hydra::Other::literalsCanBeSavedAsTypeT<char32_t>(HALF_OF_MAX_VALUE_CHAR32_T)) << std::endl
                         << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Literals (cache)
     */
    TEST_CASE("[Other::CanBeSavedAsTypeT] literals (cache)", "[Other::CanBeSavedAsTypeT]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          canBeSavedAsTypeTLiteralsForCacheResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            // char8_t
            actualResult << "char8_t - " << std::to_string(HALF_OF_MAX_VALUE_CHAR8_T) << ": "
                         << std::to_string(Hydra::Other::literalsCanBeSavedAsTypeTForCache<char8_t>(HALF_OF_MAX_VALUE_CHAR8_T)) << std::endl;
            actualResult << "char8_t - " << std::to_string(HALF_OF_MAX_VALUE_CHAR8_T + 1) << ": "
                         << std::to_string(Hydra::Other::literalsCanBeSavedAsTypeTForCache<char8_t>(HALF_OF_MAX_VALUE_CHAR8_T + 1)) << std::endl
                         << std::endl;

            // char16_t
            actualResult << "char16_t - " << std::to_string(HALF_OF_MAX_VALUE_CHAR16_T) << ": "
                         << std::to_string(Hydra::Other::literalsCanBeSavedAsTypeTForCache<char16_t>(HALF_OF_MAX_VALUE_CHAR16_T)) << std::endl;
            actualResult << "char16_t - " << std::to_string(HALF_OF_MAX_VALUE_CHAR16_T + 1) << ": "
                         << std::to_string(Hydra::Other::literalsCanBeSavedAsTypeTForCache<char16_t>(HALF_OF_MAX_VALUE_CHAR16_T + 1)) << std::endl
                         << std::endl;

            // char32_t
            actualResult << "char32_t - " << std::to_string(HALF_OF_MAX_VALUE_CHAR32_T) << ": "
                         << std::to_string(Hydra::Other::literalsCanBeSavedAsTypeTForCache<char32_t>(HALF_OF_MAX_VALUE_CHAR32_T)) << std::endl;
            actualResult << "char32_t - " << std::to_string(HALF_OF_MAX_VALUE_CHAR32_T + 1) << ": "
                         << std::to_string(Hydra::Other::literalsCanBeSavedAsTypeTForCache<char32_t>(HALF_OF_MAX_VALUE_CHAR32_T + 1)) << std::endl
                         << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clause identifiers
     */
    TEST_CASE("[Other::CanBeSavedAsTypeT] clause identifiers", "[Other::CanBeSavedAsTypeT]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          canBeSavedAsTypeTClauseIdentifiersResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            // char8_t
            actualResult << "char8_t - " << std::to_string(MAX_VALUE_CHAR8_T) << ": "
                         << std::to_string(Hydra::Other::clauseIdCanBeSavedAsTypeT<char8_t>(MAX_VALUE_CHAR8_T)) << std::endl;
            actualResult << "char8_t - " << std::to_string(MAX_VALUE_CHAR8_T + 1) << ": "
                         << std::to_string(Hydra::Other::clauseIdCanBeSavedAsTypeT<char8_t>(MAX_VALUE_CHAR8_T + 1)) << std::endl
                         << std::endl;

            // char16_t
            actualResult << "char16_t - " << std::to_string(MAX_VALUE_CHAR16_T) << ": "
                         << std::to_string(Hydra::Other::clauseIdCanBeSavedAsTypeT<char16_t>(MAX_VALUE_CHAR16_T)) << std::endl;
            actualResult << "char16_t - " << std::to_string(MAX_VALUE_CHAR16_T + 1) << ": "
                         << std::to_string(Hydra::Other::clauseIdCanBeSavedAsTypeT<char16_t>(MAX_VALUE_CHAR16_T + 1)) << std::endl
                         << std::endl;

            // char32_t
            actualResult << "char32_t - " << std::to_string(MAX_VALUE_CHAR32_T) << ": "
                         << std::to_string(Hydra::Other::clauseIdCanBeSavedAsTypeT<char32_t>(MAX_VALUE_CHAR32_T)) << std::endl;
            actualResult << "char32_t - " << std::to_string(MAX_VALUE_CHAR32_T + 1) << ": "
                         << std::to_string(Hydra::Other::clauseIdCanBeSavedAsTypeT<char32_t>(MAX_VALUE_CHAR32_T + 1)) << std::endl
                         << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Other::CanBeSavedAsTypeT
