#pragma once

#include <string>

namespace HydraTest::Circuit::Parser {
    inline std::string circuitParserDnnfInput = "c -------------------\n"
                                                "c ------ Bella ------\n"
                                                "c -------------------\n"
                                                "c DNNF\n"
                                                "c\n"
                                                "nnf 7 2 2\n"
                                                "c literal leaf: 4\n"
                                                "c constant leaf: 2\n"
                                                "c OR inner node: 1\n"
                                                "O 0 0\n"
                                                "A 0\n"
                                                "L 1\n"
                                                "L -1\n"
                                                "L 2\n"
                                                "L -2\n"
                                                "O 0 2 2 5\n";

    inline std::string circuitParserPWDnnfInput = "c -------------------\n"
                                                  "c ------ Bella ------\n"
                                                  "c -------------------\n"
                                                  "c pwDNNF\n"
                                                  "c\n"
                                                  "nnf 21 17 6\n"
                                                  "c literal leaf: 12\n"
                                                  "c constant leaf: 2\n"
                                                  "c AND inner node: 3\n"
                                                  "c OR inner node: 3\n"
                                                  "c binary OR inner node: 1\n"
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
                                                  "O 0 3 2 4 8\n"
                                                  "O 0 3 2 4 10\n"
                                                  "O 0 2 4 12\n"
                                                  "A 2 6 14\n"
                                                  "A 2 2 7\n"
                                                  "O 3 2 17 18\n"
                                                  "P 3 15 16 19\n";

    inline std::string circuitParserNWDnnfInput = "c -------------------\n"
                                                  "c ------ Bella ------\n"
                                                  "c -------------------\n"
                                                  "c nwDNNF\n"
                                                  "c\n"
                                                  "nnf 13 10 3\n"
                                                  "c literal leaf: 6\n"
                                                  "c constant leaf: 2\n"
                                                  "c AND inner node: 3\n"
                                                  "c OR inner node: 1\n"
                                                  "c binary OR inner node: 1\n"
                                                  "O 0 0\n"
                                                  "A 0\n"
                                                  "L 1\n"
                                                  "L -1\n"
                                                  "L 2\n"
                                                  "L -2\n"
                                                  "L 3\n"
                                                  "L -3\n"
                                                  "O 0 2 2 5\n"
                                                  "A 2 1 6\n"
                                                  "A 2 5 7\n"
                                                  "O 3 2 9 10\n"
                                                  "N 2 8 11\n";

    inline std::string circuitParserWDnnf1Input = "c -------------------\n"
                                                  "c ------ Bella ------\n"
                                                  "c -------------------\n"
                                                  "c wDNNF\n"
                                                  "c\n"
                                                  "nnf 8 5 2\n"
                                                  "c literal leaf: 4\n"
                                                  "c constant leaf: 2\n"
                                                  "c AND inner node: 1\n"
                                                  "c OR inner node: 1\n"
                                                  "O 0 0\n"
                                                  "A 0\n"
                                                  "L 1\n"
                                                  "L -1\n"
                                                  "L 2\n"
                                                  "L -2\n"
                                                  "O 0 2 2 5\n"
                                                  "B 3 2 5 6\n";

    inline std::string circuitParserWDnnf2Input = "c -------------------\n"
                                                  "c ------ Bella ------\n"
                                                  "c -------------------\n"
                                                  "c wDNNF\n"
                                                  "c\n"
                                                  "nnf 15 14 3\n"
                                                  "c literal leaf: 6\n"
                                                  "c constant leaf: 2\n"
                                                  "c AND inner node: 4\n"
                                                  "c OR inner node: 2\n"
                                                  "c binary OR inner node: 1\n"
                                                  "O 0 0\n"
                                                  "A 0\n"
                                                  "L 1\n"
                                                  "L -1\n"
                                                  "L 2\n"
                                                  "L -2\n"
                                                  "L 3\n"
                                                  "L -3\n"
                                                  "O 0 2 2 5\n"
                                                  "P 2 2 8\n"
                                                  "O 0 2 3 4\n"
                                                  "N 2 3 10\n"
                                                  "A 2 6 9\n"
                                                  "A 2 7 11\n"
                                                  "O 3 2 12 13\n";

