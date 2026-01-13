#pragma once

#include "./Compiler.hpp"

namespace Hydra {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void Compiler<VarT, LiteralT, ClauseIdT>::initializeComponentCache() {
        // Cache cleaning strategy
        CacheCleaningStrategyAbstractUniquePtrType<ComponentCacheValueType> cacheCleaningStrategyAbstractUniquePtr(nullptr);
        switch (configuration_.cacheCleaningStrategyComponentCachingType) {
            case CacheCleaningStrategyTypeEnum::CARA:
                cacheCleaningStrategyAbstractUniquePtr = std::make_unique<CaraCacheCleaningStrategyType<ComponentCacheValueType>>(configuration_.caraCacheCleaningStrategyComponentCachingConfiguration);
                break;
            case CacheCleaningStrategyTypeEnum::NONE:
                cacheCleaningStrategyAbstractUniquePtr = std::make_unique<NoneCacheCleaningStrategyType<ComponentCacheValueType>>();
                break;
            case CacheCleaningStrategyTypeEnum::SHARP_SAT:
                cacheCleaningStrategyAbstractUniquePtr = std::make_unique<SharpSatCacheCleaningStrategyType<ComponentCacheValueType>>(configuration_.sharpSatCacheCleaningStrategyComponentCachingConfiguration);
                break;
            default:
                throw Exception::NotImplementedException(Cache::CacheCleaningStrategy::cacheCleaningStrategyTypeEnumToString(configuration_.cacheCleaningStrategyComponentCachingType),
                                                         "Hydra::Compiler::initializeComponentCache");
        }

        // Caching scheme
        CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr(nullptr);
        switch (configuration_.cachingSchemeComponentCachingType) {
            case CachingSchemeTypeEnum::BASIC:
                cachingSchemeAbstractUniquePtr = std::make_unique<BasicCachingSchemeType>(formulaRepresentationAbstractUniquePtr_.get(), CacheTypeEnum::COMPONENT,
                                                                                          configuration_.basicCachingSchemeComponentCachingConfiguration);
                break;
            case CachingSchemeTypeEnum::CARA:
                cachingSchemeAbstractUniquePtr = std::make_unique<CaraCachingSchemeType>(formulaRepresentationAbstractUniquePtr_.get(), CacheTypeEnum::COMPONENT,
                                                                                         configuration_.caraCachingSchemeComponentCachingConfiguration);
                break;
            case CachingSchemeTypeEnum::HYBRID:
                cachingSchemeAbstractUniquePtr = std::make_unique<HybridCachingSchemeType>(formulaRepresentationAbstractUniquePtr_.get(), CacheTypeEnum::COMPONENT,
                                                                                           configuration_.hybridCachingSchemeComponentCachingConfiguration);
                break;
            case CachingSchemeTypeEnum::NONE:
                cachingSchemeAbstractUniquePtr = std::make_unique<NoneCachingSchemeType>(formulaRepresentationAbstractUniquePtr_.get(), CacheTypeEnum::COMPONENT);
                break;
            case CachingSchemeTypeEnum::STANDARD:
                cachingSchemeAbstractUniquePtr = std::make_unique<StandardCachingSchemeType>(formulaRepresentationAbstractUniquePtr_.get(), CacheTypeEnum::COMPONENT,
                                                                                             configuration_.standardCachingSchemeComponentCachingConfiguration);
                break;
            default:
                throw Exception::NotImplementedException(Cache::CachingScheme::cachingSchemeTypeEnumToString(configuration_.cachingSchemeComponentCachingType),
                                                         "Hydra::Compiler::initializeComponentCache");
        }

