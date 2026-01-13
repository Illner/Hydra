#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/formula/representation/contagious/parser/ContagiousFormulaRepresentationParserTestFormula.hpp"
#include "HydraTest/formula/representation/contagious/parser/ContagiousFormulaRepresentationParserTestInput.hpp"
#include "HydraTest/formula/representation/contagious/parser/ContagiousFormulaRepresentationParserTestResult.hpp"

#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.hpp"
#include "Hydra/formula/representation/contagious/parser/ContagiousFormulaParser.hpp"
#include "Hydra/other/parser/Parser.hpp"

#include "Cara/sharpSolver/enums/ModelCountingTypeEnum.hpp"

namespace HydraTest::Formula::Representation::Contagious::Parser {

    //region Types
    using VarT = char16_t;
    using LiteralT = char16_t;
    using ClauseIdT = char16_t;

    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

    using ModelCountingTypeEnum = Cara::ModelCountingTypeEnum;
    //endregion

    //region Functions
    FormulaRepresentationAbstractUniquePtrType parseFormula(const std::string& formulaString, bool forbidClausesContainingComplementaryLiterals = true) {
        unsigned int line = 1;

        std::istringstream stringStream(formulaString);
        std::istreambuf_iterator<char> begin(stringStream);
        std::istreambuf_iterator<char> end;

        auto header = Hydra::Other::Parser::parseDimacsCnfHeader(begin, end, line);
        return Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, header, line,
                                                                                                                                           forbidClausesContainingComplementaryLiterals);
    }

    FormulaRepresentationAbstractUniquePtrType parseFormula(const std::string& formulaString, ModelCountingTypeEnum& modelCountingType) {
        unsigned int line = 1;

        std::istringstream stringStream(formulaString);
        std::istreambuf_iterator<char> begin(stringStream);
        std::istreambuf_iterator<char> end;

        Hydra::Other::Parser::parseCommentLines(begin, end, line, modelCountingType);
        auto header = Hydra::Other::Parser::parseDimacsCnfHeader(begin, end, line);
        return Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, header, line, modelCountingType);
    }
    //endregion

    /**
     * Mixdup
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] mixdup", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserMixdupFormula);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserMixdupFormula);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Or-60-10-7-UC-10
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] or-60-10-7-UC-10", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserOr_60_10_7_UC_10Formula);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserOr_60_10_7_UC_10Formula);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Sum.32
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] sum.32", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserSum_32Formula);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserSum_32Formula);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * No comment
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] no comment", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserNoCommentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserNoCommentInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Comments
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] comments", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserCommentsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserCommentsInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Letter case
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] letter case", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserLetterCaseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserLetterCaseInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Multiple-line clause
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] multiple-line clause", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserMultipleLineClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserMultipleLineClauseInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Empty lines
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] empty lines", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserEmptyLinesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserEmptyLinesInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Complementary literals (forbidden)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] complementary literals (forbidden)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserComplementaryLiteralsForbiddenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserComplementaryLiteralsForbiddenInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Duplicate literals
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] duplicate literals", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserDuplicateLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserDuplicateLiteralsInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * UNSAT
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] UNSAT", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserUnsatResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserUnsatInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Unit clauses
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] unit clauses", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserUnitClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserUnitClausesInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Tabular
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] tabular", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserTabularResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserTabularInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Size
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] size", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserSizeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserSizeInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    //region Problem line
    /**
     * Problem line (tabular)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (tabular)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLineTabularResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLineTabularInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (missing)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (missing)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLineMissingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLineMissingInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (position)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (position)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLinePositionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLinePositionInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (p)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (p)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLinePResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLinePInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (p space)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (p space)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLinePSpaceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLinePSpaceInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (cnf)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (cnf)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLineCnfResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLineCnfInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (cnf space)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (cnf space)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLineCnfSpaceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLineCnfSpaceInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (number of variables - negative)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (number of variables - negative)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLineNumberOfVariablesNegativeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLineNumberOfVariablesNegativeInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (number of variables - not number)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (number of variables - not number)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLineNumberOfVariablesNotNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLineNumberOfVariablesNotNumberInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (number of clauses - negative)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (number of clauses - negative)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLineNumberOfClausesNegativeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLineNumberOfClausesNegativeInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (number of clauses - not number)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (number of clauses - not number)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLineNumberOfClausesNotNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLineNumberOfClausesNotNumberInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (size - negative)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (size - negative)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLineSizeNegativeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLineSizeNegativeInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (size - not number)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (size - not number)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLineSizeNotNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLineSizeNotNumberInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (more parameters)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (more parameters)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLineMoreParametersResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLineMoreParametersInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (more parameters - number)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (more parameters - number)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLineMoreParametersNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLineMoreParametersNumberInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Problem line (less parameters)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] problem line (less parameters)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserProblemLineLessParametersResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserProblemLineLessParametersInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    //endregion

    //region Model counting header
    #if defined(BELLA_COMPILER)
    /**
     * Model counting header
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #elif defined(CARA_SOLVER)
    /**
     * Model counting header (no model counting header)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (no model counting header)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderNoModelCountingHeaderResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderNoModelCountingHeaderInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (missing)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (missing)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderMissingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderMissingInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (before problem line)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (before problem line)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderBeforeProblemLineResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderBeforeProblemLineInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (after problem line)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (after problem line)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderAfterProblemLineResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderAfterProblemLineInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (in the middle)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (in the middle)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderInTheMiddleResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderInTheMiddleInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (at the end)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (at the end)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderAtTheEndResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderAtTheEndInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (tabular)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (tabular)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderTabularResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderTabularInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (missing model counting type)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (missing model counting type)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderMissingModelCountingTypeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderMissingModelCountingTypeInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (missing model counting type, tabular)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (missing model counting type, tabular)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderMissingModelCountingTypeTabularResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderMissingModelCountingTypeTabularInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (unknown model counting type)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (unknown model counting type)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderUnknownModelCountingTypeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderUnknownModelCountingTypeInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (letter case)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (letter case)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderLetterCaseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderLetterCaseInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (t space)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (t space)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderTSpaceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderTSpaceInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (model counting type space)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (model counting type space)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderModelCountingTypeSpaceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderModelCountingTypeSpaceInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (more parameters)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (more parameters)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderMoreParametersResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderMoreParametersInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (more parameters - number)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (more parameters - number)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderMoreParametersNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderMoreParametersNumberInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (more headers - same)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (more headers - same)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderMoreHeadersSameResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderMoreHeadersSameInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Model counting header (more headers - different)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] model counting header (more headers - different)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserModelCountingHeaderMoreHeadersDifferentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserModelCountingHeaderMoreHeadersDifferentInput,
                                                                                       modelCountingType);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult, true, modelCountingType);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif
    //endregion

    /**
     * Clause (not number)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] clause (not number)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserClauseNotNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserClauseNotNumberInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Missing end of clause
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] missing end of clause", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserMissingEndOfClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserMissingEndOfClauseInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Empty clause
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] empty clause", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserEmptyClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserEmptyClauseInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Empty clause (complementary literals)
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] empty clause (complementary literals)", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserEmptyClauseComplementaryLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserEmptyClauseComplementaryLiteralsInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Unused variables
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] unused variables", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserUnusedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserUnusedVariablesInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * More variables
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] more variables", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserMoreVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserMoreVariablesInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Variable out of range
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] variable out of range", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserVariableOutOfRangeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserVariableOutOfRangeInput);
            formulaUniquePtr->printCurrentFormulaInDimacsCnfFormat(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Only clauses containing complementary literals
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] only clauses containing complementary literals", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserOnlyClausesContainingComplementaryLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserOnlyClausesContainingComplementaryLiteralsInput,
                                                                                       false);
            formulaUniquePtr->printFormulaRepresentationDebug(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Complementary literals
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] complementary literals", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserComplementaryLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserComplementaryLiteralsInput,
                                                                                       false);
            formulaUniquePtr->printFormulaRepresentationDebug(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Redundant literals
     */
    TEST_CASE("[Formula::Representation::Contagious::Parser] redundant literals", "[Formula::Representation::Contagious::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contagiousFormulaRepresentationParserRedundantLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contagiousFormulaRepresentationParserRedundantLiteralsInput,
                                                                                       false);
            formulaUniquePtr->printFormulaRepresentationDebug(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Formula::Representation::Contagious::Parser
