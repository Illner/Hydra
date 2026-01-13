#pragma once

#include "./BasicCachingScheme.hpp"

namespace Hydra::Cache::CachingScheme::Basic {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    LargeNumberType BasicCachingScheme<VarT, LiteralT, ClauseIdT>::maxByteSizeKey() const {
        LargeNumberType value = (LargeNumberType)this->formulaRepresentationAbstractPtr_->getOriginalFormulaSize() +
                                (LargeNumberType)this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses();

        if (useVariableHeader())
            value += (LargeNumberType)this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula() + (LargeNumberType)1;

        switch (this->cacheType_) {
            case CacheTypeEnum::COMPONENT:
                return value * (LargeNumberType)sizeof(LiteralT);
            case CacheTypeEnum::HYPERGRAPH_CUT:
                return value * (LargeNumberType)sizeof(VarT);
            default:
                throw Exception::NotImplementedException(cacheTypeEnumToString(this->cacheType_),
                                                         "Hydra::Cache::CachingScheme::Basic::BasicCachingScheme::maxByteSizeKey");
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename BasicCachingScheme<VarT, LiteralT, ClauseIdT>::CacheRecordStruct
    BasicCachingScheme<VarT, LiteralT, ClauseIdT>::createCacheRecordStruct(const VariableSetType& currentComponentVariableSet) const {
        CacheRecordStruct cacheRecordStruct;

        // Initialization
        VarT maxVar;
        VariableSortedVectorType currentComponentVariableSortedVector = {};

        assert(!currentComponentVariableSet.empty());   // at least one variable

        // Variable header is used
        if (useVariableHeader()) {
            currentComponentVariableSortedVector = Other::sortUnorderedSet(currentComponentVariableSet);
            maxVar = currentComponentVariableSortedVector.back();
        }
        // Variable header is NOT used
        else {
            maxVar = *(std::max_element(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend()));
        }

        // char8_t
        if (((this->cacheType_ == CacheTypeEnum::COMPONENT) && Other::literalsCanBeSavedAsTypeT<char8_t>(maxVar)) ||
            ((this->cacheType_ == CacheTypeEnum::HYPERGRAPH_CUT) && Other::variablesCanBeSavedAsTypeT<char8_t>(maxVar)))
            fillCacheRecordStruct<char8_t>(currentComponentVariableSet, currentComponentVariableSortedVector, cacheRecordStruct.string8, cacheRecordStruct);
        // char16_t
        else if (((this->cacheType_ == CacheTypeEnum::COMPONENT) && Other::literalsCanBeSavedAsTypeT<char16_t>(maxVar)) ||
                 ((this->cacheType_ == CacheTypeEnum::HYPERGRAPH_CUT) && Other::variablesCanBeSavedAsTypeT<char16_t>(maxVar)))
            fillCacheRecordStruct<char16_t>(currentComponentVariableSet, currentComponentVariableSortedVector, cacheRecordStruct.string16, cacheRecordStruct);
        // char32_t
        else
            fillCacheRecordStruct<char32_t>(currentComponentVariableSet, currentComponentVariableSortedVector, cacheRecordStruct.string32, cacheRecordStruct);

        return cacheRecordStruct;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    template <typename CharT>
    void BasicCachingScheme<VarT, LiteralT, ClauseIdT>::fillCacheRecordStruct(const VariableSetType& currentComponentVariableSet,
                                                                              const VariableSortedVectorType& currentComponentVariableSortedVector,
                                                                              std::basic_string<CharT>& string, CacheRecordStruct& cacheRecordStruct) const {
        cacheRecordStruct.empty = false;
        cacheRecordStruct.maxClauseSize = 0;
        cacheRecordStruct.numberOfRemovedVariables = 0;
        cacheRecordStruct.numberOfVariables = static_cast<VarT>(currentComponentVariableSet.size());
        cacheRecordStruct.formulaSize = this->formulaRepresentationAbstractPtr_->getCurrentComponentFormulaSize(currentComponentVariableSet);
        cacheRecordStruct.removedFormulaSize = cacheRecordStruct.formulaSize;
        cacheRecordStruct.numberOfClauses = this->formulaRepresentationAbstractPtr_->getNumberOfCurrentComponentClauses(currentComponentVariableSet);
        cacheRecordStruct.numberOfRemovedClauses = cacheRecordStruct.numberOfClauses;

        assert(string.empty());                      // empty key
        assert(cacheRecordStruct.formulaSize > 0);   // non-empty formula

        if (useVariableHeader())
            string.reserve(cacheRecordStruct.numberOfVariables + 1 + cacheRecordStruct.formulaSize + cacheRecordStruct.numberOfClauses);
        else
            string.reserve(cacheRecordStruct.formulaSize + cacheRecordStruct.numberOfClauses);

        // Variable header
        if (useVariableHeader()) {
            assert(currentComponentVariableSet.size() == currentComponentVariableSortedVector.size());

            for (VarT var : currentComponentVariableSortedVector)
                string.push_back(static_cast<CharT>(var));

            string.push_back(static_cast<CharT>(0));   // delimiter
        }

        LiteralType zeroLit = Formula::createZeroLiteral<VarT, LiteralT>();
        this->formulaRepresentationAbstractPtr_->getSortedCurrentComponentClauses(currentComponentVariableSet, l_clauseIdReusableVector_fillCacheRecordStruct_,
                                                                                  configuration_.removeMultiOccurrentClauses,
                                                                                  (this->cacheType_ == CacheTypeEnum::HYPERGRAPH_CUT), this->omitClauseType_);
        cacheRecordStruct.numberOfRemovedClauses -= static_cast<ClauseIdT>(l_clauseIdReusableVector_fillCacheRecordStruct_.size());

        for (ClauseIdT clauseId : l_clauseIdReusableVector_fillCacheRecordStruct_) {
            ClauseSizeType clauseSize = 0;

            for (auto clauseIt = this->formulaRepresentationAbstractPtr_->beginSortedClause(clauseId);
                 clauseIt != this->formulaRepresentationAbstractPtr_->endSortedClause(); ++clauseIt) {
                ++clauseSize;

                assert(Other::containInSet(currentComponentVariableSet, clauseIt->getVariable()));

                switch (this->cacheType_) {
                    case CacheTypeEnum::COMPONENT:
                        string.push_back(static_cast<CharT>(clauseIt->getLiteralT()));
                        break;
                    case CacheTypeEnum::HYPERGRAPH_CUT:
                        string.push_back(static_cast<CharT>(clauseIt->getVariable()));
                        break;
                    default:
                        throw Exception::NotImplementedException(cacheTypeEnumToString(this->cacheType_),
                                                                 "Hydra::Cache::CachingScheme::Basic::BasicCachingScheme::fillCacheRecordStruct");
                }
            }

            // Unit clause
            if ((this->omitClauseType_ != OmitClauseTypeEnum::NONE) && (clauseSize == 1))
                throw Exception::Cache::CachingScheme::CachingUnitClausesIsForbiddenException();

            string.push_back(static_cast<CharT>(zeroLit.getLiteralT()));

            // Formula size
            assert(cacheRecordStruct.removedFormulaSize >= clauseSize);
            cacheRecordStruct.removedFormulaSize -= clauseSize;

            // Check max clause size
            if (clauseSize > cacheRecordStruct.maxClauseSize)
                cacheRecordStruct.maxClauseSize = clauseSize;
        }

        if ((this->omitClauseType_ != OmitClauseTypeEnum::NONE) || configuration_.removeMultiOccurrentClauses)
            string.shrink_to_fit();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool BasicCachingScheme<VarT, LiteralT, ClauseIdT>::useVariableHeader() const noexcept {
        return (this->omitClauseType_ != OmitClauseTypeEnum::NONE);
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void BasicCachingScheme<VarT, LiteralT, ClauseIdT>::processPrintCachingSchemeDebug(std::ostream& out) const {
        // Configuration
        out << "Remove multi-occurrent clauses: " << std::to_string(configuration_.removeMultiOccurrentClauses) << std::endl;
    }
    #endif
}   // namespace Hydra::Cache::CachingScheme::Basic
