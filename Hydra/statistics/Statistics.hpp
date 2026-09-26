#pragma once

#include <iostream>

#include "Hydra/cache/enums/CacheTypeEnum.hpp"

#include "Hydra/cache/Cache.hxx"
#include "Hydra/circuit/Circuit.hxx"
#include "Hydra/compiler/Compiler.hxx"
#include "Hydra/decisionHeuristic/DecisionHeuristicAbstract.hxx"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hxx"
#include "Hydra/hypergraphPartitioning/HypergraphPartitioningAbstract.hxx"
#include "Hydra/parser/cnf/CnfParser.hxx"
#include "Hydra/preprocessor/cnf/CnfPreprocessorAbstract.hxx"
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
        using CnfParserStatisticsType = Parser::Cnf::CnfParserStatistics;
        using CnfPreprocessorStatisticsType = Preprocessor::Cnf::CnfPreprocessorStatistics;
        using RenHCRecognitionStatisticsType = RenHCRecognition::RenHCRecognitionStatistics;
        using DecisionHeuristicStatisticsType = DecisionHeuristic::DecisionHeuristicStatistics;
        using FormulaRepresentationStatisticsType = Formula::Representation::FormulaRepresentationStatistics;
        using HypergraphPartitioningStatisticsType = HypergraphPartitioning::HypergraphPartitioningStatistics;

    public:
        using CacheStatisticsPtrType = Cache::CacheStatistics::CacheStatisticsPtrType;
        using CompilerStatisticsPtrType = CompilerStatistics::CompilerStatisticsPtrType;
        using CircuitStatisticsPtrType = Circuit::CircuitStatistics::CircuitStatisticsPtrType;
        using SatSolverStatisticsPtrType = SatSolver::SatSolverStatistics::SatSolverStatisticsPtrType;
        using CnfParserStatisticsPtrType = Parser::Cnf::CnfParserStatistics::CnfParserStatisticsPtrType;
        using CnfPreprocessorStatisticsPtrType = Preprocessor::Cnf::CnfPreprocessorStatistics::CnfPreprocessorStatisticsPtrType;
        using RenHCRecognitionStatisticsPtrType = RenHCRecognition::RenHCRecognitionStatistics::RenHCRecognitionStatisticsPtrType;
        using DecisionHeuristicStatisticsPtrType = DecisionHeuristic::DecisionHeuristicStatistics::DecisionHeuristicStatisticsPtrType;
        using FormulaRepresentationStatisticsPtrType = Formula::Representation::FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType;
        using HypergraphPartitioningStatisticsPtrType = HypergraphPartitioning::HypergraphPartitioningStatistics::HypergraphPartitioningStatisticsPtrType;

    public:
        using StatisticsPtrType = Statistics*;

    private:
        CircuitStatisticsType circuitStatistics_;
        CompilerStatisticsType compilerStatistics_;
        SatSolverStatisticsType satSolverStatistics_;
        CnfParserStatisticsType cnfParserStatistics_;
        CnfPreprocessorStatisticsType cnfPreprocessorStatistics_;
        RenHCRecognitionStatisticsType renHCRecognitionStatistics_;
        DecisionHeuristicStatisticsType decisionHeuristicStatistics_;
        FormulaRepresentationStatisticsType formulaRepresentationStatistics_;
        HypergraphPartitioningStatisticsType hypergraphPartitioningStatistics_;
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
         * @return a pointer to the hypergraph partitioning statistics
         */
        HypergraphPartitioningStatisticsPtrType getHypergraphPartitioningStatisticsPtr() noexcept;

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

        /**
         * @return a pointer to the CNF preprocessor statistics
         */
        CnfPreprocessorStatisticsPtrType getCnfPreprocessorStatisticsPtr() noexcept;

        /**
         * @return a pointer to the CNF parser statistics
         */
        CnfParserStatisticsPtrType getCnfParserStatisticsPtr() noexcept;

        void printStatistics(std::ostream& out, bool addLabels) const;
    };
}   // namespace Hydra::Statistics
