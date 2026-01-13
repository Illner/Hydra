#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "Hydra/cache/CacheRecordStructure.hpp"
#include "Hydra/cache/cachingScheme/CachingSchemeAbstract.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/reusableVector/ReusableVector.hpp"

#include "Hydra/cache/cachingScheme/exceptions/CachingSchemeException.hpp"
#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/cache/cachingScheme/enums/CachingSchemeTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/SaveTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"

#include "Hydra/cache/cachingScheme/hybrid/HybridCachingScheme.tpp"

namespace Hydra::Cache::CachingScheme::Hybrid {

    using LargeNumberType = Hydra::Cache::CachingScheme::LargeNumberType;

    /**
     * Hybrid caching scheme (final class)
     * Exceptions:
     *      CachingUnitClausesIsForbiddenException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class HybridCachingScheme final : public CachingSchemeAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using ClauseSizeType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
        using VariableSetType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using ClauseIdReusableVectorType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType;
        using FormulaRepresentationAbstractPtrType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    private:
        using CacheRecordStruct = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::CacheRecordStruct;

    private:
        using VariableReusableVectorType = Container::ReusableVector::ReusableVector<VarT>;

    public:
        HybridCachingScheme(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CacheTypeEnum cacheType,
                            const HybridCachingSchemeConfiguration& configuration = HybridCachingSchemeConfiguration()) noexcept
            : CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, CachingSchemeTypeEnum::HYBRID,
                                                               cacheType, SaveTypeEnum::CLAUSE_ID, false, configuration.omitClauseType),
              configuration_(configuration), l_clauseIdSortedReusableVector_(formulaRepresentationAbstractPtr->getNumberOfOriginalClauses()),
              l_currentComponentVariableSortedReusableVector_(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula()) { }

    private:
        HybridCachingSchemeConfiguration configuration_;

        // Local auxiliary data structures
        mutable ClauseIdReusableVectorType l_clauseIdSortedReusableVector_;
        mutable VariableReusableVectorType l_currentComponentVariableSortedReusableVector_;

    private:
        LargeNumberType maxByteSizeKey() const override;

        CacheRecordStruct createCacheRecordStruct(const VariableSetType& currentComponentVariableSet) const override;

        /**
         * Fill the cache record structure
         * Assert: string MUST be empty
         * Assert: the current formula MUST NOT be empty
         * Local auxiliary data structures:
         *      l_clauseIdSortedReusableVector_
         *      l_currentComponentVariableSortedReusableVector_
         * @tparam CharT type used for a char (char8_t / char16_t / char32_t)
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param string [output] a key that will be created
         * @param cacheRecordStruct [output] a cache record structure that will be filled
         * @throw CachingUnitClausesIsForbiddenException [omitClauseType != NONE] if a unit clause exists
         */
        template <typename CharT>
        void fillCacheRecordStruct(const VariableSetType& currentComponentVariableSet, std::basic_string<CharT>& string, CacheRecordStruct& cacheRecordStruct) const;

    #ifndef NDEBUG
    private:
        void processPrintCachingSchemeDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::Cache::CachingScheme::Hybrid

#include "./HybridCachingScheme.ipp"
