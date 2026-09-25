#pragma once

#include "Hydra/statistics/StatisticsAbstract.hpp"

namespace Hydra::Parser::Cnf {

    /**
     * CNF parser - statistics
     */
    struct CnfParserStatistics : Statistics::StatisticsAbstract {
    public:
        using CnfParserStatisticsPtrType = CnfParserStatistics*;

    public:
        CnfParserStatistics()
            : Statistics::StatisticsAbstract("CNF parser") { }

    public:
        NanoTimerStatisticsType parseTimer = NanoTimerStatisticsType("parse");

    public:
        NanoTimerStatisticsType debugTimer = NanoTimerStatisticsType("debug timer");

        RealNumberCounterStatisticsType debugCounter = RealNumberCounterStatisticsType("debug counter");

    private:
        void processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const override;
    };
}   // namespace Hydra::Parser::Cnf
