#pragma once

#include <string>

namespace Hydra::Cache::CachingScheme {

    enum class CachingSchemeVariantTypeEnum {
        NONE,
        STANDARD,
        HYBRID,
        BASIC,
        I,
        CARA
    };

    inline std::string cachingSchemeVariantTypeEnumToString(CachingSchemeVariantTypeEnum cachingSchemeVariantType) noexcept {
        switch (cachingSchemeVariantType) {
            case CachingSchemeVariantTypeEnum::NONE:
                return "none";
            case CachingSchemeVariantTypeEnum::STANDARD:
                return "standard";
            case CachingSchemeVariantTypeEnum::HYBRID:
                return "hybrid";
            case CachingSchemeVariantTypeEnum::BASIC:
                return "basic";
            case CachingSchemeVariantTypeEnum::I:
                return "i";
            case CachingSchemeVariantTypeEnum::CARA:
                return "Cara";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Cache::CachingScheme
