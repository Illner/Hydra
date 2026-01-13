#pragma once

#include "./TimerStatistics.hpp"

namespace Hydra::Statistics {

    template <typename TimeDurationT>
    void TimerStatistics<TimeDurationT>::addTime(TimeType time) noexcept {
        ++numberOfCalls_;
        sumTime_ += time;

        // Update min and max
        if (first_) {
            first_ = false;

            minTime_ = time;
            maxTime_ = time;
        }
        else {
            if (time < minTime_)
                minTime_ = time;

            if (maxTime_ < time)
                maxTime_ = time;
        }
    }

    template <typename TimeDurationT>
    void TimerStatistics<TimeDurationT>::printTimeDurationAbbreviation(std::ostream& out) const {
        // Nanoseconds
        if (std::is_same<TimeDurationT, std::chrono::nanoseconds>::value)
            out << "ns";
        // Microseconds
        else if (std::is_same<TimeDurationT, std::chrono::microseconds>::value)
            out << "us";
        // Milliseconds
        else if (std::is_same<TimeDurationT, std::chrono::milliseconds>::value)
            out << "ms";
        // Seconds
        else if (std::is_same<TimeDurationT, std::chrono::seconds>::value)
            out << "s";
        else
            throw Exception::NotImplementedException("TimeDurationT",
                                                     "Hydra::Statistics::TimerStatistics::printTimeDurationAbbreviation");
    }

    template <typename TimeDurationT>
    const std::string& TimerStatistics<TimeDurationT>::getName() const noexcept {
        return name_;
    }

    template <typename TimeDurationT>
    LargeNumberType TimerStatistics<TimeDurationT>::getNumberOfCalls() const noexcept {
        return numberOfCalls_;
    }

    template <typename TimeDurationT>
    TimeType TimerStatistics<TimeDurationT>::getSumTime() const noexcept {
        return sumTime_;
    }

    template <typename TimeDurationT>
    TimeType TimerStatistics<TimeDurationT>::getMinTime() const noexcept {
        return minTime_;
    }

    template <typename TimeDurationT>
    TimeType TimerStatistics<TimeDurationT>::getMaxTime() const noexcept {
        return maxTime_;
    }

    template <typename TimeDurationT>
    LargeFloatingNumberType TimerStatistics<TimeDurationT>::averageTime() const noexcept {
        if (numberOfCalls_ == 0)
            return 0;

        return (static_cast<LargeFloatingNumberType>(sumTime_) / static_cast<LargeFloatingNumberType>(numberOfCalls_));
    }

    template <typename TimeDurationT>
    bool TimerStatistics<TimeDurationT>::atLeastOneCall() const noexcept {
        return (numberOfCalls_ > 0);
    }

    template <typename TimeDurationT>
    void TimerStatistics<TimeDurationT>::startStopwatch() {
        assert(!d_isStopwatchActivated_);   // stopwatch is not activated

        startTimePoint_ = std::chrono::steady_clock::now();

        #ifndef NDEBUG
        d_isStopwatchActivated_ = true;
        #endif
    }

    template <typename TimeDurationT>
    void TimerStatistics<TimeDurationT>::stopStopwatch() {
        assert(d_isStopwatchActivated_);   // stopwatch is activated

        TimePointType stopTimePoint = std::chrono::steady_clock::now();

        addTime(static_cast<LargeNumberType>(duration_cast<TimeDurationT>(stopTimePoint - startTimePoint_).count()));

        #ifndef NDEBUG
        d_isStopwatchActivated_ = false;
        #endif
    }

    template <typename TimeDurationT>
    void TimerStatistics<TimeDurationT>::printTimerStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels, bool printOnlyTime) const {
        assert(!d_isStopwatchActivated_);   // stopwatch is not activated

        // Name
        if (addLabels)
            Other::printTitle(out, name_, 50, '-');
        else {
            if (printOnlyTime)
                out << "Timer (reduced): ";
            else
                out << "Timer: ";

            out << name_;

            out << " [";
            printTimeDurationAbbreviation(out);
            out << "]";

            if (!statisticsName.empty())
                out << " {" << statisticsName << "}";

            out << std::endl;
        }

        // Print only time
        if (printOnlyTime) {
            assert(numberOfCalls_ <= 1);

            // Set
            if (addLabels)
                out << "Set: ";
            out << std::to_string(numberOfCalls_ != 0) << std::endl;

            // Time
            if (addLabels) {
                out << "Time: " << std::to_string(sumTime_) << " ";
                printTimeDurationAbbreviation(out);
                out << std::endl;
            }
            else
                out << std::to_string(sumTime_) << std::endl;

            return;
        }

        // Number of calls
        if (addLabels)
            out << "Number of calls: ";
        out << std::to_string(numberOfCalls_) << std::endl;

        // Sum time
        if (addLabels) {
            out << "Sum time: " << std::to_string(sumTime_) << " ";
            printTimeDurationAbbreviation(out);
            out << std::endl;
        }
        else
            out << std::to_string(sumTime_) << std::endl;

        // Min time
        if (addLabels) {
            out << "Min time: " << std::to_string(minTime_) << " ";
            printTimeDurationAbbreviation(out);
            out << std::endl;
        }
        else
            out << std::to_string(minTime_) << std::endl;

        // Max time
        if (addLabels) {
            out << "Max time: " << std::to_string(maxTime_) << " ";
            printTimeDurationAbbreviation(out);
            out << std::endl;
        }
        else
            out << std::to_string(maxTime_) << std::endl;

        // Average time
        if (addLabels) {
            out << "Average time: " << std::to_string(averageTime()) << " ";
            printTimeDurationAbbreviation(out);
            out << std::endl;
        }
        else
            out << std::to_string(averageTime()) << std::endl;

        // out << std::endl;
    }
}   // namespace Hydra::Statistics
