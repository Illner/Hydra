#include "./CnfPreprocessorAbstract.hxx"

namespace Hydra::Preprocessor::Cnf {

    void CnfPreprocessorStatistics::processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const {
        preprocessTimer.printTimerStatistics(out, statisticsName, addLabels, true);

        ratioOfNumberOfNewVariablesToNumberOfOldVariablesNumber.printNumberStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfNewClausesToNumberOfOldClausesNumber.printNumberStatistics(out, statisticsName, addLabels);

        ratioOfNewFormulaSizeToOldFormulaSizeNumber.printNumberStatistics(out, statisticsName, addLabels);

        // Debug
        if (debugTimer.atLeastOneCall())
            debugTimer.printTimerStatistics(out, statisticsName, addLabels);

        if (debugCounter.atLeastOneCall())
            debugCounter.printCounterStatistics(out, statisticsName, addLabels);
    }
}   // namespace Hydra::Preprocessor::Cnf
