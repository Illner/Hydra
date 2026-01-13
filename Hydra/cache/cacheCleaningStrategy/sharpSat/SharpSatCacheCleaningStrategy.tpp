#pragma once

#include "Hydra/cache/cacheCleaningStrategy/CacheCleaningStrategyAbstract.hpp"

namespace Hydra::Cache::CacheCleaningStrategy::SharpSat {

    using LargeNumberType = Hydra::Cache::CacheCleaningStrategy::LargeNumberType;

    /**
     * SharpSAT cache cleaning strategy - configuration
     */
    struct SharpSatCacheCleaningStrategyConfiguration {
    public:
        /**
         * True - time (=score) is reset whenever a positive hit occurs
         * False - time (=score) is unchangeable
         */
        bool resetTime = true;

        /**
         * Percentage of entries that will be deleted
         * Note: 0 is forbidden
         */
        int percentageOfDeletedEntries = 50;

        /**
         * The maximum size (in bytes) of the cache
         */
        LargeNumberType maxByteSizeCache = EIGHT_GIGABYTES_IN_BYTES;
    };
}   // namespace Hydra::Cache::CacheCleaningStrategy::SharpSat
