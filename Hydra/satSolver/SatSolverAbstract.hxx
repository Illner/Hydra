#pragma once

#include "Hydra/statistics/StatisticsAbstract.hpp"

namespace Hydra::SatSolver {

    /**
     * SAT solver - statistics
     */
    struct SatSolverStatistics : Statistics::StatisticsAbstract {
    public:
        using SatSolverStatisticsPtrType = SatSolverStatistics*;

    public:
        SatSolverStatistics()
            : Statistics::StatisticsAbstract("SAT solver") { }

    public:
        NanoTimerStatisticsType initializeTimer = NanoTimerStatisticsType("initialize");

        NanoTimerStatisticsType initialSimplificationTimer = NanoTimerStatisticsType("initial simplification");

        NanoTimerStatisticsType initiallyImpliedLiteralsTimer = NanoTimerStatisticsType("initially implied literals");

        NumberStatisticsType numberOfInitiallyImpliedLiteralsNumber = NumberStatisticsType("#initially implied literals", false);

        RealNumberStatisticsType ratioOfNumberOfInitiallyImpliedLiteralsToNumberOfVariablesNumber = RealNumberStatisticsType("#initially implied literals / #variables", false);

        NanoTimerStatisticsType isSatisfiableTimer = NanoTimerStatisticsType("is satisfiable");

        NanoTimerStatisticsType unitPropagationTimer = NanoTimerStatisticsType("unit propagation");

        NumberCounterStatisticsType numberOfImpliedLiteralsCounter = NumberCounterStatisticsType("#implied literals");

        RealNumberCounterStatisticsType ratioOfNumberOfImpliedLiteralsToNumberOfVariablesCounter = RealNumberCounterStatisticsType("#implied literals / #variables");

        NanoTimerStatisticsType createEquivalencePreprocessingStructTimer = NanoTimerStatisticsType("create equivalence preprocessing structure");

        RealNumberCounterStatisticsType ratioOfNumberOfImplicitImpliedLiteralsToNumberOfVariablesCounter = RealNumberCounterStatisticsType("#implicit implied literals / #variables");

        RealNumberCounterStatisticsType ratioOfNumberOfIgnoredVariablesToNumberOfVariablesCounter = RealNumberCounterStatisticsType("#ignored variables / #variables");

    public:
        NanoTimerStatisticsType debugTimer = NanoTimerStatisticsType("debug timer");

        RealNumberCounterStatisticsType debugCounter = RealNumberCounterStatisticsType("debug counter");

    private:
        void processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const override;
    };
}   // namespace Hydra::SatSolver
