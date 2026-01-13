#pragma once

#include "./VariableStateVector.hpp"

namespace Hydra::Container::VariableStateVector {

    template <typename VarT, typename LiteralT>
    bool VariableStateVector<VarT, LiteralT>::isAssigned(VarT variable) const {
        assert(variable > 0);
        assert(variable < variableStateStructVector_.size());

        return variableStateStructVector_[variable].isAssigned;
    }

    template <typename VarT, typename LiteralT>
    bool VariableStateVector<VarT, LiteralT>::isAssigned(const LiteralType& lit) const {
        return isAssigned(lit.getVariable());
    }

    template <typename VarT, typename LiteralT>
    void VariableStateVector<VarT, LiteralT>::unassignVariable(VarT variable) {
        assert(variable > 0);
        assert(variable < variableStateStructVector_.size());

        VariableStateStruct& variableState = variableStateStructVector_[variable];

        // The variable is NOT assigned
        if (!variableState.isAssigned)
            throw Exception::Container::VariableStateVector::AttemptToUnassignVariableThatHasNotBeenAssignedException(variable);

        variableState.isAssigned = false;
    }

    template <typename VarT, typename LiteralT>
    void VariableStateVector<VarT, LiteralT>::unassignVariable(const LiteralType& lit) {
        unassignVariable(lit.getVariable());
    }

    template <typename VarT, typename LiteralT>
    void VariableStateVector<VarT, LiteralT>::assignVariable(VarT variable, bool sign) {
        assert(variable > 0);
        assert(variable < variableStateStructVector_.size());

        VariableStateStruct& variableState = variableStateStructVector_[variable];

        // The variable is already assigned
        if (variableState.isAssigned)
            throw Exception::Container::VariableStateVector::AttemptToReassignVariableException(variable);

        variableState.sign = sign;
        variableState.isAssigned = true;
    }

    template <typename VarT, typename LiteralT>
    void VariableStateVector<VarT, LiteralT>::assignVariable(const LiteralType& lit) {
        assignVariable(lit.getVariable(), lit.isPositive());
    }

    template <typename VarT, typename LiteralT>
    bool VariableStateVector<VarT, LiteralT>::getSignOfAssignedVariable(VarT variable) const {
        assert(variable > 0);
        assert(variable < variableStateStructVector_.size());

        const VariableStateStruct& variableState = variableStateStructVector_[variable];

        // The variable is not assigned
        if (!variableState.isAssigned)
            throw Exception::Container::VariableStateVector::VariableIsNotAssignedException(variable);

        return variableState.sign;
    }

    template <typename VarT, typename LiteralT>
    bool VariableStateVector<VarT, LiteralT>::getSignOfAssignedVariable(const LiteralType& lit) const {
        return getSignOfAssignedVariable(lit.getVariable());
    }

    template <typename VarT, typename LiteralT>
    bool VariableStateVector<VarT, LiteralT>::isLiteralSatisfied(const LiteralType& lit) const {
        assert(!lit.isZeroLiteral());   // not a zero literal
        assert(lit.getVariable() < variableStateStructVector_.size());

        const VariableStateStruct& variableState = variableStateStructVector_[lit.getVariable()];

        // The variable is not assigned
        if (!variableState.isAssigned)
            throw Exception::Container::VariableStateVector::VariableIsNotAssignedException(lit.getVariable());

        return (lit.isPositive() == variableState.sign);
    }

    template <typename VarT, typename LiteralT>
    bool VariableStateVector<VarT, LiteralT>::areAllVariablesUnassigned() const noexcept {
        for (VarT var = 1; var < variableStateStructVector_.size(); ++var) {
            if (variableStateStructVector_[var].isAssigned)
                return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT>
    bool VariableStateVector<VarT, LiteralT>::areAllVariablesAssigned() const noexcept {
        for (VarT var = 1; var < variableStateStructVector_.size(); ++var) {
            if (!variableStateStructVector_[var].isAssigned)
                return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT>
    VarT VariableStateVector<VarT, LiteralT>::getNumberOfVariables() const noexcept {
        return static_cast<VarT>(variableStateStructVector_.size() - 1);
    }

    template <typename VarT, typename LiteralT>
    void VariableStateVector<VarT, LiteralT>::clear() noexcept {
        for (VariableStateStruct& variableState : variableStateStructVector_) {
            variableState.sign = true;
            variableState.isAssigned = false;
        }
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    void VariableStateVector<VarT, LiteralT>::printVariableStateVectorDebug(std::ostream& out) const {
        out << "Variable state vector:";
        for (VarT var = 1; var < variableStateStructVector_.size(); ++var) {
            out << " ";

            const VariableStateStruct& variableState = variableStateStructVector_[var];

            // The variable is NOT assigned
            if (!variableState.isAssigned)
                out << "_";
            // The variable is assigned
            else
                out << LiteralType(var, variableState.sign);
        }
        out << std::endl;
    }
    #endif
}   // namespace Hydra::Container::VariableStateVector
