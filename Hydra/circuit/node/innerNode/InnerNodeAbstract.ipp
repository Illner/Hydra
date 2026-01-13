#pragma once

#include "./InnerNodeAbstract.hpp"

namespace Hydra::Circuit::Node {

    template <typename VarT, typename LiteralT>
    SizeNodeType InnerNodeAbstract<VarT, LiteralT>::getNumberOfChildren() const noexcept {
        return static_cast<SizeNodeType>(children_.size());
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    void InnerNodeAbstract<VarT, LiteralT>::sortChildrenDebug() {
        // Children are already sorted
        if (d_sortedChildren_)
            return;

        std::sort(children_.begin(), children_.end(),
                  [](ChildPtrType a, ChildPtrType b) -> bool { return a->getId() < b->getId(); });
        d_sortedChildren_ = true;
    }

    template <typename VarT, typename LiteralT>
    void InnerNodeAbstract<VarT, LiteralT>::printChildrenDebug(std::ostream& out) {
        sortChildrenDebug();   // deterministic output

        out << "Children (IDs):";
        for (ChildConstPtrType childPtr : children_)
            out << " " << std::to_string(childPtr->getId());
    }

    template <typename VarT, typename LiteralT>
    typename InnerNodeAbstract<VarT, LiteralT>::LiteralSortedVectorType
    InnerNodeAbstract<VarT, LiteralT>::computeAndReturnSortedLiteralsInCircuitDebug() const {
        LiteralSetType literalInCircuitSet;

        for (ChildConstPtrType childPtr : children_)
            childPtr->insertLiteralsInCircuitToSetDebug(literalInCircuitSet);

        LiteralSortedVectorType literalInCircuitSortedVector = Other::sortUnorderedSet(literalInCircuitSet);
        return literalInCircuitSortedVector;
    }

    template <typename VarT, typename LiteralT>
    typename InnerNodeAbstract<VarT, LiteralT>::VariableSortedVectorType
    InnerNodeAbstract<VarT, LiteralT>::computeAndReturnSortedVariablesInCircuitDebug() const {
        VariableSetType variableInCircuitSet;

        for (ChildConstPtrType childPtr : children_)
            childPtr->insertVariablesInCircuitToSetDebug(variableInCircuitSet);

        VariableSortedVectorType variableInCircuitSortedVector = Other::sortUnorderedSet(variableInCircuitSet);
        return variableInCircuitSortedVector;
    }

    template <typename VarT, typename LiteralT>
    void InnerNodeAbstract<VarT, LiteralT>::printChildrenVariablesDebug(std::ostream& out) {
        sortChildrenDebug();   // deterministic output

        SizeNodeType i = 0;
        for (ChildConstPtrType childPtr : children_) {
            out << "child" << std::to_string(++i) << ":";

            VariableSortedVectorType variableSortedVectorTmp = childPtr->getSortedVariablesInCircuitDebug();
            for (VarT var : variableSortedVectorTmp)
                out << " " << std::to_string(var);

            out << std::endl;
        }
    }

    template <typename VarT, typename LiteralT>
    void InnerNodeAbstract<VarT, LiteralT>::printChildrenLiteralsDebug(std::ostream& out) {
        sortChildrenDebug();   // deterministic output

        SizeNodeType i = 0;
        for (ChildConstPtrType childPtr : children_) {
            out << "child" << std::to_string(++i) << ":";

            LiteralSortedVectorType literalSortedVectorTmp = childPtr->getSortedLiteralsInCircuitDebug();
            for (const LiteralType& lit : literalSortedVectorTmp)
                out << " " << lit;

            out << std::endl;
        }
    }
    #endif
}   // namespace Hydra::Circuit::Node
