#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Hydra/cache/CacheRecordStructure.hpp"
#include "Hydra/cache/cachingScheme/CachingSchemeAbstract.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/reusableVector/ReusableVector.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/cache/cachingScheme/enums/CachingSchemeTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/PreprocessingTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/SaveTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"

#include "Hydra/cache/cachingScheme/cara/CaraCachingScheme.tpp"

namespace Hydra::Cache::CachingScheme::Cara {

    using FormulaSizeType = Hydra::Cache::CachingScheme::FormulaSizeType;
    using LargeNumberType = Hydra::Cache::CachingScheme::LargeNumberType;

    /**
     * Cara caching scheme (final class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class CaraCachingScheme final : public CachingSchemeAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using LiteralType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using VectorSetType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::VectorSetType;
        using ClauseSizeType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
        using VariableSetType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using LiteralVectorType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
        using VariableVectorType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
        using ClauseIdReusableVectorType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType;
        using FormulaRepresentationAbstractPtrType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    private:
        using VariableReusableVectorType = Container::ReusableVector::ReusableVector<VarT>;

    private:
        using CacheRecordStruct = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::CacheRecordStruct;

    public:
        using SampleMomentType = std::vector<LargeNumberType>;
        using SampleMomentVectorType = std::vector<SampleMomentType>;

    public:
        #if defined(BELLA_COMPILER)
        CaraCachingScheme(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CacheTypeEnum cacheType,
                          const CaraCachingSchemeConfiguration& configuration = CaraCachingSchemeConfiguration()) noexcept
            : CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, CachingSchemeTypeEnum::CARA,
                                                               cacheType, SaveTypeEnum::LITERAL, true),
              configuration_(configuration), l_sampleMomentVector_(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula(), SampleMomentType(static_cast<typename SampleMomentType::size_type>(2 + 2 * configuration_.numberOfSampleMoments + 1), 0)),
              l_variableToIndexVectorMapping_(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), (VarT)0),
              l_clauseIdReusableVector_(formulaRepresentationAbstractPtr->getNumberOfOriginalClauses()),
              l_usedVariableVectorSet_createCacheRecordStruct_((configuration_.preprocessingType != PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES) ? 0 : formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormulaUsedForIndexing()),
              l_variableToLiteralVectorMapping_createCacheRecordStruct_(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), Formula::createZeroLiteral<VarT, LiteralT>()),
              l_variableSortedReusableVector_createCacheRecordStruct_(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula()),
              l_precomputedSampleMoments_createSampleMomentDataStructure_(1 + formulaRepresentationAbstractPtr->getMaxOriginalClauseSize(), SampleMomentType(static_cast<typename SampleMomentType::size_type>(1 + configuration_.numberOfSampleMoments))) {
            initializePrecomputedSampleMoments(formulaRepresentationAbstractPtr->getMaxOriginalClauseSize());
        }
        #elif defined(CARA_SOLVER)
        CaraCachingScheme(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CacheTypeEnum cacheType,
                          const CaraCachingSchemeConfiguration& configuration = CaraCachingSchemeConfiguration()) noexcept
            : CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, CachingSchemeTypeEnum::CARA,
                                                               cacheType, SaveTypeEnum::LITERAL, (cacheType == CacheTypeEnum::HYPERGRAPH_CUT)),   // mapping only for hypergraph cut caching
              configuration_(configuration), l_sampleMomentVector_(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula(), SampleMomentType(static_cast<typename SampleMomentType::size_type>(2 + 2 * configuration_.numberOfSampleMoments + 1), 0)),
              l_variableToIndexVectorMapping_(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), (VarT)0),
              l_clauseIdReusableVector_(formulaRepresentationAbstractPtr->getNumberOfOriginalClauses()),
              l_usedVariableVectorSet_createCacheRecordStruct_(((configuration_.preprocessingType != PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES) || (cacheType != CacheTypeEnum::HYPERGRAPH_CUT)) ? 0 : formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormulaUsedForIndexing()),
              l_variableToLiteralVectorMapping_createCacheRecordStruct_(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), Formula::createZeroLiteral<VarT, LiteralT>()),
              l_variableSortedReusableVector_createCacheRecordStruct_(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula()),
              l_precomputedSampleMoments_createSampleMomentDataStructure_(1 + formulaRepresentationAbstractPtr->getMaxOriginalClauseSize(), SampleMomentType(static_cast<typename SampleMomentType::size_type>(1 + configuration_.numberOfSampleMoments))) {
            initializePrecomputedSampleMoments(formulaRepresentationAbstractPtr->getMaxOriginalClauseSize());
        }
        #endif

    private:
        CaraCachingSchemeConfiguration configuration_;

        // Local auxiliary data structures
        mutable SampleMomentVectorType l_sampleMomentVector_;
        mutable VariableVectorType l_variableToIndexVectorMapping_;
        mutable ClauseIdReusableVectorType l_clauseIdReusableVector_;

        // Local auxiliary data structures for createCacheRecordStruct
        mutable VectorSetType l_usedVariableVectorSet_createCacheRecordStruct_;
        mutable LiteralVectorType l_variableToLiteralVectorMapping_createCacheRecordStruct_;
        mutable VariableReusableVectorType l_variableSortedReusableVector_createCacheRecordStruct_;

        // Local auxiliary data structures for createSampleMomentDataStructure
        SampleMomentVectorType l_precomputedSampleMoments_createSampleMomentDataStructure_;

    private:
        /**
         * Initialize the precomputed sample moments
         * Local auxiliary data structures:
         *      l_precomputedSampleMoments_createSampleMomentDataStructure_
         * @param maxOriginalClauseSize the maximum clause size in the original formula
         */
        void initializePrecomputedSampleMoments(ClauseSizeType maxOriginalClauseSize) noexcept;

        LargeNumberType maxByteSizeKey() const override;

        CacheRecordStruct createCacheRecordStruct(const VariableSetType& currentComponentVariableSet) const override;

    public:
        /**
         * Compute the sample moments for each variable
         * Data structure:
         *      number of positive occurrences
         *      number of negative occurrences
         *      positive 1-st sample moment
         *      negative 1-st sample moment
         *      ...
         *      positive k-th sample moment
         *      negative k-th sample moment
         *      variable identifier
         * Assert: maxClauseSize MUST be zero
         * Assert: totalClausesSize MUST be zero
         * Local auxiliary data structures:
         *      l_sampleMomentVector_
         *      l_clauseIdReusableVector_
         *      l_variableToIndexVectorMapping_
         *      l_precomputedSampleMoments_createSampleMomentDataStructure_
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param maxClauseSize [output] the maximum clause size
         * @param totalClausesSize [output] the total size of the clauses
         */
        void createSampleMomentDataStructure(const VariableSetType& currentComponentVariableSet,
                                             ClauseSizeType& maxClauseSize, FormulaSizeType& totalClausesSize) const;

    #ifndef NDEBUG
    private:
        void processPrintCachingSchemeDebug(std::ostream& out) const override;
    #endif

    #if defined(TEST)
    public:
        /**
         * Getter
         * @return l_sampleMomentVector_
         */
        SampleMomentVectorType& getSampleMomentVector() const noexcept;

        /**
         * Getter
         * @return l_variableToIndexVectorMapping_
         */
        VariableVectorType& getVariableToIndexVectorMapping() const noexcept;

        /**
         * Getter
         * @return l_clauseIdReusableVector_
         */
        ClauseIdReusableVectorType& getClauseIdReusableVector() const noexcept;
    #endif
    };
}   // namespace Hydra::Cache::CachingScheme::Cara

#include "./CaraCachingScheme.ipp"
