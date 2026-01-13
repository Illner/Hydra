#pragma once

#include <algorithm>
#include <cassert>

#include "Hydra/circuit/node/NodeAbstract.hpp"
#include "Hydra/circuit/node/innerNode/OrInnerNode.hpp"
#include "Hydra/other/Other.hpp"

#ifndef NDEBUG
    #include <sstream>

    #include "Hydra/circuit/node/exceptions/NodeException.hpp"
    #include "Hydra/compiler/exceptions/CompilerException.hpp"
#endif

namespace Hydra::Circuit::Node {

    /**
     * Binary OR inner node representation (final class)
     * High child (index 0), low child (index 1)
     * Exceptions:
     *      NodeException (debug)
     *      VariableDoesNotExistInMappingException (debug)
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class BinaryOrInnerNode final : public OrInnerNode<VarT, LiteralT> {
    private:
        using LiteralType = typename NodeAbstract<VarT, LiteralT>::LiteralType;
        using ChildPtrType = typename NodeAbstract<VarT, LiteralT>::ChildPtrType;
        using ChildConstPtrType = typename NodeAbstract<VarT, LiteralT>::ChildConstPtrType;
        using NumberOfModelsType = typename NodeAbstract<VarT, LiteralT>::NumberOfModelsType;
        using ChildrenPtrVectorType = typename NodeAbstract<VarT, LiteralT>::ChildrenPtrVectorType;
        using PartialAssignmentType = typename NodeAbstract<VarT, LiteralT>::PartialAssignmentType;
        using ModelCountingCacheType = typename NodeAbstract<VarT, LiteralT>::ModelCountingCacheType;
        using LiteralSortedVectorType = typename NodeAbstract<VarT, LiteralT>::LiteralSortedVectorType;
        using CopySubcircuitCacheType = typename NodeAbstract<VarT, LiteralT>::CopySubcircuitCacheType;
        using VariableSortedVectorType = typename NodeAbstract<VarT, LiteralT>::VariableSortedVectorType;
        using MappingFromVariableToLiteralType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToLiteralType;
        using MappingFromVariableToOriginalVariableType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;

    public:
        BinaryOrInnerNode(IdNodeType id, ChildPtrType highChildPtr, ChildPtrType lowChildPtr, VarT decisionVariable = 0)
            : OrInnerNode<VarT, LiteralT>(id, ChildrenPtrVectorType { highChildPtr, lowChildPtr }, NodeTypeEnum::BINARY_OR_INNER_NODE),
              decisionVariable_(decisionVariable) {
            #ifndef NDEBUG
            checkDecisionVariableInCircuitDebug(true);
            #endif
        }

    private:
        VarT decisionVariable_;   // 0 = decision variable is not set

    private:
        NumberOfModelsType processModelCounting(const PartialAssignmentType& partialAssignment,
                                                ModelCountingCacheType& cache) const override;

        IdNodeType copySubcircuit(Circuit<VarT, LiteralT>* circuit, const MappingFromVariableToLiteralType& mapping,
                                  CopySubcircuitCacheType& cache, bool isVariableToLiteralMapping) override;

    public:
        void printNode(std::ostream& out, const MappingFromVariableToOriginalVariableType& mapping) const override;

        /**
         * Getter
         * @return the decision variable (0 if the decision variable is not set)
         */
        VarT getDecisionVariable() const noexcept;

    #ifndef NDEBUG
    public:
        void printNodeDebug(std::ostream& out) override;

        /**
         * Check if the decision variable is presented in both (sub)circuits
         * Note: no complete
         * @return true if the decision variable is presented in both children's (sub)circuits. Otherwise, false is returned.
         * @throw NodeException [throwException] if one of the children does not contain the decision variable
         */
        bool checkDecisionVariableInCircuitDebug(bool throwException = false);
    #endif
    };
}   // namespace Hydra::Circuit::Node

#include "./BinaryOrInnerNode.ipp"
