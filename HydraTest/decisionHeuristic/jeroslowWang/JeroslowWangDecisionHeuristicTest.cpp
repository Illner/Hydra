#include <memory>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/decisionHeuristic/CreateFormula.hpp"
#include "HydraTest/decisionHeuristic/DecisionHeuristic.hpp"
#include "HydraTest/decisionHeuristic/jeroslowWang/JeroslowWangDecisionHeuristicTestResult.hpp"

#include "Hydra/decisionHeuristic/jeroslowWang/JeroslowWangDecisionHeuristic.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/decisionHeuristic/exceptions/DecisionHeuristicException.hpp"

#include "Hydra/decisionHeuristic/enums/DecisionHeuristicTypeEnum.hpp"

#include "Hydra/decisionHeuristic/jeroslowWang/JeroslowWangDecisionHeuristic.tpp"

namespace HydraTest::DecisionHeuristic::JeroslowWang {

    //region Types
    using VarT = HydraTest::DecisionHeuristic::VarT;
    using LiteralT = HydraTest::DecisionHeuristic::LiteralT;
    using ClauseIdT = HydraTest::DecisionHeuristic::ClauseIdT;

    using JeroslowWangDecisionHeuristicType = Hydra::DecisionHeuristic::JeroslowWang::JeroslowWangDecisionHeuristic<VarT, LiteralT, ClauseIdT>;

    using DecisionHeuristicTypeEnum = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum;

    using JeroslowWangDecisionHeuristicConfigurationType = Hydra::DecisionHeuristic::JeroslowWang::JeroslowWangDecisionHeuristicConfiguration;
    //endregion

    //region Functions
    DecisionHeuristicAbstractUniquePtrType createJeroslowWangDecisionHeuristic(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                                               SatSolverAbstractPtrType satSolverAbstractPtr, bool twoSidedVariant,
                                                                               IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::NONE) {
        JeroslowWangDecisionHeuristicConfigurationType configuration;
        configuration.twoSidedVariant = twoSidedVariant;

        return std::make_unique<JeroslowWangDecisionHeuristicType>(formulaRepresentationAbstractPtr, satSolverAbstractPtr,
                                                                   ignorePureLiteralType, configuration);
    }
    //endregion

