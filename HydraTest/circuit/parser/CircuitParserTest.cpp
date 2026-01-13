#include <iterator>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/circuit/parser/CircuitParserTestInput.hpp"
#include "HydraTest/circuit/parser/CircuitParserTestResult.hpp"

#include "Hydra/circuit/Circuit.hpp"
#include "Hydra/circuit/parser/CircuitParser.hpp"

namespace HydraTest::Circuit::Parser {

    //region Types
    using VarT = char8_t;
    using LiteralT = char8_t;
    //endregion

    //region Functions
    void parseCircuit(const std::string& circuitString, std::stringstream& actualResult) {
        try {
            unsigned int line = 1;

            std::istringstream stringStream(circuitString);
            std::istreambuf_iterator<char> begin(stringStream);
            std::istreambuf_iterator<char> end;

            auto header = Hydra::Circuit::Parser::parseDimacsNnfHeader(begin, end, line);
            auto circuit = Hydra::Circuit::Parser::parseCircuit<VarT, LiteralT, std::istreambuf_iterator<char>>(begin, end, header, line);
            circuit.printCircuit(actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }
    }
    //endregion

    #if defined(BELLA_COMPILER)
    /**
     * DNNF
     */
    TEST_CASE("[Circuit::Parser] DNNF", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserDnnfResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserDnnfInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * pwDNNF
     */
    TEST_CASE("[Circuit::Parser] pwDNNF", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserPWDnnfResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserPWDnnfInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * nwDNNF
     */
    TEST_CASE("[Circuit::Parser] nwDNNF", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserNWDnnfResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserNWDnnfInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * wDNNF 1
     */
    TEST_CASE("[Circuit::Parser] wDNNF 1", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserWDnnf1Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserWDnnf1Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * wDNNF 2
     */
    TEST_CASE("[Circuit::Parser] wDNNF 2", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserWDnnf2Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserWDnnf2Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * d-DNNF
     */
    TEST_CASE("[Circuit::Parser] d-DNNF", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserDDnnfResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserDDnnfInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sd-DNNF
     */
    TEST_CASE("[Circuit::Parser] sd-DNNF", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserSDDnnfResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserSDDnnfInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {Krom-C}-d-BDMC
     */
    TEST_CASE("[Circuit::Parser] {Krom-C}-d-BDMC", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserKromCDBdmcResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserKromCDBdmcInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {Krom-C}-sd-BDMC
     */
    TEST_CASE("[Circuit::Parser] {Krom-C}-sd-BDMC", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserKromCSDBdmcResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserKromCSDBdmcInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {renH-C}-d-BDMC
     */
    TEST_CASE("[Circuit::Parser] {renH-C}-d-BDMC", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserRenHCDBdmcResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserRenHCDBdmcInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * {renH-C}-sd-BDMC
     */
    TEST_CASE("[Circuit::Parser] {renH-C}-sd-BDMC", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserRenHCSDBdmcResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserRenHCSDBdmcInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * No comments
     */
    TEST_CASE("[Circuit::Parser] no comments", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserNoCommentsResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserNoCommentsInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Letter case
     */
    TEST_CASE("[Circuit::Parser] letter case", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserLetterCaseResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserLetterCaseInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Whitespaces
     */
    TEST_CASE("[Circuit::Parser] whitespaces", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserWhitespacesResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserWhitespacesInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Missing NNF header
     */
    TEST_CASE("[Circuit::Parser] missing NNF header", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserMissingNnfHeaderResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserMissingNnfHeaderInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Missing NNF header 2
     */
    TEST_CASE("[Circuit::Parser] missing NNF header 2", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserMissingNnfHeader2Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserMissingNnfHeader2Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid NNF header
     */
    TEST_CASE("[Circuit::Parser] invalid NNF header", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidNnfHeaderResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidNnfHeaderInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid NNF header 2
     */
    TEST_CASE("[Circuit::Parser] invalid NNF header 2", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidNnfHeader2Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidNnfHeader2Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid NNF header 3
     */
    TEST_CASE("[Circuit::Parser] invalid NNF header 3", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidNnfHeader3Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidNnfHeader3Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid NNF header 4
     */
    TEST_CASE("[Circuit::Parser] invalid NNF header 4", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidNnfHeader4Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidNnfHeader4Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid NNF header 5
     */
    TEST_CASE("[Circuit::Parser] invalid NNF header 5", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidNnfHeader5Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidNnfHeader5Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid NNF header 6
     */
    TEST_CASE("[Circuit::Parser] invalid NNF header 6", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidNnfHeader6Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidNnfHeader6Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid NNF header 7
     */
    TEST_CASE("[Circuit::Parser] invalid NNF header 7", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidNnfHeader7Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidNnfHeader7Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid NNF header 8
     */
    TEST_CASE("[Circuit::Parser] invalid NNF header 8", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidNnfHeader8Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidNnfHeader8Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid literal leaf
     */
    TEST_CASE("[Circuit::Parser] invalid literal leaf", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidLiteralLeafResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidLiteralLeafInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid literal leaf 2
     */
    TEST_CASE("[Circuit::Parser] invalid literal leaf 2", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidLiteralLeaf2Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidLiteralLeaf2Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid literal leaf 3
     */
    TEST_CASE("[Circuit::Parser] invalid literal leaf 3", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidLiteralLeaf3Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidLiteralLeaf3Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid literal leaf 4
     */
    TEST_CASE("[Circuit::Parser] invalid literal leaf 4", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidLiteralLeaf4Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidLiteralLeaf4Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid literal leaf 5
     */
    TEST_CASE("[Circuit::Parser] invalid literal leaf 5", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidLiteralLeaf5Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidLiteralLeaf5Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid literal leaf 6
     */
    TEST_CASE("[Circuit::Parser] invalid literal leaf 6", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidLiteralLeaf6Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidLiteralLeaf6Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid literal leaf 7
     */
    TEST_CASE("[Circuit::Parser] invalid literal leaf 7", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidLiteralLeaf7Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidLiteralLeaf7Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid literal leaf 8
     */
    TEST_CASE("[Circuit::Parser] invalid literal leaf 8", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidLiteralLeaf8Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidLiteralLeaf8Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid literal leaf 9
     */
    TEST_CASE("[Circuit::Parser] invalid literal leaf 9", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidLiteralLeaf9Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidLiteralLeaf9Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid AND inner node
     */
    TEST_CASE("[Circuit::Parser] invalid AND inner node", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidAndInnerNodeResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidAndInnerNodeInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid AND inner node 2
     */
    TEST_CASE("[Circuit::Parser] invalid AND inner node 2", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidAndInnerNode2Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidAndInnerNode2Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid AND inner node 3
     */
    TEST_CASE("[Circuit::Parser] invalid AND inner node 3", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidAndInnerNode3Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidAndInnerNode3Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid AND inner node 4
     */
    TEST_CASE("[Circuit::Parser] invalid AND inner node 4", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidAndInnerNode4Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidAndInnerNode4Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid AND inner node 5
     */
    TEST_CASE("[Circuit::Parser] invalid AND inner node 5", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidAndInnerNode5Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidAndInnerNode5Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid AND inner node 6
     */
    TEST_CASE("[Circuit::Parser] invalid AND inner node 6", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidAndInnerNode6Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidAndInnerNode6Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid AND inner node 7
     */
    TEST_CASE("[Circuit::Parser] invalid AND inner node 7", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidAndInnerNode7Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidAndInnerNode7Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid AND inner node 8
     */
    TEST_CASE("[Circuit::Parser] invalid AND inner node 8", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidAndInnerNode8Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidAndInnerNode8Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid AND inner node 9
     */
    TEST_CASE("[Circuit::Parser] invalid AND inner node 9", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidAndInnerNode9Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidAndInnerNode9Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid AND inner node 10
     */
    TEST_CASE("[Circuit::Parser] invalid AND inner node 10", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidAndInnerNode10Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidAndInnerNode10Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid AND inner node 11
     */
    TEST_CASE("[Circuit::Parser] invalid AND inner node 11", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidAndInnerNode11Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidAndInnerNode11Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNodeResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNodeInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node 2
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node 2", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNode2Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNode2Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node 3
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node 3", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNode3Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNode3Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node 4
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node 4", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNode4Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNode4Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node 5
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node 5", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNode5Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNode5Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node 6
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node 6", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNode6Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNode6Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node 7
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node 7", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNode7Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNode7Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node 8
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node 8", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNode8Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNode8Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node 9
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node 9", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNode9Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNode9Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node 10
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node 10", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNode10Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNode10Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node 11
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node 11", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNode11Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNode11Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node 12
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node 12", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNode12Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNode12Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node 13
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node 13", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNode13Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNode13Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid OR inner node 14
     */
    TEST_CASE("[Circuit::Parser] invalid OR inner node 14", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidOrInnerNode14Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidOrInnerNode14Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeafResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeafInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 2
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 2", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf2Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf2Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 3
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 3", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf3Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf3Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 4
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 4", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf4Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf4Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 5
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 5", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf5Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf5Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 6
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 6", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf6Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf6Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 7
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 7", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf7Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf7Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 8
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 8", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf8Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf8Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 9
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 9", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf9Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf9Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 10
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 10", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf10Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf10Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 11
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 11", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf11Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf11Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 12
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 12", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf12Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf12Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 13
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 13", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf13Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf13Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 14
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 14", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf14Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf14Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 15
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 15", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf15Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf15Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 16
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 16", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf16Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf16Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 17
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 17", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf17Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf17Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 18
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 18", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf18Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf18Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 19
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 19", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf19Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf19Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 20
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 20", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf20Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf20Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 21
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 21", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf21Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf21Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 22
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 22", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf22Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf22Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 23
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 23", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf23Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf23Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid Krom-C leaf 24
     */
    TEST_CASE("[Circuit::Parser] invalid Krom-C leaf 24", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidKromCLeaf24Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidKromCLeaf24Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeafResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeafInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 2
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 2", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf2Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf2Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 3
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 3", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf3Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf3Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 4
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 4", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf4Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf4Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 5
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 5", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf5Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf5Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 6
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 6", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf6Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf6Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 7
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 7", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf7Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf7Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 8
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 8", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf8Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf8Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 9
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 9", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf9Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf9Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 10
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 10", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf10Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf10Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 11
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 11", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf11Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf11Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 12
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 12", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf12Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf12Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 13
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 13", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf13Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf13Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 14
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 14", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf14Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf14Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 15
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 15", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf15Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf15Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 16
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 16", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf16Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf16Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 17
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 17", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf17Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf17Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 18
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 18", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf18Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf18Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 19
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 19", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf19Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf19Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 20
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 20", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf20Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf20Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 21
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 21", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf21Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf21Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 22
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 22", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf22Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf22Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 23
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 23", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf23Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf23Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid renH-C leaf 24
     */
    TEST_CASE("[Circuit::Parser] invalid renH-C leaf 24", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidRenHCLeaf24Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidRenHCLeaf24Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid line
     */
    TEST_CASE("[Circuit::Parser] invalid line", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidLineResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidLineInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid line 2
     */
    TEST_CASE("[Circuit::Parser] invalid line 2", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidLine2Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidLine2Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid index
     */
    TEST_CASE("[Circuit::Parser] invalid index", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidIndexResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidIndexInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Invalid index 2
     */
    TEST_CASE("[Circuit::Parser] invalid index 2", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserInvalidIndex2Result);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserInvalidIndex2Input, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Empty
     */
    TEST_CASE("[Circuit::Parser] empty", "[Circuit::Parser]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          circuitParserEmptyResult);
        std::stringstream& actualResult = test.getStringStream();

        parseCircuit(circuitParserEmptyInput, actualResult);

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif
}   // namespace HydraTest::Circuit::Parser
