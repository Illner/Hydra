#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iterator>
#include <limits>
#include <memory>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "Hydra/cache/CacheBucketStructure.hpp"
#include "Hydra/cache/CacheRecordStructure.hpp"
#include "Hydra/cache/CacheStatisticsStructure.hpp"
#include "Hydra/cache/cachingScheme/CachingSchemeAbstract.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/cache/exceptions/CacheException.hpp"
#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/cache/cachingScheme/enums/SaveTypeEnum.hpp"
#include "Hydra/cache/enums/CacheSizeTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"

#include "Hydra/cache/Cache.hxx"

namespace Hydra::Cache {

    using InitialCacheSizeType = unsigned long int;   // at least 32 bits

    consteval LargeNumberType convertGigabytesToBytes(LargeNumberType sizeInGigabytes) {
        return sizeInGigabytes * LargeNumberType(1024) * LargeNumberType(1024) * LargeNumberType(1024);
    }

    inline constexpr LargeNumberType TWO_GIGABYTES_IN_BYTES = convertGigabytesToBytes(2);        //  2 GB
    inline constexpr LargeNumberType FOUR_GIGABYTES_IN_BYTES = convertGigabytesToBytes(4);       //  4 GB
    inline constexpr LargeNumberType EIGHT_GIGABYTES_IN_BYTES = convertGigabytesToBytes(8);      //  8 GB
    inline constexpr LargeNumberType SIXTEEN_GIGABYTES_IN_BYTES = convertGigabytesToBytes(16);   // 16 GB

    // Forward declaration
    namespace CacheCleaningStrategy {
        template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
        class CacheCleaningStrategyAbstract;

        namespace None {
            template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
            class NoneCacheCleaningStrategy;
        }   // namespace None

        namespace SharpSat {
            template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
            class SharpSatCacheCleaningStrategy;
        }   // namespace SharpSat

        namespace Cara {
            template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
            class CaraCacheCleaningStrategy;
        }   // namespace Cara
    }   // namespace CacheCleaningStrategy

