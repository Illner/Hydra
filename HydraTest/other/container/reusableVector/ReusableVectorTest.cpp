#include <algorithm>
#include <iterator>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/other/container/reusableVector/ReusableVectorTestResult.hpp"

#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/reusableVector/ReusableVector.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"
#include "Hydra/other/operatingSystem/OperatingSystem.hpp"

namespace HydraTest::Container::ReusableVector {

    //region Types
    using TypeT = char8_t;

    using LiteralType = typename Hydra::Formula::Literal<TypeT, TypeT>::LiteralType;

    using TypeVectorType = std::vector<TypeT>;
    using LiteralVectorType = std::vector<LiteralType>;
    using ReusableVectorType = Hydra::Container::ReusableVector::ReusableVector<TypeT>;
    using ReusableVectorLiteralType = Hydra::Container::ReusableVector::ReusableVector<LiteralType>;

    using TypeSetType = typename ReusableVectorType::TypeSetType;
    using LiteralSetType = typename ReusableVectorLiteralType::TypeSetType;
    //endregion

    //region Enums
    enum class IteratorPositionEnum {
        BEGIN,
        MIDDLE,
        END
    };
    //endregion

    //region Functions
    template <typename TypeT>
    void printReusableVector(const Hydra::Container::ReusableVector::ReusableVector<TypeT>& reusableVector, std::stringstream& actualResult) {
        reusableVector.printReusableVectorDebug(actualResult);
        actualResult << std::endl;
    }

    template <typename TypeT>
    void printReusableVectorUsingIterator(const Hydra::Container::ReusableVector::ReusableVector<TypeT>& reusableVector, std::stringstream& actualResult) {
        actualResult << "Reusable vector:";
        for (auto it = reusableVector.cbegin(); it != reusableVector.cend(); ++it)
            actualResult << " " << std::to_string(*it);
        actualResult << std::endl;
    }

    template <typename TypeT>
    void printReusableVectorUsingSubscriptOperator(const Hydra::Container::ReusableVector::ReusableVector<TypeT>& reusableVector, std::stringstream& actualResult) {
        actualResult << "Reusable vector:";

        for (std::size_t i = 0; i < reusableVector.size(); ++i) {
            const TypeT& element = reusableVector[i];
            actualResult << " " << std::to_string(element);
        }

        actualResult << std::endl
                     << std::endl;
    }

    template <typename TypeT>
    void printSet(const Hydra::Other::HashMap::SetType<TypeT>& set, std::stringstream& actualResult) {
        actualResult << "Set:";
        for (const TypeT& element : Hydra::Other::sortUnorderedSet(set))
            actualResult << " " << std::to_string(element);
        actualResult << std::endl;
    }

    void printTitle(const std::string& title, std::stringstream& actualResult, int numberOfDelimiters = 15) {
        Hydra::Other::printTitle(actualResult, " " + title + " ", numberOfDelimiters, '-');
        actualResult << std::endl;
    }

    void printClearTitle(std::stringstream& actualResult) {
        printTitle("clear", actualResult);
    }

    template <typename TypeT>
    void clearReusableVector(Hydra::Container::ReusableVector::ReusableVector<TypeT>& reusableVector,
                             std::stringstream& actualResult, bool printTitle_ = true) {
        if (printTitle_)
            printClearTitle(actualResult);

        reusableVector.clear();
    }

    template <typename TypeT>
    void copySetReusableVector(Hydra::Container::ReusableVector::ReusableVector<TypeT>& reusableVector,
                               const typename Hydra::Container::ReusableVector::ReusableVector<TypeT>::TypeSetType& set,
                               std::stringstream& actualResult, bool printTitle_ = true) {
        if (printTitle_)
            printTitle("copy", actualResult);

        actualResult << "Container:";
        for (const TypeT& element : Hydra::Other::sortUnorderedSet(set))
            actualResult << " " << std::to_string(element);
        actualResult << std::endl
                     << std::endl;

        reusableVector.copySet(set);
        reusableVector.sort();
    }

