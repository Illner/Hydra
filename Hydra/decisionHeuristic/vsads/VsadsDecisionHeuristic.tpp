#pragma once

namespace Hydra::DecisionHeuristic::Vsads {

    /**
     * Variable State Aware Decaying Sum (VSADS) decision heuristic - configuration
     */
    struct VsadsDecisionHeuristicConfiguration {
    public:
        /**
         * The constant factor for the VSIDS part
         */
        long double p = 1;

        /**
         * The constant factor for the DLCS part
         */
        long double q = 0.5;
    };
}   // namespace Hydra::DecisionHeuristic::Vsads
