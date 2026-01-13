#include "./RenHCRecognitionAbstract.hxx"

namespace Hydra::RenHCRecognition {

    void RenHCRecognitionStatistics::processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const {
        creationTimer.printTimerStatistics(out, statisticsName, addLabels, true);

        initializeTimer.printTimerStatistics(out, statisticsName, addLabels, true);

        setAssignedLiteralTimer.printTimerStatistics(out, statisticsName, addLabels);

        setUnassignedLiteralTimer.printTimerStatistics(out, statisticsName, addLabels);

        setInactiveClauseTimer.printTimerStatistics(out, statisticsName, addLabels);

        setActiveClauseTimer.printTimerStatistics(out, statisticsName, addLabels);

        isRenHCTimer.printTimerStatistics(out, statisticsName, addLabels);

        ratioOfRenHCCounter.printCounterStatistics(out, statisticsName, addLabels);

        // Debug
        if (debugTimer.atLeastOneCall())
            debugTimer.printTimerStatistics(out, statisticsName, addLabels);

        if (debugCounter.atLeastOneCall())
            debugCounter.printCounterStatistics(out, statisticsName, addLabels);
    }
}   // namespace Hydra::RenHCRecognition
