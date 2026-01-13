#pragma once

#include "./CounterStatistics.hpp"

namespace Hydra::Statistics {

    template <typename TypeT>
    const std::string& CounterStatistics<TypeT>::getName() const noexcept {
        return name_;
    }

    template <typename TypeT>
    LargeNumberType CounterStatistics<TypeT>::getNumberOfCalls() const noexcept {
        return numberOfCalls_;
    }

    template <typename TypeT>
    TypeT CounterStatistics<TypeT>::getSumCount() const noexcept {
        return sumCount_;
    }

    template <typename TypeT>
    TypeT CounterStatistics<TypeT>::getMinCount() const noexcept {
        return minCount_;
    }

    template <typename TypeT>
    TypeT CounterStatistics<TypeT>::getMaxCount() const noexcept {
        return maxCount_;
    }

    template <typename TypeT>
    LargeFloatingNumberType CounterStatistics<TypeT>::averageCount() const noexcept {
        if (numberOfCalls_ == 0)
            return 0;

        return (static_cast<LargeFloatingNumberType>(sumCount_) / static_cast<LargeFloatingNumberType>(numberOfCalls_));
    }

    template <typename TypeT>
    bool CounterStatistics<TypeT>::atLeastOneCall() const noexcept {
        return (numberOfCalls_ > 0);
    }

    template <typename TypeT>
    void CounterStatistics<TypeT>::addCount(TypeT count) noexcept {
        ++numberOfCalls_;
        sumCount_ += count;

        // Update min and max
        if (first_) {
            first_ = false;

            minCount_ = count;
            maxCount_ = count;
        }
        else {
            if (count < minCount_)
                minCount_ = count;

            if (maxCount_ < count)
                maxCount_ = count;
        }
    }

    template <typename TypeT>
    void CounterStatistics<TypeT>::printCounterStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const {
        // Name
        if (addLabels)
            Other::printTitle(out, name_, 50, '-');
        else {
            out << "Counter: " << name_;

            if (!statisticsName.empty())
                out << " {" << statisticsName << "}";

            out << std::endl;
        }

        // Number of calls
        if (addLabels)
            out << "Number of calls: ";
        out << std::to_string(numberOfCalls_) << std::endl;

        // Sum count
        if (addLabels)
            out << "Sum count: ";
        out << std::to_string(sumCount_) << std::endl;

        // Min count
        if (addLabels)
            out << "Min count: ";
        out << std::to_string(minCount_) << std::endl;

        // Max count
        if (addLabels)
            out << "Max count: ";
        out << std::to_string(maxCount_) << std::endl;

        // Average count
        if (addLabels)
            out << "Average count: ";
        out << std::to_string(averageCount()) << std::endl;

        // out << std::endl;
    }
}   // namespace Hydra::Statistics
