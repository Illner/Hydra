#include <sstream>
#include <stdexcept>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/other/MergeSortTestResult.hpp"

#include "Hydra/other/Other.hpp"

namespace HydraTest::Other::MergeSort {

    //region Types
    using TypeT = char16_t;

    using TypeTVectorType = std::vector<TypeT>;
    //endregion

    //region Functions
    int sortFunctor(const TypeT& element1, const TypeT& element2) {
        TypeT element1Tmp = element1;
        if (element1Tmp >= 1000)
            element1Tmp = (element1Tmp - (element1Tmp % 10));

        TypeT element2Tmp = element2;
        if (element2Tmp >= 1000)
            element2Tmp = (element2Tmp - (element2Tmp % 10));

        if (element1Tmp == element2Tmp)
            return 0;

        if (element1Tmp < element2Tmp)
            return -1;

        // element1Tmp > element2Tmp
        return 1;
    }

    void printTypeTVector(const TypeTVectorType& vector, std::stringstream& actualResult) {
        actualResult << "(" << std::to_string(vector.size()) << "): ";
        for (const TypeT& element : vector)
            actualResult << std::to_string(element) << ", ";
        actualResult << std::endl;
    }
    //endregion

    /**
     * Ignore duplicate
     */
    TEST_CASE("[Other::MergeSort] ignore duplicate", "[Other::MergeSort]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          mergeSortIgnoreDuplicateResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            std::vector<TypeTVectorType> vector { { 0 }, { 1 }, { 2 }, { 1, 2 }, { 2, 1 }, { 1, 1 }, { 2, 2 }, { 1, 2, 3 }, { 3, 2, 1 }, { 1, 1, 2 }, { 1, 2, 1 }, { 2, 1, 1 } };

            for (TypeTVectorType& typeTVector : vector) {
                actualResult << "Before: ";
                printTypeTVector(typeTVector, actualResult);

                Hydra::Other::mergeSort(typeTVector, sortFunctor, false, 0);

                actualResult << "After: ";
                printTypeTVector(typeTVector, actualResult);
                actualResult << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Ignore duplicate (random)
     */
    TEST_CASE("[Other::MergeSort] ignore duplicate (random)", "[Other::MergeSort]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          mergeSortIgnoreDuplicateRandomResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            std::vector<TypeTVectorType> vector { { 3, 8, 21, 20, 10, 9, 10, 17, 19, 4, 21, 18, 5, 7, 7, 16, 10, 2, 13, 12, 21, 9, 6, 21, 7 },
                                                  { 24, 11, 6, 16, 15, 1, 25, 2, 7, 5, 12, 3, 12, 9, 11, 5, 7, 25, 21, 25, 24, 10, 23, 7, 11 },
                                                  { 9, 11, 16, 10, 23, 19, 20, 24, 24, 11, 10, 7, 7, 21, 12, 7, 13, 13, 21, 9, 5, 6, 1, 3, 23 },
                                                  { 54, 5, 62, 79, 47, 57, 6, 24, 79, 79, 68, 21, 97, 1, 28, 1, 98, 77, 27, 40, 52, 75, 57, 48, 40 },
                                                  { 23, 59, 100, 30, 1, 21, 69, 63, 92, 62, 61, 81, 23, 12, 58, 42, 75, 73, 59, 17, 2, 84, 48, 48, 55 },
                                                  { 99, 76, 96, 6, 24, 47, 6, 30, 48, 80, 89, 33, 6, 70, 88, 49, 23, 30, 93, 20, 3, 1, 37, 70, 71 } };

            for (TypeTVectorType& typeTVector : vector) {
                actualResult << "Before: ";
                printTypeTVector(typeTVector, actualResult);

                Hydra::Other::mergeSort(typeTVector, sortFunctor, false, 0);

                actualResult << "After: ";
                printTypeTVector(typeTVector, actualResult);
                actualResult << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Remove duplicate
     */
    TEST_CASE("[Other::MergeSort] remove duplicate", "[Other::MergeSort]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          mergeSortRemoveDuplicateResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            std::vector<TypeTVectorType> vector { { 1, 1 }, { 1, 2, 1 }, { 1000 }, { 2000 }, { 1000, 2000 }, { 2000, 1000 }, { 1000, 1001 }, { 1001, 1000 }, { 1000, 1001, 2000 }, { 1001, 2000, 1000 }, { 2000, 1000, 1001 }, { 1000, 1001, 1002, 2000 }, { 1000, 1002, 2000, 1001 }, { 1002, 2000, 1001, 1000 }, { 2000, 1001, 1002, 1000 } };

            size_t estimatedNumberOfDuplicateElements = 0;
            for (TypeTVectorType& typeTVector : vector) {
                try {
                    actualResult << "Before: ";
                    printTypeTVector(typeTVector, actualResult);

                    Hydra::Other::mergeSort(typeTVector, sortFunctor, true, estimatedNumberOfDuplicateElements);

                    actualResult << "After: ";
                    printTypeTVector(typeTVector, actualResult);
                    actualResult << std::endl;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl
                                 << std::endl;
                }

                ++estimatedNumberOfDuplicateElements;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Remove duplicate (random)
     */
    TEST_CASE("[Other::MergeSort] remove duplicate (random)", "[Other::MergeSort]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          mergeSortRemoveDuplicateRandomResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            std::vector<TypeTVectorType> vector { { 1008, 1018, 1066, 1070, 1089, 1098, 1055, 1046, 1017, 1090, 1012, 1032, 1024, 1010, 1058 },
                                                  { 1078, 1026, 1084, 1057, 1043, 1046, 1018, 1044, 1090, 1095, 1029, 1007, 1089, 1015, 1012 },
                                                  { 1046, 1090, 1018, 1089, 1080, 1074, 1006, 1069, 1037, 1019, 1030, 1076, 1056, 1043, 1067 },
                                                  { 1081, 1046, 1026, 1011, 1012, 1062, 1096, 1082, 1061, 1050, 1089, 1003, 1048, 1080, 1019 } };

            size_t estimatedNumberOfDuplicateElements = 0;
            for (TypeTVectorType& typeTVector : vector) {
                actualResult << "Before: ";
                printTypeTVector(typeTVector, actualResult);

                Hydra::Other::mergeSort(typeTVector, sortFunctor, true, estimatedNumberOfDuplicateElements);

                actualResult << "After: ";
                printTypeTVector(typeTVector, actualResult);
                actualResult << std::endl;

                ++estimatedNumberOfDuplicateElements;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Other::MergeSort
