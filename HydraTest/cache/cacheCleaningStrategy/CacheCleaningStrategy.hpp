#pragma once

#include <memory>
#include <sstream>
#include <string>

#include "Hydra/cache/Cache.hpp"
#include "Hydra/cache/CacheRecordStructure.hpp"
#include "Hydra/cache/cacheCleaningStrategy/CacheCleaningStrategyAbstract.hpp"
#include "Hydra/cache/cachingScheme/CachingSchemeAbstract.hpp"
#include "Hydra/cache/cachingScheme/basic/BasicCachingScheme.hpp"
#include "Hydra/cache/cachingScheme/cara/CaraCachingScheme.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.hpp"
#include "Hydra/other/Other.hpp"

#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/PreprocessingTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"

#include "Hydra/cache/cachingScheme/basic/BasicCachingScheme.tpp"
#include "Hydra/cache/cachingScheme/cara/CaraCachingScheme.tpp"

namespace HydraTest::Cache::CacheCleaningStrategy {

    //region Types
    using VarT = char8_t;
    using LiteralT = char16_t;
    using ClauseIdT = char32_t;
    using CacheValueT = Hydra::Cache::IdNodeType;

    using VariableSetType = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::VariableSetType;
    using LiteralVectorType = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::LiteralVectorType;
    using CacheRecordStruct = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheRecordStruct;
    using VariableVectorType = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::VariableVectorType;
    using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
    using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
    using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
    using CacheValuePtrAndIdPairOptionalType = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheValuePtrAndIdPairOptionalType;
    using FormulaRepresentationAbstractPtrType = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::FormulaRepresentationAbstractPtrType;

    using CacheType = Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>;
    using CaraCachingSchemeConfigurationType = Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration;
    using CaraCachingSchemeType = Hydra::Cache::CachingScheme::Cara::CaraCachingScheme<VarT, LiteralT, ClauseIdT>;
    using BasicCachingSchemeConfigurationType = Hydra::Cache::CachingScheme::Basic::BasicCachingSchemeConfiguration;
    using BasicCachingSchemeType = Hydra::Cache::CachingScheme::Basic::BasicCachingScheme<VarT, LiteralT, ClauseIdT>;
    using FormulaRepresentationAbstractType = Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>;
    using CachingSchemeAbstractUniquePtrType = std::unique_ptr<Hydra::Cache::CachingScheme::CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>>;
    using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;
    using CacheCleaningStrategyAbstractPtrType = const Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>*;
    using CacheCleaningStrategyAbstractUniquePtrType = std::unique_ptr<Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>>;

    using CacheTypeEnum = Hydra::Cache::CacheTypeEnum;
    using OmitClauseTypeEnum = Hydra::Cache::CachingScheme::OmitClauseTypeEnum;
    using PreprocessingTypeEnum = Hydra::Cache::CachingScheme::PreprocessingTypeEnum;
    //endregion

    inline CacheType createCache(CacheCleaningStrategyAbstractUniquePtrType&& cacheCleaningStrategyAbstractUniquePtr,
                                 FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CacheTypeEnum cacheType, bool usedMapping) {
        // Cara
        if (usedMapping) {
            // Configuration
            CaraCachingSchemeConfigurationType configuration;
            configuration.numberOfSampleMoments = 1;
            configuration.useVariableToLiteralMapping = true;
            configuration.preprocessingType = PreprocessingTypeEnum::NONE;

            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = std::make_unique<CaraCachingSchemeType>(formulaRepresentationAbstractPtr,
                                                                                                                        cacheType, configuration);

            return CacheType(std::move(cachingSchemeAbstractUniquePtr), std::move(cacheCleaningStrategyAbstractUniquePtr));
        }

        // Basic
        // Configuration
        BasicCachingSchemeConfigurationType configuration;
        configuration.removeMultiOccurrentClauses = false;
        configuration.omitClauseType = OmitClauseTypeEnum::NONE;

        CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = std::make_unique<BasicCachingSchemeType>(formulaRepresentationAbstractPtr,
                                                                                                                     cacheType, configuration);

        return CacheType(std::move(cachingSchemeAbstractUniquePtr), std::move(cacheCleaningStrategyAbstractUniquePtr));
    }

