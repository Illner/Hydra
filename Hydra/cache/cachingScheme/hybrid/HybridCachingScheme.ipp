#pragma once

#include "./HybridCachingScheme.hpp"

namespace Hydra::Cache::CachingScheme::Hybrid {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    LargeNumberType HybridCachingScheme<VarT, LiteralT, ClauseIdT>::maxByteSizeKey() const {
        LargeNumberType value = (LargeNumberType)this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula() + (LargeNumberType)1 +
                                (LargeNumberType)this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses();

        return value * (LargeNumberType)std::max(sizeof(VarT), sizeof(ClauseIdT));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename HybridCachingScheme<VarT, LiteralT, ClauseIdT>::CacheRecordStruct
    HybridCachingScheme<VarT, LiteralT, ClauseIdT>::createCacheRecordStruct(const VariableSetType& currentComponentVariableSet) const {
        CacheRecordStruct cacheRecordStruct;

        // Sort variables
        l_currentComponentVariableSortedReusableVector_.copySet(currentComponentVariableSet);
        l_currentComponentVariableSortedReusableVector_.sort();

        // Sort clauses
        this->formulaRepresentationAbstractPtr_->getCurrentComponentClauses(currentComponentVariableSet, l_clauseIdSortedReusableVector_, true);

        assert(!l_currentComponentVariableSortedReusableVector_.empty());   // at least one variable
        assert(!l_clauseIdSortedReusableVector_.empty());                   // at least one clause

        char32_t maxValue = std::max(static_cast<char32_t>(l_currentComponentVariableSortedReusableVector_.back()),
                                     static_cast<char32_t>(l_clauseIdSortedReusableVector_.back()));

        // char8_t
        if (Other::clauseIdCanBeSavedAsTypeT<char8_t>(maxValue))
            fillCacheRecordStruct<char8_t>(currentComponentVariableSet, cacheRecordStruct.string8, cacheRecordStruct);
        // char16_t
        else if (Other::clauseIdCanBeSavedAsTypeT<char16_t>(maxValue))
            fillCacheRecordStruct<char16_t>(currentComponentVariableSet, cacheRecordStruct.string16, cacheRecordStruct);
        // char32_t
        else
            fillCacheRecordStruct<char32_t>(currentComponentVariableSet, cacheRecordStruct.string32, cacheRecordStruct);

        return cacheRecordStruct;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    template <typename CharT>
    void HybridCachingScheme<VarT, LiteralT, ClauseIdT>::fillCacheRecordStruct(const VariableSetType& currentComponentVariableSet,
                                                                               std::basic_string<CharT>& string, CacheRecordStruct& cacheRecordStruct) const {
        cacheRecordStruct.empty = false;
        cacheRecordStruct.maxClauseSize = 0;
        cacheRecordStruct.numberOfRemovedVariables = 0;
        cacheRecordStruct.numberOfClauses = static_cast<ClauseIdT>(l_clauseIdSortedReusableVector_.size());
        cacheRecordStruct.numberOfRemovedClauses = cacheRecordStruct.numberOfClauses;
        cacheRecordStruct.numberOfVariables = static_cast<VarT>(l_currentComponentVariableSortedReusableVector_.size());
        cacheRecordStruct.formulaSize = this->formulaRepresentationAbstractPtr_->getCurrentComponentFormulaSize(currentComponentVariableSet);
        cacheRecordStruct.removedFormulaSize = cacheRecordStruct.formulaSize;

        assert(string.empty());                      // empty key
        assert(cacheRecordStruct.formulaSize > 0);   // non-empty formula
        assert(cacheRecordStruct.numberOfClauses == this->formulaRepresentationAbstractPtr_->getNumberOfCurrentComponentClauses(currentComponentVariableSet));

        string.reserve(cacheRecordStruct.numberOfVariables + static_cast<typename std::basic_string<CharT>::size_type>(1) + cacheRecordStruct.numberOfClauses);

        // Variables
        for (VarT var : l_currentComponentVariableSortedReusableVector_)
            string.push_back(static_cast<CharT>(var));

        string.push_back(static_cast<CharT>(0));   // delimiter

        // Clauses
        for (ClauseIdT clauseId : l_clauseIdSortedReusableVector_) {
            ClauseSizeType clauseSize = this->formulaRepresentationAbstractPtr_->getCurrentClauseSize(clauseId);

            // Omit clause type
            if (this->omitClauseType_ != OmitClauseTypeEnum::NONE) {
                // Unit clause
                if (clauseSize == 1)
                    throw Exception::Cache::CachingScheme::CachingUnitClausesIsForbiddenException();

                switch (this->omitClauseType_) {
                    case OmitClauseTypeEnum::ORIGINAL_BINARY:
                        if (this->formulaRepresentationAbstractPtr_->isClauseUntouched(clauseId) && (clauseSize == 2))
                            continue;
                        break;
                    case OmitClauseTypeEnum::UNTOUCHED:
                        if (this->formulaRepresentationAbstractPtr_->isClauseUntouched(clauseId))
                            continue;
                        break;
                    default:
                        throw Exception::NotImplementedException(omitClauseTypeEnumToString(this->omitClauseType_),
                                                                 "Hydra::Cache::CachingScheme::Hybrid::HybridCachingScheme::fillCacheRecordStruct");
                }
            }

            // Formula size
            assert(cacheRecordStruct.removedFormulaSize >= clauseSize);
            cacheRecordStruct.removedFormulaSize -= clauseSize;

            // Check max clause size
            if (clauseSize > cacheRecordStruct.maxClauseSize)
                cacheRecordStruct.maxClauseSize = clauseSize;

            --cacheRecordStruct.numberOfRemovedClauses;

            string.push_back(static_cast<CharT>(clauseId));
        }

        if (this->omitClauseType_ != OmitClauseTypeEnum::NONE)
            string.shrink_to_fit();
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void HybridCachingScheme<VarT, LiteralT, ClauseIdT>::processPrintCachingSchemeDebug([[maybe_unused]] std::ostream& out) const { }
    #endif
}   // namespace Hydra::Cache::CachingScheme::Hybrid
