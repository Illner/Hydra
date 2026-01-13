#include <memory>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/decisionHeuristic/CreateFormula.hpp"
#include "HydraTest/decisionHeuristic/DecisionHeuristic.hpp"
#include "HydraTest/decisionHeuristic/vsads/VsadsDecisionHeuristicTestResult.hpp"

#include "Hydra/decisionHeuristic/vsads/VsadsDecisionHeuristic.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/decisionHeuristic/exceptions/DecisionHeuristicException.hpp"

#include "Hydra/decisionHeuristic/vsads/VsadsDecisionHeuristic.tpp"

namespace HydraTest::DecisionHeuristic::Vsads {

    //region Types
    using VarT = HydraTest::DecisionHeuristic::VarT;
    using LiteralT = HydraTest::DecisionHeuristic::LiteralT;
    using ClauseIdT = HydraTest::DecisionHeuristic::ClauseIdT;

    using VsadsDecisionHeuristicType = Hydra::DecisionHeuristic::Vsads::VsadsDecisionHeuristic<VarT, LiteralT, ClauseIdT>;

    using VsadsDecisionHeuristicConfigurationType = Hydra::DecisionHeuristic::Vsads::VsadsDecisionHeuristicConfiguration;
    //endregion

    //region Functions
    DecisionHeuristicAbstractUniquePtrType createVsadsDecisionHeuristic(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                                        SatSolverAbstractPtrType satSolverAbstractPtr,
                                                                        long double p = 1, long double q = 0.5,
                                                                        IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::NONE) {
        VsadsDecisionHeuristicConfigurationType configuration;
        configuration.p = p;
        configuration.q = q;

        return std::make_unique<VsadsDecisionHeuristicType>(formulaRepresentationAbstractPtr, satSolverAbstractPtr,
                                                            ignorePureLiteralType, configuration);
    }
    //endregion

    /**
     * VSADS
     */
    TEST_CASE("[DecisionHeuristic::Vsads] VSADS", "[DecisionHeuristic::Vsads]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vsadsDecisionHeuristicResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createPigeonHoleFormula<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createVsadsDecisionHeuristic(formulaRepresentation.get(), satSolver.get());
            printDecisionHeuristic(decisionHeuristic.get(), actualResult, false);

            VariableSetType selectedVariableSet = generateSelectedVariableSet(formulaRepresentation->getNumberOfVariablesInOriginalFormula());

            // Before calling SAT
            actualResult << "--------------------" << std::endl;
            actualResult << "------ before ------" << std::endl;
            actualResult << "--------------------" << std::endl;

            computeDecisionHeuristic(decisionHeuristic.get(), selectedVariableSet, actualResult, true);

            // After calling SAT
            actualResult << "-------------------" << std::endl;
            actualResult << "------ after ------" << std::endl;
            actualResult << "-------------------" << std::endl;

            satSolver->isSatisfiable();

            computeDecisionHeuristic(decisionHeuristic.get(), selectedVariableSet, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * VSADS (selected variables)
     */
    TEST_CASE("[DecisionHeuristic::Vsads] VSADS (selected variables)", "[DecisionHeuristic::Vsads]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vsadsDecisionHeuristicSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createPigeonHoleFormula<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createVsadsDecisionHeuristic(formulaRepresentation.get(), satSolver.get());
            printDecisionHeuristic(decisionHeuristic.get(), actualResult, false);

            std::vector<VariableSetType> selectedVariablesVector { { 1, 2, 3, 4, 5, 6 }, { 1, 7, 13, 19, 25, 31, 37 }, { 7, 8, 9 }, { 13 } };

            // Before calling SAT
            actualResult << "--------------------" << std::endl;
            actualResult << "------ before ------" << std::endl;
            actualResult << "--------------------" << std::endl;

            for (const VariableSetType& selectedVariables : selectedVariablesVector)
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, actualResult, true);

            // After calling SAT
            actualResult << "-------------------" << std::endl;
            actualResult << "------ after ------" << std::endl;
            actualResult << "-------------------" << std::endl;

            satSolver->isSatisfiable();

            for (const VariableSetType& selectedVariables : selectedVariablesVector) {
                printSelectedVariables(selectedVariables, actualResult);
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, actualResult, false);
                actualResult << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::DecisionHeuristic::Vsads
