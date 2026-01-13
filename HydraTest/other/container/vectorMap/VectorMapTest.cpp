#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/other/container/vectorMap/VectorMapTestResult.hpp"

#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/vectorMap/VectorMap.hpp"

namespace HydraTest::Container::VectorMap {

    //region Types
    using TypeT = char8_t;

    using LiteralType = typename Hydra::Formula::Literal<TypeT, TypeT>::LiteralType;

    using KeyType = std::size_t;
    using ElementType = std::pair<KeyType, TypeT>;
    using ElementVectorType = std::vector<ElementType>;
    using ElementLiteralType = std::pair<KeyType, LiteralType>;
    using ElementLiteralVectorType = std::vector<ElementLiteralType>;

    using VectorMapType = Hydra::Container::VectorMap::VectorMap<TypeT>;
    using VectorMapLiteralType = Hydra::Container::VectorMap::VectorMap<LiteralType>;
    //endregion

    //region Functions
    template <typename TypeT>
    void printVectorMap(Hydra::Container::VectorMap::VectorMap<TypeT>& vectorMap, std::stringstream& actualResult, bool printCapacity = false) {
        vectorMap.printVectorMapDebug(actualResult);

        actualResult << "----------" << std::endl;

        if (printCapacity)
            actualResult << "Capacity: " << std::to_string(vectorMap.capacity()) << std::endl;

        actualResult << "getAddedKeyVector:";
        for (KeyType key : vectorMap.getAddedKeyVector(true))
            actualResult << " " << std::to_string(key);
        actualResult << std::endl
                     << std::endl;
    }

    template <typename TypeT>
    void printNoValueRepresentative(const Hydra::Container::VectorMap::VectorMap<TypeT>& vectorMap, std::stringstream& actualResult) {
        actualResult << "No-value representative: ";

        const TypeT& noValueRepresentative = vectorMap.getNoValueRepresentative();

        actualResult << std::to_string(noValueRepresentative) << std::endl;
    }

    void printTitle(const std::string& title, std::stringstream& actualResult, int numberOfDelimiters = 15) {
        Hydra::Other::printTitle(actualResult, " " + title + " ", numberOfDelimiters, '-');
        actualResult << std::endl;
    }

    void printClearTitle(std::stringstream& actualResult) {
        printTitle("clear", actualResult);
    }

    template <typename TypeT>
    void clearVectorMap(Hydra::Container::VectorMap::VectorMap<TypeT>& vectorMap, std::stringstream& actualResult, bool printTitle_ = true) {
        if (printTitle_)
            printClearTitle(actualResult);

        vectorMap.clear();
    }

    template <typename TypeT>
    void moveConstructorVectorMap(Hydra::Container::VectorMap::VectorMap<TypeT>&& vectorMap, std::stringstream& actualResult) {
        printTitle("before", actualResult);
        printVectorMap(vectorMap, actualResult, true);

        Hydra::Container::VectorMap::VectorMap<TypeT> vectorMapMoved(std::move(vectorMap));

        printTitle("after", actualResult);
        printVectorMap(vectorMap, actualResult, true);

        printTitle("moved", actualResult);
        printVectorMap(vectorMapMoved, actualResult, true);
    }

    template <typename TypeT>
    void moveAssignmentVectorMap(Hydra::Container::VectorMap::VectorMap<TypeT>&& vectorMap, std::stringstream& actualResult) {
        printTitle("before", actualResult);
        printVectorMap(vectorMap, actualResult, true);

        Hydra::Container::VectorMap::VectorMap<TypeT> vectorMapMoved = std::move(vectorMap);

        printTitle("after", actualResult);
        printVectorMap(vectorMap, actualResult, true);

        printTitle("moved", actualResult);
        printVectorMap(vectorMapMoved, actualResult, true);
    }

    void addFullVectorMap(VectorMapType& vectorMap, std::stringstream& actualResult, TypeT initialValue = 1, bool printTitle_ = true) {
        if (printTitle_)
            printTitle("add full", actualResult);

        TypeT value = initialValue;

        for (KeyType key = 0; key < vectorMap.capacity(); ++key)
            vectorMap.insert(key, value++);
    }

