#pragma once

#include <string>

#include "HydraTest/circuit/parser/CircuitParserTestInput.hpp"

namespace HydraTest::Circuit::Parser {
    inline std::string circuitParserDnnfResult = circuitParserDnnfInput;

    inline std::string circuitParserPWDnnfResult = circuitParserPWDnnfInput;

    inline std::string circuitParserNWDnnfResult = circuitParserNWDnnfInput;

    inline std::string circuitParserWDnnf1Result = circuitParserWDnnf1Input;

    inline std::string circuitParserWDnnf2Result = circuitParserWDnnf2Input;

    inline std::string circuitParserDDnnfResult = circuitParserDDnnfInput;

    inline std::string circuitParserSDDnnfResult = circuitParserSDDnnfInput;

    inline std::string circuitParserKromCDBdmcResult = circuitParserKromCDBdmcInput;

    inline std::string circuitParserKromCSDBdmcResult = circuitParserKromCSDBdmcInput;

    inline std::string circuitParserRenHCDBdmcResult = circuitParserRenHCDBdmcInput;

    inline std::string circuitParserRenHCSDBdmcResult = circuitParserRenHCSDBdmcInput;

    inline std::string circuitParserNoCommentsResult = "c -------------------\n"
                                                       "c ------ Bella ------\n"
                                                       "c -------------------\n"
                                                       "c d-DNNF\n"
                                                       "c\n"
                                                       "nnf 21 14 6\n"
                                                       "c literal leaf: 12\n"
                                                       "c constant leaf: 2\n"
                                                       "c AND inner node: 5\n"
                                                       "c binary OR inner node: 2\n"
                                                       "O 0 0\n"
                                                       "A 0\n"
                                                       "L 1\n"
                                                       "L -1\n"
                                                       "L 2\n"
                                                       "L -2\n"
                                                       "L 3\n"
                                                       "L -3\n"
                                                       "L 4\n"
                                                       "L -4\n"
                                                       "L 5\n"
                                                       "L -5\n"
                                                       "L 6\n"
                                                       "L -6\n"
                                                       "A 2 2 4\n"
                                                       "A 2 5 6\n"
                                                       "O 2 2 14 15\n"
                                                       "A 2 8 10\n"
                                                       "A 2 11 12\n"
                                                       "O 5 2 17 18\n"
                                                       "A 2 16 19\n";

    inline std::string circuitParserLetterCaseResult = "c -------------------\n"
                                                       "c ------ Bella ------\n"
                                                       "c -------------------\n"
                                                       "c d-DNNF\n"
                                                       "c\n"
                                                       "nnf 21 14 6\n"
                                                       "c literal leaf: 12\n"
                                                       "c constant leaf: 2\n"
                                                       "c AND inner node: 5\n"
                                                       "c binary OR inner node: 2\n"
                                                       "O 0 0\n"
                                                       "A 0\n"
                                                       "L 1\n"
                                                       "L -1\n"
                                                       "L 2\n"
                                                       "L -2\n"
                                                       "L 3\n"
                                                       "L -3\n"
                                                       "L 4\n"
                                                       "L -4\n"
                                                       "L 5\n"
                                                       "L -5\n"
                                                       "L 6\n"
                                                       "L -6\n"
                                                       "A 2 2 4\n"
                                                       "A 2 5 6\n"
                                                       "O 2 2 14 15\n"
                                                       "A 2 8 10\n"
                                                       "A 2 11 12\n"
                                                       "O 5 2 17 18\n"
                                                       "A 2 16 19\n";

    inline std::string circuitParserWhitespacesResult = "c -------------------\n"
                                                        "c ------ Bella ------\n"
                                                        "c -------------------\n"
                                                        "c d-DNNF\n"
                                                        "c\n"
                                                        "nnf 21 14 6\n"
                                                        "c literal leaf: 12\n"
                                                        "c constant leaf: 2\n"
                                                        "c AND inner node: 5\n"
                                                        "c binary OR inner node: 2\n"
                                                        "O 0 0\n"
                                                        "A 0\n"
                                                        "L 1\n"
                                                        "L -1\n"
                                                        "L 2\n"
                                                        "L -2\n"
                                                        "L 3\n"
                                                        "L -3\n"
                                                        "L 4\n"
                                                        "L -4\n"
                                                        "L 5\n"
                                                        "L -5\n"
                                                        "L 6\n"
                                                        "L -6\n"
                                                        "A 2 2 4\n"
                                                        "A 2 5 6\n"
                                                        "O 2 2 14 15\n"
                                                        "A 2 8 10\n"
                                                        "A 2 11 12\n"
                                                        "O 5 2 17 18\n"
                                                        "A 2 16 19\n";

