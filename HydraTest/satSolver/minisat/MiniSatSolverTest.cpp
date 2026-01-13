#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/satSolver/CreateFormula.hpp"
#include "HydraTest/satSolver/SatSolver.hpp"
#include "HydraTest/satSolver/minisat/MiniSatSolverTestResult.hpp"

#include "Hydra/other/Other.hpp"
#include "Hydra/satSolver/minisat/MiniSatSolver.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/satSolver/exceptions/SatSolverException.hpp"

#include "Hydra/satSolver/enums/ImplicitBcpVariableOrderTypeEnum.hpp"

namespace HydraTest::SatSolver::MiniSat {

    //region Types
    using VarT = HydraTest::SatSolver::VarT;
    using LiteralT = HydraTest::SatSolver::LiteralT;
    using ClauseIdT = HydraTest::SatSolver::ClauseIdT;

    using LiteralType = typename Hydra::SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
    using VariableSetType = typename Hydra::SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
    using LiteralVectorType = typename Hydra::SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
    using VariableVectorType = typename Hydra::SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;

    using ImplicitBcpVariableOrderTypeEnum = Hydra::SatSolver::ImplicitBcpVariableOrderTypeEnum;

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

        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos8(8, true);
        //endregion

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createSatisfiableFormula<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
            printSatSolver(satSolver.get(), actualResult);

            VariableVectorType tmp;
            VariableSetType variableSet { 1, 2, 3, 4, 5, 6, 7, 8 };
            std::vector<LiteralVectorType> assumptionsVector { {}, { litPos1 }, { litPos3 }, { litPos1, litNeg3 }, { litPos2 }, { litNeg2 }, { litNeg4, litPos5 }, { litNeg6, litPos8 }, {} };

            for (const LiteralVectorType& assumptions : assumptionsVector) {
                actualResult << "--------------------------------------------------" << std::endl;
                printAssumption(assumptions, actualResult);
                actualResult << "--------------------------------------------------" << std::endl;

                for (const LiteralType& lit : assumptions)
                    variableSet.erase(lit.getVariable());

                try {
                    formulaRepresentation->addLiteralVectorToPartialAssignment(assumptions, tmp);
                    satSolver->assignLiteralVector(assumptions);

                    printSatSolver(satSolver.get(), actualResult, false);

                    bool isSatisfiable = satSolver->isSatisfiable(variableSet);
                    actualResult << "------------------------------" << std::endl;
                    actualResult << "Is satisfiable: " << std::to_string(isSatisfiable) << std::endl;
                    actualResult << "------------------------------" << std::endl;

                    satSolver->unassignLiteralVector(assumptions, true);
                    formulaRepresentation->removeLiteralVectorFromPartialAssignment(assumptions, tmp, true);

                    printSatSolver(satSolver.get(), actualResult, false);
                }
                catch (const Hydra::Exception::SatSolver::SatSolverException& e) {
                    actualResult << e.what() << std::endl;
                }

                for (const LiteralType& lit : assumptions)
                    variableSet.emplace(lit.getVariable());
            }
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

        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litNeg3(3, false);
        LiteralType litNeg4(4, false);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        //endregion

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForUnitPropagation<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
            printSatSolver(satSolver.get(), actualResult);

            VariableVectorType tmp;
            VariableSetType restrictedVariableSet { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            std::vector<LiteralVectorType> assumptionsVector { {}, { litNeg2 }, { litNeg5 }, { litPos6 }, { litNeg5, litPos6 }, { litPos1, litPos2, litNeg3, litNeg4, litNeg5 }, { litPos1, litPos2, litNeg3, litNeg4, litPos6 }, { litPos1, litPos2, litNeg3, litNeg4, litNeg5, litPos6 } };

            for (const LiteralVectorType& assumptions : assumptionsVector) {
                for (bool includeAssumptions : { true, false }) {
                    actualResult << "------------------------------" << std::endl;
                    printAssumption(assumptions, actualResult);
                    actualResult << "Include assumptions: " << std::to_string(includeAssumptions) << std::endl;
                    actualResult << "------------------------------" << std::endl;

                    try {
                        formulaRepresentation->addLiteralVectorToPartialAssignment(assumptions, tmp);
                        satSolver->assignLiteralVector(assumptions);

                        doUnitPropagation(satSolver.get(), restrictedVariableSet, includeAssumptions, actualResult);

                        satSolver->unassignLiteralVector(assumptions, true);
                        formulaRepresentation->removeLiteralVectorFromPartialAssignment(assumptions, tmp, true);
                    }
                    catch (const Hydra::Exception::SatSolver::SatSolverException& e) {
                        actualResult << e.what() << std::endl;
                    }

                    actualResult << std::endl;
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
     * Unit propagation (restrictions)
     */
    TEST_CASE("[SatSolver::MiniSat] unit propagation (restrictions)", "[SatSolver::MiniSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          miniSatSolverUnitPropagationRestrictionsResult);
        std::stringstream& actualResult = test.getStringStream();

        //region Literals
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        //endregion

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForUnitPropagation<VarT, LiteralT, ClauseIdT>();
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            SatSolverAbstractUniquePtrType satSolver = std::make_unique<MiniSatSolverType>(formulaRepresentation.get(), true);
            printSatSolver(satSolver.get(), actualResult);

            VariableVectorType tmp;
            std::vector<VariableSetType> restrictedVariableSetVector { {}, { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { 1, 2, 3, 4 }, { 5, 6, 7, 8, 9 }, { 6, 7, 8 }, { 9 } };
            std::vector<LiteralVectorType> assumptionsVector { {}, { litNeg5 }, { litPos6 }, { litNeg5, litPos6 } };

            for (const VariableSetType& restrictedVariableSet : restrictedVariableSetVector)
                for (const LiteralVectorType& assumptions : assumptionsVector) {
                    for (bool includeAssumptions : { true, false }) {
                        actualResult << "------------------------------" << std::endl;
                        printAssumption(assumptions, actualResult);
                        actualResult << "Include assumptions: " << std::to_string(includeAssumptions) << std::endl;
                        actualResult << "Restricted variables:";
                        for (VarT var : Hydra::Other::sortUnorderedSet(restrictedVariableSet))
                            actualResult << " " << std::to_string(var);
                        actualResult << std::endl;
                        actualResult << "------------------------------" << std::endl;

                        try {
                            formulaRepresentation->addLiteralVectorToPartialAssignment(assumptions, tmp);
                            satSolver->assignLiteralVector(assumptions);

                            doUnitPropagation(satSolver.get(), restrictedVariableSet, includeAssumptions, actualResult);

                            satSolver->unassignLiteralVector(assumptions, true);
                            formulaRepresentation->removeLiteralVectorFromPartialAssignment(assumptions, tmp, true);
                        }
                        catch (const Hydra::Exception::SatSolver::SatSolverException& e) {
                            actualResult << e.what() << std::endl;
                        }

                        actualResult << std::endl;
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

            VariableSetType selectedVariableSet { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 };
            EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolver->createEquivalencePreprocessingStruct(selectedVariableSet,
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

            std::vector<VariableSetType> selectedVariablesVector { {}, { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 10, 11, 12 }, { 7, 8, 9, 10, 11, 12, 13, 14, 15 }, { 16, 17, 18 }, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 } };

            for (const VariableSetType& selectedVariables : selectedVariablesVector) {
                actualResult << "------------------------------" << std::endl;
                printSelectedVariableSet(selectedVariables, actualResult);
                actualResult << "------------------------------" << std::endl;

                EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolver->createEquivalencePreprocessingStruct(selectedVariables,
                                                                                                                                false,
                                                                                                                                ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX);

                satSolver->unassignLiteralVector(equivalencePreprocessingStruct.implicitImpliedLiteralVector, true);

                printEquivalencePreprocessingStructure(equivalencePreprocessingStruct, actualResult);
            }
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

            VariableSetType selectedVariableSet { 1, 2, 3, 4, 5 };
            EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolver->createEquivalencePreprocessingStruct(selectedVariableSet,
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

            VariableSetType selectedVariableSet { 1, 2, 3, 4, 5 };
            EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolver->createEquivalencePreprocessingStruct(selectedVariableSet,
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

            VariableSetType selectedVariableSet { 1, 2, 3, 4, 5 };
            EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolver->createEquivalencePreprocessingStruct(selectedVariableSet,
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

            VariableSetType selectedVariableSet { 1, 2, 3, 4, 5 };
            EquivalencePreprocessingStruct equivalencePreprocessingStruct = satSolver->createEquivalencePreprocessingStruct(selectedVariableSet,
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
