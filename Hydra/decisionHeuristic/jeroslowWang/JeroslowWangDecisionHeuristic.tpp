#pragma once

namespace Hydra::DecisionHeuristic::JeroslowWang {

    /**
     * Jeroslow-Wang decision heuristic - configuration
     */
    struct JeroslowWangDecisionHeuristicConfiguration {
    public:
        /**
         * True - the two-sided variant
         * False - the one-sided variant
         */
        bool twoSidedVariant = true;
    };
}   // namespace Hydra::DecisionHeuristic::JeroslowWang
