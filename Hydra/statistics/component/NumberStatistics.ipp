#pragma once

#include "./NumberStatistics.hpp"

namespace Hydra::Statistics {

    template <typename TypeT>
    bool NumberStatistics<TypeT>::isSet() const noexcept {
        return set_;
    }

    template <typename TypeT>
    TypeT NumberStatistics<TypeT>::getNumber() const {
        // The number has not yet been set
        if (!set_)
            throw Exception::Statistics::NumberStatisticHasNotYetBeenSetException(name_);

        return number_;
    }

    template <typename TypeT>
    void NumberStatistics<TypeT>::setNumber(TypeT number) {
        // The number has already been set
        if (!canBeReset_ && set_)
            throw Exception::Statistics::NumberStatisticHasAlreadyBeenSetException(name_);

        set_ = true;
        number_ = number;
    }

    template <typename TypeT>
    void NumberStatistics<TypeT>::incrementNumber() {
        assert(canBeReset_);

        // The number has not yet been set
        if (!set_)
            throw Exception::Statistics::NumberStatisticHasNotYetBeenSetException(name_);

        ++number_;
    }

    template <typename TypeT>
    void NumberStatistics<TypeT>::incrementNumber(TypeT increment) {
        assert(canBeReset_);

        // The number has not yet been set
        if (!set_)
            throw Exception::Statistics::NumberStatisticHasNotYetBeenSetException(name_);

        number_ += increment;
    }

    template <typename TypeT>
    void NumberStatistics<TypeT>::printNumberStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const {
        // Name
        if (addLabels)
            Other::printTitle(out, name_, 50, '-');
        else {
            out << "Number: " << name_;

            if (!statisticsName.empty())
                out << " {" << statisticsName << "}";

            out << std::endl;
        }

        // Set
        if (addLabels)
            out << "Set: ";
        out << std::to_string(set_) << std::endl;

        // Number
        if (addLabels)
            out << "Number: ";
        out << std::to_string(number_) << std::endl;
    }
}   // namespace Hydra::Statistics
