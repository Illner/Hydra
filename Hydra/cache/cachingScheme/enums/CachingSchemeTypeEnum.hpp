#pragma once

#include <string>

namespace Hydra::Cache::CachingScheme {

    enum class CachingSchemeTypeEnum {
        NONE,
        STANDARD,
        HYBRID,
        BASIC,
        CARA
    };

    inline std::string cachingSchemeTypeEnumToString(CachingSchemeTypeEnum cachingSchemeType) noexcept {
        switch (cachingSchemeType) {
            case CachingSchemeTypeEnum::NONE:
                return "none";
            case CachingSchemeTypeEnum::STANDARD:
                return "standard";
            case CachingSchemeTypeEnum::HYBRID:
                return "hybrid";
            case CachingSchemeTypeEnum::BASIC:
                return "basic";
            case CachingSchemeTypeEnum::CARA:
                return "Cara";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Cache::CachingScheme
