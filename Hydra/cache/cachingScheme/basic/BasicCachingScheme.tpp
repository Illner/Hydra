#pragma once

#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"

namespace Hydra::Cache::CachingScheme::Basic {

    /**
     * Basic caching scheme - configuration
     */
    struct BasicCachingSchemeConfiguration {
    public:
        /**
         * Remove multi-occurrent clauses (only one occurrence per clause is kept)
         */
        bool removeMultiOccurrentClauses = true;

        /**
         * What clause type should be omitted
         */
        OmitClauseTypeEnum omitClauseType = OmitClauseTypeEnum::NONE;
    };
}   // namespace Hydra::Cache::CachingScheme::Basic
