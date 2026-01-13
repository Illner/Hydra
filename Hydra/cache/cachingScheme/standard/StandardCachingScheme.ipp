#pragma once

#include "./StandardCachingScheme.hpp"

namespace Hydra::Cache::CachingScheme::Standard {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    LargeNumberType StandardCachingScheme<VarT, LiteralT, ClauseIdT>::maxByteSizeKey() const {
        LargeNumberType value = (LargeNumberType)this->formulaRepresentationAbstractPtr_->getOriginalFormulaSize() +
                                (LargeNumberType)this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses();

        switch (this->cacheType_) {
            case CacheTypeEnum::COMPONENT:
                return value * (LargeNumberType)sizeof(LiteralT);
            case CacheTypeEnum::HYPERGRAPH_CUT:
                return value * (LargeNumberType)sizeof(VarT);
            default:
                throw Exception::NotImplementedException(cacheTypeEnumToString(this->cacheType_),
                                                         "Hydra::Cache::CachingScheme::Standard::StandardCachingScheme::maxByteSizeKey");
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename StandardCachingScheme<VarT, LiteralT, ClauseIdT>::CacheRecordStruct
    StandardCachingScheme<VarT, LiteralT, ClauseIdT>::createCacheRecordStruct(const VariableSetType& currentComponentVariableSet) const {
        CacheRecordStruct cacheRecordStruct;

        VarT maxVar = *(std::max_element(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend()));

        // char8_t
        if (((this->cacheType_ == CacheTypeEnum::COMPONENT) && Other::literalsCanBeSavedAsTypeT<char8_t>(maxVar)) ||
            ((this->cacheType_ == CacheTypeEnum::HYPERGRAPH_CUT) && Other::variablesCanBeSavedAsTypeT<char8_t>(maxVar)))
            fillCacheRecordStruct<char8_t>(currentComponentVariableSet, cacheRecordStruct.string8, cacheRecordStruct);
        // char16_t
        else if (((this->cacheType_ == CacheTypeEnum::COMPONENT) && Other::literalsCanBeSavedAsTypeT<char16_t>(maxVar)) ||
                 ((this->cacheType_ == CacheTypeEnum::HYPERGRAPH_CUT) && Other::variablesCanBeSavedAsTypeT<char16_t>(maxVar)))
            fillCacheRecordStruct<char16_t>(currentComponentVariableSet, cacheRecordStruct.string16, cacheRecordStruct);
        // char32_t
        else
            fillCacheRecordStruct<char32_t>(currentComponentVariableSet, cacheRecordStruct.string32, cacheRecordStruct);

        return cacheRecordStruct;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    template <typename CharT>
    void StandardCachingScheme<VarT, LiteralT, ClauseIdT>::fillCacheRecordStruct(const VariableSetType& currentComponentVariableSet,
                                                                                 std::basic_string<CharT>& string, CacheRecordStruct& cacheRecordStruct) const {
        cacheRecordStruct.empty = false;
        cacheRecordStruct.maxClauseSize = 0;
        cacheRecordStruct.removedFormulaSize = 0;
        cacheRecordStruct.numberOfRemovedClauses = 0;
        cacheRecordStruct.numberOfRemovedVariables = 0;
        cacheRecordStruct.numberOfVariables = static_cast<VarT>(currentComponentVariableSet.size());
        cacheRecordStruct.formulaSize = this->formulaRepresentationAbstractPtr_->getCurrentComponentFormulaSize(currentComponentVariableSet);
        cacheRecordStruct.numberOfClauses = this->formulaRepresentationAbstractPtr_->getNumberOfCurrentComponentClauses(currentComponentVariableSet);

        assert(string.empty());                      // empty key
        assert(cacheRecordStruct.formulaSize > 0);   // non-empty formula

        string.reserve(cacheRecordStruct.formulaSize + cacheRecordStruct.numberOfClauses);

        LiteralType zeroLit = Formula::createZeroLiteral<VarT, LiteralT>();
        this->formulaRepresentationAbstractPtr_->getCurrentComponentClauses(currentComponentVariableSet, l_clauseIdReusableVector_fillCacheRecordStruct_, false);

        for (ClauseIdT clauseId : l_clauseIdReusableVector_fillCacheRecordStruct_) {
            ClauseSizeType clauseSize = 0;

            for (auto clauseIt = this->formulaRepresentationAbstractPtr_->beginClause(clauseId);
                 clauseIt != this->formulaRepresentationAbstractPtr_->endClause(); ++clauseIt) {
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
                                                                 "Hydra::Cache::CachingScheme::Standard::StandardCachingScheme::fillCacheRecordStruct");
                }
            }

            string.push_back(static_cast<CharT>(zeroLit.getLiteralT()));

            // Check max clause size
            if (clauseSize > cacheRecordStruct.maxClauseSize)
                cacheRecordStruct.maxClauseSize = clauseSize;
        }
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void StandardCachingScheme<VarT, LiteralT, ClauseIdT>::processPrintCachingSchemeDebug([[maybe_unused]] std::ostream& out) const { }
    #endif
}   // namespace Hydra::Cache::CachingScheme::Standard
