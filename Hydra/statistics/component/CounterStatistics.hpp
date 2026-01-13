#pragma once

#include <ostream>
#include <string>
#include <type_traits>

#include "Hydra/other/Other.hpp"

namespace Hydra::Statistics {

    using LargeFloatingNumberType = long double;      // 128 bits
    using LargeNumberType = unsigned long long int;   // at least 64 bits

    /**
     * Counter statistics representation
     * Copy and move methods are disabled!
     * @tparam TypeT type used for a counter
     */
    template <typename TypeT>
    class CounterStatistics {
    private:
        using isValidTypeT = std::bool_constant<(std::is_same<TypeT, LargeNumberType>::value ||
                                                 std::is_same<TypeT, LargeFloatingNumberType>::value)>;

        static_assert(isValidTypeT::value, "Invalid TypeT type!");

    public:
        explicit CounterStatistics(std::string&& name)
            : first_(true), name_(std::move(name)),
              sumCount_(0), minCount_(0), maxCount_(0), numberOfCalls_(0) { }

        CounterStatistics(const CounterStatistics&) = delete;
        CounterStatistics(CounterStatistics&&) noexcept = delete;

        CounterStatistics& operator=(const CounterStatistics&) = delete;
        CounterStatistics& operator=(CounterStatistics&&) noexcept = delete;

    private:
        bool first_;
        std::string name_;

        TypeT sumCount_;
        TypeT minCount_;
        TypeT maxCount_;
        LargeNumberType numberOfCalls_;

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
         * @return the sum count
         */
        TypeT getSumCount() const noexcept;

        /**
         * Getter
         * @return the min count
         */
        TypeT getMinCount() const noexcept;

        /**
         * Getter
         * @return the max count
         */
        TypeT getMaxCount() const noexcept;

        /**
         * Note: if the number of calls is 0, then 0 is returned
         * @return the average count
         */
        LargeFloatingNumberType averageCount() const noexcept;

        /**
         * @return true if the number of calls is at least 1. Otherwise, false is returned.
         */
        bool atLeastOneCall() const noexcept;

        void addCount(TypeT count) noexcept;

        void printCounterStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels = true) const;
    };
}   // namespace Hydra::Statistics

#include "./CounterStatistics.ipp"