        componentCacheUniquePtr_ = std::make_unique<ComponentCacheType>(std::move(cachingSchemeAbstractUniquePtr), std::move(cacheCleaningStrategyAbstractUniquePtr),
                                                                        statisticsPtr_ ? statisticsPtr_->getComponentCacheStatisticsPtr() : nullptr);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void Compiler<VarT, LiteralT, ClauseIdT>::initializeHypergraphCutCache() {
        // Cache cleaning strategy
        CacheCleaningStrategyAbstractUniquePtrType<HypergraphCutCacheValueType> cacheCleaningStrategyAbstractUniquePtr(nullptr);
        switch (configuration_.cacheCleaningStrategyHypergraphCutCachingType) {
            case CacheCleaningStrategyTypeEnum::CARA:
                cacheCleaningStrategyAbstractUniquePtr = std::make_unique<CaraCacheCleaningStrategyType<HypergraphCutCacheValueType>>(configuration_.caraCacheCleaningStrategyHypergraphCutCachingConfiguration);
                break;
            case CacheCleaningStrategyTypeEnum::NONE:
                cacheCleaningStrategyAbstractUniquePtr = std::make_unique<NoneCacheCleaningStrategyType<HypergraphCutCacheValueType>>();
                break;
            case CacheCleaningStrategyTypeEnum::SHARP_SAT:
                cacheCleaningStrategyAbstractUniquePtr = std::make_unique<SharpSatCacheCleaningStrategyType<HypergraphCutCacheValueType>>(configuration_.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration);
                break;
            default:
                throw Exception::NotImplementedException(Cache::CacheCleaningStrategy::cacheCleaningStrategyTypeEnumToString(configuration_.cacheCleaningStrategyHypergraphCutCachingType),
                                                         "Hydra::Compiler::initializeHypergraphCutCache");
        }

        // Caching scheme
        CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr(nullptr);
        switch (configuration_.cachingSchemeHypergraphCutCachingType) {
            case CachingSchemeTypeEnum::BASIC:
                cachingSchemeAbstractUniquePtr = std::make_unique<BasicCachingSchemeType>(formulaRepresentationAbstractUniquePtr_.get(), CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                          configuration_.basicCachingSchemeHypergraphCutCachingConfiguration);
                break;
            case CachingSchemeTypeEnum::CARA:
                cachingSchemeAbstractUniquePtr = std::make_unique<CaraCachingSchemeType>(formulaRepresentationAbstractUniquePtr_.get(), CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                         configuration_.caraCachingSchemeHypergraphCutCachingConfiguration);
                break;
            case CachingSchemeTypeEnum::HYBRID:
                cachingSchemeAbstractUniquePtr = std::make_unique<HybridCachingSchemeType>(formulaRepresentationAbstractUniquePtr_.get(), CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                           configuration_.hybridCachingSchemeHypergraphCutCachingConfiguration);
                break;
            case CachingSchemeTypeEnum::NONE:
                cachingSchemeAbstractUniquePtr = std::make_unique<NoneCachingSchemeType>(formulaRepresentationAbstractUniquePtr_.get(), CacheTypeEnum::HYPERGRAPH_CUT);
                break;
            case CachingSchemeTypeEnum::STANDARD:
                cachingSchemeAbstractUniquePtr = std::make_unique<StandardCachingSchemeType>(formulaRepresentationAbstractUniquePtr_.get(), CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                             configuration_.standardCachingSchemeHypergraphCutCachingConfiguration);
                break;
            default:
                throw Exception::NotImplementedException(Cache::CachingScheme::cachingSchemeTypeEnumToString(configuration_.cachingSchemeHypergraphCutCachingType),
                                                         "Hydra::Compiler::initializeHypergraphCutCache");
        }

        hypergraphCutCacheUniquePtr_ = std::make_unique<HypergraphCutCacheType>(std::move(cachingSchemeAbstractUniquePtr), std::move(cacheCleaningStrategyAbstractUniquePtr),
                                                                                statisticsPtr_ ? statisticsPtr_->getHypergraphCutCacheStatisticsPtr() : nullptr);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void Compiler<VarT, LiteralT, ClauseIdT>::initializeSatSolver() {
        switch (configuration_.satSolverType) {
            case SatSolverTypeEnum::MINISAT:
                satSolverAbstractUniquePtr_ = std::make_unique<MiniSatSolverType>(formulaRepresentationAbstractUniquePtr_.get(), false,
                                                                                  configuration_.miniSatSolverConfiguration,
                                                                                  statisticsPtr_ ? statisticsPtr_->getSatSolverStatisticsPtr() : nullptr);
                break;
            case SatSolverTypeEnum::CADICAL:
                satSolverAbstractUniquePtr_ = std::make_unique<CadicalSolverType>(formulaRepresentationAbstractUniquePtr_.get(),
                                                                                  statisticsPtr_ ? statisticsPtr_->getSatSolverStatisticsPtr() : nullptr);
                break;
            default:
                throw Exception::NotImplementedException(SatSolver::satSolverTypeEnumToString(configuration_.satSolverType),
                                                         "Hydra::Compiler::initializeSatSolver");
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void Compiler<VarT, LiteralT, ClauseIdT>::initializeDecisionHeuristic() {
        switch (configuration_.decisionHeuristicType) {
            case DecisionHeuristicTypeEnum::JEROSLOW_WANG_ONE_SIDED:
            case DecisionHeuristicTypeEnum::JEROSLOW_WANG_TWO_SIDED:
                configuration_.jeroslowWangDecisionHeuristicConfiguration.twoSidedVariant = (configuration_.decisionHeuristicType == DecisionHeuristicTypeEnum::JEROSLOW_WANG_TWO_SIDED);
                decisionHeuristicAbstractUniquePtr_ = std::make_unique<JeroslowWangDecisionHeuristicType>(formulaRepresentationAbstractUniquePtr_.get(),
                                                                                                          satSolverAbstractUniquePtr_.get(),
                                                                                                          ignorePureLiteralType_,
                                                                                                          configuration_.jeroslowWangDecisionHeuristicConfiguration,
                                                                                                          statisticsPtr_ ? statisticsPtr_->getDecisionHeuristicStatisticsPtr() : nullptr);
                break;
            case DecisionHeuristicTypeEnum::DLCS:
            case DecisionHeuristicTypeEnum::DLIS:
            case DecisionHeuristicTypeEnum::DLCS_DLIS:
                configuration_.literalCountDecisionHeuristicConfiguration.decisionHeuristicType = configuration_.decisionHeuristicType;
                decisionHeuristicAbstractUniquePtr_ = std::make_unique<LiteralCountDecisionHeuristicType>(formulaRepresentationAbstractUniquePtr_.get(),
                                                                                                          satSolverAbstractUniquePtr_.get(),
                                                                                                          ignorePureLiteralType_,
                                                                                                          configuration_.literalCountDecisionHeuristicConfiguration,
                                                                                                          statisticsPtr_ ? statisticsPtr_->getDecisionHeuristicStatisticsPtr() : nullptr);
                break;
            case DecisionHeuristicTypeEnum::RANDOM:
                decisionHeuristicAbstractUniquePtr_ = std::make_unique<RandomDecisionHeuristicType>(formulaRepresentationAbstractUniquePtr_.get(),
                                                                                                    satSolverAbstractUniquePtr_.get(),
                                                                                                    ignorePureLiteralType_,
                                                                                                    configuration_.randomDecisionHeuristicConfiguration,
                                                                                                    statisticsPtr_ ? statisticsPtr_->getDecisionHeuristicStatisticsPtr() : nullptr);
                break;
            case DecisionHeuristicTypeEnum::AUPC:
            case DecisionHeuristicTypeEnum::EUPC:
                configuration_.upcDecisionHeuristicConfiguration.exactVariant = (configuration_.decisionHeuristicType == DecisionHeuristicTypeEnum::EUPC);
                decisionHeuristicAbstractUniquePtr_ = std::make_unique<UpcDecisionHeuristicType>(formulaRepresentationAbstractUniquePtr_.get(),
                                                                                                 satSolverAbstractUniquePtr_.get(),
                                                                                                 ignorePureLiteralType_,
                                                                                                 configuration_.upcDecisionHeuristicConfiguration,
                                                                                                 statisticsPtr_ ? statisticsPtr_->getDecisionHeuristicStatisticsPtr() : nullptr);
                break;
            case DecisionHeuristicTypeEnum::VSADS:
                decisionHeuristicAbstractUniquePtr_ = std::make_unique<VsadsDecisionHeuristicType>(formulaRepresentationAbstractUniquePtr_.get(),
                                                                                                   satSolverAbstractUniquePtr_.get(),
                                                                                                   ignorePureLiteralType_,
                                                                                                   configuration_.vsadsDecisionHeuristicConfiguration,
                                                                                                   statisticsPtr_ ? statisticsPtr_->getDecisionHeuristicStatisticsPtr() : nullptr);
                break;
            case DecisionHeuristicTypeEnum::VSIDS:
                decisionHeuristicAbstractUniquePtr_ = std::make_unique<VsidsDecisionHeuristicType>(formulaRepresentationAbstractUniquePtr_.get(),
                                                                                                   satSolverAbstractUniquePtr_.get(),
                                                                                                   ignorePureLiteralType_,
                                                                                                   configuration_.vsidsDecisionHeuristicConfiguration,
                                                                                                   statisticsPtr_ ? statisticsPtr_->getDecisionHeuristicStatisticsPtr() : nullptr);
                break;
            default:
                throw Exception::NotImplementedException(DecisionHeuristic::decisionHeuristicTypeEnumToString(configuration_.decisionHeuristicType),
                                                         "Hydra::Compiler::initializeDecisionHeuristic");
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void Compiler<VarT, LiteralT, ClauseIdT>::initializePartitioningHypergraph() {
        switch (configuration_.partitioningHypergraphType) {
            // Cara
            case PartitioningHypergraphTypeEnum::CARA:
            case PartitioningHypergraphTypeEnum::CARA_SPEED:
                assert(componentCacheUniquePtr_);

                #if OPERATING_SYSTEM_MACOS || OPERATING_SYSTEM_LINUX
                partitioningHypergraphAbstractUniquePtr_ = std::make_unique<CaraPartitioningHypergraphType>(formulaRepresentationAbstractUniquePtr_.get(), componentCacheUniquePtr_.get(),
                                                                                                            configuration_.allowEmptyHypergraphCut, configuration_.allowSingletonHyperedge,
                                                                                                            ignorePureLiteralType_, configuration_.vertexWeightType,
                                                                                                            configuration_.caraPartitioningHypergraphConfiguration,
                                                                                                            statisticsPtr_ ? statisticsPtr_->getPartitioningHypergraphStatisticsPtr() : nullptr);
                #else
                throw Exception::OperatingSystemIsNotSupportedException();
                #endif
                break;
            // KaHyPar
            case PartitioningHypergraphTypeEnum::KAHYPAR:
                partitioningHypergraphAbstractUniquePtr_ = std::make_unique<KahyparPartitioningHypergraphType>(formulaRepresentationAbstractUniquePtr_.get(),
                                                                                                               configuration_.allowEmptyHypergraphCut, configuration_.allowSingletonHyperedge,
                                                                                                               ignorePureLiteralType_, configuration_.vertexWeightType,
                                                                                                               configuration_.kahyparPartitioningHypergraphConfiguration,
                                                                                                               statisticsPtr_ ? statisticsPtr_->getPartitioningHypergraphStatisticsPtr() : nullptr);
                break;
            // PaToH (Linux, macOS) or hMETIS (Windows)
            case PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS:
                #if OPERATING_SYSTEM_WINDOWS
                partitioningHypergraphAbstractUniquePtr_ = std::make_unique<HmetisPartitioningHypergraphType>(formulaRepresentationAbstractUniquePtr_.get(),
                                                                                                              configuration_.allowEmptyHypergraphCut, configuration_.allowSingletonHyperedge,
                                                                                                              ignorePureLiteralType_, configuration_.vertexWeightType,
                                                                                                              configuration_.hmetisPartitioningHypergraphConfiguration,
                                                                                                              statisticsPtr_ ? statisticsPtr_->getPartitioningHypergraphStatisticsPtr() : nullptr);
                #elif OPERATING_SYSTEM_MACOS
                partitioningHypergraphAbstractUniquePtr_ = std::make_unique<PatohPartitioningHypergraphType>(formulaRepresentationAbstractUniquePtr_.get(),
                                                                                                             configuration_.allowEmptyHypergraphCut, configuration_.allowSingletonHyperedge,
                                                                                                             ignorePureLiteralType_, configuration_.vertexWeightType,
                                                                                                             configuration_.patohPartitioningHypergraphConfiguration,
                                                                                                             statisticsPtr_ ? statisticsPtr_->getPartitioningHypergraphStatisticsPtr() : nullptr);
                #elif OPERATING_SYSTEM_LINUX
                partitioningHypergraphAbstractUniquePtr_ = std::make_unique<PatohPartitioningHypergraphType>(formulaRepresentationAbstractUniquePtr_.get(),
                                                                                                             configuration_.allowEmptyHypergraphCut, configuration_.allowSingletonHyperedge,
                                                                                                             ignorePureLiteralType_, configuration_.vertexWeightType,
                                                                                                             configuration_.patohPartitioningHypergraphConfiguration,
                                                                                                             statisticsPtr_ ? statisticsPtr_->getPartitioningHypergraphStatisticsPtr() : nullptr);
                #else
                throw Exception::OperatingSystemIsNotSupportedException();
                #endif
                break;
            default:
                throw Exception::NotImplementedException(partitioningHypergraphTypeEnumToString(configuration_.partitioningHypergraphType),
                                                         "Hydra::Compiler::initializePartitioningHypergraph");
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool Compiler<VarT, LiteralT, ClauseIdT>::shouldHypergraphCutBeRecomputed(const VariableSetType& restrictedHypergraphCut,
                                                                              [[maybe_unused]] const VariableSetType& unrestrictedHypergraphCut,
                                                                              bool split, VarT numberOfVariablesBeforeUnitPropagation,
                                                                              VarT numberOfVariablesAfterUnitPropagation) const {
        // The current hypergraph cut is empty
        if (Other::containInSet(emptyCutRecomputingHypergraphCutTypeSet, configuration_.recomputingHypergraphCutType)) {
            if (restrictedHypergraphCut.empty())
                return true;
        }

        // The current formula is split
        if (Other::containInSet(formulaSplitRecomputingHypergraphCutTypeSet, configuration_.recomputingHypergraphCutType)) {
            if (split)
                return true;
        }

        switch (configuration_.recomputingHypergraphCutType) {
            case RecomputingHypergraphCutTypeEnum::ALWAYS:
                return true;
            case RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION:
            case RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION_OR_WHEN_CURRENT_FORMULA_IS_SPLIT:
                if (static_cast<double>(numberOfVariablesAfterUnitPropagation) / static_cast<double>(numberOfVariablesBeforeUnitPropagation) <= configuration_.percentageThresholdOfImmenseUnitPropagationRecomputingHypergraphCut)
                    return true;

                return false;
            case RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_FORMULA_IS_SPLIT:
            case RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY:
                return false;
            default:
                throw Exception::NotImplementedException(recomputingHypergraphCutTypeEnumToString(configuration_.recomputingHypergraphCutType),
                                                         "Hydra::Compiler::shouldHypergraphCutBeRecomputed");
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename Compiler<VarT, LiteralT, ClauseIdT>::VariableVectorType
    Compiler<VarT, LiteralT, ClauseIdT>::assignLiteralVectorInFormulaAndSatSolver(const LiteralVectorType& literalVector,
                                                                                  VariableSetType& currentComponentVariableSet,
                                                                                  bool setLiteralsInSatSolver) {
        if (literalVector.empty())
            return {};

        // Statistics
        if (compilerStatisticsPtr_)
            compilerStatisticsPtr_->assignLiteralTimer.startStopwatch();

        // Remove the literals that we want to assign from the current component
        for (const LiteralType& lit : literalVector) {
            assert(Other::containInSet(currentComponentVariableSet, lit.getVariable()));               // variable is in the current component
            assert(!formulaRepresentationAbstractUniquePtr_->isVariableAssigned(lit.getVariable()));   // variable is not assigned
            assert(!formulaRepresentationAbstractUniquePtr_->isVariableFree(lit.getVariable()));       // variable is not free

            currentComponentVariableSet.erase(lit.getVariable());
        }

        VariableVectorType freeVariableVector;
        freeVariableVector.reserve(currentComponentVariableSet.size());
        if (setLiteralsInSatSolver)
            satSolverAbstractUniquePtr_->assignLiteralVector(literalVector, false);
        formulaRepresentationAbstractUniquePtr_->addLiteralVectorToPartialAssignment(literalVector, freeVariableVector);

        #ifndef NDEBUG
        VariableSetType variableSetDebug(literalVector.size());
        for (const LiteralType& lit : literalVector)
            variableSetDebug.emplace(lit.getVariable());
        #endif

        // Remove the free variables from the current component
        for (VarT var : freeVariableVector) {
            assert(Other::containInSet(currentComponentVariableSet, var) || (Other::containInSet(variableSetDebug, var)));

            currentComponentVariableSet.erase(var);
        }

        #if defined(BELLA_COMPILER)
        // Free variables are needed only for smoothness
        if (!smoothness_)
            freeVariableVector.clear();
        #endif

        // Statistics
        if (compilerStatisticsPtr_)
            compilerStatisticsPtr_->assignLiteralTimer.stopStopwatch();

        return freeVariableVector;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void Compiler<VarT, LiteralT, ClauseIdT>::unassignLiteralVectorInFormulaAndSatSolver(const LiteralVectorType& literalVector,
                                                                                         VariableSetType& currentComponentVariableSet) {
        if (literalVector.empty())
            return;

        // Statistics
        if (compilerStatisticsPtr_)
            compilerStatisticsPtr_->unassignLiteralTimer.startStopwatch();

        // Add the literals that we want to unassign to the current component
        for (const LiteralType& lit : literalVector) {
            assert(formulaRepresentationAbstractUniquePtr_->isVariableAssigned(lit.getVariable()));   // variable is assigned
            assert(!Other::containInSet(currentComponentVariableSet, lit.getVariable()));             // variable is not in the current component

            currentComponentVariableSet.emplace(lit.getVariable());
        }

        VariableVectorType unfreeVariableVector;
        unfreeVariableVector.reserve(currentComponentVariableSet.size());   // approximately
        satSolverAbstractUniquePtr_->unassignLiteralVector(literalVector, true);
        formulaRepresentationAbstractUniquePtr_->removeLiteralVectorFromPartialAssignment(literalVector, unfreeVariableVector, true);

        #ifndef NDEBUG
        VariableSetType variableSetDebug(literalVector.size());
        for (const LiteralType& lit : literalVector)
            variableSetDebug.emplace(lit.getVariable());
        #endif

        // Add the unfree variables to the current component
        for (VarT var : unfreeVariableVector) {
            assert(!Other::containInSet(currentComponentVariableSet, var) || Other::containInSet(variableSetDebug, var));

            currentComponentVariableSet.emplace(var);
        }

        // Statistics
        if (compilerStatisticsPtr_)
            compilerStatisticsPtr_->unassignLiteralTimer.stopStopwatch();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename Compiler<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType
    Compiler<VarT, LiteralT, ClauseIdT>::getFormulaPtr() const noexcept {
        return formulaRepresentationAbstractUniquePtr_.get();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename Compiler<VarT, LiteralT, ClauseIdT>::StatisticsPtrType
    Compiler<VarT, LiteralT, ClauseIdT>::getStatisticsPtr() const noexcept {
        return statisticsPtr_;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void Compiler<VarT, LiteralT, ClauseIdT>::printCompilerDebug(std::ostream& out) {
        Other::printTitle(out, "Formula", 40, '-');
        formulaRepresentationAbstractUniquePtr_->printFormulaRepresentationDebug(out);

        #if defined(BELLA_COMPILER)
        Other::printTitle(out, "Circuit", 40, '-');
        circuitUniquePtr_->printCircuitDebug(out);
        #endif

        Other::printTitle(out, "Component cache", 40, '-');
        componentCacheUniquePtr_->printCacheDebug(out, false, true, true);

        Other::printTitle(out, "Hypergraph cut cache", 40, '-');
        hypergraphCutCacheUniquePtr_->printCacheDebug(out, false, true, true);

        Other::printTitle(out, "SAT solver", 40, '-');
        satSolverAbstractUniquePtr_->printSatSolverDebug(out, true, false, false);

        Other::printTitle(out, "Decision heuristic", 40, '-');
        decisionHeuristicAbstractUniquePtr_->printDecisionHeuristicDebug(out, false);

        Other::printTitle(out, "Partitioning hypergraph", 40, '-');
        partitioningHypergraphAbstractUniquePtr_->printPartitioningHypergraphDebug(out, false);
    }
    #endif
}   // namespace Hydra
