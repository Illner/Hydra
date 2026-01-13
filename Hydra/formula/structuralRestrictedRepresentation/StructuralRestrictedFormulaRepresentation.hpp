#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/partialAssignment/PartialAssignment.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"
#include "Hydra/other/parser/Parser.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/circuit/node/enums/FormulaLeafPostprocessingTypeEnum.hpp"
#include "Hydra/formula/enums/ClauseStatusWatchedLiteralEnum.hpp"
#include "Hydra/formula/enums/StructuralRestrictedFormulaRepresentationTypeEnum.hpp"

namespace Hydra::Formula::StructuralRestrictedRepresentation {

    using FormulaSizeType = Hydra::Formula::Representation::FormulaSizeType;

    /**
     * Structural restricted formula representation
     * Note: the formula is immutable
     * Used for: KromCLeaf, RenHCLeaf, HornCLeaf, AntiHornCLeaf, and PcLeaf
     * Copy and move methods are disabled!
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class StructuralRestrictedFormulaRepresentation {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");
        static_assert(Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isValidClauseT::value, "Invalid ClauseIdT type!");

    private:
        using VectorSetType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VectorSetType;
        using ClauseSizeType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
        using ClauseIdSetType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdSetType;
        using LiteralVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
        using ClauseIdVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ClauseOffsetVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseOffsetVectorType;
        using ClauseIdReusableVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType;

    public:
        using LiteralType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using VariableSetType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using PartialAssignmentType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::PartialAssignmentType;
        using VariableSortedVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSortedVectorType;
        using MappingFromVariableToVariableType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::MappingFromVariableToVariableType;

    private:
        using WatchedLiteralType = std::optional<ClauseSizeType>;
        using ClauseWatchedLiteralsType = std::pair<WatchedLiteralType, WatchedLiteralType>;
        using ClauseWatchedLiteralsVectorType = std::vector<ClauseWatchedLiteralsType>;
        using MappingFromLiteralTToClauseIdVectorType = Other::HashMap::MapType<LiteralT, ClauseIdVectorType>;

    public:
        using BoolVectorType = std::vector<bool>;
        using FormulaRepresentationAbstractPtrType = const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;

    public:
        using FormulaLeafPostprocessingTypeEnum = Circuit::Node::FormulaLeafPostprocessingTypeEnum;

    public:
        StructuralRestrictedFormulaRepresentation(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                  const VariableSetType& currentComponentVariableSet,
                                                  FormulaLeafPostprocessingTypeEnum formulaLeafPostprocessingType,
                                                  StructuralRestrictedFormulaRepresentationTypeEnum structuralRestrictedFormulaRepresentationType,
                                                  [[maybe_unused]] bool checkNoUnitClause = true)
            : formula_(), switchedVariables_(), clauseOffsetVector_(), variableSortedVector_(),
              structuralRestrictedFormulaRepresentationType_(structuralRestrictedFormulaRepresentationType) {
            assert(structuralRestrictedFormulaRepresentationType_ != StructuralRestrictedFormulaRepresentationTypeEnum::renH_C);   // no renH-C

            initializeFormula(formulaRepresentationAbstractPtr, currentComponentVariableSet, formulaLeafPostprocessingType);

            assert(!checkNoUnitClause || noUnitClause());      // check no unit clause
            assert(formulaSatisfiesStructuralRestriction());   // the formula satisfies the structural restriction
        }

        StructuralRestrictedFormulaRepresentation(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                  const VariableSetType& currentComponentVariableSet, VariableSetType&& switchedVariables,
                                                  FormulaLeafPostprocessingTypeEnum formulaLeafPostprocessingType,
                                                  StructuralRestrictedFormulaRepresentationTypeEnum structuralRestrictedFormulaRepresentationType,
                                                  [[maybe_unused]] bool checkNoUnitClause = true)
            : formula_(), switchedVariables_(std::move(switchedVariables)), clauseOffsetVector_(), variableSortedVector_(),
              structuralRestrictedFormulaRepresentationType_(structuralRestrictedFormulaRepresentationType) {
            assert(structuralRestrictedFormulaRepresentationType_ == StructuralRestrictedFormulaRepresentationTypeEnum::renH_C);   // renH-C

            initializeFormula(formulaRepresentationAbstractPtr, currentComponentVariableSet, formulaLeafPostprocessingType);

            assert(!checkNoUnitClause || noUnitClause());      // check no unit clause
            assert(formulaSatisfiesStructuralRestriction());   // the formula satisfies the structural restriction
        }

        StructuralRestrictedFormulaRepresentation(const StructuralRestrictedFormulaRepresentation&) = delete;
        StructuralRestrictedFormulaRepresentation(StructuralRestrictedFormulaRepresentation&&) noexcept = delete;

        StructuralRestrictedFormulaRepresentation& operator=(const StructuralRestrictedFormulaRepresentation&) = delete;
        StructuralRestrictedFormulaRepresentation& operator=(StructuralRestrictedFormulaRepresentation&&) noexcept = delete;

    private:
        LiteralVectorType formula_;
        ClauseIdT numberOfClauses_;
        FormulaSizeType formulaSize_;
        VariableSetType switchedVariables_;
        ClauseOffsetVectorType clauseOffsetVector_;
        VariableSortedVectorType variableSortedVector_;

        StructuralRestrictedFormulaRepresentationTypeEnum structuralRestrictedFormulaRepresentationType_;

    private:
        /**
         * Initialize the data structures:
         *      formula_
         *      clauseOffsetVector_
         *      variableSortedVector_
         *      formulaSize_, numberOfClauses_
         * @param formulaRepresentationAbstractPtr a pointer to the formula representation
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param formulaLeafPostprocessingType a postprocessing type
         */
        void initializeFormula(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, const VariableSetType& currentComponentVariableSet,
                               FormulaLeafPostprocessingTypeEnum formulaLeafPostprocessingType);