    inline std::string circuitParserDDnnfInput = "c -------------------\n"
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

    inline std::string circuitParserSDDnnfInput = "c -------------------\n"
                                                  "c ------ Bella ------\n"
                                                  "c -------------------\n"
                                                  "c sd-DNNF\n"
                                                  "c\n"
                                                  "nnf 29 30 6\n"
                                                  "c literal leaf: 12\n"
                                                  "c constant leaf: 2\n"
                                                  "c AND inner node: 9\n"
                                                  "c binary OR inner node: 6\n"
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
                                                  "O 3 2 6 7\n"
                                                  "A 2 2 14\n"
                                                  "O 1 2 2 3\n"
                                                  "A 2 6 16\n"
                                                  "A 2 4 15\n"
                                                  "A 2 5 17\n"
                                                  "O 2 2 18 19\n"
                                                  "O 6 2 12 13\n"
                                                  "A 2 8 21\n"
                                                  "O 4 2 8 9\n"
                                                  "A 2 12 23\n"
                                                  "A 2 10 22\n"
                                                  "A 2 11 24\n"
                                                  "O 5 2 25 26\n"
                                                  "A 2 20 27\n";

    inline std::string circuitParserKromCDBdmcInput = "c -------------------\n"
                                                      "c ------ Bella ------\n"
                                                      "c -------------------\n"
                                                      "c {Krom-C}-d-BDMC\n"
                                                      "c\n"
                                                      "nnf 15 6 4 17\n"
                                                      "c literal leaf: 8\n"
                                                      "c constant leaf: 2\n"
                                                      "c Krom-C leaf: 2\n"
                                                      "c AND inner node: 2\n"
                                                      "c binary OR inner node: 1\n"
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
                                                      "K 3 2 2 3\n"
                                                      "p cnf 2 2\n"
                                                      "1 -2 0\n"
                                                      "-1 2 0\n"
                                                      "K 3 2 1 2\n"
                                                      "p cnf 2 2\n"
                                                      "1 0\n"
                                                      "-1 2 0\n"
                                                      "A 2 8 10\n"
                                                      "A 2 9 11\n"
                                                      "O 4 2 12 13\n";

    inline std::string circuitParserKromCSDBdmcInput = "c -------------------\n"
                                                       "c ------ Bella ------\n"
                                                       "c -------------------\n"
                                                       "c {Krom-C}-sd-BDMC\n"
                                                       "c\n"
                                                       "nnf 19 14 4 25\n"
                                                       "c literal leaf: 8\n"
                                                       "c constant leaf: 2\n"
                                                       "c Krom-C leaf: 2\n"
                                                       "c AND inner node: 4\n"
                                                       "c binary OR inner node: 3\n"
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
                                                       "K 3 2 2 3\n"
                                                       "p cnf 2 2\n"
                                                       "1 -2 0\n"
                                                       "-1 2 0\n"
                                                       "K 3 2 1 2\n"
                                                       "p cnf 2 2\n"
                                                       "1 0\n"
                                                       "-1 2 0\n"
                                                       "O 1 2 2 3\n"
                                                       "A 2 10 12\n"
                                                       "O 3 2 6 7\n"
                                                       "A 2 11 14\n"
                                                       "A 2 8 13\n"
                                                       "A 2 9 15\n"
                                                       "O 4 2 16 17\n";

    inline std::string circuitParserRenHCDBdmcInput = "c -------------------\n"
                                                      "c ------ Bella ------\n"
                                                      "c -------------------\n"
                                                      "c {renH-C}-d-BDMC\n"
                                                      "c\n"
                                                      "nnf 17 6 5 21\n"
                                                      "c literal leaf: 10\n"
                                                      "c constant leaf: 2\n"
                                                      "c renH-C leaf: 2\n"
                                                      "c AND inner node: 2\n"
                                                      "c binary OR inner node: 1\n"
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
                                                      "R 4 3 -2 -3 -5\n"
                                                      "p cnf 3 3\n"
                                                      "-3 0\n"
                                                      "-1 2 0\n"
                                                      "1 -2 3 0\n"
                                                      "R 3 3 1 -2 5\n"
                                                      "p cnf 3 2\n"
                                                      "-1 2 0\n"
                                                      "1 -3 0\n"
                                                      "A 2 8 12\n"
                                                      "A 2 9 13\n"
                                                      "O 4 2 14 15\n";

