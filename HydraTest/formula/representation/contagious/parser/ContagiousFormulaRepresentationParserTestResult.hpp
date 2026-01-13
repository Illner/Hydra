#pragma once

#include <string>

namespace HydraTest::Formula::Representation::Contagious::Parser {
    inline std::string contagiousFormulaRepresentationParserNoCommentResult = "p cnf 10 9\n"
                                                                              "1 0\n"
                                                                              "-1 2 0\n"
                                                                              "-1 3 0\n"
                                                                              "-2 4 5 0\n"
                                                                              "-4 6 0\n"
                                                                              "-4 7 0\n"
                                                                              "-5 8 0\n"
                                                                              "-5 9 0\n"
                                                                              "-3 -10 0\n";

    inline std::string contagiousFormulaRepresentationParserCommentsResult = "p cnf 10 9\n"
                                                                             "1 0\n"
                                                                             "-1 2 0\n"
                                                                             "-1 3 0\n"
                                                                             "-2 4 5 0\n"
                                                                             "-4 6 0\n"
                                                                             "-4 7 0\n"
                                                                             "-5 8 0\n"
                                                                             "-5 9 0\n"
                                                                             "-3 -10 0\n";

    inline std::string contagiousFormulaRepresentationParserLetterCaseResult = "p cnf 10 9\n"
                                                                               "1 0\n"
                                                                               "-1 2 0\n"
                                                                               "-1 3 0\n"
                                                                               "-2 4 5 0\n"
                                                                               "-4 6 0\n"
                                                                               "-4 7 0\n"
                                                                               "-5 8 0\n"
                                                                               "-5 9 0\n"
                                                                               "-3 -10 0\n";

    inline std::string contagiousFormulaRepresentationParserMultipleLineClauseResult = "p cnf 10 9\n"
                                                                                       "1 0\n"
                                                                                       "-1 2 0\n"
                                                                                       "-1 3 0\n"
                                                                                       "-2 4 5 0\n"
                                                                                       "-4 6 0\n"
                                                                                       "-4 7 0\n"
                                                                                       "-5 8 0\n"
                                                                                       "-5 9 0\n"
                                                                                       "-3 -10 0\n";

    inline std::string contagiousFormulaRepresentationParserEmptyLinesResult = "p cnf 10 9\n"
                                                                               "1 0\n"
                                                                               "-1 2 0\n"
                                                                               "-1 3 0\n"
                                                                               "-2 4 5 0\n"
                                                                               "-4 6 0\n"
                                                                               "-4 7 0\n"
                                                                               "-5 8 0\n"
                                                                               "-5 9 0\n"
                                                                               "-3 -10 0\n";

    inline std::string contagiousFormulaRepresentationParserComplementaryLiteralsForbiddenResult = "The clause on line 6 contains a pair of complementary literals!\n";

    inline std::string contagiousFormulaRepresentationParserDuplicateLiteralsResult = "p cnf 10 9\n"
                                                                                      "1 0\n"
                                                                                      "-1 2 0\n"
                                                                                      "-1 3 0\n"
                                                                                      "-2 4 5 0\n"
                                                                                      "-4 6 0\n"
                                                                                      "-4 7 0\n"
                                                                                      "-5 8 0\n"
                                                                                      "-5 9 0\n"
                                                                                      "-3 -10 0\n";

    inline std::string contagiousFormulaRepresentationParserUnsatResult = "p cnf 3 6\n"
                                                                          "1 0\n"
                                                                          "-1 2 0\n"
                                                                          "-1 3 0\n"
                                                                          "1 -2 -3 0\n"
                                                                          "-2 -3 0\n"
                                                                          "2 3 0\n";

    inline std::string contagiousFormulaRepresentationParserUnitClausesResult = "p cnf 10 9\n"
                                                                                "1 0\n"
                                                                                "-1 2 0\n"
                                                                                "-1 3 0\n"
                                                                                "-2 4 5 0\n"
                                                                                "-4 6 0\n"
                                                                                "-4 0\n"
                                                                                "-5 8 0\n"
                                                                                "-5 0\n"
                                                                                "-3 -10 0\n";

    inline std::string contagiousFormulaRepresentationParserTabularResult = "p cnf 10 9\n"
                                                                            "1 0\n"
                                                                            "-1 2 0\n"
                                                                            "-1 3 0\n"
                                                                            "-2 4 5 0\n"
                                                                            "-4 6 0\n"
                                                                            "-4 7 0\n"
                                                                            "-5 8 0\n"
                                                                            "-5 9 0\n"
                                                                            "-3 -10 0\n";

