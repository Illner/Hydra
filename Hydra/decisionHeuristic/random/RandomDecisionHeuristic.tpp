#pragma once

#include "Hydra/other/seed/Seed.hpp"

namespace Hydra::DecisionHeuristic::Random {

    /**
     * Random decision heuristic - configuration
     */
    struct RandomDecisionHeuristicConfiguration {
    public:
        /**
         * Seed of the random generator
         */
        Other::Seed::SeedType seed = Other::Seed::MIN_SEED;
    };
}   // namespace Hydra::DecisionHeuristic::Random
