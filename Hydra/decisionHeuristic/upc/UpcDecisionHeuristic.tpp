#pragma once

namespace Hydra::DecisionHeuristic::Upc {

    /**
     * Unit Propagation Count (UPC) decision heuristic - configuration
     */
    struct UpcDecisionHeuristicConfiguration {
    public:
        /**
         * True - the exact variant
         * False - the approximate variant
         */
        bool exactVariant = true;

        /**
         * The number of variables for which the unit propagations and exact scores are computed
         */
        char32_t approximateNumberOfVariables = static_cast<char32_t>(10);

        /**
         * Score(var) = constant * |UP(+var)| * |UP(-var)| + |UP(+var)| + |UP(−var)|
         */
        long long int constant = 1;
    };
}   // namespace Hydra::DecisionHeuristic::Upc
