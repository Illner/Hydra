#pragma once

#include "./CacheCleaningStrategyAbstract.hpp"

namespace Hydra::Cache::CacheCleaningStrategy {

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::initializeAfterCachePtrIsSet() {
        processInitializeAfterCachePtrIsSet();

        maxByteSizeStrategyOverhead_ = maxByteSizeStrategyOverhead();
        maxByteSizeEntryWithStrategyOverhead_ = cachePtr_->maxByteSizeEntry() + maxByteSizeStrategyOverhead_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::updateCacheCleaningStrategyByteSizeAfterAddedEntry() noexcept {
        cachePtr_->cacheCleaningStrategyByteSize_ += maxByteSizeStrategyOverhead_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::updateCacheCleaningStrategyByteSizeAfterRemovedEntry() noexcept {
        cachePtr_->cacheCleaningStrategyByteSize_ -= maxByteSizeStrategyOverhead_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::cleanCache() {
        assert(cachePtr_);   // pointer is set

        processCleanCache();

        ++numberOfCacheCleanings_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    bool CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::shouldCacheBeCleaned() {
        assert(cachePtr_);   // pointer is set

        return processShouldCacheBeCleaned();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::createInfoForNewCacheBucket(const CacheBucketStruct& cacheBucketStruct,
                                                                                                            const CacheRecordStruct& cacheRecordStruct) {
        assert(cachePtr_);   // pointer is set

        processCreateInfoForNewCacheBucket(cacheBucketStruct, cacheRecordStruct);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::updateInfoForCacheBucketAfterPositiveHit(const CacheBucketStruct& cacheBucketStruct,
                                                                                                                         const CacheRecordStruct& cacheRecordStruct) {
        assert(cachePtr_);   // pointer is set

        processUpdateInfoForCacheBucketAfterPositiveHit(cacheBucketStruct, cacheRecordStruct);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::setCachePtr(CachePtrType cachePtr) {
        cachePtr_ = cachePtr;

        assert(cachePtr_);   // pointer is set

        initializeAfterCachePtrIsSet();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    LargeNumberType CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::getNumberOfCacheCleanings() const noexcept {
        return numberOfCacheCleanings_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    LargeNumberType CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::getNumberOfDeletedEntries() const noexcept {
        return numberOfDeletedEntries_;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>::printCacheCleaningStrategyDebug(std::ostream& out) const {
        out << "Cache cleaning strategy" << std::endl;
        out << "Type: " << cacheCleaningStrategyTypeEnumToString(cacheCleaningStrategyType_) << std::endl;
        out << "Number of cache cleanings: " << std::to_string(numberOfCacheCleanings_) << std::endl;
        out << "Number of deleted entries: " << std::to_string(numberOfDeletedEntries_) << std::endl;

        if (cachePtr_) {
            out << "Size (bytes): " << std::to_string(this->cachePtr_->cacheCleaningStrategyByteSize_) << std::endl;
            out << "The maximum size (in bytes) of a strategy overhead: " << std::to_string(maxByteSizeStrategyOverhead_) << std::endl;
            out << "The maximum size (in bytes) of an entry (including strategy overhead): " << std::to_string(maxByteSizeEntryWithStrategyOverhead_) << std::endl;
        }

        out << "Cache pointer: ";
        if (cachePtr_)
            out << "set";
        else
            out << "not set";
        out << std::endl;

        // Cache cleaning strategy
        this->processPrintCacheCleaningStrategyDebug(out);
    }
    #endif
}   // namespace Hydra::Cache::CacheCleaningStrategy
