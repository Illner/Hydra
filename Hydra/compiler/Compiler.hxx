#pragma once

#include "Hydra/statistics/StatisticsAbstract.hpp"

namespace Hydra {

    /**
     * Compiler - statistics
     */
    struct CompilerStatistics : Statistics::StatisticsAbstract {
    public:
        using CompilerStatisticsPtrType = CompilerStatistics*;

    public:
        CompilerStatistics()
            : Statistics::StatisticsAbstract("Compiler") { }

    public:
        NanoTimerStatisticsType initializeTimer = NanoTimerStatisticsType("initialize");

        NanoTimerStatisticsType compileTimer = NanoTimerStatisticsType("compile");

        NumberStatisticsType numberOfUnsatisfiableResidualFormulaeIncrement = NumberStatisticsType("#unsatisfiable residual formulae", true);

        NumberStatisticsType numberOfEmptyResidualFormulaeIncrement = NumberStatisticsType("#empty residual formulae", true);

        NumberStatisticsType numberOfSplitsIncrement = NumberStatisticsType("#splits", true);

        NumberStatisticsType numberOfDecisionsIncrement = NumberStatisticsType("#decisions", true);

        NumberCounterStatisticsType ratioOfRecomputedHypergraphCutsCounter = NumberCounterStatisticsType("ratio of recomputed hypergraph cuts");

        NumberCounterStatisticsType ratioOfNumberOfEmptyHypergraphCutsToNumberOfHypergraphCutsCounter = NumberCounterStatisticsType("#empty hypergraph cuts / #hypergraph cuts");

        NumberCounterStatisticsType numberOfConnectedComponentsCounter = NumberCounterStatisticsType("#connected components");

        NumberCounterStatisticsType ratioOfNumberOfMonotoneResidualFormulaeToNumberOfResidualFormulaeCounter = NumberCounterStatisticsType("#monotone residual formulae / #residual formulae");

        NumberCounterStatisticsType monotoneResidualFormulaSizeCounter = NumberCounterStatisticsType("monotone residual formula size");

        RealNumberCounterStatisticsType ratioOfNumberOfPureClausesToNumberOfClausesCounter = RealNumberCounterStatisticsType("#pure clauses / #clauses");

        RealNumberCounterStatisticsType ratioOfPureResidualFormulaSizeToResidualFormulaSizeCounter = RealNumberCounterStatisticsType("pure residual formula size / residual formula size");

        NanoTimerStatisticsType assignLiteralTimer = NanoTimerStatisticsType("assign literal");

        NanoTimerStatisticsType unassignLiteralTimer = NanoTimerStatisticsType("unassign literal");

    public:
        NanoTimerStatisticsType debugTimer = NanoTimerStatisticsType("debug timer");

        RealNumberCounterStatisticsType debugCounter = RealNumberCounterStatisticsType("debug counter");

    private:
        void processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const override;
    };
}   // namespace Hydra
