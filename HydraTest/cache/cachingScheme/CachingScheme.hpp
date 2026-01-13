#pragma once

#include <memory>
#include <sstream>
#include <string>

#include "Hydra/cache/Cache.hpp"
#include "Hydra/cache/CacheRecordStructure.hpp"
#include "Hydra/cache/cacheCleaningStrategy/CacheCleaningStrategyAbstract.hpp"
#include "Hydra/cache/cacheCleaningStrategy/none/NoneCacheCleaningStrategy.hpp"
#include "Hydra/cache/cachingScheme/CachingSchemeAbstract.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/computeConnectedComponents/ConnectedComponentStructure.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"

namespace HydraTest::Cache::CachingScheme {

    //region Types
    using VarT = char32_t;
    using LiteralT = char32_t;
    using ClauseIdT = char32_t;
    using CacheValueT = Hydra::Formula::Literal<VarT, LiteralT>::VariableVectorType;

    using ClauseSizeType = typename Hydra::Cache::CacheRecordStruct<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
    using VariableSetType = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::VariableSetType;
    using CacheRecordStruct = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheRecordStruct;
    using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
    using LiteralVectorType = typename Hydra::Cache::CachingScheme::CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
    using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
    using VariableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
    using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
    using FormulaRepresentationAbstractPtrType = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::FormulaRepresentationAbstractPtrType;
    using VariableSortedVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSortedVectorType;

    using CacheType = Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>;
    using CachingSchemeAbstractPtrType = const Hydra::Cache::CachingScheme::CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>*;
    using FormulaRepresentationAbstractType = Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>;
    using CachingSchemeAbstractUniquePtrType = std::unique_ptr<Hydra::Cache::CachingScheme::CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>>;
    using ContagiousFormulaRepresentationConfigurationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration;
    using NoneCacheCleaningStrategyType = Hydra::Cache::CacheCleaningStrategy::None::NoneCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>;
    using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;
    using CacheCleaningStrategyAbstractUniquePtrType = std::unique_ptr<Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>>;

    using ConnectedComponentStructure = Hydra::Container::ComputeConnectedComponents::ConnectedComponentStruct<VarT, LiteralT>;

    using IgnorePureLiteralTypeEnum = Hydra::IgnorePureLiteralTypeEnum;
    //endregion

    inline CacheType createCache(CachingSchemeAbstractUniquePtrType&& cachingSchemeAbstractUniquePtr) {
        CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategyAbstractUniquePtr = std::make_unique<NoneCacheCleaningStrategyType>();

        return CacheType(std::move(cachingSchemeAbstractUniquePtr), std::move(cacheCleaningStrategyAbstractUniquePtr));
    }

    inline void printCachingScheme(const CacheType& cache, std::stringstream& actualResult, bool printCurrentFormula = true) {
        cache.printCachingSchemeDebug(actualResult, printCurrentFormula);
        actualResult << std::endl;
    }

    inline void printCachingScheme(CachingSchemeAbstractPtrType cachingSchemeAbstractPtr, std::stringstream& actualResult, bool printCurrentFormula = true) {
        cachingSchemeAbstractPtr->printCachingSchemeDebug(actualResult, printCurrentFormula);
        actualResult << std::endl;
    }

    inline void printCurrentComponentVariables(const VariableSetType& currentComponentVariableSet, std::stringstream& actualResult) {
        actualResult << "Current component variables:";
        for (VarT var : Hydra::Other::sortUnorderedSet(currentComponentVariableSet))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
    }

    inline void processCachingScheme(const CacheType& cache, const VariableSetType& currentComponentVariableSet, std::stringstream& actualResult,
                                     bool printMaxByteSize = false) {
        printCurrentComponentVariables(currentComponentVariableSet, actualResult);

        CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct(currentComponentVariableSet);
        cacheRecordStruct.printCacheRecordStruct(actualResult);

        if (printMaxByteSize) {
            actualResult << std::endl;
            actualResult << "Max bytes for key: " << std::to_string(cache.maxByteSizeKey()) << std::endl;
            actualResult << "Max bytes for mapping: " << std::to_string(cache.maxByteSizeMapping()) << std::endl;
        }

        actualResult << std::endl;
    }
}   // namespace HydraTest::Cache::CachingScheme