    /**
     * One-sided
     */
    TEST_CASE("[DecisionHeuristic::JeroslowWang] one-sided", "[DecisionHeuristic::JeroslowWang]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          jeroslowWangDecisionHeuristicOneSidedResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForJeroslowWang<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createJeroslowWangDecisionHeuristic(formulaRepresentation.get(), satSolver.get(), false);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);
            computeDecisionHeuristic(decisionHeuristic.get(), { 1, 2, 3, 4, 5, 6, 7 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-sided (selected variables)
     */
    TEST_CASE("[DecisionHeuristic::JeroslowWang] one-sided (selected variables)", "[DecisionHeuristic::JeroslowWang]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          jeroslowWangDecisionHeuristicOneSidedSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForJeroslowWang<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createJeroslowWangDecisionHeuristic(formulaRepresentation.get(), satSolver.get(), false);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);

            std::vector<VariableSetType> selectedVariablesVector { { 1, 2, 3, 4, 6, 7 }, { 4, 5, 6, 7 }, { 1, 2, 4 }, { 3, 6, 7 }, { 7 } };

            for (const VariableSetType& selectedVariables : selectedVariablesVector) {
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    #if defined(BELLA_COMPILER)
    /**
     * One-sided (ignore positive pure literals)
     */
    TEST_CASE("[DecisionHeuristic::JeroslowWang] one-sided (ignore positive pure literals)", "[DecisionHeuristic::JeroslowWang]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          jeroslowWangDecisionHeuristicOneSidedIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForJeroslowWangIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createJeroslowWangDecisionHeuristic(formulaRepresentation.get(), satSolver.get(), false,
                                                                                                           IgnorePureLiteralTypeEnum::ONLY_POSITIVE);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);

            std::vector<VariableSetType> selectedVariablesVector { { 1, 2, 3, 4 }, { 1, 3, 4 }, { 2, 3, 4 }, { 3, 4 } };

            for (const VariableSetType& selectedVariables : selectedVariablesVector) {
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, actualResult, true, true);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-sided (ignore negative pure literals)
     */
    TEST_CASE("[DecisionHeuristic::JeroslowWang] one-sided (ignore negative pure literals)", "[DecisionHeuristic::JeroslowWang]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          jeroslowWangDecisionHeuristicOneSidedIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForJeroslowWangIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createJeroslowWangDecisionHeuristic(formulaRepresentation.get(), satSolver.get(), false,
                                                                                                           IgnorePureLiteralTypeEnum::ONLY_NEGATIVE);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);

            std::vector<VariableSetType> selectedVariablesVector { { 1, 2, 3, 4 }, { 1, 3, 4 }, { 2, 3, 4 }, { 3, 4 } };

            for (const VariableSetType& selectedVariables : selectedVariablesVector) {
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, actualResult, true, true);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-sided (ignore pure literals)
     */
    TEST_CASE("[DecisionHeuristic::JeroslowWang] one-sided (ignore pure literals)", "[DecisionHeuristic::JeroslowWang]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          jeroslowWangDecisionHeuristicOneSidedIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForJeroslowWangIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createJeroslowWangDecisionHeuristic(formulaRepresentation.get(), satSolver.get(), false,
                                                                                                           IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);

            std::vector<VariableSetType> selectedVariablesVector { { 1, 2, 3, 4 }, { 1, 3, 4 }, { 2, 3, 4 }, { 3, 4 } };

            for (const VariableSetType& selectedVariables : selectedVariablesVector) {
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, actualResult, true, true);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif

    /**
     * Two-sided
     */
    TEST_CASE("[DecisionHeuristic::JeroslowWang] two-sided", "[DecisionHeuristic::JeroslowWang]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          jeroslowWangDecisionHeuristicTwoSidedResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForJeroslowWang<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createJeroslowWangDecisionHeuristic(formulaRepresentation.get(), satSolver.get(), true);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);
            computeDecisionHeuristic(decisionHeuristic.get(), { 1, 2, 3, 4, 5, 6, 7 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Two-sided (selected variables)
     */
    TEST_CASE("[DecisionHeuristic::JeroslowWang] two-sided (selected variables)", "[DecisionHeuristic::JeroslowWang]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          jeroslowWangDecisionHeuristicTwoSidedSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForJeroslowWang<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createJeroslowWangDecisionHeuristic(formulaRepresentation.get(), satSolver.get(), true);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);

            std::vector<VariableSetType> selectedVariablesVector { { 1, 2, 3, 4, 6, 7 }, { 2, 4, 6, 7 }, { 3, 4, 7 }, { 1, 2 }, { 7 } };

            for (const VariableSetType& selectedVariables : selectedVariablesVector) {
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    #if defined(BELLA_COMPILER)
    /**
     * Two-sided (ignore positive pure literals)
     */
    TEST_CASE("[DecisionHeuristic::JeroslowWang] two-sided (ignore positive pure literals)", "[DecisionHeuristic::JeroslowWang]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          jeroslowWangDecisionHeuristicTwoSidedIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForJeroslowWangIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createJeroslowWangDecisionHeuristic(formulaRepresentation.get(), satSolver.get(), true,
                                                                                                           IgnorePureLiteralTypeEnum::ONLY_POSITIVE);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);

            std::vector<VariableSetType> selectedVariablesVector { { 1, 2, 3, 4 }, { 1, 3, 4 }, { 2, 3, 4 }, { 3, 4 } };

            for (const VariableSetType& selectedVariables : selectedVariablesVector) {
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, actualResult, true, true);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Two-sided (ignore negative pure literals)
     */
    TEST_CASE("[DecisionHeuristic::JeroslowWang] two-sided (ignore negative pure literals)", "[DecisionHeuristic::JeroslowWang]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          jeroslowWangDecisionHeuristicTwoSidedIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForJeroslowWangIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createJeroslowWangDecisionHeuristic(formulaRepresentation.get(), satSolver.get(), true,
                                                                                                           IgnorePureLiteralTypeEnum::ONLY_NEGATIVE);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);

            std::vector<VariableSetType> selectedVariablesVector { { 1, 2, 3, 4 }, { 1, 3, 4 }, { 2, 3, 4 }, { 3, 4 } };

            for (const VariableSetType& selectedVariables : selectedVariablesVector) {
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, actualResult, true, true);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Two-sided (ignore pure literals)
     */
    TEST_CASE("[DecisionHeuristic::JeroslowWang] two-sided (ignore pure literals)", "[DecisionHeuristic::JeroslowWang]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          jeroslowWangDecisionHeuristicTwoSidedIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForJeroslowWangIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createJeroslowWangDecisionHeuristic(formulaRepresentation.get(), satSolver.get(), true,
                                                                                                           IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);

            std::vector<VariableSetType> selectedVariablesVector { { 1, 2, 3, 4 }, { 1, 3, 4 }, { 2, 3, 4 }, { 3, 4 } };

            for (const VariableSetType& selectedVariables : selectedVariablesVector) {
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, actualResult, true, true);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif
}   // namespace HydraTest::DecisionHeuristic::JeroslowWang
