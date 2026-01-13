#pragma once

#include <cassert>
#include <ostream>
#include <string>

#include "Hydra/cache/Cache.hpp"
#include "Hydra/cache/CacheBucketStructure.hpp"
#include "Hydra/cache/CacheRecordStructure.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"

#include "Hydra/cache/cacheCleaningStrategy/enums/CacheCleaningStrategyTypeEnum.hpp"

namespace Hydra::Cache::CacheCleaningStrategy {

    using IdType = Hydra::Cache::IdType;
    using LargeNumberType = Hydra::Cache::LargeNumberType;

    /**
     * Cache cleaning strategy representation (abstract class)
     * Copy and move methods are disabled!
     * Exception:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     * @tparam CacheValueT type used for a cache value
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    class CacheCleaningStrategyAbstract {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");
        static_assert(CacheBucketStruct<VarT, LiteralT, CacheValueT>::isValidCacheValueT::value, "Invalid CacheValueT type!");
        static_assert(Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isValidClauseT::value, "Invalid ClauseIdT type!");

    protected:
        using String8Type = typename Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::String8Type;
        using String16Type = typename Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::String16Type;
        using String32Type = typename Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::String32Type;
        using IdVectorType = typename Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::IdVectorType;
        using ClauseSizeType = typename Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::ClauseSizeType;
        using LiteralVectorType = typename Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::LiteralVectorType;

    protected:
        using CacheRecordStruct = typename Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheRecordStruct;
        using CacheBucketStruct = typename Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheBucketStruct;

    private:
        using CachePtrType = Cache<VarT, LiteralT, ClauseIdT, CacheValueT>*;

    public:
        explicit CacheCleaningStrategyAbstract(CacheCleaningStrategyTypeEnum cacheCleaningStrategyType) noexcept
            : cacheCleaningStrategyType_(cacheCleaningStrategyType), cachePtr_(nullptr),
              numberOfCacheCleanings_(0), numberOfDeletedEntries_(0), maxByteSizeStrategyOverhead_(0), maxByteSizeEntryWithStrategyOverhead_(0) { }

        CacheCleaningStrategyAbstract(const CacheCleaningStrategyAbstract&) = delete;
        CacheCleaningStrategyAbstract(CacheCleaningStrategyAbstract&&) noexcept = delete;

        CacheCleaningStrategyAbstract& operator=(const CacheCleaningStrategyAbstract&) = delete;
        CacheCleaningStrategyAbstract& operator=(CacheCleaningStrategyAbstract&&) noexcept = delete;

        virtual ~CacheCleaningStrategyAbstract() noexcept = default;

    private:
        CacheCleaningStrategyTypeEnum cacheCleaningStrategyType_;

    protected:
        CachePtrType cachePtr_;
        LargeNumberType numberOfCacheCleanings_;
        LargeNumberType numberOfDeletedEntries_;
        LargeNumberType maxByteSizeStrategyOverhead_;
        LargeNumberType maxByteSizeEntryWithStrategyOverhead_;

    private:
        void initializeAfterCachePtrIsSet();

    protected:
        virtual void processCleanCache() = 0;

        virtual bool processShouldCacheBeCleaned() noexcept = 0;

        virtual void processCreateInfoForNewCacheBucket(const CacheBucketStruct& cacheBucketStruct, const CacheRecordStruct& cacheRecordStruct) = 0;

        virtual void processUpdateInfoForCacheBucketAfterPositiveHit(const CacheBucketStruct& cacheBucketStruct, const CacheRecordStruct& cacheRecordStruct) = 0;

        virtual void processInitializeAfterCachePtrIsSet() = 0;

        virtual void changeIndex(IdType oldIndex, IdType newIndex) = 0;

        /**
         * Note: the function is called after the cache pointer is set
         * @return the maximum number of bytes needed for a strategy overhead
         */
        virtual LargeNumberType maxByteSizeStrategyOverhead() const noexcept = 0;

        /**
         * Increase cacheCleaningStrategyByteSize_ by maxByteSizeStrategyOverhead_
         */
        void updateCacheCleaningStrategyByteSizeAfterAddedEntry() noexcept;

        /**
         * Decrease cacheCleaningStrategyByteSize_ by maxByteSizeStrategyOverhead_
         */
        void updateCacheCleaningStrategyByteSizeAfterRemovedEntry() noexcept;

    public:
        /**
         * Clean the cache
         * Assert: cachePtr_ MUST be set
         */
        void cleanCache();

        /**
         * Assert: cachePtr_ MUST be set
         * @return true if the cache should be cleaned. Otherwise, false is returned.
         */
        bool shouldCacheBeCleaned();

        /**
         * Create info for the new cache bucket
         * Assert: cachePtr_ MUST be set
         * @param cacheBucketStruct a cache bucket structure
         * @param cacheRecordStruct a cache record structure
         */
        void createInfoForNewCacheBucket(const CacheBucketStruct& cacheBucketStruct, const CacheRecordStruct& cacheRecordStruct);

        /**
         * Update the info
         * Assert: cachePtr_ MUST be set
         * @param cacheBucketStruct a cache bucket structure
         * @param cacheRecordStruct a cache record structure
         */
        void updateInfoForCacheBucketAfterPositiveHit(const CacheBucketStruct& cacheBucketStruct, const CacheRecordStruct& cacheRecordStruct);

        /**
         * Set the cache pointer
         * @param cachePtr a cache pointer
         */
        void setCachePtr(CachePtrType cachePtr);

        /**
         * Getter
         * @return the number of cache cleanings
         */
        LargeNumberType getNumberOfCacheCleanings() const noexcept;

        /**
         * Getter
         * @return the number of deleted entries
         */
        LargeNumberType getNumberOfDeletedEntries() const noexcept;

    #ifndef NDEBUG
    public:
        void printCacheCleaningStrategyDebug(std::ostream& out) const;

    protected:
        virtual void processPrintCacheCleaningStrategyDebug(std::ostream& out) const = 0;
    #endif
    };
}   // namespace Hydra::Cache::CacheCleaningStrategy

#include "./CacheCleaningStrategyAbstract.ipp"
