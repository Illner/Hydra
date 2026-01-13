#include "./Circuit.hxx"

namespace Hydra::Circuit {

    void CircuitStatistics::processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const {
        circuitSizeNumber.printNumberStatistics(out, statisticsName, addLabels);

        numberOfNodesNumber.printNumberStatistics(out, statisticsName, addLabels);

        numberOfEdgesNumber.printNumberStatistics(out, statisticsName, addLabels);

        numberOfVariablesNumber.printNumberStatistics(out, statisticsName, addLabels);

        copySubcircuitTimer.printTimerStatistics(out, statisticsName, addLabels);

        formulaSizeCopySubcircuitCounter.printCounterStatistics(out, statisticsName, addLabels);

        numberOfVariablesCopySubcircuitCounter.printCounterStatistics(out, statisticsName, addLabels);

        numberOfClausesCopySubcircuitCounter.printCounterStatistics(out, statisticsName, addLabels);

        // Debug
        if (debugTimer.atLeastOneCall())
            debugTimer.printTimerStatistics(out, statisticsName, addLabels);

        if (debugCounter.atLeastOneCall())
            debugCounter.printCounterStatistics(out, statisticsName, addLabels);
    }
}   // namespace Hydra::Circuit