        /**
         * Time complexity: O(|F|)
         * @return true if the formula contains no unit clause. Otherwise, false is returned.
         */
        bool noUnitClause() const noexcept;

        /**
         * Time complexity: O(|F|)
         * @return true if the formula is Krom-C. Otherwise, false is returned.
         */
        bool formulaIsKromC() const noexcept;

        /**
         * Time complexity: O(|F|)
         * @return true if the formula is Horn-C. Otherwise, false is returned.
         */
        bool formulaIsHornC() const noexcept;

        /**
         * Time complexity: O(|F|)
         * @return true if the formula is anti-Horn-C. Otherwise, false is returned.
         */
        bool formulaIsAntiHornC() const noexcept;

        /**
         * Time complexity: O(|F|)
         * @return true if the formula is renH-C. Otherwise, false is returned.
         */
        bool formulaIsRenHC() const noexcept;

        /**
         * Time complexity: O(|F|)
         * @return true if the formula satisfies the structural restriction defined by structuralRestrictedFormulaRepresentationType_. Otherwise, false is returned.
         */
        bool formulaSatisfiesStructuralRestriction() const;

        /**
         * Initialize both watched literals in the clause
         * Assert: both watched literals MUST NOT be set
         * Note: if it is returned that the clause is satisfied, the watched literals are reset
         * @param clauseId a clause ID
         * @param clauseWatchedLiterals two watched literals in the clause
         * @param partialAssignment a partial assignment
         * @return the clause status
         */
        ClauseStatusWatchedLiteralEnum initializeClauseWatchedLiterals(ClauseIdT clauseId, ClauseWatchedLiteralsType& clauseWatchedLiterals,
                                                                       const PartialAssignmentType& partialAssignment) const;

        /**
         * Update the watched literals which are invalid (based on the partial assignment)
         * Assert: both watched literals MUST be set
         * Note: if it is returned that the clause is satisfied, the watched literals are reset
         * @param clauseId a clause ID
         * @param clauseWatchedLiterals two watched literals in the clause
         * @param partialAssignment a partial assignment
         * @return the clause status
         */
        ClauseStatusWatchedLiteralEnum updateClauseWatchedLiterals(ClauseIdT clauseId, ClauseWatchedLiteralsType& clauseWatchedLiterals,
                                                                   const PartialAssignmentType& partialAssignment) const;

    public:
        /**
         * Getter
         * Time complexity: O(1)
         * @return the size of the formula
         */
        FormulaSizeType getFormulaSize() const noexcept;

        /**
         * Getter
         * Time complexity: O(1)
         * @return the number of clauses
         */
        ClauseIdT getNumberOfClauses() const noexcept;

        /**
         * Getter
         * Time complexity: O(1)
         * @return a sorted vector of variables in the formula
         */
        const VariableSortedVectorType& getVariableSortedVector() const noexcept;

        /**
         * Getter
         * Time complexity: O(1)
         * @return the number of variables in the formula
         */
        VarT getNumberOfVariables() const noexcept;

        /**
         * Check if the formula is satisfiable under the complete assignment
         * Assert: all the variables in the formula MUST be assigned in the complete assignment
         * @param completeAssignment a complete assignment
         * @return true if the formula is satisfiable under the complete assignment. Otherwise, false is returned.
         */
        bool isSatisfiableUnderCompleteAssignment(const PartialAssignmentType& completeAssignment) const;

        /**
         * Do unit propagation
         * Implied literals will be added to the partial assignment (partialAssignment)
         * The partial assignment will be cleared if a contradiction is found during unit propagation
         * Assert: the size of satisfiedClauseVector MUST be 0 (that is, no satisfied clauses), or the number of clauses
         * @param partialAssignment a partial assignment
         * @param satisfiedClauseVector [optional] a bit map representing satisfied clauses
         * @return true if the formula is consistent after applying unit propagation. Otherwise, false is returned.
         */
        bool unitPropagation(PartialAssignmentType& partialAssignment) const;
        bool unitPropagation(PartialAssignmentType& partialAssignment, BoolVectorType& satisfiedClauseVector) const;

        /**
         * Print the formula in the DIMACS CNF format
         * @param mappingFromVarToIndex a variable mapping function that is used while printing.
         * If a variable does not exist in the mapping, no mapping will be applied to the variable.
         */
        void printFormulaInDimacsCnfFormat(std::ostream& out, const MappingFromVariableToVariableType& mappingFromVarToIndex = {}) const;

    #ifndef NDEBUG
    public:
        void printStructuralRestrictedFormulaRepresentationDebug(std::ostream& out) const;
    #endif
    };
}   // namespace Hydra::Formula::StructuralRestrictedRepresentation

#include "./StructuralRestrictedFormulaRepresentation.ipp"