    inline std::string circuitParserRenHCSDBdmcInput = "c -------------------\n"
                                                       "c ------ Bella ------\n"
                                                       "c -------------------\n"
                                                       "c {renH-C}-sd-BDMC\n"
                                                       "c\n"
                                                       "nnf 21 14 5 29\n"
                                                       "c literal leaf: 10\n"
                                                       "c constant leaf: 2\n"
                                                       "c renH-C leaf: 2\n"
                                                       "c AND inner node: 4\n"
                                                       "c binary OR inner node: 3\n"
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
                                                       "R 4 3 -2 -3 -5\n"
                                                       "p cnf 3 3\n"
                                                       "-3 0\n"
                                                       "-1 2 0\n"
                                                       "1 -2 3 0\n"
                                                       "R 3 3 1 -2 5\n"
                                                       "p cnf 3 2\n"
                                                       "-1 2 0\n"
                                                       "1 -3 0\n"
                                                       "O 1 2 2 3\n"
                                                       "A 2 12 14\n"
                                                       "O 3 2 6 7\n"
                                                       "A 2 13 16\n"
                                                       "A 2 8 15\n"
                                                       "A 2 9 17\n"
                                                       "O 4 2 18 19\n";

    inline std::string circuitParserNoCommentsInput = "nnf 21 14 6\n"
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

    inline std::string circuitParserLetterCaseInput = "C -------------------\n"
                                                      "c ------ Bella ------\n"
                                                      "c -------------------\n"
                                                      "c d-DNNF\n"
                                                      "c\n"
                                                      "nNf 21 14 6\n"
                                                      "c literal leaf: 12\n"
                                                      "C constant leaf: 2\n"
                                                      "c AND inner node: 5\n"
                                                      "c binary OR inner node: 2\n"
                                                      "o 0 0\n"
                                                      "A 0\n"
                                                      "L 1\n"
                                                      "l -1\n"
                                                      "L 2\n"
                                                      "L -2\n"
                                                      "L 3\n"
                                                      "l -3\n"
                                                      "L 4\n"
                                                      "L -4\n"
                                                      "L 5\n"
                                                      "L -5\n"
                                                      "L 6\n"
                                                      "L -6\n"
                                                      "a 2 2 4\n"
                                                      "A 2 5 6\n"
                                                      "O 2 2 14 15\n"
                                                      "A 2 8 10\n"
                                                      "a 2 11 12\n"
                                                      "o 5 2 17 18\n"
                                                      "A 2 16 19\n";

    inline std::string circuitParserWhitespacesInput = "c -------------------\n"
                                                       "c ------ Bella ------\n"
                                                       "c -------------------\n"
                                                       "c d-DNNF\n"
                                                       "c\n"
                                                       "nnf   21\t14   \t6\t   \n"
                                                       "c\tliteral leaf: 12\n"
                                                       "c   constant leaf: 2\n"
                                                       "c   \tAND inner node: 5\n"
                                                       "c\t   binary OR inner node: 2\n"
                                                       "O\t0 0\n"
                                                       "A   0\n"
                                                       "L 1\n"
                                                       "\n"
                                                       "L   -1\n"
                                                       "L 2\n"
                                                       "L\t-2\n"
                                                       "L 3\t   \n"
                                                       "L -3   \t\n"
                                                       "L\t4\n"
                                                       "L -4\n"
                                                       "L   5   \n"
                                                       "L -5   \n"
                                                       "L 6\t\t\n"
                                                       "\t\n"
                                                       "L -6\t\n"
                                                       "A   2 2 4\n"
                                                       "A\t2 5 6\n"
                                                       "   \n"
                                                       "O   2   2   14   15   \n"
                                                       "A 2 8 10\n"
                                                       "A   2   11   12   \n"
                                                       "O\t5\t2\t17\t18\t\n"
                                                       "A\t2\t16\t19\t\n";

