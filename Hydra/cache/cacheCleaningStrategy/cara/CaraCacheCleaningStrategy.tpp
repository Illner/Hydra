#pragma once

#include "Hydra/cache/cacheCleaningStrategy/CacheCleaningStrategyAbstract.hpp"

namespace Hydra::Cache::CacheCleaningStrategy::Cara {

    using ActivityType = double;   // 64 bits

    using LargeNumberType = Hydra::Cache::CacheCleaningStrategy::LargeNumberType;

    /**
     * Cara cache cleaning strategy - configuration
     */
    struct CaraCacheCleaningStrategyConfiguration {
    public:
        /**
         * The activity decay factor
         * Note: 0 is forbidden
         * Note: less than or equal to 1
         */
        ActivityType activityDecayFactor = 0.99999;

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
}   // namespace Hydra::Cache::CacheCleaningStrategy::Cara