    inline std::string contagiousFormulaRepresentationParserSizeResult = "p cnf 10 9\n"
                                                                         "1 0\n"
                                                                         "-1 2 0\n"
                                                                         "-1 3 0\n"
                                                                         "-2 4 5 0\n"
                                                                         "-4 6 0\n"
                                                                         "-4 7 0\n"
                                                                         "-5 8 0\n"
                                                                         "-5 9 0\n"
                                                                         "-3 -10 0\n";

    inline std::string contagiousFormulaRepresentationParserProblemLineTabularResult = "p cnf 10 9\n"
                                                                                       "1 0\n"
                                                                                       "-1 2 0\n"
                                                                                       "-1 3 0\n"
                                                                                       "-2 4 5 0\n"
                                                                                       "-4 6 0\n"
                                                                                       "-4 7 0\n"
                                                                                       "-5 8 0\n"
                                                                                       "-5 9 0\n"
                                                                                       "-3 -10 0\n";

    inline std::string contagiousFormulaRepresentationParserProblemLineMissingResult = "Invalid line 1 (1...) has occurred before the DIMACS CNF header!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLinePositionResult = "Invalid line 1 (1...) has occurred before the DIMACS CNF header!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLinePResult = "Invalid line 1 (a...) has occurred before the DIMACS CNF header!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLinePSpaceResult = "A whitespace (excluding the new line symbol (\\n)) after the char p in the DIMACS CNF header is expected, but another symbol (c) is detected on line 1!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLineCnfResult = "The character (n) in the DIMACS CNF header on line 1 is invalid!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLineCnfSpaceResult = "A whitespace (excluding the new line symbol (\\n)) after the string 'cnf' in the DIMACS CNF header is expected, but another symbol (1) is detected on line 1!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLineNumberOfVariablesNegativeResult = "A digit is expected, but another symbol (-) is detected on line 1!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLineNumberOfVariablesNotNumberResult = "A digit is expected, but another symbol (a) is detected on line 1!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLineNumberOfClausesNegativeResult = "A digit is expected, but another symbol (-) is detected on line 1!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLineNumberOfClausesNotNumberResult = "A digit is expected, but another symbol (a) is detected on line 1!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLineSizeNegativeResult = "A digit is expected, but another symbol (-) is detected on line 1!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLineSizeNotNumberResult = "A digit is expected, but another symbol (a) is detected on line 1!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLineMoreParametersResult = "A digit is expected, but another symbol (a) is detected on line 1!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLineMoreParametersNumberResult = "The DIMACS CNF header on line 1 does not have the correct number of parameters!\n";

    inline std::string contagiousFormulaRepresentationParserProblemLineLessParametersResult = "The DIMACS CNF header on line 1 does not have the correct number of parameters!\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderResult = "p cnf 6 4\n"
                                                                                        "-1 -2 0\n"
                                                                                        "2 3 -4 0\n"
                                                                                        "4 5 0\n"
                                                                                        "4 6 0\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderNoModelCountingHeaderResult = "p cnf 6 4\n"
                                                                                                             "-1 -2 0\n"
                                                                                                             "2 3 -4 0\n"
                                                                                                             "4 5 0\n"
                                                                                                             "4 6 0\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderMissingResult = "p cnf 6 4\n"
                                                                                               "-1 -2 0\n"
                                                                                               "2 3 -4 0\n"
                                                                                               "4 5 0\n"
                                                                                               "4 6 0\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderBeforeProblemLineResult = "p cnf 6 4\n"
                                                                                                         "c t mc\n"
                                                                                                         "-1 -2 0\n"
                                                                                                         "2 3 -4 0\n"
                                                                                                         "4 5 0\n"
                                                                                                         "4 6 0\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderAfterProblemLineResult = "p cnf 6 4\n"
                                                                                                        "c t wmc\n"
                                                                                                        "-1 -2 0\n"
                                                                                                        "2 3 -4 0\n"
                                                                                                        "4 5 0\n"
                                                                                                        "4 6 0\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderInTheMiddleResult = "p cnf 6 4\n"
                                                                                                   "c t pmc\n"
                                                                                                   "-1 -2 0\n"
                                                                                                   "2 3 -4 0\n"
                                                                                                   "4 5 0\n"
                                                                                                   "4 6 0\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderAtTheEndResult = "p cnf 6 4\n"
                                                                                                "c t pwmc\n"
                                                                                                "-1 -2 0\n"
                                                                                                "2 3 -4 0\n"
                                                                                                "4 5 0\n"
                                                                                                "4 6 0\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderTabularResult = "p cnf 6 4\n"
                                                                                               "c t mc\n"
                                                                                               "-1 -2 0\n"
                                                                                               "2 3 -4 0\n"
                                                                                               "4 5 0\n"
                                                                                               "4 6 0\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderMissingModelCountingTypeResult = "The model counting header on line 2 is invalid!\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderMissingModelCountingTypeTabularResult = "The model counting header on line 3 is invalid!\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderUnknownModelCountingTypeResult = "The model counting header on line 1 has an invalid type (a)!\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderLetterCaseResult = "p cnf 6 4\n"
                                                                                                  "c t wmc\n"
                                                                                                  "-1 -2 0\n"
                                                                                                  "2 3 -4 0\n"
                                                                                                  "4 5 0\n"
                                                                                                  "4 6 0\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderTSpaceResult = "p cnf 6 4\n"
                                                                                              "-1 -2 0\n"
                                                                                              "2 3 -4 0\n"
                                                                                              "4 5 0\n"
                                                                                              "4 6 0\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderModelCountingTypeSpaceResult = "p cnf 6 4\n"
                                                                                                              "-1 -2 0\n"
                                                                                                              "2 3 -4 0\n"
                                                                                                              "4 5 0\n"
                                                                                                              "4 6 0\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderMoreParametersResult = "A new line (\\n) or the end of the stream is expected, but another symbol (a) is detected on line 2!\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderMoreParametersNumberResult = "A new line (\\n) or the end of the stream is expected, but another symbol (1) is detected on line 6!\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderMoreHeadersSameResult = "p cnf 6 4\n"
                                                                                                       "c t mc\n"
                                                                                                       "-1 -2 0\n"
                                                                                                       "2 3 -4 0\n"
                                                                                                       "4 5 0\n"
                                                                                                       "4 6 0\n";

