#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/other/container/exceptions/VariableStateVectorException.hpp"

namespace Hydra::Container::VariableStateVector {

    /**
     * Variable state vector representation
     * Copy and move methods are disabled!
     * Exceptions:
     *      VariableIsNotAssignedException
     *      AttemptToReassignVariableException
     *      SomethingCannotBeSavedAsStdSizeTException
     *      AttemptToUnassignVariableThatHasNotBeenAssignedException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class VariableStateVector {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");

    public:
        using LiteralType = typename Formula::Literal<VarT, LiteralT>::LiteralType;

    private:
        struct VariableStateStruct {
        public:
            bool sign = true;
            bool isAssigned = false;
        };

    private:
        using VariableStateStructVectorType = std::vector<VariableStateStruct>;

    public:
        explicit VariableStateVector(VarT numberOfVariables)
            : variableStateStructVector_(static_cast<typename VariableStateStructVectorType::size_type>(1) + numberOfVariables) {
            // The variables cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<VarT>(numberOfVariables, 1))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("variables", numberOfVariables);
        }

        VariableStateVector(const VariableStateVector&) = delete;
        VariableStateVector(VariableStateVector&&) noexcept = delete;

        VariableStateVector& operator=(const VariableStateVector&) = delete;
        VariableStateVector& operator=(VariableStateVector&&) noexcept = delete;

    private:
        VariableStateStructVectorType variableStateStructVector_;

    public:
        /**
         * Check if the variable is assigned
         * @param variable a variable
         * @return true if the variable is assigned. Otherwise, false is returned.
         */
        bool isAssigned(VarT variable) const;
        bool isAssigned(const LiteralType& lit) const;

        /**
         * Unassign the variable
         * @param variable a variable
         * @throw AttemptToUnassignVariableThatHasNotBeenAssignedException if the variable is not assigned
         */
        void unassignVariable(VarT variable);
        void unassignVariable(const LiteralType& lit);

        /**
         * Assign the variable
         * @param variable a variable
         * @param sign a sign of the assignment
         * @throw AttemptToReassignVariableException if the variable is already assigned
         */
        void assignVariable(VarT variable, bool sign);
        void assignVariable(const LiteralType& lit);

        /**
         * Get the sign of the assigned variable
         * @param variable a variable
         * @return the sign
         * @throw VariableIsNotAssignedException if the variable is not assigned
         */
        bool getSignOfAssignedVariable(VarT variable) const;
        bool getSignOfAssignedVariable(const LiteralType& lit) const;

        /**
         * Check if the literal is satisfied
         * Assert: the literal MUST NOT be a zero literal
         * @param lit a literal
         * @return true if the literal is satisfied. Otherwise, false is returned.
         * @throw VariableIsNotAssignedException if the variable is not assigned
         */
        bool isLiteralSatisfied(const LiteralType& lit) const;

        /**
         * Check if all the variables are unassigned
         * Note: used for checking if the structure is empty
         * Time complexity: O(#variables)
         * @return true if all the variables are unassigned. Otherwise, false is returned.
         */
        bool areAllVariablesUnassigned() const noexcept;

        /**
         * Check if all the variables are assigned
         * Time complexity: O(#variables)
         * @return true if all the variables are assigned. Otherwise, false is returned.
         */
        bool areAllVariablesAssigned() const noexcept;

        /**
         * @return the number of variables
         */
        VarT getNumberOfVariables() const noexcept;

        /**
         * Clear the structure (that is, unassign all the variables)
         */
        void clear() noexcept;

    #ifndef NDEBUG
    public:
        void printVariableStateVectorDebug(std::ostream& out) const;
    #endif
    };
}   // namespace Hydra::Container::VariableStateVector

#include "./VariableStateVector.ipp"
