#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/external/unitTesting/Catch2/catch.hpp"
#include "HydraTest/formula/representation/contiguous/parser/ContiguousFormulaRepresentationParserTestFormula.hpp"
#include "HydraTest/formula/representation/contiguous/parser/ContiguousFormulaRepresentationParserTestInput.hpp"
#include "HydraTest/formula/representation/contiguous/parser/ContiguousFormulaRepresentationParserTestResult.hpp"

#include "Hydra/formula/representation/contiguous/ContiguousFormulaRepresentation.hpp"
#include "Hydra/formula/representation/contiguous/parser/cnf/ContiguousFormulaCnfParser.hpp"
#include "Hydra/other/parser/Parser.hpp"

#include "Cara/sharpSolver/enums/ModelCountingTypeEnum.hpp"

namespace HydraTest::Formula::Representation::Contiguous::Parser {

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
        return Hydra::Formula::Representation::Contiguous::Parser::Cnf::parseCnfFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, header, line,
                                                                                                                                                   forbidClausesContainingComplementaryLiterals);
    }

    FormulaRepresentationAbstractUniquePtrType parseFormula(const std::string& formulaString, ModelCountingTypeEnum& modelCountingType) {
        unsigned int line = 1;

        std::istringstream stringStream(formulaString);
        std::istreambuf_iterator<char> begin(stringStream);
        std::istreambuf_iterator<char> end;

        Hydra::Other::Parser::parseCommentLines(begin, end, line, modelCountingType);
        auto header = Hydra::Other::Parser::parseDimacsCnfHeader(begin, end, line);
        return Hydra::Formula::Representation::Contiguous::Parser::Cnf::parseCnfFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, header, line, modelCountingType);
    }
    //endregion

    /**
     * Mixdup
     */
    TEST_CASE("[Formula::Representation::Contiguous::Parser] mixdup", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserMixdupFormula);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserMixdupFormula);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] or-60-10-7-UC-10", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserOr_60_10_7_UC_10Formula);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserOr_60_10_7_UC_10Formula);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] sum.32", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserSum_32Formula);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserSum_32Formula);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] no comment", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserNoCommentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserNoCommentInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] comments", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserCommentsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserCommentsInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] letter case", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserLetterCaseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserLetterCaseInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] multiple-line clause", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserMultipleLineClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserMultipleLineClauseInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] empty lines", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserEmptyLinesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserEmptyLinesInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] complementary literals (forbidden)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserComplementaryLiteralsForbiddenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserComplementaryLiteralsForbiddenInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] duplicate literals", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserDuplicateLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserDuplicateLiteralsInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] UNSAT", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserUnsatResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserUnsatInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] unit clauses", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserUnitClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserUnitClausesInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] tabular", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserTabularResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserTabularInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] size", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserSizeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserSizeInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (tabular)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLineTabularResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLineTabularInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (missing)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLineMissingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLineMissingInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (position)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLinePositionResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLinePositionInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (p)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLinePResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLinePInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (p space)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLinePSpaceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLinePSpaceInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (cnf)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLineCnfResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLineCnfInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (cnf space)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLineCnfSpaceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLineCnfSpaceInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (number of variables - negative)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLineNumberOfVariablesNegativeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLineNumberOfVariablesNegativeInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (number of variables - not number)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLineNumberOfVariablesNotNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLineNumberOfVariablesNotNumberInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (number of clauses - negative)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLineNumberOfClausesNegativeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLineNumberOfClausesNegativeInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (number of clauses - not number)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLineNumberOfClausesNotNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLineNumberOfClausesNotNumberInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (size - negative)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLineSizeNegativeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLineSizeNegativeInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (size - not number)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLineSizeNotNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLineSizeNotNumberInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (more parameters)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLineMoreParametersResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLineMoreParametersInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (more parameters - number)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLineMoreParametersNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLineMoreParametersNumberInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] problem line (less parameters)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserProblemLineLessParametersResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserProblemLineLessParametersInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (no model counting header)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderNoModelCountingHeaderResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderNoModelCountingHeaderInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (missing)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderMissingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderMissingInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (before problem line)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderBeforeProblemLineResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderBeforeProblemLineInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (after problem line)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderAfterProblemLineResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderAfterProblemLineInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (in the middle)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderInTheMiddleResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderInTheMiddleInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (at the end)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderAtTheEndResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderAtTheEndInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (tabular)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderTabularResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderTabularInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (missing model counting type)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderMissingModelCountingTypeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderMissingModelCountingTypeInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (missing model counting type, tabular)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderMissingModelCountingTypeTabularResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderMissingModelCountingTypeTabularInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (unknown model counting type)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderUnknownModelCountingTypeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderUnknownModelCountingTypeInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (letter case)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderLetterCaseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderLetterCaseInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (t space)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderTSpaceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderTSpaceInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (model counting type space)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderModelCountingTypeSpaceResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderModelCountingTypeSpaceInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (more parameters)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderMoreParametersResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderMoreParametersInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (more parameters - number)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderMoreParametersNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderMoreParametersNumberInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (more headers - same)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderMoreHeadersSameResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderMoreHeadersSameInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] model counting header (more headers - different)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserModelCountingHeaderMoreHeadersDifferentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserModelCountingHeaderMoreHeadersDifferentInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] clause (not number)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserClauseNotNumberResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserClauseNotNumberInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] missing end of clause", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserMissingEndOfClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserMissingEndOfClauseInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] empty clause", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserEmptyClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserEmptyClauseInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] empty clause (complementary literals)", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserEmptyClauseComplementaryLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserEmptyClauseComplementaryLiteralsInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] unused variables", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserUnusedVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserUnusedVariablesInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] more variables", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserMoreVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserMoreVariablesInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] variable out of range", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserVariableOutOfRangeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserVariableOutOfRangeInput);
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] only clauses containing complementary literals", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserOnlyClausesContainingComplementaryLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserOnlyClausesContainingComplementaryLiteralsInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] complementary literals", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserComplementaryLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserComplementaryLiteralsInput,
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
    TEST_CASE("[Formula::Representation::Contiguous::Parser] redundant literals", "[Formula::Representation::Contiguous::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          contiguousFormulaRepresentationParserRedundantLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaUniquePtr = parseFormula(contiguousFormulaRepresentationParserRedundantLiteralsInput,
                                                                                       false);
            formulaUniquePtr->printFormulaRepresentationDebug(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Formula::Representation::Contiguous::Parser