    inline std::string contagiousFormulaRepresentationParserModelCountingHeaderMoreHeadersDifferentResult = "More different model counting headers exist (weighted model counting, and projected model counting)!\n";

    inline std::string contagiousFormulaRepresentationParserClauseNotNumberResult = "A digit is expected, but another symbol (a) is detected on line 6!\n";

    inline std::string contagiousFormulaRepresentationParserMissingEndOfClauseResult = "The end of the clause (0) is expected, but the end of the stream is detected!\n";

    inline std::string contagiousFormulaRepresentationParserEmptyClauseResult = "The clause on line 7 is empty!\n";

    inline std::string contagiousFormulaRepresentationParserEmptyClauseComplementaryLiteralsResult = "The clause on line 7 contains a pair of complementary literals!\n";

    inline std::string contagiousFormulaRepresentationParserUnusedVariablesResult = "p cnf 15 9\n"
                                                                                    "1 0\n"
                                                                                    "-1 2 0\n"
                                                                                    "-1 3 0\n"
                                                                                    "-2 4 5 0\n"
                                                                                    "-4 6 0\n"
                                                                                    "-4 7 0\n"
                                                                                    "-5 8 0\n"
                                                                                    "-5 9 0\n"
                                                                                    "-3 -10 0\n";

    inline std::string contagiousFormulaRepresentationParserMoreVariablesResult = "The parsed variable (10) is out of range!\n";

    inline std::string contagiousFormulaRepresentationParserVariableOutOfRangeResult = "The parsed variable (11) is out of range!\n";

    inline std::string contagiousFormulaRepresentationParserOnlyClausesContainingComplementaryLiteralsResult = "The formula is empty!\n";

