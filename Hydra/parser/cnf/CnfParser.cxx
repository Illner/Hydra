#include "./CnfParser.hxx"

namespace Hydra::Parser::Cnf {

    void CnfParserStatistics::processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const {
        parseTimer.printTimerStatistics(out, statisticsName, addLabels, true);

        // Debug
        if (debugTimer.atLeastOneCall())
            debugTimer.printTimerStatistics(out, statisticsName, addLabels);

        if (debugCounter.atLeastOneCall())
            debugCounter.printCounterStatistics(out, statisticsName, addLabels);
    }
}   // namespace Hydra::Parser::Cnf