    /**
     * Cache representation
     * Copy methods are disabled! Move methods (default) are allowed!
     * Exception:
     *      CacheIsTooBigException
     *      MappingCacheIsTooBigException
     *      MappingIsNotInjectiveException (debug)
     *      SomethingCannotBeSavedAsStdSizeTException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     * @tparam CacheValueT type used for a cache value
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    class Cache {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");
        static_assert(CacheBucketStruct<VarT, LiteralT, CacheValueT>::isValidCacheValueT::value, "Invalid CacheValueT type!");
        static_assert(Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isValidClauseT::value, "Invalid ClauseIdT type!");

    private:
        using MpzIntType = typename CacheBucketStruct<VarT, LiteralT, CacheValueT>::MpzIntType;
        using CustomType = typename CacheBucketStruct<VarT, LiteralT, CacheValueT>::CustomType;

    public:
        using CacheStatisticsPtrType = typename CacheStatistics::CacheStatisticsPtrType;
        using LiteralType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::LiteralType;
        using String8Type = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::String8Type;
        using String16Type = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::String16Type;
        using String32Type = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::String32Type;
        using IdVectorType = typename CacheBucketStruct<VarT, LiteralT, CacheValueT>::IdVectorType;
        using ClauseSizeType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
        using VariableSetType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using LiteralVectorType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
        using VariableVectorType = typename CacheBucketStruct<VarT, LiteralT, CacheValueT>::VariableVectorType;
        using IdSortedVectorType = typename CacheBucketStruct<VarT, LiteralT, CacheValueT>::IdSortedVectorType;
        using MappingFromVariableToLiteralType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::MappingFromVariableToLiteralType;
        using FormulaRepresentationAbstractPtrType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    public:
        using CacheBucketStruct = typename Hydra::Cache::CacheBucketStruct<VarT, LiteralT, CacheValueT>;
        using CacheStatisticsStruct = typename Hydra::Cache::CacheStatisticsStruct<VarT, LiteralT, ClauseIdT>;
        using CacheRecordStruct = typename CachingScheme::CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::CacheRecordStruct;

    private:
        using CacheValuePtrType = const CacheValueT*;
        using LargeNumberVectorType = std::vector<LargeNumberType>;
        using MappingCacheType = Other::HashMap::MapType<IdType, LiteralVectorType>;
        using Cache8Type = Other::HashMap::StringMapType<String8Type, CacheBucketStruct>;
        using Cache16Type = Other::HashMap::StringMapType<String16Type, CacheBucketStruct>;
        using Cache32Type = Other::HashMap::StringMapType<String32Type, CacheBucketStruct>;
        using CachingSchemeAbstractUniquePtrType = std::unique_ptr<Hydra::Cache::CachingScheme::CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>>;
        using CacheCleaningStrategyAbstractUniquePtrType = std::unique_ptr<Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>>;

    public:
        using CacheValuePtrAndIdPairOptionalType = std::optional<std::pair<CacheValuePtrType, IdType>>;

    public:
        Cache(CachingSchemeAbstractUniquePtrType&& cachingSchemeAbstractUniquePtr,
              CacheCleaningStrategyAbstractUniquePtrType&& cacheCleaningStrategyAbstractUniquePtr,
              CacheStatisticsPtrType cacheStatisticsPtr = nullptr)
            : id_counter_(0), usedMapping_(cachingSchemeAbstractUniquePtr->getUsedMapping()),
              keyByteSizeCache8_(0), valueByteSizeCache8_(0), keyByteSizeCache16_(0), valueByteSizeCache16_(0),
              keyByteSizeCache32_(0), valueByteSizeCache32_(0), keyByteSizeMappingCache_(0), valueByteSizeMappingCache_(0), cacheCleaningStrategyByteSize_(0),
              numberOfEntriesCache8_(0), numberOfEntriesCache16_(0), numberOfEntriesCache32_(0), numberOfEntriesTotalCache_(0), numberOfEntriesMappingCache_(0),
              numberOfHits_(0), numberOfPositiveHits_(0), numberOfNegativeHits_(0),
              variableNumberOfHits_(cachingSchemeAbstractUniquePtr->getFormulaRepresentationAbstractPtr()->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), 0),
              variableNumberOfPositiveHits_(cachingSchemeAbstractUniquePtr->getFormulaRepresentationAbstractPtr()->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), 0),
              variableNumberOfNegativeHits_(cachingSchemeAbstractUniquePtr->getFormulaRepresentationAbstractPtr()->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), 0),
              totalHitCacheStatistics_(cachingSchemeAbstractUniquePtr->getFormulaRepresentationAbstractPtr()),
              positiveHitCacheStatistics_(cachingSchemeAbstractUniquePtr->getFormulaRepresentationAbstractPtr()),
              negativeHitCacheStatistics_(cachingSchemeAbstractUniquePtr->getFormulaRepresentationAbstractPtr()),
              cachingSchemeAbstractUniquePtr_(std::move(cachingSchemeAbstractUniquePtr)),
              cacheCleaningStrategyAbstractUniquePtr_(std::move(cacheCleaningStrategyAbstractUniquePtr)),
              cacheStatisticsPtr_(cacheStatisticsPtr) {
            // The variables cannot be saved as std::size_t
            VarT numberOfVariablesInOriginalFormula = cachingSchemeAbstractUniquePtr_->getFormulaRepresentationAbstractPtr()->getNumberOfVariablesInOriginalFormula();
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<VarT>(numberOfVariablesInOriginalFormula, 1))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("variables", numberOfVariablesInOriginalFormula);

            // The formula size cannot be saved as std::size_t
            FormulaSizeType originalFormulaSize = cachingSchemeAbstractUniquePtr_->getFormulaRepresentationAbstractPtr()->getOriginalFormulaSize();
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<FormulaSizeType>(originalFormulaSize))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("formula size", originalFormulaSize);

            cacheCleaningStrategyAbstractUniquePtr_->setCachePtr(this);

            initializeCaches();
        }

        Cache(const Cache&) = delete;
        Cache(Cache&&) noexcept = default;

        Cache& operator=(const Cache&) = delete;
        Cache& operator=(Cache&&) noexcept = default;

    private:
        IdType id_counter_;
        const bool usedMapping_;

        Cache8Type cache8_;
        Cache16Type cache16_;
        Cache32Type cache32_;
        MappingCacheType mappingCache_;

        LargeNumberType keyByteSizeCache8_;
        LargeNumberType valueByteSizeCache8_;
        LargeNumberType keyByteSizeCache16_;
        LargeNumberType valueByteSizeCache16_;
        LargeNumberType keyByteSizeCache32_;
        LargeNumberType valueByteSizeCache32_;
        LargeNumberType keyByteSizeMappingCache_;
        LargeNumberType valueByteSizeMappingCache_;
        LargeNumberType cacheCleaningStrategyByteSize_;   // owned by CacheCleaningStrategy

        LargeNumberType numberOfEntriesCache8_;
        LargeNumberType numberOfEntriesCache16_;
        LargeNumberType numberOfEntriesCache32_;
        LargeNumberType numberOfEntriesTotalCache_;   // 8 + 16 + 32
        LargeNumberType numberOfEntriesMappingCache_;

        LargeNumberType numberOfHits_;
        LargeNumberType numberOfPositiveHits_;
        LargeNumberType numberOfNegativeHits_;

        LargeNumberVectorType variableNumberOfHits_;
        LargeNumberVectorType variableNumberOfPositiveHits_;
        LargeNumberVectorType variableNumberOfNegativeHits_;

        CacheStatisticsStruct totalHitCacheStatistics_;
        CacheStatisticsStruct positiveHitCacheStatistics_;
        CacheStatisticsStruct negativeHitCacheStatistics_;

        CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr_;
        CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategyAbstractUniquePtr_;

        CacheStatisticsPtrType cacheStatisticsPtr_;

        inline static constexpr LargeNumberType S_VAR_BYTE_SIZE_ = sizeof(VarT);
        inline static constexpr LargeNumberType S_ID_BYTE_SIZE_ = sizeof(IdType);
        inline static constexpr LargeNumberType S_LIMB_BYTE_SIZE_ = sizeof(mp_limb_t);
        inline static constexpr LargeNumberType S_LITERAL_BYTE_SIZE_ = sizeof(LiteralT);
        inline static constexpr LargeNumberType S_ID_NODE_BYTE_SIZE_ = sizeof(IdNodeType);
        inline static constexpr LargeNumberType S_DIGIT_CUSTOM_BYTE_SIZE_ = CustomType::S_DIGIT_BYTE_SIZE;

        inline static constexpr InitialCacheSizeType S_CACHE_8_INITIAL_SIZE_ = 1 << 19;         // 2^19 =   524'288
        inline static constexpr InitialCacheSizeType S_CACHE_16_INITIAL_SIZE_ = 1 << 18;        // 2^18 =   262'144
        inline static constexpr InitialCacheSizeType S_CACHE_32_INITIAL_SIZE_ = 1 << 17;        // 2^17 =   131'072
        inline static constexpr InitialCacheSizeType S_MAPPING_CACHE_INITIAL_SIZE_ = 1 << 20;   // 2^20 = 1'048'576

    private:
        /**
         * Initialize the caches (8 + 16 + 32 + mapping)
         */
        void initializeCaches();

