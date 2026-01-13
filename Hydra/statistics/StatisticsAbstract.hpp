#pragma once

#include <chrono>
#include <ostream>
#include <string>

#include "Hydra/other/Other.hpp"
#include "Hydra/statistics/component/CounterStatistics.hpp"
#include "Hydra/statistics/component/NumberStatistics.hpp"
#include "Hydra/statistics/component/TimerStatistics.hpp"

namespace Hydra::Statistics {

    /**
     * Statistics template (abstract class)
     * Copy and move methods are disabled!
     */
    class StatisticsAbstract {
    public:
        using NumberStatisticsType = NumberStatistics<LargeNumberType>;
        using RealNumberStatisticsType = NumberStatistics<LargeFloatingNumberType>;

    public:
        using NumberCounterStatisticsType = CounterStatistics<LargeNumberType>;
        using RealNumberCounterStatisticsType = CounterStatistics<LargeFloatingNumberType>;

    public:
        using TimerStatisticsType = TimerStatistics<std::chrono::seconds>;
        using NanoTimerStatisticsType = TimerStatistics<std::chrono::nanoseconds>;
        using MicroTimerStatisticsType = TimerStatistics<std::chrono::microseconds>;
        using MilliTimerStatisticsType = TimerStatistics<std::chrono::milliseconds>;

    public:
        explicit StatisticsAbstract(std::string&& name)
            : name_(std::move(name)) { }

        StatisticsAbstract(const StatisticsAbstract&) = delete;
        StatisticsAbstract(StatisticsAbstract&&) noexcept = delete;

        StatisticsAbstract& operator=(const StatisticsAbstract&) = delete;
        StatisticsAbstract& operator=(StatisticsAbstract&&) noexcept = delete;

        virtual ~StatisticsAbstract() noexcept = default;

    private:
        std::string name_;

    private:
        virtual void processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const = 0;

    public:
        void printStatistics(std::ostream& out, bool addLabels) const;
    };
}   // namespace Hydra::Statistics
