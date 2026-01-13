#pragma once

#include "Hydra/circuit/node/NodeAbstract.hpp"
#include "Hydra/circuit/node/leafNode/formulaLeaf/FormulaLeafAbstract.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/partialAssignment/PartialAssignment.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/circuit/node/exceptions/NodeException.hpp"
#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Circuit::Node {

    inline constexpr char KROM_C_LEAF = 'K';

    /**
     * Krom-C leaf representation (final class)
     * Exceptions:
     *      FormulaIsNotKromCException (debug)
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class KromCLeaf final : public FormulaLeafAbstract<VarT, LiteralT> {
    private:
        using LiteralType = typename NodeAbstract<VarT, LiteralT>::LiteralType;
        using ClauseType = typename FormulaLeafAbstract<VarT, LiteralT>::ClauseType;
        using FormulaType = typename FormulaLeafAbstract<VarT, LiteralT>::FormulaType;
        using VariableSetType = typename NodeAbstract<VarT, LiteralT>::VariableSetType;
        using PartialAssignmentType = typename NodeAbstract<VarT, LiteralT>::PartialAssignmentType;
        using CopySubcircuitCacheType = typename NodeAbstract<VarT, LiteralT>::CopySubcircuitCacheType;
        using ConsistencyCheckCacheType = typename NodeAbstract<VarT, LiteralT>::ConsistencyCheckCacheType;
        using MappingFromVariableToLiteralType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToLiteralType;
        using MappingFromVariableToVariableType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToVariableType;
        using MappingFromVariableToOriginalVariableType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;

    public:
        KromCLeaf(IdNodeType id, const FormulaType& formula)
            : FormulaLeafAbstract<VarT, LiteralT>(id, NodeTypeEnum::Krom_C_LEAF, formula) {
            #ifndef NDEBUG
            isKrom(true);
            #endif
        }

        KromCLeaf(IdNodeType id, FormulaType&& formula)
            : FormulaLeafAbstract<VarT, LiteralT>(id, NodeTypeEnum::Krom_C_LEAF, std::move(formula)) {
            #ifndef NDEBUG
            isKrom(true);
            #endif
        }

    private:
        bool processConsistencyCheck(const PartialAssignmentType& partialAssignment,
                                     const VariableSetType& forgottenVariableSet,
                                     ConsistencyCheckCacheType& cache) override;

        IdNodeType copySubcircuit(Circuit<VarT, LiteralT>* circuit, const MappingFromVariableToLiteralType& mapping,
                                  CopySubcircuitCacheType& cache, bool isVariableToLiteralMapping) override;

    public:
        void printNode(std::ostream& out, const MappingFromVariableToOriginalVariableType& mapping) const override;

        /**
         * Check if the formula is Krom
         * Time complexity: O(#clauses)
         * @return true if the formula is Krom. Otherwise, false is returned.
         * @throw FormulaIsNotKromCException [throwException] if the formula is not Krom
         */
        bool isKrom(bool throwException = false) const;

    #ifndef NDEBUG
    public:
        void printNodeDebug(std::ostream& out) override;
    #endif
    };
}   // namespace Hydra::Circuit::Node

#include "./KromCLeaf.ipp"
