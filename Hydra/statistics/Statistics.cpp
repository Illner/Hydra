#include "./Statistics.hpp"

namespace Hydra::Statistics {

    Statistics::DecisionHeuristicStatisticsPtrType
    Statistics::getDecisionHeuristicStatisticsPtr() noexcept {
        return &decisionHeuristicStatistics_;
    }

    Statistics::SatSolverStatisticsPtrType
    Statistics::getSatSolverStatisticsPtr() noexcept {
        return &satSolverStatistics_;
    }

    Statistics::HypergraphPartitioningStatisticsPtrType
    Statistics::getHypergraphPartitioningStatisticsPtr() noexcept {
        return &hypergraphPartitioningStatistics_;
    }

    Statistics::CacheStatisticsPtrType
    Statistics::getComponentCacheStatisticsPtr() noexcept {
        return &componentCacheStatistics_;
    }

    Statistics::CacheStatisticsPtrType
    Statistics::getHypergraphCutCacheStatisticsPtr() noexcept {
        return &hypergraphCutCacheStatistics_;
    }

    Statistics::CircuitStatisticsPtrType
    Statistics::getCircuitStatisticsPtr() noexcept {
        return &circuitStatistics_;
    }

    Statistics::CompilerStatisticsPtrType
    Statistics::getCompilerStatisticsPtr() noexcept {
        return &compilerStatistics_;
    }

    Statistics::FormulaRepresentationStatisticsPtrType
    Statistics::getFormulaRepresentationStatisticsPtr() noexcept {
        return &formulaRepresentationStatistics_;
    }

    Statistics::RenHCRecognitionStatisticsPtrType
    Statistics::getRenHCRecognitionStatisticsPtr() noexcept {
        return &renHCRecognitionStatistics_;
    }

    Statistics::CnfPreprocessorStatisticsPtrType
    Statistics::getCnfPreprocessorStatisticsPtr() noexcept {
        return &cnfPreprocessorStatistics_;
    }

    void Statistics::printStatistics(std::ostream& out, bool addLabels) const {
        if (addLabels)
            Other::printTitle(out, "Statistics", 100, '-');

        // Formula representation
        formulaRepresentationStatistics_.printStatistics(out, addLabels);

        // Circuit
        circuitStatistics_.printStatistics(out, addLabels);

        // CNF preprocessor
        cnfPreprocessorStatistics_.printStatistics(out, addLabels);

        // Compiler
        compilerStatistics_.printStatistics(out, addLabels);

        // Decision heuristic
        decisionHeuristicStatistics_.printStatistics(out, addLabels);

        // SAT solver
        satSolverStatistics_.printStatistics(out, addLabels);

        // Hypergraph partitioning
        hypergraphPartitioningStatistics_.printStatistics(out, addLabels);

        // RenH-C recognition
        renHCRecognitionStatistics_.printStatistics(out, addLabels);

        // Component cache
        componentCacheStatistics_.printStatistics(out, addLabels);

        // Hypergraph cut cache
        hypergraphCutCacheStatistics_.printStatistics(out, addLabels);

        if (addLabels)
            Other::printTitle(out, "Statistics", 100, '-');
    }
}   // namespace Hydra::Statistics
