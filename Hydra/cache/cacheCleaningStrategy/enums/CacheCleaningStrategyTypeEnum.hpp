#pragma once

#include <string>

namespace Hydra::Cache::CacheCleaningStrategy {

    enum class CacheCleaningStrategyTypeEnum {
        NONE,
        SHARP_SAT,
        CARA
    };

    inline std::string cacheCleaningStrategyTypeEnumToString(CacheCleaningStrategyTypeEnum cacheCleaningStrategyType) noexcept {
        switch (cacheCleaningStrategyType) {
            case CacheCleaningStrategyTypeEnum::NONE:
                return "none";
            case CacheCleaningStrategyTypeEnum::SHARP_SAT:
                return "sharpSAT";
            case CacheCleaningStrategyTypeEnum::CARA:
                return "Cara";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Cache::CacheCleaningStrategy
