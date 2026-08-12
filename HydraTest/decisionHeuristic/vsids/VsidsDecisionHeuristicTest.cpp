#include <memory>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/decisionHeuristic/CreateFormula.hpp"
#include "HydraTest/decisionHeuristic/DecisionHeuristic.hpp"
#include "HydraTest/decisionHeuristic/vsids/VsidsDecisionHeuristicTestResult.hpp"
#include "HydraTest/external/unitTesting/Catch2/catch.hpp"

#include "Hydra/decisionHeuristic/vsids/VsidsDecisionHeuristic.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/decisionHeuristic/exceptions/DecisionHeuristicException.hpp"

#include "Hydra/decisionHeuristic/vsids/VsidsDecisionHeuristic.tpp"

namespace HydraTest::DecisionHeuristic::Vsids {

    //region Types
    using VarT = HydraTest::DecisionHeuristic::VarT;
    using LiteralT = HydraTest::DecisionHeuristic::LiteralT;
    using ClauseIdT = HydraTest::DecisionHeuristic::ClauseIdT;

    using VsidsDecisionHeuristicType = Hydra::DecisionHeuristic::Vsids::VsidsDecisionHeuristic<VarT, LiteralT, ClauseIdT>;

    using VsidsDecisionHeuristicConfigurationType = Hydra::DecisionHeuristic::Vsids::VsidsDecisionHeuristicConfiguration;
    //endregion

    //region Functions
    DecisionHeuristicAbstractUniquePtrType createVsidsDecisionHeuristic(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                                        SatSolverAbstractPtrType satSolverAbstractPtr,
                                                                        IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::NONE) {
        VsidsDecisionHeuristicConfigurationType configuration;

        return std::make_unique<VsidsDecisionHeuristicType>(formulaRepresentationAbstractPtr, satSolverAbstractPtr,
                                                            ignorePureLiteralType, configuration);
    }

    void processVsids(SatSolverTypeEnum satSolverType, std::stringstream& actualResult) {
        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createPigeonHoleFormula<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get(), satSolverType);

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createVsidsDecisionHeuristic(formulaRepresentation.get(), satSolver.get());
            printDecisionHeuristic(decisionHeuristic.get(), actualResult, false);

            VariableSetType currentComponentVariableSet = generateCurrentComponentVariableSet(formulaRepresentation->getNumberOfVariablesInOriginalFormula());

            // Before calling SAT
            actualResult << "--------------------" << std::endl;
            actualResult << "------ before ------" << std::endl;
            actualResult << "--------------------" << std::endl;

            computeDecisionHeuristic(decisionHeuristic.get(), currentComponentVariableSet, currentComponentVariableSet,
                                     actualResult, true);

            // After calling SAT
            actualResult << "-------------------" << std::endl;
            actualResult << "------ after ------" << std::endl;
            actualResult << "-------------------" << std::endl;

            satSolver->isSatisfiable();

            computeDecisionHeuristic(decisionHeuristic.get(), currentComponentVariableSet, currentComponentVariableSet,
                                     actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }
    }

    void processVsidsSelectedVariables(SatSolverTypeEnum satSolverType, std::stringstream& actualResult) {
        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createPigeonHoleFormula<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get(), satSolverType);

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createVsidsDecisionHeuristic(formulaRepresentation.get(), satSolver.get());
            printDecisionHeuristic(decisionHeuristic.get(), actualResult, false);

            VariableSetType currentComponentVariableSet = generateCurrentComponentVariableSet(formulaRepresentation->getNumberOfVariablesInOriginalFormula());
            std::vector<VariableSetType> selectedVariablesVector { { 1, 2, 3, 4, 5, 6 }, { 1, 7, 13, 19, 25, 31, 37 }, { 7, 8, 9 }, { 13 } };

            // Before calling SAT
            actualResult << "--------------------" << std::endl;
            actualResult << "------ before ------" << std::endl;
            actualResult << "--------------------" << std::endl;

            for (const VariableSetType& selectedVariables : selectedVariablesVector)
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, currentComponentVariableSet,
                                         actualResult, true);

            // After calling SAT
            actualResult << "-------------------" << std::endl;
            actualResult << "------ after ------" << std::endl;
            actualResult << "-------------------" << std::endl;

            satSolver->isSatisfiable();

            for (const VariableSetType& selectedVariables : selectedVariablesVector) {
                printSelectedVariables(selectedVariables, actualResult);
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, currentComponentVariableSet,
                                         actualResult, false);
                actualResult << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }
    }
    //endregion

    /**
     * VSIDS
     */
    TEST_CASE("[DecisionHeuristic::Vsids] VSIDS", "[DecisionHeuristic::Vsids]") {
        // MiniSat
        SECTION(Hydra::SatSolver::satSolverTypeEnumToString(SatSolverTypeEnum::MINISAT)) {
            SatSolverTypeEnum satSolverType = SatSolverTypeEnum::MINISAT;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ")",
                              vsidsDecisionHeuristicResult);
            std::stringstream& actualResult = test.getStringStream();

            processVsids(satSolverType, actualResult);

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // Glucose
        SECTION(Hydra::SatSolver::satSolverTypeEnumToString(SatSolverTypeEnum::GLUCOSE)) {
            SatSolverTypeEnum satSolverType = SatSolverTypeEnum::GLUCOSE;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ")",
                              vsidsDecisionHeuristicResult);
            std::stringstream& actualResult = test.getStringStream();

            processVsids(satSolverType, actualResult);

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }
    }

    /**
     * VSIDS (selected variables)
     */
    TEST_CASE("[DecisionHeuristic::Vsids] VSIDS (selected variables)", "[DecisionHeuristic::Vsids]") {
        // MiniSat
        SECTION(Hydra::SatSolver::satSolverTypeEnumToString(SatSolverTypeEnum::MINISAT)) {
            SatSolverTypeEnum satSolverType = SatSolverTypeEnum::MINISAT;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ")",
                              vsidsDecisionHeuristicSelectedVariablesResult);
            std::stringstream& actualResult = test.getStringStream();

            processVsidsSelectedVariables(satSolverType, actualResult);

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // Glucose
        SECTION(Hydra::SatSolver::satSolverTypeEnumToString(SatSolverTypeEnum::GLUCOSE)) {
            SatSolverTypeEnum satSolverType = SatSolverTypeEnum::GLUCOSE;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ")",
                              vsidsDecisionHeuristicSelectedVariablesResult);
            std::stringstream& actualResult = test.getStringStream();

            processVsidsSelectedVariables(satSolverType, actualResult);

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }
    }
}   // namespace HydraTest::DecisionHeuristic::Vsids