    template <typename TypeT>
    void copyVectorReusableVector(Hydra::Container::ReusableVector::ReusableVector<TypeT>& reusableVector, const std::vector<TypeT>& vector,
                                  std::stringstream& actualResult, bool printTitle_ = true) {
        if (printTitle_)
            printTitle("copy", actualResult);

        actualResult << "Container:";
        for (const TypeT& element : vector)
            actualResult << " " << std::to_string(element);
        actualResult << std::endl
                     << std::endl;

        reusableVector.copyVector(vector);
    }

    void fillReusableVector(ReusableVectorType& reusableVector, std::stringstream& actualResult,
                            bool half = false, TypeT initialValue = 1, bool printTitle_ = true) {
        if (printTitle_)
            printTitle(half ? "half-fill" : "fill", actualResult);

        std::size_t capacity = reusableVector.capacity();

        if (half)
            capacity = static_cast<std::size_t>(capacity / 2);

        for (TypeT i = initialValue; i <= (static_cast<TypeT>(capacity) + initialValue - 1); ++i)
            reusableVector.push_back(i);
    }

    void fillReusableVector(ReusableVectorLiteralType& reusableVector, std::stringstream& actualResult,
                            bool half = false, TypeT initialVariable = 1, bool printTitle_ = true) {
        if (printTitle_)
            printTitle(half ? "half-fill" : "fill", actualResult);

        bool sign = true;
        std::size_t capacity = reusableVector.capacity();

        if (half)
            capacity = static_cast<std::size_t>(capacity / 2);

        for (TypeT var = initialVariable; var <= (static_cast<TypeT>(capacity) + initialVariable - 1); ++var) {
            reusableVector.emplace_back(var, sign);

            sign = !sign;
        }
    }

    template <typename TypeT>
    void addElementsReusableVector(Hydra::Container::ReusableVector::ReusableVector<TypeT>& reusableVector, const std::vector<TypeT>& elementVector,
                                   std::stringstream& actualResult, bool printTitle_ = true) {
        if (printTitle_)
            printTitle("add elements", actualResult, 20);

        for (const TypeT& element : elementVector)
            reusableVector.push_back(element);
    }

    template <typename TypeT>
    void moveConstructorReusableVector(Hydra::Container::ReusableVector::ReusableVector<TypeT>&& reusableVector, std::stringstream& actualResult) {
        printTitle("before", actualResult);
        printReusableVector(reusableVector, actualResult);

        Hydra::Container::ReusableVector::ReusableVector<TypeT> reusableVectorMoved(std::move(reusableVector));

        printTitle("after", actualResult);
        printReusableVector(reusableVector, actualResult);

        printTitle("moved", actualResult);
        printReusableVector(reusableVectorMoved, actualResult);
    }

    template <typename TypeT>
    void moveAssignmentReusableVector(Hydra::Container::ReusableVector::ReusableVector<TypeT>&& reusableVector, std::stringstream& actualResult) {
        printTitle("before", actualResult);
        printReusableVector(reusableVector, actualResult);

        Hydra::Container::ReusableVector::ReusableVector<TypeT> reusableVectorMoved = std::move(reusableVector);

        printTitle("after", actualResult);
        printReusableVector(reusableVector, actualResult);

        printTitle("moved", actualResult);
        printReusableVector(reusableVectorMoved, actualResult);
    }

    template <typename TypeT>
    void backReusableVector(const Hydra::Container::ReusableVector::ReusableVector<TypeT>& reusableVector, std::stringstream& actualResult) {
        const TypeT& lastElement = reusableVector.back();

        actualResult << "Last element: " << std::to_string(lastElement) << std::endl;
        actualResult << std::endl;
    }

    template <typename TypeT>
    void shuffle(std::vector<TypeT>& typeVector) {
        #ifdef __CYGWIN__
        std::random_device rd { "/dev/urandom" };
        #else
        std::random_device rd;
        #endif

        std::mt19937 generator(rd());

        std::shuffle(typeVector.begin(), typeVector.end(), generator);
    }