    inline std::string circuitParserMissingNnfHeaderResult = "Invalid line 1 (O...) has occurred before the DIMACS NNF header!\n";

    inline std::string circuitParserMissingNnfHeader2Result = "Invalid line 1 (O...) has occurred before the DIMACS NNF header!\n";

    inline std::string circuitParserInvalidNnfHeaderResult = "The character (f) in the DIMACS NNF header on line 1 is invalid!\n";

    inline std::string circuitParserInvalidNnfHeader2Result = "A whitespace (excluding the new line symbol (\\n)) after the string 'nnf' in the DIMACS NNF header is expected, but another symbol (\\n) is detected on line 1!\n";

    inline std::string circuitParserInvalidNnfHeader3Result = "The DIMACS NNF header on line 1 does not have the correct number of parameters (2)!\n";

    inline std::string circuitParserInvalidNnfHeader4Result = "The DIMACS NNF header on line 1 does not have the correct number of parameters (5)!\n";

    inline std::string circuitParserInvalidNnfHeader5Result = "A digit is expected, but another symbol (a) is detected on line 1!\n";

    inline std::string circuitParserInvalidNnfHeader6Result = "A digit is expected, but another symbol (-) is detected on line 1!\n";

    inline std::string circuitParserInvalidNnfHeader7Result = "Invalid line 1 (L...) has occurred before the DIMACS NNF header!\n";

    inline std::string circuitParserInvalidNnfHeader8Result = "A whitespace (excluding the new line symbol (\\n)) after the string 'nnf' in the DIMACS NNF header is expected, but another symbol (2) is detected on line 1!\n";

    inline std::string circuitParserInvalidLiteralLeafResult = "A digit is expected, but another symbol (a) is detected on line 2!\n";

    inline std::string circuitParserInvalidLiteralLeaf2Result = "A digit is expected, but another symbol (a) is detected on line 2!\n";

    inline std::string circuitParserInvalidLiteralLeaf3Result = "A whitespace (excluding \\n) is expected, but another symbol (\\n) is detected on line 2!\n";

    inline std::string circuitParserInvalidLiteralLeaf4Result = "A digit is expected, but another symbol ('space') is detected on line 2!\n";

    inline std::string circuitParserInvalidLiteralLeaf5Result = "A digit is expected, but another symbol (\\t) is detected on line 2!\n";

    inline std::string circuitParserInvalidLiteralLeaf6Result = "A new line (\\n) is expected, but another symbol (2) is detected on line 2!\n";

    inline std::string circuitParserInvalidLiteralLeaf7Result = "A whitespace (excluding \\n) is expected, but another symbol (1) is detected on line 2!\n";

    inline std::string circuitParserInvalidLiteralLeaf8Result = "A whitespace (excluding \\n) is expected, but another symbol (-) is detected on line 2!\n";

    inline std::string circuitParserInvalidLiteralLeaf9Result = "The literal leaf on line 2 is invalid!\n";

    inline std::string circuitParserInvalidAndInnerNodeResult = "A whitespace (excluding \\n) is expected, but another symbol (\\n) is detected on line 3!\n";

    inline std::string circuitParserInvalidAndInnerNode2Result = "A digit is expected, but another symbol (-) is detected on line 3!\n";

    inline std::string circuitParserInvalidAndInnerNode3Result = "A digit is expected, but another symbol (a) is detected on line 3!\n";

    inline std::string circuitParserInvalidAndInnerNode4Result = "The AND node on line 3 has an invalid number of children!\n";

    inline std::string circuitParserInvalidAndInnerNode5Result = "The AND node on line 4 has an invalid number of children!\n";

    inline std::string circuitParserInvalidAndInnerNode6Result = "A digit is expected, but another symbol (a) is detected on line 3!\n";

    inline std::string circuitParserInvalidAndInnerNode7Result = "The node's identifier (1) does not exist in the circuit!\n";

    inline std::string circuitParserInvalidAndInnerNode8Result = "A digit is expected, but another symbol (-) is detected on line 3!\n";

    inline std::string circuitParserInvalidAndInnerNode9Result = "A whitespace (excluding \\n) is expected, but another symbol (1) is detected on line 3!\n";

    inline std::string circuitParserInvalidAndInnerNode10Result = "The AND node on line 3 is invalid!\n";

    inline std::string circuitParserInvalidAndInnerNode11Result = "A new line (\\n) is expected, but another symbol (1) is detected on line 3!\n";

    inline std::string circuitParserInvalidOrInnerNodeResult = "A whitespace (excluding \\n) is expected, but another symbol (\\n) is detected on line 3!\n";

    inline std::string circuitParserInvalidOrInnerNode2Result = "A digit is expected, but another symbol (-) is detected on line 3!\n";

    inline std::string circuitParserInvalidOrInnerNode3Result = "A digit is expected, but another symbol (a) is detected on line 3!\n";

    inline std::string circuitParserInvalidOrInnerNode4Result = "The OR node on line 3 is invalid!\n";

    inline std::string circuitParserInvalidOrInnerNode5Result = "A number is expected, but the end of the stream is detected!\n";

    inline std::string circuitParserInvalidOrInnerNode6Result = "A digit is expected, but another symbol (a) is detected on line 3!\n";

    inline std::string circuitParserInvalidOrInnerNode7Result = "A digit is expected, but another symbol (-) is detected on line 3!\n";

    inline std::string circuitParserInvalidOrInnerNode8Result = "A new line (\\n) is expected, but another symbol (1) is detected on line 3!\n";

    inline std::string circuitParserInvalidOrInnerNode9Result = "A whitespace (excluding \\n) is expected, but another symbol (0) is detected on line 3!\n";

    inline std::string circuitParserInvalidOrInnerNode10Result = "The OR node on line 3 has an invalid number of children!\n";

    inline std::string circuitParserInvalidOrInnerNode11Result = "The OR node on line 3 has an invalid number of children!\n";

    inline std::string circuitParserInvalidOrInnerNode12Result = "A digit is expected, but another symbol (-) is detected on line 3!\n";

    inline std::string circuitParserInvalidOrInnerNode13Result = "A digit is expected, but another symbol (a) is detected on line 3!\n";

    inline std::string circuitParserInvalidOrInnerNode14Result = "The node's identifier (1) does not exist in the circuit!\n";

    inline std::string circuitParserInvalidKromCLeafResult = "A digit is expected, but another symbol (a) is detected on line 2!\n";

    inline std::string circuitParserInvalidKromCLeaf2Result = "A digit is expected, but another symbol (-) is detected on line 2!\n";

    inline std::string circuitParserInvalidKromCLeaf3Result = "A whitespace (excluding \\n) is expected, but another symbol (3) is detected on line 2!\n";

    inline std::string circuitParserInvalidKromCLeaf4Result = "The Krom-C leaf on line 2 is invalid!\n";

    inline std::string circuitParserInvalidKromCLeaf5Result = "A whitespace (excluding \\n) is expected, but another symbol (\\n) is detected on line 2!\n";

    inline std::string circuitParserInvalidKromCLeaf6Result = "A digit is expected, but another symbol (\\n) is detected on line 2!\n";

    inline std::string circuitParserInvalidKromCLeaf7Result = "A digit is expected, but another symbol (a) is detected on line 2!\n";

    inline std::string circuitParserInvalidKromCLeaf8Result = "A digit is expected, but another symbol (-) is detected on line 2!\n";

    inline std::string circuitParserInvalidKromCLeaf9Result = "The Krom-C leaf on line 2 has an invalid number of variables!\n";

    inline std::string circuitParserInvalidKromCLeaf10Result = "The Krom-C leaf on line 2 has an invalid number of variables!\n";

    inline std::string circuitParserInvalidKromCLeaf11Result = "A digit is expected, but another symbol (a) is detected on line 2!\n";

    inline std::string circuitParserInvalidKromCLeaf12Result = "A digit is expected, but another symbol (-) is detected on line 2!\n";

    inline std::string circuitParserInvalidKromCLeaf13Result = "The variable (2) is mentioned multiple times on line 2 in the mapping!\n";

    inline std::string circuitParserInvalidKromCLeaf14Result = "A digit is expected, but another symbol (a) is detected on line 3!\n";

    inline std::string circuitParserInvalidKromCLeaf15Result = "A digit is expected, but another symbol (-) is detected on line 3!\n";

    inline std::string circuitParserInvalidKromCLeaf16Result = "The DIMACS CNF header on line 3 does not have the correct number of parameters!\n";

    inline std::string circuitParserInvalidKromCLeaf17Result = "The DIMACS CNF header on line 3 does not have the correct number of parameters!\n";

    inline std::string circuitParserInvalidKromCLeaf18Result = "A digit is expected, but another symbol (a) is detected on line 3!\n";

    inline std::string circuitParserInvalidKromCLeaf19Result = "A digit is expected, but another symbol (-) is detected on line 3!\n";

    inline std::string circuitParserInvalidKromCLeaf20Result = "Invalid line 5 (-...) has occurred!\n";

    inline std::string circuitParserInvalidKromCLeaf21Result = "A clause is expected, but the end of the stream is detected!\n";

