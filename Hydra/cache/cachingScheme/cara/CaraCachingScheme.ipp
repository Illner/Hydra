#pragma once

#include "./CaraCachingScheme.hpp"

namespace Hydra::Cache::CachingScheme::Cara {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CaraCachingScheme<VarT, LiteralT, ClauseIdT>::initializePrecomputedSampleMoments(ClauseSizeType maxOriginalClauseSize) noexcept {
        for (std::size_t clauseSize = 1; clauseSize <= maxOriginalClauseSize; ++clauseSize) {
            LargeNumberType valueTmp = 1;

            for (std::size_t k = 1; k <= configuration_.numberOfSampleMoments; ++k) {
                valueTmp *= clauseSize;
                l_precomputedSampleMoments_createSampleMomentDataStructure_[clauseSize][k] = valueTmp;
            }
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    LargeNumberType CaraCachingScheme<VarT, LiteralT, ClauseIdT>::maxByteSizeKey() const {
        LargeNumberType value = (LargeNumberType)this->formulaRepresentationAbstractPtr_->getOriginalFormulaSize() +
                                (LargeNumberType)this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses();

        switch (this->cacheType_) {
            case CacheTypeEnum::COMPONENT:
                return value * (LargeNumberType)sizeof(LiteralT);
            case CacheTypeEnum::HYPERGRAPH_CUT:
                return value * (LargeNumberType)sizeof(VarT);
            default:
                throw Exception::NotImplementedException(cacheTypeEnumToString(this->cacheType_),
                                                         "Hydra::Cache::CachingScheme::Cara::CaraCachingScheme::maxByteSizeKey");
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename CaraCachingScheme<VarT, LiteralT, ClauseIdT>::CacheRecordStruct
    CaraCachingScheme<VarT, LiteralT, ClauseIdT>::createCacheRecordStruct(const VariableSetType& currentComponentVariableSet) const {
        CacheRecordStruct cacheRecordStruct;

        assert(this->formulaRepresentationAbstractPtr_->getCurrentComponentFormulaSize(currentComponentVariableSet) > 0);   // non-empty formula

        auto processNotSubsumedClausesLambda = [this, &currentComponentVariableSet]() -> bool {
            this->formulaRepresentationAbstractPtr_->getCurrentComponentNotSubsumedClauses(currentComponentVariableSet, l_clauseIdReusableVector_,
                                                                                           l_usedVariableVectorSet_createCacheRecordStruct_, true,
                                                                                           (this->cacheType_ == CacheTypeEnum::HYPERGRAPH_CUT), false);

            // Invalid cache record
            if (l_usedVariableVectorSet_createCacheRecordStruct_.size() < currentComponentVariableSet.size()) {
                // Discard the cache record
                if (configuration_.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing) {
                    ++this->numberOfDiscardedCacheRecords_;

                    return true;
                }

                // Get the not duplicate clauses instead
                this->formulaRepresentationAbstractPtr_->getCurrentComponentNotDuplicateClauses(currentComponentVariableSet, l_clauseIdReusableVector_,
                                                                                                (this->cacheType_ == CacheTypeEnum::HYPERGRAPH_CUT), false);
            }

            return false;
        };

        bool discardCacheRecord = false;   // for not subsumed clauses preprocessing

        switch (configuration_.preprocessingType) {
            // None
            case PreprocessingTypeEnum::NONE:
                this->formulaRepresentationAbstractPtr_->getCurrentComponentClauses(currentComponentVariableSet, l_clauseIdReusableVector_, false);
                break;
            // Not duplicate clauses
            case PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES:
                this->formulaRepresentationAbstractPtr_->getCurrentComponentNotDuplicateClauses(currentComponentVariableSet, l_clauseIdReusableVector_,
                                                                                                (this->cacheType_ == CacheTypeEnum::HYPERGRAPH_CUT), false);
                break;
            // Not subsumed clauses
            case PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES:
                #if defined(BELLA_COMPILER)
                discardCacheRecord = processNotSubsumedClausesLambda();
                #elif defined(CARA_SOLVER)
                switch (this->cacheType_) {
                    // Hypergraph cut caching
                    case CacheTypeEnum::HYPERGRAPH_CUT:
                        discardCacheRecord = processNotSubsumedClausesLambda();
                        break;
                    // Component caching
                    case CacheTypeEnum::COMPONENT:
                        this->formulaRepresentationAbstractPtr_->getCurrentComponentNotSubsumedClauses(currentComponentVariableSet, l_clauseIdReusableVector_,
                                                                                                       l_usedVariableVectorSet_createCacheRecordStruct_, false,
                                                                                                       false, false);
                        break;
                    default:
                        throw Exception::NotImplementedException(cacheTypeEnumToString(this->cacheType_),
                                                                 "Hydra::Cache::CachingScheme::Cara::CaraCachingScheme::createCacheRecordStruct");
                }
                #endif

                if (discardCacheRecord) {
                    cacheRecordStruct.empty = true;
                    return cacheRecordStruct;
                }

                break;
            default:
                throw Exception::NotImplementedException(preprocessingTypeEnumToString(configuration_.preprocessingType),
                                                         "Hydra::Cache::CachingScheme::Cara::CaraCachingScheme::createCacheRecordStruct");
        }

        cacheRecordStruct.empty = false;
        cacheRecordStruct.maxClauseSize = 0;
        cacheRecordStruct.numberOfRemovedVariables = 0;
        cacheRecordStruct.numberOfVariables = static_cast<VarT>(currentComponentVariableSet.size());
        cacheRecordStruct.formulaSize = this->formulaRepresentationAbstractPtr_->getCurrentComponentFormulaSize(currentComponentVariableSet);
        cacheRecordStruct.removedFormulaSize = cacheRecordStruct.formulaSize;
        cacheRecordStruct.numberOfClauses = this->formulaRepresentationAbstractPtr_->getNumberOfCurrentComponentClauses(currentComponentVariableSet);
        cacheRecordStruct.numberOfRemovedClauses = (cacheRecordStruct.numberOfClauses - static_cast<ClauseIdT>(l_clauseIdReusableVector_.size()));

        #ifndef NDEBUG
        l_clauseIdReusableVector_.sort();
        #endif

        assert(!l_clauseIdReusableVector_.empty());   // at least one clause

        FormulaSizeType totalClausesSize = 0;

        createSampleMomentDataStructure(currentComponentVariableSet, cacheRecordStruct.maxClauseSize, totalClausesSize);

        // Formula size
        assert(cacheRecordStruct.removedFormulaSize >= totalClausesSize);
        cacheRecordStruct.removedFormulaSize -= totalClausesSize;

        /**
         * Return true if var1 < var2 based on the sample moments. Otherwise, false is returned.
         */
        auto sampleMomentComparatorLambda = [this](VarT var1, VarT var2) -> bool {
            // Can happen
            if (var1 == var2)
                return false;

            const SampleMomentType& sampleMomentVar1 = l_sampleMomentVector_[l_variableToIndexVectorMapping_[var1]];
            const SampleMomentType& sampleMomentVar2 = l_sampleMomentVector_[l_variableToIndexVectorMapping_[var2]];

            assert(sampleMomentVar1.back() == (LargeNumberType)var1);
            assert(sampleMomentVar2.back() == (LargeNumberType)var2);
            assert(sampleMomentVar1.size() == sampleMomentVar2.size());

            for (std::size_t i = 0; i < sampleMomentVar1.size(); ++i) {
                if (sampleMomentVar1[i] < sampleMomentVar2[i])
                    return true;

                if (sampleMomentVar1[i] > sampleMomentVar2[i])
                    return false;
            }

            assert(false);   // both vectors MUST differ because of the variable identifiers

            return false;
        };

        // Sort the variables based on the sample moment data structure
        l_variableSortedReusableVector_createCacheRecordStruct_.copySet(currentComponentVariableSet);
        std::sort(l_variableSortedReusableVector_createCacheRecordStruct_.begin(), l_variableSortedReusableVector_createCacheRecordStruct_.end(),
                  sampleMomentComparatorLambda);

        // Create the mapping(s)
        VarT indexTmp = 1;
        if (this->usedMapping_)
            cacheRecordStruct.mapping.reserve(l_variableSortedReusableVector_createCacheRecordStruct_.size());
        for (VarT var : l_variableSortedReusableVector_createCacheRecordStruct_) {
            const SampleMomentType& sampleMoment = l_sampleMomentVector_[l_variableToIndexVectorMapping_[var]];

            assert(sampleMoment.size() >= 3);   // number of positive occurrences, number of negative occurrences, ..., variable identifier

            if (configuration_.preprocessingType == PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES) {
                // The variable is free because of subsumption
                if ((sampleMoment[0] == 0) && (sampleMoment[1] == 0)) {
                    --cacheRecordStruct.numberOfVariables;
                    ++cacheRecordStruct.numberOfRemovedVariables;

                    continue;
                }
            }

            bool isPositive = true;

            // Variable to literal mapping is used
            if (configuration_.useVariableToLiteralMapping) {
                // Number of positive occurrences < number of negative occurrences
                if (sampleMoment[0] < sampleMoment[1])
                    isPositive = false;
            }

            if (this->usedMapping_)
                cacheRecordStruct.mapping.emplace_back(var, isPositive);
            l_variableToLiteralVectorMapping_createCacheRecordStruct_[var] = LiteralType(indexTmp, isPositive);

            ++indexTmp;
        }

        assert((cacheRecordStruct.numberOfVariables + cacheRecordStruct.numberOfRemovedVariables) == l_variableSortedReusableVector_createCacheRecordStruct_.size());

        // char8_t
        if (((this->cacheType_ == CacheTypeEnum::COMPONENT) && Other::literalsCanBeSavedAsTypeT<char8_t>(cacheRecordStruct.numberOfVariables)) ||
            ((this->cacheType_ == CacheTypeEnum::HYPERGRAPH_CUT) && Other::variablesCanBeSavedAsTypeT<char8_t>(cacheRecordStruct.numberOfVariables)))
            this->createSortedKeyWithMapping(cacheRecordStruct.string8, l_clauseIdReusableVector_,
                                             l_variableToLiteralVectorMapping_createCacheRecordStruct_, totalClausesSize);
        // char16_t
        else if (((this->cacheType_ == CacheTypeEnum::COMPONENT) && Other::literalsCanBeSavedAsTypeT<char16_t>(cacheRecordStruct.numberOfVariables)) ||
                 ((this->cacheType_ == CacheTypeEnum::HYPERGRAPH_CUT) && Other::variablesCanBeSavedAsTypeT<char16_t>(cacheRecordStruct.numberOfVariables)))
            this->createSortedKeyWithMapping(cacheRecordStruct.string16, l_clauseIdReusableVector_,
                                             l_variableToLiteralVectorMapping_createCacheRecordStruct_, totalClausesSize);
        // char32_t
        else
            this->createSortedKeyWithMapping(cacheRecordStruct.string32, l_clauseIdReusableVector_,
                                             l_variableToLiteralVectorMapping_createCacheRecordStruct_, totalClausesSize);

        #ifndef NDEBUG
        if (this->usedMapping_)
            assert(static_cast<VarT>(cacheRecordStruct.mapping.size()) == cacheRecordStruct.numberOfVariables);
        #endif

        return cacheRecordStruct;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CaraCachingScheme<VarT, LiteralT, ClauseIdT>::createSampleMomentDataStructure(const VariableSetType& currentComponentVariableSet,
                                                                                       ClauseSizeType& maxClauseSize, FormulaSizeType& totalClausesSize) const {
        assert(maxClauseSize == 0);
        assert(totalClausesSize == 0);

        // Initialize the mapping and sample moments
        VarT indexTmp = 0;
        #ifndef NDEBUG
        for (VarT var : Other::sortUnorderedSet(currentComponentVariableSet)) {
        #else
        for (VarT var : currentComponentVariableSet) {
        #endif
            l_variableToIndexVectorMapping_[var] = indexTmp;

            // Clear the sample moments for the variable
            std::fill(l_sampleMomentVector_[indexTmp].begin(), l_sampleMomentVector_[indexTmp].end(), 0);
            l_sampleMomentVector_[indexTmp].back() = static_cast<LargeNumberType>(var);

            ++indexTmp;
        }

        // Compute the sample moments
        for (ClauseIdT clauseId : l_clauseIdReusableVector_) {
            ClauseSizeType clauseSize = this->formulaRepresentationAbstractPtr_->getCurrentClauseSize(clauseId);
            totalClausesSize += clauseSize;

            assert(clauseSize > 0);

            // Check max clause size
            if (clauseSize > maxClauseSize)
                maxClauseSize = clauseSize;

            // Clause iterating
            for (auto clauseIt = this->formulaRepresentationAbstractPtr_->beginClause(clauseId);
                 clauseIt != this->formulaRepresentationAbstractPtr_->endClause(); ++clauseIt) {
                const LiteralType& lit = *clauseIt;

                VarT index = l_variableToIndexVectorMapping_[lit.getVariable()];

                SampleMomentType::size_type shift = lit.isPositive() ? 0 : 1;
                if (this->cacheType_ == CacheTypeEnum::HYPERGRAPH_CUT)
                    shift = 0;

                ++l_sampleMomentVector_[index][shift];   // occurrence

                // Sample moments
                for (NumberOfSampleMomentsType k = 1; k <= configuration_.numberOfSampleMoments; ++k)
                    l_sampleMomentVector_[index][2 * k + shift] += l_precomputedSampleMoments_createSampleMomentDataStructure_[clauseSize][k];   // k-th sample moment
            }
        }
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CaraCachingScheme<VarT, LiteralT, ClauseIdT>::processPrintCachingSchemeDebug(std::ostream& out) const {
        // Configuration
        out << "Number of sample moments: " << std::to_string(configuration_.numberOfSampleMoments) << std::endl;
        out << "Preprocessing type: " << preprocessingTypeEnumToString(configuration_.preprocessingType) << std::endl;
        out << "Variable to " << (configuration_.useVariableToLiteralMapping ? "literal" : "variable") << " mapping is used" << std::endl;

        if (configuration_.preprocessingType == PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES)
            out << "Discard invalid cache records: " << std::to_string(configuration_.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing) << std::endl;
    }
    #endif

    #if defined(TEST)
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    CaraCachingScheme<VarT, LiteralT, ClauseIdT>::SampleMomentVectorType&
    CaraCachingScheme<VarT, LiteralT, ClauseIdT>::getSampleMomentVector() const noexcept {
        return l_sampleMomentVector_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    CaraCachingScheme<VarT, LiteralT, ClauseIdT>::VariableVectorType&
    CaraCachingScheme<VarT, LiteralT, ClauseIdT>::getVariableToIndexVectorMapping() const noexcept {
        return l_variableToIndexVectorMapping_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    CaraCachingScheme<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType&
    CaraCachingScheme<VarT, LiteralT, ClauseIdT>::getClauseIdReusableVector() const noexcept {
        return l_clauseIdReusableVector_;
    }
    #endif
}   // namespace Hydra::Cache::CachingScheme::Cara
