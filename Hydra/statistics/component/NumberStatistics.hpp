#pragma once

#include <cassert>
#include <ostream>
#include <string>
#include <type_traits>

#include "Hydra/statistics/component/CounterStatistics.hpp"

#include "Hydra/statistics/exceptions/StatisticsException.hpp"

namespace Hydra::Statistics {

    /**
     * Number statistics representation
     * Copy and move methods are disabled!
     * Exception:
     *      NumberStatisticHasNotYetBeenSetException
     *      NumberStatisticHasAlreadyBeenSetException
     * @tparam TypeT type used for a number
     */
    template <typename TypeT>
    class NumberStatistics {
    private:
        using isValidTypeT = std::bool_constant<(std::is_same<TypeT, LargeNumberType>::value ||
                                                 std::is_same<TypeT, LargeFloatingNumberType>::value)>;

        static_assert(isValidTypeT::value, "Invalid TypeT type!");

    public:
        explicit NumberStatistics(std::string&& name, bool canBeReset = false)
            : set_(false), canBeReset_(canBeReset),
              name_(std::move(name)), number_(0) { }

        NumberStatistics(const NumberStatistics&) = delete;
        NumberStatistics(NumberStatistics&&) noexcept = delete;

        NumberStatistics& operator=(const NumberStatistics&) = delete;
        NumberStatistics& operator=(NumberStatistics&&) noexcept = delete;

    private:
        bool set_;
        bool canBeReset_;
        std::string name_;

        TypeT number_;

    public:
        /**
         * Getter
         * @return true if the number is set. Otherwise, false is returned.
         */
        bool isSet() const noexcept;

        /**
         * Getter
         * @return the number
         * @throw NumberStatisticHasNotYetBeenSetException if the number has not yet been set
         */
        TypeT getNumber() const;

        /**
         * Setter
         * @param number the number
         * @throw NumberStatisticHasAlreadyBeenSetException [!canBeReset_] if the number has already been set
         */
        void setNumber(TypeT number);

        /**
         * Increment the number
         * Assert: canBeReset_ = true
         * @throw NumberStatisticHasNotYetBeenSetException if the number has not yet been set
         */
        void incrementNumber();

        /**
         * Increment the number
         * Assert: canBeReset_ = true
         * @param increment the increment
         * @throw NumberStatisticHasNotYetBeenSetException if the number has not yet been set
         */
        void incrementNumber(TypeT increment);

        void printNumberStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels = true) const;
    };
}   // namespace Hydra::Statistics

#include "./NumberStatistics.ipp"