    inline std::string circuitParserInvalidKromCLeaf22Result = "A digit is expected, but another symbol (a) is detected on line 4!\n";

    inline std::string circuitParserInvalidKromCLeaf23Result = "The character (n) in the DIMACS CNF header on line 3 is invalid!\n";

    inline std::string circuitParserInvalidKromCLeaf24Result = "A whitespace (excluding the new line symbol (\\n)) after the string 'cnf' in the DIMACS CNF header is expected, but another symbol (2) is detected on line 3!\n";

    inline std::string circuitParserInvalidRenHCLeafResult = "A digit is expected, but another symbol (a) is detected on line 2!\n";

    inline std::string circuitParserInvalidRenHCLeaf2Result = "A digit is expected, but another symbol (-) is detected on line 2!\n";

    inline std::string circuitParserInvalidRenHCLeaf3Result = "A whitespace (excluding \\n) is expected, but another symbol (4) is detected on line 2!\n";

    inline std::string circuitParserInvalidRenHCLeaf4Result = "The renH-C leaf on line 2 is invalid!\n";

    inline std::string circuitParserInvalidRenHCLeaf5Result = "A whitespace (excluding \\n) is expected, but another symbol (\\n) is detected on line 2!\n";

    inline std::string circuitParserInvalidRenHCLeaf6Result = "A digit is expected, but another symbol (\\n) is detected on line 2!\n";

    inline std::string circuitParserInvalidRenHCLeaf7Result = "A digit is expected, but another symbol (a) is detected on line 2!\n";

    inline std::string circuitParserInvalidRenHCLeaf8Result = "A digit is expected, but another symbol (-) is detected on line 2!\n";

    inline std::string circuitParserInvalidRenHCLeaf9Result = "The renH-C leaf on line 2 has an invalid number of variables!\n";

    inline std::string circuitParserInvalidRenHCLeaf10Result = "The renH-C leaf on line 2 has an invalid number of variables!\n";

    inline std::string circuitParserInvalidRenHCLeaf11Result = "A digit is expected, but another symbol (a) is detected on line 2!\n";

    inline std::string circuitParserInvalidRenHCLeaf12Result = "The variable (2) is mentioned multiple times on line 2 in the mapping!\n";

    inline std::string circuitParserInvalidRenHCLeaf13Result = "The variable (2) is mentioned multiple times on line 2 in the mapping!\n";

    inline std::string circuitParserInvalidRenHCLeaf14Result = "A digit is expected, but another symbol (a) is detected on line 3!\n";

    inline std::string circuitParserInvalidRenHCLeaf15Result = "A digit is expected, but another symbol (-) is detected on line 3!\n";

    inline std::string circuitParserInvalidRenHCLeaf16Result = "A digit is expected, but another symbol (a) is detected on line 3!\n";

    inline std::string circuitParserInvalidRenHCLeaf17Result = "A digit is expected, but another symbol (-) is detected on line 3!\n";

    inline std::string circuitParserInvalidRenHCLeaf18Result = "The DIMACS CNF header on line 3 does not have the correct number of parameters!\n";

    inline std::string circuitParserInvalidRenHCLeaf19Result = "The DIMACS CNF header on line 3 does not have the correct number of parameters!\n";

    inline std::string circuitParserInvalidRenHCLeaf20Result = "Invalid line 6 (1...) has occurred!\n";

    inline std::string circuitParserInvalidRenHCLeaf21Result = "A clause is expected, but the end of the stream is detected!\n";

    inline std::string circuitParserInvalidRenHCLeaf22Result = "A digit is expected, but another symbol (a) is detected on line 4!\n";

    inline std::string circuitParserInvalidRenHCLeaf23Result = "The character (n) in the DIMACS CNF header on line 3 is invalid!\n";

    inline std::string circuitParserInvalidRenHCLeaf24Result = "A whitespace (excluding the new line symbol (\\n)) after the string 'cnf' in the DIMACS CNF header is expected, but another symbol (3) is detected on line 3!\n";

    inline std::string circuitParserInvalidLineResult = "Invalid line 6 (X...) has occurred!\n";

    inline std::string circuitParserInvalidLine2Result = "Invalid line 6 (y...) has occurred!\n";

    inline std::string circuitParserInvalidIndexResult = "The node's identifier (15) does not exist in the circuit!\n";

    inline std::string circuitParserInvalidIndex2Result = "The node's identifier (18) does not exist in the circuit!\n";

    inline std::string circuitParserEmptyResult = "The DIMACS NNF header was not found!\n";
}   // namespace HydraTest::Circuit::Parser
