#pragma once

#include "./NoneCacheCleaningStrategy.hpp"

namespace Hydra::Cache::CacheCleaningStrategy::None {

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void NoneCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processCleanCache() {
        assert(false);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    bool NoneCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processShouldCacheBeCleaned() noexcept {
        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void NoneCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processCreateInfoForNewCacheBucket([[maybe_unused]] const CacheBucketStruct& cacheBucketStruct,
                                                                                                               [[maybe_unused]] const CacheRecordStruct& cacheRecordStruct) { }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void NoneCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processUpdateInfoForCacheBucketAfterPositiveHit([[maybe_unused]] const CacheBucketStruct& cacheBucketStruct,
                                                                                                                            [[maybe_unused]] const CacheRecordStruct& cacheRecordStruct) { }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void NoneCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processInitializeAfterCachePtrIsSet() { }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void NoneCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::changeIndex([[maybe_unused]] IdType oldIndex, [[maybe_unused]] IdType newIndex) { }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    LargeNumberType NoneCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::maxByteSizeStrategyOverhead() const noexcept {
        return static_cast<LargeNumberType>(0);
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void NoneCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processPrintCacheCleaningStrategyDebug([[maybe_unused]] std::ostream& out) const { }
    #endif
}   // namespace Hydra::Cache::CacheCleaningStrategy::None
