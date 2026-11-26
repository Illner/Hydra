#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
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

#include "Hydra/cache/cacheCleaningStrategy/cara/CaraCacheCleaningStrategy.tpp"

namespace Hydra::Cache::CacheCleaningStrategy::Cara {

    using IdType = Hydra::Cache::CacheCleaningStrategy::IdType;

    /**
     * Cara cache cleaning strategy (final class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     * @tparam CacheValueT type used for a cache value
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    class CaraCacheCleaningStrategy final : public CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT> {
    private:
        using CacheRecordStruct = typename CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheRecordStruct;
        using CacheBucketStruct = typename CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheBucketStruct;

    private:
        using ActivityVectorType = std::vector<ActivityType>;
        using MappingFromIdToActivityType = Other::HashMap::MapType<IdType, ActivityType>;

    public:
        explicit CaraCacheCleaningStrategy(const CaraCacheCleaningStrategyConfiguration& configuration = CaraCacheCleaningStrategyConfiguration())
            : CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>(CacheCleaningStrategyTypeEnum::CARA),
              activityCounter_(1), activityIncrement_(static_cast<ActivityType>(1) / configuration.activityDecayFactor),
              configuration_(configuration) {
            assert(configuration_.activityDecayFactor > 0 && configuration_.activityDecayFactor <= 1);
            assert(activityIncrement_ <= std::ldexp(static_cast<ActivityType>(1), S_ACTIVITY_RESCALING_EXPONENT_ - 1));   // the activity counter cannot overflow between two rescalings
            assert(configuration_.percentageOfDeletedEntries > 0 && configuration_.percentageOfDeletedEntries <= 100);
        }

    private:
        ActivityType activityCounter_;
        const ActivityType activityIncrement_;
        MappingFromIdToActivityType mappingFromIdToActivity_;
        CaraCacheCleaningStrategyConfiguration configuration_;

        inline static constexpr int S_ACTIVITY_RESCALING_EXPONENT_ = 512;

    private:
        void processCleanCache() override;

        bool processShouldCacheBeCleaned() noexcept override;

        void processCreateInfoForNewCacheBucket(const CacheBucketStruct& cacheBucketStruct, const CacheRecordStruct& cacheRecordStruct) override;

        void processUpdateInfoForCacheBucketAfterPositiveHit(const CacheBucketStruct& cacheBucketStruct, const CacheRecordStruct& cacheRecordStruct) override;

        void processInitializeAfterCachePtrIsSet() override;

        void changeIndex(IdType oldIndex, IdType newIndex) override;

        LargeNumberType maxByteSizeStrategyOverhead() const noexcept override;

        /**
         * Update the activity counter
         * Note: activityCounter_ *= activityIncrement_
         * Note: if the activity counter exceeds 2^S_ACTIVITY_RESCALING_EXPONENT_, the activity counter and all the activities are multiplied by 2^(-S_ACTIVITY_RESCALING_EXPONENT_)
         */
        void updateActivityCounter() noexcept;

    #ifndef NDEBUG
    private:
        void printMappingFromIdToActivityDebug(std::ostream& out) const;

        void processPrintCacheCleaningStrategyDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::Cache::CacheCleaningStrategy::Cara

#include "./CaraCacheCleaningStrategy.ipp"
