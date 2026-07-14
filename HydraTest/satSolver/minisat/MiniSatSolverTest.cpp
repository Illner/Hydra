#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/satSolver/CreateFormula.hpp"
#include "HydraTest/satSolver/SatSolver.hpp"
#include "HydraTest/satSolver/minisat/MiniSatSolverTestResult.hpp"

#include "Hydra/satSolver/minisat/MiniSatSolver.hpp"

namespace HydraTest::SatSolver::MiniSat {

    //region Types
    using VarT = HydraTest::SatSolver::VarT;
    using LiteralT = HydraTest::SatSolver::LiteralT;
    using ClauseIdT = HydraTest::SatSolver::ClauseIdT;

    using MiniSatSolverType = Hydra::SatSolver::MiniSat::MiniSatSolver<VarT, LiteralT, ClauseIdT>;
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[SatSolver::MiniSat] constructor", "[SatSolver::MiniSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          miniSatSolverConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaWithUnitClauses<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
            printSatSolver(satSolver.get(), actualResult);
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
    TEST_CASE("[SatSolver::MiniSat] satisfiability (satisfiable formula)", "[SatSolver::MiniSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          miniSatSolverSatisfiabilitySatisfiableFormulaResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaWithUnitClauses<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::MiniSat] satisfiability (unsatisfiable formula)", "[SatSolver::MiniSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          miniSatSolverSatisfiabilityUnsatisfiableFormulaResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createUnsatisfiableFormula<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::MiniSat] satisfiability (assumptions)", "[SatSolver::MiniSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          miniSatSolverSatisfiabilityAssumptionsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createSatisfiableFormula<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::MiniSat] unit propagation", "[SatSolver::MiniSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          miniSatSolverUnitPropagationResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForUnitPropagation<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::MiniSat] unit propagation (restrictions)", "[SatSolver::MiniSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          miniSatSolverUnitPropagationRestrictionsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForUnitPropagation<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::MiniSat] equivalence preprocessing structure", "[SatSolver::MiniSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          miniSatSolverEquivalencePreprocessingStructureResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::MiniSat] equivalence preprocessing structure (selected variables)", "[SatSolver::MiniSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          miniSatSolverEquivalencePreprocessingStructureSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::MiniSat] equivalence preprocessing structure (no ignore)", "[SatSolver::MiniSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          miniSatSolverEquivalencePreprocessingStructureNoIgnoreResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure2<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::MiniSat] equivalence preprocessing structure (ignore)", "[SatSolver::MiniSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          miniSatSolverEquivalencePreprocessingStructureIgnoreResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure2<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::MiniSat] equivalence preprocessing structure (clause reduction heuristic - ascending)", "[SatSolver::MiniSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          miniSatSolverEquivalencePreprocessingStructureClauseReductionHeuristicAscendingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure2<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
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
    TEST_CASE("[SatSolver::MiniSat] equivalence preprocessing structure (clause reduction heuristic - descending)", "[SatSolver::MiniSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          miniSatSolverEquivalencePreprocessingStructureClauseReductionHeuristicDescendingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForEquivalencePreprocessingStructure2<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
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
}   // namespace HydraTest::SatSolver::MiniSat
