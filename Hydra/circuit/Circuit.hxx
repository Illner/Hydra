#pragma once

#include "Hydra/statistics/StatisticsAbstract.hpp"

namespace Hydra::Circuit {

    /**
     * Circuit - statistics
     */
    struct CircuitStatistics : Statistics::StatisticsAbstract {
    public:
        using CircuitStatisticsPtrType = CircuitStatistics*;

    public:
        CircuitStatistics()
            : Statistics::StatisticsAbstract("Circuit") { }

    public:
        NumberStatisticsType circuitSizeNumber = NumberStatisticsType("circuit size", false);

        NumberStatisticsType numberOfNodesNumber = NumberStatisticsType("#nodes", false);

        NumberStatisticsType numberOfEdgesNumber = NumberStatisticsType("#edges", false);

        NumberStatisticsType numberOfVariablesNumber = NumberStatisticsType("#variables", false);

        NanoTimerStatisticsType copySubcircuitTimer = NanoTimerStatisticsType("copy subcircuit");

        NumberCounterStatisticsType formulaSizeCopySubcircuitCounter = NumberCounterStatisticsType("formula size (copy subcircuit)");

        NumberCounterStatisticsType numberOfVariablesCopySubcircuitCounter = NumberCounterStatisticsType("#variables (copy subcircuit)");

        NumberCounterStatisticsType numberOfClausesCopySubcircuitCounter = NumberCounterStatisticsType("#clauses (copy subcircuit)");

    public:
        NanoTimerStatisticsType debugTimer = NanoTimerStatisticsType("debug timer");

        RealNumberCounterStatisticsType debugCounter = RealNumberCounterStatisticsType("debug counter");

    private:
        void processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const override;
    };
}   // namespace Hydra::Circuit
