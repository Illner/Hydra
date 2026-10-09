#pragma once

namespace Hydra::HypergraphPartitioning::Hmetis {

    /**
     * hMETIS - configuration
     */
    struct HmetisHypergraphPartitioningConfiguration {
    public:
        /**
         * This is the number of desired partitions
         */
        int NpartsHmetisLibrary = 2;

        /**
         * This parameter is used to specify the allowed imbalance between the partitions during recursive bisection.
         * This is an integer number between 1 and 49, and specifies the allowed load imbalance.
         */
        int UBfactorHmetisLibrary = 5;
    };
}   // namespace Hydra::HypergraphPartitioning::Hmetis
