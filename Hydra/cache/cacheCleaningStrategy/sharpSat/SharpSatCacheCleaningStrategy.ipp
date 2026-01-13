#pragma once

#include "./SharpSatCacheCleaningStrategy.hpp"

namespace Hydra::Cache::CacheCleaningStrategy::SharpSat {

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void SharpSatCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processCleanCache() {
        assert(mappingFromIdToTime_.size() > 1);   // at least two entries

        TimeVectorType timeVector;
        timeVector.reserve(mappingFromIdToTime_.size());

        #ifndef NDEBUG
        IdType maxId = 0;
        #endif

        for (const auto& [key, value] : mappingFromIdToTime_) {
            timeVector.emplace_back(value);

            #ifndef NDEBUG
            if (key > maxId)
                maxId = key;
            #endif
        }

        TimeVectorType::size_type timeVectorLastElementPosition = (timeVector.size() - 1);
        TimeVectorType::size_type position = timeVectorLastElementPosition * ((double)configuration_.percentageOfDeletedEntries / (double)100);

        // The newest entry MUST survive
        if (position == timeVectorLastElementPosition)
            --position;

        auto elementIt = timeVector.begin();
        std::advance(elementIt, position);
        std::nth_element(timeVector.begin(), elementIt, timeVector.end());

        TimeType timeThreshold = *elementIt;

        // Cache 8
        for (auto it = this->cachePtr_->cache8_.begin(); it != this->cachePtr_->cache8_.end();) {
            IdType id = it->second.id;

            assert(Other::containInMap(mappingFromIdToTime_, id));   // ID exists

            // Delete the entry
            if (mappingFromIdToTime_[id] <= timeThreshold) {
                ++this->numberOfDeletedEntries_;

                this->cachePtr_->updateDataStructuresAndVariablesBeforeRemovingCacheBucket(it->second, CacheSizeTypeEnum::CACHE_8, it->first.size());
                it = this->cachePtr_->cache8_.erase(it);

                mappingFromIdToTime_.erase(id);
                this->updateCacheCleaningStrategyByteSizeAfterRemovedEntry();
            }
            // Keep the entry
            else
                ++it;
        }

        // Cache 16
        for (auto it = this->cachePtr_->cache16_.begin(); it != this->cachePtr_->cache16_.end();) {
            IdType id = it->second.id;

            assert(Other::containInMap(mappingFromIdToTime_, id));   // ID exists

            // Delete the entry
            if (mappingFromIdToTime_[id] <= timeThreshold) {
                ++this->numberOfDeletedEntries_;

                this->cachePtr_->updateDataStructuresAndVariablesBeforeRemovingCacheBucket(it->second, CacheSizeTypeEnum::CACHE_16, it->first.size());
                it = this->cachePtr_->cache16_.erase(it);

                mappingFromIdToTime_.erase(id);
                this->updateCacheCleaningStrategyByteSizeAfterRemovedEntry();
            }
            // Keep the entry
            else
                ++it;
        }

        // Cache 32
        for (auto it = this->cachePtr_->cache32_.begin(); it != this->cachePtr_->cache32_.end();) {
            IdType id = it->second.id;

            assert(Other::containInMap(mappingFromIdToTime_, id));   // ID exists

            // Delete the entry
            if (mappingFromIdToTime_[id] <= timeThreshold) {
                ++this->numberOfDeletedEntries_;

                this->cachePtr_->updateDataStructuresAndVariablesBeforeRemovingCacheBucket(it->second, CacheSizeTypeEnum::CACHE_32, it->first.size());
                it = this->cachePtr_->cache32_.erase(it);

                mappingFromIdToTime_.erase(id);
                this->updateCacheCleaningStrategyByteSizeAfterRemovedEntry();
            }
            // Keep the entry
            else
                ++it;
        }

        assert(Other::containInMap(mappingFromIdToTime_, maxId));                                              // the newest entry exists
        assert(this->cachePtr_->numberOfEntriesTotalCache_ == (LargeNumberType)mappingFromIdToTime_.size());   // valid number of entries
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    bool SharpSatCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processShouldCacheBeCleaned() noexcept {
        // Not enough entries
        if (mappingFromIdToTime_.size() <= 1)
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
    void SharpSatCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processCreateInfoForNewCacheBucket(const CacheBucketStruct& cacheBucketStruct,
                                                                                                                   [[maybe_unused]] const CacheRecordStruct& cacheRecordStruct) {
        assert(!Other::containInMap(mappingFromIdToTime_, cacheBucketStruct.id));   // ID does not exist

        assert(this->cachePtr_->numberOfEntriesTotalCache_ <= std::numeric_limits<std::size_t>::max());   // not too many entries

        // Shift time
        if (timeCounter_ == std::numeric_limits<TimeType>::max())
            shiftTime();

        assert(timeCounter_ < std::numeric_limits<TimeType>::max());

        mappingFromIdToTime_[cacheBucketStruct.id] = timeCounter_;
        ++timeCounter_;

        this->updateCacheCleaningStrategyByteSizeAfterAddedEntry();

        assert(this->cachePtr_->numberOfEntriesTotalCache_ == (LargeNumberType)mappingFromIdToTime_.size());   // valid number of entries
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void SharpSatCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processUpdateInfoForCacheBucketAfterPositiveHit(const CacheBucketStruct& cacheBucketStruct,
                                                                                                                                [[maybe_unused]] const CacheRecordStruct& cacheRecordStruct) {
        assert(Other::containInMap(mappingFromIdToTime_, cacheBucketStruct.id));   // ID exists

        if (!configuration_.resetTime)
            return;

        // Shift time
        if (timeCounter_ == std::numeric_limits<TimeType>::max())
            shiftTime();

        assert(timeCounter_ < std::numeric_limits<TimeType>::max());

        mappingFromIdToTime_[cacheBucketStruct.id] = timeCounter_;
        ++timeCounter_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void SharpSatCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processInitializeAfterCachePtrIsSet() {
        mappingFromIdToTime_ = MappingFromIdToTimeType(this->cachePtr_->S_MAPPING_CACHE_INITIAL_SIZE_);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void SharpSatCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::changeIndex(IdType oldIndex, IdType newIndex) {
        assert(Other::containInMap(mappingFromIdToTime_, oldIndex));    // oldIndex exists
        assert(!Other::containInMap(mappingFromIdToTime_, newIndex));   // newIndex does not exist

        auto it = mappingFromIdToTime_.find(oldIndex);

        mappingFromIdToTime_[newIndex] = it->second;
        mappingFromIdToTime_.erase(it);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    LargeNumberType SharpSatCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::maxByteSizeStrategyOverhead() const noexcept {
        return (this->cachePtr_->S_ID_BYTE_SIZE_ + static_cast<LargeNumberType>(sizeof(TimeType)));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void SharpSatCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::shiftTime() {
        IdVectorType structure;
        structure.reserve(mappingFromIdToTime_.size());

        // Fill the structure
        for (const auto& [key, value] : mappingFromIdToTime_)
            structure.emplace_back(key);

        std::sort(structure.begin(), structure.end(), [this](IdType id1, IdType id2) -> bool {
            assert(mappingFromIdToTime_[id1] != mappingFromIdToTime_[id2]);

            return mappingFromIdToTime_[id1] < mappingFromIdToTime_[id2];
        });

        timeCounter_ = 0;
        for (IdType id : structure) {
            mappingFromIdToTime_[id] = timeCounter_;
            ++timeCounter_;
        }
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void SharpSatCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::printMappingFromIdToTimeDebug(std::ostream& out) const {
        // Empty
        if (mappingFromIdToTime_.empty()) {
            out << "Empty" << std::endl;
            return;
        }

        for (IdType id : Other::extractKeysFromMap(mappingFromIdToTime_, true))
            out << "ID: " << std::to_string(id) << ", time: " << std::to_string(mappingFromIdToTime_.at(id)) << std::endl;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void SharpSatCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>::processPrintCacheCleaningStrategyDebug(std::ostream& out) const {
        // Configuration
        out << "Reset time: " << std::to_string(configuration_.resetTime) << std::endl;
        out << "Percentage of entries that will be deleted: " << std::to_string(configuration_.percentageOfDeletedEntries) << std::endl;
        out << "The maximum size (in bytes) of the cache: " << std::to_string(configuration_.maxByteSizeCache) << std::endl;

        out << "Mapping from ID to time" << std::endl;
        printMappingFromIdToTimeDebug(out);
        out << std::endl;
    }
    #endif
}   // namespace Hydra::Cache::CacheCleaningStrategy::SharpSat
