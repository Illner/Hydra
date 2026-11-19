#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/external/unitTesting/Catch2/catch.hpp"
#include "HydraTest/satSolver/CreateFormula.hpp"
#include "HydraTest/satSolver/SatSolver.hpp"
#include "HydraTest/satSolver/cadical/CadicalSolverTestResult.hpp"

#include "Hydra/satSolver/cadical/CadicalSolver.hpp"

namespace HydraTest::SatSolver::Cadical {

    //region Types
    using VarT = HydraTest::SatSolver::VarT;
    using LiteralT = HydraTest::SatSolver::LiteralT;
    using ClauseIdT = HydraTest::SatSolver::ClauseIdT;

    using CadicalSolverType = Hydra::SatSolver::Cadical::CadicalSolver<VarT, LiteralT, ClauseIdT>;
    //endregion

    //region Functions
    SatSolverAbstractUniquePtrType createSatSolver(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                   bool computeInitiallyImpliedLiterals = true) {
        SatSolverAbstractUniquePtrType satSolverAbstractUniquePtr = std::make_unique<CadicalSolverType>(formulaRepresentationAbstractPtr);

        if (computeInitiallyImpliedLiterals)
            satSolverAbstractUniquePtr->computeAndSetInitiallyImpliedLiterals();

        return satSolverAbstractUniquePtr;
    }
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[SatSolver::Cadical] constructor", "[SatSolver::Cadical]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cadicalSolverConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaWithUnitClauses<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());
            printSatSolver(satSolver.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Formula with conflicting unit clauses
     */
    TEST_CASE("[SatSolver::Cadical] formula with conflicting unit clauses", "[SatSolver::Cadical]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cadicalSolverFormulaWithConflictingUnitClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaWithConflictingUnitClauses<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());
            printSatSolver(satSolver.get(), actualResult);

            bool isSatisfiable = satSolver->isSatisfiable();
            actualResult << "Is satisfiable: " << std::to_string(isSatisfiable) << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Satisfiability (satisfiable formula)
     */
    TEST_CASE("[SatSolver::Cadical] satisfiability (satisfiable formula)", "[SatSolver::Cadical]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cadicalSolverSatisfiabilitySatisfiableFormulaResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaWithUnitClauses<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());
            printSatSolver(satSolver.get(), actualResult);

            bool isSatisfiable = satSolver->isSatisfiable();
            actualResult << "Is satisfiable: " << std::to_string(isSatisfiable) << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Satisfiability (unsatisfiable formula)
     */
    TEST_CASE("[SatSolver::Cadical] satisfiability (unsatisfiable formula)", "[SatSolver::Cadical]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cadicalSolverSatisfiabilityUnsatisfiableFormulaResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createUnsatisfiableFormula<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());
            printSatSolver(satSolver.get(), actualResult);

            bool isSatisfiable = satSolver->isSatisfiable();
            actualResult << "Is satisfiable: " << std::to_string(isSatisfiable) << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Satisfiability (assumptions)
     */
    TEST_CASE("[SatSolver::Cadical] satisfiability (assumptions)", "[SatSolver::Cadical]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cadicalSolverSatisfiabilityAssumptionsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createSatisfiableFormula<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());
            printSatSolver(satSolver.get(), actualResult);

            isSatisfiableAssumptions(formulaRepresentation.get(), satSolver.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Unit propagation
     */
    TEST_CASE("[SatSolver::Cadical] unit propagation", "[SatSolver::Cadical]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cadicalSolverUnitPropagationResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForUnitPropagation<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());
            printSatSolver(satSolver.get(), actualResult);

            processUnitPropagation(formulaRepresentation.get(), satSolver.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Unit propagation (restrictions)
     */
    TEST_CASE("[SatSolver::Cadical] unit propagation (restrictions)", "[SatSolver::Cadical]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cadicalSolverUnitPropagationRestrictionsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForUnitPropagation<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());
            printSatSolver(satSolver.get(), actualResult);

            processUnitPropagationRestrictions(formulaRepresentation.get(), satSolver.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Equivalence preprocessing structure
     */
    TEST_CASE("[SatSolver::Cadical] equivalence preprocessing structure", "[SatSolver::Cadical]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cadicalSolverEquivalencePreprocessingStructureResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());
            printSatSolver(satSolver.get(), actualResult);

            EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolver->createEquivalencePreprocessingStruct(generateSelectedVariableSet(formulaRepresentation->getNumberOfVariablesInOriginalFormula()),
                                                                                                                            false,
                                                                                                                            ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX);
            printEquivalencePreprocessingStructure(equivalencePreprocessingStruct, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Equivalence preprocessing structure (selected variables)
     */
    TEST_CASE("[SatSolver::Cadical] equivalence preprocessing structure (selected variables)", "[SatSolver::Cadical]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cadicalSolverEquivalencePreprocessingStructureSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());
            printSatSolver(satSolver.get(), actualResult);

            processEquivalencePreprocessingStructureSelectedVariables(satSolver.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Equivalence preprocessing structure (no ignore)
     */
    TEST_CASE("[SatSolver::Cadical] equivalence preprocessing structure (no ignore)", "[SatSolver::Cadical]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cadicalSolverEquivalencePreprocessingStructureNoIgnoreResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure2<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());
            printSatSolver(satSolver.get(), actualResult);

            EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolver->createEquivalencePreprocessingStruct(generateSelectedVariableSet(formulaRepresentation->getNumberOfVariablesInOriginalFormula()),
                                                                                                                            false,
                                                                                                                            ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX);
            printEquivalencePreprocessingStructure(equivalencePreprocessingStruct, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Equivalence preprocessing structure (ignore)
     */
    TEST_CASE("[SatSolver::Cadical] equivalence preprocessing structure (ignore)", "[SatSolver::Cadical]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cadicalSolverEquivalencePreprocessingStructureIgnoreResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure2<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());
            printSatSolver(satSolver.get(), actualResult);

            EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolver->createEquivalencePreprocessingStruct(generateSelectedVariableSet(formulaRepresentation->getNumberOfVariablesInOriginalFormula()),
                                                                                                                            true,
                                                                                                                            ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX);
            printEquivalencePreprocessingStructure(equivalencePreprocessingStruct, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Equivalence preprocessing structure (clause reduction heuristic - ascending)
     */
    TEST_CASE("[SatSolver::Cadical] equivalence preprocessing structure (clause reduction heuristic - ascending)", "[SatSolver::Cadical]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cadicalSolverEquivalencePreprocessingStructureClauseReductionHeuristicAscendingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure2<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());
            printSatSolver(satSolver.get(), actualResult);

            EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolver->createEquivalencePreprocessingStruct(generateSelectedVariableSet(formulaRepresentation->getNumberOfVariablesInOriginalFormula()),
                                                                                                                            false,
                                                                                                                            ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_ASCENDING);
            printEquivalencePreprocessingStructure(equivalencePreprocessingStruct, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Equivalence preprocessing structure (clause reduction heuristic - descending)
     */
    TEST_CASE("[SatSolver::Cadical] equivalence preprocessing structure (clause reduction heuristic - descending)", "[SatSolver::Cadical]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cadicalSolverEquivalencePreprocessingStructureClauseReductionHeuristicDescendingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure2<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());
            printSatSolver(satSolver.get(), actualResult);

            EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolver->createEquivalencePreprocessingStruct(generateSelectedVariableSet(formulaRepresentation->getNumberOfVariablesInOriginalFormula()),
                                                                                                                            false,
                                                                                                                            ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_DESCENDING);
            printEquivalencePreprocessingStructure(equivalencePreprocessingStruct, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::SatSolver::Cadical
