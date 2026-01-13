#pragma once

#include <string>

namespace Hydra::Cache {

    enum class CacheSizeTypeEnum {
        CACHE_8,
        CACHE_16,
        CACHE_32
    };

    inline std::string cacheSizeTypeEnumToString(CacheSizeTypeEnum cacheSizeType) noexcept {
        switch (cacheSizeType) {
            case CacheSizeTypeEnum::CACHE_8:
                return "cache 8";
            case CacheSizeTypeEnum::CACHE_16:
                return "cache 16";
            case CacheSizeTypeEnum::CACHE_32:
                return "cache 32";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Cache
