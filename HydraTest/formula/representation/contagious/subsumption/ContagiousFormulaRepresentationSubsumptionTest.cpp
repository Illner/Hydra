#include <sstream>
#include <stdexcept>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/formula/representation/contagious/subsumption/ContagiousFormulaRepresentationSubsumptionTestResult.hpp"

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.tpp"

#include "Hydra/formula/representation/contagious/enums/SubsumptionTypeEnum.hpp"

namespace HydraTest::Formula::Representation::Contagious::Subsumption {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    using ClauseIdT = char8_t;

    using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
    using LiteralVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
    using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
    using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
    using VariableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;

    using ContagiousFormulaRepresentationConfigurationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration;
    using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

    using SubsumptionTypeEnum = Hydra::Formula::Representation::Contagious::SubsumptionTypeEnum;
    //endregion

    //region Functions
    void printContagiousFormulaRepresentationSubsumption(const ContagiousFormulaRepresentationType& contagiousFormulaRepresentation,
                                                         std::stringstream& actualResult) {
        actualResult << "Current formula: " << std::endl;
        contagiousFormulaRepresentation.printCurrentFormulaDebug(actualResult, false, false);
        actualResult << std::endl
                     << "--------------------" << std::endl
                     << std::endl;

        actualResult << "Current formula (no duplicate clauses): " << std::endl;
        contagiousFormulaRepresentation.printCurrentFormulaDebug(actualResult, true, false);
        actualResult << std::endl
                     << "--------------------" << std::endl
                     << std::endl;

        actualResult << "Current formula (no duplicate and subsumed clauses): " << std::endl;
        contagiousFormulaRepresentation.printCurrentFormulaDebug(actualResult, true, true);
        actualResult << std::endl
                     << "--------------------" << std::endl
                     << std::endl;
    }

    void processSubsumptionAssignment(ContagiousFormulaRepresentationType& contagiousFormulaRepresentation, std::stringstream& actualResult) {
        printContagiousFormulaRepresentationSubsumption(contagiousFormulaRepresentation, actualResult);
        actualResult << "--------------------------------------------------------------------------------" << std::endl
                     << std::endl;

        LiteralVectorType assignment { LiteralType(1, false),
                                       LiteralType(3, true),
                                       LiteralType(8, true),
                                       LiteralType(13, false),
                                       LiteralType(11, true) };

        for (const LiteralType& lit : assignment) {
            actualResult << "Add assignment: " << lit << std::endl;

            VariableVectorType tmp;
            contagiousFormulaRepresentation.addLiteralToPartialAssignment(lit, tmp);

            printContagiousFormulaRepresentationSubsumption(contagiousFormulaRepresentation, actualResult);
        }

        actualResult << std::endl
                     << "----------------------------------------" << std::endl
                     << std::endl;

        for (auto it = assignment.rbegin(); it != assignment.rend(); ++it) {
            const LiteralType& lit = *it;

            actualResult << "Remove assignment: " << lit << std::endl;

            VariableVectorType tmp;
            contagiousFormulaRepresentation.removeLiteralFromPartialAssignment(lit, tmp);

            printContagiousFormulaRepresentationSubsumption(contagiousFormulaRepresentation, actualResult);
        }
    }
    //endregion

