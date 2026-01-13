#pragma once

#include "./CachingSchemeAbstract.hpp"

namespace Hydra::Cache::CachingScheme {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    LargeNumberType CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::maxByteSizeMapping() const {
        return (LargeNumberType)formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula() * (LargeNumberType)sizeof(LiteralT);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::getUsedMapping() const noexcept {
        return usedMapping_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    SaveTypeEnum CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::getSaveType() const noexcept {
        return saveType_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    CacheTypeEnum CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::getCacheType() const noexcept {
        return cacheType_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType
    CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::getFormulaRepresentationAbstractPtr() const noexcept {
        return formulaRepresentationAbstractPtr_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    template <typename CharT>
    void CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::createSortedKeyWithMapping(std::basic_string<CharT>& string,
                                                                                      ClauseIdReusableVectorType& clauseIdReusableVector,
                                                                                      const LiteralVectorType& variableToLiteralVectorMapping,
                                                                                      FormulaSizeType totalClausesSize) const {
        // Initialize local auxiliary data structures
        if (l_firstCall_createSortedKeyWithMapping_) {
            l_clauseMetadataVector_createSortedKeyWithMapping_ = ClauseMetadataVectorType(formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses());
            l_mappedFormulaReusableVector_createSortedKeyWithMapping_ = LiteralReusableVectorType(formulaRepresentationAbstractPtr_->getOriginalFormulaSize());

            l_firstCall_createSortedKeyWithMapping_ = false;
        }

        assert(string.empty());   // empty key

        string.reserve(totalClausesSize + clauseIdReusableVector.size());

        l_mappedFormulaReusableVector_createSortedKeyWithMapping_.clear();

        // Remap the clauses
        // Precompute metadata for clauses
        FormulaSizeType currentOffset = 0;
        for (ClauseIdT clauseId : clauseIdReusableVector) {
            assert(clauseId < l_clauseMetadataVector_createSortedKeyWithMapping_.size());

            ClauseMetadataStruct& clauseMetadata = l_clauseMetadataVector_createSortedKeyWithMapping_[clauseId];

            // Clause size
            ClauseSizeType clauseSize = formulaRepresentationAbstractPtr_->getCurrentClauseSize(clauseId);
            clauseMetadata.clauseSize = clauseSize;

            // Clause iterating
            for (auto clauseIt = formulaRepresentationAbstractPtr_->beginClause(clauseId);
                 clauseIt != this->formulaRepresentationAbstractPtr_->endClause(); ++clauseIt) {
                VarT var = clauseIt->getVariable();

                #ifndef NDEBUG
                // The variable does not exist in the mapping
                if (variableToLiteralVectorMapping[var].isZeroLiteral()) {
                    VariableSortedVectorType tmp = Other::extractKeysFromVectorMapping<VarT, LiteralType>(variableToLiteralVectorMapping,
                                                                                                          Formula::createZeroLiteral<VarT, LiteralT>());
                    std::stringstream stringStreamTmp = Other::createStringStreamFromContainerWithToStringConversion(tmp.cbegin(), tmp.cend());

                    throw Exception::VariableDoesNotExistInMappingException(var, stringStreamTmp.str());
                }
                #endif

                const LiteralType& mappedLit = variableToLiteralVectorMapping[var];
                assert(!mappedLit.isZeroLiteral());

                l_mappedFormulaReusableVector_createSortedKeyWithMapping_.emplace_back(mappedLit.getVariable(),
                                                                                       mappedLit.isPositive() ? clauseIt->isPositive() : clauseIt->isNegative());
            }

            // Begin iterator
            auto it = l_mappedFormulaReusableVector_createSortedKeyWithMapping_.cbegin();
            std::advance(it, currentOffset);
            clauseMetadata.beginIt = it;

            // End iterator
            std::advance(it, clauseSize);
            clauseMetadata.endIt = it;

            currentOffset += clauseSize;

            assert(it == l_mappedFormulaReusableVector_createSortedKeyWithMapping_.cend());   // valid iterator

            // Sort the clause
            std::sort(l_mappedFormulaReusableVector_createSortedKeyWithMapping_.end() - clauseSize, l_mappedFormulaReusableVector_createSortedKeyWithMapping_.end());
        }

        assert(l_mappedFormulaReusableVector_createSortedKeyWithMapping_.size() == totalClausesSize);

        /**
         * Return true if clauseId1 < clauseId2. Otherwise, false is returned.
         */
        auto comparatorLambda = [this](ClauseIdT clauseId1, ClauseIdT clauseId2) -> bool {
            const ClauseMetadataStruct& clause1Metadata = l_clauseMetadataVector_createSortedKeyWithMapping_[clauseId1];
            const ClauseMetadataStruct& clause2Metadata = l_clauseMetadataVector_createSortedKeyWithMapping_[clauseId2];

            if (clause1Metadata.clauseSize != clause2Metadata.clauseSize)
                return (clause1Metadata.clauseSize < clause2Metadata.clauseSize);

            for (auto clause1It = clause1Metadata.beginIt, clause2It = clause2Metadata.beginIt; clause1It != clause1Metadata.endIt; ++clause1It, ++clause2It) {
                const LiteralType& lit1 = *clause1It;
                const LiteralType& lit2 = *clause2It;

                if (lit1 < lit2)
                    return true;

                if (lit1 > lit2)
                    return false;
            }

            return false;
        };

        /**
         * Return true if clauseId1 < clauseId2. Otherwise, false is returned.
         * Note: only variables are considered, not literals
         */
        auto variableComparatorLambda = [this](ClauseIdT clauseId1, ClauseIdT clauseId2) -> bool {
            const ClauseMetadataStruct& clause1Metadata = l_clauseMetadataVector_createSortedKeyWithMapping_[clauseId1];
            const ClauseMetadataStruct& clause2Metadata = l_clauseMetadataVector_createSortedKeyWithMapping_[clauseId2];

            if (clause1Metadata.clauseSize != clause2Metadata.clauseSize)
                return (clause1Metadata.clauseSize < clause2Metadata.clauseSize);

            for (auto clause1It = clause1Metadata.beginIt, clause2It = clause2Metadata.beginIt; clause1It != clause1Metadata.endIt; ++clause1It, ++clause2It) {
                VarT var1 = clause1It->getVariable();
                VarT var2 = clause2It->getVariable();

                if (var1 < var2)
                    return true;

                if (var1 > var2)
                    return false;
            }

            return false;
        };

        // Sort the clauses
        switch (cacheType_) {
            case CacheTypeEnum::COMPONENT:
                #ifndef NDEBUG
                std::stable_sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(), comparatorLambda);
                #else
                std::sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(), comparatorLambda);
                #endif
                break;
            case CacheTypeEnum::HYPERGRAPH_CUT:
                #ifndef NDEBUG
                std::stable_sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(), variableComparatorLambda);
                #else
                std::sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(), variableComparatorLambda);
                #endif
                break;
            default:
                throw Exception::NotImplementedException(cacheTypeEnumToString(cacheType_),
                                                         "Hydra::Cache::CachingScheme::CachingSchemeAbstract::createSortedKeyWithMapping");
        }

        LiteralType zeroLit = Formula::createZeroLiteral<VarT, LiteralT>();

        // Create the sorted key
        switch (cacheType_) {
            // Component caching
            case CacheTypeEnum::COMPONENT:
                for (ClauseIdT clauseId : clauseIdReusableVector) {
                    const ClauseMetadataStruct& clauseMetadata = l_clauseMetadataVector_createSortedKeyWithMapping_[clauseId];

                    for (auto clauseIt = clauseMetadata.beginIt; clauseIt != clauseMetadata.endIt; ++clauseIt)
                        string.push_back(static_cast<CharT>(clauseIt->getLiteralT()));

                    string.push_back(static_cast<CharT>(zeroLit.getLiteralT()));
                }

                break;
            // Hypergraph cut caching
            case CacheTypeEnum::HYPERGRAPH_CUT:
                for (ClauseIdT clauseId : clauseIdReusableVector) {
                    const ClauseMetadataStruct& clauseMetadata = l_clauseMetadataVector_createSortedKeyWithMapping_[clauseId];

                    for (auto clauseIt = clauseMetadata.beginIt; clauseIt != clauseMetadata.endIt; ++clauseIt)
                        string.push_back(static_cast<CharT>(clauseIt->getVariable()));

                    string.push_back(static_cast<CharT>(zeroLit.getLiteralT()));
                }

                break;
            default:
                throw Exception::NotImplementedException(cacheTypeEnumToString(cacheType_),
                                                         "Hydra::Cache::CachingScheme::CachingSchemeAbstract::createSortedKeyWithMapping");
        }
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::printCachingSchemeDebug(std::ostream& out, bool printCurrentFormula) const {
        out << "Caching scheme" << std::endl;
        out << "Type: " << cachingSchemeTypeEnumToString(cachingSchemeType_) << std::endl;
        out << "Cache type: " << cacheTypeEnumToString(cacheType_) << std::endl;
        out << "Used mapping: " << std::to_string(usedMapping_) << std::endl;

        // Omit clause type
        if (omitClauseType_ != OmitClauseTypeEnum::NONE)
            out << "Omit clause type: " << omitClauseTypeEnumToString(omitClauseType_) << std::endl;

        // The number of discarded cache records
        if (numberOfDiscardedCacheRecords_ > 0)
            out << "Number of discarded cache records: " << std::to_string(numberOfDiscardedCacheRecords_) << std::endl;

        // Current formula
        if (printCurrentFormula) {
            out << "Current formula: ";
            formulaRepresentationAbstractPtr_->printCurrentFormulaDebug(out);
            out << std::endl;
        }

        // Caching scheme
        this->processPrintCachingSchemeDebug(out);
    }
    #endif
}   // namespace Hydra::Cache::CachingScheme
