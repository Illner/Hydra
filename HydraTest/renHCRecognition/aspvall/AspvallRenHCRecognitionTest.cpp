#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/renHCRecognition/CreateFormula.hpp"
#include "HydraTest/renHCRecognition/RenHCRecognition.hpp"
#include "HydraTest/renHCRecognition/aspvall/AspvallRenHCRecognitionTestResult.hpp"

#include "Hydra/renHCRecognition/aspvall/creation/AspvallRenHCRecognitionCreation.hpp"

#include "Hydra/renHCRecognition/exceptions/RenHCRecognitionException.hpp"

namespace HydraTest::RenHCRecognition::Aspvall {

    //region Types
    using VarT = HydraTest::RenHCRecognition::VarT;
    using LiteralT = HydraTest::RenHCRecognition::LiteralT;
    using ClauseIdT = HydraTest::RenHCRecognition::ClauseIdT;

    using IgnorePureLiteralTypeEnum = HydraTest::RenHCRecognition::IgnorePureLiteralTypeEnum;
    //endregion

    //region Functions
    RenHCRecognitionAbstractUniquePtrType createAspvallRenHCRecognition(FormulaRepresentationAbstractConstPtrType formulaRepresentationAbstractPtr,
                                                                        const VariableSetType& currentComponentVariableSet = {},
                                                                        IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE) {
        return Hydra::RenHCRecognition::Aspvall::Creation::createAspvallRenHCRecognition(formulaRepresentationAbstractPtr, ignorePureLiteralType,
                                                                                         nullptr, currentComponentVariableSet);
    }
    //endregion

    #if defined(BELLA_COMPILER)
    /**
     * Constructor
     */
    TEST_CASE("[RenHCRecognition::Aspvall] constructor", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>(variableSet, false);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Constructor (residual)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] constructor (residual)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionConstructorResidualResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>(variableSet, true);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Set (in)active clauses
     */
    TEST_CASE("[RenHCRecognition::Aspvall] set (in)active clauses", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionSetInActiveClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createMonotoneFormula<VarT, LiteralT, ClauseIdT>(variableSet, false);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);
            actualResult << std::endl;

            std::vector<ClauseIdSetType> clausesVector { { (ClauseIdT)0 }, { (ClauseIdT)1 }, { (ClauseIdT)2 }, { (ClauseIdT)3 }, { (ClauseIdT)0, (ClauseIdT)3 }, { (ClauseIdT)0, (ClauseIdT)1, (ClauseIdT)2, (ClauseIdT)3 } };