    TypeVectorType createTypeVector(TypeT firstElement, TypeT lastElement, bool shuffleVector = false) {
        TypeVectorType typeVector;
        typeVector.reserve(lastElement - firstElement + 1);

        for (TypeT element = firstElement; element <= lastElement; ++element)
            typeVector.emplace_back(element);

        if (shuffleVector)
            shuffle(typeVector);

        return typeVector;
    }

    LiteralVectorType createLiteralVector(TypeT firstVariable, TypeT lastVariable, bool shuffleVector = false) {
        LiteralVectorType literalVector;
        literalVector.reserve(lastVariable - firstVariable + 1);

        bool sign = true;

        for (TypeT var = firstVariable; var <= lastVariable; ++var) {
            literalVector.emplace_back(var, sign);

            sign = !sign;
        }

        if (shuffleVector)
            shuffle(literalVector);

        return literalVector;
    }

    TypeSetType createTypeSet(TypeT firstElement, TypeT lastElement) {
        TypeSetType typeSet(lastElement - firstElement + 1);

        for (TypeT element = firstElement; element <= lastElement; ++element)
            typeSet.emplace(element);

        return typeSet;
    }

    LiteralSetType createLiteralSet(TypeT firstVariable, TypeT lastVariable) {
        LiteralSetType literalSet(lastVariable - firstVariable + 1);

        bool sign = true;

        for (TypeT var = firstVariable; var <= lastVariable; ++var) {
            literalSet.emplace(var, sign);

            sign = !sign;
        }

        return literalSet;
    }

