#pragma once

#include <string>

namespace CaraTest::SharpSolver {
    inline std::string sharpSolverEmptyFormulaResult = "The formula is empty!\n";

    inline std::string sharpSolverUnsatisfiableFormulaResult = "Current formula: -1 -2 0 1 -2 0 1 2 0 -1 2 -3 0 -1 2 3 0 \n"
                                                               "\n"
                                                               "Number of models: 0\n";

    inline std::string sharpSolverOneUnitClauseResult = "Current formula: -2 0 \n"
                                                        "\n"
                                                        "Number of models: 4\n";

    inline std::string sharpSolverOneClauseResult = "Current formula: 1 -2 0 \n"
                                                    "\n"
                                                    "Number of models: 3\n";

    inline std::string sharpSolverFreeVariablesResult = "Current formula: -2 3 0 \n"
                                                        "\n"
                                                        "Number of models: 12\n";

    inline std::string sharpSolverFreeVariablesInDecisionNodeResult = "Current formula: -1 2 0 -2 3 0 \n"
                                                                      "\n"
                                                                      "Number of models: 4\n";

    inline std::string sharpSolverTwoDisjointClausesResult = "Current formula: 1 2 0 -3 -4 0 \n"
                                                             "\n"
                                                             "Number of models: 9\n";

    inline std::string sharpSolverInitiallyImpliedLiteralsResult = "Current formula: 1 0 -4 0 -1 2 0 1 3 0 -4 6 0 4 5 0 8 9 0 -9 10 0 -1 3 4 0 1 -3 -4 0 \n"
                                                                   "\n"
                                                                   "Number of models: 16\n";
}   // namespace CaraTest::SharpSolver
