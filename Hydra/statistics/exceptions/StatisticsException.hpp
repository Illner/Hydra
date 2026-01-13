#pragma once

#include <string>

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Exception::Statistics {

    /**
     * Statistics exception (main)
     */
    class StatisticsException : public CompilerException {
    public:
        explicit StatisticsException(const std::string& message)
            : CompilerException(message) { }

        explicit StatisticsException(std::string&& message)
            : CompilerException(std::move(message)) { }

        StatisticsException(const std::string& message, const std::string& functionName)
            : CompilerException(message, functionName) { }
    };

    /**
     * Number statistic has already been set
     */
    class NumberStatisticHasAlreadyBeenSetException : public StatisticsException {
    public:
        explicit NumberStatisticHasAlreadyBeenSetException(const std::string& numberStatisticsName)
            : StatisticsException("The number statistic (" + numberStatisticsName + ") has already been set!") { }
    };

    /**
     * Number statistic has not yet been set
     */
    class NumberStatisticHasNotYetBeenSetException : public StatisticsException {
    public:
        explicit NumberStatisticHasNotYetBeenSetException(const std::string& numberStatisticsName)
            : StatisticsException("The number statistic (" + numberStatisticsName + ") has not yet been set!") { }
    };
}   // namespace Hydra::Exception::Statistics