    void addFullVectorMap(VectorMapLiteralType& vectorMap, std::stringstream& actualResult, TypeT initialVariable = 1, bool printTitle_ = true) {
        if (printTitle_)
            printTitle("add full", actualResult);

        bool sign = true;
        TypeT var = initialVariable;

        for (KeyType key = 0; key < vectorMap.capacity(); ++key) {
            vectorMap.emplace(key, var++, sign);

            sign = !sign;
        }
    }

    void addEvenVectorMap(VectorMapType& vectorMap, std::stringstream& actualResult, TypeT initialValue = 1, bool printTitle_ = true) {
        if (printTitle_)
            printTitle("add even", actualResult);

        TypeT value = initialValue;

        for (KeyType key = 0; key < vectorMap.capacity(); key += 2)
            vectorMap.insert(key, value++);
    }

    void addEvenVectorMap(VectorMapLiteralType& vectorMap, std::stringstream& actualResult, TypeT initialVariable = 1, bool printTitle_ = true) {
        if (printTitle_)
            printTitle("add even", actualResult);

        bool sign = true;
        TypeT var = initialVariable;

        for (KeyType key = 0; key < vectorMap.capacity(); key += 2) {
            vectorMap.emplace(key, var++, sign);

            sign = !sign;
        }
    }

    void addOddVectorMap(VectorMapType& vectorMap, std::stringstream& actualResult, TypeT initialValue = 1, bool printTitle_ = true) {
        if (printTitle_)
            printTitle("add odd", actualResult);

        TypeT value = initialValue;

        for (KeyType key = 1; key < vectorMap.capacity(); key += 2)
            vectorMap.insert(key, value++);
    }

    void addOddVectorMap(VectorMapLiteralType& vectorMap, std::stringstream& actualResult, TypeT initialVariable = 1, bool printTitle_ = true) {
        if (printTitle_)
            printTitle("add odd", actualResult);

        bool sign = true;
        TypeT var = initialVariable;

        for (KeyType key = 1; key < vectorMap.capacity(); key += 2) {
            vectorMap.emplace(key, var++, sign);

            sign = !sign;
        }
    }

    template <typename TypeT>
    void insertElementsVectorMap(Hydra::Container::VectorMap::VectorMap<TypeT>& vectorMap, const std::vector<std::pair<KeyType, TypeT>>& elementVector,
                                 std::stringstream& actualResult, bool checkExistence) {
        for (const std::pair<KeyType, TypeT>& element : elementVector) {
            actualResult << "Add element: " << std::to_string(element) << std::endl;
            actualResult << std::endl;

            vectorMap.insert(element.first, element.second, checkExistence);
            printVectorMap(vectorMap, actualResult);
        }
    }

    template <typename TypeT>
    void containsFindAndSubscriptOperatorVectorMap(const Hydra::Container::VectorMap::VectorMap<TypeT>& vectorMap, std::stringstream& actualResult) {
        for (KeyType key = 0; key < vectorMap.capacity(); ++key) {
            actualResult << "Key " << std::to_string(key) << ": ";

            bool exists = vectorMap.contains(key);
            actualResult << std::to_string(exists);

            if (exists) {
                // Find
                const TypeT& valueFind = vectorMap.find(key);
                actualResult << " (" << std::to_string(valueFind) << ")";

                // Subscript operator
                const TypeT& valueSubscriptOperator = vectorMap[key];
                actualResult << " [" << std::to_string(valueSubscriptOperator) << "]";
            }

            actualResult << std::endl;
        }
    }

