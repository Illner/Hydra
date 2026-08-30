#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/external/unitTesting/Catch2/catch.hpp"
#include "HydraTest/formula/representation/contiguous/subsumption/ContiguousFormulaRepresentationUnsortedSubsumptionTestResult.hpp"

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contiguous/ContiguousFormulaRepresentation.hpp"
#include "Hydra/formula/representation/contiguous/ContiguousFormulaRepresentation.tpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/computeConnectedComponents/ConnectedComponentStructure.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/formula/representation/contiguous/enums/SubsumptionTypeEnum.hpp"

namespace HydraTest::Formula::Representation::Contiguous::UnsortedSubsumption {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
    using FormulaType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::FormulaType;
    using VectorSetType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VectorSetType;
    using VariableSetType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
    using LiteralVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
    using VariableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
    using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
    using VariableSortedVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSortedVectorType;
    using ClauseIdReusableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType;

    using ContiguousFormulaRepresentationConfigurationType = Hydra::Formula::Representation::Contiguous::ContiguousFormulaRepresentationConfiguration;
    using ContiguousFormulaRepresentationType = Hydra::Formula::Representation::Contiguous::ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

    using ConnectedComponentStructure = Hydra::Container::ComputeConnectedComponents::ConnectedComponentStruct<VarT, LiteralT>;

    using IgnorePureLiteralTypeEnum = Hydra::IgnorePureLiteralTypeEnum;
    using SubsumptionTypeEnum = Hydra::Formula::Representation::Contiguous::SubsumptionTypeEnum;
    //endregion

    //region Functions
    void printContiguousFormulaRepresentationUnsortedSubsumption(const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation,
                                                                 std::stringstream& actualResult) {
        actualResult << "Current formula: " << std::endl;
        contiguousFormulaRepresentation.printCurrentFormulaDebug(actualResult, false, false);
        actualResult << std::endl
                     << "--------------------" << std::endl
                     << std::endl;

        actualResult << "Current formula (no duplicate and subsumed clauses): " << std::endl;
        contiguousFormulaRepresentation.printCurrentFormulaDebug(actualResult, true, true);
        actualResult << std::endl
                     << "--------------------" << std::endl
                     << std::endl;
    }

    void printUsedVariables(VectorSetType& usedVariableVectorSet, std::stringstream& actualResult) {
        actualResult << "Used variables:";
        for (std::size_t var : usedVariableVectorSet.getAddedElementVector(true))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
    }