        /**
         * Update the data structures and variables after a positive hit
         * @param cacheRecordStruct a cache record structure
         * @param cacheBucketStruct the cache bucket structure
         */
        void updateDataStructuresAndVariablesAfterPositiveHit(const CacheRecordStruct& cacheRecordStruct, const CacheBucketStruct& cacheBucketStruct);

        /**
         * Update the data structures and variables after a negative hit
         * @param cacheRecordStruct a cache record structure
         */
        void updateDataStructuresAndVariablesAfterNegativeHit(const CacheRecordStruct& cacheRecordStruct) noexcept;

        /**
         * Update the data structures and variables before the cache bucket will be deleted
         * Assert: keySize is greater than zero
         * Note: the cache bucket will NOT be deleted from the cache
         * Note: the corresponding mapping will be removed from the mapping cache
         * @param cacheBucketStruct a cache bucket structure
         * @param cacheSizeType the cache size in which the cache bucket is saved
         * @param keySize the size (=number of chars) of the key
         */
        void updateDataStructuresAndVariablesBeforeRemovingCacheBucket(const CacheBucketStruct& cacheBucketStruct, CacheSizeTypeEnum cacheSizeType,
                                                                       LargeNumberType keySize);

        /**
         * Note:
         *      ID node         - S_ID_BYTE_SIZE_ + S_ID_NODE_BYTE_SIZE_
         *      mpz_int         - S_ID_BYTE_SIZE_ + S_LIMB_BYTE_SIZE_ * |limb|
         *      custom          - S_ID_BYTE_SIZE_ + S_DIGIT_CUSTOM_BYTE_SIZE_ * |digit|
         *      Variable vector - S_ID_BYTE_SIZE_ + S_VAR_BYTE_SIZE_ * |variable|
         * @param cacheBucketStruct a cache bucket structure
         * @return the size (in bytes) of the cache bucket structure
         */
        LargeNumberType computeCacheBucketByteSize(const CacheBucketStruct& cacheBucketStruct) const;

