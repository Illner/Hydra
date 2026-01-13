#pragma once

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Exception::DecisionHeuristic {

    /**
     * Decision heuristic exception (main)
     */
    class DecisionHeuristicException : public CompilerException {
    public:
        explicit DecisionHeuristicException(const std::string& message)
            : CompilerException(message) { }

        explicit DecisionHeuristicException(std::string&& message)
            : CompilerException(std::move(message)) { }

        DecisionHeuristicException(const std::string& message, const std::string& functionName)
            : CompilerException(message, functionName) { }
    };
}   // namespace Hydra::Exception::DecisionHeuristic
