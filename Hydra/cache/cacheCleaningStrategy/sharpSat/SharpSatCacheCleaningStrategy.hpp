#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <vector>

#include "Hydra/cache/Cache.hpp"
#include "Hydra/cache/CacheBucketStructure.hpp"
#include "Hydra/cache/CacheRecordStructure.hpp"
#include "Hydra/cache/cacheCleaningStrategy/CacheCleaningStrategyAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/cache/cacheCleaningStrategy/enums/CacheCleaningStrategyTypeEnum.hpp"

#include "Hydra/cache/cacheCleaningStrategy/sharpSat/SharpSatCacheCleaningStrategy.tpp"

namespace Hydra::Cache::CacheCleaningStrategy::SharpSat {

    #ifndef NDEBUG
    using TimeType = unsigned long long int;   // at least 64 bits
    #else
    using TimeType = std::size_t;
    #endif
    using IdType = Hydra::Cache::CacheCleaningStrategy::IdType;
    using LargeNumberType = Hydra::Cache::CacheCleaningStrategy::LargeNumberType;

    /**
     * SharpSAT cache cleaning strategy (final class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     * @tparam CacheValueT type used for a cache value
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    class SharpSatCacheCleaningStrategy final : public CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT> {
    private:
        using IdVectorType = typename CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::IdVectorType;

    private:
        using CacheRecordStruct = typename CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheRecordStruct;
        using CacheBucketStruct = typename CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheBucketStruct;

    private:
        using TimeVectorType = std::vector<TimeType>;
        using MappingFromIdToTimeType = Other::HashMap::MapType<IdType, TimeType>;

    public:
        explicit SharpSatCacheCleaningStrategy(const SharpSatCacheCleaningStrategyConfiguration& configuration = SharpSatCacheCleaningStrategyConfiguration())
            : CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>(CacheCleaningStrategyTypeEnum::SHARP_SAT),
              timeCounter_(0), configuration_(configuration) {
            assert(configuration_.percentageOfDeletedEntries > 0 && configuration_.percentageOfDeletedEntries <= 100);
        }

    private:
        TimeType timeCounter_;
        MappingFromIdToTimeType mappingFromIdToTime_;
        SharpSatCacheCleaningStrategyConfiguration configuration_;

    private:
        void processCleanCache() override;

        bool processShouldCacheBeCleaned() noexcept override;

        void processCreateInfoForNewCacheBucket(const CacheBucketStruct& cacheBucketStruct, const CacheRecordStruct& cacheRecordStruct) override;

        void processUpdateInfoForCacheBucketAfterPositiveHit(const CacheBucketStruct& cacheBucketStruct, const CacheRecordStruct& cacheRecordStruct) override;

        void processInitializeAfterCachePtrIsSet() override;

        void changeIndex(IdType oldIndex, IdType newIndex) override;

        LargeNumberType maxByteSizeStrategyOverhead() const noexcept override;

        /**
         * Shift time
         */
        void shiftTime();

    #ifndef NDEBUG
    private:
        void printMappingFromIdToTimeDebug(std::ostream& out) const;

        void processPrintCacheCleaningStrategyDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::Cache::CacheCleaningStrategy::SharpSat

#include "./SharpSatCacheCleaningStrategy.ipp"