    public:
        /**
         * Note: used for tests
         * @return the maximum number of bytes needed for a key
         */
        LargeNumberType maxByteSizeKey() const;

        /**
         * Note: used for tests
         * @return the maximum number of bytes needed for a mapping
         */
        LargeNumberType maxByteSizeMapping() const;

        /**
         * @return the maximum number of bytes needed for a cache bucket
         */
        LargeNumberType maxByteSizeCacheBucket() const;

        /**
         * @return the maximum number of bytes needed for an entry
         */
        LargeNumberType maxByteSizeEntry() const;

        /**
         * @return the current size (in bytes) of the cache
         */
        LargeNumberType currentByteSizeCache() const noexcept;

        /**
         * Getter
         * @return the formula representation pointer
         */
        FormulaRepresentationAbstractPtrType getFormulaRepresentationAbstractPtr() const noexcept;

        /**
         * Create a cache record structure
         * Assert: at least one variable
         * Assert: the variables MUST NOT be free
         * Assert: the variables MUST NOT be assigned
         * Assert: the variables MUST be in the current component
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @return a cache record structure
         * @throw MappingIsNotInjectiveException (debug) if the created mapping is not injective
         */
        CacheRecordStruct createCacheRecordStruct(const VariableSetType& currentComponentVariableSet) const;

        /**
         * Check if the cache record exists in the cache
         * Note: if the cache record does not exist in the cache, the optional type does not have a value
         * @param cacheRecordStruct a cache record structure
         * @return (cache value pointer, identifier of the cache bucket)
         */
        CacheValuePtrAndIdPairOptionalType searchInCache(const CacheRecordStruct& cacheRecordStruct);

        /**
         * Add the cache record to the cache
         * Note: if a cache record with the same key already exists in the cache, nothing happens
         * @param cacheRecordStruct a cache record structure
         * @param cacheValue a cache value
         * @throw CacheIsTooBigException if the cache is too big
         * @throw MappingCacheIsTooBigException if the mapping cache is too big
         */
        void addCacheRecordToCache(CacheRecordStruct&& cacheRecordStruct, CacheValueT&& cacheValue);

        /**
         * Create the composed mapping based on the mappings in the cache bucket and cache record
         * Assert: both mappings MUST have the same size
         * Note: if mapping is not used, an empty mapping is returned
         * Note: if the mapping is identical, an empty mapping is returned
         * @param id the identifier of a cache bucket
         * @param cacheRecordStruct a cache record structure
         * @return the composed mapping
         */
        MappingFromVariableToLiteralType createMapping(IdType id, const CacheRecordStruct& cacheRecordStruct) const;

        /**
         * Set statistics after the compilation
         * Statistics:
         *      numberOfCurrentEntriesNumber
         *      numberOfDeletedEntriesNumber
         *      numberOfCacheCleaningsNumber
         */
        void setStatisticsAfterCompilation() const;

        /**
         * Getter
         * @return the total hit cache statistics
         */
        const CacheStatisticsStruct& getTotalHitCacheStatistics() const noexcept;

        /**
         * Getter
         * @return the positive hit cache statistics
         */
        const CacheStatisticsStruct& getPositiveHitCacheStatistics() const noexcept;

        /**
         * Getter
         * @return the negative hit cache statistics
         */
        const CacheStatisticsStruct& getNegativeHitCacheStatistics() const noexcept;

    private:
        template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
        friend class CacheCleaningStrategy::CacheCleaningStrategyAbstract;

        template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
        friend class CacheCleaningStrategy::None::NoneCacheCleaningStrategy;

        template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
        friend class CacheCleaningStrategy::SharpSat::SharpSatCacheCleaningStrategy;

        template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
        friend class CacheCleaningStrategy::Cara::CaraCacheCleaningStrategy;

    #ifndef NDEBUG
    private:
        template <typename CacheT, typename StringT>
        void printCacheDebug(std::ostream& out, const CacheT& cache) const;

    public:
        void printCacheDebug(std::ostream& out, bool printCurrentFormula = false, bool printCaches = false,
                             bool printVariableNumberOfHits = true, bool printCacheStatistics = true) const;

        void printCachingSchemeDebug(std::ostream& out, bool printCurrentFormula = false) const;

        void printCacheCleaningStrategyDebug(std::ostream& out) const;
    #endif
    };
}   // namespace Hydra::Cache

#include "./Cache.ipp"