    inline std::string circuitParserMissingNnfHeaderInput = "O 0 0\n";

    inline std::string circuitParserMissingNnfHeader2Input = "O 0 0\n"
                                                             "nnf 21 14 6\n";

    inline std::string circuitParserInvalidNnfHeaderInput = "nf 21 14 6\n";

    inline std::string circuitParserInvalidNnfHeader2Input = "nnf\n";

    inline std::string circuitParserInvalidNnfHeader3Input = "nnf 21 14\n";

    inline std::string circuitParserInvalidNnfHeader4Input = "nnf 21 14 6 14 1\n";

    inline std::string circuitParserInvalidNnfHeader5Input = "nnf 21 14 a\n";

    inline std::string circuitParserInvalidNnfHeader6Input = "nnf 21 14 -6\n";

    inline std::string circuitParserInvalidNnfHeader7Input = "L a\n";

    inline std::string circuitParserInvalidNnfHeader8Input = "nnf21 14 6\n";

    inline std::string circuitParserInvalidLiteralLeafInput = "nnf 21 14 6\n"
                                                              "L a\n";

    inline std::string circuitParserInvalidLiteralLeaf2Input = "nnf 21 14 6\n"
                                                               "L -a\n";

    inline std::string circuitParserInvalidLiteralLeaf3Input = "nnf 21 14 6\n"
                                                               "L\n";

    inline std::string circuitParserInvalidLiteralLeaf4Input = "nnf 21 14 6\n"
                                                               "L - 1\n";

    inline std::string circuitParserInvalidLiteralLeaf5Input = "nnf 21 14 6\n"
                                                               "L -\t1\n";

    inline std::string circuitParserInvalidLiteralLeaf6Input = "nnf 21 14 6\n"
                                                               "L -1 2\n";

    inline std::string circuitParserInvalidLiteralLeaf7Input = "nnf 21 14 6\n"
                                                               "L1\n";

    inline std::string circuitParserInvalidLiteralLeaf8Input = "nnf 21 14 6\n"
                                                               "L-1\n";

    inline std::string circuitParserInvalidLiteralLeaf9Input = "nnf 21 14 6\n"
                                                               "L";

    inline std::string circuitParserInvalidAndInnerNodeInput = "nnf 21 14 6\n"
                                                               "L 1\n"
                                                               "A\n";

    inline std::string circuitParserInvalidAndInnerNode2Input = "nnf 21 14 6\n"
                                                                "L 1\n"
                                                                "A -1 0\n";

    inline std::string circuitParserInvalidAndInnerNode3Input = "nnf 21 14 6\n"
                                                                "L 1\n"
                                                                "A a 0\n";

    inline std::string circuitParserInvalidAndInnerNode4Input = "nnf 21 14 6\n"
                                                                "L 1\n"
                                                                "A 1\n";

    inline std::string circuitParserInvalidAndInnerNode5Input = "nnf 21 14 6\n"
                                                                "L 1\n"
                                                                "L -1\n"
                                                                "A 1 0 1\n";

    inline std::string circuitParserInvalidAndInnerNode6Input = "nnf 21 14 6\n"
                                                                "L 1\n"
                                                                "A 1 a\n";

    inline std::string circuitParserInvalidAndInnerNode7Input = "nnf 21 14 6\n"
                                                                "L 1\n"
                                                                "A 2 0 1\n";

    inline std::string circuitParserInvalidAndInnerNode8Input = "nnf 21 14 6\n"
                                                                "L 1\n"
                                                                "A 1 -0\n";

    inline std::string circuitParserInvalidAndInnerNode9Input = "nnf 21 14 6\n"
                                                                "L 1\n"
                                                                "A1 0\n";

    inline std::string circuitParserInvalidAndInnerNode10Input = "nnf 21 14 6\n"
                                                                 "L 1\n"
                                                                 "A";

    inline std::string circuitParserInvalidAndInnerNode11Input = "nnf 21 14 6\n"
                                                                 "L 1\n"
                                                                 "A 0 1\n";

    inline std::string circuitParserInvalidOrInnerNodeInput = "nnf 21 14 6\n"
                                                              "L 1\n"
                                                              "O\n";

