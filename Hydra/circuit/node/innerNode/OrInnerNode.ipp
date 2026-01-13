#pragma once

#include "./OrInnerNode.hpp"

namespace Hydra::Circuit::Node {

    template <typename VarT, typename LiteralT>
    bool OrInnerNode<VarT, LiteralT>::processIsCircuitSmooth(MappingFromIdNodeToVariableSetType& mappingFromIdNodeToVariableSet) const {
        VariableSetType variableSet;

        for (ChildConstPtrType childPtr : this->children_) {
            bool isSmooth = childPtr->isCircuitSmooth(mappingFromIdNodeToVariableSet);

            if (!isSmooth)
                return false;

            // Update the variable set
            for (VarT var : mappingFromIdNodeToVariableSet[childPtr->getId()]) {
                if (!Other::containInSet(variableSet, var))
                    variableSet.emplace(var);
            }
        }

        assert(!this->children_.empty());   // at least one child

        const VariableSetType& child0VariableSet = mappingFromIdNodeToVariableSet[this->children_[0]->getId()];

        for (SizeNodeType i = 1; i < this->children_.size(); ++i) {
            const VariableSetType& childVariableSet = mappingFromIdNodeToVariableSet[this->children_[i]->getId()];

            // Not smooth
            if (child0VariableSet != childVariableSet)
                return false;
        }

        mappingFromIdNodeToVariableSet[this->id_] = std::move(variableSet);

        return true;
    }

    template <typename VarT, typename LiteralT>
    bool OrInnerNode<VarT, LiteralT>::processConsistencyCheck(const PartialAssignmentType& partialAssignment,
                                                              const VariableSetType& forgottenVariableSet,
                                                              ConsistencyCheckCacheType& cache) {
        for (ChildPtrType childPtr : this->children_) {
            if (childPtr->consistencyCheck(partialAssignment, forgottenVariableSet, cache))
                return true;
        }

        return false;
    }

    template <typename VarT, typename LiteralT>
    typename OrInnerNode<VarT, LiteralT>::NumberOfModelsType
    OrInnerNode<VarT, LiteralT>::processModelCounting([[maybe_unused]] const PartialAssignmentType& partialAssignment,
                                                      [[maybe_unused]] ModelCountingCacheType& cache) const {
        // (classical) OR nodes do not support model counting
        throw Exception::Circuit::Node::OrInnerNodesDoNotSupportModelCountingException();
    }

    template <typename VarT, typename LiteralT>
    IdNodeType OrInnerNode<VarT, LiteralT>::copySubcircuit(Circuit<VarT, LiteralT>* circuit, const MappingFromVariableToLiteralType& mapping,
                                                           CopySubcircuitCacheType& cache, [[maybe_unused]] bool isVariableToLiteralMapping) {
        // The node has already been processed
        if (auto itTmp = cache.find(this->id_); itTmp != cache.end())
            return itTmp->second;

        LiteralVectorType childrenLiteralVector;
        childrenLiteralVector.reserve(this->children_.size());

        for (ChildConstPtrType childPtr : this->children_) {
            #ifndef NDEBUG
            const LiteralLeafType* literalLeafPtr = dynamic_cast<const LiteralLeafType*>(childPtr);
            #else
            const LiteralLeafType* literalLeafPtr = static_cast<const LiteralLeafType*>(childPtr);
            #endif

            childrenLiteralVector.push_back(std::move(literalLeafPtr->createMappedLiteral(mapping)));
        }

        IdNodeType mappedNodeId = circuit->createOrInnerNode(childrenLiteralVector);

        // Cache
        cache[this->id_] = mappedNodeId;

        return mappedNodeId;
    }

    template <typename VarT, typename LiteralT>
    void OrInnerNode<VarT, LiteralT>::printNode(std::ostream& out, [[maybe_unused]] const MappingFromVariableToOriginalVariableType& mapping) const {
        out << OR_INNER_NODE << " 0 " << std::to_string(this->getNumberOfChildren());

        for (ChildConstPtrType childPtr : this->children_)
            out << " " << std::to_string(childPtr->getId());

        out << std::endl;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    void OrInnerNode<VarT, LiteralT>::printNodeDebug(std::ostream& out) {
        out << "OR inner node - ID: " << std::to_string(this->getId()) << " "
            << "Size: " << std::to_string(this->getSize()) << " "
            << "Is smooth: " << std::to_string(isSmoothDebug()) << " ";

        this->printChildrenDebug(out);
        out << " ";
        this->printVariablesInCircuitDebug(out);
        out << " ";
        this->printLiteralsInCircuitDebug(out);

        out << std::endl;
    }

    template <typename VarT, typename LiteralT>
    bool OrInnerNode<VarT, LiteralT>::isSmoothDebug() const {
        assert(!this->children_.empty());   // at least one child

        const VariableSortedVectorType& child0VariableSortedVector = this->children_[0]->getSortedVariablesInCircuitDebug();

        for (SizeNodeType i = 1; i < this->children_.size(); ++i) {
            const VariableSortedVectorType& childVariableSortedVector = this->children_[i]->getSortedVariablesInCircuitDebug();

            // Not smooth
            if (child0VariableSortedVector != childVariableSortedVector)
                return false;
        }

        return true;
    }
    #endif
}   // namespace Hydra::Circuit::Node
