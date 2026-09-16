#pragma once

#include "Hydra/hypergraphPartitioning/kahypar/Kahypar.h"
#include "Hydra/other/seed/Seed.hpp"

namespace Hydra::HypergraphPartitioning::Kahypar {

    /**
     * KaHyPar - configuration
     */
    struct KahyparHypergraphPartitioningConfiguration {
    public:
        /**
         * Number of parts
         */
        kahypar_partition_id_t kKahyparLibrary = 2;

        /**
         * Seed of the random generator
         */
        Other::Seed::SeedType seedKahyparLibrary = Other::Seed::MIN_SEED;

        /**
         * Imbalance factor
         */
        double imbalanceFactorKahyparLibrary = 0.15;
    };
}   // namespace Hydra::HypergraphPartitioning::Kahypar
