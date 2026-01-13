#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/other/container/stackWithLevels/StackWithLevelsTestResult.hpp"

#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/stackWithLevels/StackWithLevels.hpp"
#include "Hydra/other/std/Std.hpp"

#include "Hydra/other/container/exceptions/StackWithLevelsException.hpp"

namespace HydraTest::Container::StackWithLevels {

    using LargeNumberType = Hydra::Container::StackWithLevels::LargeNumberType;

    //region Types
    using TypeT = char8_t;
    using LevelTypeT = char8_t;

    using TypeTVectorType = std::vector<TypeT>;
    using TypeTPairType = std::pair<TypeT, TypeT>;
    using TypeTPairVectorType = std::vector<TypeTPairType>;
    using StackWithLevelsType = Hydra::Container::StackWithLevels::StackWithLevels<TypeT, LevelTypeT>;
    using PairStackWithLevelsType = Hydra::Container::StackWithLevels::StackWithLevels<TypeTPairType, LevelTypeT>;
    //endregion

    //region Functions
    template <typename StackWithLevelsTypeT>
    void printStackWithLevels(const StackWithLevelsTypeT& stackWithLevels, std::stringstream& actualResult) {
        stackWithLevels.printStackWithLevelsDebug(actualResult);
        actualResult << std::endl;
    }

    template <typename StackWithLevelsTypeT, typename VectorTypeT>
    void addElementsAndLevels(StackWithLevelsTypeT& stackWithLevels, const VectorTypeT& elementVector, bool newLevels,
                              std::stringstream& actualResult, bool print = true) {
        std::size_t nextLevel = 1;
        std::size_t currentPosition = 0;

        for (auto element : elementVector) {
            if (print)
                actualResult << "Add element: " << std::to_string(element) << std::endl;

            try {
                stackWithLevels.addElement(element);

                ++currentPosition;
                if (nextLevel == currentPosition) {
                    ++nextLevel;
                    currentPosition = 0;

                    if (newLevels) {
                        if (print)
                            actualResult << "Add new level" << std::endl;

                        stackWithLevels.addNewLevel();
                    }
                }
            }
            catch (const Hydra::Exception::Container::StackWithLevels::StackWithLevelsException& e) {
                actualResult << e.what() << std::endl;
            }

            if (print)
                printStackWithLevels(stackWithLevels, actualResult);
        }
    }

    StackWithLevelsType createStackWithLevels(bool addInitialLevel = true, LargeNumberType maxNumberOfElements = 10, LargeNumberType maxNumberOfLevels = 10) {
        StackWithLevelsType stackWithLevels(maxNumberOfElements, maxNumberOfLevels);

        if (addInitialLevel)
            stackWithLevels.addNewLevel();

        return stackWithLevels;
    }

