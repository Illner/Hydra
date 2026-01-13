#pragma once

#include <string>

#include "Hydra/formula/Literal.hpp"

#include "Hydra/formula/exceptions/FormulaException.hpp"

#include "Hydra/formula/enums/FormulaRepresentationTypeEnum.hpp"
#include "Hydra/formula/enums/RecognitionTypeEnum.hpp"

namespace Hydra::Exception::Formula::Representation {

    /**
     * Formula representation exception (main)
     */
    class FormulaRepresentationException : public FormulaException {
    public:
        explicit FormulaRepresentationException(const std::string& message)
            : FormulaException(message) { }

        explicit FormulaRepresentationException(std::string&& message)
            : FormulaException(std::move(message)) { }

        FormulaRepresentationException(const std::string& message, const std::string& functionName)
            : FormulaException(message, functionName) { }
    };

    /**
     * Formula representation does not support the function
     */
    class FormulaRepresentationDoesNotSupportFunctionException : public FormulaRepresentationException {
    public:
        FormulaRepresentationDoesNotSupportFunctionException(Hydra::Formula::Representation::FormulaRepresentationTypeEnum formulaRepresentationType,
                                                             const std::string& functionName)
            : FormulaRepresentationException("The formula representation (" +
                                             Hydra::Formula::Representation::formulaRepresentationEnumToString(formulaRepresentationType) +
                                             ") does not support the function (" + functionName + ")!") { }
    };

    /**
     * Iterating over a satisfied clause
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class IteratingOverSatisfiedClauseException : public FormulaRepresentationException {
    public:
        IteratingOverSatisfiedClauseException(ClauseIdT clauseId, const Hydra::Formula::Literal<VarT, LiteralT>& satisfiedLiteral)
            : FormulaRepresentationException("Iterating over a satisfied clause (clause ID: " + std::to_string(clauseId) +
                                             ", satisfied literal: " + satisfiedLiteral.toString() + ")!") { }
    };

    /**
     * Attempt to remove a literal that is not the last assigned literal in the assignment stack
     */
    template <typename VarT, typename LiteralT>
    class AttemptRemoveNotLastAssignedLiteralFromAssignmentStackException : public FormulaRepresentationException {
    public:
        AttemptRemoveNotLastAssignedLiteralFromAssignmentStackException(const Hydra::Formula::Literal<VarT, LiteralT>& removingLiteral,
                                                                        const std::string& assignmentStackString)
            : FormulaRepresentationException("Attempt to remove the literal (" + removingLiteral.toString() +
                                             ") that is not the last assigned literal in the assignment stack (" + assignmentStackString + ")!") { }
    };

    /**
     * The i-th element of the partial assignment does not exist
     */
    template <typename VarT>
    class IthElementOfPartialAssignmentDoesNotExistException : public FormulaRepresentationException {
    public:
        IthElementOfPartialAssignmentDoesNotExistException(VarT i, VarT partialAssignmentSize)
            : FormulaRepresentationException("The " + std::to_string(i) + "th element of the partial assignment with the size of " +
                                             std::to_string(partialAssignmentSize) + " does not exist!") { }
    };

    /**
     * Formula is empty
     */
    class FormulaIsEmptyException : public FormulaRepresentationException {
    public:
        FormulaIsEmptyException()
            : FormulaRepresentationException("The formula is empty!") { }
    };

    /**
     * Recognition of something is not supported
     */
    class RecognitionOfSomethingIsNotSupportedException : public FormulaRepresentationException {
    public:
        explicit RecognitionOfSomethingIsNotSupportedException(Hydra::Formula::Representation::RecognitionTypeEnum recognitionType)
            : FormulaRepresentationException("Recognition of " +
                                             Hydra::Formula::Representation::recognitionTypeEnumToString(recognitionType) +
                                             " is not supported!") { }
    };
}   // namespace Hydra::Exception::Formula::Representation
