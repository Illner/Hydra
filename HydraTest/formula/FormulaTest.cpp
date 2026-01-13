#include <sstream>
#include <stdexcept>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/formula/FormulaTestResult.hpp"

#include "Hydra/formula/Literal.hpp"

namespace HydraTest::Formula {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;

    using LiteralType = Hydra::Formula::Literal<VarT, LiteralT>::LiteralType;
    using LiteralVectorType = Hydra::Formula::Literal<VarT, LiteralT>::LiteralVectorType;
    //endregion

    //region Functions
    void printLiteral(LiteralType& lit, std::stringstream& actualResult) {
        actualResult << "Variable: " << std::to_string(lit.getVariable()) << std::endl;
        actualResult << "Is positive: " << lit.isPositive() << std::endl;
        actualResult << "Is negative: " << lit.isNegative() << std::endl;
        actualResult << "LiteralT: " << std::to_string(lit.getLiteralT()) << std::endl;
        actualResult << "Complementary LiteralT: " << std::to_string(lit.getComplementaryLiteralT()) << std::endl;
        actualResult << "ToString: " << lit.toString() << std::endl;
        actualResult << lit << std::endl;
        actualResult << std::endl;
    }
    //endregion

    /**
     * Literal (constructor)
     */
    TEST_CASE("[Formula] literal (constructor)", "[Formula]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          formulaLiteralConstructorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType lit1(1, true);
            printLiteral(lit1, actualResult);

            LiteralType lit2(2, false);
            printLiteral(lit2, actualResult);

            LiteralType lit3(3);
            printLiteral(lit3, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Literal (copy and move)
     */
    TEST_CASE("[Formula] literal (copy and move)", "[Formula]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          formulaLiteralCopyAndMoveResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType lit1(1, false);
            printLiteral(lit1, actualResult);

            actualResult << "Copy method" << std::endl;
            LiteralType lit2 = lit1;
            lit2.makePositive();
            printLiteral(lit1, actualResult);
            printLiteral(lit2, actualResult);

            actualResult << "Move method" << std::endl;
            LiteralType lit3 = std::move(lit1);
            printLiteral(lit3, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Literal (operators)
     */
    TEST_CASE("[Formula] literal (operators)", "[Formula]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          formulaLiteralOperatorsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            LiteralType litPos1(1, true);
            LiteralType litNeg1(1, false);
            LiteralType litPos2(2, true);
            LiteralType litNeg2(2, false);

            LiteralVectorType literalVector { litPos1, litNeg1, litPos2, litNeg2 };

            for (std::size_t i = 0; i < literalVector.size() - 1; ++i) {
                LiteralType& lit1 = literalVector[i];

                actualResult << "Negation (" << lit1 << "): ";
                LiteralType litTmp = !lit1;
                actualResult << litTmp << std::endl;

                for (std::size_t j = i; j < literalVector.size(); ++j) {
                    LiteralType& lit2 = literalVector[j];

                    actualResult << lit1 << " == " << lit2 << ": " << (lit1 == lit2) << std::endl;
                    actualResult << lit1 << " != " << lit2 << ": " << (lit1 != lit2) << std::endl;
                    actualResult << lit1 << " < " << lit2 << ": " << (lit1 < lit2) << std::endl;
                    actualResult << lit1 << " > " << lit2 << ": " << (lit1 > lit2) << std::endl;
                    actualResult << std::endl;
                }
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Formula
