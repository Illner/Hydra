#pragma once

#include "./CaraCacheCleaningStrategy.hpp"

namespace Hydra::Cache::CacheCleaningStrategy::Cara {

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CaraCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processCleanCache() {
        assert(mappingFromIdToActivity_.size() > 1);   // at least two entries

        ActivityVectorType activityVector;
        activityVector.reserve(mappingFromIdToActivity_.size());

        IdType maxId = 0;
        for (const auto& [key, value] : mappingFromIdToActivity_) {
            activityVector.emplace_back(value);

            if (key > maxId)
                maxId = key;
        }

        ActivityVectorType::size_type position = (activityVector.size() - 1) * ((double)configuration_.percentageOfDeletedEntries / (double)100);

        auto elementIt = activityVector.begin();
        std::advance(elementIt, position);
        std::nth_element(activityVector.begin(), elementIt, activityVector.end());

        ActivityType activityThreshold = *elementIt;

        // Cache 8
        for (auto it = this->cachePtr_->cache8_.begin(); it != this->cachePtr_->cache8_.end();) {
            IdType id = it->second.id;

            assert(Other::containInMap(mappingFromIdToActivity_, id));   // ID exists

            // Delete the entry
            if ((id != maxId) && (mappingFromIdToActivity_[id] <= activityThreshold)) {
                ++this->numberOfDeletedEntries_;

                this->cachePtr_->updateDataStructuresAndVariablesBeforeRemovingCacheBucket(it->second, CacheSizeTypeEnum::CACHE_8, it->first.size());
                it = this->cachePtr_->cache8_.erase(it);

                mappingFromIdToActivity_.erase(id);
                this->updateCacheCleaningStrategyByteSizeAfterRemovedEntry();
            }
            // Keep the entry
            else
                ++it;
        }

        // Cache 16
        for (auto it = this->cachePtr_->cache16_.begin(); it != this->cachePtr_->cache16_.end();) {
            IdType id = it->second.id;

            assert(Other::containInMap(mappingFromIdToActivity_, id));   // ID exists

            // Delete the entry
            if ((id != maxId) && (mappingFromIdToActivity_[id] <= activityThreshold)) {
                ++this->numberOfDeletedEntries_;

                this->cachePtr_->updateDataStructuresAndVariablesBeforeRemovingCacheBucket(it->second, CacheSizeTypeEnum::CACHE_16, it->first.size());
                it = this->cachePtr_->cache16_.erase(it);

                mappingFromIdToActivity_.erase(id);
                this->updateCacheCleaningStrategyByteSizeAfterRemovedEntry();
            }
            // Keep the entry
            else
                ++it;
        }

        // Cache 32
        for (auto it = this->cachePtr_->cache32_.begin(); it != this->cachePtr_->cache32_.end();) {
            IdType id = it->second.id;

            assert(Other::containInMap(mappingFromIdToActivity_, id));   // ID exists

            // Delete the entry
            if ((id != maxId) && (mappingFromIdToActivity_[id] <= activityThreshold)) {
                ++this->numberOfDeletedEntries_;

                this->cachePtr_->updateDataStructuresAndVariablesBeforeRemovingCacheBucket(it->second, CacheSizeTypeEnum::CACHE_32, it->first.size());
                it = this->cachePtr_->cache32_.erase(it);

                mappingFromIdToActivity_.erase(id);
                this->updateCacheCleaningStrategyByteSizeAfterRemovedEntry();
            }
            // Keep the entry
            else
                ++it;
        }

        assert(Other::containInMap(mappingFromIdToActivity_, maxId));                                              // the newest entry exists
        assert(this->cachePtr_->numberOfEntriesTotalCache_ == (LargeNumberType)mappingFromIdToActivity_.size());   // valid number of entries
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    bool CaraCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processShouldCacheBeCleaned() noexcept {
        // Not enough entries
        if (mappingFromIdToActivity_.size() <= 1)
            return false;

        // The configuration limit
        if ((this->cachePtr_->currentByteSizeCache() + this->maxByteSizeEntryWithStrategyOverhead_) >= configuration_.maxByteSizeCache)
            return true;

        // The std::size_t limit
        if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>((LargeNumberType)10 + this->cachePtr_->numberOfEntriesTotalCache_))
            return true;

        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CaraCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processCreateInfoForNewCacheBucket(const CacheBucketStruct& cacheBucketStruct,
                                                                                                               [[maybe_unused]] const CacheRecordStruct& cacheRecordStruct) {
        assert(!Other::containInMap(mappingFromIdToActivity_, cacheBucketStruct.id));   // ID does not exist

        assert(this->cachePtr_->numberOfEntriesTotalCache_ <= std::numeric_limits<std::size_t>::max());   // not too many entries

        mappingFromIdToActivity_[cacheBucketStruct.id] = activityCounter_;
        updateActivityCounter();

        this->updateCacheCleaningStrategyByteSizeAfterAddedEntry();

        assert(this->cachePtr_->numberOfEntriesTotalCache_ == (LargeNumberType)mappingFromIdToActivity_.size());   // valid number of entries
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CaraCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processUpdateInfoForCacheBucketAfterPositiveHit(const CacheBucketStruct& cacheBucketStruct,
                                                                                                                            [[maybe_unused]] const CacheRecordStruct& cacheRecordStruct) {
        assert(Other::containInMap(mappingFromIdToActivity_, cacheBucketStruct.id));   // ID exists

        mappingFromIdToActivity_[cacheBucketStruct.id] += activityCounter_;
        updateActivityCounter();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CaraCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processInitializeAfterCachePtrIsSet() {
        mappingFromIdToActivity_ = MappingFromIdToActivityType(this->cachePtr_->S_MAPPING_CACHE_INITIAL_SIZE_);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CaraCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::changeIndex(IdType oldIndex, IdType newIndex) {
        assert(Other::containInMap(mappingFromIdToActivity_, oldIndex));    // oldIndex exists
        assert(!Other::containInMap(mappingFromIdToActivity_, newIndex));   // newIndex does not exist

        auto it = mappingFromIdToActivity_.find(oldIndex);

        mappingFromIdToActivity_[newIndex] = it->second;
        mappingFromIdToActivity_.erase(it);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    LargeNumberType CaraCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::maxByteSizeStrategyOverhead() const noexcept {
        return (this->cachePtr_->S_ID_BYTE_SIZE_ + static_cast<LargeNumberType>(sizeof(ActivityType)));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CaraCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::updateActivityCounter() noexcept {
        activityCounter_ *= activityIncrement_;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CaraCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::printMappingFromIdToActivityDebug(std::ostream& out) const {
        // Empty
        if (mappingFromIdToActivity_.empty()) {
            out << "Empty" << std::endl;
            return;
        }

        for (IdType id : Other::extractKeysFromMap(mappingFromIdToActivity_, true))
            out << "ID: " << std::to_string(id) << ", activity: " << std::to_string(mappingFromIdToActivity_.at(id)) << std::endl;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CaraCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processPrintCacheCleaningStrategyDebug(std::ostream& out) const {
        // Configuration
        out << "Activity decay factor: " << std::to_string(configuration_.activityDecayFactor) << std::endl;
        out << "Percentage of entries that will be deleted: " << std::to_string(configuration_.percentageOfDeletedEntries) << std::endl;
        out << "The maximum size (in bytes) of the cache: " << std::to_string(configuration_.maxByteSizeCache) << std::endl;

        out << "Mapping from ID to activity" << std::endl;
        printMappingFromIdToActivityDebug(out);
        out << std::endl;
    }
    #endif
}   // namespace Hydra::Cache::CacheCleaningStrategy::Cara
