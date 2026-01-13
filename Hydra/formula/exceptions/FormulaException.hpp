#pragma once

#include "Hydra/formula/Literal.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Exception::Formula {

    /**
     * Formula exception (main)
     */
    class FormulaException : public CompilerException {
    public:
        explicit FormulaException(const std::string& message)
            : CompilerException(message) { }

        explicit FormulaException(std::string&& message)
            : CompilerException(std::move(message)) { }

        FormulaException(const std::string& message, const std::string& functionName)
            : CompilerException(message, functionName) { }
    };

    /**
     * Attempt to add a literal that already exists in the partial assignment
     */
    template <typename VarT, typename LiteralT>
    class AttemptAddLiteralExistsInPartialAssignmentException : public FormulaException {
    public:
        explicit AttemptAddLiteralExistsInPartialAssignmentException(const Hydra::Formula::Literal<VarT, LiteralT>& lit)
            : FormulaException("Attempt to add the literal (" + lit.toString() + ") that already exists in the partial assignment!") { }
    };

    /**
     * Attempt to add a complementary literal to the partial assignment
     */
    template <typename VarT, typename LiteralT>
    class AttemptAddComplementaryLiteralToPartialAssignmentException : public FormulaException {
    public:
        explicit AttemptAddComplementaryLiteralToPartialAssignmentException(const Hydra::Formula::Literal<VarT, LiteralT>& lit)
            : FormulaException("Attempt to add the complementary literal (" + lit.toString() + ") to the partial assignment!") { }
    };

    /**
     * Attempt to delete a literal that does not exist in the partial assignment
     */
    template <typename VarT, typename LiteralT>
    class AttemptDeleteLiteralDoesNotExistInPartialAssignmentException : public FormulaException {
    public:
        explicit AttemptDeleteLiteralDoesNotExistInPartialAssignmentException(const Hydra::Formula::Literal<VarT, LiteralT>& lit)
            : FormulaException("Attempt to delete the literal (" + lit.toString() + ") that does not exist in the partial assignment!") { }
    };

    /**
     * Attempt to delete a complementary literal from the partial assignment
     */
    template <typename VarT, typename LiteralT>
    class AttemptDeleteComplementaryLiteralFromPartialAssignmentException : public FormulaException {
    public:
        explicit AttemptDeleteComplementaryLiteralFromPartialAssignmentException(const Hydra::Formula::Literal<VarT, LiteralT>& lit)
            : FormulaException("Attempt to delete the complementary literal (" + lit.toString() + ") from the partial assignment!") { }
    };

    /**
     * Attempt to add a variable that exceeds the upper limit of a partial assignment
     */
    template <typename VarT>
    class AttemptAddVariableExceedsUpperLimitOfPartialAssignmentException : public FormulaException {
    public:
        AttemptAddVariableExceedsUpperLimitOfPartialAssignmentException(VarT addedVariable, VarT upperLimit)
            : FormulaException("Attempt to add the variable (" + std::to_string(addedVariable) + ") that exceeds the upper limit (" + std::to_string(upperLimit) + ") of the partial assignment!") { }
    };
}   // namespace Hydra::Exception::Formula
