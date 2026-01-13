#pragma once

#include "./ConstantLeaf.hpp"

namespace Hydra::Circuit::Node {

    template <typename VarT, typename LiteralT>
    void ConstantLeaf<VarT, LiteralT>::setUsedVariables([[maybe_unused]] BoolVectorType& usedVariableVector,
                                                        [[maybe_unused]] VarT& numberOfUsedVariables) const { }

    template <typename VarT, typename LiteralT>
    bool ConstantLeaf<VarT, LiteralT>::processIsCircuitSmooth(MappingFromIdNodeToVariableSetType& mappingFromIdNodeToVariableSet) const {
        mappingFromIdNodeToVariableSet[this->id_] = VariableSetType {};

        return true;
    }

    template <typename VarT, typename LiteralT>
    bool ConstantLeaf<VarT, LiteralT>::processConsistencyCheck([[maybe_unused]] const PartialAssignmentType& partialAssignment,
                                                               [[maybe_unused]] const VariableSetType& forgottenVariableSet,
                                                               [[maybe_unused]] ConsistencyCheckCacheType& cache) {
        return constant_;
    }

    template <typename VarT, typename LiteralT>
    typename ConstantLeaf<VarT, LiteralT>::NumberOfModelsType
    ConstantLeaf<VarT, LiteralT>::processModelCounting([[maybe_unused]] const PartialAssignmentType& partialAssignment,
                                                       [[maybe_unused]] ModelCountingCacheType& cache) const {
        NumberOfModelsType tmp;   // 0

        if (constant_)
            ++tmp;   // 1

        return tmp;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType ConstantLeaf<VarT, LiteralT>::copySubcircuit([[maybe_unused]] Circuit<VarT, LiteralT>* circuit,
                                                            [[maybe_unused]] const MappingFromVariableToLiteralType& mapping,
                                                            [[maybe_unused]] CopySubcircuitCacheType& cache,
                                                            [[maybe_unused]] bool isVariableToLiteralMapping) {
        return this->id_;
    }

    template <typename VarT, typename LiteralT>
    void ConstantLeaf<VarT, LiteralT>::printNode(std::ostream& out,
                                                 [[maybe_unused]] const MappingFromVariableToOriginalVariableType& mapping) const {
        // TRUE leaf
        if (constant_)
            out << AND_INNER_NODE_CLASSICAL_DECOMPOSABILITY << " 0" << std::endl;
        // FALSE leaf
        else
            out << OR_INNER_NODE << " 0 0" << std::endl;
    }

    template <typename VarT, typename LiteralT>
    bool ConstantLeaf<VarT, LiteralT>::getConstant() const noexcept {
        return constant_;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    typename ConstantLeaf<VarT, LiteralT>::LiteralSortedVectorType
    ConstantLeaf<VarT, LiteralT>::computeAndReturnSortedLiteralsInCircuitDebug() const {
        return {};
    }

    template <typename VarT, typename LiteralT>
    typename ConstantLeaf<VarT, LiteralT>::VariableSortedVectorType
    ConstantLeaf<VarT, LiteralT>::computeAndReturnSortedVariablesInCircuitDebug() const {
        return {};
    }

    template <typename VarT, typename LiteralT>
    void ConstantLeaf<VarT, LiteralT>::printNodeDebug(std::ostream& out) {
        out << "Constant leaf - ID: " << std::to_string(this->getId()) << " "
            << "Size: " << std::to_string(this->getSize()) << " "
            << "Constant: " << std::to_string(this->getConstant()) << std::endl;
    }
    #endif
}   // namespace Hydra::Circuit::Node
