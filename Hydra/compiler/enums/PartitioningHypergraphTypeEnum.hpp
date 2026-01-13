#pragma once

#include <string>

#include "Hydra/other/operatingSystem/OperatingSystem.hpp"

namespace Hydra {

    enum class PartitioningHypergraphTypeEnum {
        CARA,
        KAHYPAR,
        PATOH_OR_HMETIS,

        CARA_SPEED
    };

    inline std::string partitioningHypergraphTypeEnumToString(PartitioningHypergraphTypeEnum partitioningHypergraphType) noexcept {
        switch (partitioningHypergraphType) {
            case PartitioningHypergraphTypeEnum::CARA:
                return "Cara";
            case PartitioningHypergraphTypeEnum::CARA_SPEED:
                return "Cara (speed)";
            case PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS:
                // Windows
                if (Other::OperatingSystem::isWindows())
                    return "hMETIS";
                // Linux, macOS
                else
                    return "PaToH";
            case PartitioningHypergraphTypeEnum::KAHYPAR:
                return "KaHyPar";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra
