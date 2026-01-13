#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/statistics/StatisticsTestResult.hpp"

#include "Hydra/statistics/StatisticsAbstract.hpp"
#include "Hydra/statistics/component/CounterStatistics.hpp"
#include "Hydra/statistics/component/NumberStatistics.hpp"
#include "Hydra/statistics/component/TimerStatistics.hpp"

namespace HydraTest::Statistics {

    using LargeNumberType = Hydra::Statistics::LargeNumberType;
    using LargeFloatingNumberType = Hydra::Statistics::LargeFloatingNumberType;

    //region Types
    using TimerStatisticsType = typename Hydra::Statistics::StatisticsAbstract::TimerStatisticsType;
    using NumberStatisticsType = typename Hydra::Statistics::StatisticsAbstract::NumberStatisticsType;
    using NanoTimerStatisticsType = typename Hydra::Statistics::StatisticsAbstract::NanoTimerStatisticsType;
    using RealNumberStatisticsType = typename Hydra::Statistics::StatisticsAbstract::RealNumberStatisticsType;
    using MilliTimerStatisticsType = typename Hydra::Statistics::StatisticsAbstract::MilliTimerStatisticsType;
    using MicroTimerStatisticsType = typename Hydra::Statistics::StatisticsAbstract::MicroTimerStatisticsType;
    using NumberCounterStatisticsType = typename Hydra::Statistics::StatisticsAbstract::NumberCounterStatisticsType;
    using RealNumberCounterStatisticsType = typename Hydra::Statistics::StatisticsAbstract::RealNumberCounterStatisticsType;

    using LargeNumberVectorType = std::vector<LargeNumberType>;
    using LargeFloatingNumberVectorType = std::vector<LargeFloatingNumberType>;
    //endregion

    #if defined(BELLA_COMPILER)
    /**
     * Number counter
     */
    TEST_CASE("[Statistics] number counter", "[Statistics]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          statisticsNumberCounterResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            NumberCounterStatisticsType counter("number counter");
            counter.printCounterStatistics(actualResult, "", true);
            actualResult << std::endl;

            LargeNumberVectorType largeNumberVector { 3, 1, 2, 0, 3, 3, 100, 9999 };

            for (LargeNumberType largeNumber : largeNumberVector) {
                actualResult << "Add: " << std::to_string(largeNumber) << std::endl;

                counter.addCount(largeNumber);
                counter.printCounterStatistics(actualResult, "", false);

                actualResult << "--------------------" << std::endl;
                actualResult << std::endl;
            }

            counter.printCounterStatistics(actualResult, "", true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Real number counter
     */
    TEST_CASE("[Statistics] real number counter", "[Statistics]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          statisticsRealNumberCounterResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            RealNumberCounterStatisticsType counter("real number counter");
            counter.printCounterStatistics(actualResult, "", true);
            actualResult << std::endl;

            LargeFloatingNumberVectorType largeFloatingNumberVector { 3.5, 1, 2.1, 0, 3.8, 3.7, 100, 9999 };

            for (LargeFloatingNumberType largeFloatingNumber : largeFloatingNumberVector) {
                actualResult << "Add: " << std::to_string(largeFloatingNumber) << std::endl;

                counter.addCount(largeFloatingNumber);
                counter.printCounterStatistics(actualResult, "", false);

                actualResult << "--------------------" << std::endl;
                actualResult << std::endl;
            }

            counter.printCounterStatistics(actualResult, "", true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Number
     */
    TEST_CASE("[Statistics] number", "[Statistics]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          statisticsNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            NumberStatisticsType number("number", false);
            number.printNumberStatistics(actualResult, "", true);
            actualResult << std::endl;

            LargeNumberVectorType largeNumberVector { 3, 1, 2, 0, 3, 3, 100, 9999 };

            for (LargeNumberType largeNumber : largeNumberVector) {
                actualResult << "Set: " << std::to_string(largeNumber) << std::endl;

                number.setNumber(largeNumber);
                number.printNumberStatistics(actualResult, "", false);

                actualResult << "--------------------" << std::endl;
                actualResult << std::endl;
            }

            number.printNumberStatistics(actualResult, "", true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Number (reset)
     */
    TEST_CASE("[Statistics] number (reset)", "[Statistics]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          statisticsNumberResetResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            NumberStatisticsType number("number", true);
            number.printNumberStatistics(actualResult, "", true);
            actualResult << std::endl;

            LargeNumberVectorType largeNumberVector { 3, 1, 2, 0, 3, 3, 100, 9999 };

            for (LargeNumberType largeNumber : largeNumberVector) {
                actualResult << "Set: " << std::to_string(largeNumber) << std::endl;

                number.setNumber(largeNumber);
                number.printNumberStatistics(actualResult, "", false);

                actualResult << "--------------------" << std::endl;
                actualResult << std::endl;
            }

            number.printNumberStatistics(actualResult, "", true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Number (increment)
     */
    TEST_CASE("[Statistics] number (increment)", "[Statistics]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          statisticsNumberIncrementResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            NumberStatisticsType number("number", true);
            number.printNumberStatistics(actualResult, "", true);
            actualResult << std::endl;

            LargeNumberVectorType largeNumberVector { 3, 1, 2, 0, 3, 3, 100, 9999 };

            for (LargeNumberType largeNumber : largeNumberVector) {
                actualResult << "Set: " << std::to_string(largeNumber) << std::endl;

                number.setNumber(largeNumber);
                number.printNumberStatistics(actualResult, "", false);
                actualResult << std::endl;

                for (std::size_t i = 0; i < 3; ++i) {
                    actualResult << "Increment" << std::endl;

                    number.incrementNumber();
                    number.printNumberStatistics(actualResult, "", false);
                    actualResult << std::endl;
                }

                actualResult << "--------------------" << std::endl;
                actualResult << std::endl;
            }

            number.printNumberStatistics(actualResult, "", true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Number (increment - number)
     */
    TEST_CASE("[Statistics] number (increment - number)", "[Statistics]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          statisticsNumberIncrementNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            NumberStatisticsType number("number", true);
            number.printNumberStatistics(actualResult, "", true);
            actualResult << std::endl;

            number.setNumber(static_cast<Statistics::LargeNumberType>(0));

            LargeNumberVectorType largeNumberVector { 3, 1, 2, 0, 3, 3, 100, 9999 };

            for (LargeNumberType largeNumber : largeNumberVector) {
                actualResult << "Increment: " << std::to_string(largeNumber) << std::endl;

                number.incrementNumber(largeNumber);
                number.printNumberStatistics(actualResult, "", false);

                actualResult << "--------------------" << std::endl;
                actualResult << std::endl;
            }

            number.printNumberStatistics(actualResult, "", true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Real number
     */
    TEST_CASE("[Statistics] real number", "[Statistics]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          statisticsRealNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            RealNumberStatisticsType number("real number", false);
            number.printNumberStatistics(actualResult, "", true);
            actualResult << std::endl;

            LargeFloatingNumberVectorType largeFloatingNumberVector { 3.5, 1, 2.1, 0, 3.8, 3.7, 100, 9999 };

            for (LargeFloatingNumberType largeFloatingNumber : largeFloatingNumberVector) {
                actualResult << "Set: " << std::to_string(largeFloatingNumber) << std::endl;

                number.setNumber(largeFloatingNumber);
                number.printNumberStatistics(actualResult, "", false);

                actualResult << "--------------------" << std::endl;
                actualResult << std::endl;
            }

            number.printNumberStatistics(actualResult, "", true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Real number (reset)
     */
    TEST_CASE("[Statistics] real number (reset)", "[Statistics]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          statisticsRealNumberResetResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            RealNumberStatisticsType number("real number", true);
            number.printNumberStatistics(actualResult, "", true);
            actualResult << std::endl;

            LargeFloatingNumberVectorType largeFloatingNumberVector { 3.5, 1, 2.1, 0, 3.8, 3.7, 100, 9999 };

            for (LargeFloatingNumberType largeFloatingNumber : largeFloatingNumberVector) {
                actualResult << "Set: " << std::to_string(largeFloatingNumber) << std::endl;

                number.setNumber(largeFloatingNumber);
                number.printNumberStatistics(actualResult, "", false);

                actualResult << "--------------------" << std::endl;
                actualResult << std::endl;
            }

            number.printNumberStatistics(actualResult, "", true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Timer (seconds)
     */
    TEST_CASE("[Statistics] timer (seconds)", "[Statistics]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          statisticsTimerSecondsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            TimerStatisticsType timer("timer - seconds");
            timer.printTimerStatistics(actualResult, "", true);

            actualResult << std::endl;

            timer.printTimerStatistics(actualResult, "", false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Timer (milliseconds)
     */
    TEST_CASE("[Statistics] timer (milliseconds)", "[Statistics]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          statisticsTimerMillisecondsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            MilliTimerStatisticsType timer("timer - milliseconds");
            timer.printTimerStatistics(actualResult, "", true);

            actualResult << std::endl;

            timer.printTimerStatistics(actualResult, "", false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Timer (microseconds)
     */
    TEST_CASE("[Statistics] timer (microseconds)", "[Statistics]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          statisticsTimerMicrosecondsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            MicroTimerStatisticsType timer("timer - microseconds");
            timer.printTimerStatistics(actualResult, "", true);

            actualResult << std::endl;

            timer.printTimerStatistics(actualResult, "", false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Timer (nanoseconds)
     */
    TEST_CASE("[Statistics] timer (nanoseconds)", "[Statistics]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          statisticsTimerNanosecondsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            NanoTimerStatisticsType timer("timer - nanoseconds");
            timer.printTimerStatistics(actualResult, "", true);

            actualResult << std::endl;

            timer.printTimerStatistics(actualResult, "", false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif
}   // namespace HydraTest::Statistics