    inline void printCache(const CacheType& cache, std::stringstream& actualResult, bool printCurrentFormula = true, bool printCaches = true) {
        cache.printCacheDebug(actualResult, printCurrentFormula, printCaches, true, false);
        actualResult << std::endl;
    }

    inline void printCacheCleaningStrategy(const CacheType& cache, std::stringstream& actualResult) {
        cache.printCacheCleaningStrategyDebug(actualResult);
        actualResult << std::endl;
    }

    inline void printCacheCleaningStrategy(CacheCleaningStrategyAbstractPtrType cacheCleaningStrategyAbstractPtr, std::stringstream& actualResult) {
        cacheCleaningStrategyAbstractPtr->printCacheCleaningStrategyDebug(actualResult);
        actualResult << std::endl;
    }

    inline void printCurrentFormula(const CacheType& cache, std::stringstream& actualResult) {
        actualResult << "Current formula: ";
        FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr = cache.getFormulaRepresentationAbstractPtr();
        formulaRepresentationAbstractPtr->printCurrentFormulaDebug(actualResult, false, false);
        actualResult << std::endl
                     << std::endl;
    }

    inline void fillCache(CacheType& cache, std::stringstream& actualResult, bool print = false,
                          bool cacheEven = true, bool cacheOdd = true, bool cacheOriginalFormula = true) {
        VariableVectorType tmp;
        CacheValueT cacheValue = (CacheValueT)1;
        VariableVectorType assignment { 1, 2, 3, 4, 5, 6, 7, 8 };
        VariableSetType currentComponentVariableSet { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        FormulaRepresentationAbstractType* formulaRepresentationAbstractPtr = const_cast<FormulaRepresentationAbstractType*>(cache.getFormulaRepresentationAbstractPtr());

        CacheRecordStruct cacheRecordStruct;
        CacheValuePtrAndIdPairOptionalType searchResult;

        if (cacheOriginalFormula) {
            cacheRecordStruct = cache.createCacheRecordStruct(currentComponentVariableSet);
            searchResult = cache.searchInCache(cacheRecordStruct);

            // Not found
            if (!searchResult.has_value())
                cache.addCacheRecordToCache(std::move(cacheRecordStruct), std::move(cacheValue));

            if (print) {
                printCache(cache, actualResult, true, false);
                actualResult << "----------------------------------------" << std::endl
                             << std::endl;
            }
        }

        for (VarT var : assignment) {
            LiteralType lit(var, true);
            currentComponentVariableSet.erase(var);

            if (print)
                actualResult << "Assign: " << lit << std::endl;

            formulaRepresentationAbstractPtr->addLiteralToPartialAssignment(lit, tmp);

            if ((!cacheEven && (var % 2 == 0)) || (!cacheOdd && (var % 2 == 1)))
                continue;

            cacheRecordStruct = cache.createCacheRecordStruct(currentComponentVariableSet);
            searchResult = cache.searchInCache(cacheRecordStruct);

            // Not found
            if (!searchResult.has_value()) {
                cacheValue *= 2;
                cache.addCacheRecordToCache(std::move(cacheRecordStruct), std::move(cacheValue));
            }

            if (print) {
                printCache(cache, actualResult, true, false);
                actualResult << "----------------------------------------" << std::endl
                             << std::endl;
            }
        }

        for (auto it = assignment.crbegin(); it != assignment.crend(); ++it) {
            VarT var = *it;
            LiteralType lit(var, true);
            formulaRepresentationAbstractPtr->removeLiteralFromPartialAssignment(lit, tmp);
        }
    }
}   // namespace HydraTest::Cache::CacheCleaningStrategy
