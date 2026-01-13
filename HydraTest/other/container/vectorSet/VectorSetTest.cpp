#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/other/container/vectorSet/VectorSetTestResult.hpp"

#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/vectorSet/VectorSet.hpp"

namespace HydraTest::Container::VectorSet {

    //region Types
    using ElementType = char8_t;
    using ElementVectorType = std::vector<ElementType>;

    using VectorSetType = Hydra::Container::VectorSet::VectorSet;
    using IndexVectorType = Hydra::Container::VectorSet::VectorSet::IndexVectorType;
    //endregion

    //region Functions
    void printVectorSet(VectorSetType& vectorSet, std::stringstream& actualResult, bool printCapacity = false) {
        vectorSet.printVectorSetDebug(actualResult);

        actualResult << "----------" << std::endl;

        if (printCapacity)
            actualResult << "Capacity: " << std::to_string(vectorSet.capacity()) << std::endl;

        actualResult << "getAddedElementVector:";
        const IndexVectorType& addedElementVector = vectorSet.getAddedElementVector(true);
        for (ElementType element : addedElementVector)
            actualResult << " " << std::to_string(element);
        actualResult << std::endl
                     << std::endl;
    }

    void printTitle(const std::string& title, std::stringstream& actualResult) {
        Hydra::Other::printTitle(actualResult, " " + title + " ", 15, '-');
        actualResult << std::endl;
    }

    void printClearTitle(std::stringstream& actualResult) {
        printTitle("clear", actualResult);
    }

    void addFullVectorSet(VectorSetType& vectorSet, std::stringstream& actualResult, bool printTitle_ = true) {
        if (printTitle_)
            printTitle("add full", actualResult);

        for (ElementType element = 0; element < static_cast<ElementType>(vectorSet.capacity()); ++element)
            vectorSet.emplace(element);
    }

    void addEvenVectorSet(VectorSetType& vectorSet, std::stringstream& actualResult, bool printTitle_ = true) {
        if (printTitle_)
            printTitle("add even", actualResult);

        for (ElementType element = 0; element < static_cast<ElementType>(vectorSet.capacity()); element += 2)
            vectorSet.emplace(element);
    }

    void addOddVectorSet(VectorSetType& vectorSet, std::stringstream& actualResult, bool printTitle_ = true) {
        if (printTitle_)
            printTitle("add odd", actualResult);

        for (ElementType element = 1; element < static_cast<ElementType>(vectorSet.capacity()); element += 2)
            vectorSet.emplace(element);
    }

    void containsVectorSet(const VectorSetType& vectorSet, std::stringstream& actualResult) {
        for (ElementType element = 0; element < static_cast<ElementType>(vectorSet.capacity()); ++element) {
            actualResult << "Element " << std::to_string(element) << ": ";

            bool exists = vectorSet.contains(element);
            actualResult << std::to_string(exists) << std::endl;
        }
    }

    void addElementsVectorSet(VectorSetType& vectorSet, const ElementVectorType& elementVector, std::stringstream& actualResult, bool checkExistence) {
        for (ElementType element : elementVector) {
            actualResult << "Add element: " << std::to_string(element) << std::endl;
            actualResult << std::endl;

            vectorSet.emplace(element, checkExistence);
            printVectorSet(vectorSet, actualResult);
        }
    }

    void moveConstructorVectorSet(VectorSetType&& vectorSet, std::stringstream& actualResult) {
        printTitle("before", actualResult);
        printVectorSet(vectorSet, actualResult, true);

        VectorSetType vectorSetMoved(std::move(vectorSet));

        printTitle("after", actualResult);
        printVectorSet(vectorSet, actualResult, true);

        printTitle("moved", actualResult);
        printVectorSet(vectorSetMoved, actualResult, true);
    }

    void moveAssignmentVectorSet(VectorSetType&& vectorSet, std::stringstream& actualResult) {
        printTitle("before", actualResult);
        printVectorSet(vectorSet, actualResult, true);

        VectorSetType vectorSetMoved = std::move(vectorSet);

        printTitle("after", actualResult);
        printVectorSet(vectorSet, actualResult, true);

        printTitle("moved", actualResult);
        printVectorSet(vectorSetMoved, actualResult, true);
    }

