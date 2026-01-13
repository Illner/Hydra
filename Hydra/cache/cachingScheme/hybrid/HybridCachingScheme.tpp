#pragma once

#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"

namespace Hydra::Cache::CachingScheme::Hybrid {

    /**
     * Hybrid caching scheme - configuration
     */
    struct HybridCachingSchemeConfiguration {
    public:
        /**
         * What clause type should be omitted
         */
        OmitClauseTypeEnum omitClauseType = OmitClauseTypeEnum::NONE;
    };
}   // namespace Hydra::Cache::CachingScheme::Hybrid
