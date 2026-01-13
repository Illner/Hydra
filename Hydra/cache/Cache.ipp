#pragma once

#include "./Cache.hpp"

namespace Hydra::Cache {

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::initializeCaches() {
        // The mapping cache
        if (!usedMapping_)
            mappingCache_ = MappingCacheType(0);
        else
            mappingCache_ = MappingCacheType(S_MAPPING_CACHE_INITIAL_SIZE_);

        CacheTypeEnum cacheType = cachingSchemeAbstractUniquePtr_->getCacheType();

        // Caches (8 + 16 + 32)
        switch (cachingSchemeAbstractUniquePtr_->getSaveType()) {
            // None
            case CachingScheme::SaveTypeEnum::NONE:
                cache8_ = Cache8Type(0);
                cache16_ = Cache16Type(0);
                cache32_ = Cache32Type(0);
                break;
            // Clause ID
            case CachingScheme::SaveTypeEnum::CLAUSE_ID:
                if (std::is_same<ClauseIdT, char8_t>::value) {
                    cache8_ = Cache8Type(S_CACHE_8_INITIAL_SIZE_);
                    cache16_ = Cache16Type(0);
                    cache32_ = Cache32Type(0);
                }
                else if (std::is_same<ClauseIdT, char16_t>::value) {
                    cache8_ = Cache8Type(S_CACHE_8_INITIAL_SIZE_);
                    cache16_ = Cache16Type(S_CACHE_16_INITIAL_SIZE_);
                    cache32_ = Cache32Type(0);
                }
                else {
                    cache8_ = Cache8Type(S_CACHE_8_INITIAL_SIZE_);
                    cache16_ = Cache16Type(S_CACHE_16_INITIAL_SIZE_);
                    cache32_ = Cache32Type(S_CACHE_32_INITIAL_SIZE_);
                }
                break;
            // Literal (resp. variable)
            case CachingScheme::SaveTypeEnum::LITERAL:
                if (((cacheType == CacheTypeEnum::COMPONENT) && std::is_same<LiteralT, char8_t>::value) ||
                    ((cacheType == CacheTypeEnum::HYPERGRAPH_CUT) && std::is_same<VarT, char8_t>::value)) {
                    cache8_ = Cache8Type(S_CACHE_8_INITIAL_SIZE_);
                    cache16_ = Cache16Type(0);
                    cache32_ = Cache32Type(0);
                }
                else if (((cacheType == CacheTypeEnum::COMPONENT) && std::is_same<LiteralT, char16_t>::value) ||
                         ((cacheType == CacheTypeEnum::HYPERGRAPH_CUT) && std::is_same<VarT, char16_t>::value)) {
                    cache8_ = Cache8Type(S_CACHE_8_INITIAL_SIZE_);
                    cache16_ = Cache16Type(S_CACHE_16_INITIAL_SIZE_);
                    cache32_ = Cache32Type(0);
                }
                else {
                    cache8_ = Cache8Type(S_CACHE_8_INITIAL_SIZE_);
                    cache16_ = Cache16Type(S_CACHE_16_INITIAL_SIZE_);
                    cache32_ = Cache32Type(S_CACHE_32_INITIAL_SIZE_);
                }
                break;
            default:
                throw Exception::NotImplementedException(CachingScheme::saveTypeEnumToString(cachingSchemeAbstractUniquePtr_->getSaveType()),
                                                         "Hydra::Cache::Cache::initializeCaches");
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::updateDataStructuresAndVariablesAfterPositiveHit(const CacheRecordStruct& cacheRecordStruct,
                                                                                                         const CacheBucketStruct& cacheBucketStruct) {
        ++numberOfPositiveHits_;
        ++variableNumberOfPositiveHits_[cacheRecordStruct.numberOfVariables];

        // Cache statistics
        totalHitCacheStatistics_.add(cacheRecordStruct.getCachedNumberOfVariables(), cacheRecordStruct.getCachedNumberOfClauses(),
                                     cacheRecordStruct.getCachedFormulaSize());
        positiveHitCacheStatistics_.add(cacheRecordStruct.getCachedNumberOfVariables(), cacheRecordStruct.getCachedNumberOfClauses(),
                                        cacheRecordStruct.getCachedFormulaSize());

        // Update the info
        cacheCleaningStrategyAbstractUniquePtr_->updateInfoForCacheBucketAfterPositiveHit(cacheBucketStruct, cacheRecordStruct);

        // Statistics
        if (cacheStatisticsPtr_) {
            cacheStatisticsPtr_->ratioOfNumberOfPositiveHitsToNumberOfHitsCounter.addCount(static_cast<Statistics::LargeNumberType>(1));

            cacheStatisticsPtr_->formulaSizePositiveHitCounter.addCount(static_cast<Statistics::LargeNumberType>(cacheRecordStruct.formulaSize));
            cacheStatisticsPtr_->numberOfVariablesPositiveHitCounter.addCount(static_cast<Statistics::LargeNumberType>(cacheRecordStruct.numberOfVariables));
            cacheStatisticsPtr_->numberOfClausesPositiveHitCounter.addCount(static_cast<Statistics::LargeNumberType>(cacheRecordStruct.numberOfClauses));
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::updateDataStructuresAndVariablesAfterNegativeHit(const CacheRecordStruct& cacheRecordStruct) noexcept {
        ++numberOfNegativeHits_;
        ++variableNumberOfNegativeHits_[cacheRecordStruct.numberOfVariables];

        // Cache statistics
        totalHitCacheStatistics_.add(cacheRecordStruct.getCachedNumberOfVariables(), cacheRecordStruct.getCachedNumberOfClauses(),
                                     cacheRecordStruct.getCachedFormulaSize());
        negativeHitCacheStatistics_.add(cacheRecordStruct.getCachedNumberOfVariables(), cacheRecordStruct.getCachedNumberOfClauses(),
                                        cacheRecordStruct.getCachedFormulaSize());

        // Statistics
        if (cacheStatisticsPtr_) {
            cacheStatisticsPtr_->ratioOfNumberOfPositiveHitsToNumberOfHitsCounter.addCount(static_cast<Statistics::LargeNumberType>(0));

            cacheStatisticsPtr_->formulaSizeNegativeHitCounter.addCount(static_cast<Statistics::LargeNumberType>(cacheRecordStruct.formulaSize));
            cacheStatisticsPtr_->numberOfVariablesNegativeHitCounter.addCount(static_cast<Statistics::LargeNumberType>(cacheRecordStruct.numberOfVariables));
            cacheStatisticsPtr_->numberOfClausesNegativeHitCounter.addCount(static_cast<Statistics::LargeNumberType>(cacheRecordStruct.numberOfClauses));
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::updateDataStructuresAndVariablesBeforeRemovingCacheBucket(const CacheBucketStruct& cacheBucketStruct,
                                                                                                                  CacheSizeTypeEnum cacheSizeType,
                                                                                                                  LargeNumberType keySize) {
        assert(keySize > 0);
        assert(numberOfEntriesTotalCache_ > 0);

        --numberOfEntriesTotalCache_;

        LargeNumberType keyByteSize = 0;
        LargeNumberType valueByteSize = computeCacheBucketByteSize(cacheBucketStruct);

        switch (cacheSizeType) {
            // Cache 8
            case CacheSizeTypeEnum::CACHE_8:
                --numberOfEntriesCache8_;

                keyByteSize = (LargeNumberType)1 * keySize;

                assert(keyByteSizeCache8_ >= keyByteSize);
                assert(valueByteSizeCache8_ >= valueByteSize);

                keyByteSizeCache8_ -= keyByteSize;
                valueByteSizeCache8_ -= valueByteSize;
                break;
            // Cache 16
            case CacheSizeTypeEnum::CACHE_16:
                --numberOfEntriesCache16_;

                keyByteSize = (LargeNumberType)2 * keySize;

                assert(keyByteSizeCache16_ >= keyByteSize);
                assert(valueByteSizeCache16_ >= valueByteSize);

                keyByteSizeCache16_ -= keyByteSize;
                valueByteSizeCache16_ -= valueByteSize;
                break;
            // Cache 32
            case CacheSizeTypeEnum::CACHE_32:
                --numberOfEntriesCache32_;

                keyByteSize = (LargeNumberType)4 * keySize;

                assert(keyByteSizeCache32_ >= keyByteSize);
                assert(valueByteSizeCache32_ >= valueByteSize);

                keyByteSizeCache32_ -= keyByteSize;
                valueByteSizeCache32_ -= valueByteSize;
                break;
            default:
                throw Exception::NotImplementedException(cacheSizeTypeEnumToString(cacheSizeType),
                                                         "Hydra::Cache::Cache::updateDataStructuresAndVariablesBeforeRemovingCacheBucket");
        }

        assert(keyByteSize != 0);

        // Mapping
        if (usedMapping_) {
            assert(numberOfEntriesMappingCache_ > 0);

            --numberOfEntriesMappingCache_;

            assert(Other::containInMap(mappingCache_, cacheBucketStruct.id));   // mapping exists in the mapping cache

            auto mappingIt = mappingCache_.find(cacheBucketStruct.id);

            LargeNumberType mappingByteSize = S_LITERAL_BYTE_SIZE_ * static_cast<LargeNumberType>(mappingIt->second.size());

            assert(keyByteSizeMappingCache_ >= S_ID_BYTE_SIZE_);
            assert(valueByteSizeMappingCache_ >= mappingByteSize);

            keyByteSizeMappingCache_ -= S_ID_BYTE_SIZE_;
            valueByteSizeMappingCache_ -= mappingByteSize;

            mappingCache_.erase(mappingIt);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    LargeNumberType Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::computeCacheBucketByteSize(const CacheBucketStruct& cacheBucketStruct) const {
        LargeNumberType cacheBucketByteSize = S_ID_BYTE_SIZE_;

        // ID node
        if constexpr (std::is_same<CacheValueT, IdNodeType>::value)
            cacheBucketByteSize += S_ID_NODE_BYTE_SIZE_;
        // mpz_int
        else if constexpr (std::is_same<CacheValueT, MpzIntType>::value)
            cacheBucketByteSize += S_LIMB_BYTE_SIZE_ * static_cast<LargeNumberType>(mpz_size(cacheBucketStruct.value.backend().data()));
        // Custom
        else if constexpr (std::is_same<CacheValueT, CustomType>::value)
            cacheBucketByteSize += cacheBucketStruct.value.getCurrentByteSize();
        // Variable vector
        else if constexpr (std::is_same<CacheValueT, VariableVectorType>::value)
            cacheBucketByteSize += S_VAR_BYTE_SIZE_ * static_cast<LargeNumberType>(cacheBucketStruct.value.capacity());
        else
            throw Exception::NotImplementedException("CacheValueT",
                                                     "Hydra::Cache::Cache::computeCacheBucketByteSize");

        return cacheBucketByteSize;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    LargeNumberType Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::maxByteSizeKey() const {
        return cachingSchemeAbstractUniquePtr_->maxByteSizeKey();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    LargeNumberType Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::maxByteSizeMapping() const {
        return cachingSchemeAbstractUniquePtr_->maxByteSizeMapping();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    LargeNumberType Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::maxByteSizeCacheBucket() const {
        LargeNumberType maxByteSizeCacheBucket = S_ID_BYTE_SIZE_;

        // ID node
        if constexpr (std::is_same<CacheValueT, IdNodeType>::value)
            maxByteSizeCacheBucket += S_ID_NODE_BYTE_SIZE_;
        // mpz_int
        else if constexpr (std::is_same<CacheValueT, MpzIntType>::value) {
            MpzIntType tmp = MpzIntType(1) << static_cast<std::size_t>(getFormulaRepresentationAbstractPtr()->getNumberOfVariablesInOriginalFormula());   // 2^|V| = max number of models

            maxByteSizeCacheBucket += S_LIMB_BYTE_SIZE_ * static_cast<LargeNumberType>(mpz_size(tmp.backend().data()));
        }
        // Custom
        else if constexpr (std::is_same<CacheValueT, CustomType>::value)
            maxByteSizeCacheBucket += S_DIGIT_CUSTOM_BYTE_SIZE_ * static_cast<LargeNumberType>(std::floor(static_cast<long double>(getFormulaRepresentationAbstractPtr()->getNumberOfVariablesInOriginalFormula()) * std::log10(2.0L))) + 1;   // |_ |V|*log_10(2) _| + 1
        // Variable vector
        else if constexpr (std::is_same<CacheValueT, VariableVectorType>::value)
            maxByteSizeCacheBucket += S_VAR_BYTE_SIZE_ * static_cast<LargeNumberType>(getFormulaRepresentationAbstractPtr()->getNumberOfVariablesInOriginalFormula());
        else
            throw Exception::NotImplementedException("CacheValueT",
                                                     "Hydra::Cache::Cache::maxByteSizeCacheBucket");

        return maxByteSizeCacheBucket;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    LargeNumberType Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::maxByteSizeEntry() const {
        LargeNumberType maxByteSizeEntry = maxByteSizeKey() + maxByteSizeCacheBucket();

        // Mapping
        if (usedMapping_)
            maxByteSizeEntry += S_ID_BYTE_SIZE_ + maxByteSizeMapping();

        return maxByteSizeEntry;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    LargeNumberType Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::currentByteSizeCache() const noexcept {
        return keyByteSizeCache8_ + valueByteSizeCache8_ +
               keyByteSizeCache16_ + valueByteSizeCache16_ +
               keyByteSizeCache32_ + valueByteSizeCache32_ +
               keyByteSizeMappingCache_ + valueByteSizeMappingCache_ +
               cacheCleaningStrategyByteSize_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    typename Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::FormulaRepresentationAbstractPtrType
    Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::getFormulaRepresentationAbstractPtr() const noexcept {
        return cachingSchemeAbstractUniquePtr_->getFormulaRepresentationAbstractPtr();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    typename Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheRecordStruct
    Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::createCacheRecordStruct(const VariableSetType& currentComponentVariableSet) const {
        assert(!currentComponentVariableSet.empty());   // at least one variable

        #ifndef NDEBUG
        for (VarT var : currentComponentVariableSet) {
            assert(!getFormulaRepresentationAbstractPtr()->isVariableAssigned(var));   // variable is not assigned
            assert(!getFormulaRepresentationAbstractPtr()->isVariableFree(var));       // variable is not free + in the current component
        }
        #endif

        // Statistics
        if (cacheStatisticsPtr_)
            cacheStatisticsPtr_->createCacheRecordStructTimer.startStopwatch();

        CacheRecordStruct cacheRecordStruct = cachingSchemeAbstractUniquePtr_->createCacheRecordStruct(currentComponentVariableSet);

        // Statistics
        if (cacheStatisticsPtr_) {
            cacheStatisticsPtr_->ratioOfNumberOfEmptyCacheRecordsToNumberOfCacheRecordsCounter.addCount(static_cast<Statistics::LargeNumberType>(cacheRecordStruct.empty ? 1 : 0));

            if (!cacheRecordStruct.empty) {
                cacheStatisticsPtr_->formulaSizeCacheRecordStructCounter.addCount(static_cast<Statistics::LargeNumberType>(cacheRecordStruct.formulaSize));
                cacheStatisticsPtr_->numberOfVariablesCacheRecordStructCounter.addCount(static_cast<Statistics::LargeNumberType>(cacheRecordStruct.numberOfVariables));
                cacheStatisticsPtr_->numberOfClausesCacheRecordStructCounter.addCount(static_cast<Statistics::LargeNumberType>(cacheRecordStruct.numberOfClauses));
                cacheStatisticsPtr_->ratioOfNumberOfRemovedClausesToNumberOfClausesCounter.addCount(static_cast<Statistics::LargeFloatingNumberType>(cacheRecordStruct.numberOfRemovedClauses) / static_cast<Statistics::LargeFloatingNumberType>(cacheRecordStruct.numberOfClauses));
            }

            cacheStatisticsPtr_->createCacheRecordStructTimer.stopStopwatch();
        }

        assert(usedMapping_ ? cacheRecordStruct.mapping.size() == cacheRecordStruct.numberOfVariables : cacheRecordStruct.mapping.size() == 0);   // mapping has valid size

        #ifndef NDEBUG
        // Check if the mapping is (variable) injective
        VariableSetType variableSetTmp(cacheRecordStruct.mapping.size());

        for (const LiteralType& lit : cacheRecordStruct.mapping)
            variableSetTmp.emplace(lit.getVariable());

        // The mapping is not (variable) injective
        if (cacheRecordStruct.mapping.size() != variableSetTmp.size()) {
            std::stringstream stringStreamTmp;

            for (VarT i = 0; i < cacheRecordStruct.mapping.size(); ++i) {
                if (i > 0)
                    stringStreamTmp << ", ";

                stringStreamTmp << std::to_string(i) << " -> " << cacheRecordStruct.mapping[i];
            }

            throw Exception::MappingIsNotInjectiveException(stringStreamTmp.str());
        }
        #endif

        #ifndef NDEBUG
        if (!cacheRecordStruct.empty) {
            assert(cacheRecordStruct.formulaSize > 0);         // non-empty formula
            assert(cacheRecordStruct.numberOfClauses > 0);     // at least one clause
            assert(cacheRecordStruct.numberOfVariables > 0);   // at least one variable

            assert(cacheRecordStruct.removedFormulaSize <= cacheRecordStruct.formulaSize);               // removed formula size
            assert(cacheRecordStruct.numberOfRemovedClauses <= cacheRecordStruct.numberOfClauses);       // number of removed clauses
            assert(cacheRecordStruct.numberOfRemovedVariables <= cacheRecordStruct.numberOfVariables);   // number of removed variables
        }
        #endif

        return cacheRecordStruct;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    typename Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheValuePtrAndIdPairOptionalType
    Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::searchInCache(const CacheRecordStruct& cacheRecordStruct) {
        // The cache record is empty
        if (cacheRecordStruct.empty)
            return std::nullopt;

        assert((!cacheRecordStruct.string8.empty() && cacheRecordStruct.string16.empty() && cacheRecordStruct.string32.empty()) ||
               (cacheRecordStruct.string8.empty() && !cacheRecordStruct.string16.empty() && cacheRecordStruct.string32.empty()) ||
               (cacheRecordStruct.string8.empty() && cacheRecordStruct.string16.empty() && !cacheRecordStruct.string32.empty()));   // valid cache record

        // Statistics
        if (cacheStatisticsPtr_)
            cacheStatisticsPtr_->searchCacheRecordStructTimer.startStopwatch();

        ++numberOfHits_;
        ++variableNumberOfHits_[cacheRecordStruct.numberOfVariables];

        IdType id = 0;
        CacheValuePtrType cacheValuePtr = nullptr;

        // Cache 8
        if (!cacheRecordStruct.string8.empty()) {
            // Positive hit
            if (auto itTmp = cache8_.find(cacheRecordStruct.string8); itTmp != cache8_.end()) {
                updateDataStructuresAndVariablesAfterPositiveHit(cacheRecordStruct, itTmp->second);

                id = itTmp->second.id;
                cacheValuePtr = &(itTmp->second.value);
            }
            // Negative hit
            else
                updateDataStructuresAndVariablesAfterNegativeHit(cacheRecordStruct);
        }
        // Cache 16
        else if (!cacheRecordStruct.string16.empty()) {
            // Positive hit
            if (auto itTmp = cache16_.find(cacheRecordStruct.string16); itTmp != cache16_.end()) {
                updateDataStructuresAndVariablesAfterPositiveHit(cacheRecordStruct, itTmp->second);

                id = itTmp->second.id;
                cacheValuePtr = &(itTmp->second.value);
            }
            // Negative hit
            else
                updateDataStructuresAndVariablesAfterNegativeHit(cacheRecordStruct);
        }
        // Cache 32
        else {
            // Positive hit
            if (auto itTmp = cache32_.find(cacheRecordStruct.string32); itTmp != cache32_.end()) {
                updateDataStructuresAndVariablesAfterPositiveHit(cacheRecordStruct, itTmp->second);

                id = itTmp->second.id;
                cacheValuePtr = &(itTmp->second.value);
            }
            // Negative hit
            else
                updateDataStructuresAndVariablesAfterNegativeHit(cacheRecordStruct);
        }

        assert(numberOfPositiveHits_ + numberOfNegativeHits_ == numberOfHits_);

        // Statistics
        if (cacheStatisticsPtr_)
            cacheStatisticsPtr_->searchCacheRecordStructTimer.stopStopwatch();

        // Not found
        if (!cacheValuePtr)
            return std::nullopt;

        // Found
        return CacheValuePtrAndIdPairOptionalType { std::make_pair(cacheValuePtr, id) };
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::addCacheRecordToCache(CacheRecordStruct&& cacheRecordStruct, CacheValueT&& cacheValue) {
        // The cache record is empty
        if (cacheRecordStruct.empty)
            return;

        assert((!cacheRecordStruct.string8.empty() && cacheRecordStruct.string16.empty() && cacheRecordStruct.string32.empty()) ||
               (cacheRecordStruct.string8.empty() && !cacheRecordStruct.string16.empty() && cacheRecordStruct.string32.empty()) ||
               (cacheRecordStruct.string8.empty() && cacheRecordStruct.string16.empty() && !cacheRecordStruct.string32.empty()));   // valid cache record

        // There is already a cache record with the same key in the cache (can happen due to recursion)
        if ((!cacheRecordStruct.string8.empty() && (cache8_.find(cacheRecordStruct.string8) != cache8_.end())) ||
            (!cacheRecordStruct.string16.empty() && (cache16_.find(cacheRecordStruct.string16) != cache16_.end())) ||
            (!cacheRecordStruct.string32.empty() && (cache32_.find(cacheRecordStruct.string32) != cache32_.end()))) {
            #ifndef NDEBUG
                #if defined(CARA_SOLVER)
                // Check that the number of models is the same
                if (cachingSchemeAbstractUniquePtr_->getCacheType() == CacheTypeEnum::COMPONENT) {
                    // Cache 8
                    if (!cacheRecordStruct.string8.empty())
                        assert(cache8_.find(cacheRecordStruct.string8)->second.value == cacheValue);
                    // Cache 16
                    else if (!cacheRecordStruct.string16.empty())
                        assert(cache16_.find(cacheRecordStruct.string16)->second.value == cacheValue);
                    // Cache 32
                    else
                        assert(cache32_.find(cacheRecordStruct.string32)->second.value == cacheValue);
                }
                #endif
            #endif

            return;
        }

        assert(id_counter_ < std::numeric_limits<IdType>::max());   // not too many identifiers

        // Statistics
        if (cacheStatisticsPtr_)
            cacheStatisticsPtr_->addCacheRecordStructTimer.startStopwatch();

        // Create a cache bucket
        CacheBucketStruct cacheBucketStruct(id_counter_);
        cacheBucketStruct.value = std::move(cacheValue);

        ++id_counter_;
        ++numberOfEntriesTotalCache_;

        cacheCleaningStrategyAbstractUniquePtr_->createInfoForNewCacheBucket(cacheBucketStruct, cacheRecordStruct);

        // Mapping
        if (usedMapping_) {
            ++numberOfEntriesMappingCache_;

            // The mapping cache is too big
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(numberOfEntriesMappingCache_))
                throw Exception::Cache::MappingCacheIsTooBigException();

            assert(!cacheRecordStruct.mapping.empty());

            LargeNumberType mappingByteSizeTmp = S_LITERAL_BYTE_SIZE_ * static_cast<LargeNumberType>(cacheRecordStruct.mapping.size());

            keyByteSizeMappingCache_ += S_ID_BYTE_SIZE_;
            valueByteSizeMappingCache_ += mappingByteSizeTmp;

            mappingCache_.insert({ cacheBucketStruct.id, std::move(cacheRecordStruct.mapping) });
        }

        LargeNumberType cacheBucketByteSize = computeCacheBucketByteSize(cacheBucketStruct);

        // Cache 8
        if (!cacheRecordStruct.string8.empty()) {
            ++numberOfEntriesCache8_;

            // The cache is too big
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(numberOfEntriesCache8_))
                throw Exception::Cache::CacheIsTooBigException(CacheSizeTypeEnum::CACHE_8);

            LargeNumberType keyByteSizeTmp = (LargeNumberType)1 * static_cast<LargeNumberType>(cacheRecordStruct.string8.size());
            keyByteSizeCache8_ += keyByteSizeTmp;
            valueByteSizeCache8_ += cacheBucketByteSize;

            cache8_.insert({ std::move(cacheRecordStruct.string8), std::move(cacheBucketStruct) });
        }
        // Cache 16
        else if (!cacheRecordStruct.string16.empty()) {
            ++numberOfEntriesCache16_;

            // The cache is too big
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(numberOfEntriesCache16_))
                throw Exception::Cache::CacheIsTooBigException(CacheSizeTypeEnum::CACHE_16);

            LargeNumberType keyByteSizeTmp = (LargeNumberType)2 * static_cast<LargeNumberType>(cacheRecordStruct.string16.size());
            keyByteSizeCache16_ += keyByteSizeTmp;
            valueByteSizeCache16_ += cacheBucketByteSize;

            cache16_.insert({ std::move(cacheRecordStruct.string16), std::move(cacheBucketStruct) });
        }
        // Cache 32
        else {
            ++numberOfEntriesCache32_;

            // The cache is too big
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(numberOfEntriesCache32_))
                throw Exception::Cache::CacheIsTooBigException(CacheSizeTypeEnum::CACHE_32);

            LargeNumberType keyByteSizeTmp = (LargeNumberType)4 * static_cast<LargeNumberType>(cacheRecordStruct.string32.size());
            keyByteSizeCache32_ += keyByteSizeTmp;
            valueByteSizeCache32_ += cacheBucketByteSize;

            cache32_.insert({ std::move(cacheRecordStruct.string32), std::move(cacheBucketStruct) });
        }

        // Statistics
        if (cacheStatisticsPtr_)
            cacheStatisticsPtr_->addCacheRecordStructTimer.stopStopwatch();

        // Cache cleaning strategy
        if (cacheCleaningStrategyAbstractUniquePtr_->shouldCacheBeCleaned()) {
            // Statistics
            if (cacheStatisticsPtr_)
                cacheStatisticsPtr_->cleanCacheTimer.startStopwatch();

            cacheCleaningStrategyAbstractUniquePtr_->cleanCache();

            // Statistics
            if (cacheStatisticsPtr_)
                cacheStatisticsPtr_->cleanCacheTimer.stopStopwatch();
        }

        assert(keyByteSizeCache8_ % 1 == 0);
        assert(keyByteSizeCache16_ % 2 == 0);
        assert(keyByteSizeCache32_ % 4 == 0);

        assert((LargeNumberType)cache8_.size() == numberOfEntriesCache8_);
        assert((LargeNumberType)cache16_.size() == numberOfEntriesCache16_);
        assert((LargeNumberType)cache32_.size() == numberOfEntriesCache32_);
        assert((LargeNumberType)mappingCache_.size() == numberOfEntriesMappingCache_);

        assert(numberOfEntriesCache8_ + numberOfEntriesCache16_ + numberOfEntriesCache32_ == numberOfEntriesTotalCache_);
        assert(usedMapping_ ? numberOfEntriesTotalCache_ == numberOfEntriesMappingCache_ : numberOfEntriesMappingCache_ == 0);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    typename Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::MappingFromVariableToLiteralType
    Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::createMapping(IdType id, const CacheRecordStruct& cacheRecordStruct) const {
        // Mapping is not used
        if (!usedMapping_)
            return {};

        assert(Other::containInMap(mappingCache_, id));

        const LiteralVectorType& cacheBucketMapping = mappingCache_.at(id);
        const LiteralVectorType& cacheRecordMapping = cacheRecordStruct.mapping;

        assert(cacheBucketMapping.size() == cacheRecordMapping.size());   // both mappings have the same size

        bool isIdentical = true;
        MappingFromVariableToLiteralType mapping(cacheBucketMapping.size());

        for (VarT i = 0; i < cacheBucketMapping.size(); ++i) {
            const LiteralType& litBucket = cacheBucketMapping[i];
            const LiteralType& litRecord = cacheRecordMapping[i];

            LiteralType lit(litRecord.getVariable(), litBucket.isPositive() ? litRecord.isPositive() : litRecord.isNegative());

            if (!isIdentical || litBucket.getVariable() != lit.getVariable() || lit.isNegative())
                isIdentical = false;

            mapping.insert({ litBucket.getVariable(), std::move(lit) });
        }

        // Statistics
        if (cacheStatisticsPtr_)
            cacheStatisticsPtr_->ratioOfNumberOfIdenticalMappingsToNumberOfMappingsCounter.addCount(static_cast<LargeNumberType>(isIdentical ? 1 : 0));

        // The mapping is identical
        if (isIdentical)
            return {};

        return mapping;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::setStatisticsAfterCompilation() const {
        // Statistics
        if (cacheStatisticsPtr_) {
            cacheStatisticsPtr_->numberOfCurrentEntriesNumber.setNumber(static_cast<Statistics::LargeNumberType>(numberOfEntriesTotalCache_));
            cacheStatisticsPtr_->numberOfDeletedEntriesNumber.setNumber(static_cast<Statistics::LargeNumberType>(cacheCleaningStrategyAbstractUniquePtr_->getNumberOfDeletedEntries()));
            cacheStatisticsPtr_->numberOfCacheCleaningsNumber.setNumber(static_cast<Statistics::LargeNumberType>(cacheCleaningStrategyAbstractUniquePtr_->getNumberOfCacheCleanings()));
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    const Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheStatisticsStruct&
    Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::getTotalHitCacheStatistics() const noexcept {
        return totalHitCacheStatistics_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    const Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheStatisticsStruct&
    Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::getPositiveHitCacheStatistics() const noexcept {
        return positiveHitCacheStatistics_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    const Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheStatisticsStruct&
    Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::getNegativeHitCacheStatistics() const noexcept {
        return negativeHitCacheStatistics_;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    template <typename CacheT, typename StringT>
    void Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::printCacheDebug(std::ostream& out, const CacheT& cache) const {
        // Empty cache
        if (cache.empty()) {
            out << "Empty" << std::endl;
            return;
        }

        Other::HashMap::MapType<IdType, const StringT*> structure(cache.size());

        // Fill the structure
        for (const auto& [key, value] : cache)
            structure.insert({ value.id, &key });

        IdSortedVectorType idSortedVector = Other::extractKeysFromMap(structure, true);

        for (IdType id : idSortedVector) {
            const StringT* key = structure[id];
            const CacheBucketStruct& cacheBucketStruct = cache.at(*key);

            // Key
            out << "Key:";
            for (auto c : *key)
                out << " " << std::to_string(c);
            out << std::endl;

            // Cache bucket structure
            cacheBucketStruct.printCacheBucketStruct(out);

            // Mapping
            if (usedMapping_) {
                assert(Other::containInMap(mappingCache_, id));

                const LiteralVectorType& mapping = mappingCache_.at(id);

                out << "Mapping:";
                for (const LiteralType& lit : mapping)
                    out << " " << lit;
                out << std::endl;
            }

            out << "---" << std::endl;
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::printCacheDebug(std::ostream& out, bool printCurrentFormula, bool printCaches,
                                                                        bool printVariableNumberOfHits, bool printCacheStatistics) const {
        out << "Cache" << std::endl;

        // Total cache
        out << "Total cache" << std::endl;
        out << "\tsize (bytes): " << std::to_string(currentByteSizeCache()) << std::endl;
        out << "\tnumber of entries: " << std::to_string(numberOfEntriesTotalCache_) << std::endl;

        // Cache 8
        out << cacheSizeTypeEnumToString(CacheSizeTypeEnum::CACHE_8) << std::endl;
        out << "\tkey size (bytes): " << std::to_string(keyByteSizeCache8_) << std::endl;
        out << "\tvalue size (bytes): " << std::to_string(valueByteSizeCache8_) << std::endl;
        out << "\tnumber of entries: " << std::to_string(numberOfEntriesCache8_) << std::endl;

        // Cache 16
        out << cacheSizeTypeEnumToString(CacheSizeTypeEnum::CACHE_16) << std::endl;
        out << "\tkey size (bytes): " << std::to_string(keyByteSizeCache16_) << std::endl;
        out << "\tvalue size (bytes): " << std::to_string(valueByteSizeCache16_) << std::endl;
        out << "\tnumber of entries: " << std::to_string(numberOfEntriesCache16_) << std::endl;

        // Cache 32
        out << cacheSizeTypeEnumToString(CacheSizeTypeEnum::CACHE_32) << std::endl;
        out << "\tkey size (bytes): " << std::to_string(keyByteSizeCache32_) << std::endl;
        out << "\tvalue size (bytes): " << std::to_string(valueByteSizeCache32_) << std::endl;
        out << "\tnumber of entries: " << std::to_string(numberOfEntriesCache32_) << std::endl;

        // The mapping cache
        if (usedMapping_) {
            out << "Mapping cache" << std::endl;
            out << "\tkey size (bytes): " << std::to_string(keyByteSizeMappingCache_) << std::endl;
            out << "\tvalue size (bytes): " << std::to_string(valueByteSizeMappingCache_) << std::endl;
            out << "\tnumber of entries: " << std::to_string(numberOfEntriesMappingCache_) << std::endl;
        }

        out << std::endl;

        // Hits
        out << "Number of hits: " << std::to_string(numberOfHits_) << std::endl;
        out << "Number of positive hits: " << std::to_string(numberOfPositiveHits_) << std::endl;
        out << "Number of negative hits: " << std::to_string(numberOfNegativeHits_) << std::endl;
        out << std::endl;

        // Variables - hits
        if (printVariableNumberOfHits) {
            out << "Number of hits (variables):";
            for (LargeNumberType numberOfHits : variableNumberOfHits_)
                out << " " << std::to_string(numberOfHits);
            out << std::endl;

            // Variables - positive hits
            out << "Number of positive hits (variables):";
            for (LargeNumberType numberOfPositiveHits : variableNumberOfPositiveHits_)
                out << " " << std::to_string(numberOfPositiveHits);
            out << std::endl;

            // Variables - negative hits
            out << "Number of negative hits (variables):";
            for (LargeNumberType numberOfNegativeHits : variableNumberOfNegativeHits_)
                out << " " << std::to_string(numberOfNegativeHits);
            out << std::endl;
            out << std::endl;
        }

        // Cache statistics
        if (printCacheStatistics) {
            out << "Total hit - ";
            totalHitCacheStatistics_.printCacheStatisticsStruct(out);
            out << std::endl;

            out << "Positive hit - ";
            positiveHitCacheStatistics_.printCacheStatisticsStruct(out);
            out << std::endl;

            out << "Negative hit - ";
            negativeHitCacheStatistics_.printCacheStatisticsStruct(out);
            out << std::endl;
        }

        // Caching scheme
        cachingSchemeAbstractUniquePtr_->printCachingSchemeDebug(out, printCurrentFormula);
        out << std::endl;

        // Cache cleaning strategy
        cacheCleaningStrategyAbstractUniquePtr_->printCacheCleaningStrategyDebug(out);
        out << std::endl;

        // Print the caches
        if (printCaches) {
            out << "Caches" << std::endl;

            // Cache 8
            out << cacheSizeTypeEnumToString(CacheSizeTypeEnum::CACHE_8) << std::endl;
            printCacheDebug<Cache8Type, String8Type>(out, cache8_);
            out << std::endl;

            // Cache 16
            out << cacheSizeTypeEnumToString(CacheSizeTypeEnum::CACHE_16) << std::endl;
            printCacheDebug<Cache16Type, String16Type>(out, cache16_);
            out << std::endl;

            // Cache 32
            out << cacheSizeTypeEnumToString(CacheSizeTypeEnum::CACHE_32) << std::endl;
            printCacheDebug<Cache32Type, String32Type>(out, cache32_);
            out << std::endl;
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::printCachingSchemeDebug(std::ostream& out, bool printCurrentFormula) const {
        cachingSchemeAbstractUniquePtr_->printCachingSchemeDebug(out, printCurrentFormula);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::printCacheCleaningStrategyDebug(std::ostream& out) const {
        cacheCleaningStrategyAbstractUniquePtr_->printCacheCleaningStrategyDebug(out);
    }
    #endif
}   // namespace Hydra::Cache