    void clearVectorSet(VectorSetType& vectorSet, std::stringstream& actualResult, bool printTitle_ = true) {
        if (printTitle_)
            printClearTitle(actualResult);

        vectorSet.clear();
    }
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[Container::VectorSet] constructor", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(10);
            printVectorSet(vectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Constructor - empty
     */
    TEST_CASE("[Container::VectorSet] constructor - empty", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetConstructorEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet;
            printVectorSet(vectorSet, actualResult);
            actualResult << "Capacity: " << std::to_string(vectorSet.capacity()) << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - empty
     */
    TEST_CASE("[Container::VectorSet] move constructor - empty", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetMoveConstructorAssignmentEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(11);
            moveConstructorVectorSet(std::move(vectorSet), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - full
     */
    TEST_CASE("[Container::VectorSet] move constructor - full", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetMoveConstructorAssignmentFullResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(12);
            addFullVectorSet(vectorSet, actualResult, false);
            moveConstructorVectorSet(std::move(vectorSet), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - even
     */
    TEST_CASE("[Container::VectorSet] move constructor - even", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetMoveConstructorAssignmentEvenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(13);
            addEvenVectorSet(vectorSet, actualResult, false);
            moveConstructorVectorSet(std::move(vectorSet), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - odd
     */
    TEST_CASE("[Container::VectorSet] move constructor - odd", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetMoveConstructorAssignmentOddResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(14);
            addOddVectorSet(vectorSet, actualResult, false);
            moveConstructorVectorSet(std::move(vectorSet), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - clear
     */
    TEST_CASE("[Container::VectorSet] move constructor - clear", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetMoveConstructorAssignmentClearResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(15);

            // Add full
            addFullVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);

            // Clear
            clearVectorSet(vectorSet, actualResult);

            moveConstructorVectorSet(std::move(vectorSet), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - empty
     */
    TEST_CASE("[Container::VectorSet] move assignment - empty", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetMoveConstructorAssignmentEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(11);
            moveAssignmentVectorSet(std::move(vectorSet), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - full
     */
    TEST_CASE("[Container::VectorSet] move assignment - full", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetMoveConstructorAssignmentFullResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(12);
            addFullVectorSet(vectorSet, actualResult, false);
            moveAssignmentVectorSet(std::move(vectorSet), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - even
     */
    TEST_CASE("[Container::VectorSet] move assignment - even", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetMoveConstructorAssignmentEvenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(13);
            addEvenVectorSet(vectorSet, actualResult, false);
            moveAssignmentVectorSet(std::move(vectorSet), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - odd
     */
    TEST_CASE("[Container::VectorSet] move assignment - odd", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetMoveConstructorAssignmentOddResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(14);
            addOddVectorSet(vectorSet, actualResult, false);
            moveAssignmentVectorSet(std::move(vectorSet), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - clear
     */
    TEST_CASE("[Container::VectorSet] move assignment - clear", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetMoveConstructorAssignmentClearResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(15);

            // Add full
            addFullVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);

            // Clear
            clearVectorSet(vectorSet, actualResult);

            moveAssignmentVectorSet(std::move(vectorSet), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Emplace
     */
    TEST_CASE("[Container::VectorSet] emplace", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetEmplaceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(9);
            printVectorSet(vectorSet, actualResult);

            ElementVectorType elementVector { (ElementType)0, (ElementType)1, (ElementType)8, (ElementType)7, (ElementType)4, (ElementType)3, (ElementType)5 };

            addElementsVectorSet(vectorSet, elementVector, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Emplace with check existence
     */
    TEST_CASE("[Container::VectorSet] emplace with check existence", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetEmplaceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(9);
            printVectorSet(vectorSet, actualResult);

            ElementVectorType elementVector { (ElementType)0, (ElementType)1, (ElementType)8, (ElementType)7, (ElementType)4, (ElementType)3, (ElementType)5 };

            addElementsVectorSet(vectorSet, elementVector, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Emplace (multiple occurrences)
     */
    TEST_CASE("[Container::VectorSet] emplace (multiple occurrences)", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetEmplaceMultipleOccurrencesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(8);
            printVectorSet(vectorSet, actualResult);

            ElementVectorType elementVector { (ElementType)5, (ElementType)4, (ElementType)3, (ElementType)2, (ElementType)4 };

            addElementsVectorSet(vectorSet, elementVector, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Emplace with check existence (multiple occurrences)
     */
    TEST_CASE("[Container::VectorSet] emplace with check existence (multiple occurrences)", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetEmplaceWithCheckExistenceMultipleOccurrencesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(8);
            printVectorSet(vectorSet, actualResult);

            ElementVectorType elementVector { (ElementType)5, (ElementType)4, (ElementType)3, (ElementType)2, (ElementType)4 };

            addElementsVectorSet(vectorSet, elementVector, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add full
     */
    TEST_CASE("[Container::VectorSet] add full", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetAddFullResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(7);
            addFullVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add even
     */
    TEST_CASE("[Container::VectorSet] add even", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetAddEvenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(6);
            addEvenVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add odd
     */
    TEST_CASE("[Container::VectorSet] add odd", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetAddOddResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(5);
            addOddVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear full
     */
    TEST_CASE("[Container::VectorSet] clear full", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetClearFullResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(4);

            // Add full
            addFullVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);

            // Clear
            clearVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear even
     */
    TEST_CASE("[Container::VectorSet] clear even", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetClearEvenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(5);

            // Add even
            addEvenVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);

            // Clear
            clearVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear odd
     */
    TEST_CASE("[Container::VectorSet] clear odd", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetClearOddResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(6);

            // Add odd
            addOddVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);

            // Clear
            clearVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear empty
     */
    TEST_CASE("[Container::VectorSet] clear empty", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetClearEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(7);
            printVectorSet(vectorSet, actualResult);

            // Clear
            clearVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Contains full
     */
    TEST_CASE("[Container::VectorSet] contains full", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetContainsFullResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(8);

            // Add full
            addFullVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);

            // Contains
            containsVectorSet(vectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Contains even
     */
    TEST_CASE("[Container::VectorSet] contains even", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetContainsEvenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(8);

            // Add even
            addEvenVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);

            // Contains
            containsVectorSet(vectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Contains odd
     */
    TEST_CASE("[Container::VectorSet] contains odd", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetContainsOddResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(8);

            // Add odd
            addOddVectorSet(vectorSet, actualResult);
            printVectorSet(vectorSet, actualResult);

            // Contains
            containsVectorSet(vectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Contains empty
     */
    TEST_CASE("[Container::VectorSet] contains empty", "[Container::VectorSet]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorSetContainsEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorSetType vectorSet(8);
            printVectorSet(vectorSet, actualResult);

            // Contains
            containsVectorSet(vectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Container::VectorSet
