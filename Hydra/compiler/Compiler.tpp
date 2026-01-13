#pragma once

#include "Hydra/cache/cacheCleaningStrategy/enums/CacheCleaningStrategyTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/CachingSchemeTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/CachingSchemeVariantTypeEnum.hpp"
#include "Hydra/circuit/enums/CircuitTypeEnum.hpp"
#include "Hydra/compiler/enums/PartitioningHypergraphTypeEnum.hpp"
#include "Hydra/compiler/enums/RecomputingHypergraphCutTypeEnum.hpp"
#include "Hydra/decisionHeuristic/enums/DecisionHeuristicTypeEnum.hpp"
#include "Hydra/partitioningHypergraph/enums/VertexWeightTypeEnum.hpp"
#include "Hydra/satSolver/enums/ImplicitBcpVariableOrderTypeEnum.hpp"
#include "Hydra/satSolver/enums/SatSolverTypeEnum.hpp"

#include "Hydra/cache/cacheCleaningStrategy/cara/CaraCacheCleaningStrategy.tpp"
#include "Hydra/cache/cacheCleaningStrategy/sharpSat/SharpSatCacheCleaningStrategy.tpp"
#include "Hydra/cache/cachingScheme/basic/BasicCachingScheme.tpp"
#include "Hydra/cache/cachingScheme/cara/CaraCachingScheme.tpp"
#include "Hydra/cache/cachingScheme/hybrid/HybridCachingScheme.tpp"
#include "Hydra/cache/cachingScheme/standard/StandardCachingScheme.tpp"
#include "Hydra/decisionHeuristic/jeroslowWang/JeroslowWangDecisionHeuristic.tpp"
#include "Hydra/decisionHeuristic/literalCount/LiteralCountDecisionHeuristic.tpp"
#include "Hydra/decisionHeuristic/random/RandomDecisionHeuristic.tpp"
#include "Hydra/decisionHeuristic/upc/UpcDecisionHeuristic.tpp"
#include "Hydra/decisionHeuristic/vsads/VsadsDecisionHeuristic.tpp"
#include "Hydra/decisionHeuristic/vsids/VsidsDecisionHeuristic.tpp"
#include "Hydra/partitioningHypergraph/cara/CaraPartitioningHypergraph.tpp"
#include "Hydra/partitioningHypergraph/hmetis/HmetisPartitioningHypergraph.tpp"
#include "Hydra/partitioningHypergraph/kahypar/KahyparPartitioningHypergraph.tpp"
#include "Hydra/partitioningHypergraph/patoh/PatohPartitioningHypergraph.tpp"
#include "Hydra/satSolver/minisat/MiniSatSolver.tpp"

namespace Hydra {

    /**
     * Compiler - configuration
     */
    struct CompilerConfiguration {
    public:
        using MiniSatSolverConfigurationType = SatSolver::MiniSat::MiniSatSolverConfiguration;
        using CaraCachingSchemeConfigurationType = Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration;
        using UpcDecisionHeuristicConfigurationType = DecisionHeuristic::Upc::UpcDecisionHeuristicConfiguration;
        using BasicCachingSchemeConfigurationType = Cache::CachingScheme::Basic::BasicCachingSchemeConfiguration;
        using HybridCachingSchemeConfigurationType = Cache::CachingScheme::Hybrid::HybridCachingSchemeConfiguration;
        using VsadsDecisionHeuristicConfigurationType = DecisionHeuristic::Vsads::VsadsDecisionHeuristicConfiguration;
        using VsidsDecisionHeuristicConfigurationType = DecisionHeuristic::Vsids::VsidsDecisionHeuristicConfiguration;
        using RandomDecisionHeuristicConfigurationType = DecisionHeuristic::Random::RandomDecisionHeuristicConfiguration;
        using StandardCachingSchemeConfigurationType = Cache::CachingScheme::Standard::StandardCachingSchemeConfiguration;
        using CaraPartitioningHypergraphConfigurationType = PartitioningHypergraph::Cara::CaraPartitioningHypergraphConfiguration;
        using PatohPartitioningHypergraphConfigurationType = PartitioningHypergraph::Patoh::PatohPartitioningHypergraphConfiguration;
        using CaraCacheCleaningStrategyConfigurationType = Cache::CacheCleaningStrategy::Cara::CaraCacheCleaningStrategyConfiguration;
        using HmetisPartitioningHypergraphConfigurationType = PartitioningHypergraph::Hmetis::HmetisPartitioningHypergraphConfiguration;
        using KahyparPartitioningHypergraphConfigurationType = PartitioningHypergraph::Kahypar::KahyparPartitioningHypergraphConfiguration;
        using JeroslowWangDecisionHeuristicConfigurationType = DecisionHeuristic::JeroslowWang::JeroslowWangDecisionHeuristicConfiguration;
        using LiteralCountDecisionHeuristicConfigurationType = DecisionHeuristic::LiteralCount::LiteralCountDecisionHeuristicConfiguration;
        using SharpSatCacheCleaningStrategyConfigurationType = Cache::CacheCleaningStrategy::SharpSat::SharpSatCacheCleaningStrategyConfiguration;

    public:
        using CircuitTypeEnum = Circuit::CircuitTypeEnum;
        using SatSolverTypeEnum = SatSolver::SatSolverTypeEnum;
        using VertexWeightTypeEnum = PartitioningHypergraph::VertexWeightTypeEnum;
        using CachingSchemeTypeEnum = Cache::CachingScheme::CachingSchemeTypeEnum;
        using DecisionHeuristicTypeEnum = DecisionHeuristic::DecisionHeuristicTypeEnum;
        using ImplicitBcpVariableOrderTypeEnum = SatSolver::ImplicitBcpVariableOrderTypeEnum;
        using CachingSchemeVariantTypeEnum = Cache::CachingScheme::CachingSchemeVariantTypeEnum;
        using CacheCleaningStrategyTypeEnum = Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum;

    public:
        /**
         * Cache cleaning strategy (component caching)
         */
        CacheCleaningStrategyTypeEnum cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::NONE;
        CaraCacheCleaningStrategyConfigurationType caraCacheCleaningStrategyComponentCachingConfiguration;
        SharpSatCacheCleaningStrategyConfigurationType sharpSatCacheCleaningStrategyComponentCachingConfiguration;

        /**
         * Cache cleaning strategy (hypergraph cut caching)
         */
        CacheCleaningStrategyTypeEnum cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::NONE;
        CaraCacheCleaningStrategyConfigurationType caraCacheCleaningStrategyHypergraphCutCachingConfiguration;
        SharpSatCacheCleaningStrategyConfigurationType sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration;

        /**
         * Caching scheme (component caching)
         */
        CachingSchemeTypeEnum cachingSchemeComponentCachingType = CachingSchemeTypeEnum::NONE;
        CachingSchemeVariantTypeEnum cachingSchemeVariantComponentCachingType = CachingSchemeVariantTypeEnum::NONE;
        CaraCachingSchemeConfigurationType caraCachingSchemeComponentCachingConfiguration;
        BasicCachingSchemeConfigurationType basicCachingSchemeComponentCachingConfiguration;
        HybridCachingSchemeConfigurationType hybridCachingSchemeComponentCachingConfiguration;
        StandardCachingSchemeConfigurationType standardCachingSchemeComponentCachingConfiguration;

        /**
         * Caching scheme (hypergraph cut caching)
         */
        CachingSchemeTypeEnum cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::NONE;
        CaraCachingSchemeConfigurationType caraCachingSchemeHypergraphCutCachingConfiguration;
        BasicCachingSchemeConfigurationType basicCachingSchemeHypergraphCutCachingConfiguration;
        HybridCachingSchemeConfigurationType hybridCachingSchemeHypergraphCutCachingConfiguration;
        StandardCachingSchemeConfigurationType standardCachingSchemeHypergraphCutCachingConfiguration;

        /**
         * Circuit
         */
        CircuitTypeEnum circuitType = CircuitTypeEnum::sd_DNNF;

        /**
         * SAT solver
         */
        SatSolverTypeEnum satSolverType = SatSolverTypeEnum::MINISAT;
        MiniSatSolverConfigurationType miniSatSolverConfiguration;

        /**
         * Decision heuristic
         */
        DecisionHeuristicTypeEnum decisionHeuristicType = DecisionHeuristicTypeEnum::VSADS;
        UpcDecisionHeuristicConfigurationType upcDecisionHeuristicConfiguration;
        VsadsDecisionHeuristicConfigurationType vsadsDecisionHeuristicConfiguration;
        VsidsDecisionHeuristicConfigurationType vsidsDecisionHeuristicConfiguration;
        RandomDecisionHeuristicConfigurationType randomDecisionHeuristicConfiguration;
        JeroslowWangDecisionHeuristicConfigurationType jeroslowWangDecisionHeuristicConfiguration;
        LiteralCountDecisionHeuristicConfigurationType literalCountDecisionHeuristicConfiguration;

        /**
         * Partitioning hypergraph
         */
        bool allowEmptyHypergraphCut = true;
        bool allowSingletonHyperedge = false;
        bool useEquivalenceSimplificationMethod = true;
        bool ignoreMultiOccurrentIgnoredVariables = false;
        std::size_t notEnoughVariablesForComputingHypergraphCut = 6;     // 0 = ignore
        std::size_t tooManyVariablesForComputingHypergraphCut = 5'000;   // 0 = ignore
        VertexWeightTypeEnum vertexWeightType = VertexWeightTypeEnum::STANDARD;
        double percentageThresholdOfImmenseUnitPropagationRecomputingHypergraphCut = 0.7;   // percentage
        RecomputingHypergraphCutTypeEnum recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::ALWAYS;
        PartitioningHypergraphTypeEnum partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;
        ImplicitBcpVariableOrderTypeEnum implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX;
        CaraPartitioningHypergraphConfigurationType caraPartitioningHypergraphConfiguration;
        PatohPartitioningHypergraphConfigurationType patohPartitioningHypergraphConfiguration;
        HmetisPartitioningHypergraphConfigurationType hmetisPartitioningHypergraphConfiguration;
        KahyparPartitioningHypergraphConfigurationType kahyparPartitioningHypergraphConfiguration;

        #if defined(CARA_SOLVER)
        /**
         * Brute-force approach
         */
        std::size_t numberOfClausesThresholdForBruteForceApproach = 8;     // 0 = ignore
        std::size_t numberOfVariablesThresholdForBruteForceApproach = 6;   // 0 = ignore
        #endif
    };
}   // namespace Hydra
