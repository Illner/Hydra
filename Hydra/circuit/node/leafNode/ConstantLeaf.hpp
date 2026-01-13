#pragma once

#include "Hydra/circuit/node/innerNode/AndInnerNode.hpp"
#include "Hydra/circuit/node/innerNode/OrInnerNode.hpp"
#include "Hydra/circuit/node/leafNode/LeafAbstract.hpp"
#include "Hydra/formula/partialAssignment/PartialAssignment.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#define CONSTANT_LEAF_SIZE 0

namespace Hydra::Circuit::Node {

    /**
     * Constant leaf representation (final class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class ConstantLeaf final : public LeafAbstract<VarT, LiteralT> {
    private:
        using LiteralType = typename NodeAbstract<VarT, LiteralT>::LiteralType;
        using BoolVectorType = typename NodeAbstract<VarT, LiteralT>::BoolVectorType;
        using VariableSetType = typename NodeAbstract<VarT, LiteralT>::VariableSetType;
        using NumberOfModelsType = typename NodeAbstract<VarT, LiteralT>::NumberOfModelsType;
        using PartialAssignmentType = typename NodeAbstract<VarT, LiteralT>::PartialAssignmentType;
        using ModelCountingCacheType = typename NodeAbstract<VarT, LiteralT>::ModelCountingCacheType;
        using CopySubcircuitCacheType = typename NodeAbstract<VarT, LiteralT>::CopySubcircuitCacheType;
        using LiteralSortedVectorType = typename NodeAbstract<VarT, LiteralT>::LiteralSortedVectorType;
        using VariableSortedVectorType = typename NodeAbstract<VarT, LiteralT>::VariableSortedVectorType;
        using ConsistencyCheckCacheType = typename NodeAbstract<VarT, LiteralT>::ConsistencyCheckCacheType;
        using MappingFromVariableToLiteralType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToLiteralType;
        using MappingFromIdNodeToVariableSetType = typename NodeAbstract<VarT, LiteralT>::MappingFromIdNodeToVariableSetType;
        using MappingFromVariableToOriginalVariableType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;

    public:
        ConstantLeaf(IdNodeType id, bool constant) noexcept
            : LeafAbstract<VarT, LiteralT>(id, NodeTypeEnum::CONSTANT_LEAF, CONSTANT_LEAF_SIZE), constant_(constant) { }

    private:
        bool constant_;

    private:
        void setUsedVariables(BoolVectorType& usedVariableVector, VarT& numberOfUsedVariables) const override;

        bool processIsCircuitSmooth(MappingFromIdNodeToVariableSetType& mappingFromIdNodeToVariableSet) const override;

        bool processConsistencyCheck(const PartialAssignmentType& partialAssignment,
                                     const VariableSetType& forgottenVariableSet,
                                     ConsistencyCheckCacheType& cache) override;

        NumberOfModelsType processModelCounting(const PartialAssignmentType& partialAssignment,
                                                ModelCountingCacheType& cache) const override;

        IdNodeType copySubcircuit(Circuit<VarT, LiteralT>* circuit, const MappingFromVariableToLiteralType& mapping,
                                  CopySubcircuitCacheType& cache, bool isVariableToLiteralMapping) override;

    public:
        void printNode(std::ostream& out, const MappingFromVariableToOriginalVariableType& mapping) const override;

        /**
         * Getter
         * @return the leaf's constant (TRUE / FALSE)
         */
        bool getConstant() const noexcept;

    #ifndef NDEBUG
    private:
        LiteralSortedVectorType computeAndReturnSortedLiteralsInCircuitDebug() const override;

        VariableSortedVectorType computeAndReturnSortedVariablesInCircuitDebug() const override;

    public:
        void printNodeDebug(std::ostream& out) override;
    #endif
    };
}   // namespace Hydra::Circuit::Node

#include "./ConstantLeaf.ipp"
