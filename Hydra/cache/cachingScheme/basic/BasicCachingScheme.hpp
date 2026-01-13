#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "Hydra/cache/CacheRecordStructure.hpp"
#include "Hydra/cache/cachingScheme/CachingSchemeAbstract.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"

#include "Hydra/cache/cachingScheme/exceptions/CachingSchemeException.hpp"
#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/cache/cachingScheme/enums/CachingSchemeTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/SaveTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"

#include "Hydra/cache/cachingScheme/basic/BasicCachingScheme.tpp"

namespace Hydra::Cache::CachingScheme::Basic {

    using LargeNumberType = Hydra::Cache::CachingScheme::LargeNumberType;

    /**
     * Basic caching scheme (final class)
     * Exceptions:
     *      ConfigurationIsNotSupportedException
     *      CachingUnitClausesIsForbiddenException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class BasicCachingScheme final : public CachingSchemeAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using LiteralType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using ClauseSizeType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
        using VariableSetType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using VariableSortedVectorType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::VariableSortedVectorType;
        using ClauseIdReusableVectorType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType;
        using FormulaRepresentationAbstractPtrType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    private:
        using CacheRecordStruct = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::CacheRecordStruct;

    public:
        BasicCachingScheme(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CacheTypeEnum cacheType,
                           const BasicCachingSchemeConfiguration& configuration = BasicCachingSchemeConfiguration())
            : CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, CachingSchemeTypeEnum::BASIC,
                                                               cacheType, SaveTypeEnum::LITERAL, false, configuration.omitClauseType),
              configuration_(configuration), l_clauseIdReusableVector_fillCacheRecordStruct_(formulaRepresentationAbstractPtr->getNumberOfOriginalClauses()) {
            // Unsupported configuration
            if ((this->cacheType_ == CacheTypeEnum::HYPERGRAPH_CUT) && (this->omitClauseType_ != OmitClauseTypeEnum::NONE))
                throw Exception::ConfigurationIsNotSupportedException("basic caching scheme - \'" + cacheTypeEnumToString(this->cacheType_) + "\' and \'" + omitClauseTypeEnumToString(this->omitClauseType_) + "\'");
        }

    private:
        BasicCachingSchemeConfiguration configuration_;

        // Local auxiliary data structures for fillCacheRecordStruct
        mutable ClauseIdReusableVectorType l_clauseIdReusableVector_fillCacheRecordStruct_;

    private:
        LargeNumberType maxByteSizeKey() const override;

        CacheRecordStruct createCacheRecordStruct(const VariableSetType& currentComponentVariableSet) const override;

        /**
         * Fill the cache record structure
         * Assert: string MUST be empty
         * Assert: the current formula MUST NOT be empty
         * Local auxiliary data structures:
         *      l_clauseIdReusableVector_fillCacheRecordStruct_
         * @tparam CharT type used for a char (char8_t / char16_t / char32_t)
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param currentComponentVariableSortedVector [useVariableHeader] a sorted vector of variables appearing in the current component
         * @param string [output] a key that will be created
         * @param cacheRecordStruct [output] a cache record structure that will be filled
         * @throw CachingUnitClausesIsForbiddenException [omitClauseType != NONE] if a unit clause exists
         */
        template <typename CharT>
        void fillCacheRecordStruct(const VariableSetType& currentComponentVariableSet, const VariableSortedVectorType& currentComponentVariableSortedVector,
                                   std::basic_string<CharT>& string, CacheRecordStruct& cacheRecordStruct) const;

        /**
         * @return true if the variable header must be used. Otherwise, false is returned.
         */
        bool useVariableHeader() const noexcept;

    #ifndef NDEBUG
    private:
        void processPrintCachingSchemeDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::Cache::CachingScheme::Basic

#include "./BasicCachingScheme.ipp"
