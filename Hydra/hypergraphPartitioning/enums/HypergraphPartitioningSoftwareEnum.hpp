#pragma once

#include <string>

namespace Hydra::HypergraphPartitioning {

    enum class HypergraphPartitioningSoftwareEnum {
        HMETIS,
        PATOH,
        KAHYPAR,
        WRAPPER
    };

    inline std::string hypergraphPartitioningSoftwareEnumToString(HypergraphPartitioningSoftwareEnum hypergraphPartitioningSoftware) noexcept {
        switch (hypergraphPartitioningSoftware) {
            case HypergraphPartitioningSoftwareEnum::HMETIS:
                return "hMETIS";
            case HypergraphPartitioningSoftwareEnum::PATOH:
                return "PaToH";
            case HypergraphPartitioningSoftwareEnum::KAHYPAR:
                return "KaHyPar";
            case HypergraphPartitioningSoftwareEnum::WRAPPER:
                return "wrapper";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::HypergraphPartitioning
