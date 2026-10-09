#pragma once

#include "Hydra/statistics/StatisticsAbstract.hpp"

namespace Hydra::HypergraphPartitioning {

    /**
     * Hypergraph partitioning - statistics
     */
    struct HypergraphPartitioningStatistics : Statistics::StatisticsAbstract {
    public:
        using HypergraphPartitioningStatisticsPtrType = HypergraphPartitioningStatistics*;

    public:
        HypergraphPartitioningStatistics()
            : Statistics::StatisticsAbstract("Hypergraph partitioning") { }

    public:
        NanoTimerStatisticsType computeCutTimer = NanoTimerStatisticsType("compute cut");

        NumberCounterStatisticsType cutSizeCounter = NumberCounterStatisticsType("cut size");

        RealNumberCounterStatisticsType ratioOfCutSizeToNumberOfVariablesCounter = RealNumberCounterStatisticsType("cut size / #variables");

        NanoTimerStatisticsType createOccurrenceListStructTimer = NanoTimerStatisticsType("create occurrence list structure");

        NumberCounterStatisticsType numberOfVerticesCounter = NumberCounterStatisticsType("#vertices");

        RealNumberCounterStatisticsType ratioOfNumberOfVerticesToNumberOfClausesCounter = RealNumberCounterStatisticsType("#vertices / #clauses");

        NumberCounterStatisticsType numberOfHyperedgesCounter = NumberCounterStatisticsType("#hyperedges");

        RealNumberCounterStatisticsType ratioOfNumberOfHyperedgesToNumberOfVariablesCounter = RealNumberCounterStatisticsType("#hyperedges / #variables");

        NumberCounterStatisticsType hypergraphSizeCounter = NumberCounterStatisticsType("hypergraph size");

        RealNumberCounterStatisticsType ratioOfHypergraphSizeToFormulaSizeCounter = RealNumberCounterStatisticsType("hypergraph size / formula size");

        NanoTimerStatisticsType createEquivalenceStructTimer = NanoTimerStatisticsType("create equivalence structure");

    public:
        NanoTimerStatisticsType debugTimer = NanoTimerStatisticsType("debug timer");

        RealNumberCounterStatisticsType debugCounter = RealNumberCounterStatisticsType("debug counter");

    private:
        void processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const override;
    };
}   // namespace Hydra::HypergraphPartitioning
