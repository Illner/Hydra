#pragma once

#include <cassert>

#include "Hydra/circuit/node/NodeAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#ifndef NDEBUG
    #include <algorithm>

    #include "Hydra/formula/Literal.hpp"
#endif

namespace Hydra::Circuit::Node {

    /**
     * Inner node representation (abstract class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class InnerNodeAbstract : public NodeAbstract<VarT, LiteralT> {
    private:
        using LiteralType = typename NodeAbstract<VarT, LiteralT>::LiteralType;
        using ChildPtrType = typename NodeAbstract<VarT, LiteralT>::ChildPtrType;
        using LiteralSetType = typename NodeAbstract<VarT, LiteralT>::LiteralSetType;
        using VariableSetType = typename NodeAbstract<VarT, LiteralT>::VariableSetType;
        using ChildConstPtrType = typename NodeAbstract<VarT, LiteralT>::ChildConstPtrType;
        using ChildrenPtrVectorType = typename NodeAbstract<VarT, LiteralT>::ChildrenPtrVectorType;
        using LiteralSortedVectorType = typename NodeAbstract<VarT, LiteralT>::LiteralSortedVectorType;
        using VariableSortedVectorType = typename NodeAbstract<VarT, LiteralT>::VariableSortedVectorType;

    public:
        InnerNodeAbstract(IdNodeType id, NodeTypeEnum nodeType, const ChildrenPtrVectorType& childrenPtrVector, SizeNodeType size)
            : NodeAbstract<VarT, LiteralT>(id, nodeType, size), children_(childrenPtrVector) {
            assert(!children_.empty());   // at least one child

            children_.shrink_to_fit();
        }

        InnerNodeAbstract(IdNodeType id, NodeTypeEnum nodeType, const ChildrenPtrVectorType& childrenPtrVector)
            : NodeAbstract<VarT, LiteralT>(id, nodeType, static_cast<SizeNodeType>(childrenPtrVector.size())), children_(childrenPtrVector) {
            assert(!children_.empty());   // at least one child

            children_.shrink_to_fit();
        }

        InnerNodeAbstract(IdNodeType id, NodeTypeEnum nodeType, ChildrenPtrVectorType&& childrenPtrVector, SizeNodeType size)
            : NodeAbstract<VarT, LiteralT>(id, nodeType, size), children_(std::move(childrenPtrVector)) {
            assert(!children_.empty());   // at least one child

            children_.shrink_to_fit();
        }

        InnerNodeAbstract(IdNodeType id, NodeTypeEnum nodeType, ChildrenPtrVectorType&& childrenPtrVector)
            : NodeAbstract<VarT, LiteralT>(id, nodeType, static_cast<SizeNodeType>(childrenPtrVector.size())), children_(std::move(childrenPtrVector)) {
            assert(!children_.empty());   // at least one child

            children_.shrink_to_fit();
        }

    protected:
        ChildrenPtrVectorType children_;

    public:
        /**
         * @return the number of children
         */
        SizeNodeType getNumberOfChildren() const noexcept;

    #ifndef NDEBUG
    private:
        mutable bool d_sortedChildren_ = false;

    protected:
        /**
         * Sort the children
         */
        void sortChildrenDebug();

        /**
         * Print the children's identifiers
         * Note: prefix
         */
        void printChildrenDebug(std::ostream& out);

        LiteralSortedVectorType computeAndReturnSortedLiteralsInCircuitDebug() const override;

        VariableSortedVectorType computeAndReturnSortedVariablesInCircuitDebug() const override;

    public:
        /**
         * For each child print its variables
         */
        void printChildrenVariablesDebug(std::ostream& out);

        /**
         * For each child print its literals
         */
        void printChildrenLiteralsDebug(std::ostream& out);
    #endif
    };
}   // namespace Hydra::Circuit::Node

#include "./InnerNodeAbstract.ipp"
