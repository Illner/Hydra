#pragma once

#include <string>

#include "Hydra/other/operatingSystem/OperatingSystem.hpp"

namespace Hydra {

    enum class HypergraphPartitioningTypeEnum {
        CARA,
        KAHYPAR,
        PATOH_OR_HMETIS,

        CARA_SPEED
    };

    inline std::string hypergraphPartitioningTypeEnumToString(HypergraphPartitioningTypeEnum hypergraphPartitioningType) noexcept {
        switch (hypergraphPartitioningType) {
            case HypergraphPartitioningTypeEnum::CARA:
                return "Cara";
            case HypergraphPartitioningTypeEnum::CARA_SPEED:
                return "Cara (speed)";
            case HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS:
                // Windows
                if (Other::OperatingSystem::isWindows())
                    return "hMETIS";
                // Linux, macOS
                else
                    return "PaToH";
            case HypergraphPartitioningTypeEnum::KAHYPAR:
                return "KaHyPar";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra
