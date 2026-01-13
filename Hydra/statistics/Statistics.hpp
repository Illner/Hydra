#pragma once

#include <ostream>

#include "Hydra/other/Other.hpp"

#include "Hydra/cache/enums/CacheTypeEnum.hpp"

#include "Hydra/cache/Cache.hxx"
#include "Hydra/circuit/Circuit.hxx"
#include "Hydra/compiler/Compiler.hxx"
#include "Hydra/decisionHeuristic/DecisionHeuristicAbstract.hxx"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hxx"
#include "Hydra/partitioningHypergraph/PartitioningHypergraphAbstract.hxx"
#include "Hydra/renHCRecognition/RenHCRecognitionAbstract.hxx"
#include "Hydra/satSolver/SatSolverAbstract.hxx"

namespace Hydra::Statistics {

    /**
     * Statistics
     */
    struct Statistics {
    private:
        using CompilerStatisticsType = CompilerStatistics;
        using CacheStatisticsType = Cache::CacheStatistics;
        using CircuitStatisticsType = Circuit::CircuitStatistics;
        using SatSolverStatisticsType = SatSolver::SatSolverStatistics;
        using RenHCRecognitionStatisticsType = RenHCRecognition::RenHCRecognitionStatistics;
        using DecisionHeuristicStatisticsType = DecisionHeuristic::DecisionHeuristicStatistics;
        using FormulaRepresentationStatisticsType = Formula::Representation::FormulaRepresentationStatistics;
        using PartitioningHypergraphStatisticsType = PartitioningHypergraph::PartitioningHypergraphStatistics;

    public:
        using CacheStatisticsPtrType = typename Cache::CacheStatistics::CacheStatisticsPtrType;
        using CompilerStatisticsPtrType = typename CompilerStatistics::CompilerStatisticsPtrType;
        using CircuitStatisticsPtrType = typename Circuit::CircuitStatistics::CircuitStatisticsPtrType;
        using SatSolverStatisticsPtrType = typename SatSolver::SatSolverStatistics::SatSolverStatisticsPtrType;
        using RenHCRecognitionStatisticsPtrType = typename RenHCRecognition::RenHCRecognitionStatistics::RenHCRecognitionStatisticsPtrType;
        using DecisionHeuristicStatisticsPtrType = typename DecisionHeuristic::DecisionHeuristicStatistics::DecisionHeuristicStatisticsPtrType;
        using FormulaRepresentationStatisticsPtrType = typename Formula::Representation::FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType;
        using PartitioningHypergraphStatisticsPtrType = typename PartitioningHypergraph::PartitioningHypergraphStatistics::PartitioningHypergraphStatisticsPtrType;

    public:
        using StatisticsPtrType = Statistics*;

    private:
        CircuitStatisticsType circuitStatistics_;
        CompilerStatisticsType compilerStatistics_;
        SatSolverStatisticsType satSolverStatistics_;
        RenHCRecognitionStatisticsType renHCRecognitionStatistics_;
        DecisionHeuristicStatisticsType decisionHeuristicStatistics_;
        FormulaRepresentationStatisticsType formulaRepresentationStatistics_;
        PartitioningHypergraphStatisticsType partitioningHypergraphStatistics_;
        CacheStatisticsType componentCacheStatistics_ = CacheStatisticsType(Cache::CacheTypeEnum::COMPONENT);
        CacheStatisticsType hypergraphCutCacheStatistics_ = CacheStatisticsType(Cache::CacheTypeEnum::HYPERGRAPH_CUT);

    public:
        /**
         * @return a pointer to the decision heuristic statistics
         */
        DecisionHeuristicStatisticsPtrType getDecisionHeuristicStatisticsPtr() noexcept;

        /**
         * @return a pointer to the SAT solver statistics
         */
        SatSolverStatisticsPtrType getSatSolverStatisticsPtr() noexcept;

        /**
         * @return a pointer to the partitioning hypergraph statistics
         */
        PartitioningHypergraphStatisticsPtrType getPartitioningHypergraphStatisticsPtr() noexcept;

        /**
         * @return a pointer to the component cache statistics
         */
        CacheStatisticsPtrType getComponentCacheStatisticsPtr() noexcept;

        /**
         * @return a pointer to the hypergraph cut cache statistics
         */
        CacheStatisticsPtrType getHypergraphCutCacheStatisticsPtr() noexcept;

        /**
         * @return a pointer to the circuit statistics
         */
        CircuitStatisticsPtrType getCircuitStatisticsPtr() noexcept;

        /**
         * @return a pointer to the compiler statistics
         */
        CompilerStatisticsPtrType getCompilerStatisticsPtr() noexcept;

        /**
         * @return a pointer to the formula representation statistics
         */
        FormulaRepresentationStatisticsPtrType getFormulaRepresentationStatisticsPtr() noexcept;

        /**
         * @return a pointer to the renH-C recognition statistics
         */
        RenHCRecognitionStatisticsPtrType getRenHCRecognitionStatisticsPtr() noexcept;

        void printStatistics(std::ostream& out, bool addLabels) const;
    };
}   // namespace Hydra::Statistics