    template <typename TypeT>
    void eraseReusableVector(Hydra::Container::ReusableVector::ReusableVector<TypeT>& reusableVector, IteratorPositionEnum iteratorPosition,
                             std::stringstream& actualResult, bool printTitle_ = true) {
        if (printTitle_)
            printTitle("erase", actualResult);

        auto it = reusableVector.begin();

        actualResult << "Iterator position: ";
        // Begin
        if (iteratorPosition == IteratorPositionEnum::BEGIN) {
            actualResult << "begin" << std::endl;
            it = reusableVector.begin();
        }
        // Middle
        else if (iteratorPosition == IteratorPositionEnum::MIDDLE) {
            actualResult << "middle" << std::endl;
            std::advance(it, static_cast<std::size_t>(reusableVector.size() / 2));
        }
        // End
        else if (iteratorPosition == IteratorPositionEnum::END) {
            actualResult << "end" << std::endl;
            it = reusableVector.end();
        }
        actualResult << std::endl;

        reusableVector.erase(it);
        printReusableVector(reusableVector, actualResult);
    }
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[Container::ReusableVector] constructor", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(10);
            printReusableVector(reusableVector, actualResult);
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
    TEST_CASE("[Container::ReusableVector] constructor - empty", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorConstructorEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector;
            printReusableVector(reusableVector, actualResult);
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
    TEST_CASE("[Container::ReusableVector] constructor (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(10);
            printReusableVector(reusableVector, actualResult);
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
    TEST_CASE("[Container::ReusableVector] constructor - empty (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorConstructorEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector;
            printReusableVector(reusableVector, actualResult);
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
    TEST_CASE("[Container::ReusableVector] move constructor - empty", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(10);
            moveConstructorReusableVector(std::move(reusableVector), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - half-fill
     */
    TEST_CASE("[Container::ReusableVector] move constructor - half-fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentHalfFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, true, 1, false);
            moveConstructorReusableVector(std::move(reusableVector), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - fill
     */
    TEST_CASE("[Container::ReusableVector] move constructor - fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            moveConstructorReusableVector(std::move(reusableVector), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - fill - clear - half-fill
     */
    TEST_CASE("[Container::ReusableVector] move constructor - fill - clear - half-fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentFillClearHalfFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            clearReusableVector(reusableVector, actualResult, false);
            fillReusableVector(reusableVector, actualResult, true, 11, false);
            moveConstructorReusableVector(std::move(reusableVector), actualResult);
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
    TEST_CASE("[Container::ReusableVector] move assignment - empty", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(10);
            moveAssignmentReusableVector(std::move(reusableVector), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - half-fill
     */
    TEST_CASE("[Container::ReusableVector] move assignment - half-fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentHalfFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, true, 1, false);
            moveAssignmentReusableVector(std::move(reusableVector), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - fill
     */
    TEST_CASE("[Container::ReusableVector] move assignment - fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            moveAssignmentReusableVector(std::move(reusableVector), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - fill - clear - half-fill
     */
    TEST_CASE("[Container::ReusableVector] move assignment - fill - clear - half-fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentFillClearHalfFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            clearReusableVector(reusableVector, actualResult, false);
            fillReusableVector(reusableVector, actualResult, true, 11, false);
            moveAssignmentReusableVector(std::move(reusableVector), actualResult);
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
    TEST_CASE("[Container::ReusableVector] move constructor - empty (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentEmptyLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(10);
            moveConstructorReusableVector(std::move(reusableVector), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - half-fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] move constructor - half-fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentHalfFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, true, 1, false);
            moveConstructorReusableVector(std::move(reusableVector), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] move constructor - fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            moveConstructorReusableVector(std::move(reusableVector), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move constructor - fill - clear - half-fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] move constructor - fill - clear - half-fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentFillClearHalfFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            clearReusableVector(reusableVector, actualResult, false);
            fillReusableVector(reusableVector, actualResult, true, 11, false);
            moveConstructorReusableVector(std::move(reusableVector), actualResult);
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
    TEST_CASE("[Container::ReusableVector] move assignment - empty (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentEmptyLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(10);
            moveAssignmentReusableVector(std::move(reusableVector), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - half-fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] move assignment - half-fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentHalfFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, true, 1, false);
            moveAssignmentReusableVector(std::move(reusableVector), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] move assignment - fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            moveAssignmentReusableVector(std::move(reusableVector), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Move assignment - fill - clear - half-fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] move assignment - fill - clear - half-fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorMoveConstructorAssignmentFillClearHalfFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            clearReusableVector(reusableVector, actualResult, false);
            fillReusableVector(reusableVector, actualResult, true, 11, false);
            moveAssignmentReusableVector(std::move(reusableVector), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Push back
     */
    TEST_CASE("[Container::ReusableVector] push back", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorPushBackResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(9);

            // lvalue
            TypeT element = 1;
            reusableVector.push_back(element);

            // rvalue
            reusableVector.push_back(2);

            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Push back - full
     */
    TEST_CASE("[Container::ReusableVector] push back - full", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorPushBackFullResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(3);
            fillReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            reusableVector.push_back(4);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Emplace back
     */
    TEST_CASE("[Container::ReusableVector] emplace back", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEmplaceBackResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(8);

            reusableVector.emplace_back(1);

            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Emplace back - full
     */
    TEST_CASE("[Container::ReusableVector] emplace back - full", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEmplaceBackFullResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(2);
            fillReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            reusableVector.emplace_back(3);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Push back (literal)
     */
    TEST_CASE("[Container::ReusableVector] push back (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorPushBackLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(9);

            // lvalue
            LiteralType lit(1, true);
            reusableVector.push_back(lit);

            // rvalue
            reusableVector.push_back(LiteralType(2, false));

            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Push back - full (literal)
     */
    TEST_CASE("[Container::ReusableVector] push back - full (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorPushBackFullLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(3);
            fillReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            reusableVector.push_back(LiteralType(4, true));
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Emplace back (literal)
     */
    TEST_CASE("[Container::ReusableVector] emplace back (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEmplaceBackLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(8);

            reusableVector.emplace_back(1, false);

            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Emplace back - full (literal)
     */
    TEST_CASE("[Container::ReusableVector] emplace back - full (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEmplaceBackFullLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(2);
            fillReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            reusableVector.emplace_back(3, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Fill
     */
    TEST_CASE("[Container::ReusableVector] fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(7);
            fillReusableVector(reusableVector, actualResult);

            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Half-fill
     */
    TEST_CASE("[Container::ReusableVector] half-fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorHalfFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(6);
            fillReusableVector(reusableVector, actualResult, true);

            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(7);
            fillReusableVector(reusableVector, actualResult);

            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Half-fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] half-fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorHalfFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(6);
            fillReusableVector(reusableVector, actualResult, true);

            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Iterator - fill
     */
    TEST_CASE("[Container::ReusableVector] iterator - fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorIteratorFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(5);
            fillReusableVector(reusableVector, actualResult);

            printReusableVectorUsingIterator(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Iterator - half-fill
     */
    TEST_CASE("[Container::ReusableVector] iterator - half-fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorIteratorHalfFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(4);
            fillReusableVector(reusableVector, actualResult, true);

            printReusableVectorUsingIterator(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Iterator - fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] iterator - fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorIteratorFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(5);
            fillReusableVector(reusableVector, actualResult);

            printReusableVectorUsingIterator(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Iterator - half-fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] iterator - half-fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorIteratorHalfFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(4);
            fillReusableVector(reusableVector, actualResult, true);

            printReusableVectorUsingIterator(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear - fill
     */
    TEST_CASE("[Container::ReusableVector] clear - fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorClearFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(11);

            // Fill
            fillReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear - half-fill
     */
    TEST_CASE("[Container::ReusableVector] clear - half-fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorClearHalfFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(12);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Fill - clear - half-fill
     */
    TEST_CASE("[Container::ReusableVector] fill - clear - half-fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorFillClearHalfFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(13);

            // Fill
            fillReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true, 14);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear - fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] clear - fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorClearFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(11);

            // Fill
            fillReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Clear - half-fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] clear - half-fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorClearHalfFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(12);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Fill - clear - half-fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] fill - clear - half-fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorFillClearHalfFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(13);

            // Fill
            fillReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true, 14);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Subscript operator
     */
    TEST_CASE("[Container::ReusableVector] subscript operator", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorSubscriptOperatorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(10);

            // Empty
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true);
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);

            // Fill
            fillReusableVector(reusableVector, actualResult, true, 10);
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Subscript operator - clear
     */
    TEST_CASE("[Container::ReusableVector] subscript operator - clear", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorSubscriptOperatorClearResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(8);

            // Fill
            fillReusableVector(reusableVector, actualResult, false, 10);
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true);
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Subscript operator - inactive element
     */
    TEST_CASE("[Container::ReusableVector] subscript operator - inactive element", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorSubscriptOperatorInactiveElementResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(6);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true);
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);

            reusableVector[3];
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Subscript operator (literal)
     */
    TEST_CASE("[Container::ReusableVector] subscript operator (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorSubscriptOperatorLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(10);

            // Empty
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true);
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);

            // Fill
            fillReusableVector(reusableVector, actualResult, true, 10);
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Subscript operator - clear (literal)
     */
    TEST_CASE("[Container::ReusableVector] subscript operator - clear (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorSubscriptOperatorClearLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(8);

            // Fill
            fillReusableVector(reusableVector, actualResult, false, 10);
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true);
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Subscript operator - inactive element (literal)
     */
    TEST_CASE("[Container::ReusableVector] subscript operator - inactive element (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorSubscriptOperatorInactiveElementLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(6);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true);
            printReusableVector(reusableVector, actualResult);
            printReusableVectorUsingSubscriptOperator(reusableVector, actualResult);

            reusableVector[3];
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Back
     */
    TEST_CASE("[Container::ReusableVector] back", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorBackResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(4);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true);
            printReusableVector(reusableVector, actualResult);
            backReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Fill
            fillReusableVector(reusableVector, actualResult, false, 5);
            printReusableVector(reusableVector, actualResult);
            backReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true, 9);
            printReusableVector(reusableVector, actualResult);
            backReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Back - empty
     */
    TEST_CASE("[Container::ReusableVector] back - empty", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorBackEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(2);
            backReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Back (literal)
     */
    TEST_CASE("[Container::ReusableVector] back (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorBackLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(5);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true);
            printReusableVector(reusableVector, actualResult);
            backReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Fill
            fillReusableVector(reusableVector, actualResult, false, 6);
            printReusableVector(reusableVector, actualResult);
            backReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true, 11);
            printReusableVector(reusableVector, actualResult);
            backReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Back - empty (literal)
     */
    TEST_CASE("[Container::ReusableVector] back - empty (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorBackEmptyLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(2);
            backReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sort
     */
    TEST_CASE("[Container::ReusableVector] sort", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorSortResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(20);
            reusableVector.sort();

            // Half-fill
            addElementsReusableVector(reusableVector, createTypeVector(1, 10, true), actualResult);
            reusableVector.sort();
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Fill
            addElementsReusableVector(reusableVector, createTypeVector(21, 40, true), actualResult);
            reusableVector.sort();
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            addElementsReusableVector(reusableVector, createTypeVector(41, 50, true), actualResult);
            reusableVector.sort();
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sort (literal)
     */
    TEST_CASE("[Container::ReusableVector] sort (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorSortLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(20);
            reusableVector.sort();

            // Half-fill
            addElementsReusableVector(reusableVector, createLiteralVector(1, 10, true), actualResult);
            reusableVector.sort();
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Fill
            addElementsReusableVector(reusableVector, createLiteralVector(21, 40, true), actualResult);
            reusableVector.sort();
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            addElementsReusableVector(reusableVector, createLiteralVector(41, 50, true), actualResult);
            reusableVector.sort();
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy set
     */
    TEST_CASE("[Container::ReusableVector] copy set", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetVectorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(10);

            // Empty
            copySetReusableVector(reusableVector, {}, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            copySetReusableVector(reusableVector, createTypeSet(1, 5), actualResult);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Fill
            copySetReusableVector(reusableVector, createTypeSet(11, 20), actualResult);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            copySetReusableVector(reusableVector, createTypeSet(21, 25), actualResult);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy set - exceeding capacity
     */
    TEST_CASE("[Container::ReusableVector] copy set - exceeding capacity", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetVectorExceedingCapacityResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(5);
            copySetReusableVector(reusableVector, createTypeSet(1, 6), actualResult);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy set (literal)
     */
    TEST_CASE("[Container::ReusableVector] copy set (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetVectorLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(10);

            // Empty
            copySetReusableVector(reusableVector, {}, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            copySetReusableVector(reusableVector, createLiteralSet(1, 5), actualResult);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Fill
            copySetReusableVector(reusableVector, createLiteralSet(11, 20), actualResult);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            copySetReusableVector(reusableVector, createLiteralSet(21, 25), actualResult);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy set - exceeding capacity (literal)
     */
    TEST_CASE("[Container::ReusableVector] copy set - exceeding capacity (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetVectorExceedingCapacityLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(5);
            copySetReusableVector(reusableVector, createLiteralSet(1, 6), actualResult);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy vector
     */
    TEST_CASE("[Container::ReusableVector] copy vector", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetVectorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(10);

            // Empty
            copyVectorReusableVector(reusableVector, {}, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            copyVectorReusableVector(reusableVector, createTypeVector(1, 5), actualResult);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Fill
            copyVectorReusableVector(reusableVector, createTypeVector(11, 20), actualResult);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            copyVectorReusableVector(reusableVector, createTypeVector(21, 25), actualResult);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy vector - exceeding capacity
     */
    TEST_CASE("[Container::ReusableVector] copy vector - exceeding capacity", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetVectorExceedingCapacityResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(5);
            copyVectorReusableVector(reusableVector, createTypeVector(1, 6), actualResult);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy vector (literal)
     */
    TEST_CASE("[Container::ReusableVector] copy vector (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetVectorLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(10);

            // Empty
            copyVectorReusableVector(reusableVector, {}, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            copyVectorReusableVector(reusableVector, createLiteralVector(1, 5), actualResult);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Fill
            copyVectorReusableVector(reusableVector, createLiteralVector(11, 20), actualResult);
            printReusableVector(reusableVector, actualResult);

            // Clear
            clearReusableVector(reusableVector, actualResult);
            printReusableVector(reusableVector, actualResult);

            // Half-fill
            copyVectorReusableVector(reusableVector, createLiteralVector(21, 25), actualResult);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy vector - exceeding capacity (literal)
     */
    TEST_CASE("[Container::ReusableVector] copy vector - exceeding capacity (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetVectorExceedingCapacityLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(5);
            copyVectorReusableVector(reusableVector, createLiteralVector(1, 6), actualResult);
            printReusableVector(reusableVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Erase - empty
     */
    TEST_CASE("[Container::ReusableVector] erase - empty", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEraseEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(4);
            printReusableVector(reusableVector, actualResult);

            eraseReusableVector(reusableVector, IteratorPositionEnum::END, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::MIDDLE, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::BEGIN, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Erase - half-fill
     */
    TEST_CASE("[Container::ReusableVector] erase - half-fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEraseHalfFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(8);
            fillReusableVector(reusableVector, actualResult, true, 1, false);
            printReusableVector(reusableVector, actualResult);

            eraseReusableVector(reusableVector, IteratorPositionEnum::END, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::MIDDLE, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::BEGIN, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Erase - fill
     */
    TEST_CASE("[Container::ReusableVector] erase - fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEraseFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            printReusableVector(reusableVector, actualResult);

            eraseReusableVector(reusableVector, IteratorPositionEnum::END, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::MIDDLE, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::BEGIN, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Erase - half-fill - begin
     */
    TEST_CASE("[Container::ReusableVector] erase - half-fill - begin", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEraseHalfFillBeginResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(14);
            fillReusableVector(reusableVector, actualResult, true, 1, false);
            printReusableVector(reusableVector, actualResult);

            eraseReusableVector(reusableVector, IteratorPositionEnum::BEGIN, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Erase - fill - begin
     */
    TEST_CASE("[Container::ReusableVector] erase - fill - begin", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEraseFillBeginResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(12);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            printReusableVector(reusableVector, actualResult);

            eraseReusableVector(reusableVector, IteratorPositionEnum::BEGIN, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Fill - clear - erase
     */
    TEST_CASE("[Container::ReusableVector] fill - clear - erase", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorFillClearEraseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(6);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            clearReusableVector(reusableVector, actualResult, false);
            printReusableVector(reusableVector, actualResult);

            eraseReusableVector(reusableVector, IteratorPositionEnum::END, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::MIDDLE, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::BEGIN, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Erase - empty (literal)
     */
    TEST_CASE("[Container::ReusableVector] erase - empty (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEraseEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(4);
            printReusableVector(reusableVector, actualResult);

            eraseReusableVector(reusableVector, IteratorPositionEnum::END, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::MIDDLE, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::BEGIN, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Erase - half-fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] erase - half-fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEraseHalfFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(8);
            fillReusableVector(reusableVector, actualResult, true, 1, false);
            printReusableVector(reusableVector, actualResult);

            eraseReusableVector(reusableVector, IteratorPositionEnum::END, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::MIDDLE, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::BEGIN, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Erase - fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] erase - fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEraseFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(10);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            printReusableVector(reusableVector, actualResult);

            eraseReusableVector(reusableVector, IteratorPositionEnum::END, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::MIDDLE, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::BEGIN, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Erase - half-fill - begin (literal)
     */
    TEST_CASE("[Container::ReusableVector] erase - half-fill - begin (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEraseHalfFillBeginLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(14);
            fillReusableVector(reusableVector, actualResult, true, 1, false);
            printReusableVector(reusableVector, actualResult);

            eraseReusableVector(reusableVector, IteratorPositionEnum::BEGIN, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Erase - fill - begin (literal)
     */
    TEST_CASE("[Container::ReusableVector] erase - fill - begin (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorEraseFillBeginLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(12);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            printReusableVector(reusableVector, actualResult);

            eraseReusableVector(reusableVector, IteratorPositionEnum::BEGIN, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Fill - clear - erase (literal)
     */
    TEST_CASE("[Container::ReusableVector] fill - clear - erase (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorFillClearEraseLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(6);
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            clearReusableVector(reusableVector, actualResult, false);
            printReusableVector(reusableVector, actualResult);

            eraseReusableVector(reusableVector, IteratorPositionEnum::END, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::MIDDLE, actualResult);
            eraseReusableVector(reusableVector, IteratorPositionEnum::BEGIN, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy set - empty
     */
    TEST_CASE("[Container::ReusableVector] copy set - empty", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(2);
            printReusableVector(reusableVector, actualResult);

            // Set
            TypeSetType set = reusableVector.createSetUsingEmplace();
            printSet(set, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy set - fill
     */
    TEST_CASE("[Container::ReusableVector] copy set - fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(3);

            // Fill
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            printReusableVector(reusableVector, actualResult);

            // Set
            TypeSetType set = reusableVector.createSetUsingEmplace();
            printSet(set, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy set - half-fill
     */
    TEST_CASE("[Container::ReusableVector] copy set - half-fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetHalfFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(4);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true, 1, false);
            printReusableVector(reusableVector, actualResult);

            // Set
            TypeSetType set = reusableVector.createSetUsingEmplace();
            printSet(set, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy set - fill - clear - half-fill
     */
    TEST_CASE("[Container::ReusableVector] copy set - fill - clear - half-fill", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetFillClearHalfFillResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorType reusableVector(6);

            // Fill
            fillReusableVector(reusableVector, actualResult, false, 1, false);

            // Clear
            clearReusableVector(reusableVector, actualResult, false);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true, 7, false);
            printReusableVector(reusableVector, actualResult);

            // Set
            TypeSetType set = reusableVector.createSetUsingEmplace();
            printSet(set, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy set - empty (literal)
     */
    TEST_CASE("[Container::ReusableVector] copy set - empty (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetEmptyLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(2);
            printReusableVector(reusableVector, actualResult);

            // Set
            LiteralSetType set = reusableVector.createSet();
            printSet(set, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy set - fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] copy set - fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(3);

            // Fill
            fillReusableVector(reusableVector, actualResult, false, 1, false);
            printReusableVector(reusableVector, actualResult);

            // Set
            LiteralSetType set = reusableVector.createSet();
            printSet(set, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy set - half-fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] copy set - half-fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetHalfFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(4);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true, 1, false);
            printReusableVector(reusableVector, actualResult);

            // Set
            LiteralSetType set = reusableVector.createSet();
            printSet(set, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy set - fill - clear - half-fill (literal)
     */
    TEST_CASE("[Container::ReusableVector] copy set - fill - clear - half-fill (literal)", "[Container::ReusableVector]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          reusableVectorCopySetFillClearHalfFillLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ReusableVectorLiteralType reusableVector(6);

            // Fill
            fillReusableVector(reusableVector, actualResult, false, 1, false);

            // Clear
            clearReusableVector(reusableVector, actualResult, false);

            // Half-fill
            fillReusableVector(reusableVector, actualResult, true, 7, false);
            printReusableVector(reusableVector, actualResult);

            // Set
            LiteralSetType set = reusableVector.createSet();
            printSet(set, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Container::ReusableVector
