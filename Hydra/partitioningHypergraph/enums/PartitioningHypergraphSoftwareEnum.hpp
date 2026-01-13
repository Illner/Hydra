#pragma once

#include <string>

namespace Hydra::PartitioningHypergraph {

    enum class PartitioningHypergraphSoftwareEnum {
        HMETIS,
        PATOH,
        KAHYPAR,
        WRAPPER
    };

    inline std::string partitioningHypergraphSoftwareEnumToString(PartitioningHypergraphSoftwareEnum partitioningHypergraphSoftware) noexcept {
        switch (partitioningHypergraphSoftware) {
            case PartitioningHypergraphSoftwareEnum::HMETIS:
                return "hMETIS";
            case PartitioningHypergraphSoftwareEnum::PATOH:
                return "PaToH";
            case PartitioningHypergraphSoftwareEnum::KAHYPAR:
                return "KaHyPar";
            case PartitioningHypergraphSoftwareEnum::WRAPPER:
                return "wrapper";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::PartitioningHypergraph
