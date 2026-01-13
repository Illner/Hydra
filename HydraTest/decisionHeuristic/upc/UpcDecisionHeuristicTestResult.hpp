#pragma once

#include <string>

namespace HydraTest::DecisionHeuristic::Upc {
    inline std::string upcDecisionHeuristicEupcResult = "Decision heuristic\n"
                                                        "Type: exact unit propagation count (EUPC)\n"
                                                        "Ignore pure literal type: pure literals are not ignored\n"
                                                        "Current formula: -1 -5 0 1 2 0 -3 4 0 -3 -5 0 5 6 0 -1 -2 3 0 1 -2 -3 0 \n"
                                                        "Constant: 1\n"
                                                        "\n"
                                                        "\n"
                                                        "Selected variables: 1 2 3 4 5 6\n"
                                                        "Decision variable: 1\n"
                                                        "\n";

    inline std::string upcDecisionHeuristicEupcSelectedVariablesResult = "Decision heuristic\n"
                                                                         "Type: exact unit propagation count (EUPC)\n"
                                                                         "Ignore pure literal type: pure literals are not ignored\n"
                                                                         "Current formula: -1 -5 0 1 2 0 -3 4 0 -3 -5 0 5 6 0 -1 -2 3 0 1 -2 -3 0 \n"
                                                                         "Constant: 1\n"
                                                                         "\n"
                                                                         "\n"
                                                                         "Selected variables: 2 3 4 5 6\n"
                                                                         "Decision variable: 5\n"
                                                                         "\n"
                                                                         "Selected variables: 2 3\n"
                                                                         "Decision variable: 2\n"
                                                                         "\n"
                                                                         "Selected variables: 4\n"
                                                                         "Decision variable: 4\n"
                                                                         "\n";

    inline std::string upcDecisionHeuristicAupcResult = "Decision heuristic\n"
                                                        "Type: approximate unit propagation count (AUPC)\n"
                                                        "Ignore pure literal type: pure literals are not ignored\n"
                                                        "Current formula: -1 -5 0 1 2 0 -3 4 0 -3 -5 0 5 6 0 -1 -2 3 0 1 -2 -3 0 \n"
                                                        "Approximate number of variables: 1\n"
                                                        "Constant: 1\n"
                                                        "\n"
                                                        "\n"
                                                        "Selected variables: 1 2 3 4 5 6\n"
                                                        "Decision variable: 5\n"
                                                        "\n";

    inline std::string upcDecisionHeuristicAupcSelectedVariablesResult = "Decision heuristic\n"
                                                                         "Type: approximate unit propagation count (AUPC)\n"
                                                                         "Ignore pure literal type: pure literals are not ignored\n"
                                                                         "Current formula: -1 -5 0 1 2 0 -3 4 0 -3 -5 0 5 6 0 -1 -2 3 0 1 -2 -3 0 \n"
                                                                         "Approximate number of variables: 2\n"
                                                                         "Constant: 1\n"
                                                                         "\n"
                                                                         "\n"
                                                                         "Selected variables: 3\n"
                                                                         "Decision variable: 3\n"
                                                                         "\n"
                                                                         "Selected variables: 2 3 5\n"
                                                                         "Decision variable: 5\n"
                                                                         "\n"
                                                                         "Selected variables: 2 4 6\n"
                                                                         "Decision variable: 2\n"
                                                                         "\n"
                                                                         "Selected variables: 3 4 6\n"
                                                                         "Decision variable: 3\n"
                                                                         "\n"
                                                                         "Selected variables: 1 2 3 4 5 6\n"
                                                                         "Decision variable: 1\n"
                                                                         "\n";
}   // namespace HydraTest::DecisionHeuristic::Upc