    PairStackWithLevelsType createPairStackWithLevels(bool addInitialLevel = true, LargeNumberType maxNumberOfElements = 10, LargeNumberType maxNumberOfLevels = 10) {
        PairStackWithLevelsType stackWithLevels(maxNumberOfElements, maxNumberOfLevels);

        if (addInitialLevel)
            stackWithLevels.addNewLevel();

        return stackWithLevels;
    }
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[Container::StackWithLevels] constructor", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StackWithLevelsType stackWithLevels = createStackWithLevels();
            printStackWithLevels(stackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Constructor (pair)
     */
    TEST_CASE("[Container::StackWithLevels] constructor (pair)", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            PairStackWithLevelsType pairStackWithLevels = createPairStackWithLevels();
            printStackWithLevels(pairStackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add elements
     */
    TEST_CASE("[Container::StackWithLevels] add elements", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsAddElementsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StackWithLevelsType stackWithLevels = createStackWithLevels();
            printStackWithLevels(stackWithLevels, actualResult);

            TypeTVectorType elementVector { 4, 5, 7, 2, 1 };

            addElementsAndLevels(stackWithLevels, elementVector, false, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add elements (pair)
     */
    TEST_CASE("[Container::StackWithLevels] add elements (pair)", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsAddElementsPairResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            PairStackWithLevelsType pairStackWithLevels = createPairStackWithLevels();
            printStackWithLevels(pairStackWithLevels, actualResult);

            TypeTPairVectorType elementVector { { 3, 4 }, { 4, 3 }, { 3, 5 }, { 2, 4 }, { 0, 0 }, { 2, 2 } };

            addElementsAndLevels(pairStackWithLevels, elementVector, false, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add multi-occurrent elements
     */
    TEST_CASE("[Container::StackWithLevels] add multi-occurrent elements", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsAddMultiOccurrentElementsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StackWithLevelsType stackWithLevels = createStackWithLevels();
            printStackWithLevels(stackWithLevels, actualResult);

            TypeTVectorType elementVector { 1, 2, 3, 1, 4, 2, 5, 5 };

            addElementsAndLevels(stackWithLevels, elementVector, false, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add multi-occurrent elements (pair)
     */
    TEST_CASE("[Container::StackWithLevels] add multi-occurrent elements (pair)", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsAddMultiOccurrentElementsPairResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            PairStackWithLevelsType pairStackWithLevels = createPairStackWithLevels();
            printStackWithLevels(pairStackWithLevels, actualResult);

            TypeTPairVectorType elementVector { { 1, 2 }, { 2, 1 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 2, 1 }, { 1, 1 }, { 4, 5 }, { 4, 5 } };

            addElementsAndLevels(pairStackWithLevels, elementVector, false, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add levels
     */
    TEST_CASE("[Container::StackWithLevels] add levels", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsAddLevelsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StackWithLevelsType stackWithLevels = createStackWithLevels();
            printStackWithLevels(stackWithLevels, actualResult);

            TypeTVectorType elementVector { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

            addElementsAndLevels(stackWithLevels, elementVector, true, actualResult);

            actualResult << "Add new level" << std::endl;
            stackWithLevels.addNewLevel();
            printStackWithLevels(stackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add levels (pair)
     */
    TEST_CASE("[Container::StackWithLevels] add levels (pair)", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsAddLevelsPairResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            PairStackWithLevelsType pairStackWithLevels = createPairStackWithLevels();
            printStackWithLevels(pairStackWithLevels, actualResult);

            TypeTPairVectorType elementVector { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 }, { 6, 6 }, { 7, 7 }, { 8, 8 }, { 9, 9 }, { 10, 10 } };

            addElementsAndLevels(pairStackWithLevels, elementVector, true, actualResult);

            actualResult << "Add new level" << std::endl;
            pairStackWithLevels.addNewLevel();
            printStackWithLevels(pairStackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Remove current level
     */
    TEST_CASE("[Container::StackWithLevels] remove current level", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsRemoveCurrentLevelResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            TypeTVectorType elementVector { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            StackWithLevelsType stackWithLevels = createStackWithLevels();
            addElementsAndLevels(stackWithLevels, elementVector, true, actualResult, false);
            printStackWithLevels(stackWithLevels, actualResult);

            actualResult << "Remove current level" << std::endl;
            stackWithLevels.removeCurrentLevel();

            printStackWithLevels(stackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Remove current level - functor
     */
    TEST_CASE("[Container::StackWithLevels] remove current level - functor", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsRemoveCurrentLevelFunctorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            TypeTVectorType elementVector { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            StackWithLevelsType stackWithLevels = createStackWithLevels();
            addElementsAndLevels(stackWithLevels, elementVector, true, actualResult, false);
            printStackWithLevels(stackWithLevels, actualResult);

            actualResult << "Remove current level" << std::endl;
            stackWithLevels.removeCurrentLevel([&actualResult](TypeT element) -> void { actualResult << "Removed element: " << std::to_string(element) << std::endl; });

            printStackWithLevels(stackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Remove current level - empty
     */
    TEST_CASE("[Container::StackWithLevels] remove current level - empty", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsRemoveCurrentLevelEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            TypeTVectorType elementVector { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            StackWithLevelsType stackWithLevels = createStackWithLevels();
            addElementsAndLevels(stackWithLevels, elementVector, true, actualResult, false);
            printStackWithLevels(stackWithLevels, actualResult);

            actualResult << "Remove current level" << std::endl;
            stackWithLevels.removeCurrentLevel();

            printStackWithLevels(stackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Remove current level (pair)
     */
    TEST_CASE("[Container::StackWithLevels] remove current level (pair)", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsRemoveCurrentLevelPairResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            PairStackWithLevelsType pairStackWithLevels = createPairStackWithLevels();
            TypeTPairVectorType elementVector { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 }, { 6, 6 }, { 7, 7 }, { 8, 8 }, { 9, 9 } };
            addElementsAndLevels(pairStackWithLevels, elementVector, true, actualResult, false);
            printStackWithLevels(pairStackWithLevels, actualResult);

            actualResult << "Remove current level" << std::endl;
            pairStackWithLevels.removeCurrentLevel();

            printStackWithLevels(pairStackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Remove current level - functor (pair)
     */
    TEST_CASE("[Container::StackWithLevels] remove current level - functor (pair)", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsRemoveCurrentLevelFunctorPairResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            PairStackWithLevelsType pairStackWithLevels = createPairStackWithLevels();
            TypeTPairVectorType elementVector { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 }, { 6, 6 }, { 7, 7 }, { 8, 8 }, { 9, 9 } };
            addElementsAndLevels(pairStackWithLevels, elementVector, true, actualResult, false);
            printStackWithLevels(pairStackWithLevels, actualResult);

            actualResult << "Remove current level" << std::endl;
            pairStackWithLevels.removeCurrentLevel([&actualResult](TypeTPairType element) -> void { actualResult << "Removed element: " << std::to_string(element) << std::endl; });

            printStackWithLevels(pairStackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Remove current level - empty (pair)
     */
    TEST_CASE("[Container::StackWithLevels] remove current level - empty (pair)", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsRemoveCurrentLevelEmptyPairResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            PairStackWithLevelsType pairStackWithLevels = createPairStackWithLevels();
            TypeTPairVectorType elementVector { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 }, { 6, 6 }, { 7, 7 }, { 8, 8 }, { 9, 9 }, { 10, 10 } };
            addElementsAndLevels(pairStackWithLevels, elementVector, true, actualResult, false);
            printStackWithLevels(pairStackWithLevels, actualResult);

            actualResult << "Remove current level" << std::endl;
            pairStackWithLevels.removeCurrentLevel();

            printStackWithLevels(pairStackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear
     */
    TEST_CASE("[Container::StackWithLevels] clear", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsClearResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            TypeTVectorType elementVector { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            StackWithLevelsType stackWithLevels = createStackWithLevels();
            addElementsAndLevels(stackWithLevels, elementVector, true, actualResult, false);
            printStackWithLevels(stackWithLevels, actualResult);

            actualResult << "Clear" << std::endl;
            stackWithLevels.clear();

            printStackWithLevels(stackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear - functor
     */
    TEST_CASE("[Container::StackWithLevels] clear - functor", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsClearFunctorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            TypeTVectorType elementVector { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            StackWithLevelsType stackWithLevels = createStackWithLevels();
            addElementsAndLevels(stackWithLevels, elementVector, true, actualResult, false);
            printStackWithLevels(stackWithLevels, actualResult);

            actualResult << "Clear" << std::endl;
            stackWithLevels.clear([&actualResult](TypeT element) -> void { actualResult << "Removed element: " << std::to_string(element) << std::endl; });

            printStackWithLevels(stackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear - empty
     */
    TEST_CASE("[Container::StackWithLevels] clear - empty", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsClearEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StackWithLevelsType stackWithLevels = createStackWithLevels(false);
            printStackWithLevels(stackWithLevels, actualResult);

            actualResult << "Clear" << std::endl;
            stackWithLevels.clear();

            printStackWithLevels(stackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear (pair)
     */
    TEST_CASE("[Container::StackWithLevels] clear (pair)", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsClearPairResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            PairStackWithLevelsType pairStackWithLevels = createPairStackWithLevels();
            TypeTPairVectorType elementVector { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 }, { 6, 6 }, { 7, 7 }, { 8, 8 }, { 9, 9 }, { 10, 10 } };
            addElementsAndLevels(pairStackWithLevels, elementVector, true, actualResult, false);
            printStackWithLevels(pairStackWithLevels, actualResult);

            actualResult << "Clear" << std::endl;
            pairStackWithLevels.clear();

            printStackWithLevels(pairStackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear - functor (pair)
     */
    TEST_CASE("[Container::StackWithLevels] clear - functor (pair)", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsClearFunctorPairResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            PairStackWithLevelsType pairStackWithLevels = createPairStackWithLevels();
            TypeTPairVectorType elementVector { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 }, { 6, 6 }, { 7, 7 }, { 8, 8 }, { 9, 9 }, { 10, 10 } };
            addElementsAndLevels(pairStackWithLevels, elementVector, true, actualResult, false);
            printStackWithLevels(pairStackWithLevels, actualResult);

            actualResult << "Clear" << std::endl;
            pairStackWithLevels.clear([&actualResult](TypeTPairType element) -> void { actualResult << "Removed element: " << std::to_string(element) << std::endl; });

            printStackWithLevels(pairStackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear - empty (pair)
     */
    TEST_CASE("[Container::StackWithLevels] clear - empty (pair)", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsClearEmptyPairResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            PairStackWithLevelsType pairStackWithLevels = createPairStackWithLevels(false);
            printStackWithLevels(pairStackWithLevels, actualResult);

            actualResult << "Clear" << std::endl;
            pairStackWithLevels.clear();

            printStackWithLevels(pairStackWithLevels, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Print - functor
     */
    TEST_CASE("[Container::StackWithLevels] print - functor", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsPrintFunctorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            StackWithLevelsType stackWithLevels = createStackWithLevels();
            TypeTVectorType elementVector { 4, 5, 7, 2, 1 };
            addElementsAndLevels(stackWithLevels, elementVector, true, actualResult, false);
            printStackWithLevels(stackWithLevels, actualResult);

            actualResult << "Printed with functor (+1): ";
            stackWithLevels.printStackWithLevelsDebug(actualResult, [](TypeT element) -> std::string { return std::to_string(element + 1); });
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Print - functor (pair)
     */
    TEST_CASE("[Container::StackWithLevels] print - functor (pair)", "[Container::StackWithLevels]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          stackWithLevelsPrintFunctorPairResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            PairStackWithLevelsType pairStackWithLevels = createPairStackWithLevels();
            TypeTPairVectorType elementVector { { 3, 4 }, { 4, 3 }, { 3, 5 }, { 2, 4 }, { 0, 0 }, { 2, 2 } };
            addElementsAndLevels(pairStackWithLevels, elementVector, true, actualResult, false);
            printStackWithLevels(pairStackWithLevels, actualResult);

            actualResult << "Printed with functor (+1, +2): ";
            pairStackWithLevels.printStackWithLevelsDebug(actualResult, [](TypeTPairType element) -> std::string { return "(" + std::to_string(element.first + 1) + ", " + std::to_string(element.second + 2) + ")"; });
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Container::StackWithLevels
