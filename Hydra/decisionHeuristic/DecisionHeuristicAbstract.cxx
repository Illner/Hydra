#include "./DecisionHeuristicAbstract.hxx"

namespace Hydra::DecisionHeuristic {

    void DecisionHeuristicStatistics::processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const {
        getDecisionVariableTimer.printTimerStatistics(out, statisticsName, addLabels);

        numberOfPreselectedVariablesCounter.printCounterStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfRestrictedVariablesToNumberOfPreselectedVariablesCounter.printCounterStatistics(out, statisticsName, addLabels);

        // Debug
        if (debugTimer.atLeastOneCall())
            debugTimer.printTimerStatistics(out, statisticsName, addLabels);

        if (debugCounter.atLeastOneCall())
            debugCounter.printCounterStatistics(out, statisticsName, addLabels);
    }
}   // namespace Hydra::DecisionHeuristic
