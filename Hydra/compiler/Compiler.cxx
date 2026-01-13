#include "./Compiler.hxx"

namespace Hydra {

    void CompilerStatistics::processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const {
        initializeTimer.printTimerStatistics(out, statisticsName, addLabels, true);

        compileTimer.printTimerStatistics(out, statisticsName, addLabels, true);

        numberOfUnsatisfiableResidualFormulaeIncrement.printNumberStatistics(out, statisticsName, addLabels);

        numberOfEmptyResidualFormulaeIncrement.printNumberStatistics(out, statisticsName, addLabels);

        numberOfSplitsIncrement.printNumberStatistics(out, statisticsName, addLabels);

        numberOfDecisionsIncrement.printNumberStatistics(out, statisticsName, addLabels);

        ratioOfRecomputedHypergraphCutsCounter.printCounterStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfEmptyHypergraphCutsToNumberOfHypergraphCutsCounter.printCounterStatistics(out, statisticsName, addLabels);

        numberOfConnectedComponentsCounter.printCounterStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfMonotoneResidualFormulaeToNumberOfResidualFormulaeCounter.printCounterStatistics(out, statisticsName, addLabels);

        monotoneResidualFormulaSizeCounter.printCounterStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfPureClausesToNumberOfClausesCounter.printCounterStatistics(out, statisticsName, addLabels);

        ratioOfPureResidualFormulaSizeToResidualFormulaSizeCounter.printCounterStatistics(out, statisticsName, addLabels);

        assignLiteralTimer.printTimerStatistics(out, statisticsName, addLabels);

        unassignLiteralTimer.printTimerStatistics(out, statisticsName, addLabels);

        // Debug
        if (debugTimer.atLeastOneCall())
            debugTimer.printTimerStatistics(out, statisticsName, addLabels);

        if (debugCounter.atLeastOneCall())
            debugCounter.printCounterStatistics(out, statisticsName, addLabels);
    }
}   // namespace Hydra