    //region ContagiousFormulaRepresentation
    ContagiousFormulaRepresentationType createContagiousFormulaRepresentation(SubsumptionTypeEnum subsumptionType) {
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litPos9(9, true);
        LiteralType litNeg9(9, false);
        LiteralType litPos10(10, true);
        LiteralType litNeg10(10, false);
        LiteralType litPos11(11, true);
        LiteralType litNeg11(11, false);
        LiteralType litPos12(12, true);
        LiteralType litNeg12(12, false);
        LiteralType litPos13(13, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, litPos2, zeroLit,   // 0
            litPos1, litNeg2, zeroLit,   // 1
            litNeg1, litPos2, zeroLit,   // 2
            litNeg1, litNeg2, zeroLit,   // 3

            litNeg2, litNeg1, zeroLit,   // 4
            litPos2, litNeg1, zeroLit,   // 5
            litNeg2, litPos1, zeroLit,   // 6
            litPos2, litPos1, zeroLit,   // 7

            litPos3, zeroLit,            // 8
            litPos3, litPos4, zeroLit,   // 9
            litPos3, litNeg4, zeroLit,   // 10
            litNeg3, litPos4, zeroLit,   // 11
            litNeg3, litNeg4, zeroLit,   // 12

            litPos4, litPos3, zeroLit,   // 13
            litNeg4, litPos3, zeroLit,   // 14
            litPos4, litNeg3, zeroLit,   // 15
            litNeg4, litNeg3, zeroLit,   // 16
            litPos3, zeroLit,            // 17

            litPos5, litPos6, zeroLit,   // 18
            litPos5, litNeg6, zeroLit,   // 19
            litNeg5, litPos6, zeroLit,   // 20
            litNeg5, litNeg6, zeroLit,   // 21
            litNeg6, zeroLit,            // 22

            litPos7, litNeg8, zeroLit,            // 23
            litPos7, litPos8, litPos9, zeroLit,   // 24
            litPos7, litPos8, litNeg9, zeroLit,   // 25
            litPos7, litNeg8, litPos9, zeroLit,   // 26
            litPos7, litNeg8, litNeg9, zeroLit,   // 27
            litNeg7, litPos8, litPos9, zeroLit,   // 28
            litNeg7, litPos8, litNeg9, zeroLit,   // 29
            litNeg7, litNeg8, litPos9, zeroLit,   // 30
            litNeg7, litNeg8, litNeg9, zeroLit,   // 31

            litPos10, litPos11, litPos12, zeroLit,   // 32
            litPos10, litPos11, litPos13, zeroLit,   // 33

            litNeg10, litNeg11, zeroLit,   // 34
            litNeg10, litNeg12, zeroLit    // 35
        };

        VarT numberOfVariables = 13;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        ContagiousFormulaRepresentationConfigurationType configuration;
        configuration.subsumptionType = subsumptionType;

        ContagiousFormulaRepresentationType contagiousFormulaRepresentation(std::move(formula),
                                                                            numberOfVariables, numberOfClauses,
                                                                            literalNumberOfOccurrences,
                                                                            configuration);
        return contagiousFormulaRepresentation;
    }
    //endregion

    /**
     * Backward subsumption detection
     */
    TEST_CASE("[Formula::Representation::Contagious::Subsumption] backward subsumption detection", "[Formula::Representation::Contagious::Subsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousFormulaRepresentationType formula = createContagiousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION);
            printContagiousFormulaRepresentationSubsumption(formula, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward subsumption detection (assignment)
     */
    TEST_CASE("[Formula::Representation::Contagious::Subsumption] backward subsumption detection (assignment)", "[Formula::Representation::Contagious::Subsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSubsumptionAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousFormulaRepresentationType formula = createContagiousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION);
            processSubsumptionAssignment(formula, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward subsumption detection - intersection
     */
    TEST_CASE("[Formula::Representation::Contagious::Subsumption] backward subsumption detection - intersection", "[Formula::Representation::Contagious::Subsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousFormulaRepresentationType formula = createContagiousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION);
            printContagiousFormulaRepresentationSubsumption(formula, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Backward subsumption detection - intersection (assignment)
     */
    TEST_CASE("[Formula::Representation::Contagious::Subsumption] backward subsumption detection - intersection (assignment)", "[Formula::Representation::Contagious::Subsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSubsumptionAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousFormulaRepresentationType formula = createContagiousFormulaRepresentation(SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION);
            processSubsumptionAssignment(formula, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward subsumption detection
     */
    TEST_CASE("[Formula::Representation::Contagious::Subsumption] forward subsumption detection", "[Formula::Representation::Contagious::Subsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousFormulaRepresentationType formula = createContagiousFormulaRepresentation(SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION);
            printContagiousFormulaRepresentationSubsumption(formula, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Forward subsumption detection (assignment)
     */
    TEST_CASE("[Formula::Representation::Contagious::Subsumption] forward subsumption detection (assignment)", "[Formula::Representation::Contagious::Subsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSubsumptionAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousFormulaRepresentationType formula = createContagiousFormulaRepresentation(SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION);
            processSubsumptionAssignment(formula, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm
     */
    TEST_CASE("[Formula::Representation::Contagious::Subsumption] one-literal watching algorithm", "[Formula::Representation::Contagious::Subsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSubsumptionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousFormulaRepresentationType formula = createContagiousFormulaRepresentation(SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM);
            printContagiousFormulaRepresentationSubsumption(formula, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One-literal watching algorithm (assignment)
     */
    TEST_CASE("[Formula::Representation::Contagious::Subsumption] one-literal watching algorithm (assignment)", "[Formula::Representation::Contagious::Subsumption]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationSubsumptionAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ContagiousFormulaRepresentationType formula = createContagiousFormulaRepresentation(SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM);
            processSubsumptionAssignment(formula, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Formula::Representation::Contagious::Subsumption
