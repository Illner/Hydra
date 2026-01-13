#pragma once

#include "Hydra/formula/Literal.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Exception::RenHCRecognition {

    /**
     * RenH-C recognition exception (main)
     */
    class RenHCRecognitionException : public CompilerException {
    public:
        explicit RenHCRecognitionException(const std::string& message)
            : CompilerException(message) { }

        explicit RenHCRecognitionException(std::string&& message)
            : CompilerException(std::move(message)) { }

        RenHCRecognitionException(const std::string& message, const std::string& functionName)
            : CompilerException(message, functionName) { }
    };

    /**
     * Aspvall formula has too many ...
     */
    class AspvallFormulaHasTooManySomethingException : public RenHCRecognitionException {
    public:
        explicit AspvallFormulaHasTooManySomethingException(const std::string& something)
            : RenHCRecognitionException("The Aspvall formula has too many " + something + "!") { }
    };

    /**
     * Attempt to remove a literal that is not the last assigned literal in the assignment stack
     */
    template <typename VarT, typename LiteralT>
    class AttemptRemoveNotLastAssignedLiteralFromAssignmentStackException : public RenHCRecognitionException {
    public:
        AttemptRemoveNotLastAssignedLiteralFromAssignmentStackException(const Hydra::Formula::Literal<VarT, LiteralT>& removingLiteral,
                                                                        const std::string& assignmentStackString)
            : RenHCRecognitionException("Attempt to remove the literal (" + removingLiteral.toString() +
                                        ") that is not the last assigned literal in the assignment stack (" + assignmentStackString + ")!") { }
    };
}   // namespace Hydra::Exception::RenHCRecognition
