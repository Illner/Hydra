#pragma once

#include <cassert>
#include <iostream>

#include "Hydra/cache/Cache.hpp"
#include "Hydra/cache/cacheCleaningStrategy/CacheCleaningStrategyAbstract.hpp"

#include "Hydra/cache/cacheCleaningStrategy/enums/CacheCleaningStrategyTypeEnum.hpp"

namespace Hydra::Cache::CacheCleaningStrategy::None {

    using IdType = Hydra::Cache::CacheCleaningStrategy::IdType;
    using LargeNumberType = Hydra::Cache::CacheCleaningStrategy::LargeNumberType;

    /**
     * None cache cleaning strategy (final class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     * @tparam CacheValueT type used for a cache value
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    class NoneCacheCleaningStrategy final : public CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT> {
    private:
        using CacheRecordStruct = typename CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheRecordStruct;
        using CacheBucketStruct = typename CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheBucketStruct;

    public:
        NoneCacheCleaningStrategy() noexcept
            : CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>(CacheCleaningStrategyTypeEnum::NONE) { }

    private:
        void processCleanCache() override;

        bool processShouldCacheBeCleaned() noexcept override;

        void processCreateInfoForNewCacheBucket(const CacheBucketStruct& cacheBucketStruct, const CacheRecordStruct& cacheRecordStruct) override;

        void processUpdateInfoForCacheBucketAfterPositiveHit(const CacheBucketStruct& cacheBucketStruct, const CacheRecordStruct& cacheRecordStruct) override;

        void processInitializeAfterCachePtrIsSet() override;

        void changeIndex(IdType oldIndex, IdType newIndex) override;

        LargeNumberType maxByteSizeStrategyOverhead() const noexcept override;

    #ifndef NDEBUG
    private:
        void processPrintCacheCleaningStrategyDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::Cache::CacheCleaningStrategy::None

#include "./NoneCacheCleaningStrategy.ipp"