    inline std::string circuitParserInvalidOrInnerNode2Input = "nnf 21 14 6\n"
                                                               "L 1\n"
                                                               "O -1 0\n";

    inline std::string circuitParserInvalidOrInnerNode3Input = "nnf 21 14 6\n"
                                                               "L 1\n"
                                                               "O a 0\n";

    inline std::string circuitParserInvalidOrInnerNode4Input = "nnf 21 14 6\n"
                                                               "L 1\n"
                                                               "O";

    inline std::string circuitParserInvalidOrInnerNode5Input = "nnf 21 14 6\n"
                                                               "L 1\n"
                                                               "O 0";

    inline std::string circuitParserInvalidOrInnerNode6Input = "nnf 21 14 6\n"
                                                               "L 1\n"
                                                               "O 0 a\n";

    inline std::string circuitParserInvalidOrInnerNode7Input = "nnf 21 14 6\n"
                                                               "L 1\n"
                                                               "O 0 -1\n";

    inline std::string circuitParserInvalidOrInnerNode8Input = "nnf 21 14 6\n"
                                                               "L 1\n"
                                                               "O 0 0 1\n";

    inline std::string circuitParserInvalidOrInnerNode9Input = "nnf 21 14 6\n"
                                                               "L 1\n"
                                                               "O0 0\n";

    inline std::string circuitParserInvalidOrInnerNode10Input = "nnf 21 14 6\n"
                                                                "L 1\n"
                                                                "O 0 1\n";

    inline std::string circuitParserInvalidOrInnerNode11Input = "nnf 21 14 6\n"
                                                                "L 1\n"
                                                                "O 0 1 0 1\n";

    inline std::string circuitParserInvalidOrInnerNode12Input = "nnf 21 14 6\n"
                                                                "L 1\n"
                                                                "O 0 1 -0\n";

    inline std::string circuitParserInvalidOrInnerNode13Input = "nnf 21 14 6\n"
                                                                "L 1\n"
                                                                "O 0 1 a\n";

    inline std::string circuitParserInvalidOrInnerNode14Input = "nnf 21 14 6\n"
                                                                "L 1\n"
                                                                "O 1 2 0 1\n";

    inline std::string circuitParserInvalidKromCLeafInput = "nnf 21 14 6\n"
                                                            "K a 2 2 3\n";

    inline std::string circuitParserInvalidKromCLeaf2Input = "nnf 21 14 6\n"
                                                             "K -1 2 2 3\n";

    inline std::string circuitParserInvalidKromCLeaf3Input = "nnf 21 14 6\n"
                                                             "K3 2 2 3\n";

    inline std::string circuitParserInvalidKromCLeaf4Input = "nnf 21 14 6\n"
                                                             "K";

    inline std::string circuitParserInvalidKromCLeaf5Input = "nnf 21 14 6\n"
                                                             "K\n";

    inline std::string circuitParserInvalidKromCLeaf6Input = "nnf 21 14 6\n"
                                                             "K 3\n";

    inline std::string circuitParserInvalidKromCLeaf7Input = "nnf 21 14 6\n"
                                                             "K 3 a 2 3\n";

    inline std::string circuitParserInvalidKromCLeaf8Input = "nnf 21 14 6\n"
                                                             "K 3 -1 2 3\n";

    inline std::string circuitParserInvalidKromCLeaf9Input = "nnf 21 14 6\n"
                                                             "K 3 1 2 3\n";

    inline std::string circuitParserInvalidKromCLeaf10Input = "nnf 21 14 6\n"
                                                              "K 3 3 2 3\n";

    inline std::string circuitParserInvalidKromCLeaf11Input = "nnf 21 14 6\n"
                                                              "K 3 2 a 3\n";

    inline std::string circuitParserInvalidKromCLeaf12Input = "nnf 21 14 6\n"
                                                              "K 3 2 -1 3\n";

    inline std::string circuitParserInvalidKromCLeaf13Input = "nnf 21 14 6\n"
                                                              "K 3 2 2 2\n";

    inline std::string circuitParserInvalidKromCLeaf14Input = "nnf 21 14 6\n"
                                                              "K 3 2 2 3\n"
                                                              "P cnf a 2\n";

