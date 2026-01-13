#pragma once

#include <algorithm>
#include <cassert>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "Hydra/cache/CacheRecordStructure.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/reusableVector/ReusableVector.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/cache/cachingScheme/exceptions/CachingSchemeException.hpp"
#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/cache/cachingScheme/enums/CachingSchemeTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/SaveTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"

namespace Hydra::Cache::CachingScheme {

    using FormulaSizeType = Hydra::Cache::FormulaSizeType;
    using LargeNumberType = Hydra::Cache::LargeNumberType;

    /**
     * Caching scheme representation (abstract class)
     * Copy and move methods are disabled!
     * Exception:
     *      VariableDoesNotExistInMappingException (debug)
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class CachingSchemeAbstract {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");
        static_assert(Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isValidClauseT::value, "Invalid ClauseIdT type!");

    protected:
        using LiteralType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::LiteralType;
        using ClauseSizeType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
        using VariableSetType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using VariableSortedVectorType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::VariableSortedVectorType;
        using MappingFromVariableToVariableType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::MappingFromVariableToVariableType;
        using FormulaRepresentationAbstractPtrType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;
        using ClauseIdVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;

    public:
        using LiteralVectorType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
        using VariableVectorType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::VariableVectorType;
        using VectorSetType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VectorSetType;
        using ClauseIdReusableVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType;

    private:
        using LiteralReusableVectorType = Container::ReusableVector::ReusableVector<LiteralType>;

    public:
        using CacheRecordStruct = Cache::CacheRecordStruct<VarT, LiteralT, ClauseIdT>;

    private:
        struct ClauseMetadataStruct {
        public:
            ClauseSizeType clauseSize;
            LiteralReusableVectorType::ConstIteratorType beginIt;
            LiteralReusableVectorType::ConstIteratorType endIt;
        };

    private:
        using ClauseMetadataVectorType = std::vector<ClauseMetadataStruct>;

    public:
        CachingSchemeAbstract(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CachingSchemeTypeEnum cachingSchemeType,
                              CacheTypeEnum cacheType, SaveTypeEnum saveType, bool usedMapping,
                              OmitClauseTypeEnum omitClauseType = OmitClauseTypeEnum::NONE) noexcept
            : saveType_(saveType), cachingSchemeType_(cachingSchemeType), l_firstCall_createSortedKeyWithMapping_(true),
              l_clauseMetadataVector_createSortedKeyWithMapping_(), l_mappedFormulaReusableVector_createSortedKeyWithMapping_(),
              usedMapping_(usedMapping), cacheType_(cacheType), omitClauseType_(omitClauseType), numberOfDiscardedCacheRecords_(0),
              formulaRepresentationAbstractPtr_(formulaRepresentationAbstractPtr) { }

        CachingSchemeAbstract(const CachingSchemeAbstract&) = delete;
        CachingSchemeAbstract(CachingSchemeAbstract&&) noexcept = delete;

        CachingSchemeAbstract& operator=(const CachingSchemeAbstract&) = delete;
        CachingSchemeAbstract& operator=(CachingSchemeAbstract&&) noexcept = delete;

        virtual ~CachingSchemeAbstract() noexcept = default;

    private:
        SaveTypeEnum saveType_;
        CachingSchemeTypeEnum cachingSchemeType_;

        // Local auxiliary data structures for createSortedKeyWithMapping
        mutable bool l_firstCall_createSortedKeyWithMapping_;
        mutable ClauseMetadataVectorType l_clauseMetadataVector_createSortedKeyWithMapping_;
        mutable LiteralReusableVectorType l_mappedFormulaReusableVector_createSortedKeyWithMapping_;

    protected:
        const bool usedMapping_;
        CacheTypeEnum cacheType_;
        OmitClauseTypeEnum omitClauseType_;
        mutable LargeNumberType numberOfDiscardedCacheRecords_;
        FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr_;

    public:
        /**
         * Create a cache record structure
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @return a cache record structure
         */
        virtual CacheRecordStruct createCacheRecordStruct(const VariableSetType& currentComponentVariableSet) const = 0;

        /**
         * @return the maximum number of bytes needed for a key
         */
        virtual LargeNumberType maxByteSizeKey() const = 0;

        /**
         * @return the maximum number of bytes needed for a mapping
         */
        LargeNumberType maxByteSizeMapping() const;

        /**
         * Getter
         * @return true if mapping is used. Otherwise, false is returned.
         */
        bool getUsedMapping() const noexcept;

        /**
         * Getter
         * @return the save type
         */
        SaveTypeEnum getSaveType() const noexcept;

        /**
         * Getter
         * @return the cache type
         */
        CacheTypeEnum getCacheType() const noexcept;

        /**
         * Getter
         * @return the formula representation pointer
         */
        FormulaRepresentationAbstractPtrType getFormulaRepresentationAbstractPtr() const noexcept;

        /**
         * Create a sorted key based on the clauses and mapping
         * Assert: string MUST be empty
         * Side effect: clauseIdReusableVector will be sorted
         * Local auxiliary data structures:
         *      l_firstCall_createSortedKeyWithMapping_
         *      l_clauseMetadataVector_createSortedKeyWithMapping_
         *      l_mappedFormulaReusableVector_createSortedKeyWithMapping_
         * @tparam CharT type used for a char (char8_t / char16_t / char32_t)
         * @param string [output] a sorted key that will be created
         * @param clauseIdReusableVector a reusable vector of clauses that we want to cache
         * @param variableToLiteralVectorMapping a vector mapping from variables to literals
         * @param totalClausesSize the total size of the clauses
         * @throw VariableDoesNotExistInMappingException (debug) if a variable does not exist in the mapping
         */
        template <typename CharT>
        void createSortedKeyWithMapping(std::basic_string<CharT>& string, ClauseIdReusableVectorType& clauseIdReusableVector,
                                        const LiteralVectorType& variableToLiteralVectorMapping, FormulaSizeType totalClausesSize) const;

    #ifndef NDEBUG
    public:
        void printCachingSchemeDebug(std::ostream& out, bool printCurrentFormula = false) const;

    protected:
        virtual void processPrintCachingSchemeDebug(std::ostream& out) const = 0;
    #endif
    };
}   // namespace Hydra::Cache::CachingScheme

#include "./CachingSchemeAbstract.ipp"
