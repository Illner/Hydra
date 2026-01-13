#include "./SatSolverAbstract.hxx"

namespace Hydra::SatSolver {

    void SatSolverStatistics::processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const {
        initializeTimer.printTimerStatistics(out, statisticsName, addLabels, true);

        initialSimplificationTimer.printTimerStatistics(out, statisticsName, addLabels, true);

        initiallyImpliedLiteralsTimer.printTimerStatistics(out, statisticsName, addLabels, true);

        numberOfInitiallyImpliedLiteralsNumber.printNumberStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfInitiallyImpliedLiteralsToNumberOfVariablesNumber.printNumberStatistics(out, statisticsName, addLabels);

        isSatisfiableTimer.printTimerStatistics(out, statisticsName, addLabels);

        unitPropagationTimer.printTimerStatistics(out, statisticsName, addLabels);

        numberOfImpliedLiteralsCounter.printCounterStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfImpliedLiteralsToNumberOfVariablesCounter.printCounterStatistics(out, statisticsName, addLabels);

        createEquivalencePreprocessingStructTimer.printTimerStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfImplicitImpliedLiteralsToNumberOfVariablesCounter.printCounterStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfIgnoredVariablesToNumberOfVariablesCounter.printCounterStatistics(out, statisticsName, addLabels);

        // Debug
        if (debugTimer.atLeastOneCall())
            debugTimer.printTimerStatistics(out, statisticsName, addLabels);

        if (debugCounter.atLeastOneCall())
            debugCounter.printCounterStatistics(out, statisticsName, addLabels);
    }
}   // namespace Hydra::SatSolver
