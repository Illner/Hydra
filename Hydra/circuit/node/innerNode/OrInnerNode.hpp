#pragma once

#include <cassert>

#include "Hydra/circuit/node/NodeAbstract.hpp"
#include "Hydra/circuit/node/innerNode/InnerNodeAbstract.hpp"
#include "Hydra/circuit/node/leafNode/LiteralLeaf.hpp"
#include "Hydra/formula/partialAssignment/PartialAssignment.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/circuit/node/exceptions/NodeException.hpp"

namespace Hydra::Circuit::Node {

    inline constexpr char OR_INNER_NODE = 'O';

    /**
     * OR inner node representation
     * Exceptions:
     *      OrInnerNodesDoNotSupportModelCountingException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class OrInnerNode : public InnerNodeAbstract<VarT, LiteralT> {
    private:
        using LiteralType = typename NodeAbstract<VarT, LiteralT>::LiteralType;
        using ChildPtrType = typename NodeAbstract<VarT, LiteralT>::ChildPtrType;
        using VariableSetType = typename NodeAbstract<VarT, LiteralT>::VariableSetType;
        using ChildConstPtrType = typename NodeAbstract<VarT, LiteralT>::ChildConstPtrType;
        using LiteralVectorType = typename NodeAbstract<VarT, LiteralT>::LiteralVectorType;
        using NumberOfModelsType = typename NodeAbstract<VarT, LiteralT>::NumberOfModelsType;
        using ChildrenPtrVectorType = typename NodeAbstract<VarT, LiteralT>::ChildrenPtrVectorType;
        using PartialAssignmentType = typename NodeAbstract<VarT, LiteralT>::PartialAssignmentType;
        using ModelCountingCacheType = typename NodeAbstract<VarT, LiteralT>::ModelCountingCacheType;
        using CopySubcircuitCacheType = typename NodeAbstract<VarT, LiteralT>::CopySubcircuitCacheType;
        using VariableSortedVectorType = typename NodeAbstract<VarT, LiteralT>::VariableSortedVectorType;
        using ConsistencyCheckCacheType = typename NodeAbstract<VarT, LiteralT>::ConsistencyCheckCacheType;
        using MappingFromVariableToLiteralType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToLiteralType;
        using MappingFromIdNodeToVariableSetType = typename NodeAbstract<VarT, LiteralT>::MappingFromIdNodeToVariableSetType;
        using MappingFromVariableToOriginalVariableType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;

    private:
        using LiteralLeafType = Node::LiteralLeaf<VarT, LiteralT>;

    public:
        OrInnerNode(IdNodeType id, const ChildrenPtrVectorType& childrenPtrVector, NodeTypeEnum nodeType = NodeTypeEnum::OR_INNER_NODE)
            : InnerNodeAbstract<VarT, LiteralT>(id, nodeType, childrenPtrVector) { }

        OrInnerNode(IdNodeType id, ChildrenPtrVectorType&& childrenPtrVector, NodeTypeEnum nodeType = NodeTypeEnum::OR_INNER_NODE)
            : InnerNodeAbstract<VarT, LiteralT>(id, nodeType, std::move(childrenPtrVector)) { }

    private:
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

    #ifndef NDEBUG
    public:
        void printNodeDebug(std::ostream& out) override;

        /**
         * Check if the OR inner node satisfies the smoothness property
         * Time complexity: linear with respect to the size of the (sub)circuit
         * Side effect: variable sets for nodes in the (sub)circuit are saved
         * @return true if the OR inner node is smooth. Otherwise, false is returned.
         */
        bool isSmoothDebug() const;
    #endif
    };
}   // namespace Hydra::Circuit::Node

#include "./OrInnerNode.ipp"