    inline std::string circuitParserInvalidKromCLeaf15Input = "nnf 21 14 6\n"
                                                              "K 3 2 2 3\n"
                                                              "p Cnf -1 2\n";

    inline std::string circuitParserInvalidKromCLeaf16Input = "nnf 21 14 6\n"
                                                              "K 3 2 2 3\n"
                                                              "p cNf 2\n";

    inline std::string circuitParserInvalidKromCLeaf17Input = "nnf 21 14 6\n"
                                                              "K 3 2 2 3\n"
                                                              "p cnF 2 2 2 2\n";

    inline std::string circuitParserInvalidKromCLeaf18Input = "nnf 21 14 6\n"
                                                              "K 3 2 2 3\n"
                                                              "p CNF 2 a\n";

    inline std::string circuitParserInvalidKromCLeaf19Input = "nnf 21 14 6\n"
                                                              "K 3 2 2 3\n"
                                                              "p cnf 2 -1\n";

    inline std::string circuitParserInvalidKromCLeaf20Input = "nnf 21 14 6\n"
                                                              "K 2 2 2 3\n"
                                                              "p cnf 2 1\n"
                                                              "1 -2 0\n"
                                                              "-1 2 0\n";

    inline std::string circuitParserInvalidKromCLeaf21Input = "nnf 21 14 6\n"
                                                              "K 4 2 2 3\n"
                                                              "p cnf 2 3\n"
                                                              "1 -2 0\n"
                                                              "-1 2 0\n";

    inline std::string circuitParserInvalidKromCLeaf22Input = "nnf 21 14 6\n"
                                                              "K 3 2 2 3\n"
                                                              "p cnf 2 2\n"
                                                              "a -2 0\n"
                                                              "-1 2 0\n";

    inline std::string circuitParserInvalidKromCLeaf23Input = "nnf 21 14 6\n"
                                                              "K 3 2 2 3\n"
                                                              "p nnf 2 2\n"
                                                              "1 -2 0\n"
                                                              "-1 2 0\n";

    inline std::string circuitParserInvalidKromCLeaf24Input = "nnf 21 14 6\n"
                                                              "K 3 2 2 3\n"
                                                              "p cnf2 2\n";

    inline std::string circuitParserInvalidRenHCLeafInput = "nnf 17 6 5\n"
                                                            "R a 3 -2 -3 -5\n";

    inline std::string circuitParserInvalidRenHCLeaf2Input = "nnf 17 6 5\n"
                                                             "R -4 3 -2 -3 -5\n";

    inline std::string circuitParserInvalidRenHCLeaf3Input = "nnf 17 6 5\n"
                                                             "R4 3 -2 -3 -5\n";

    inline std::string circuitParserInvalidRenHCLeaf4Input = "nnf 17 6 5\n"
                                                             "R";

    inline std::string circuitParserInvalidRenHCLeaf5Input = "nnf 17 6 5\n"
                                                             "R\n";

    inline std::string circuitParserInvalidRenHCLeaf6Input = "nnf 17 6 5\n"
                                                             "R 4\n";

    inline std::string circuitParserInvalidRenHCLeaf7Input = "nnf 17 6 5\n"
                                                             "R 4 a -2 -3 -5\n";

    inline std::string circuitParserInvalidRenHCLeaf8Input = "nnf 17 6 5\n"
                                                             "R 4 -1 -2 -3 -5\n";

    inline std::string circuitParserInvalidRenHCLeaf9Input = "nnf 17 6 5\n"
                                                             "R 4 2 -2 -3 -5\n";

    inline std::string circuitParserInvalidRenHCLeaf10Input = "nnf 17 6 5\n"
                                                              "R 4 4 -2 -3 -5\n";

    inline std::string circuitParserInvalidRenHCLeaf11Input = "nnf 17 6 5\n"
                                                              "R 4 3 -2 a -5\n";

    inline std::string circuitParserInvalidRenHCLeaf12Input = "nnf 17 6 5\n"
                                                              "R 4 3 -2 2 -5\n";

