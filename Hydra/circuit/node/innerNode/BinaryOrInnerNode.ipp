#pragma once

#include "./BinaryOrInnerNode.hpp"

namespace Hydra::Circuit::Node {

    template <typename VarT, typename LiteralT>
    typename BinaryOrInnerNode<VarT, LiteralT>::NumberOfModelsType
    BinaryOrInnerNode<VarT, LiteralT>::processModelCounting(const PartialAssignmentType& partialAssignment,
                                                            ModelCountingCacheType& cache) const {
        NumberOfModelsType result;   // 0

        for (ChildConstPtrType childPtr : this->children_) {
            childPtr->modelCounting(partialAssignment, cache);

            assert(Other::containInMap(cache, childPtr->getId()));

            result += cache[childPtr->getId()];
        }

        return result;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType BinaryOrInnerNode<VarT, LiteralT>::copySubcircuit(Circuit<VarT, LiteralT>* circuit, const MappingFromVariableToLiteralType& mapping,
                                                                 CopySubcircuitCacheType& cache, bool isVariableToLiteralMapping) {
        // The node has already been processed
        if (auto itTmp = cache.find(this->id_); itTmp != cache.end())
            return itTmp->second;

        #ifndef NDEBUG
        // The decision variable does not exist in the mapping
        if (!Other::containInMap(mapping, decisionVariable_)) {
            VariableSortedVectorType tmp = Other::extractKeysFromMap(mapping, true);
            std::stringstream stringStreamTmp = Other::createStringStreamFromContainerWithToStringConversion(tmp.cbegin(), tmp.cend());

            throw Exception::VariableDoesNotExistInMappingException(decisionVariable_, stringStreamTmp.str());
        }
        #endif

        const LiteralType& mappedDecisionLiteral = mapping.at(decisionVariable_);

        IdNodeType mappedHighChildId = this->children_[0]->copySubcircuit(circuit, mapping, cache, isVariableToLiteralMapping);
        IdNodeType mappedLowChildId = this->children_[1]->copySubcircuit(circuit, mapping, cache, isVariableToLiteralMapping);

        // The high child and the low child must be swapped
        if (mappedDecisionLiteral.isNegative())
            std::swap(mappedHighChildId, mappedLowChildId);

        IdNodeType mappedNodeId = circuit->createBinaryOrInnerNodeCopySubcircuit(mappedDecisionLiteral.getVariable(),
                                                                                 mappedHighChildId, mappedLowChildId);

        // Cache
        cache[this->id_] = mappedNodeId;

        return mappedNodeId;
    }

    template <typename VarT, typename LiteralT>
    void BinaryOrInnerNode<VarT, LiteralT>::printNode(std::ostream& out, [[maybe_unused]] const MappingFromVariableToOriginalVariableType& mapping) const {
        out << OR_INNER_NODE << " " << std::to_string(decisionVariable_) << " 2 "
            << std::to_string(this->children_[0]->getId()) << " "
            << std::to_string(this->children_[1]->getId()) << std::endl;
    }

    template <typename VarT, typename LiteralT>
    VarT BinaryOrInnerNode<VarT, LiteralT>::getDecisionVariable() const noexcept {
        return decisionVariable_;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    void BinaryOrInnerNode<VarT, LiteralT>::printNodeDebug(std::ostream& out) {
        out << "Binary OR inner node - ID: " << std::to_string(this->getId()) << " "
            << "Size: " << std::to_string(this->getSize()) << " "
            << "Decision variable: " << std::to_string(this->getDecisionVariable()) << " "
            << "High child (ID): " << std::to_string(this->children_[0]->getId()) << " "
            << "Low child (ID): " << std::to_string(this->children_[1]->getId()) << " "
            << "Is smooth: " << std::to_string(this->isSmoothDebug()) << " ";

        this->printVariablesInCircuitDebug(out);
        out << " ";
        this->printLiteralsInCircuitDebug(out);

        out << std::endl;
    }

    template <typename VarT, typename LiteralT>
    bool BinaryOrInnerNode<VarT, LiteralT>::checkDecisionVariableInCircuitDebug(bool throwException) {
        // The decision variable is not set
        if (decisionVariable_ == 0)
            return true;

        const LiteralSortedVectorType& child0LiteralSortedVector = this->children_[0]->getSortedLiteralsInCircuitDebug();
        const LiteralSortedVectorType& child1LiteralSortedVector = this->children_[1]->getSortedLiteralsInCircuitDebug();

        LiteralType posLit(decisionVariable_, true);
        LiteralType negLit(decisionVariable_, false);

        if (Other::containInSortedVector(child0LiteralSortedVector, posLit) &&
            Other::containInSortedVector(child1LiteralSortedVector, negLit))
            return true;

        if (Other::containInSortedVector(child0LiteralSortedVector, negLit) &&
            Other::containInSortedVector(child1LiteralSortedVector, posLit))
            return true;

        if (throwException)
            throw Exception::Circuit::Node::NodeException("The decision variable (" + std::to_string(decisionVariable_) + ") does not occur in the circuit!");

        return false;
    }
    #endif
}   // namespace Hydra::Circuit::Node
