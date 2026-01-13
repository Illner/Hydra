#include <cassert>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/formula/structuralRestrictedRepresentation/CreateFormula.hpp"
#include "HydraTest/formula/structuralRestrictedRepresentation/StructuralRestrictedFormulaRepresentationTestResult.hpp"

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/structuralRestrictedRepresentation/StructuralRestrictedFormulaRepresentation.hpp"
#include "Hydra/other/Other.hpp"

#include "Hydra/circuit/node/enums/FormulaLeafPostprocessingTypeEnum.hpp"
#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/formula/enums/StructuralRestrictedFormulaRepresentationTypeEnum.hpp"

namespace HydraTest::Formula::StructuralRestrictedRepresentation {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using ConnectedComponentType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentType;
    using LiteralType = typename Hydra::Formula::StructuralRestrictedRepresentation::StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::LiteralType;
    using VariableSetType = typename Hydra::Formula::StructuralRestrictedRepresentation::StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::VariableSetType;
    using PureVariableRemovedClausesVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::PureVariableRemovedClausesVectorType;
    using PartialAssignmentType = typename Hydra::Formula::StructuralRestrictedRepresentation::StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::PartialAssignmentType;
    using VariableSortedVectorType = typename Hydra::Formula::StructuralRestrictedRepresentation::StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::VariableSortedVectorType;
    using MappingFromVariableToVariableType = typename Hydra::Formula::StructuralRestrictedRepresentation::StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::MappingFromVariableToVariableType;

    using ConnectedComponentStruct = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentStruct;

    using FormulaRepresentationAbstractPtrType = Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;
    using FormulaRepresentationAbstractConstPtrType = const Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;
    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;
    using StructuralRestrictedFormulaRepresentationType = Hydra::Formula::StructuralRestrictedRepresentation::StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

    using IgnorePureLiteralTypeEnum = Hydra::IgnorePureLiteralTypeEnum;
    using FormulaLeafPostprocessingTypeEnum = Hydra::Circuit::Node::FormulaLeafPostprocessingTypeEnum;
    using StructuralRestrictedFormulaRepresentationTypeEnum = Hydra::Formula::StructuralRestrictedRepresentation::StructuralRestrictedFormulaRepresentationTypeEnum;
    //endregion

    //region Functions
    void printFormula(FormulaRepresentationAbstractConstPtrType formulaRepresentationAbstractPtr, std::stringstream& actualResult,
                      bool removeDuplicateClauses = false, bool removeSubsumedClauses = false) {
        actualResult << "Formula: ";
        formulaRepresentationAbstractPtr->printCurrentFormulaDebug(actualResult, removeDuplicateClauses, removeSubsumedClauses);
        actualResult << std::endl;
        actualResult << std::endl;
    }

    void printStructuralRestrictedFormulaRepresentation(const StructuralRestrictedFormulaRepresentationType& structuralRestrictedFormulaRepresentation,
                                                        std::stringstream& actualResult) {
        structuralRestrictedFormulaRepresentation.printStructuralRestrictedFormulaRepresentationDebug(actualResult);
        actualResult << std::endl;
    }

    void printVariablesInFormula(const StructuralRestrictedFormulaRepresentationType& structuralRestrictedFormulaRepresentation, std::stringstream& actualResult) {
        VariableSortedVectorType variableSortedVector = structuralRestrictedFormulaRepresentation.getVariableSortedVector();

        actualResult << "Variables:";
        for (VarT var : variableSortedVector)
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
    }

    void printPartialAssignment(const PartialAssignmentType& partialAssignment, std::stringstream& actualResult) {
        actualResult << "Partial assignment: " << partialAssignment << std::endl;
    }

    void printFormulaInDimacsCnfFormat(const StructuralRestrictedFormulaRepresentationType& structuralRestrictedFormulaRepresentation,
                                       std::stringstream& actualResult, const MappingFromVariableToVariableType& mappingFromVarToIndex = {}) {
        actualResult << "Formula in the DIMACS format:" << std::endl;
        structuralRestrictedFormulaRepresentation.printFormulaInDimacsCnfFormat(actualResult, mappingFromVarToIndex);
        actualResult << std::endl;
    }

    void printConnectedComponents(const ConnectedComponentType& connectedComponents, std::stringstream& actualResult) {
        actualResult << "Connected components:" << std::endl;

        for (const ConnectedComponentStruct& connectedComponentStruct : connectedComponents) {
            actualResult << "\t";

            for (VarT var : Hydra::Other::sortUnorderedSet(connectedComponentStruct.variableSet))
                actualResult << " " << std::to_string(var);

            actualResult << std::endl;
        }

        actualResult << std::endl;
    }

    void printSetNewConnectedComponent(const ConnectedComponentStruct& newConnectedComponent, std::stringstream& actualResult) {
        actualResult << "----------------------------------------" << std::endl;
        actualResult << "Set connected component:";
        for (VarT var : Hydra::Other::sortUnorderedSet(newConnectedComponent.variableSet))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
        actualResult << "----------------------------------------" << std::endl;
    }

