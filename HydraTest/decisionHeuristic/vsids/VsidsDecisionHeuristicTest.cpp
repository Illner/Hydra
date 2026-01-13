#include <memory>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/decisionHeuristic/CreateFormula.hpp"
#include "HydraTest/decisionHeuristic/DecisionHeuristic.hpp"
#include "HydraTest/decisionHeuristic/vsids/VsidsDecisionHeuristicTestResult.hpp"

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
    //endregion

    /**
     * VSIDS
     */
    TEST_CASE("[DecisionHeuristic::Vsids] VSIDS", "[DecisionHeuristic::Vsids]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vsidsDecisionHeuristicResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createPigeonHoleFormula<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createVsidsDecisionHeuristic(formulaRepresentation.get(), satSolver.get());
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
     * VSIDS (selected variables)
     */
    TEST_CASE("[DecisionHeuristic::Vsids] VSIDS (selected variables)", "[DecisionHeuristic::Vsids]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          vsidsDecisionHeuristicSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createPigeonHoleFormula<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createVsidsDecisionHeuristic(formulaRepresentation.get(), satSolver.get());
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
}   // namespace HydraTest::DecisionHeuristic::Vsids
