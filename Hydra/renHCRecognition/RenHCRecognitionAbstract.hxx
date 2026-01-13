#pragma once

#include "Hydra/statistics/StatisticsAbstract.hpp"

namespace Hydra::RenHCRecognition {

    /**
     * RenH-C recognition - statistics
     */
    struct RenHCRecognitionStatistics : Statistics::StatisticsAbstract {
    public:
        using RenHCRecognitionStatisticsPtrType = RenHCRecognitionStatistics*;

    public:
        RenHCRecognitionStatistics()
            : Statistics::StatisticsAbstract("RenH-C recognition") { }

    public:
        NanoTimerStatisticsType creationTimer = NanoTimerStatisticsType("creation");

        NanoTimerStatisticsType initializeTimer = NanoTimerStatisticsType("initialize");

        NanoTimerStatisticsType setAssignedLiteralTimer = NanoTimerStatisticsType("set assigned literal");

        NanoTimerStatisticsType setUnassignedLiteralTimer = NanoTimerStatisticsType("set unassigned literal");

        NanoTimerStatisticsType setInactiveClauseTimer = NanoTimerStatisticsType("set inactive clause");

        NanoTimerStatisticsType setActiveClauseTimer = NanoTimerStatisticsType("set active clause");

        NanoTimerStatisticsType isRenHCTimer = NanoTimerStatisticsType("is renH-C");

        NumberCounterStatisticsType ratioOfRenHCCounter = NumberCounterStatisticsType("ratio of renH-C");

    public:
        NanoTimerStatisticsType debugTimer = NanoTimerStatisticsType("debug timer");

        RealNumberCounterStatisticsType debugCounter = RealNumberCounterStatisticsType("debug counter");

    private:
        void processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const override;
    };
}   // namespace Hydra::RenHCRecognition