    void printPopPreviousConnectedComponent(const ConnectedComponentStruct& newConnectedComponent, std::stringstream& actualResult) {
        actualResult << "----------------------------------------" << std::endl;
        actualResult << "Pop connected component:";
        for (VarT var : Hydra::Other::sortUnorderedSet(newConnectedComponent.variableSet))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
        actualResult << "----------------------------------------" << std::endl;
    }

    void processIsSatisfiableUnderCompleteAssignment(const StructuralRestrictedFormulaRepresentationType& structuralRestrictedFormulaRepresentation,
                                                     const PartialAssignmentType& completeAssignment, std::stringstream& actualResult) {
        printPartialAssignment(completeAssignment, actualResult);

        bool isSatisfiable = structuralRestrictedFormulaRepresentation.isSatisfiableUnderCompleteAssignment(completeAssignment);

        actualResult << "Is satisfiable: " << std::to_string(isSatisfiable) << std::endl;
        actualResult << std::endl;
    }

    void assignLiteral(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, VariableSetType& currentComponentVariableSet,
                       const LiteralType& lit, std::stringstream& actualResult) {
        assert(Hydra::Other::containInSet(currentComponentVariableSet, lit.getVariable()));   // in the current component

        actualResult << "--------------------------------------------------------------------------------" << std::endl;
        actualResult << "Assign literal: " << lit << std::endl;
        actualResult << "--------------------------------------------------------------------------------" << std::endl;
        VariableSortedVectorType freeVariableVector;
        currentComponentVariableSet.erase(lit.getVariable());
        formulaRepresentationAbstractPtr->addLiteralToPartialAssignment(lit, freeVariableVector);

        // Remove the free variables
        for (VarT var : freeVariableVector)
            currentComponentVariableSet.erase(var);
    }
    //endregion

