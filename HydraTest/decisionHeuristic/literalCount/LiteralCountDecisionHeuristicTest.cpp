#include <memory>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/decisionHeuristic/CreateFormula.hpp"
#include "HydraTest/decisionHeuristic/DecisionHeuristic.hpp"
#include "HydraTest/decisionHeuristic/literalCount/LiteralCountDecisionHeuristicTestResult.hpp"

#include "Hydra/decisionHeuristic/literalCount/LiteralCountDecisionHeuristic.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/decisionHeuristic/exceptions/DecisionHeuristicException.hpp"

#include "Hydra/decisionHeuristic/enums/DecisionHeuristicTypeEnum.hpp"

#include "Hydra/decisionHeuristic/literalCount/LiteralCountDecisionHeuristic.tpp"

namespace HydraTest::DecisionHeuristic::LiteralCount {

    //region Types
    using VarT = HydraTest::DecisionHeuristic::VarT;
    using LiteralT = HydraTest::DecisionHeuristic::LiteralT;
    using ClauseIdT = HydraTest::DecisionHeuristic::ClauseIdT;

    using LiteralCountDecisionHeuristicType = Hydra::DecisionHeuristic::LiteralCount::LiteralCountDecisionHeuristic<VarT, LiteralT, ClauseIdT>;

    using DecisionHeuristicTypeEnum = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum;

    using LiteralCountDecisionHeuristicConfigurationType = Hydra::DecisionHeuristic::LiteralCount::LiteralCountDecisionHeuristicConfiguration;
    //endregion

    //region Functions
    DecisionHeuristicAbstractUniquePtrType createLiteralCountDecisionHeuristic(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                                               SatSolverAbstractPtrType satSolverAbstractPtr,
                                                                               DecisionHeuristicTypeEnum decisionHeuristicType,
                                                                               IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::NONE) {
        LiteralCountDecisionHeuristicConfigurationType configuration;
        configuration.decisionHeuristicType = decisionHeuristicType;

        return std::make_unique<LiteralCountDecisionHeuristicType>(formulaRepresentationAbstractPtr, satSolverAbstractPtr,
                                                                   ignorePureLiteralType, configuration);
    }
    //endregion

    /**
     * DLCS
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLCS", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlcsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCount<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLCS);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);
            computeDecisionHeuristic(decisionHeuristic.get(), { 1, 2, 3, 4, 5, 6 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * DLCS (selected variables)
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLCS (selected variables)", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlcsSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCount<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLCS);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);

            std::vector<VariableSetType> selectedVariablesVector { { 1, 3, 4, 5, 6 }, { 1, 3, 5, 6 }, { 1, 5, 6 }, { 4, 5 }, { 1 } };

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
     * DLCS (ignore positive pure literals)
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLCS (ignore positive pure literals)", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlcsIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCountIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLCS,
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
     * DLCS (ignore negative pure literals)
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLCS (ignore negative pure literals)", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlcsIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCountIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLCS,
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
     * DLCS (ignore pure literals)
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLCS (ignore pure literals)", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlcsIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCountIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLCS,
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
     * DLIS
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLIS", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlisResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCount<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLIS);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);
            computeDecisionHeuristic(decisionHeuristic.get(), { 1, 2, 3, 4, 5, 6 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * DLIS (selected variables)
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLIS (selected variables)", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlisSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCount<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLIS);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);

            std::vector<VariableSetType> selectedVariablesVector { { 1, 2, 3, 4, 5 }, { 2, 3, 5 }, { 1, 3 }, { 2 } };

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
     * DLIS (ignore positive pure literals)
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLIS (ignore positive pure literals)", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlisIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCountIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLIS,
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
     * DLIS (ignore negative pure literals)
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLIS (ignore negative pure literals)", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlisIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCountIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLIS,
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
     * DLIS (ignore pure literals)
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLIS (ignore pure literals)", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlisIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCountIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLIS,
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
     * DLCS-DLIS
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLCS-DLIS", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlcsDlisResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCount<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLCS_DLIS);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);
            computeDecisionHeuristic(decisionHeuristic.get(), { 1, 2, 3, 4, 5, 6 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * DLCS-DLIS (selected variables)
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLCS-DLIS (selected variables)", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlcsDlisSelectedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCount<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLCS_DLIS);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);

            std::vector<VariableSetType> selectedVariablesVector { { 1, 2, 4, 5, 6 }, { 1, 5, 6 }, { 4, 5 }, { 1 } };

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
     * DLCS-DLIS (ignore positive pure literals)
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLCS-DLIS (ignore positive pure literals)", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlcsDlisIgnorePositivePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCountIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLCS_DLIS,
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
     * DLCS-DLIS (ignore negative pure literals)
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLCS-DLIS (ignore negative pure literals)", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlcsDlisIgnoreNegativePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCountIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLCS_DLIS,
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
     * DLCS-DLIS (ignore pure literals)
     */
    TEST_CASE("[DecisionHeuristic::LiteralCount] DLCS-DLIS (ignore pure literals)", "[DecisionHeuristic::LiteralCount]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          literalCountDecisionHeuristicDlcsDlisIgnorePureLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForLiteralCountIgnorePureLiterals<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get());

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createLiteralCountDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                           DecisionHeuristicTypeEnum::DLCS_DLIS,
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
}   // namespace HydraTest::DecisionHeuristic::LiteralCount