    LiteralType createZeroLiteral() {
        return Hydra::Formula::createZeroLiteral<TypeT, TypeT>();
    }
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[Container::VectorMap] constructor", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(10, 0);
            printVectorMap(vectorMap, actualResult, true);
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
    TEST_CASE("[Container::VectorMap] constructor - empty", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapConstructorEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap;
            printVectorMap(vectorMap, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Constructor (literal)
     */
    TEST_CASE("[Container::VectorMap] constructor (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(10, createZeroLiteral());
            printVectorMap(vectorMap, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Constructor - empty (literal)
     */
    TEST_CASE("[Container::VectorMap] constructor - empty (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapConstructorEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(createZeroLiteral());
            printVectorMap(vectorMap, actualResult, true);
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
    TEST_CASE("[Container::VectorMap] move constructor - empty", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(11, 0);
            moveConstructorVectorMap(std::move(vectorMap), actualResult);
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
    TEST_CASE("[Container::VectorMap] move constructor - full", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentFullResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(12, 0);
            addFullVectorMap(vectorMap, actualResult, 1, false);
            moveConstructorVectorMap(std::move(vectorMap), actualResult);
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
    TEST_CASE("[Container::VectorMap] move constructor - even", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentEvenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(13, 0);
            addEvenVectorMap(vectorMap, actualResult, 1, false);
            moveConstructorVectorMap(std::move(vectorMap), actualResult);
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
    TEST_CASE("[Container::VectorMap] move constructor - odd", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentOddResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(14, 0);
            addOddVectorMap(vectorMap, actualResult, 1, false);
            moveConstructorVectorMap(std::move(vectorMap), actualResult);
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
    TEST_CASE("[Container::VectorMap] move constructor - clear", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentClearResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(15, 0);

            // Add full
            addFullVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Clear
            clearVectorMap(vectorMap, actualResult);

            moveConstructorVectorMap(std::move(vectorMap), actualResult);
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
    TEST_CASE("[Container::VectorMap] move assignment - empty", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(11, 0);
            moveAssignmentVectorMap(std::move(vectorMap), actualResult);
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
    TEST_CASE("[Container::VectorMap] move assignment - full", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentFullResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(12, 0);
            addFullVectorMap(vectorMap, actualResult, 1, false);
            moveAssignmentVectorMap(std::move(vectorMap), actualResult);
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
    TEST_CASE("[Container::VectorMap] move assignment - even", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentEvenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(13, 0);
            addEvenVectorMap(vectorMap, actualResult, 1, false);
            moveAssignmentVectorMap(std::move(vectorMap), actualResult);
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
    TEST_CASE("[Container::VectorMap] move assignment - odd", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentOddResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(14, 0);
            addOddVectorMap(vectorMap, actualResult, 1, false);
            moveAssignmentVectorMap(std::move(vectorMap), actualResult);
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
    TEST_CASE("[Container::VectorMap] move assignment - clear", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentClearResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(15, 0);

            // Add full
            addFullVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Clear
            clearVectorMap(vectorMap, actualResult);

            moveAssignmentVectorMap(std::move(vectorMap), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - empty (literal)
     */
    TEST_CASE("[Container::VectorMap] move constructor - empty (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentEmptyLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(11, createZeroLiteral());
            moveConstructorVectorMap(std::move(vectorMap), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - full (literal)
     */
    TEST_CASE("[Container::VectorMap] move constructor - full (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentFullLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(12, createZeroLiteral());
            addFullVectorMap(vectorMap, actualResult, 1, false);
            moveConstructorVectorMap(std::move(vectorMap), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - even (literal)
     */
    TEST_CASE("[Container::VectorMap] move constructor - even (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentEvenLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(13, createZeroLiteral());
            addEvenVectorMap(vectorMap, actualResult, 1, false);
            moveConstructorVectorMap(std::move(vectorMap), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - odd (literal)
     */
    TEST_CASE("[Container::VectorMap] move constructor - odd (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentOddLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(14, createZeroLiteral());
            addOddVectorMap(vectorMap, actualResult, 1, false);
            moveConstructorVectorMap(std::move(vectorMap), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - clear (literal)
     */
    TEST_CASE("[Container::VectorMap] move constructor - clear (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentClearLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(15, createZeroLiteral());

            // Add full
            addFullVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Clear
            clearVectorMap(vectorMap, actualResult);

            moveConstructorVectorMap(std::move(vectorMap), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - empty (literal)
     */
    TEST_CASE("[Container::VectorMap] move assignment - empty (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentEmptyLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(11, createZeroLiteral());
            moveAssignmentVectorMap(std::move(vectorMap), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - full (literal)
     */
    TEST_CASE("[Container::VectorMap] move assignment - full (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentFullLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(12, createZeroLiteral());
            addFullVectorMap(vectorMap, actualResult, 1, false);
            moveAssignmentVectorMap(std::move(vectorMap), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - even (literal)
     */
    TEST_CASE("[Container::VectorMap] move assignment - even (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentEvenLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(13, createZeroLiteral());
            addEvenVectorMap(vectorMap, actualResult, 1, false);
            moveAssignmentVectorMap(std::move(vectorMap), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - odd (literal)
     */
    TEST_CASE("[Container::VectorMap] move assignment - odd (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentOddLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(14, createZeroLiteral());
            addOddVectorMap(vectorMap, actualResult, 1, false);
            moveAssignmentVectorMap(std::move(vectorMap), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - clear (literal)
     */
    TEST_CASE("[Container::VectorMap] move assignment - clear (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapMoveConstructorAssignmentClearLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(15, createZeroLiteral());

            // Add full
            addFullVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Clear
            clearVectorMap(vectorMap, actualResult);

            moveAssignmentVectorMap(std::move(vectorMap), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Insert
     */
    TEST_CASE("[Container::VectorMap] insert", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapInsertResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(9, 0);

            // lvalue
            TypeT value = 1;
            vectorMap.insert(3, value, false);

            // rvalue
            vectorMap.insert(6, 2, false);

            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Insert with check existence
     */
    TEST_CASE("[Container::VectorMap] insert with check existence", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapInsertResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(9, 0);

            // lvalue
            TypeT value = 1;
            vectorMap.insert(3, value, true);

            // rvalue
            vectorMap.insert(6, 2, true);

            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Insert - multiple occurrences
     */
    TEST_CASE("[Container::VectorMap] insert - multiple occurrences", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapInsertMultipleOccurrencesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(8, 0);
            printVectorMap(vectorMap, actualResult);

            ElementVectorType elementVector { { 0, 7 }, { 1, 6 }, { 4, 3 }, { 6, 1 }, { 7, 0 }, { 3, 4 }, { 4, 4 } };
            insertElementsVectorMap(vectorMap, elementVector, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Insert with check existence - multiple occurrences
     */
    TEST_CASE("[Container::VectorMap] insert with check existence - multiple occurrences", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapInsertWithCheckExistenceMultipleOccurrencesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(8, 0);
            printVectorMap(vectorMap, actualResult);

            ElementVectorType elementVector { { 0, 7 }, { 1, 6 }, { 4, 3 }, { 6, 1 }, { 7, 0 }, { 3, 4 }, { 4, 4 } };
            insertElementsVectorMap(vectorMap, elementVector, actualResult, true);
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
    TEST_CASE("[Container::VectorMap] emplace", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapEmplaceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(7, 0);

            vectorMap.emplace(4, 100);

            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Emplace - multiple occurrences
     */
    TEST_CASE("[Container::VectorMap] emplace - multiple occurrences", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapEmplaceMultipleOccurrencesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(7, 0);

            vectorMap.emplace(3, 99);
            vectorMap.emplace(0, 50);
            vectorMap.emplace(3, 1);

            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Insert (literal)
     */
    TEST_CASE("[Container::VectorMap] insert (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapInsertLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(9, createZeroLiteral());

            // lvalue
            LiteralType lit(1, false);
            vectorMap.insert(3, lit, false);

            // rvalue
            vectorMap.insert(6, LiteralType(2, true), false);

            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Insert with check existence (literal)
     */
    TEST_CASE("[Container::VectorMap] insert with check existence (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapInsertLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(9, createZeroLiteral());

            // lvalue
            LiteralType lit(1, false);
            vectorMap.insert(3, lit, true);

            // rvalue
            vectorMap.insert(6, LiteralType(2, true), true);

            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Insert - multiple occurrences (literal)
     */
    TEST_CASE("[Container::VectorMap] insert - multiple occurrences (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapInsertMultipleOccurrencesLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(8, createZeroLiteral());
            printVectorMap(vectorMap, actualResult);

            ElementLiteralVectorType elementVector { { 0, LiteralType(8, false) }, { 1, LiteralType(7, true) }, { 4, LiteralType(4, false) }, { 6, LiteralType(2, true) }, { 7, LiteralType(1, false) }, { 3, LiteralType(5, true) }, { 4, LiteralType(5, false) } };
            insertElementsVectorMap(vectorMap, elementVector, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Insert with check existence - multiple occurrences (literal)
     */
    TEST_CASE("[Container::VectorMap] insert with check existence - multiple occurrences (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapInsertWithCheckExistenceMultipleOccurrencesLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(8, createZeroLiteral());
            printVectorMap(vectorMap, actualResult);

            ElementLiteralVectorType elementVector { { 0, LiteralType(8, false) }, { 1, LiteralType(7, true) }, { 4, LiteralType(4, false) }, { 6, LiteralType(2, true) }, { 7, LiteralType(1, false) }, { 3, LiteralType(5, true) }, { 4, LiteralType(5, false) } };
            insertElementsVectorMap(vectorMap, elementVector, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Emplace (literal)
     */
    TEST_CASE("[Container::VectorMap] emplace (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapEmplaceLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(7, createZeroLiteral());

            vectorMap.emplace(4, 100, true);

            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Emplace - multiple occurrences (literal)
     */
    TEST_CASE("[Container::VectorMap] emplace - multiple occurrences (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapEmplaceMultipleOccurrencesLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(7, createZeroLiteral());

            vectorMap.emplace(3, 99, false);
            vectorMap.emplace(0, 50, false);
            vectorMap.emplace(3, 1, true);

            printVectorMap(vectorMap, actualResult);
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
    TEST_CASE("[Container::VectorMap] add full", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapAddFullResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(6, 0);
            addFullVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
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
    TEST_CASE("[Container::VectorMap] add even", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapAddEvenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(5, 0);
            addEvenVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
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
    TEST_CASE("[Container::VectorMap] add odd", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapAddOddResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(4, 0);
            addOddVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add full (literal)
     */
    TEST_CASE("[Container::VectorMap] add full (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapAddFullLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(6, createZeroLiteral());
            addFullVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add even (literal)
     */
    TEST_CASE("[Container::VectorMap] add even (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapAddEvenLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(5, createZeroLiteral());
            addEvenVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add odd (literal)
     */
    TEST_CASE("[Container::VectorMap] add odd (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapAddOddLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(4, createZeroLiteral());
            addOddVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
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
    TEST_CASE("[Container::VectorMap] clear full", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapClearFullResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(4, 0);

            // Add full
            addFullVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Clear
            clearVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
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
    TEST_CASE("[Container::VectorMap] clear even", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapClearEvenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(5, 0);

            // Add even
            addEvenVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Clear
            clearVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
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
    TEST_CASE("[Container::VectorMap] clear odd", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapClearOddResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(6, 0);

            // Add odd
            addOddVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Clear
            clearVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
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
    TEST_CASE("[Container::VectorMap] clear empty", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapClearEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(7, 0);
            printVectorMap(vectorMap, actualResult);

            // Clear
            clearVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear full (literal)
     */
    TEST_CASE("[Container::VectorMap] clear full (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapClearFullLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(4, createZeroLiteral());

            // Add full
            addFullVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Clear
            clearVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear even (literal)
     */
    TEST_CASE("[Container::VectorMap] clear even (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapClearEvenLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(5, createZeroLiteral());

            // Add even
            addEvenVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Clear
            clearVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear odd (literal)
     */
    TEST_CASE("[Container::VectorMap] clear odd (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapClearOddLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(6, createZeroLiteral());

            // Add odd
            addOddVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Clear
            clearVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear empty (literal)
     */
    TEST_CASE("[Container::VectorMap] clear empty (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapClearEmptyLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(7, createZeroLiteral());
            printVectorMap(vectorMap, actualResult);

            // Clear
            clearVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Contains, find and subscript operator full
     */
    TEST_CASE("[Container::VectorMap] contains, find and subscript operator full", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapContainsFindAndSubscriptOperatorFullResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(8, 0);

            // Add full
            addFullVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Contains, find and subscript operator
            containsFindAndSubscriptOperatorVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Contains, find and subscript operator even
     */
    TEST_CASE("[Container::VectorMap] contains, find and subscript operator even", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapContainsFindAndSubscriptOperatorEvenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(8, 0);

            // Add even
            addEvenVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Contains, find and subscript operator
            containsFindAndSubscriptOperatorVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Contains, find and subscript operator odd
     */
    TEST_CASE("[Container::VectorMap] contains, find and subscript operator odd", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapContainsFindAndSubscriptOperatorOddResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(8, 0);

            // Add odd
            addOddVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Contains, find and subscript operator
            containsFindAndSubscriptOperatorVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Contains, find and subscript operator - empty
     */
    TEST_CASE("[Container::VectorMap] contains, find and subscript operator - empty", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapContainsFindAndSubscriptOperatorEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(8, 0);
            printVectorMap(vectorMap, actualResult);

            // Contains, find and subscript operator
            containsFindAndSubscriptOperatorVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Contains, find and subscript operator full (literal)
     */
    TEST_CASE("[Container::VectorMap] contains, find and subscript operator full (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapContainsFindAndSubscriptOperatorFullLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(8, createZeroLiteral());

            // Add full
            addFullVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Contains, find and subscript operator
            containsFindAndSubscriptOperatorVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Contains, find and subscript operator even (literal)
     */
    TEST_CASE("[Container::VectorMap] contains, find and subscript operator even (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapContainsFindAndSubscriptOperatorEvenLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(8, createZeroLiteral());

            // Add even
            addEvenVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Contains, find and subscript operator
            containsFindAndSubscriptOperatorVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Contains, find and subscript operator odd (literal)
     */
    TEST_CASE("[Container::VectorMap] contains, find and subscript operator odd (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapContainsFindAndSubscriptOperatorOddLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(8, createZeroLiteral());

            // Add odd
            addOddVectorMap(vectorMap, actualResult);
            printVectorMap(vectorMap, actualResult);

            // Contains, find and subscript operator
            containsFindAndSubscriptOperatorVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Contains, find and subscript operator - empty (literal)
     */
    TEST_CASE("[Container::VectorMap] contains, find and subscript operator - empty (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapContainsFindAndSubscriptOperatorEmptyLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(8, createZeroLiteral());
            printVectorMap(vectorMap, actualResult);

            // Contains, find and subscript operator
            containsFindAndSubscriptOperatorVectorMap(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Find - no element
     */
    TEST_CASE("[Container::VectorMap] find - no element", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapFindNoElementResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(4, 0);
            printVectorMap(vectorMap, actualResult);

            // Find
            const TypeT& value = vectorMap.find(2);
            actualResult << "2: " << std::to_string(value) << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Find - no element (literal)
     */
    TEST_CASE("[Container::VectorMap] find - no element (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapFindNoElementResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(4, createZeroLiteral());
            printVectorMap(vectorMap, actualResult);

            // Find
            const LiteralType& value = vectorMap.find(2);
            actualResult << "2: " << std::to_string(value) << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * No-value representative - not set
     */
    TEST_CASE("[Container::VectorMap] no-value representative - not set", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapNoValueRepresentativeNotSetResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap;
            printNoValueRepresentative(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * No-value representative - set
     */
    TEST_CASE("[Container::VectorMap] no-value representative - set", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapNoValueRepresentativeSetResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapType vectorMap(1, 2);
            printNoValueRepresentative(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * No-value representative (literal)
     */
    TEST_CASE("[Container::VectorMap] no-value representative (literal)", "[Container::VectorMap]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vectorMapNoValueRepresentativeLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VectorMapLiteralType vectorMap(1, LiteralType(3, false));
            printNoValueRepresentative(vectorMap, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Container::VectorMap
