#include <memory>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/decisionHeuristic/CreateFormula.hpp"
#include "HydraTest/decisionHeuristic/DecisionHeuristic.hpp"
#include "HydraTest/decisionHeuristic/upc/UpcDecisionHeuristicTestResult.hpp"

#include "Hydra/decisionHeuristic/upc/UpcDecisionHeuristic.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/decisionHeuristic/exceptions/DecisionHeuristicException.hpp"

#include "Hydra/decisionHeuristic/upc/UpcDecisionHeuristic.tpp"

namespace HydraTest::DecisionHeuristic::Upc {

    //region Types
    using VarT = HydraTest::DecisionHeuristic::VarT;
    using LiteralT = HydraTest::DecisionHeuristic::LiteralT;
    using ClauseIdT = HydraTest::DecisionHeuristic::ClauseIdT;

    using UpcDecisionHeuristicType = Hydra::DecisionHeuristic::Upc::UpcDecisionHeuristic<VarT, LiteralT, ClauseIdT>;

    using UpcDecisionHeuristicConfigurationType = Hydra::DecisionHeuristic::Upc::UpcDecisionHeuristicConfiguration;
    //endregion

    //region Functions
    DecisionHeuristicAbstractUniquePtrType createUpcDecisionHeuristic(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                                      SatSolverAbstractPtrType satSolverAbstractPtr,
                                                                      bool exactVariant = true, VarT approximateNumberOfVariables = 1,
                                                                      IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::NONE) {
        UpcDecisionHeuristicConfigurationType configuration;
        configuration.exactVariant = exactVariant;
        configuration.approximateNumberOfVariables = approximateNumberOfVariables;

        return std::make_unique<UpcDecisionHeuristicType>(formulaRepresentationAbstractPtr, satSolverAbstractPtr,
                                                          ignorePureLiteralType, configuration);
    }

