#include "./PartitioningHypergraphAbstract.hxx"

namespace Hydra::PartitioningHypergraph {

    void PartitioningHypergraphStatistics::processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const {
        computeCutTimer.printTimerStatistics(out, statisticsName, addLabels);

        cutSizeCounter.printCounterStatistics(out, statisticsName, addLabels);

        ratioOfCutSizeToNumberOfVariablesCounter.printCounterStatistics(out, statisticsName, addLabels);

        createOccurrenceListStructTimer.printTimerStatistics(out, statisticsName, addLabels);

        numberOfVerticesCounter.printCounterStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfVerticesToNumberOfClausesCounter.printCounterStatistics(out, statisticsName, addLabels);

        numberOfHyperedgesCounter.printCounterStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfHyperedgesToNumberOfVariablesCounter.printCounterStatistics(out, statisticsName, addLabels);

        hypergraphSizeCounter.printCounterStatistics(out, statisticsName, addLabels);

        ratioOfHypergraphSizeToFormulaSizeCounter.printCounterStatistics(out, statisticsName, addLabels);

        createEquivalenceStructTimer.printTimerStatistics(out, statisticsName, addLabels);

        // Debug
        if (debugTimer.atLeastOneCall())
            debugTimer.printTimerStatistics(out, statisticsName, addLabels);

        if (debugCounter.atLeastOneCall())
            debugCounter.printCounterStatistics(out, statisticsName, addLabels);
    }
}   // namespace Hydra::PartitioningHypergraph
