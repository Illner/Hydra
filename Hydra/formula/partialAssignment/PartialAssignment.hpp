#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Hydra/formula/Literal.hpp"

#include "Hydra/formula/exceptions/FormulaException.hpp"

namespace Hydra::Formula::PartialAssignment {

    /**
     * Partial assignment representation
     * Copy and move methods (default) are allowed!
     * Invariant: variables MUST be indexed from 1 to N (= maxNumberOfVariables_)
     * Exceptions:
     *      FormulaException (debug)
     *      AttemptAddLiteralExistsInPartialAssignmentException (debug)
     *      AttemptAddComplementaryLiteralToPartialAssignmentException (debug)
     *      AttemptDeleteLiteralDoesNotExistInPartialAssignmentException (debug)
     *      AttemptDeleteComplementaryLiteralFromPartialAssignmentException (debug)
     *      AttemptAddVariableExceedsUpperLimitOfPartialAssignmentException (debug)
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class PartialAssignment {
    private:
        using LiteralType = typename Literal<VarT, LiteralT>::LiteralType;
        using LiteralSetType = typename Literal<VarT, LiteralT>::LiteralSetType;
        using LiteralVectorType = typename Literal<VarT, LiteralT>::LiteralVectorType;

    private:
        struct VariableStateStruct {
        public:
            bool sign = true;
            bool isAssigned = false;
        };

    private:
        using VariableStateStructVectorType = std::vector<VariableStateStruct>;

    public:
        explicit PartialAssignment(VarT maxNumberOfVariables)
            : maxNumberOfVariables_(maxNumberOfVariables), numberOfVariablesInPartialAssignment_(0),
              variableStateStructVector_((VarT)1 + maxNumberOfVariables) { }

        PartialAssignment(const LiteralVectorType& literalVector, VarT maxNumberOfVariables)
            : maxNumberOfVariables_(maxNumberOfVariables), numberOfVariablesInPartialAssignment_(0),
              variableStateStructVector_((VarT)1 + maxNumberOfVariables) {
            for (const LiteralType& lit : literalVector)
                addLiteral(lit);
        }

        PartialAssignment(const LiteralSetType& literalSet, VarT maxNumberOfVariables)
            : maxNumberOfVariables_(maxNumberOfVariables), numberOfVariablesInPartialAssignment_(0),
              variableStateStructVector_((VarT)1 + maxNumberOfVariables) {
            for (const LiteralType& lit : literalSet)
                addLiteral(lit);
        }

        PartialAssignment(const PartialAssignment&) = default;
        PartialAssignment(PartialAssignment&&) noexcept = default;

        PartialAssignment& operator=(const PartialAssignment&) = default;
        PartialAssignment& operator=(PartialAssignment&&) noexcept = default;

    private:
        VarT maxNumberOfVariables_;
        VarT numberOfVariablesInPartialAssignment_;
        VariableStateStructVectorType variableStateStructVector_;

    public:
        /**
         * Add the literal to the partial assignment
         * Time complexity: O(1)
         * @throw FormulaException (debug) if the literal is a zero literal
         * @throw AttemptAddLiteralExistsInPartialAssignmentException (debug) if the literal already exists in the partial assignment
         * @throw AttemptAddComplementaryLiteralToPartialAssignmentException (debug) if the complementary literal already exists in the partial assignment
         * @throw AttemptAddVariableExceedsUpperLimitOfPartialAssignmentException (debug) if the variable exceeds the upper limit (= maxNumberOfVariables_)
         */
        void addLiteral(const LiteralType& lit);

        /**
         * Remove the literal from the partial assignment
         * Time complexity: O(1)
         * @throw AttemptDeleteLiteralDoesNotExistInPartialAssignmentException (debug) if the partial assignment does not contain the literal
         * @throw AttemptDeleteComplementaryLiteralFromPartialAssignmentException (debug) if the partial assignment contains the complementary literal
         */
        void removeLiteral(const LiteralType& lit);

        /**
         * Time complexity: O(1)
         * @return true if the literal exists in the partial assignment. Otherwise, false is returned.
         */
        bool literalExists(const LiteralType& lit) const noexcept;

        /**
         * Time complexity: O(1)
         * @return true if the complementary literal (-lit) exists in the partial assignment. Otherwise, false is returned.
         */
        bool complementaryLiteralExists(const LiteralType& lit) const noexcept;

        /**
         * Time complexity: O(1)
         * @return true if the variable exists in the partial assignment. Otherwise, false is returned.
         */
        bool variableExists(VarT var) const noexcept;

        /**
         * Time complexity: O(1)
         * @return the number of assigned variables
         */
        VarT getNumberOfAssignedVariables() const noexcept;

        /**
         * Time complexity: O(1)
         * @return true if all the variables (1, ..., maxNumberOfVariables_) are assigned. Otherwise, false is returned.
         */
        bool areAllVariablesAssigned() const noexcept;

        /**
         * Getter
         * @return the maximum number of variables (that is, the maximum index of a variable)
         */
        VarT getMaxNumberOfVariables() const noexcept;

        /**
         * Print SORTED partial assignment
         * Note: no prefix
         * Time complexity: O(maxNumberOfVariables_)
         */
        void printSortedPartialAssignment(std::ostream& out) const;

        /**
         * Print SORTED assigned variables in the partial assignment
         * Note: no prefix
         * Time complexity: O(maxNumberOfVariables_)
         */
        void printSortedVariablesInPartialAssignment(std::ostream& out) const;

        /**
         * Clear the partial assignment
         */
        void clear() noexcept;

    public:
        /**
         * ostream << Partial assignment
         */
        friend std::ostream& operator<<(std::ostream& out, const PartialAssignment& partialAssignment) {
            partialAssignment.printSortedPartialAssignment(out);

            return out;
        }
    };
}   // namespace Hydra::Formula::PartialAssignment

#include "PartialAssignment.ipp"
