#pragma once

#include "./LiteralLeaf.hpp"

namespace Hydra::Circuit::Node {

    template <typename VarT, typename LiteralT>
    void LiteralLeaf<VarT, LiteralT>::setUsedVariables(BoolVectorType& usedVariableVector, VarT& numberOfUsedVariables) const {
        VarT var = literal_.getVariable();

        assert(var < usedVariableVector.size());

        // New variable
        if (!usedVariableVector[var]) {
            ++numberOfUsedVariables;
            usedVariableVector[var] = true;
        }
    }

    template <typename VarT, typename LiteralT>
    bool LiteralLeaf<VarT, LiteralT>::processIsCircuitSmooth(MappingFromIdNodeToVariableSetType& mappingFromIdNodeToVariableSet) const {
        mappingFromIdNodeToVariableSet[this->id_] = VariableSetType { literal_.getVariable() };

        return true;
    }

    template <typename VarT, typename LiteralT>
    bool LiteralLeaf<VarT, LiteralT>::processConsistencyCheck(const PartialAssignmentType& partialAssignment,
                                                              const VariableSetType& forgottenVariableSet,
                                                              [[maybe_unused]] ConsistencyCheckCacheType& cache) {
        // Forgotten variable
        if (Other::containInSet(forgottenVariableSet, literal_.getVariable()))
            return true;

        // Satisfied
        if (partialAssignment.literalExists(literal_))
            return true;

        // Dissatisfied
        if (partialAssignment.complementaryLiteralExists(literal_))
            return false;

        return true;
    }

    template <typename VarT, typename LiteralT>
    typename LiteralLeaf<VarT, LiteralT>::NumberOfModelsType
    LiteralLeaf<VarT, LiteralT>::processModelCounting(const PartialAssignmentType& partialAssignment,
                                                      [[maybe_unused]] ModelCountingCacheType& cache) const {
        NumberOfModelsType tmp;   // 0

        // Satisfied
        if (partialAssignment.literalExists(literal_)) {
            ++tmp;   // 1
            return tmp;
        }

        // Unsatisfied
        if (partialAssignment.complementaryLiteralExists(literal_))
            return tmp;   // 0

        // Free variable
        ++tmp;
        return tmp;   // 1
    }

    template <typename VarT, typename LiteralT>
    IdNodeType LiteralLeaf<VarT, LiteralT>::copySubcircuit(Circuit<VarT, LiteralT>* circuit, const MappingFromVariableToLiteralType& mapping,
                                                           [[maybe_unused]] CopySubcircuitCacheType& cache, [[maybe_unused]] bool isVariableToLiteralMapping) {
        #ifndef NDEBUG
        VarT var = literal_.getVariable();

        // The variable does not exist in the mapping
        if (!Other::containInMap(mapping, var)) {
            VariableSortedVectorType tmp = Other::extractKeysFromMap(mapping, true);
            std::stringstream stringStreamTmp = Other::createStringStreamFromContainerWithToStringConversion(tmp.cbegin(), tmp.cend());

            throw Exception::VariableDoesNotExistInMappingException(var, stringStreamTmp.str());
        }
        #endif

        const LiteralType& mappedLiteral = mapping.at(literal_.getVariable());

        if (literal_.isPositive())
            return circuit->createLiteralLeaf(mappedLiteral);
        else
            return circuit->createLiteralLeaf(~mappedLiteral);
    }

    template <typename VarT, typename LiteralT>
    void LiteralLeaf<VarT, LiteralT>::printNode(std::ostream& out,
                                                const MappingFromVariableToOriginalVariableType& mapping) const {
        out << LITERAL_LEAF << " ";
        literal_.printLiteral(out, mapping);
        out << std::endl;
    }

    template <typename VarT, typename LiteralT>
    typename LiteralLeaf<VarT, LiteralT>::LiteralType
    LiteralLeaf<VarT, LiteralT>::getLiteral() const noexcept {
        return literal_;
    }

    template <typename VarT, typename LiteralT>
    typename LiteralLeaf<VarT, LiteralT>::LiteralType
    LiteralLeaf<VarT, LiteralT>::createMappedLiteral(const MappingFromVariableToLiteralType& mapping) const {
        #ifndef NDEBUG
        VarT var = literal_.getVariable();

        // The variable does not exist in the mapping
        if (!Other::containInMap(mapping, var)) {
            VariableSortedVectorType tmp = Other::extractKeysFromMap(mapping, true);
            std::stringstream stringStreamTmp = Other::createStringStreamFromContainerWithToStringConversion(tmp.cbegin(), tmp.cend());

            throw Exception::VariableDoesNotExistInMappingException(var, stringStreamTmp.str());
        }
        #endif

        const LiteralType& mappedLiteral = mapping.at(literal_.getVariable());
        bool sign = literal_.isPositive() ? mappedLiteral.isPositive() : !mappedLiteral.isPositive();

        return LiteralType(mappedLiteral.getVariable(), sign);
    }

    template <typename VarT, typename LiteralT>
    VarT LiteralLeaf<VarT, LiteralT>::getVariable() const noexcept {
        return literal_.getVariable();
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    typename LiteralLeaf<VarT, LiteralT>::LiteralSortedVectorType
    LiteralLeaf<VarT, LiteralT>::computeAndReturnSortedLiteralsInCircuitDebug() const {
        return { getLiteral() };
    }

    template <typename VarT, typename LiteralT>
    typename LiteralLeaf<VarT, LiteralT>::VariableSortedVectorType
    LiteralLeaf<VarT, LiteralT>::computeAndReturnSortedVariablesInCircuitDebug() const {
        return { getVariable() };
    }

    template <typename VarT, typename LiteralT>
    void LiteralLeaf<VarT, LiteralT>::printNodeDebug(std::ostream& out) {
        out << "Literal leaf - ID: " << std::to_string(this->getId()) << " "
            << "Size: " << std::to_string(this->getSize()) << " "
            << "Literal: " << this->getLiteral() << " "
            << "Variable: " << std::to_string(this->getVariable()) << std::endl;
    }
    #endif
}   // namespace Hydra::Circuit::Node
