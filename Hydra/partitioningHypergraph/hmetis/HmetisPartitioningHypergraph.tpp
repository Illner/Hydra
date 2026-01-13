#pragma once

namespace Hydra::PartitioningHypergraph::Hmetis {

    /**
     * hMETIS - configuration
     */
    struct HmetisPartitioningHypergraphConfiguration {
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
}   // namespace Hydra::PartitioningHypergraph::Hmetis