    void printClauses(const ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, ClauseIdReusableVectorType& clauseIdReusableVector,
                      std::stringstream& actualResult, bool considerOnlyVariables) {
        // Variables
        if (considerOnlyVariables)
            std::stable_sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(),
                             ContiguousFormulaRepresentationType::ClauseVariableComparatorFunctor(&contiguousFormulaRepresentation));
        // Literals
        else
            std::stable_sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(),
                             ContiguousFormulaRepresentationType::ClauseComparatorFunctor(&contiguousFormulaRepresentation));

        actualResult << "Current formula (no duplicate and subsumed clauses) - unsorted variant: " << std::endl;
        for (ClauseIdT clauseId : clauseIdReusableVector)
            contiguousFormulaRepresentation.printCurrentClauseDebug(actualResult, clauseId, considerOnlyVariables);
        actualResult << std::endl;
    }

    void processUnsortedSubsumptionAssignment(ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, std::stringstream& actualResult,
                                              bool considerOnlyVariables) {
        LiteralVectorType assignment { LiteralType(7, false),
                                       LiteralType(8, true) };

        ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
        VectorSetType usedVariableVectorSet(contiguousFormulaRepresentation.getNumberOfVariablesInOriginalFormulaUsedForIndexing());

        for (const LiteralType& lit : assignment) {
            actualResult << "Add assignment: " << lit << std::endl;

            VariableVectorType tmp;
            contiguousFormulaRepresentation.addLiteralToPartialAssignment(lit, tmp);
            printContiguousFormulaRepresentationUnsortedSubsumption(contiguousFormulaRepresentation, actualResult);

            contiguousFormulaRepresentation.getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                                                  usedVariableVectorSet, true, considerOnlyVariables, true);

            printClauses(contiguousFormulaRepresentation, clauseIdReusableVector, actualResult, considerOnlyVariables);
            printUsedVariables(usedVariableVectorSet, actualResult);
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }

        actualResult << std::endl
                     << "----------------------------------------" << std::endl
                     << "----------------------------------------" << std::endl
                     << std::endl;

        for (auto it = assignment.rbegin(); it != assignment.rend(); ++it) {
            const LiteralType& lit = *it;

            actualResult << "Remove assignment: " << lit << std::endl;

            VariableVectorType tmp;
            contiguousFormulaRepresentation.removeLiteralFromPartialAssignment(lit, tmp);
            printContiguousFormulaRepresentationUnsortedSubsumption(contiguousFormulaRepresentation, actualResult);

            contiguousFormulaRepresentation.getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                                                  usedVariableVectorSet, true, considerOnlyVariables, true);

            printClauses(contiguousFormulaRepresentation, clauseIdReusableVector, actualResult, considerOnlyVariables);
            printUsedVariables(usedVariableVectorSet, actualResult);
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }
    }

    void processUnsortedSubsumptionCurrentComponent(ContiguousFormulaRepresentationType& contiguousFormulaRepresentation, std::stringstream& actualResult,
                                                    bool considerOnlyVariables) {
        std::vector<VariableSetType> currentComponentVariableSetVector { { 1 }, { 2, 3 }, { 4, 5, 6, 7, 8 } };

        ClauseIdReusableVectorType clauseIdReusableVector(contiguousFormulaRepresentation.getNumberOfOriginalClauses());
        VectorSetType usedVariableVectorSet(contiguousFormulaRepresentation.getNumberOfVariablesInOriginalFormulaUsedForIndexing());

        for (const VariableSetType& currentComponentVariableSet : currentComponentVariableSetVector) {
            actualResult << "Current component:";
            VariableSortedVectorType variableSortedVector = Hydra::Other::sortUnorderedSet(currentComponentVariableSet);
            for (VarT var : variableSortedVector)
                actualResult << " " << std::to_string(var);
            actualResult << std::endl;

            ConnectedComponentStructure connectedComponentStructure(currentComponentVariableSet.size());
            connectedComponentStructure.variableSet.insert(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend());

            contiguousFormulaRepresentation.setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);
            printContiguousFormulaRepresentationUnsortedSubsumption(contiguousFormulaRepresentation, actualResult);

            contiguousFormulaRepresentation.getCurrentComponentNotSubsumedClauses(currentComponentVariableSet, clauseIdReusableVector,
                                                                                  usedVariableVectorSet, true, considerOnlyVariables, true);

            printClauses(contiguousFormulaRepresentation, clauseIdReusableVector, actualResult, considerOnlyVariables);
            printUsedVariables(usedVariableVectorSet, actualResult);

            contiguousFormulaRepresentation.popPreviousComponent(connectedComponentStructure, {});
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }
    }
    //endregion

    //region ContiguousFormulaRepresentation
    ContiguousFormulaRepresentationType createContiguousFormulaRepresentation(SubsumptionTypeEnum subsumptionType) {
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg8(8, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos4, litNeg5, litPos6, zeroLit,   // 21
            litPos2, litPos3, zeroLit,            // 10
            litPos4, litPos7, zeroLit,            // 15
            litPos2, litNeg3, zeroLit,            // 8
            litPos1, zeroLit,                     // 2
            litPos6, litPos7, zeroLit,            // 18
            litNeg2, litPos3, zeroLit,            // 6
            litNeg6, litPos7, zeroLit,            // 16
            litNeg2, litNeg3, zeroLit,            // 4
            litNeg4, litPos5, zeroLit,            // 12
            litNeg2, litNeg3, zeroLit,            // 5
            litPos1, zeroLit,                     // 3
            litNeg4, litPos5, litNeg6, zeroLit,   // 20
            litNeg2, litPos3, zeroLit,            // 7
            litNeg6, litNeg8, zeroLit,            // 17
            litPos2, litNeg3, zeroLit,            // 9
            litNeg1, zeroLit,                     // 0
            litPos6, litNeg8, zeroLit,            // 19
            litPos2, litPos3, zeroLit,            // 11
            litNeg1, zeroLit,                     // 1
            litNeg4, litNeg8, zeroLit,            // 13
            litPos4, litNeg5, zeroLit             // 14
        };

        VarT numberOfVariables = 8;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contiguous::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contiguous::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContiguousFormulaRepresentationConfigurationType configuration;
        configuration.subsumptionType = subsumptionType;

        ContiguousFormulaRepresentationType contiguousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences,
                                                                            configuration);
        return contiguousFormulaRepresentation;
    }
    //endregion

    /**
     * Backward subsumption detection
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] backward subsumption detection", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION);
            printContiguousFormulaRepresentationUnsortedSubsumption(formula, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(formula.getNumberOfOriginalClauses());
            VectorSetType usedVariableVectorSet(formula.getNumberOfVariablesInOriginalFormulaUsedForIndexing());
            formula.getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                          usedVariableVectorSet, true, false, true);
            printClauses(formula, clauseIdReusableVector, actualResult, false);
            printUsedVariables(usedVariableVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward subsumption detection (assignment)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] backward subsumption detection (assignment)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedSubsumptionAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION);
            processUnsortedSubsumptionAssignment(formula, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward subsumption detection (current component)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] backward subsumption detection (current component)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedSubsumptionCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION);
            processUnsortedSubsumptionCurrentComponent(formula, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward variable subsumption detection
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] backward variable subsumption detection", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedVariableSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION);
            printContiguousFormulaRepresentationUnsortedSubsumption(formula, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(formula.getNumberOfOriginalClauses());
            VectorSetType usedVariableVectorSet(formula.getNumberOfVariablesInOriginalFormulaUsedForIndexing());
            formula.getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                          usedVariableVectorSet, true, true, true);
            printClauses(formula, clauseIdReusableVector, actualResult, true);
            printUsedVariables(usedVariableVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward variable subsumption detection (assignment)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] backward variable subsumption detection (assignment)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedVariableSubsumptionAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION);
            processUnsortedSubsumptionAssignment(formula, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward variable subsumption detection (current component)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] backward variable subsumption detection (current component)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedVariableSubsumptionCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION);
            processUnsortedSubsumptionCurrentComponent(formula, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward subsumption detection - intersection
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] backward subsumption detection - intersection", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION);
            printContiguousFormulaRepresentationUnsortedSubsumption(formula, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(formula.getNumberOfOriginalClauses());
            VectorSetType usedVariableVectorSet(formula.getNumberOfVariablesInOriginalFormulaUsedForIndexing());
            formula.getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                          usedVariableVectorSet, true, false, true);
            printClauses(formula, clauseIdReusableVector, actualResult, false);
            printUsedVariables(usedVariableVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward subsumption detection - intersection (assignment)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] backward subsumption detection - intersection (assignment)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedSubsumptionAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION);
            processUnsortedSubsumptionAssignment(formula, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward subsumption detection - intersection (current component)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] backward subsumption detection - intersection (current component)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedSubsumptionCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION);
            processUnsortedSubsumptionCurrentComponent(formula, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward variable subsumption detection - intersection
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] backward variable subsumption detection - intersection", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedVariableSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION);
            printContiguousFormulaRepresentationUnsortedSubsumption(formula, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(formula.getNumberOfOriginalClauses());
            VectorSetType usedVariableVectorSet(formula.getNumberOfVariablesInOriginalFormulaUsedForIndexing());
            formula.getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                          usedVariableVectorSet, true, true, true);
            printClauses(formula, clauseIdReusableVector, actualResult, true);
            printUsedVariables(usedVariableVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward variable subsumption detection - intersection (assignment)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] backward variable subsumption detection - intersection (assignment)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedVariableSubsumptionAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION);
            processUnsortedSubsumptionAssignment(formula, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward variable subsumption detection - intersection (current component)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] backward variable subsumption detection - intersection (current component)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedVariableSubsumptionCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION);
            processUnsortedSubsumptionCurrentComponent(formula, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward subsumption detection
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] forward subsumption detection", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION);
            printContiguousFormulaRepresentationUnsortedSubsumption(formula, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(formula.getNumberOfOriginalClauses());
            VectorSetType usedVariableVectorSet(formula.getNumberOfVariablesInOriginalFormulaUsedForIndexing());
            formula.getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                          usedVariableVectorSet, true, false, true);
            printClauses(formula, clauseIdReusableVector, actualResult, false);
            printUsedVariables(usedVariableVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward subsumption detection (assignment)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] forward subsumption detection (assignment)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedSubsumptionAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION);
            processUnsortedSubsumptionAssignment(formula, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward subsumption detection (current component)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] forward subsumption detection (current component)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedSubsumptionCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION);
            processUnsortedSubsumptionCurrentComponent(formula, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption detection
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] forward variable subsumption detection", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedVariableSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION);
            printContiguousFormulaRepresentationUnsortedSubsumption(formula, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(formula.getNumberOfOriginalClauses());
            VectorSetType usedVariableVectorSet(formula.getNumberOfVariablesInOriginalFormulaUsedForIndexing());
            formula.getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                          usedVariableVectorSet, true, true, true);
            printClauses(formula, clauseIdReusableVector, actualResult, true);
            printUsedVariables(usedVariableVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption detection (assignment)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] forward variable subsumption detection (assignment)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedVariableSubsumptionAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION);
            processUnsortedSubsumptionAssignment(formula, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward variable subsumption detection (current component)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] forward variable subsumption detection (current component)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedVariableSubsumptionCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION);
            processUnsortedSubsumptionCurrentComponent(formula, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] one-literal watching algorithm", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM);
            printContiguousFormulaRepresentationUnsortedSubsumption(formula, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(formula.getNumberOfOriginalClauses());
            VectorSetType usedVariableVectorSet(formula.getNumberOfVariablesInOriginalFormulaUsedForIndexing());
            formula.getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                          usedVariableVectorSet, true, false, true);
            printClauses(formula, clauseIdReusableVector, actualResult, false);
            printUsedVariables(usedVariableVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm (assignment)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] one-literal watching algorithm (assignment)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedSubsumptionAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM);
            processUnsortedSubsumptionAssignment(formula, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm (current component)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] one-literal watching algorithm (current component)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedSubsumptionCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM);
            processUnsortedSubsumptionCurrentComponent(formula, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm variable
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] one-literal watching algorithm variable", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedVariableSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM);
            printContiguousFormulaRepresentationUnsortedSubsumption(formula, actualResult);

            ClauseIdReusableVectorType clauseIdReusableVector(formula.getNumberOfOriginalClauses());
            VectorSetType usedVariableVectorSet(formula.getNumberOfVariablesInOriginalFormulaUsedForIndexing());
            formula.getCurrentComponentNotSubsumedClauses({ 1, 2, 3, 4, 5, 6, 7, 8 }, clauseIdReusableVector,
                                                          usedVariableVectorSet, true, true, true);
            printClauses(formula, clauseIdReusableVector, actualResult, true);
            printUsedVariables(usedVariableVectorSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm variable (assignment)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] one-literal watching algorithm variable (assignment)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedVariableSubsumptionAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM);
            processUnsortedSubsumptionAssignment(formula, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm variable (current component)
     */
    TEST_CASE("[Formula::Representation::Contiguous::UnsortedSubsumption] one-literal watching algorithm variable (current component)", "[Formula::Representation::Contiguous::UnsortedSubsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationUnsortedVariableSubsumptionCurrentComponentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContiguousFormulaRepresentationType formula = createContiguousFormulaRepresentation(SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM);
            processUnsortedSubsumptionCurrentComponent(formula, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Formula::Representation::Contiguous::UnsortedSubsumption
