#pragma once

#include <cassert>
#include <chrono>
#include <ostream>
#include <string>
#include <type_traits>

#include "Hydra/other/Other.hpp"
#include "Hydra/statistics/component/CounterStatistics.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Statistics {

    using TimeType = unsigned long long int;   // at least 64 bits

    /**
     * Timer statistics representation
     * Copy and move methods are disabled!
     * @tparam TimeDurationT type used for a time duration (nanoseconds / microseconds / milliseconds / seconds)
     */
    template <typename TimeDurationT>
    class TimerStatistics {
    private:
        using TimePointType = std::chrono::steady_clock::time_point;

    private:
        using isValidTimeDurationT = std::bool_constant<(std::is_same<TimeDurationT, std::chrono::nanoseconds>::value ||
                                                         std::is_same<TimeDurationT, std::chrono::microseconds>::value ||
                                                         std::is_same<TimeDurationT, std::chrono::milliseconds>::value ||
                                                         std::is_same<TimeDurationT, std::chrono::seconds>::value)>;

        static_assert(isValidTimeDurationT::value, "Invalid TimeDurationT type!");

    public:
        explicit TimerStatistics(std::string&& name)
            : first_(true), name_(std::move(name)),
              sumTime_(0), minTime_(0), maxTime_(0), numberOfCalls_(0) { }

        TimerStatistics(const TimerStatistics&) = delete;
        TimerStatistics(TimerStatistics&&) noexcept = delete;

        TimerStatistics& operator=(const TimerStatistics&) = delete;
        TimerStatistics& operator=(TimerStatistics&&) noexcept = delete;

    private:
        bool first_;
        std::string name_;
        TimePointType startTimePoint_;

        TimeType sumTime_;
        TimeType minTime_;
        TimeType maxTime_;
        LargeNumberType numberOfCalls_;

    private:
        void addTime(TimeType time) noexcept;

        /**
         * Based on TimeDurationT, print "s", "ms", "us", or "ns"
         */
        void printTimeDurationAbbreviation(std::ostream& out) const;

    public:
        /**
         * Getter
         * @return the name
         */
        const std::string& getName() const noexcept;

        /**
         * Getter
         * @return the number of calls
         */
        LargeNumberType getNumberOfCalls() const noexcept;

        /**
         * Getter
         * @return the sum time
         */
        TimeType getSumTime() const noexcept;

        /**
         * Getter
         * @return the min time
         */
        TimeType getMinTime() const noexcept;

        /**
         * Getter
         * @return the max time
         */
        TimeType getMaxTime() const noexcept;

        /**
         * Note: if the number of calls is 0, then 0 is returned
         * @return the average time
         */
        LargeFloatingNumberType averageTime() const noexcept;

        /**
         * @return true if the number of calls is at least 1. Otherwise, false is returned.
         */
        bool atLeastOneCall() const noexcept;

        /**
         * Start the stopwatch
         * Assert: the stopwatch MUST NOT be activated
         */
        void startStopwatch();

        /**
         * Stop the stopwatch and add time
         * Assert: the stopwatch MUST be activated
         */
        void stopStopwatch();

        /**
         * Assert: the stopwatch MUST NOT be activated
         */
        void printTimerStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels = true, bool printOnlyTime = false) const;

    #ifndef NDEBUG
    private:
        bool d_isStopwatchActivated_ = false;
    #endif
    };
}   // namespace Hydra::Statistics

#include "./TimerStatistics.ipp"
