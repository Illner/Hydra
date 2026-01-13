#pragma once

#include "Hydra/statistics/StatisticsAbstract.hpp"

namespace Hydra::DecisionHeuristic {

    /**
     * Decision heuristic - statistics
     */
    struct DecisionHeuristicStatistics : Statistics::StatisticsAbstract {
    public:
        using DecisionHeuristicStatisticsPtrType = DecisionHeuristicStatistics*;

    public:
        DecisionHeuristicStatistics()
            : Statistics::StatisticsAbstract("Decision heuristic") { }

    public:
        NanoTimerStatisticsType getDecisionVariableTimer = NanoTimerStatisticsType("get decision variable");

        NumberCounterStatisticsType numberOfPreselectedVariablesCounter = NumberCounterStatisticsType("#preselected variables");

        RealNumberCounterStatisticsType ratioOfNumberOfRestrictedVariablesToNumberOfPreselectedVariablesCounter = RealNumberCounterStatisticsType("#restricted variables / #preselected variables");

    public:
        NanoTimerStatisticsType debugTimer = NanoTimerStatisticsType("debug timer");

        RealNumberCounterStatisticsType debugCounter = RealNumberCounterStatisticsType("debug counter");

    private:
        void processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const override;
    };
}   // namespace Hydra::DecisionHeuristic
