#pragma once

#include <cassert>

#include "Hydra/circuit/node/NodeAbstract.hpp"
#include "Hydra/circuit/node/innerNode/InnerNodeAbstract.hpp"
#include "Hydra/formula/partialAssignment/PartialAssignment.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/circuit/node/enums/DecomposabilityTypeEnum.hpp"

#ifndef NDEBUG
    #include "Hydra/circuit/node/exceptions/NodeException.hpp"
    #include "Hydra/compiler/exceptions/CompilerException.hpp"
#endif

namespace Hydra::Circuit::Node {

    inline constexpr char AND_INNER_NODE_BELLA_DECOMPOSABILITY = 'B';
    inline constexpr char AND_INNER_NODE_POS_BELLA_DECOMPOSABILITY = 'P';
    inline constexpr char AND_INNER_NODE_NEG_BELLA_DECOMPOSABILITY = 'N';
    inline constexpr char AND_INNER_NODE_CLASSICAL_DECOMPOSABILITY = 'A';

    /**
     * AND inner node representation (final class)
     * Exceptions:
     *      UnexpectedArgumentException (debug)
     *      InnerNodeDoesNotSatisfyPropertyException (debug)
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class AndInnerNode final : public InnerNodeAbstract<VarT, LiteralT> {
    private:
        using LiteralType = typename NodeAbstract<VarT, LiteralT>::LiteralType;
        using ChildPtrType = typename NodeAbstract<VarT, LiteralT>::ChildPtrType;
        using VariableSetType = typename NodeAbstract<VarT, LiteralT>::VariableSetType;
        using IdNodeVectorType = typename NodeAbstract<VarT, LiteralT>::IdNodeVectorType;
        using ChildConstPtrType = typename NodeAbstract<VarT, LiteralT>::ChildConstPtrType;
        using NumberOfModelsType = typename NodeAbstract<VarT, LiteralT>::NumberOfModelsType;
        using ChildrenPtrVectorType = typename NodeAbstract<VarT, LiteralT>::ChildrenPtrVectorType;
        using PartialAssignmentType = typename NodeAbstract<VarT, LiteralT>::PartialAssignmentType;
        using ModelCountingCacheType = typename NodeAbstract<VarT, LiteralT>::ModelCountingCacheType;
        using LiteralSortedVectorType = typename NodeAbstract<VarT, LiteralT>::LiteralSortedVectorType;
        using CopySubcircuitCacheType = typename NodeAbstract<VarT, LiteralT>::CopySubcircuitCacheType;
        using VariableSortedVectorType = typename NodeAbstract<VarT, LiteralT>::VariableSortedVectorType;
        using ConsistencyCheckCacheType = typename NodeAbstract<VarT, LiteralT>::ConsistencyCheckCacheType;
        using MappingFromVariableToLiteralType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToLiteralType;
        using MappingFromIdNodeToVariableSetType = typename NodeAbstract<VarT, LiteralT>::MappingFromIdNodeToVariableSetType;
        using MappingFromVariableToOriginalVariableType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;

    public:
        AndInnerNode(IdNodeType id, const ChildrenPtrVectorType& childrenPtrVector, DecomposabilityTypeEnum decomposabilityType)
            : InnerNodeAbstract<VarT, LiteralT>(id, NodeTypeEnum::AND_INNER_NODE, childrenPtrVector),
              decomposabilityType_(decomposabilityType) {
            #ifndef NDEBUG
            checkDecomposabilityTypeDebug(true);
            #endif
        }

        AndInnerNode(IdNodeType id, ChildrenPtrVectorType&& childrenPtrVector, DecomposabilityTypeEnum decomposabilityType)
            : InnerNodeAbstract<VarT, LiteralT>(id, NodeTypeEnum::AND_INNER_NODE, std::move(childrenPtrVector)),
              decomposabilityType_(decomposabilityType) {
            #ifndef NDEBUG
            checkDecomposabilityTypeDebug(true);
            #endif
        }

    private:
        DecomposabilityTypeEnum decomposabilityType_;

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
    private:
        /**
         * Check if the particular type of decomposability (decomposabilityType_) is satisfied
         * @return true if the node satisfies the particular type of decomposability. Otherwise, false is returned.
         * @throw NotImplementedException if the checking method for the particular type of decomposability is not implemented
         * @throw InnerNodeDoesNotSatisfyPropertyException [throwException] if the particular type of decomposability is not satisfied
         */
        bool checkDecomposabilityTypeDebug(bool throwException = false);

    public:
        void printNodeDebug(std::ostream& out) override;

        /**
         * Check if the AND node satisfies the (classical) decomposability property
         * @return true if the AND node is (classically) decomposable. Otherwise, false is returned.
         */
        bool isClassicalDecomposabilitySatisfiedDebug() const;

        /**
         * Check if the AND node satisfies the (- / pos / neg) Bella decomposability property
         * @param decomposabilityVariant a variant of decomposability
         * @return true if the AND node is (- / pos / neg) Bella decomposable. Otherwise, false is returned.
         * @throw UnexpectedArgumentException if decomposabilityVariant is not the (- / pos / neg) Bella decomposability property
         */
        bool isBellaDecomposabilitySatisfiedDebug(DecomposabilityTypeEnum decomposabilityVariant) const;
    #endif
    };
}   // namespace Hydra::Circuit::Node

#include "./AndInnerNode.ipp"