    #if defined(BELLA_COMPILER)
    /**
     * Krom-C (none)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] Krom-C (none)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationKromCNoneResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createKromCNone<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet,
                                                                                                    FormulaLeafPostprocessingTypeEnum::NONE,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::Krom_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Krom-C (no duplicate)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] Krom-C (no duplicate)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationKromCNoDuplicateResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createKromCNoDuplicate<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet,
                                                                                                    FormulaLeafPostprocessingTypeEnum::NO_DUPLICATE_CLAUSES,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::Krom_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Krom-C (no subsumed)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] Krom-C (no subsumed)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationKromCNoSubsumedResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createKromCNoSubsumed<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet,
                                                                                                    FormulaLeafPostprocessingTypeEnum::NO_SUBSUMED_CLAUSES,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::Krom_C,
                                                                                                    false);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Horn-C (none)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] Horn-C (none)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationHornCNoneResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createHornCNone<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet,
                                                                                                    FormulaLeafPostprocessingTypeEnum::NONE,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::Horn_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Horn-C (no duplicate)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] Horn-C (no duplicate)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationHornCNoDuplicateResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createHornCNoDuplicate<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet,
                                                                                                    FormulaLeafPostprocessingTypeEnum::NO_DUPLICATE_CLAUSES,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::Horn_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Horn-C (no subsumed)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] Horn-C (no subsumed)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationHornCNoSubsumedResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createHornCNoSubsumed<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet,
                                                                                                    FormulaLeafPostprocessingTypeEnum::NO_SUBSUMED_CLAUSES,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::Horn_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * anti-Horn-C (none)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] anti-Horn-C (none)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationAntiHornCNoneResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createAntiHornCNone<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet,
                                                                                                    FormulaLeafPostprocessingTypeEnum::NONE,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::anti_Horn_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * anti-Horn-C (no duplicate)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] anti-Horn-C (no duplicate)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationAntiHornCNoDuplicateResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createAntiHornCNoDuplicate<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet,
                                                                                                    FormulaLeafPostprocessingTypeEnum::NO_DUPLICATE_CLAUSES,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::anti_Horn_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * anti-Horn-C (no subsumed)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] anti-Horn-C (no subsumed)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationAntiHornCNoSubsumedResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createAntiHornCNoSubsumed<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet,
                                                                                                    FormulaLeafPostprocessingTypeEnum::NO_SUBSUMED_CLAUSES,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::anti_Horn_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * renH-C (none)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] renH-C (none)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationRenHCNoneResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createRenHCNone<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet, { 1, 4 },
                                                                                                    FormulaLeafPostprocessingTypeEnum::NONE,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::renH_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * renH-C (no duplicate)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] renH-C (no duplicate)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationRenHCNoDuplicateResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createRenHCNoDuplicate<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet, {},
                                                                                                    FormulaLeafPostprocessingTypeEnum::NO_DUPLICATE_CLAUSES,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::renH_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * renH-C (no subsumed)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] renH-C (no subsumed)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationRenHCNoSubsumedResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createRenHCNoSubsumed<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet, { 1, 2, 4 },
                                                                                                    FormulaLeafPostprocessingTypeEnum::NO_SUBSUMED_CLAUSES,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::renH_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Krom-C (partial assignment)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] Krom-C (partial assignment)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationKromCPartialAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createKromCPartialAssignment<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            assignLiteral(formula.get(), currentComponentVariableSet, LiteralType(1, false), actualResult);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet,
                                                                                                    FormulaLeafPostprocessingTypeEnum::NONE,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::Krom_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Horn-C (partial assignment)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] Horn-C (partial assignment)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationHornCPartialAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createHornCPartialAssignment<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            assignLiteral(formula.get(), currentComponentVariableSet, LiteralType(4, false), actualResult);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet,
                                                                                                    FormulaLeafPostprocessingTypeEnum::NONE,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::Horn_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * anti-Horn-C (partial assignment)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] anti-Horn-C (partial assignment)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationAntiHornCPartialAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createAntiHornCPartialAssignment<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            assignLiteral(formula.get(), currentComponentVariableSet, LiteralType(4, true), actualResult);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet,
                                                                                                    FormulaLeafPostprocessingTypeEnum::NONE,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::anti_Horn_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * renH-C (partial assignment)
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] renH-C (partial assignment)", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationRenHCPartialAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createRenHCPartialAssignment<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            assignLiteral(formula.get(), currentComponentVariableSet, LiteralType(4, true), actualResult);
            printFormula(formula.get(), actualResult);

            StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), currentComponentVariableSet, { 3, 7 },
                                                                                                    FormulaLeafPostprocessingTypeEnum::NONE,
                                                                                                    StructuralRestrictedFormulaRepresentationTypeEnum::renH_C);
            printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Connected components
     */
    TEST_CASE("[Formula::StructuralRestrictedRepresentation] connected components", "[Formula::StructuralRestrictedRepresentation]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          structuralRestrictedFormulaRepresentationConnectedComponentsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createFormulaWithConnectedComponents<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);
            printFormula(formula.get(), actualResult);

            ConnectedComponentType connectedComponents = formula->computeConnectedComponents(currentComponentVariableSet);
            printConnectedComponents(connectedComponents, actualResult);

            // Connected components
            for (const ConnectedComponentStruct& newConnectedComponent : connectedComponents) {
                // Set new component
                printSetNewConnectedComponent(newConnectedComponent, actualResult);
                PureVariableRemovedClausesVectorType pureVariableRemovedClausesVector = formula->setNewComponent(newConnectedComponent,
                                                                                                                 IgnorePureLiteralTypeEnum::NONE);
                assert(pureVariableRemovedClausesVector.empty());

                printFormula(formula.get(), actualResult);

                StructuralRestrictedFormulaRepresentationTypeEnum structuralRestrictedFormulaRepresentationType;
                // Krom-C
                if (Hydra::Other::containInSet(newConnectedComponent.variableSet, (VarT)1))
                    structuralRestrictedFormulaRepresentationType = StructuralRestrictedFormulaRepresentationTypeEnum::Krom_C;
                // Horn-C
                else if (Hydra::Other::containInSet(newConnectedComponent.variableSet, (VarT)3))
                    structuralRestrictedFormulaRepresentationType = StructuralRestrictedFormulaRepresentationTypeEnum::Horn_C;
                // anti-Horn-C
                else {
                    assert(Hydra::Other::containInSet(newConnectedComponent.variableSet, (VarT)6));

                    structuralRestrictedFormulaRepresentationType = StructuralRestrictedFormulaRepresentationTypeEnum::anti_Horn_C;
                }

                // Krom-C, Horn-C, and anti-Horn-C
                Hydra::Other::printTitle(actualResult, Hydra::Formula::StructuralRestrictedRepresentation::structuralRestrictedFormulaRepresentationTypeEnumToString(structuralRestrictedFormulaRepresentationType), 20, '-');
                StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentation(formula.get(), newConnectedComponent.variableSet,
                                                                                                        FormulaLeafPostprocessingTypeEnum::NONE,
                                                                                                        structuralRestrictedFormulaRepresentationType);
                printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentation, actualResult);

                // renH-C
                Hydra::Other::printTitle(actualResult, Hydra::Formula::StructuralRestrictedRepresentation::structuralRestrictedFormulaRepresentationTypeEnumToString(StructuralRestrictedFormulaRepresentationTypeEnum::renH_C), 20, '-');
                StructuralRestrictedFormulaRepresentationType structuralRestrictedFormulaRepresentationRenHC(formula.get(), newConnectedComponent.variableSet,
                                                                                                             { 2, 6, 7, 8 },
                                                                                                             FormulaLeafPostprocessingTypeEnum::NO_SUBSUMED_CLAUSES,   // to filter out the switched variables
                                                                                                             StructuralRestrictedFormulaRepresentationTypeEnum::renH_C);
                printStructuralRestrictedFormulaRepresentation(structuralRestrictedFormulaRepresentationRenHC, actualResult);

                // Pop previous component
                printPopPreviousConnectedComponent(newConnectedComponent, actualResult);
                formula->popPreviousComponent(newConnectedComponent, pureVariableRemovedClausesVector);

                actualResult << "--------------------------------------------------------------------------------" << std::endl;
                actualResult << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif
}   // namespace HydraTest::Formula::StructuralRestrictedRepresentation
