#pragma once

#include <string>

namespace HydraTest::DecisionHeuristic::Random {
    inline std::string randomDecisionHeuristicResult = "Decision heuristic\n"
                                                       "Type: random\n"
                                                       "Ignore pure literal type: pure literals are not ignored\n"
                                                       "\n"
                                                       "\n"
                                                       "Selected variables: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42\n"
                                                       "Decision variable: correct\n"
                                                       "Decision variable: correct\n"
                                                       "Decision variable: correct\n"
                                                       "Decision variable: correct\n"
                                                       "Decision variable: correct\n"
                                                       "Decision variable: correct\n"
                                                       "Decision variable: correct\n"
                                                       "Decision variable: correct\n"
                                                       "Decision variable: correct\n"
                                                       "Decision variable: correct\n";

    inline std::string randomDecisionHeuristicSelectedVariablesResult = "Decision heuristic\n"
                                                                        "Type: random\n"
                                                                        "Ignore pure literal type: pure literals are not ignored\n"
                                                                        "\n"
                                                                        "\n"
                                                                        "Selected variables: 1 2 3 4 5 6\n"
                                                                        "Decision variable: correct\n"
                                                                        "\n"
                                                                        "Selected variables: 1 7 13 19 25 31 37\n"
                                                                        "Decision variable: correct\n"
                                                                        "\n"
                                                                        "Selected variables: 7 8 9\n"
                                                                        "Decision variable: correct\n"
                                                                        "\n"
                                                                        "Selected variables: 13\n"
                                                                        "Decision variable: correct\n"
                                                                        "\n";
}   // namespace HydraTest::DecisionHeuristic::Random
