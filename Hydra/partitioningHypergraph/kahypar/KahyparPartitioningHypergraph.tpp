#pragma once

#include "Hydra/partitioningHypergraph/kahypar/Kahypar.h"

namespace Hydra::PartitioningHypergraph::Kahypar {

    /**
     * KaHyPar - configuration
     */
    struct KahyparPartitioningHypergraphConfiguration {
    public:
        /**
         * Number of parts
         */
        kahypar_partition_id_t kKahyparLibrary = 2;

        /**
         * Seed of the random generator
         */
        int seedKahyparLibrary = 777;

        /**
         * Imbalance factor
         */
        double imbalanceFactorKahyparLibrary = 0.15;
    };
}   // namespace Hydra::PartitioningHypergraph::Kahypar
