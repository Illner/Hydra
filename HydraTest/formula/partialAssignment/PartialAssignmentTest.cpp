#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/formula/partialAssignment/PartialAssignmentTestResult.hpp"

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/partialAssignment/PartialAssignment.hpp"

namespace HydraTest::Formula::PartialAssignment {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;

    using LiteralType = typename Hydra::Formula::Literal<VarT, LiteralT>::LiteralType;
    using LiteralVectorType = typename Hydra::Formula::Literal<VarT, LiteralT>::LiteralVectorType;

    using PartialAssignmentType = Hydra::Formula::PartialAssignment::PartialAssignment<VarT, LiteralT>;
    using PartialAssignmentVectorType = std::vector<PartialAssignmentType>;
    //endregion

    //region Functions
    void printPartialAssignment(PartialAssignmentType& partialAssignment, std::stringstream& actualResult) {
        actualResult << "Partial assignment: " << std::endl;
        actualResult << "Number of assigned variables: " << std::to_string(partialAssignment.getNumberOfAssignedVariables()) << std::endl;
        actualResult << "Are all variables assigned: " << std::to_string(partialAssignment.areAllVariablesAssigned()) << std::endl;
        actualResult << "Literals: " << partialAssignment << std::endl;
        actualResult << "Variables: ";
        partialAssignment.printSortedVariablesInPartialAssignment(actualResult);
        actualResult << std::endl;
    }
    //endregion

    /**
     * Constructor
     */
    TEST_CASE("[Formula::PartialAssignment] constructor", "[Formula::PartialAssignment]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          formulaPartialAssignmentConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            actualResult << "Empty partial assignment: " << std::endl;
            PartialAssignmentType partialAssignment1(0);
            printPartialAssignment(partialAssignment1, actualResult);
            actualResult << std::endl;

            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);

            actualResult << "Initialized partial assignment: " << std::endl;
            PartialAssignmentType partialAssignment2(LiteralVectorType { litPos1, litNeg2, litPos3 }, 3);
            printPartialAssignment(partialAssignment2, actualResult);
            actualResult << std::endl;

            actualResult << "Inconsistent partial assignment: " << std::endl;
            try {
                PartialAssignmentType partialAssignment3(LiteralVectorType { litPos1, litNeg2, litNeg1 }, 2);
            }
            catch (const Hydra::Exception::Formula::FormulaException& e) {
                actualResult << e.what() << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Copy and move
     */
    TEST_CASE("[Formula::PartialAssignment] copy and move", "[Formula::PartialAssignment]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          formulaPartialAssignmentCopyAndMoveResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType lit1(1, true);
            LiteralType lit2(2, false);
            LiteralType lit3(3, true);
            LiteralType lit4(4, false);

            PartialAssignmentType partialAssignment1(LiteralVectorType { lit1, lit2, lit3 }, 4);
            printPartialAssignment(partialAssignment1, actualResult);
            actualResult << std::endl;

            actualResult << "Copy method" << std::endl;
            PartialAssignmentType partialAssignment2 = partialAssignment1;
            partialAssignment2.addLiteral(lit4);
            printPartialAssignment(partialAssignment1, actualResult);
            printPartialAssignment(partialAssignment2, actualResult);
            actualResult << std::endl;

            actualResult << "Move method" << std::endl;
            PartialAssignmentType partialAssignment3 = std::move(partialAssignment1);
            printPartialAssignment(partialAssignment3, actualResult);
            actualResult << std::endl;
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Add literals
     */
    TEST_CASE("[Formula::PartialAssignment] add literals", "[Formula::PartialAssignment]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          formulaPartialAssignmentAddLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);

            PartialAssignmentType partialAssignment(LiteralVectorType { litPos1 }, 3);
            printPartialAssignment(partialAssignment, actualResult);
            actualResult << std::endl;

            LiteralVectorType literalVector { litNeg2, litPos3, litNeg1, litPos1 };

            for (const LiteralType& lit : literalVector) {
                actualResult << "Add literal: " << lit << std::endl;

                try {
                    partialAssignment.addLiteral(lit);
                    printPartialAssignment(partialAssignment, actualResult);
                }
                catch (const Hydra::Exception::Formula::FormulaException& e) {
                    actualResult << e.what() << std::endl;
                }

                actualResult << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Remove literals
     */
    TEST_CASE("[Formula::PartialAssignment] remove literals", "[Formula::PartialAssignment]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          formulaPartialAssignmentRemoveLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType litNeg4(4, false);

            PartialAssignmentType partialAssignment(LiteralVectorType { litPos1, litNeg2, litPos3 }, 4);
            printPartialAssignment(partialAssignment, actualResult);
            actualResult << std::endl;

            LiteralVectorType literalVector { litNeg2, litNeg1, litNeg4, litPos1 };

            for (const LiteralType& lit : literalVector) {
                actualResult << "Remove literal: " << lit << std::endl;

                try {
                    partialAssignment.removeLiteral(lit);
                    printPartialAssignment(partialAssignment, actualResult);
                }
                catch (const Hydra::Exception::Formula::FormulaException& e) {
                    actualResult << e.what() << std::endl;
                }

                actualResult << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Exist literals
     */
    TEST_CASE("[Formula::PartialAssignment] exist literals", "[Formula::PartialAssignment]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          formulaPartialAssignmentExistLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litNeg2(2, false);
            LiteralType litPos3(3, true);
            LiteralType litNeg4(4, false);

            PartialAssignmentType partialAssignment(LiteralVectorType { litPos1, litNeg2, litPos3 }, 4);
            printPartialAssignment(partialAssignment, actualResult);
            actualResult << std::endl;

            LiteralVectorType literalVector { litNeg2, litNeg1, litNeg4 };

            for (const LiteralType& lit : literalVector) {
                actualResult << "Literal exists (" << lit << "): ";
                bool result = partialAssignment.literalExists(lit);
                actualResult << result << std::endl;

                actualResult << "Complementary literal exists (" << lit << "): ";
                result = partialAssignment.complementaryLiteralExists(lit);
                actualResult << result << std::endl;

                actualResult << "Variable exists (" << std::to_string(lit.getVariable()) << "): ";
                result = partialAssignment.variableExists(lit.getVariable());
                actualResult << result << std::endl;

                actualResult << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Formula::PartialAssignment
