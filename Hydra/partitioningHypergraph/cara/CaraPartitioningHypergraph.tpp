#pragma once

#include "Hydra/partitioningHypergraph/patoh/Patoh.h"

namespace Hydra::PartitioningHypergraph::Cara {

    /**
     * Cara - configuration
     */
    struct CaraPartitioningHypergraphConfiguration {
    public:
        /**
         * Number of parts
         */
        int k = 2;

        /**
         * Seed of the random generator
         */
        int seed = 777;

        /**
         * Imbalance factor
         */
        double imbalanceFactorKahyparLibrary = 0.15;

        /**
         * Imbalance ratio of the final partition
         */
        double finalImbalPatohLibrary = 0.2;

        /**
         * Must be set to one of
         * (0) PATOH_SUGPARAM_DEFAULT: sets the parameters to default values,
         * (1) PATOH_SUGPARAM_SPEED: if you need faster partitioning use this. For most of the matrix partitioning problems, we observed that this setting will produce reasonably good results much faster than the default value,
         * (2) PATOH_SUGPARAM_QUALITY: if you could afford a little bit more extra time for a little better quality (such as VLSI partitioning), use this value.
         */
        int lowNumberOfVariablesSuggestByProblemTypePatohLibrary = PATOH_SUGPARAM_SPEED;
        int highNumberOfVariablesSuggestByProblemTypePatohLibrary = PATOH_SUGPARAM_DEFAULT;

        /**
         * Enforces/relaxes PaToH's balance constraint.
         * (0) PATOH_BALANCE_STRICT: strictly forces balance to be \epsilon / log(K) in each bisection,
         * (1) PATOH_BALANCE_ADAPTIVE: dynamically adjusts imbalance in each recursion aiming \epsilon imbalance at the end,
         * (2) PATOH_BALANCE_RELAXED: each bisection in recursion will have maximum imbalance \epsilon.
         */
        int balancePatohLibrary = PATOH_BALANCE_ADAPTIVE;
    };
}   // namespace Hydra::PartitioningHypergraph::Cara