            for (const ClauseIdSetType& clauseSet : clausesVector) {
                printClauses(clauseSet, actualResult);

                actualResult << "set inactive clause(s)" << std::endl;
                aspvall->setInactiveClauseSet(clauseSet);
                printRenHCRecognition(aspvall.get(), actualResult);

                actualResult << "set active clause(s)" << std::endl;
                aspvall->setActiveClauseSet(clauseSet, variableSet);
                printRenHCRecognition(aspvall.get(), actualResult);

                actualResult << "--------------------" << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Set (in)active clauses (residual)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] set (in)active clauses (residual)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionSetInActiveClausesResidualResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createMonotoneFormula<VarT, LiteralT, ClauseIdT>(variableSet, true);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);
            actualResult << std::endl;

            std::vector<ClauseIdSetType> clausesVector { { (ClauseIdT)1 }, { (ClauseIdT)2 }, { (ClauseIdT)1, (ClauseIdT)2 } };

            for (const ClauseIdSetType& clauseSet : clausesVector) {
                printClauses(clauseSet, actualResult);

                actualResult << "set inactive clause(s)" << std::endl;
                aspvall->setInactiveClauseSet(clauseSet);
                printRenHCRecognition(aspvall.get(), actualResult);

                actualResult << "set active clause(s)" << std::endl;
                aspvall->setActiveClauseSet(clauseSet, variableSet);
                printRenHCRecognition(aspvall.get(), actualResult);

                actualResult << "--------------------" << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Set (un)assigned literal
     */
    TEST_CASE("[RenHCRecognition::Aspvall] set (un)assigned literal", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionSetUnAssignedLiteralResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet, false);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);

            LiteralVectorType literalVector { LiteralType(1, true), LiteralType(1, false), LiteralType(2, true), LiteralType(2, false),
                                              LiteralType(3, true), LiteralType(3, false), LiteralType(4, true), LiteralType(4, false) };

            for (const LiteralType& lit : literalVector) {
                // Assign the literal
                assignLiteral(formulaRepresentation.get(), aspvall.get(), lit, currentComponentVariableSet, actualResult);

                // Unassign the literal
                unassignLiteral(formulaRepresentation.get(), aspvall.get(), lit, currentComponentVariableSet, actualResult);

                actualResult << "------------------------------------------------------------" << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Set (un)assigned literal (residual)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] set (un)assigned literal (residual)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionSetUnAssignedLiteralResidualResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet, true);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);

            LiteralVectorType literalVector { LiteralType(1, true), LiteralType(1, false), LiteralType(2, true), LiteralType(2, false),
                                              LiteralType(3, true), LiteralType(3, false) };

            for (const LiteralType& lit : literalVector) {
                // Assign the literal
                assignLiteral(formulaRepresentation.get(), aspvall.get(), lit, currentComponentVariableSet, actualResult);

                // Unassign the literal
                unassignLiteral(formulaRepresentation.get(), aspvall.get(), lit, currentComponentVariableSet, actualResult);

                actualResult << "------------------------------------------------------------" << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Set (un)assigned literal (deep)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] set (un)assigned literal (deep)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionSetUnAssignedLiteralDeepResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet, false);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);

            LiteralType litNeg1(1, false);
            LiteralType litNeg2(2, false);
            LiteralType litNeg3(3, false);
            LiteralType litNeg4(4, false);

            // Assign -x_4
            assignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg4, currentComponentVariableSet, actualResult);

            // Assign -x_1
            assignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg1, currentComponentVariableSet, actualResult);

            // Assign -x_3
            assignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg3, currentComponentVariableSet, actualResult);

            // Assign -x_2
            assignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg2, currentComponentVariableSet, actualResult);

            actualResult << "------------------------------------------------------------" << std::endl;

            // Unassign -x_2
            unassignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg2, currentComponentVariableSet, actualResult);

            // Unassign -x_3
            unassignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg3, currentComponentVariableSet, actualResult);

            // Unassign -x_1
            unassignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg1, currentComponentVariableSet, actualResult);

            // Unassign -x_4
            unassignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg4, currentComponentVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Set (un)assigned literal (deep) (residual)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] set (un)assigned literal (deep) (residual)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionSetUnAssignedLiteralDeepResidualResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet, true);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);

            LiteralType litNeg1(1, false);
            LiteralType litNeg2(2, false);
            LiteralType litNeg3(3, false);

            // Assign -x_1
            assignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg1, currentComponentVariableSet, actualResult);

            // Assign -x_3
            assignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg3, currentComponentVariableSet, actualResult);

            // Assign -x_2
            assignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg2, currentComponentVariableSet, actualResult);

            actualResult << "------------------------------------------------------------" << std::endl;

            // Unassign -x_2
            unassignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg2, currentComponentVariableSet, actualResult);

            // Unassign -x_3
            unassignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg3, currentComponentVariableSet, actualResult);

            // Unassign -x_1
            unassignLiteral(formulaRepresentation.get(), aspvall.get(), litNeg1, currentComponentVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Set (un)assigned literals (empty)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] set (un)assigned literals (empty)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionSetUnAssignedLiteralsEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet, false);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);

            assignLiteralVector(formulaRepresentation.get(), aspvall.get(), {}, currentComponentVariableSet, actualResult);
            unassignLiteralVector(formulaRepresentation.get(), aspvall.get(), {}, currentComponentVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Set (un)assigned literals (empty) (residual)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] set (un)assigned literals (empty) (residual)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionSetUnAssignedLiteralsEmptyResidualResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet, true);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);

            assignLiteralVector(formulaRepresentation.get(), aspvall.get(), {}, currentComponentVariableSet, actualResult);
            unassignLiteralVector(formulaRepresentation.get(), aspvall.get(), {}, currentComponentVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Set (un)assigned literals
     */
    TEST_CASE("[RenHCRecognition::Aspvall] set (un)assigned literals", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionSetUnAssignedLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet, false);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);

            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType litNeg3(3, false);
            LiteralType litPos4(4, true);
            LiteralType litNeg4(4, false);

            std::vector<LiteralVectorType> literalsVector { { litPos1 }, { litNeg1 }, { litPos2 }, { litNeg2 }, { litPos3 }, { litNeg3 }, { litPos4 }, { litNeg4 }, { litPos1, litNeg3 }, { litNeg3, litPos1 }, { litPos1, litNeg2 }, { litPos1, litPos2, litPos4 }, { litPos1, litNeg2, litNeg3, litNeg4 } };

            for (const LiteralVectorType& literalVector : literalsVector) {
                // Assign the literals
                assignLiteralVector(formulaRepresentation.get(), aspvall.get(), literalVector, currentComponentVariableSet, actualResult);

                // Unassign the literals
                unassignLiteralVector(formulaRepresentation.get(), aspvall.get(), literalVector, currentComponentVariableSet, actualResult);

                actualResult << "------------------------------------------------------------" << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Set (un)assigned literals (residual)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] set (un)assigned literals (residual)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionSetUnAssignedLiteralsResidualResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet, true);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);

            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType litNeg3(3, false);

            std::vector<LiteralVectorType> literalsVector { { litPos1 }, { litNeg1 }, { litPos2 }, { litNeg2 }, { litPos3 }, { litNeg3 }, { litPos1, litPos2 }, { litPos2, litPos1 }, { litPos3, litNeg2 }, { litPos3, litPos2, litPos1 } };

            for (const LiteralVectorType& literalVector : literalsVector) {
                // Assign the literals
                assignLiteralVector(formulaRepresentation.get(), aspvall.get(), literalVector, currentComponentVariableSet, actualResult);

                // Unassign the literals
                unassignLiteralVector(formulaRepresentation.get(), aspvall.get(), literalVector, currentComponentVariableSet, actualResult);

                actualResult << "------------------------------------------------------------" << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Set (un)assigned literals (deep)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] set (un)assigned literals (deep)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionSetUnAssignedLiteralsDeepResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet, false);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);

            std::vector<LiteralVectorType> literalsVector { { LiteralType(4, true), LiteralType(1, false) }, { LiteralType(2, false) } };

            // Assign the literals
            for (const LiteralVectorType& literalVector : literalsVector) {
                assignLiteralVector(formulaRepresentation.get(), aspvall.get(), literalVector, currentComponentVariableSet, actualResult);
            }

            actualResult << "------------------------------------------------------------" << std::endl;

            // Unassign the literals
            for (auto it = literalsVector.crbegin(); it != literalsVector.crend(); ++it) {
                const LiteralVectorType& literalVector = *it;

                unassignLiteralVector(formulaRepresentation.get(), aspvall.get(), literalVector, currentComponentVariableSet, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Set (un)assigned literals (deep) (residual)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] set (un)assigned literals (deep) (residual)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionSetUnAssignedLiteralsDeepResidualResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet, true);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get());
            printRenHCRecognition(aspvall.get(), actualResult);

            std::vector<LiteralVectorType> literalsVector { { LiteralType(2, false), LiteralType(1, false) }, { LiteralType(3, false) } };

            // Assign the literals
            for (const LiteralVectorType& literalVector : literalsVector) {
                assignLiteralVector(formulaRepresentation.get(), aspvall.get(), literalVector, currentComponentVariableSet, actualResult);
            }

            actualResult << "------------------------------------------------------------" << std::endl;

            // Unassign the literals
            for (auto it = literalsVector.crbegin(); it != literalsVector.crend(); ++it) {
                const LiteralVectorType& literalVector = *it;

                unassignLiteralVector(formulaRepresentation.get(), aspvall.get(), literalVector, currentComponentVariableSet, actualResult);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Current component formula - whole (constructor)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] current component formula - whole (constructor)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionCurrentComponentFormulaWholeConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createCurrentComponentFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                                        false);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), currentComponentVariableSet);
            printRenHCRecognition(aspvall.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Current component formula - whole (residual) (constructor)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] current component formula - whole (residual) (constructor)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionCurrentComponentFormulaWholeResidualConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createCurrentComponentFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                                        true);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), currentComponentVariableSet);
            printRenHCRecognition(aspvall.get(), actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Current component formula (constructor)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] current component formula (constructor)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionCurrentComponentFormulaConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createCurrentComponentFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                                        false);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            ConnectedComponentType connectedComponents = computeConnectedComponents(formulaRepresentation.get(), currentComponentVariableSet, actualResult);

            for (const ConnectedComponentStruct& connectedComponent : connectedComponents) {
                setNewComponent(formulaRepresentation.get(), connectedComponent, actualResult);

                RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), connectedComponent.variableSet);
                printRenHCRecognition(aspvall.get(), actualResult);

                popPreviousComponent(formulaRepresentation.get(), connectedComponent, actualResult, false);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Current component formula (residual) (constructor)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] current component formula (residual) (constructor)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionCurrentComponentFormulaResidualConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createCurrentComponentFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                                        true);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            ConnectedComponentType connectedComponents = computeConnectedComponents(formulaRepresentation.get(), currentComponentVariableSet, actualResult);

            for (const ConnectedComponentStruct& connectedComponent : connectedComponents) {
                setNewComponent(formulaRepresentation.get(), connectedComponent, actualResult);

                RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), connectedComponent.variableSet);
                printRenHCRecognition(aspvall.get(), actualResult);

                popPreviousComponent(formulaRepresentation.get(), connectedComponent, actualResult, false);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Verify renH-C - whole
     */
    TEST_CASE("[RenHCRecognition::Aspvall] verify renH-C - whole", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionVerifyRenHCWholeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createCurrentComponentFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                                        false);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), currentComponentVariableSet);
            printRenHCRecognition(aspvall.get(), actualResult);

            std::vector<VariableSetType> switchedVariablesVector = { {},
                                                                     { 3 },
                                                                     { 1, 2, 3 },
                                                                     { 4 },
                                                                     { 5 },
                                                                     { 3, 6 },
                                                                     { 1, 2, 3, 6 },
                                                                     { 1, 4 },
                                                                     { 2, 4 },
                                                                     { 1, 5 },
                                                                     { 2, 5 },
                                                                     { 3, 4 },
                                                                     { 3, 5 },
                                                                     { 1, 2, 3, 4 },
                                                                     { 1, 2, 3, 5 },
                                                                     { 1, 2, 3, 4, 5, 6 } };

            for (const VariableSetType& switchedVariableSet : switchedVariablesVector)
                verifyRenHC(aspvall.get(), switchedVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Verify renH-C - whole (residual)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] verify renH-C - whole (residual)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionVerifyRenHCWholeResidualResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createCurrentComponentFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                                        true);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), currentComponentVariableSet);
            printRenHCRecognition(aspvall.get(), actualResult);

            std::vector<VariableSetType> switchedVariablesVector = { {},
                                                                     { 2 },
                                                                     { 3 },
                                                                     { 2, 3 },
                                                                     { 4 },
                                                                     { 5 },
                                                                     { 2, 4 },
                                                                     { 2, 5 },
                                                                     { 3, 4 },
                                                                     { 3, 5 },
                                                                     { 2, 3, 4 },
                                                                     { 2, 3, 5 },
                                                                     { 2, 3, 4, 5 } };

            for (const VariableSetType& switchedVariableSet : switchedVariablesVector)
                verifyRenHC(aspvall.get(), switchedVariableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Verify renH-C
     */
    TEST_CASE("[RenHCRecognition::Aspvall] verify renH-C", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionVerifyRenHCResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createCurrentComponentFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                                        false);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            std::vector<VariableSetType> firstComponentSwitchedVariablesVector = { {}, { 1 }, { 2 }, { 3 }, { 1, 2 }, { 1, 3 }, { 2, 3 }, { 1, 2, 3 } };
            std::vector<VariableSetType> secondComponentSwitchedVariablesVector = { {}, { 4 }, { 5 }, { 6 }, { 4, 5 }, { 4, 6 }, { 5, 6 }, { 4, 5, 6 } };

            ConnectedComponentType connectedComponents = computeConnectedComponents(formulaRepresentation.get(), currentComponentVariableSet, actualResult);

            for (const ConnectedComponentStruct& connectedComponent : connectedComponents) {
                setNewComponent(formulaRepresentation.get(), connectedComponent, actualResult);

                RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), connectedComponent.variableSet);
                printRenHCRecognition(aspvall.get(), actualResult);

                auto switchedVariablesVector = Hydra::Other::containInSet(connectedComponent.variableSet, (VarT)2) ? firstComponentSwitchedVariablesVector : secondComponentSwitchedVariablesVector;

                for (const VariableSetType& switchedVariableSet : switchedVariablesVector)
                    verifyRenHC(aspvall.get(), switchedVariableSet, actualResult);

                popPreviousComponent(formulaRepresentation.get(), connectedComponent, actualResult, false);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Verify renH-C (residual)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] verify renH-C (residual)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionVerifyRenHCResidualResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createCurrentComponentFormula<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet,
                                                                                                                                        true);
            printCurrentFormula(formulaRepresentation.get(), actualResult);

            std::vector<VariableSetType> firstComponentSwitchedVariablesVector = { {}, { 2 }, { 3 }, { 2, 3 } };
            std::vector<VariableSetType> secondComponentSwitchedVariablesVector = { {}, { 4 }, { 5 }, { 4, 5 } };

            ConnectedComponentType connectedComponents = computeConnectedComponents(formulaRepresentation.get(), currentComponentVariableSet, actualResult);

            for (const ConnectedComponentStruct& connectedComponent : connectedComponents) {
                setNewComponent(formulaRepresentation.get(), connectedComponent, actualResult);

                RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), connectedComponent.variableSet);
                printRenHCRecognition(aspvall.get(), actualResult);

                auto switchedVariablesVector = Hydra::Other::containInSet(connectedComponent.variableSet, (VarT)2) ? firstComponentSwitchedVariablesVector : secondComponentSwitchedVariablesVector;

                for (const VariableSetType& switchedVariableSet : switchedVariablesVector)
                    verifyRenHC(aspvall.get(), switchedVariableSet, actualResult);

                popPreviousComponent(formulaRepresentation.get(), connectedComponent, actualResult, false);
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * RenH-C (positive)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] renH-C (positive)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionRenHCPositiveResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createRenHCPositive<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);

            IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::ONLY_POSITIVE;
            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), {}, ignorePureLiteralType);

            isRenHC(formulaRepresentation.get(), aspvall.get(), currentComponentVariableSet, ignorePureLiteralType, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * No renH-C (positive)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] no renH-C (positive)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionNoRenHCPositiveResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createNoRenHCPositive<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);

            IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::ONLY_POSITIVE;
            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), {}, ignorePureLiteralType);

            isRenHC(formulaRepresentation.get(), aspvall.get(), currentComponentVariableSet, ignorePureLiteralType, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * RenH-C - partial assignment (positive)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] renH-C - partial assignment (positive)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionRenHCPartialAssignmentPositiveResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createRenHCPartialAssignmentPositive<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);

            IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::ONLY_POSITIVE;
            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), {}, ignorePureLiteralType);

            LiteralVectorType partialAssignment = { LiteralType((VarT)2, false) };

            partialAssignmentIsRenHC(formulaRepresentation.get(), aspvall.get(),
                                     partialAssignment, currentComponentVariableSet, ignorePureLiteralType, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * RenH-C (negative)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] renH-C (negative)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionRenHCNegativeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createRenHCNegative<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);

            IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::ONLY_NEGATIVE;
            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), {}, ignorePureLiteralType);

            isRenHC(formulaRepresentation.get(), aspvall.get(), currentComponentVariableSet, ignorePureLiteralType, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * No renH-C (negative)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] no renH-C (negative)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionNoRenHCNegativeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createNoRenHCNegative<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);

            IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::ONLY_NEGATIVE;
            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), {}, ignorePureLiteralType);

            isRenHC(formulaRepresentation.get(), aspvall.get(), currentComponentVariableSet, ignorePureLiteralType, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * RenH-C - partial assignment (negative)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] renH-C - partial assignment (negative)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionRenHCPartialAssignmentNegativeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createRenHCPartialAssignmentNegative<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);

            IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::ONLY_NEGATIVE;
            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), {}, ignorePureLiteralType);

            LiteralVectorType partialAssignment = { LiteralType((VarT)1, false) };

            partialAssignmentIsRenHC(formulaRepresentation.get(), aspvall.get(),
                                     partialAssignment, currentComponentVariableSet, ignorePureLiteralType, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * RenH-C (both positive and negative)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] renH-C (both positive and negative)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionRenHCBothPositiveAndNegativeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createRenHCBothPositiveAndNegative<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);

            IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE;
            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), {}, ignorePureLiteralType);

            isRenHC(formulaRepresentation.get(), aspvall.get(), currentComponentVariableSet, ignorePureLiteralType, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * No renH-C (both positive and negative)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] no renH-C (both positive and negative)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionNoRenHCBothPositiveAndNegativeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createNoRenHCBothPositiveAndNegative<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);

            IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE;
            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), {}, ignorePureLiteralType);

            isRenHC(formulaRepresentation.get(), aspvall.get(), currentComponentVariableSet, ignorePureLiteralType, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * RenH-C - partial assignment (both positive and negative)
     */
    TEST_CASE("[RenHCRecognition::Aspvall] renH-C - partial assignment (both positive and negative)", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionRenHCPartialAssignmentBothPositiveAndNegativeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createRenHCPartialAssignmentBothPositiveAndNegative<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);

            IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE;
            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), {}, ignorePureLiteralType);

            LiteralVectorType partialAssignment = { LiteralType((VarT)5, false) };

            partialAssignmentIsRenHC(formulaRepresentation.get(), aspvall.get(),
                                     partialAssignment, currentComponentVariableSet, ignorePureLiteralType, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * RenH-C
     */
    TEST_CASE("[RenHCRecognition::Aspvall] renH-C", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionRenHCResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createRenHC<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);

            IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::NONE;
            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), {}, ignorePureLiteralType);

            isRenHC(formulaRepresentation.get(), aspvall.get(), currentComponentVariableSet, ignorePureLiteralType, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * RenH-C - partial assignment
     */
    TEST_CASE("[RenHCRecognition::Aspvall] renH-C - partial assignment", "[RenHCRecognition::Aspvall]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          aspvallRenHCRecognitionRenHCPartialAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType currentComponentVariableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createRenHCPartialAssignment<VarT, LiteralT, ClauseIdT>(currentComponentVariableSet);

            IgnorePureLiteralTypeEnum ignorePureLiteralType = IgnorePureLiteralTypeEnum::NONE;
            RenHCRecognitionAbstractUniquePtrType aspvall = createAspvallRenHCRecognition(formulaRepresentation.get(), {}, ignorePureLiteralType);

            std::vector<LiteralVectorType> partialAssignmentVector = { { LiteralType((VarT)3, false), LiteralType((VarT)1, false) },
                                                                       { LiteralType((VarT)4, false), LiteralType((VarT)2, false) } };

            for (const LiteralVectorType& partialAssignment : partialAssignmentVector) {
                partialAssignmentIsRenHC(formulaRepresentation.get(), aspvall.get(),
                                         partialAssignment, currentComponentVariableSet, ignorePureLiteralType, actualResult);

                actualResult << "------------------------------------------------------------" << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif
}   // namespace HydraTest::RenHCRecognition::Aspvall
