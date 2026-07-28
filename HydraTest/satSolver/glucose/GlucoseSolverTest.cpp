#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/satSolver/CreateFormula.hpp"
#include "HydraTest/satSolver/SatSolver.hpp"
#include "HydraTest/satSolver/glucose/GlucoseSolverTestResult.hpp"

#include "Hydra/satSolver/glucose/GlucoseSolver.hpp"

namespace HydraTest::SatSolver::Glucose {

    //region Types
    using VarT = HydraTest::SatSolver::VarT;
    using LiteralT = HydraTest::SatSolver::LiteralT;
    using ClauseIdT = HydraTest::SatSolver::ClauseIdT;

    using GlucoseSolverType = Hydra::SatSolver::Glucose::GlucoseSolver<VarT, LiteralT, ClauseIdT>;
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[SatSolver::Glucose] constructor", "[SatSolver::Glucose]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          glucoseSolverConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaWithUnitClauses<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<GlucoseSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::Glucose] formula with conflicting unit clauses", "[SatSolver::Glucose]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          glucoseSolverFormulaWithConflictingUnitClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaWithConflictingUnitClauses<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<GlucoseSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::Glucose] satisfiability (satisfiable formula)", "[SatSolver::Glucose]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          glucoseSolverSatisfiabilitySatisfiableFormulaResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaWithUnitClauses<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<GlucoseSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::Glucose] satisfiability (unsatisfiable formula)", "[SatSolver::Glucose]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          glucoseSolverSatisfiabilityUnsatisfiableFormulaResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createUnsatisfiableFormula<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<GlucoseSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::Glucose] satisfiability (assumptions)", "[SatSolver::Glucose]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          glucoseSolverSatisfiabilityAssumptionsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createSatisfiableFormula<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<GlucoseSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::Glucose] unit propagation", "[SatSolver::Glucose]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          glucoseSolverUnitPropagationResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForUnitPropagation<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<GlucoseSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::Glucose] unit propagation (restrictions)", "[SatSolver::Glucose]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          glucoseSolverUnitPropagationRestrictionsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForUnitPropagation<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<GlucoseSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::Glucose] equivalence preprocessing structure", "[SatSolver::Glucose]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          glucoseSolverEquivalencePreprocessingStructureResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<GlucoseSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::Glucose] equivalence preprocessing structure (selected variables)", "[SatSolver::Glucose]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          glucoseSolverEquivalencePreprocessingStructureSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<GlucoseSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::Glucose] equivalence preprocessing structure (no ignore)", "[SatSolver::Glucose]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          glucoseSolverEquivalencePreprocessingStructureNoIgnoreResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure2<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<GlucoseSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::Glucose] equivalence preprocessing structure (ignore)", "[SatSolver::Glucose]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          glucoseSolverEquivalencePreprocessingStructureIgnoreResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure2<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<GlucoseSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::Glucose] equivalence preprocessing structure (clause reduction heuristic - ascending)", "[SatSolver::Glucose]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          glucoseSolverEquivalencePreprocessingStructureClauseReductionHeuristicAscendingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure2<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<GlucoseSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::Glucose] equivalence preprocessing structure (clause reduction heuristic - descending)", "[SatSolver::Glucose]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          glucoseSolverEquivalencePreprocessingStructureClauseReductionHeuristicDescendingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure2<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<GlucoseSolverType>(formulaRepresentation.get(), true);
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
}   // namespace HydraTest::SatSolver::Glucose
