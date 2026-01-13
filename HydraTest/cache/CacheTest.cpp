#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/cache/CacheTestResult.hpp"
#include "HydraTest/catch.hpp"

#include "Hydra/cache/Cache.hpp"
#include "Hydra/cache/CacheBucketStructure.hpp"
#include "Hydra/cache/CacheRecordStructure.hpp"
#include "Hydra/cache/cacheCleaningStrategy/CacheCleaningStrategyAbstract.hpp"
#include "Hydra/cache/cacheCleaningStrategy/none/NoneCacheCleaningStrategy.hpp"
#include "Hydra/cache/cachingScheme/CachingSchemeAbstract.hpp"
#include "Hydra/cache/cachingScheme/basic/BasicCachingScheme.hpp"
#include "Hydra/cache/cachingScheme/basic/BasicCachingScheme.tpp"
#include "Hydra/cache/cachingScheme/cara/CaraCachingScheme.hpp"
#include "Hydra/cache/cachingScheme/cara/CaraCachingScheme.tpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/computeConnectedComponents/ConnectedComponentStructure.hpp"

#include "Hydra/cache/exceptions/CacheException.hpp"

#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/PreprocessingTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"
#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"

namespace HydraTest::Cache {
    //region Types
    using VarT = char32_t;
    using LiteralT = char32_t;
    using ClauseIdT = char32_t;
    using CacheValueT = Hydra::Cache::IdNodeType;

    using VariableSetType = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::VariableSetType;
    using LiteralVectorType = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::LiteralVectorType;
    using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
    using MappingFromVariableToLiteralType = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::MappingFromVariableToLiteralType;
    using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
    using VariableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
    using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
    using CacheValuePtrAndIdPairOptionalType = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheValuePtrAndIdPairOptionalType;
    using FormulaRepresentationAbstractPtrType = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::FormulaRepresentationAbstractPtrType;

    using CacheRecordStruct = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheRecordStruct;
    using CacheBucketStruct = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheBucketStruct;

    using VariableSetVectorType = std::vector<VariableSetType>;
    using CacheType = Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>;
    using CaraCachingSchemeType = Hydra::Cache::CachingScheme::Cara::CaraCachingScheme<VarT, LiteralT, ClauseIdT>;
    using BasicCachingSchemeType = Hydra::Cache::CachingScheme::Basic::BasicCachingScheme<VarT, LiteralT, ClauseIdT>;
    using FormulaRepresentationAbstractType = Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>;
    using CachingSchemeAbstractUniquePtrType = std::unique_ptr<Hydra::Cache::CachingScheme::CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>>;
    using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
    using NoneCacheCleaningStrategyType = Hydra::Cache::CacheCleaningStrategy::None::NoneCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>;
    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;
    using CacheCleaningStrategyAbstractUniquePtrType = std::unique_ptr<Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyAbstract<VarT, LiteralT, ClauseIdT, CacheValueT>>;

    using ConnectedComponentStructure = Hydra::Container::ComputeConnectedComponents::ConnectedComponentStruct<VarT, LiteralT>;

    using CacheTypeEnum = Hydra::Cache::CacheTypeEnum;
    using IgnorePureLiteralTypeEnum = Hydra::IgnorePureLiteralTypeEnum;
    using OmitClauseTypeEnum = Hydra::Cache::CachingScheme::OmitClauseTypeEnum;
    using PreprocessingTypeEnum = Hydra::Cache::CachingScheme::PreprocessingTypeEnum;

    using CaraCachingSchemeConfigurationType = Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration;
    using BasicCachingSchemeConfigurationType = Hydra::Cache::CachingScheme::Basic::BasicCachingSchemeConfiguration;
    //endregion

    //region Functions
    CacheType createCacheWithMapping(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CacheTypeEnum cacheType) {
        // Cache cleaning strategy
        CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategyAbstractUniquePtr = std::make_unique<NoneCacheCleaningStrategyType>();

        // Caching scheme
        CaraCachingSchemeConfigurationType configuration;
        configuration.numberOfSampleMoments = 0;
        configuration.useVariableToLiteralMapping = true;
        configuration.preprocessingType = PreprocessingTypeEnum::NONE;

        CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = std::make_unique<CaraCachingSchemeType>(formulaRepresentationAbstractPtr,
                                                                                                                    cacheType, configuration);

        return CacheType(std::move(cachingSchemeAbstractUniquePtr), std::move(cacheCleaningStrategyAbstractUniquePtr));
    }

    CacheType createCacheWithoutMapping(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CacheTypeEnum cacheType) {
        // Cache cleaning strategy
        CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategyAbstractUniquePtr = std::make_unique<NoneCacheCleaningStrategyType>();

        // Caching scheme
        BasicCachingSchemeConfigurationType configuration;
        configuration.removeMultiOccurrentClauses = false;
        configuration.omitClauseType = OmitClauseTypeEnum::NONE;

        CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = std::make_unique<BasicCachingSchemeType>(formulaRepresentationAbstractPtr, cacheType,
                                                                                                                     configuration);

        return CacheType(std::move(cachingSchemeAbstractUniquePtr), std::move(cacheCleaningStrategyAbstractUniquePtr));
    }

    void printCache(const CacheType& cache, std::stringstream& actualResult, bool printCurrentFormula = true,
                    bool printVariableNumberOfHits = true, bool printCacheStatistics = true) {
        cache.printCacheDebug(actualResult, printCurrentFormula, true, printVariableNumberOfHits, printCacheStatistics);
    }

    void printCurrentComponentVariables(const VariableSetType& currentComponentVariableSet, std::stringstream& actualResult) {
        actualResult << "Current component variables:";
        for (VarT var : Hydra::Other::sortUnorderedSet(currentComponentVariableSet))
            actualResult << " " << std::to_string(var);
        actualResult << std::endl;
    }

    void printCurrentFormula(const CacheType& cache, std::stringstream& actualResult) {
        actualResult << "Current formula: ";
        FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr = cache.getFormulaRepresentationAbstractPtr();
        formulaRepresentationAbstractPtr->printCurrentFormulaDebug(actualResult, false, false);
        actualResult << std::endl
                     << std::endl;
    }

    void printResult(const CacheValuePtrAndIdPairOptionalType& cacheValuePtrAndIdPairOptional, std::stringstream& actualResult) {
        // Found
        if (cacheValuePtrAndIdPairOptional.has_value()) {
            actualResult << "ID: " << std::to_string(cacheValuePtrAndIdPairOptional->second) << std::endl;
            actualResult << "Value: " << std::to_string(*(cacheValuePtrAndIdPairOptional->first)) << std::endl;
        }
        // Not found
        else
            actualResult << "Not found" << std::endl;

        actualResult << std::endl;
    }

    void processCreateCacheRecord(const CacheType& cache, std::stringstream& actualResult) {
        FormulaRepresentationAbstractType* formulaRepresentationAbstractPtr = const_cast<FormulaRepresentationAbstractType*>(cache.getFormulaRepresentationAbstractPtr());

        VariableSetVectorType currentComponentVariableSetVector { { 1, 2, 3 }, { 1, 2, 3, 4, 5, 6 }, { 7, 8, 9 }, { 7, 8, 9, 10, 11, 12 } };

        for (const VariableSetType& currentComponentVariableSet : currentComponentVariableSetVector) {
            printCurrentComponentVariables(currentComponentVariableSet, actualResult);

            ConnectedComponentStructure connectedComponentStructure(currentComponentVariableSet.size());
            connectedComponentStructure.variableSet.insert(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend());

            formulaRepresentationAbstractPtr->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);
            printCurrentFormula(cache, actualResult);

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct(currentComponentVariableSet);
            cacheRecordStruct.printCacheRecordStruct(actualResult);

            formulaRepresentationAbstractPtr->popPreviousComponent(connectedComponentStructure, {});
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }
    }

    void processAddCacheRecord(CacheType& cache, std::stringstream& actualResult) {
        FormulaRepresentationAbstractType* formulaRepresentationAbstractPtr = const_cast<FormulaRepresentationAbstractType*>(cache.getFormulaRepresentationAbstractPtr());

        CacheValueT cacheValue = (CacheValueT)1;
        VariableSetVectorType currentComponentVariableSetVector { { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
                                                                  { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                                                                  { 1, 2, 3, 4, 5, 6 },
                                                                  { 1, 2, 3 } };

        for (const VariableSetType& currentComponentVariableSet : currentComponentVariableSetVector) {
            printCurrentComponentVariables(currentComponentVariableSet, actualResult);

            ConnectedComponentStructure connectedComponentStructure(currentComponentVariableSet.size());
            connectedComponentStructure.variableSet.insert(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend());

            formulaRepresentationAbstractPtr->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);
            printCurrentFormula(cache, actualResult);

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct(currentComponentVariableSet);
            cacheRecordStruct.printCacheRecordStruct(actualResult);
            actualResult << std::endl;

            cache.addCacheRecordToCache(std::move(cacheRecordStruct), cacheValue++);
            printCache(cache, actualResult, false);

            formulaRepresentationAbstractPtr->popPreviousComponent(connectedComponentStructure, {});
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }
    }

    void processAssignment(const CacheType& cache, std::stringstream& actualResult) {
        VariableSetType currentComponentVariableSet { 1, 2, 3, 4, 5 };
        ConnectedComponentStructure connectedComponentStructure(currentComponentVariableSet.size());
        connectedComponentStructure.variableSet.insert(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend());

        FormulaRepresentationAbstractType* formulaRepresentationAbstractPtr = const_cast<FormulaRepresentationAbstractType*>(cache.getFormulaRepresentationAbstractPtr());
        formulaRepresentationAbstractPtr->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

        std::vector<LiteralVectorType> assignmentsVector { { LiteralType(3, true), LiteralType(4, true) },
                                                           { LiteralType(3, false), LiteralType(4, false) } };

        for (const LiteralVectorType& assignment : assignmentsVector) {
            actualResult << "Assignment:";
            for (const LiteralType& lit : assignment) {
                actualResult << " " << lit;
                currentComponentVariableSet.erase(lit.getVariable());
            }
            actualResult << std::endl;

            VariableVectorType tmp;
            formulaRepresentationAbstractPtr->addLiteralVectorToPartialAssignment(assignment, tmp);
            printCurrentFormula(cache, actualResult);

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct(currentComponentVariableSet);
            cacheRecordStruct.printCacheRecordStruct(actualResult);
            actualResult << std::endl;

            formulaRepresentationAbstractPtr->removeLiteralVectorFromPartialAssignment(assignment, tmp);

            for (const LiteralType& lit : assignment)
                currentComponentVariableSet.insert(lit.getVariable());

            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }
    }

    void processSearch(CacheType& cache, std::stringstream& actualResult) {
        VariableVectorType tmp;
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);

        VariableSetType currentComponentVariableSet { 6, 7, 8 };
        ConnectedComponentStructure connectedComponentStructure(currentComponentVariableSet.size());
        connectedComponentStructure.variableSet.insert(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend());

        FormulaRepresentationAbstractType* formulaRepresentationAbstractPtr = const_cast<FormulaRepresentationAbstractType*>(cache.getFormulaRepresentationAbstractPtr());
        formulaRepresentationAbstractPtr->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);
        printCurrentFormula(cache, actualResult);

        // -
        CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct(currentComponentVariableSet);
        cacheRecordStruct.printCacheRecordStruct(actualResult);
        actualResult << std::endl;

        printResult(cache.searchInCache(cacheRecordStruct), actualResult);

        cache.addCacheRecordToCache(std::move(cacheRecordStruct), (CacheValueT)1);
        printCache(cache, actualResult);

        actualResult << "----------------------------------------" << std::endl
                     << std::endl;

        // x_8
        actualResult << "Assignment: " << litPos8 << std::endl;
        formulaRepresentationAbstractPtr->addLiteralToPartialAssignment(litPos8, tmp);
        printCurrentFormula(cache, actualResult);

        cacheRecordStruct = cache.createCacheRecordStruct({ 6, 7 });
        cacheRecordStruct.printCacheRecordStruct(actualResult);
        actualResult << std::endl;

        printResult(cache.searchInCache(cacheRecordStruct), actualResult);

        cache.addCacheRecordToCache(std::move(cacheRecordStruct), (CacheValueT)2);

        cacheRecordStruct = cache.createCacheRecordStruct({ 6, 7 });
        printResult(cache.searchInCache(cacheRecordStruct), actualResult);

        printCache(cache, actualResult);
        formulaRepresentationAbstractPtr->removeLiteralFromPartialAssignment(litPos8, tmp);

        actualResult << "----------------------------------------" << std::endl
                     << std::endl;

        // -x_8
        actualResult << "Assignment: " << litNeg8 << std::endl;
        formulaRepresentationAbstractPtr->addLiteralToPartialAssignment(litNeg8, tmp);
        printCurrentFormula(cache, actualResult);

        cacheRecordStruct = cache.createCacheRecordStruct({ 6, 7 });
        cacheRecordStruct.printCacheRecordStruct(actualResult);
        actualResult << std::endl;

        printResult(cache.searchInCache(cacheRecordStruct), actualResult);
        printCache(cache, actualResult);
    }

    void processCreateMapping(CacheType& cache, std::stringstream& actualResult) {
        FormulaRepresentationAbstractType* formulaRepresentationAbstractPtr = const_cast<FormulaRepresentationAbstractType*>(cache.getFormulaRepresentationAbstractPtr());

        VariableSetVectorType currentComponentVariableSetVector { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 10, 11, 12 } };

        for (const VariableSetType& currentComponentVariableSet : currentComponentVariableSetVector) {
            printCurrentComponentVariables(currentComponentVariableSet, actualResult);

            ConnectedComponentStructure connectedComponentStructure(currentComponentVariableSet.size());
            connectedComponentStructure.variableSet.insert(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend());

            formulaRepresentationAbstractPtr->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);
            printCurrentFormula(cache, actualResult);

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct(currentComponentVariableSet);
            cacheRecordStruct.printCacheRecordStruct(actualResult);
            actualResult << std::endl;

            CacheValuePtrAndIdPairOptionalType cacheValuePtrAndIdPairOptional = cache.searchInCache(cacheRecordStruct);
            printResult(cacheValuePtrAndIdPairOptional, actualResult);

            // Found
            if (cacheValuePtrAndIdPairOptional.has_value()) {
                MappingFromVariableToLiteralType mapping = cache.createMapping(cacheValuePtrAndIdPairOptional->second, cacheRecordStruct);

                actualResult << "Mapping" << std::endl;
                for (VarT var : Hydra::Other::extractKeysFromMap(mapping, true)) {
                    actualResult << "\t" << std::to_string(var) << " -> " << mapping.at(var) << std::endl;
                }
                actualResult << std::endl;
            }
            // Not found
            else
                cache.addCacheRecordToCache(std::move(cacheRecordStruct), (CacheValueT)1);

            printCache(cache, actualResult, false);

            formulaRepresentationAbstractPtr->popPreviousComponent(connectedComponentStructure, {});
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }
    }

    void processChar(CacheType& cache, const VariableSetVectorType& currentComponentVariableSetVector, std::stringstream& actualResult) {
        CacheValueT cacheValue = (CacheValueT)1;
        FormulaRepresentationAbstractType* formulaRepresentationAbstractPtr = const_cast<FormulaRepresentationAbstractType*>(cache.getFormulaRepresentationAbstractPtr());

        for (const VariableSetType& currentComponentVariableSet : currentComponentVariableSetVector) {
            printCurrentComponentVariables(currentComponentVariableSet, actualResult);

            ConnectedComponentStructure connectedComponentStructure(currentComponentVariableSet.size());
            connectedComponentStructure.variableSet.insert(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend());

            formulaRepresentationAbstractPtr->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);
            printCurrentFormula(cache, actualResult);

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct(currentComponentVariableSet);
            cacheRecordStruct.printCacheRecordStruct(actualResult);
            actualResult << std::endl;

            printResult(cache.searchInCache(cacheRecordStruct), actualResult);

            cacheValue *= 2;
            cache.addCacheRecordToCache(std::move(cacheRecordStruct), std::move(cacheValue));

            cacheRecordStruct = cache.createCacheRecordStruct(currentComponentVariableSet);
            cacheRecordStruct.printCacheRecordStruct(actualResult);
            actualResult << std::endl;

            printResult(cache.searchInCache(cacheRecordStruct), actualResult);

            printCache(cache, actualResult, false, false);

            formulaRepresentationAbstractPtr->popPreviousComponent(connectedComponentStructure, {});
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;
        }
    }
    //endregion

    //region FormulaRepresentation
    FormulaRepresentationAbstractUniquePtrType createFormula() {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litPos9(9, true);
        LiteralType litNeg10(10, false);
        LiteralType litPos11(11, true);
        LiteralType litNeg11(11, false);
        LiteralType litPos12(12, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos1, litNeg2, zeroLit,   // 0
            litPos2, litNeg3, zeroLit,   // 1

            litPos4, litNeg5, zeroLit,   // 2
            litPos5, litNeg6, zeroLit,   // 3

            litPos7, litPos8, zeroLit,   // 4
            litNeg8, litPos9, zeroLit,   // 5

            litNeg10, litPos11, zeroLit,   // 6
            litNeg11, litPos12, zeroLit    // 7
        };

        VarT numberOfVariables = 12;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    FormulaRepresentationAbstractUniquePtrType createFormulaForAssignment() {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litNeg1, litNeg4, litPos5, zeroLit,   // 0
            litPos1, litPos3, litPos5, zeroLit,   // 1
            litNeg2, litNeg3, litNeg5, zeroLit,   // 2
            litPos2, litPos4, litNeg5, zeroLit,   // 3

            litPos6, litNeg7, litNeg8, zeroLit,   // 4
            litPos6, litNeg7, litPos8, zeroLit    // 5
        };

        VarT numberOfVariables = 8;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    FormulaRepresentationAbstractUniquePtrType createFormulaVariableChar() {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litPos255(255, true);
        LiteralType litNeg255(255, false);
        LiteralType litPos256(256, true);
        LiteralType litNeg256(256, false);
        LiteralType litPos65535(65535, true);
        LiteralType litNeg65535(65535, false);
        LiteralType litPos65536(65536, true);
        LiteralType litNeg65536(65536, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos1, litPos2, zeroLit,     // 1
            litNeg1, litNeg255, zeroLit,   // 0
            litNeg2, litPos255, zeroLit,   // 2

            litNeg3, litNeg4, zeroLit,     // 3
            litPos3, litNeg256, zeroLit,   // 4
            litPos4, litPos256, zeroLit,   // 5

            litPos5, litNeg6, zeroLit,       // 7
            litNeg5, litPos65535, zeroLit,   // 6
            litPos6, litNeg65535, zeroLit,   // 8

            litNeg7, litPos8, zeroLit,       // 9
            litPos7, litPos65536, zeroLit,   // 10
            litNeg8, litNeg65536, zeroLit    // 11
        };

        VarT numberOfVariables = 65536;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    FormulaRepresentationAbstractUniquePtrType createFormulaLiteralChar() {
        //region Literals
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litPos127(127, true);
        LiteralType litNeg127(127, false);
        LiteralType litPos128(128, true);
        LiteralType litNeg128(128, false);
        LiteralType litPos32767(32767, true);
        LiteralType litNeg32767(32767, false);
        LiteralType litPos32768(32768, true);
        LiteralType litNeg32768(32768, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();
        //endregion

        FormulaType formula {
            litPos1, litPos2, zeroLit,     // 1
            litNeg1, litNeg127, zeroLit,   // 0
            litNeg2, litPos127, zeroLit,   // 2

            litNeg3, litNeg4, zeroLit,     // 3
            litPos3, litNeg128, zeroLit,   // 4
            litPos4, litPos128, zeroLit,   // 5

            litPos5, litNeg6, zeroLit,       // 7
            litNeg5, litPos32767, zeroLit,   // 6
            litPos6, litNeg32767, zeroLit,   // 8

            litNeg7, litPos8, zeroLit,       // 9
            litPos7, litPos32768, zeroLit,   // 10
            litNeg8, litNeg32768, zeroLit    // 11
        };

        VarT numberOfVariables = 32768;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }
    //endregion

    /**
     * Cache with mapping - component caching
     */
    TEST_CASE("[Cache] cache with mapping - component caching", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithMappingComponentCachingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithMapping(formulaRepresentation.get(), CacheTypeEnum::COMPONENT);
            printCache(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache with mapping - component caching (create cache record)
     */
    TEST_CASE("[Cache] cache with mapping - component caching (create cache record)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithMappingComponentCachingCreateCacheRecordResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithMapping(formulaRepresentation.get(), CacheTypeEnum::COMPONENT);
            processCreateCacheRecord(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache with mapping - component caching (add cache record)
     */
    TEST_CASE("[Cache] cache with mapping - component caching (add cache record)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithMappingComponentCachingAddCacheRecordResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithMapping(formulaRepresentation.get(), CacheTypeEnum::COMPONENT);
            processAddCacheRecord(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache with mapping - component caching (assignment)
     */
    TEST_CASE("[Cache] cache with mapping - component caching (assignment)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithMappingComponentCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForAssignment();
            CacheType cache = createCacheWithMapping(formulaRepresentation.get(), CacheTypeEnum::COMPONENT);
            processAssignment(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache with mapping - component caching (search)
     */
    TEST_CASE("[Cache] cache with mapping - component caching (search)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithMappingComponentCachingSearchResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForAssignment();
            CacheType cache = createCacheWithMapping(formulaRepresentation.get(), CacheTypeEnum::COMPONENT);
            processSearch(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    #if defined(BELLA_COMPILER)
    /**
     * Cache with mapping - component caching (create mapping)
     */
    TEST_CASE("[Cache] cache with mapping - component caching (create mapping)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithMappingComponentCachingCreateMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithMapping(formulaRepresentation.get(), CacheTypeEnum::COMPONENT);
            processCreateMapping(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
    #endif

    /**
     * Cache without mapping - component caching
     */
    TEST_CASE("[Cache] cache without mapping - component caching", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithoutMappingComponentCachingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithoutMapping(formulaRepresentation.get(), CacheTypeEnum::COMPONENT);
            printCache(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache without mapping - component caching (create cache record)
     */
    TEST_CASE("[Cache] cache without mapping - component caching (create cache record)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithoutMappingComponentCachingCreateCacheRecordResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithoutMapping(formulaRepresentation.get(), CacheTypeEnum::COMPONENT);
            processCreateCacheRecord(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache without mapping - component caching (add cache record)
     */
    TEST_CASE("[Cache] cache without mapping - component caching (add cache record)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithoutMappingComponentCachingAddCacheRecordResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithoutMapping(formulaRepresentation.get(), CacheTypeEnum::COMPONENT);
            processAddCacheRecord(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache without mapping - component caching (assignment)
     */
    TEST_CASE("[Cache] cache without mapping - component caching (assignment)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithoutMappingComponentCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForAssignment();
            CacheType cache = createCacheWithoutMapping(formulaRepresentation.get(), CacheTypeEnum::COMPONENT);
            processAssignment(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache without mapping - component caching (search)
     */
    TEST_CASE("[Cache] cache without mapping - component caching (search)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithoutMappingComponentCachingSearchResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForAssignment();
            CacheType cache = createCacheWithoutMapping(formulaRepresentation.get(), CacheTypeEnum::COMPONENT);
            processSearch(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache with mapping - hypergraph cut caching
     */
    TEST_CASE("[Cache] cache with mapping - hypergraph cut caching", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithMappingHypergraphCutCachingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithMapping(formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT);
            printCache(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache with mapping - hypergraph cut caching (create cache record)
     */
    TEST_CASE("[Cache] cache with mapping - hypergraph cut caching (create cache record)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithMappingHypergraphCutCachingCreateCacheRecordResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithMapping(formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT);
            processCreateCacheRecord(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache with mapping - hypergraph cut caching (add cache record)
     */
    TEST_CASE("[Cache] cache with mapping - hypergraph cut caching (add cache record)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithMappingHypergraphCutCachingAddCacheRecordResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithMapping(formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT);
            processAddCacheRecord(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache with mapping - hypergraph cut caching (assignment)
     */
    TEST_CASE("[Cache] cache with mapping - hypergraph cut caching (assignment)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithMappingHypergraphCutCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForAssignment();
            CacheType cache = createCacheWithMapping(formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT);
            processAssignment(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache with mapping - hypergraph cut caching (search)
     */
    TEST_CASE("[Cache] cache with mapping - hypergraph cut caching (search)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithMappingHypergraphCutCachingSearchResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForAssignment();
            CacheType cache = createCacheWithMapping(formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT);
            processSearch(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache with mapping - hypergraph cut caching (create mapping)
     */
    TEST_CASE("[Cache] cache with mapping - hypergraph cut caching (create mapping)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithMappingHypergraphCutCachingCreateMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithMapping(formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT);
            processCreateMapping(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache without mapping - hypergraph cut caching
     */
    TEST_CASE("[Cache] cache without mapping - hypergraph cut caching", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithoutMappingHypergraphCutCachingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithoutMapping(formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT);
            printCache(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache without mapping - hypergraph cut caching (create cache record)
     */
    TEST_CASE("[Cache] cache without mapping - hypergraph cut caching (create cache record)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithoutMappingHypergraphCutCachingCreateCacheRecordResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithoutMapping(formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT);
            processCreateCacheRecord(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache without mapping - hypergraph cut caching (add cache record)
     */
    TEST_CASE("[Cache] cache without mapping - hypergraph cut caching (add cache record)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithoutMappingHypergraphCutCachingAddCacheRecordResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula();
            CacheType cache = createCacheWithoutMapping(formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT);
            processAddCacheRecord(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache without mapping - hypergraph cut caching (assignment)
     */
    TEST_CASE("[Cache] cache without mapping - hypergraph cut caching (assignment)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithoutMappingHypergraphCutCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForAssignment();
            CacheType cache = createCacheWithoutMapping(formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT);
            processAssignment(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache without mapping - hypergraph cut caching (search)
     */
    TEST_CASE("[Cache] cache without mapping - hypergraph cut caching (search)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithoutMappingHypergraphCutCachingSearchResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForAssignment();
            CacheType cache = createCacheWithoutMapping(formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT);
            processSearch(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache without mapping - component caching (char)
     */
    TEST_CASE("[Cache] cache without mapping - component caching (char)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithoutMappingComponentCachingCharResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaLiteralChar();
            CacheType cache = createCacheWithoutMapping(formulaRepresentation.get(), CacheTypeEnum::COMPONENT);

            VariableSetVectorType currentComponentVariableSetVector { { 1, 2, 127 }, { 3, 4, 128 }, { 5, 6, 32767 }, { 7, 8, 32768 } };
            processChar(cache, currentComponentVariableSetVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache without mapping - hypergraph cut caching (char)
     */
    TEST_CASE("[Cache] cache without mapping - hypergraph cut caching (char)", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheWithoutMappingHypergraphCutCachingCharResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar();
            CacheType cache = createCacheWithoutMapping(formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT);

            VariableSetVectorType currentComponentVariableSetVector { { 1, 2, 255 }, { 3, 4, 256 }, { 5, 6, 65535 }, { 7, 8, 65536 } };
            processChar(cache, currentComponentVariableSetVector, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Cache
