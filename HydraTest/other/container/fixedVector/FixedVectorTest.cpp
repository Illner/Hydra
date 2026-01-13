#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/other/container/fixedVector/FixedVectorTestResult.hpp"

#include "Hydra/other/container/fixedVector/FixedVector.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

namespace HydraTest::Container::FixedVector {

    //region Types
    using TypeT = char8_t;

    using TypeTVectorType = std::vector<TypeT>;
    using TypeTSetType = Hydra::Other::HashMap::SetType<TypeT>;
    using FixedVectorType = Hydra::Container::FixedVector::FixedVector<TypeT>;
    //endregion

    //region Functions
    void printFixedVector(const FixedVectorType& fixedVector, std::stringstream& actualResult) {
        fixedVector.printFixedVectorDebug(actualResult);
        actualResult << std::endl;
    }
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[Container::FixedVector] constructor", "[Container::FixedVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          fixedVectorConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            // Empty
            actualResult << "Empty constructor" << std::endl;
            FixedVectorType fixedVector1({});
            printFixedVector(fixedVector1, actualResult);

            // Copy
            actualResult << "Copy constructor" << std::endl;
            TypeTVectorType vector2 { 1, 2, 3, 4, 5 };
            FixedVectorType fixedVector2(vector2);
            printFixedVector(fixedVector2, actualResult);

            // Move
            actualResult << "Move constructor" << std::endl;
            TypeTVectorType vector3 { 1, 2, 3, 4, 5 };
            FixedVectorType fixedVector3(std::move(vector3));
            printFixedVector(fixedVector3, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Constructor (range)
     */
    TEST_CASE("[Container::FixedVector] constructor (range)", "[Container::FixedVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          fixedVectorConstructorRangeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            std::vector<std::pair<TypeT, TypeT>> rangeVector { { 0, 1 }, { 1, 2 }, { 3, 4 }, { 1, 5 }, { 3, 8 }, { 10, 12 } };

            for (auto rangePair : rangeVector) {
                actualResult << "FirstValue: " << std::to_string(rangePair.first)
                             << ", lastValue: " << std::to_string(rangePair.second) << std::endl;

                FixedVectorType fixedVector(rangePair.first, rangePair.second);
                printFixedVector(fixedVector, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy and move
     */
    TEST_CASE("[Container::FixedVector] copy and move", "[Container::FixedVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          fixedVectorCopyAndMoveResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FixedVectorType fixedVector1({ 1, 2, 3, 4, 5 });
            printFixedVector(fixedVector1, actualResult);

            actualResult << "Copy method" << std::endl;
            FixedVectorType fixedVector2 = fixedVector1;
            fixedVector2.changeNumberOfActiveElements(1);
            printFixedVector(fixedVector1, actualResult);
            printFixedVector(fixedVector2, actualResult);

            actualResult << "Move method" << std::endl;
            FixedVectorType fixedVector3 = std::move(fixedVector1);
            printFixedVector(fixedVector3, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Change
     */
    TEST_CASE("[Container::FixedVector] change", "[Container::FixedVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          fixedVectorChangeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FixedVectorType fixedVector({ 1, 2, 3, 4, 5 });
            printFixedVector(fixedVector, actualResult);

            for (size_t i : std::vector<std::size_t> { 0, 1, 2, 3, 4, 5 }) {
                actualResult << "Change: " << std::to_string(i) << std::endl;
                fixedVector.changeNumberOfActiveElements(i);
                printFixedVector(fixedVector, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Swap
     */
    TEST_CASE("[Container::FixedVector] swap", "[Container::FixedVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          fixedVectorSwapResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FixedVectorType fixedVector({ 1, 2, 3, 4, 5, 6 });
            fixedVector.changeNumberOfActiveElements(4);
            printFixedVector(fixedVector, actualResult);

            std::vector<std::pair<size_t, size_t>> swapVector { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 3 }, { 3, 1 }, { 3, 4 }, { 4, 3 }, { 4, 4 }, { 4, 5 } };

            for (auto swapPair : swapVector) {
                try {
                    actualResult << "Swap: " << std::to_string(swapPair.first) << "<->" << std::to_string(swapPair.second) << std::endl;

                    fixedVector.swap(swapPair.first, swapPair.second);
                    printFixedVector(fixedVector, actualResult);
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }
            }

            actualResult << std::endl;
            printFixedVector(fixedVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Swap (element)
     */
    TEST_CASE("[Container::FixedVector] swap (element)", "[Container::FixedVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          fixedVectorSwapElementResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FixedVectorType fixedVector({ 1, 2, 3, 4, 5, 6 });
            fixedVector.changeNumberOfActiveElements(4);
            printFixedVector(fixedVector, actualResult);

            TypeTVectorType swapVector { 1, 3, 5, 7, 2, 2, 4, 6, 8 };

            for (TypeT element : swapVector) {
                try {
                    actualResult << "Element: " << std::to_string(element) << std::endl;

                    fixedVector.swap(element);
                    printFixedVector(fixedVector, actualResult);
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl
                                 << std::endl;
                }
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Swap (elements)
     */
    TEST_CASE("[Container::FixedVector] swap (elements)", "[Container::FixedVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          fixedVectorSwapElementsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FixedVectorType fixedVector({ 1, 2, 3, 4, 5, 6 });
            printFixedVector(fixedVector, actualResult);

            std::vector<TypeTVectorType> swapElementsVector { {}, { 1 }, { 3 }, { 3 }, { 2, 1 }, { 4, 5 }, { 4, 5 }, { 6, 2, 4 }, /*{ 3, 7 }, { 7, 8 },*/ { 1, 2, 3, 4, 5, 6 } };

            for (const TypeTVectorType& swapElements : swapElementsVector) {
                try {
                    actualResult << "Elements:";
                    for (TypeT element : swapElements)
                        actualResult << " " << std::to_string(element);
                    actualResult << std::endl;

                    TypeTSetType swapElementsTmp(swapElements.cbegin(), swapElements.cend());
                    fixedVector.swap(swapElementsTmp);

                    printFixedVector(fixedVector, actualResult);
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl
                                 << std::endl;
                }

                fixedVector.changeNumberOfActiveElements(6);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Container::FixedVector
