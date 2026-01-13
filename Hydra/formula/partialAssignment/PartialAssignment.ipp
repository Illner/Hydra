#pragma once

#include "./PartialAssignment.hpp"

namespace Hydra::Formula::PartialAssignment {

    template <typename VarT, typename LiteralT>
    void PartialAssignment<VarT, LiteralT>::addLiteral(const LiteralType& lit) {
        assert(lit.getVariable() < variableStateStructVector_.size());

        #ifndef NDEBUG
        // The variable is assigned
        if (variableStateStructVector_[lit.getVariable()].isAssigned) {
            // The literal already exists in the partial assignment
            if (variableStateStructVector_[lit.getVariable()].sign == lit.isPositive())
                throw Exception::Formula::AttemptAddLiteralExistsInPartialAssignmentException(lit);

            // The complementary literal already exists in the partial assignment
            if (variableStateStructVector_[lit.getVariable()].sign != lit.isPositive())
                throw Exception::Formula::AttemptAddComplementaryLiteralToPartialAssignmentException(lit);
        }

        // Check the upper limit
        if (lit.getVariable() > maxNumberOfVariables_)
            throw Exception::Formula::AttemptAddVariableExceedsUpperLimitOfPartialAssignmentException(lit.getVariable(), maxNumberOfVariables_);

        // Zero literal
        if (lit.isZeroLiteral())
            throw Exception::Formula::FormulaException("Attempt to add a zero literal to the partial assignment!");
        #endif

        VariableStateStruct& variableState = variableStateStructVector_[lit.getVariable()];

        variableState.isAssigned = true;
        variableState.sign = lit.isPositive();

        ++numberOfVariablesInPartialAssignment_;
    }

    template <typename VarT, typename LiteralT>
    void PartialAssignment<VarT, LiteralT>::removeLiteral(const LiteralType& lit) {
        assert(numberOfVariablesInPartialAssignment_ > 0);
        assert(lit.getVariable() < variableStateStructVector_.size());

        #ifndef NDEBUG
        // The variable does not exist in the partial assignment
        if (!variableStateStructVector_[lit.getVariable()].isAssigned)
            throw Exception::Formula::AttemptDeleteLiteralDoesNotExistInPartialAssignmentException(lit);

        // The complementary literal exists in the partial assignment
        if (variableStateStructVector_[lit.getVariable()].isAssigned && (variableStateStructVector_[lit.getVariable()].sign != lit.isPositive()))
            throw Exception::Formula::AttemptDeleteComplementaryLiteralFromPartialAssignmentException(lit);
        #endif

        variableStateStructVector_[lit.getVariable()].isAssigned = false;

        --numberOfVariablesInPartialAssignment_;
    }

    template <typename VarT, typename LiteralT>
    bool PartialAssignment<VarT, LiteralT>::literalExists(const LiteralType& lit) const noexcept {
        assert(lit.getVariable() < variableStateStructVector_.size());

        const VariableStateStruct& variableState = variableStateStructVector_[lit.getVariable()];

        return (variableState.isAssigned && (variableState.sign == lit.isPositive()));
    }

    template <typename VarT, typename LiteralT>
    bool PartialAssignment<VarT, LiteralT>::complementaryLiteralExists(const LiteralType& lit) const noexcept {
        #if defined(TEST)
        if (lit.getVariable() >= variableStateStructVector_.size())
            return false;
        #endif

        assert(lit.getVariable() < variableStateStructVector_.size());

        const VariableStateStruct& variableState = variableStateStructVector_[lit.getVariable()];

        return (variableState.isAssigned && (variableState.sign != lit.isPositive()));
    }

    template <typename VarT, typename LiteralT>
    bool PartialAssignment<VarT, LiteralT>::variableExists(VarT var) const noexcept {
        #if defined(TEST)
        if (var >= variableStateStructVector_.size())
            return false;
        #endif

        assert(var < variableStateStructVector_.size());

        return variableStateStructVector_[var].isAssigned;
    }

    template <typename VarT, typename LiteralT>
    VarT PartialAssignment<VarT, LiteralT>::getNumberOfAssignedVariables() const noexcept {
        return numberOfVariablesInPartialAssignment_;
    }

    template <typename VarT, typename LiteralT>
    bool PartialAssignment<VarT, LiteralT>::areAllVariablesAssigned() const noexcept {
        return (numberOfVariablesInPartialAssignment_ == maxNumberOfVariables_);
    }

    template <typename VarT, typename LiteralT>
    VarT PartialAssignment<VarT, LiteralT>::getMaxNumberOfVariables() const noexcept {
        return maxNumberOfVariables_;
    }

    template <typename VarT, typename LiteralT>
    void PartialAssignment<VarT, LiteralT>::printSortedPartialAssignment(std::ostream& out) const {
        for (VarT var = 1; var < variableStateStructVector_.size(); ++var) {
            const VariableStateStruct& variableState = variableStateStructVector_[var];

            if (variableState.isAssigned)
                out << LiteralType(var, variableState.sign) << " ";
        }
    }

    template <typename VarT, typename LiteralT>
    void PartialAssignment<VarT, LiteralT>::printSortedVariablesInPartialAssignment(std::ostream& out) const {
        for (VarT var = 1; var < variableStateStructVector_.size(); ++var) {
            if (variableStateStructVector_[var].isAssigned)
                out << std::to_string(var) << " ";
        }
    }

    template <typename VarT, typename LiteralT>
    void PartialAssignment<VarT, LiteralT>::clear() noexcept {
        numberOfVariablesInPartialAssignment_ = (VarT)0;

        for (VarT var = 0; var < variableStateStructVector_.size(); ++var)
            variableStateStructVector_[var].isAssigned = false;
    }
}   // namespace Hydra::Formula::PartialAssignment
