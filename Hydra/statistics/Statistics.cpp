#include "./Statistics.hpp"

namespace Hydra::Statistics {

    typename Statistics::DecisionHeuristicStatisticsPtrType
    Statistics::getDecisionHeuristicStatisticsPtr() noexcept {
        return &decisionHeuristicStatistics_;
    }

    typename Statistics::SatSolverStatisticsPtrType
    Statistics::getSatSolverStatisticsPtr() noexcept {
        return &satSolverStatistics_;
    }

    typename Statistics::PartitioningHypergraphStatisticsPtrType
    Statistics::getPartitioningHypergraphStatisticsPtr() noexcept {
        return &partitioningHypergraphStatistics_;
    }

    typename Statistics::CacheStatisticsPtrType
    Statistics::getComponentCacheStatisticsPtr() noexcept {
        return &componentCacheStatistics_;
    }

    typename Statistics::CacheStatisticsPtrType
    Statistics::getHypergraphCutCacheStatisticsPtr() noexcept {
        return &hypergraphCutCacheStatistics_;
    }

    typename Statistics::CircuitStatisticsPtrType
    Statistics::getCircuitStatisticsPtr() noexcept {
        return &circuitStatistics_;
    }

    typename Statistics::CompilerStatisticsPtrType
    Statistics::getCompilerStatisticsPtr() noexcept {
        return &compilerStatistics_;
    }

    typename Statistics::FormulaRepresentationStatisticsPtrType
    Statistics::getFormulaRepresentationStatisticsPtr() noexcept {
        return &formulaRepresentationStatistics_;
    }

    typename Statistics::RenHCRecognitionStatisticsPtrType
    Statistics::getRenHCRecognitionStatisticsPtr() noexcept {
        return &renHCRecognitionStatistics_;
    }

    void Statistics::printStatistics(std::ostream& out, bool addLabels) const {
        if (addLabels)
            Other::printTitle(out, "Statistics", 100, '-');

        // Formula representation
        formulaRepresentationStatistics_.printStatistics(out, addLabels);

        // Circuit
        circuitStatistics_.printStatistics(out, addLabels);

        // Compiler
        compilerStatistics_.printStatistics(out, addLabels);

        // Decision heuristic
        decisionHeuristicStatistics_.printStatistics(out, addLabels);

        // SAT solver
        satSolverStatistics_.printStatistics(out, addLabels);

        // Partitioning hypergraph
        partitioningHypergraphStatistics_.printStatistics(out, addLabels);

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