    inline std::string circuitParserInvalidRenHCLeaf13Input = "nnf 17 6 5\n"
                                                              "R 4 3 2 -3 2\n";

    inline std::string circuitParserInvalidRenHCLeaf14Input = "nnf 17 6 5\n"
                                                              "R 4 3 -2 -3 -5\n"
                                                              "P cnf a 3\n";

    inline std::string circuitParserInvalidRenHCLeaf15Input = "nnf 17 6 5\n"
                                                              "R 4 3 -2 -3 -5\n"
                                                              "p Cnf -1 3\n";

    inline std::string circuitParserInvalidRenHCLeaf16Input = "nnf 17 6 5\n"
                                                              "R 4 3 -2 -3 -5\n"
                                                              "p cNf 3 a\n";

    inline std::string circuitParserInvalidRenHCLeaf17Input = "nnf 17 6 5\n"
                                                              "R 4 3 -2 -3 -5\n"
                                                              "p cnF 3 -1\n";

    inline std::string circuitParserInvalidRenHCLeaf18Input = "nnf 17 6 5\n"
                                                              "R 4 3 -2 -3 -5\n"
                                                              "p CNF 3\n";

    inline std::string circuitParserInvalidRenHCLeaf19Input = "nnf 17 6 5\n"
                                                              "R 4 3 -2 -3 -5\n"
                                                              "p cnf 3 3 3 3\n";

    inline std::string circuitParserInvalidRenHCLeaf20Input = "nnf 17 6 5\n"
                                                              "R 3 3 -2 -3 -5\n"
                                                              "p cnf 3 2\n"
                                                              "-3 0\n"
                                                              "-1 2 0\n"
                                                              "1 -2 3 0\n";

    inline std::string circuitParserInvalidRenHCLeaf21Input = "nnf 17 6 5\n"
                                                              "R 5 3 -2 -3 -5\n"
                                                              "p cnf 3 4\n"
                                                              "-3 0\n"
                                                              "-1 2 0\n"
                                                              "1 -2 3 0\n";

    inline std::string circuitParserInvalidRenHCLeaf22Input = "nnf 17 6 5\n"
                                                              "R 4 3 -2 -3 -5\n"
                                                              "p cnf 3 3\n"
                                                              "a 0\n"
                                                              "-1 2 0\n"
                                                              "1 -2 3 0\n";

    inline std::string circuitParserInvalidRenHCLeaf23Input = "nnf 17 6 5\n"
                                                              "R 4 3 -2 -3 -5\n"
                                                              "p nnf 3 3\n"
                                                              "-3 0\n"
                                                              "-1 2 0\n"
                                                              "1 -2 3 0\n";

    inline std::string circuitParserInvalidRenHCLeaf24Input = "nnf 17 6 5\n"
                                                              "R 4 3 -2 -3 -5\n"
                                                              "p cnf3 3\n";

    inline std::string circuitParserInvalidLineInput = "nnf 21 14 6\n"
                                                       "c literal leaf: 12\n"
                                                       "c constant leaf: 2\n"
                                                       "c AND inner node: 5\n"
                                                       "c binary OR inner node: 2\n"
                                                       "X\n";

    inline std::string circuitParserInvalidLine2Input = "nnf 21 14 6\n"
                                                        "c literal leaf: 12\n"
                                                        "c constant leaf: 2\n"
                                                        "c AND inner node: 5\n"
                                                        "c binary OR inner node: 2\n"
                                                        "\t   y\n";

    inline std::string circuitParserInvalidIndexInput = "nnf 21 14 6\n"
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
                                                        "A 2 15 6\n"
                                                        "O 2 2 14 15\n"
                                                        "A 2 8 10\n"
                                                        "A 2 11 12\n"
                                                        "O 5 2 17 18\n"
                                                        "A 2 16 19";

    inline std::string circuitParserInvalidIndex2Input = "nnf 21 14 6\n"
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
                                                         "O 2 2 18 15\n"
                                                         "A 2 8 10\n"
                                                         "A 2 11 12\n"
                                                         "O 5 2 17 18\n"
                                                         "A 2 16 19";

    inline std::string circuitParserEmptyInput = "";
}   // namespace HydraTest::Circuit::Parser
