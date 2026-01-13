#include <memory>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/decisionHeuristic/CreateFormula.hpp"
#include "HydraTest/decisionHeuristic/DecisionHeuristic.hpp"
#include "HydraTest/decisionHeuristic/random/RandomDecisionHeuristicTestResult.hpp"

#include "Hydra/decisionHeuristic/random/RandomDecisionHeuristic.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/decisionHeuristic/exceptions/DecisionHeuristicException.hpp"

#include "Hydra/decisionHeuristic/random/RandomDecisionHeuristic.tpp"

namespace HydraTest::DecisionHeuristic::Random {

    //region Types
    using VarT = HydraTest::DecisionHeuristic::VarT;
    using LiteralT = HydraTest::DecisionHeuristic::LiteralT;
    using ClauseIdT = HydraTest::DecisionHeuristic::ClauseIdT;

    using RandomDecisionHeuristicType = Hydra::DecisionHeuristic::Random::RandomDecisionHeuristic<VarT, LiteralT, ClauseIdT>;

    using RandomDecisionHeuristicConfigurationType = Hydra::DecisionHeuristic::Random::RandomDecisionHeuristicConfiguration;
    //endregion

    //region Functions
    DecisionHeuristicAbstractUniquePtrType createRandomDecisionHeuristic(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                                         SatSolverAbstractPtrType satSolverAbstractPtr,
                                                                         IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::NONE) {
        RandomDecisionHeuristicConfigurationType configuration;

        return std::make_unique<RandomDecisionHeuristicType>(formulaRepresentationAbstractPtr, satSolverAbstractPtr,
                                                             ignorePureLiteralType, configuration);
    }
    //endregion

    /**
     * Random
     */
    TEST_CASE("[DecisionHeuristic::Random] random", "[DecisionHeuristic::Random]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          randomDecisionHeuristicResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createPigeonHoleFormula<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createRandomDecisionHeuristic(formulaRepresentation.get(), satSolver.get());
            printDecisionHeuristic(decisionHeuristic.get(), actualResult, false);

            VariableSetType selectedVariableSet = generateSelectedVariableSet(formulaRepresentation->getNumberOfVariablesInOriginalFormula());
            printSelectedVariables(selectedVariableSet, actualResult);

            int numberOfIteration = 10;
            for (int i = 0; i < numberOfIteration; ++i)
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariableSet, actualResult, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Random (selected variables)
     */
    TEST_CASE("[DecisionHeuristic::Random] random (selected variables)", "[DecisionHeuristic::Random]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          randomDecisionHeuristicSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createPigeonHoleFormula<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createRandomDecisionHeuristic(formulaRepresentation.get(), satSolver.get());
            printDecisionHeuristic(decisionHeuristic.get(), actualResult, false);

            std::vector<VariableSetType> selectedVariablesVector { { 1, 2, 3, 4, 5, 6 }, { 1, 7, 13, 19, 25, 31, 37 }, { 7, 8, 9 }, { 13 } };

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
}   // namespace HydraTest::DecisionHeuristic::Random
