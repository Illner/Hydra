#pragma once

#include "Hydra/statistics/StatisticsAbstract.hpp"

namespace Hydra::Formula::Representation {

    /**
     * Formula representation - statistics
     */
    struct FormulaRepresentationStatistics : Statistics::StatisticsAbstract {
    public:
        using FormulaRepresentationStatisticsPtrType = FormulaRepresentationStatistics*;

    public:
        FormulaRepresentationStatistics()
            : Statistics::StatisticsAbstract("Formula representation") { }

    public:
        NumberStatisticsType formulaSizeNumber = NumberStatisticsType("formula size", false);

        NumberStatisticsType numberOfVariablesNumber = NumberStatisticsType("#variables", false);

        NumberStatisticsType numberOfClausesNumber = NumberStatisticsType("#clauses", false);

        NanoTimerStatisticsType initializeTimer = NanoTimerStatisticsType("initialize");

        NanoTimerStatisticsType computeConnectedComponentsTimer = NanoTimerStatisticsType("compute connected components");

        NanoTimerStatisticsType recognitionOfKromCTimer = NanoTimerStatisticsType("recognition of Krom-C");

        NanoTimerStatisticsType recognitionOfHornCTimer = NanoTimerStatisticsType("recognition of Horn-C");

        NanoTimerStatisticsType recognitionOfAntiHornCTimer = NanoTimerStatisticsType("recognition of anti-Horn-C");

    public:
        NanoTimerStatisticsType debugTimer = NanoTimerStatisticsType("debug timer");

        RealNumberCounterStatisticsType debugCounter = RealNumberCounterStatisticsType("debug counter");

    private:
        void processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const override;
    };
}   // namespace Hydra::Formula::Representation