    void processEupc(SatSolverTypeEnum satSolverType, std::stringstream& actualResult) {
        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForUpc<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get(), satSolverType);

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createUpcDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                  true);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);
            computeDecisionHeuristic(decisionHeuristic.get(),
                                     generateSelectedVariableSet(formulaRepresentation->getNumberOfVariablesInOriginalFormula()),
                                     actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }
    }

    void processEupcSelectedVariables(SatSolverTypeEnum satSolverType, std::stringstream& actualResult) {
        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForUpc<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get(), satSolverType);

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createUpcDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                  true);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);

            std::vector<VariableSetType> selectedVariablesVector { { 2, 3, 4, 5, 6 }, { 2, 3 }, { 4 } };

            for (const VariableSetType& selectedVariables : selectedVariablesVector) {
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }
    }

    void processAupc(SatSolverTypeEnum satSolverType, std::stringstream& actualResult) {
        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForUpc<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get(), satSolverType);

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createUpcDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                  false, 1);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);
            computeDecisionHeuristic(decisionHeuristic.get(),
                                     generateSelectedVariableSet(formulaRepresentation->getNumberOfVariablesInOriginalFormula()),
                                     actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }
    }

    void processAupcSelectedVariables(SatSolverTypeEnum satSolverType, std::stringstream& actualResult) {
        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForUpc<VarT, LiteralT, ClauseIdT>();
            SatSolverAbstractUniquePtrType satSolver = createSatSolver(formulaRepresentation.get(), satSolverType);

            DecisionHeuristicAbstractUniquePtrType decisionHeuristic = createUpcDecisionHeuristic(formulaRepresentation.get(), satSolver.get(),
                                                                                                  false, 2);
            printDecisionHeuristic(decisionHeuristic.get(), actualResult);

            std::vector<VariableSetType> selectedVariablesVector { { 3 }, { 2, 3, 5 }, { 2, 4, 6 }, { 3, 4, 6 }, { 1, 2, 3, 4, 5, 6 } };

            for (const VariableSetType& selectedVariables : selectedVariablesVector) {
                computeDecisionHeuristic(decisionHeuristic.get(), selectedVariables, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }
    }
    //endregion

    /**
     * EUPC
     */
    TEST_CASE("[DecisionHeuristic::Upc] EUPC", "[DecisionHeuristic::Upc]") {
        // MiniSat
        SECTION(Hydra::SatSolver::satSolverTypeEnumToString(SatSolverTypeEnum::MINISAT)) {
            SatSolverTypeEnum satSolverType = SatSolverTypeEnum::MINISAT;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ")",
                              upcDecisionHeuristicEupcResult);
            std::stringstream& actualResult = test.getStringStream();

            processEupc(satSolverType, actualResult);

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // Glucose
        SECTION(Hydra::SatSolver::satSolverTypeEnumToString(SatSolverTypeEnum::GLUCOSE)) {
            SatSolverTypeEnum satSolverType = SatSolverTypeEnum::GLUCOSE;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ")",
                              upcDecisionHeuristicEupcResult);
            std::stringstream& actualResult = test.getStringStream();

            processEupc(satSolverType, actualResult);

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }
    }

    /**
     * EUPC (selected variables)
     */
    TEST_CASE("[DecisionHeuristic::Upc] EUPC (selected variables)", "[DecisionHeuristic::Upc]") {
        // MiniSat
        SECTION(Hydra::SatSolver::satSolverTypeEnumToString(SatSolverTypeEnum::MINISAT)) {
            SatSolverTypeEnum satSolverType = SatSolverTypeEnum::MINISAT;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ")",
                              upcDecisionHeuristicEupcSelectedVariablesResult);
            std::stringstream& actualResult = test.getStringStream();

            processEupcSelectedVariables(satSolverType, actualResult);

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // Glucose
        SECTION(Hydra::SatSolver::satSolverTypeEnumToString(SatSolverTypeEnum::GLUCOSE)) {
            SatSolverTypeEnum satSolverType = SatSolverTypeEnum::GLUCOSE;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ")",
                              upcDecisionHeuristicEupcSelectedVariablesResult);
            std::stringstream& actualResult = test.getStringStream();

            processEupcSelectedVariables(satSolverType, actualResult);

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }
    }

    /**
     * AUPC
     */
    TEST_CASE("[DecisionHeuristic::Upc] AUPC", "[DecisionHeuristic::Upc]") {
        // MiniSat
        SECTION(Hydra::SatSolver::satSolverTypeEnumToString(SatSolverTypeEnum::MINISAT)) {
            SatSolverTypeEnum satSolverType = SatSolverTypeEnum::MINISAT;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ")",
                              upcDecisionHeuristicAupcResult);
            std::stringstream& actualResult = test.getStringStream();

            processAupc(satSolverType, actualResult);

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // Glucose
        SECTION(Hydra::SatSolver::satSolverTypeEnumToString(SatSolverTypeEnum::GLUCOSE)) {
            SatSolverTypeEnum satSolverType = SatSolverTypeEnum::GLUCOSE;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ")",
                              upcDecisionHeuristicAupcResult);
            std::stringstream& actualResult = test.getStringStream();

            processAupc(satSolverType, actualResult);

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }
    }

    /**
     * AUPC (selected variables)
     */
    TEST_CASE("[DecisionHeuristic::Upc] AUPC (selected variables)", "[DecisionHeuristic::Upc]") {
        // MiniSat
        SECTION(Hydra::SatSolver::satSolverTypeEnumToString(SatSolverTypeEnum::MINISAT)) {
            SatSolverTypeEnum satSolverType = SatSolverTypeEnum::MINISAT;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ")",
                              upcDecisionHeuristicAupcSelectedVariablesResult);
            std::stringstream& actualResult = test.getStringStream();

            processAupcSelectedVariables(satSolverType, actualResult);

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // Glucose
        SECTION(Hydra::SatSolver::satSolverTypeEnumToString(SatSolverTypeEnum::GLUCOSE)) {
            SatSolverTypeEnum satSolverType = SatSolverTypeEnum::GLUCOSE;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + Hydra::SatSolver::satSolverTypeEnumToString(satSolverType) + ")",
                              upcDecisionHeuristicAupcSelectedVariablesResult);
            std::stringstream& actualResult = test.getStringStream();

            processAupcSelectedVariables(satSolverType, actualResult);

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }
    }
}   // namespace HydraTest::DecisionHeuristic::Upc
