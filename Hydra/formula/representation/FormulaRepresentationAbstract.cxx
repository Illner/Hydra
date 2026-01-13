#include "./FormulaRepresentationAbstract.hxx"

namespace Hydra::Formula::Representation {

    void FormulaRepresentationStatistics::processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const {
        formulaSizeNumber.printNumberStatistics(out, statisticsName, addLabels);

        numberOfVariablesNumber.printNumberStatistics(out, statisticsName, addLabels);

        numberOfClausesNumber.printNumberStatistics(out, statisticsName, addLabels);

        initializeTimer.printTimerStatistics(out, statisticsName, addLabels, true);

        computeConnectedComponentsTimer.printTimerStatistics(out, statisticsName, addLabels);

        recognitionOfKromCTimer.printTimerStatistics(out, statisticsName, addLabels);

        recognitionOfHornCTimer.printTimerStatistics(out, statisticsName, addLabels);

        recognitionOfAntiHornCTimer.printTimerStatistics(out, statisticsName, addLabels);

        // Debug
        if (debugTimer.atLeastOneCall())
            debugTimer.printTimerStatistics(out, statisticsName, addLabels);

        if (debugCounter.atLeastOneCall())
            debugCounter.printCounterStatistics(out, statisticsName, addLabels);
    }
}   // namespace Hydra::Formula::Representation