    inline std::string contagiousFormulaRepresentationParserComplementaryLiteralsResult = "Formula representation\n"
                                                                                          "Type: contagious\n"
                                                                                          "Original formula size: 4\n"
                                                                                          "Number of original clauses: 2\n"
                                                                                          "Maximum original clause size: 2\n"
                                                                                          "Assignment stack:\n"
                                                                                          "Partial assignment: \n"
                                                                                          "Number of assigned variables: 0\n"
                                                                                          "Is full assignment: 0\n"
                                                                                          "--------------------\n"
                                                                                          "Original formula: 1 2 0 5 -6 0 \n"
                                                                                          "Original clause offset: 0 3 \n"
                                                                                          "Clause - number of satisfied literals: 0 0 \n"
                                                                                          "Clause - number of unsatisfied literals: 0 0 \n"
                                                                                          "Original clause size: 2 2 \n"
                                                                                          "Clause watcher: 0 0 \n"
                                                                                          "Current component formula size: 4\n"
                                                                                          "Current component variable set (stack): \n"
                                                                                          "\t1 2 3 4 5 6 7 \n"
                                                                                          "Occurrence list: 0 2 2 0 2 2 2 2 2 2 1 2 2 2 1 2 2 2 \n"
                                                                                          "Separator: 2\n"
                                                                                          "Literal offset (end offset): 1: 0 (1) -1: 2 (2) 2: 3 (4) -2: 5 (5) 3: 6 (6) -3: 7 (7) 4: 8 (8) -4: 9 (9) 5: 10 (11) -5: 12 (12) 6: 13 (13) -6: 14 (15) 7: 16 (16) -7: 17 (17) \n"
                                                                                          "Current component clauses (fixed vector):\n"
                                                                                          "Vector: 0 1 \n"
                                                                                          "Fixed vector: 0 1 \n"
                                                                                          "Number of active elements: 2\n"
                                                                                          "Number of all elements: 2\n"
                                                                                          "Current component clauses (stack): \n"
                                                                                          "--------------------\n"
                                                                                          "Current formula: \n"
                                                                                          "1 2 0 5 -6 0 \n"
                                                                                          "--------------------\n"
                                                                                          "Current formula (no duplicate clauses): \n"
                                                                                          "1 2 0 5 -6 0 \n"
                                                                                          "--------------------\n"
                                                                                          "Current formula (no duplicate and subsumed clauses): \n"
                                                                                          "1 2 0 5 -6 0 \n"
                                                                                          "\n";

    inline std::string contagiousFormulaRepresentationParserRedundantLiteralsResult = "Formula representation\n"
                                                                                      "Type: contagious\n"
                                                                                      "Original formula size: 12\n"
                                                                                      "Number of original clauses: 6\n"
                                                                                      "Maximum original clause size: 3\n"
                                                                                      "Assignment stack:\n"
                                                                                      "Partial assignment: \n"
                                                                                      "Number of assigned variables: 0\n"
                                                                                      "Is full assignment: 0\n"
                                                                                      "--------------------\n"
                                                                                      "Original formula: 1 0 1 2 0 -2 3 0 4 -5 0 5 -6 0 -1 2 -6 0 \n"
                                                                                      "Original clause offset: 0 2 5 8 11 14 \n"
                                                                                      "Clause - number of satisfied literals: 0 0 0 0 0 0 \n"
                                                                                      "Clause - number of unsatisfied literals: 0 0 0 0 0 0 \n"
                                                                                      "Original clause size: 1 2 2 2 2 3 \n"
                                                                                      "Clause watcher: 0 0 0 0 0 0 \n"
                                                                                      "Current component formula size: 12\n"
                                                                                      "Current component variable set (stack): \n"
                                                                                      "\t1 2 3 4 5 6 7 \n"
                                                                                      "Occurrence list: 0 1 6 5 6 1 5 6 2 6 2 6 6 3 6 6 4 6 3 6 6 4 5 6 6 6 \n"
                                                                                      "Separator: 6\n"
                                                                                      "Literal offset (end offset): 1: 0 (2) -1: 3 (4) 2: 5 (7) -2: 8 (9) 3: 10 (11) -3: 12 (12) 4: 13 (14) -4: 15 (15) 5: 16 (17) -5: 18 (19) 6: 20 (20) -6: 21 (23) 7: 24 (24) -7: 25 (25) \n"
                                                                                      "Current component clauses (fixed vector):\n"
                                                                                      "Vector: 0 1 2 3 4 5 \n"
                                                                                      "Fixed vector: 0 1 2 3 4 5 \n"
                                                                                      "Number of active elements: 6\n"
                                                                                      "Number of all elements: 6\n"
                                                                                      "Current component clauses (stack): \n"
                                                                                      "--------------------\n"
                                                                                      "Current formula: \n"
                                                                                      "1 0 1 2 0 -2 3 0 4 -5 0 5 -6 0 -1 2 -6 0 \n"
                                                                                      "--------------------\n"
                                                                                      "Current formula (no duplicate clauses): \n"
                                                                                      "1 0 1 2 0 -2 3 0 4 -5 0 5 -6 0 -1 2 -6 0 \n"
                                                                                      "--------------------\n"
                                                                                      "Current formula (no duplicate and subsumed clauses): \n"
                                                                                      "1 0 -2 3 0 4 -5 0 5 -6 0 -1 2 -6 0 \n"
                                                                                      "\n";
}   // namespace HydraTest::Formula::Representation::Contagious::Parser
