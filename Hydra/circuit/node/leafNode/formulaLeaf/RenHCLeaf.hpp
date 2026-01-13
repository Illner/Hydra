#pragma once

#include "Hydra/circuit/node/NodeAbstract.hpp"
#include "Hydra/circuit/node/leafNode/formulaLeaf/FormulaLeafAbstract.hpp"
#include "Hydra/formula/partialAssignment/PartialAssignment.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/circuit/node/exceptions/NodeException.hpp"
#include "Hydra/compiler/exceptions/CompilerException.hpp"

#ifndef NDEBUG
    #include <algorithm>
    #include <vector>
#endif

namespace Hydra::Circuit::Node {

    inline constexpr char RENH_C_LEAF = 'R';

    /**
     * RenH-C leaf representation (final class)
     * Exception:
     *      FormulaIsNotRenHCException (debug)
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class RenHCLeaf final : public FormulaLeafAbstract<VarT, LiteralT> {
    private:
        using LiteralType = typename NodeAbstract<VarT, LiteralT>::LiteralType;
        using ClauseType = typename FormulaLeafAbstract<VarT, LiteralT>::ClauseType;
        using FormulaType = typename FormulaLeafAbstract<VarT, LiteralT>::FormulaType;
        using VariableSetType = typename NodeAbstract<VarT, LiteralT>::VariableSetType;
        using PartialAssignmentType = typename NodeAbstract<VarT, LiteralT>::PartialAssignmentType;
        using CopySubcircuitCacheType = typename NodeAbstract<VarT, LiteralT>::CopySubcircuitCacheType;
        using VariableSortedVectorType = typename NodeAbstract<VarT, LiteralT>::VariableSortedVectorType;
        using ConsistencyCheckCacheType = typename NodeAbstract<VarT, LiteralT>::ConsistencyCheckCacheType;
        using MappingFromVariableToLiteralType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToLiteralType;
        using MappingFromVariableToVariableType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToVariableType;
        using MappingFromVariableToOriginalVariableType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;

    public:
        RenHCLeaf(IdNodeType id, const FormulaType& formula, const VariableSetType& switchedVariables)
            : FormulaLeafAbstract<VarT, LiteralT>(id, NodeTypeEnum::renH_C_LEAF, formula),
              switchedVariables_(switchedVariables) {
            #ifndef NDEBUG
            isRenamableHorn(true);
            #endif
        }

        RenHCLeaf(IdNodeType id, const FormulaType& formula, VariableSetType&& switchedVariables)
            : FormulaLeafAbstract<VarT, LiteralT>(id, NodeTypeEnum::renH_C_LEAF, formula),
              switchedVariables_(std::move(switchedVariables)) {
            #ifndef NDEBUG
            isRenamableHorn(true);
            #endif
        }

        RenHCLeaf(IdNodeType id, FormulaType&& formula, const VariableSetType& switchedVariables)
            : FormulaLeafAbstract<VarT, LiteralT>(id, NodeTypeEnum::renH_C_LEAF, std::move(formula)),
              switchedVariables_(switchedVariables) {
            #ifndef NDEBUG
            isRenamableHorn(true);
            #endif
        }

        RenHCLeaf(IdNodeType id, FormulaType&& formula, VariableSetType&& switchedVariables)
            : FormulaLeafAbstract<VarT, LiteralT>(id, NodeTypeEnum::renH_C_LEAF, std::move(formula)),
              switchedVariables_(std::move(switchedVariables)) {
            #ifndef NDEBUG
            isRenamableHorn(true);
            #endif
        }

    private:
        VariableSetType switchedVariables_;

    private:
        bool processConsistencyCheck(const PartialAssignmentType& partialAssignment,
                                     const VariableSetType& forgottenVariableSet,
                                     ConsistencyCheckCacheType& cache) override;

        IdNodeType copySubcircuit(Circuit<VarT, LiteralT>* circuit, const MappingFromVariableToLiteralType& mapping,
                                  CopySubcircuitCacheType& cache, bool isVariableToLiteralMapping) override;

    public:
        void printNode(std::ostream& out, const MappingFromVariableToOriginalVariableType& mapping) const override;

        /**
         * Check if the formula is renamable Horn with respect to the switched variables
         * Time complexity: O(|F|)
         * @return true if the formula is renamable Horn. Otherwise, false is returned.
         * @throw FormulaIsNotRenHCException [throwException] if the formula is not renamable Horn
         */
        bool isRenamableHorn(bool throwException = false) const;

        /**
         * Print the switched variables
         * Note: no prefix
         */
        void printSwitchedVariables(std::ostream& out) const;

    #ifndef NDEBUG
    private:
        /**
         * Print the SORTED switched variables
         * Note: prefix
         */
        void printSortedSwitchedVariablesDebug(std::ostream& out) const;

    public:
        void printNodeDebug(std::ostream& out) override;
    #endif
    };
}   // namespace Hydra::Circuit::Node

#include "./RenHCLeaf.ipp"
