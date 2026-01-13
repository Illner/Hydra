#pragma once

#include <cassert>
#include <vector>

#include "Hydra/circuit/node/NodeAbstract.hpp"
#include "Hydra/circuit/node/leafNode/LeafAbstract.hpp"
#include "Hydra/circuit/node/leafNode/formulaLeaf/Clause.hpp"
#include "Hydra/formula/partialAssignment/PartialAssignment.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"
#include "Hydra/other/parser/Parser.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/formula/enums/ClauseStatusEnum.hpp"
#include "Hydra/formula/enums/ClauseStatusWatchedLiteralEnum.hpp"
#include "Hydra/formula/enums/FormulaStatusEnum.hpp"

#ifndef NDEBUG
    #include <algorithm>
#endif

namespace Hydra::Circuit::Node {

    /**
     * Formula leaf representation (abstract class)
     * The formula cannot be modified
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class FormulaLeafAbstract : public LeafAbstract<VarT, LiteralT> {
    private:
        using LiteralType = typename NodeAbstract<VarT, LiteralT>::LiteralType;
        using LiteralSetType = typename NodeAbstract<VarT, LiteralT>::LiteralSetType;
        using BoolVectorType = typename NodeAbstract<VarT, LiteralT>::BoolVectorType;
        using VariableSetType = typename NodeAbstract<VarT, LiteralT>::VariableSetType;
        using LiteralVectorType = typename NodeAbstract<VarT, LiteralT>::LiteralVectorType;
        using NumberOfModelsType = typename NodeAbstract<VarT, LiteralT>::NumberOfModelsType;
        using PartialAssignmentType = typename NodeAbstract<VarT, LiteralT>::PartialAssignmentType;
        using ModelCountingCacheType = typename NodeAbstract<VarT, LiteralT>::ModelCountingCacheType;
        using LiteralSortedVectorType = typename NodeAbstract<VarT, LiteralT>::LiteralSortedVectorType;
        using VariableSortedVectorType = typename NodeAbstract<VarT, LiteralT>::VariableSortedVectorType;
        using MappingFromVariableToVariableType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToVariableType;
        using MappingFromIdNodeToVariableSetType = typename NodeAbstract<VarT, LiteralT>::MappingFromIdNodeToVariableSetType;

    private:
        using ClauseStatusEnum = Formula::ClauseStatusEnum;
        using FormulaStatusEnum = Formula::FormulaStatusEnum;
        using ClauseStatusWatchedLiteralEnum = Formula::ClauseStatusWatchedLiteralEnum;

    public:
        using ClauseSizeType = VarT;
        using ClauseIdType = SizeNodeType;
        using FormulaSizeType = SizeNodeType;
        using ClauseType = Clause<VarT, LiteralT>;
        using FormulaType = std::vector<ClauseType>;
        using ClauseIdVectorType = std::vector<ClauseIdType>;
        using ClauseIdSetType = Other::HashMap::SetType<ClauseIdType>;

    private:
        using ConstIteratorType = typename FormulaType::const_iterator;

    public:
        FormulaLeafAbstract(IdNodeType id, NodeTypeEnum nodeType, const FormulaType& formula)
            : LeafAbstract<VarT, LiteralT>(id, nodeType, 0), formula_(formula) {
            computeAndSetLeafSize();
        }

        FormulaLeafAbstract(IdNodeType id, NodeTypeEnum nodeType, FormulaType&& formula)
            : LeafAbstract<VarT, LiteralT>(id, nodeType, 0), formula_(std::move(formula)) {
            computeAndSetLeafSize();
        }

    private:
        inline static constexpr VarT S_ESTIMATED_NUMBER_OF_VARIABLES_ = 10;

    protected:
        FormulaType formula_;

    private:
        /**
         * Compute and set the size of the leaf
         * The size of the leaf is equal to |F| (or |F| + #clauses)
         * Time complexity: O(#clauses)
         * @param includeNumberOfClauses should be the number of clauses included in the size
         */
        void computeAndSetLeafSize(bool includeNumberOfClauses = true) noexcept;

        void setUsedVariables(BoolVectorType& usedVariableVector, VarT& numberOfUsedVariables) const override;

        bool processIsCircuitSmooth(MappingFromIdNodeToVariableSetType& mappingFromIdNodeToVariableSet) const override;

        NumberOfModelsType processModelCounting(const PartialAssignmentType& partialAssignment,
                                                ModelCountingCacheType& cache) const override;

        /**
         * Recursively try all assignments. For every satisfying assignment, increment the number of models.
         * @param indexVariable the index of a variable that should be assigned next
         * @param partialAssignment [auxiliary] an assignment
         * @param variableSortedVector a sorted vector of variables
         * @param numberOfModels [output] the number of models
         */
        void processModelCounting(VarT indexVariable, PartialAssignmentType& partialAssignment,
                                  const VariableSortedVectorType& variableSortedVector, NumberOfModelsType& numberOfModels) const;

    public:
        /**
         * Time complexity: O(#clauses)
         * @return the size of the formula
         */
        FormulaSizeType getFormulaSize() const noexcept;

        /**
         * Time complexity: O(|F|)
         * @return a set of variables in the formula
         */
        VariableSetType getVariableSet() const noexcept;

        /**
         * Time complexity: O(|F|)
         * @return the number of variables in the formula
         */
        VarT getNumberOfVariables() const noexcept;

        /**
         * Time complexity: O(1)
         * @return the number of clauses
         */
        ClauseIdType getNumberOfClauses() const noexcept;

        /**
         * Time complexity O(|F|)
         * Let M be any mapping function from Var to {1, 2, ..., |V|}
         * @return (M, M^(-1))
         */
        std::pair<MappingFromVariableToVariableType, MappingFromVariableToVariableType> getVariableMapping() const noexcept;

        /**
         * Print the formula in the DIMACS CNF format
         * @param mappingFromVarToIndex a variable mapping function that is used while printing.
         * If a variable does not exist in the mapping, no mapping will be applied to the variable.
         * @param numberOfVariables the number of variables in the formula (needed only for the Problem line).
         * If the number of variables is set to 0, the number of variables will be directly computed from the formula.
         * @param printProblemLine should be the Problem line printed
         */
        void printFormulaInDimacsCnfFormat(std::ostream& out,
                                           const MappingFromVariableToVariableType& mappingFromVarToIndex = {},
                                           VarT numberOfVariables = 0, bool printProblemLine = true) const;

        /**
         * Time complexity: O(|F|)
         * @return the formula status with respect to the partial assignment
         */
        FormulaStatusEnum getFormulaStatus(const PartialAssignmentType& partialAssignment) const;

        /**
         * Do unit propagation
         * Implied literals will be added to the partial assignment (partialAssignment)
         * The partial assignment will be cleared if a contradiction is found during unit propagation
         * @param partialAssignment a partial assignment
         * @return true if the formula is consistent after applying unit propagation. Otherwise, false is returned.
         */
        bool unitPropagation(PartialAssignmentType& partialAssignment);

    public:
        ConstIteratorType begin() const noexcept;
        ConstIteratorType end() const noexcept;

    #ifndef NDEBUG
    private:
        mutable bool d_sortedFormula_ = false;

    protected:
        /**
         * Sort the formula
         */
        void sortFormulaDebug();

        LiteralSortedVectorType computeAndReturnSortedLiteralsInCircuitDebug() const override;

        VariableSortedVectorType computeAndReturnSortedVariablesInCircuitDebug() const override;

    public:
        void printFormulaDebug(std::ostream& out);
    #endif
    };
}   // namespace Hydra::Circuit::Node

#include "./FormulaLeafAbstract.ipp"
