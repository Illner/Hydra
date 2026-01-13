#pragma once

#include "Hydra/partitioningHypergraph/patoh/Patoh.h"

namespace Hydra::PartitioningHypergraph::Patoh {

    /**
     * PaToH - configuration
     */
    struct PatohPartitioningHypergraphConfiguration {
    public:
        /**
         * Number of parts
         */
        int kPatohLibrary = 2;

        /**
         * Determines the cost function for partitioning. Must be either
         * (1) PATOH_CONPART for 'Connectivity-1' metric or
         * (2) PATOH_CUTPART for cutnet metric.
         */
        int cutTypePatohLibrary = PATOH_CONPART;

        /**
         * If the number of variables is
         * (1) equal or greater than the threshold, highNumberOfVariablesSuggestByProblemTypePatohLibrary is used,
         * (2) less than the threshold, lowNumberOfVariablesSuggestByProblemTypePatohLibrary is used.
         */
        char32_t numberOfVariablesThreshold = 200;

        /**
         * Must be set to one of
         * (0) PATOH_SUGPARAM_DEFAULT: sets the parameters to default values,
         * (1) PATOH_SUGPARAM_SPEED: if you need faster partitioning use this. For most of the matrix partitioning problems, we observed that this setting will produce reasonably good results much faster than the default value,
         * (2) PATOH_SUGPARAM_QUALITY: if you could afford a little bit more extra time for a little better quality (such as VLSI partitioning), use this value.
         */
        int lowNumberOfVariablesSuggestByProblemTypePatohLibrary = PATOH_SUGPARAM_DEFAULT;
        int highNumberOfVariablesSuggestByProblemTypePatohLibrary = PATOH_SUGPARAM_QUALITY;

        /**
         * Seed of the random generator. Set to
         * (-1) for using current time as the seed for random generator,
         * (0) for using partitioning count (number of times PaToH partitions called) as the seed,
         * (any other non-zero value) to for fixing random generator seed.
         */
        int seedPatohLibrary = 777;

        /**
         * Imbalance ratio of the final partition
         */
        double finalImbalPatohLibrary = 0.2;

        /**
         * Enforces/relaxes PaToH's balance constraint.
         * (0) PATOH_BALANCE_STRICT: strictly forces balance to be \epsilon / log(K) in each bisection,
         * (1) PATOH_BALANCE_ADAPTIVE: dynamically adjusts imbalance in each recursion aiming \epsilon imbalance at the end,
         * (2) PATOH_BALANCE_RELAXED: each bisection in recursion will have maximum imbalance \epsilon.
         */
        int balancePatohLibrary = PATOH_BALANCE_ADAPTIVE;
    };
}   // namespace Hydra::PartitioningHypergraph::Patoh
