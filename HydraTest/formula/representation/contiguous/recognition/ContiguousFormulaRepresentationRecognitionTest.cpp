#include <sstream>
#include <stdexcept>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/external/unitTesting/Catch2/catch.hpp"
#include "HydraTest/formula/representation/CreateFormulaRecognition.hpp"
#include "HydraTest/formula/representation/Recognition.hpp"
#include "HydraTest/formula/representation/contiguous/recognition/ContiguousFormulaRepresentationRecognitionTestResult.hpp"

#include "Hydra/formula/representation/contiguous/ContiguousFormulaRepresentation.tpp"

using namespace HydraTest::Formula::Representation::Recognition;

namespace HydraTest::Formula::Representation::Contiguous::Recognition {

    //region Types
    using VarT = Representation::Recognition::VarT;
    using LiteralT = Representation::Recognition::LiteralT;
    using ClauseIdT = Representation::Recognition::ClauseIdT;

    using VariableSetType = Representation::Recognition::VariableSetType;
    using FormulaRepresentationAbstractUniquePtrType = Representation::Recognition::FormulaRepresentationAbstractUniquePtrType;

    using ContiguousFormulaRepresentationConfigurationType = Hydra::Formula::Representation::Contiguous::ContiguousFormulaRepresentationConfiguration;
    //endregion

    //region Functions
    ContiguousFormulaRepresentationConfigurationType createConfiguration(bool kromC = true, bool hornC = true, bool antiHornC = true) {
        ContiguousFormulaRepresentationConfigurationType configuration;
        configuration.recognitionTypeStruct.kromC = kromC;
        configuration.recognitionTypeStruct.hornC = hornC;
        configuration.recognitionTypeStruct.antiHornC = antiHornC;

        return configuration;
    }
    //endregion

    #if defined(BELLA_COMPILER)
    /**
     * Connected components
     */
    TEST_CASE("[Formula::Representation::Contiguous::Recognition] connected components", "[Formula::Representation::Contiguous::Recognition]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationRecognitionConnectedComponentsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createFormulaWithConnectedComponents<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                                 createConfiguration());
            processRecognitionConnectedComponents(formula.get(), currentComponentVariableSet, IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE,
                                                  actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Trivial
     */
    TEST_CASE("[Formula::Representation::Contiguous::Recognition] trivial", "[Formula::Representation::Contiguous::Recognition]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationRecognitionTrivialResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createTrivialFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                 createConfiguration());
            processRecognition(formula.get(), currentComponentVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Connected components (partial assignment)
     */
    TEST_CASE("[Formula::Representation::Contiguous::Recognition] connected components (partial assignment)", "[Formula::Representation::Contiguous::Recognition]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationRecognitionConnectedComponentsPartialAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litNeg1(1, false);
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createFormulaWithConnectedComponentsPartialAssignment<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                                                  createConfiguration());
            processRecognitionConnectedComponents(formula.get(), currentComponentVariableSet, IgnorePureLiteralTypeEnum::NONE, actualResult);

            // Assign the literal -x_1
            assignLiteral(formula.get(), currentComponentVariableSet, litNeg1, actualResult);

            processRecognitionConnectedComponents(formula.get(), currentComponentVariableSet, IgnorePureLiteralTypeEnum::NONE, actualResult);

            // Unassign the literal -x_1
            unassignLiteral(formula.get(), currentComponentVariableSet, litNeg1, actualResult);

            processRecognitionConnectedComponents(formula.get(), currentComponentVariableSet, IgnorePureLiteralTypeEnum::NONE, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Pure clauses
     */
    TEST_CASE("[Formula::Representation::Contiguous::Recognition] pure clauses", "[Formula::Representation::Contiguous::Recognition]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationRecognitionPureClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createFormulaWithPureClauses<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                         createConfiguration());
            processRecognition(formula.get(), currentComponentVariableSet, actualResult);

            processRecognitionConnectedComponents(formula.get(), currentComponentVariableSet, IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE,
                                                  actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Krom-C
     */
    TEST_CASE("[Formula::Representation::Contiguous::Recognition] Krom-C", "[Formula::Representation::Contiguous::Recognition]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationRecognitionKromCResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createKromC<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                        createConfiguration());
            processRecognition(formula.get(), currentComponentVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Krom-C (partial assignment)
     */
    TEST_CASE("[Formula::Representation::Contiguous::Recognition] Krom-C (partial assignment)", "[Formula::Representation::Contiguous::Recognition]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationRecognitionKromCPartialAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createKromCPartialAssignment<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                         createConfiguration());
            processRecognitionAssignment(formula.get(), currentComponentVariableSet, LiteralType(5, true), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Not Krom-C
     */
    TEST_CASE("[Formula::Representation::Contiguous::Recognition] not Krom-C", "[Formula::Representation::Contiguous::Recognition]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationRecognitionNotKromCResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createNotKromC<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                           createConfiguration());
            processRecognition(formula.get(), currentComponentVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Horn-C
     */
    TEST_CASE("[Formula::Representation::Contiguous::Recognition] Horn-C", "[Formula::Representation::Contiguous::Recognition]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationRecognitionHornCResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createHornC<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                        createConfiguration());
            processRecognition(formula.get(), currentComponentVariableSet, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Horn-C (partial assignment)
     */
    TEST_CASE("[Formula::Representation::Contiguous::Recognition] Horn-C (partial assignment)", "[Formula::Representation::Contiguous::Recognition]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationRecognitionHornCPartialAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createHornCPartialAssignment<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                         createConfiguration());
            processRecognitionAssignment(formula.get(), currentComponentVariableSet, LiteralType(3, false), actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Not Horn-C
     */
    TEST_CASE("[Formula::Representation::Contiguous::Recognition] not Horn-C", "[Formula::Representation::Contiguous::Recognition]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationRecognitionNotHornCResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createNotHornC<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                           createConfiguration());
            processRecognition(formula.get(), currentComponentVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Anti-Horn-C
     */
    TEST_CASE("[Formula::Representation::Contiguous::Recognition] anti-Horn-C", "[Formula::Representation::Contiguous::Recognition]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationRecognitionAntiHornCResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createAntiHornC<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                            createConfiguration());
            processRecognition(formula.get(), currentComponentVariableSet, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Anti-Horn-C (partial assignment)
     */
    TEST_CASE("[Formula::Representation::Contiguous::Recognition] anti-Horn-C (partial assignment)", "[Formula::Representation::Contiguous::Recognition]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationRecognitionAntiHornCPartialAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createAntiHornCPartialAssignment<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                             createConfiguration());
            processRecognitionAssignment(formula.get(), currentComponentVariableSet, LiteralType(2, true), actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Not anti-Horn-C
     */
    TEST_CASE("[Formula::Representation::Contiguous::Recognition] not anti-Horn-C", "[Formula::Representation::Contiguous::Recognition]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationRecognitionNotAntiHornCResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formula = createNotAntiHornC<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                               createConfiguration());
            processRecognition(formula.get(), currentComponentVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif
}   // namespace HydraTest::Formula::Representation::Contiguous::Recognition
