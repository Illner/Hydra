#pragma once

#include <string>

namespace Hydra::Cache {

    enum class CacheTypeEnum {
        COMPONENT,
        HYPERGRAPH_CUT
    };

    inline std::string cacheTypeEnumToString(CacheTypeEnum cacheType) noexcept {
        switch (cacheType) {
            case CacheTypeEnum::COMPONENT:
                return "component caching";
            case CacheTypeEnum::HYPERGRAPH_CUT:
                return "hypergraph cut caching";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Cache
