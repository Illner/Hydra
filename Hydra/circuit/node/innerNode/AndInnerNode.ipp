#pragma once

#include "./AndInnerNode.hpp"

namespace Hydra::Circuit::Node {

    template <typename VarT, typename LiteralT>
    bool AndInnerNode<VarT, LiteralT>::processIsCircuitSmooth(MappingFromIdNodeToVariableSetType& mappingFromIdNodeToVariableSet) const {
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

        mappingFromIdNodeToVariableSet[this->id_] = std::move(variableSet);

        return true;
    }

    template <typename VarT, typename LiteralT>
    bool AndInnerNode<VarT, LiteralT>::processConsistencyCheck(const PartialAssignmentType& partialAssignment,
                                                               const VariableSetType& forgottenVariableSet,
                                                               ConsistencyCheckCacheType& cache) {
        assert(Other::containInSet(supportConsistencyCheckDecomposabilityTypeSet, decomposabilityType_));

        for (ChildPtrType childPtr : this->children_) {
            if (!childPtr->consistencyCheck(partialAssignment, forgottenVariableSet, cache))
                return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT>
    typename AndInnerNode<VarT, LiteralT>::NumberOfModelsType
    AndInnerNode<VarT, LiteralT>::processModelCounting(const PartialAssignmentType& partialAssignment,
                                                       ModelCountingCacheType& cache) const {
        assert(Other::containInSet(supportModelCountingDecomposabilityTypeSet, decomposabilityType_));

        NumberOfModelsType result;
        ++result;   // 1

        for (ChildConstPtrType childPtr : this->children_) {
            childPtr->modelCounting(partialAssignment, cache);

            assert(Other::containInMap(cache, childPtr->getId()));

            result *= cache[childPtr->getId()];
        }

        return result;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType AndInnerNode<VarT, LiteralT>::copySubcircuit(Circuit<VarT, LiteralT>* circuit, const MappingFromVariableToLiteralType& mapping,
                                                            CopySubcircuitCacheType& cache, bool isVariableToLiteralMapping) {
        // The node has already been processed
        if (auto itTmp = cache.find(this->id_); itTmp != cache.end())
            return itTmp->second;

        IdNodeVectorType childrenVector;
        childrenVector.reserve(this->children_.size());

        for (ChildPtrType childPtr : this->children_)
            childrenVector.emplace_back(childPtr->copySubcircuit(circuit, mapping, cache, isVariableToLiteralMapping));

        DecomposabilityTypeEnum newDecomposabilityType = decomposabilityType_;

        // (pos / neg) Bella decomposability and a variable to literal mapping -> Bella decomposability
        if (isVariableToLiteralMapping &&
            (decomposabilityType_ == DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY || decomposabilityType_ == DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY))
            newDecomposabilityType = DecomposabilityTypeEnum::BELLA_DECOMPOSABILITY;

        IdNodeType mappedNodeId = circuit->createAndInnerNode(childrenVector, newDecomposabilityType);

        // Cache
        cache[this->id_] = mappedNodeId;

        return mappedNodeId;
    }

    template <typename VarT, typename LiteralT>
    void AndInnerNode<VarT, LiteralT>::printNode(std::ostream& out, [[maybe_unused]] const MappingFromVariableToOriginalVariableType& mapping) const {
        switch (decomposabilityType_) {
            case DecomposabilityTypeEnum::BELLA_DECOMPOSABILITY:
                out << AND_INNER_NODE_BELLA_DECOMPOSABILITY << " ";
                break;
            case DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY:
                out << AND_INNER_NODE_POS_BELLA_DECOMPOSABILITY << " ";
                break;
            case DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY:
                out << AND_INNER_NODE_NEG_BELLA_DECOMPOSABILITY << " ";
                break;
            default:
                out << AND_INNER_NODE_CLASSICAL_DECOMPOSABILITY << " ";
        }

        out << std::to_string(this->getNumberOfChildren());

        for (ChildConstPtrType childPtr : this->children_)
            out << " " << std::to_string(childPtr->getId());

        out << std::endl;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    bool AndInnerNode<VarT, LiteralT>::checkDecomposabilityTypeDebug(bool throwException) {
        // None
        if (decomposabilityType_ == DecomposabilityTypeEnum::NONE)
            return true;

        // (- / pos / neg) Bella decomposability
        else if (Other::containInSet(bellaDecomposabilityTypeSet, decomposabilityType_)) {
            if (!isBellaDecomposabilitySatisfiedDebug(decomposabilityType_)) {
                if (throwException)
                    throw Exception::Circuit::Node::InnerNodeDoesNotSatisfyPropertyException(decomposabilityTypeEnumToString(decomposabilityType_),
                                                                                             this, false, true);

                return false;
            }

            return true;
        }

        // (Classical) decomposability
        else if (decomposabilityType_ == DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY) {
            if (!isClassicalDecomposabilitySatisfiedDebug()) {
                if (throwException)
                    throw Exception::Circuit::Node::InnerNodeDoesNotSatisfyPropertyException(decomposabilityTypeEnumToString(decomposabilityType_),
                                                                                             this, true, false);

                return false;
            }

            return true;
        }

        // Not implemented
        throw Exception::NotImplementedException(decomposabilityTypeEnumToString(decomposabilityType_),
                                                 "Hydra::Circuit::Node::AndInnerNode::checkDecomposabilityTypeDebug");
    }

    template <typename VarT, typename LiteralT>
    void AndInnerNode<VarT, LiteralT>::printNodeDebug(std::ostream& out) {
        out << "AND inner node - ID: " << std::to_string(this->getId()) << " "
            << "Size: " << std::to_string(this->getSize()) << " "
            << "Is (classically) decomposable: " << std::to_string(isClassicalDecomposabilitySatisfiedDebug()) << " "
            << "Is Bella decomposable: " << std::to_string(isBellaDecomposabilitySatisfiedDebug(DecomposabilityTypeEnum::BELLA_DECOMPOSABILITY)) << " "
            << "Is posBella decomposable: " << std::to_string(isBellaDecomposabilitySatisfiedDebug(DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY)) << " "
            << "Is negBella decomposable: " << std::to_string(isBellaDecomposabilitySatisfiedDebug(DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY)) << " ";

        this->printChildrenDebug(out);
        out << " ";
        this->printVariablesInCircuitDebug(out);
        out << " ";
        this->printLiteralsInCircuitDebug(out);

        out << std::endl;
    }

    template <typename VarT, typename LiteralT>
    bool AndInnerNode<VarT, LiteralT>::isClassicalDecomposabilitySatisfiedDebug() const {
        SizeNodeType numberOfChildren = this->getNumberOfChildren();

        for (SizeNodeType i = 0; i < numberOfChildren - 1; ++i) {
            ChildPtrType childPtr0 = this->children_[i];

            for (SizeNodeType j = i + 1; j < numberOfChildren; ++j) {
                ChildPtrType childPtr1 = this->children_[j];

                // Not (classically) decomposable
                if (!Other::emptyIntersectionSortedVectors(childPtr0->getSortedVariablesInCircuitDebug(),
                                                           childPtr1->getSortedVariablesInCircuitDebug())) {
                    return false;
                }
            }
        }

        return true;
    }

    template <typename VarT, typename LiteralT>
    bool AndInnerNode<VarT, LiteralT>::isBellaDecomposabilitySatisfiedDebug(DecomposabilityTypeEnum decomposabilityVariant) const {
        // Invalid argument
        if (!Other::containInSet(bellaDecomposabilityTypeSet, decomposabilityVariant))
            throw Exception::UnexpectedArgumentException(decomposabilityTypeEnumToString(decomposabilityVariant),
                                                         "isBellaDecomposabilitySatisfiedDebug");

        SizeNodeType numberOfChildren = this->getNumberOfChildren();

        for (SizeNodeType i = 0; i < numberOfChildren - 1; ++i) {
            ChildPtrType childPtr0 = this->children_[i];
            const VariableSortedVectorType& child0VariableSortedVector = childPtr0->getSortedVariablesInCircuitDebug();

            for (SizeNodeType j = i + 1; j < numberOfChildren; ++j) {
                ChildPtrType childPtr1 = this->children_[j];
                const VariableSortedVectorType& child1VariableSortedVector = childPtr1->getSortedVariablesInCircuitDebug();

                auto child0Iterator = child0VariableSortedVector.cbegin();
                auto child1Iterator = child1VariableSortedVector.cbegin();

                while (child0Iterator != child0VariableSortedVector.cend() &&
                       child1Iterator != child1VariableSortedVector.cend()) {
                    if (*child0Iterator < *child1Iterator) {
                        ++child0Iterator;
                        continue;
                    }

                    if (*child0Iterator > *child1Iterator) {
                        ++child1Iterator;
                        continue;
                    }

                    // Shared variable
                    VarT varTmp = (*child0Iterator);
                    LiteralType posLitTmp(varTmp, true);
                    LiteralType negLitTmp(varTmp, false);

                    const LiteralSortedVectorType& child0LiteralSortedVector = childPtr0->getSortedLiteralsInCircuitDebug();
                    const LiteralSortedVectorType& child1LiteralSortedVector = childPtr1->getSortedLiteralsInCircuitDebug();

                    if ((Other::containInSortedVector(child0LiteralSortedVector, posLitTmp) && Other::containInSortedVector(child1LiteralSortedVector, negLitTmp)) ||
                        (Other::containInSortedVector(child0LiteralSortedVector, negLitTmp) && Other::containInSortedVector(child1LiteralSortedVector, posLitTmp))) {
                        return false;
                    }
                    // Pure literal
                    else {
                        switch (decomposabilityVariant) {
                            case DecomposabilityTypeEnum::BELLA_DECOMPOSABILITY:
                                break;
                            case DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY:
                                if (Other::containInSortedVector(child0LiteralSortedVector, negLitTmp))
                                    return false;
                                break;
                            case DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY:
                                if (Other::containInSortedVector(child0LiteralSortedVector, posLitTmp))
                                    return false;
                                break;
                            default:
                                throw Exception::NotImplementedException(decomposabilityTypeEnumToString(decomposabilityVariant),
                                                                         "Hydra::Circuit::Node::AndInnerNode::isBellaDecomposabilitySatisfiedDebug");
                        }

                        ++child0Iterator;
                        ++child1Iterator;
                    }
                }
            }
        }

        return true;
    }
    #endif
}   // namespace Hydra::Circuit::Node
