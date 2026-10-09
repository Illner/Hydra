#pragma once

#include "Hydra/statistics/StatisticsAbstract.hpp"

namespace Hydra::Preprocessor::Cnf {

    /**
     * CNF preprocessor - statistics
     */
    struct CnfPreprocessorStatistics : Statistics::StatisticsAbstract {
    public:
        using CnfPreprocessorStatisticsPtrType = CnfPreprocessorStatistics*;

    public:
        CnfPreprocessorStatistics()
            : Statistics::StatisticsAbstract("CNF preprocessor") { }

    public:
        NanoTimerStatisticsType preprocessTimer = NanoTimerStatisticsType("preprocess");

        RealNumberStatisticsType ratioOfNumberOfNewVariablesToNumberOfOldVariablesNumber = RealNumberStatisticsType("#new variables / #old variables", false);

        RealNumberStatisticsType ratioOfNumberOfNewClausesToNumberOfOldClausesNumber = RealNumberStatisticsType("#new clauses / #old clauses", false);

        RealNumberStatisticsType ratioOfNewFormulaSizeToOldFormulaSizeNumber = RealNumberStatisticsType("new formula size / old formula size", false);

    public:
        NanoTimerStatisticsType debugTimer = NanoTimerStatisticsType("debug timer");

        RealNumberCounterStatisticsType debugCounter = RealNumberCounterStatisticsType("debug counter");

    private:
        void processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const override;
    };
}   // namespace Hydra::Preprocessor::Cnf
