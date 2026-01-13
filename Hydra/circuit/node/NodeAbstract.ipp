#pragma once

#include "./NodeAbstract.hpp"

namespace Hydra::Circuit::Node {

    template <typename VarT, typename LiteralT>
    IdNodeType NodeAbstract<VarT, LiteralT>::getId() const noexcept {
        return id_;
    }

    template <typename VarT, typename LiteralT>
    SizeNodeType NodeAbstract<VarT, LiteralT>::getSize() const noexcept {
        return size_;
    }

    template <typename VarT, typename LiteralT>
    NodeTypeEnum NodeAbstract<VarT, LiteralT>::getNodeType() const noexcept {
        return nodeType_;
    }

    template <typename VarT, typename LiteralT>
    bool NodeAbstract<VarT, LiteralT>::isCircuitSmooth(IdNodeType numberOfNodes) const {
        MappingFromIdNodeToVariableSetType mappingFromIdNodeToVariableSet(numberOfNodes);

        return isCircuitSmooth(mappingFromIdNodeToVariableSet);
    }

    template <typename VarT, typename LiteralT>
    bool NodeAbstract<VarT, LiteralT>::isCircuitSmooth(MappingFromIdNodeToVariableSetType& mappingFromIdNodeToVariableSet) const {
        // The node has already been processed
        if (Other::containInMap(mappingFromIdNodeToVariableSet, id_))
            return true;

        if (!processIsCircuitSmooth(mappingFromIdNodeToVariableSet))
            return false;

        assert(Other::containInMap(mappingFromIdNodeToVariableSet, id_));   // node has been processed

        return true;
    }

    template <typename VarT, typename LiteralT>
    bool NodeAbstract<VarT, LiteralT>::consistencyCheck(const PartialAssignmentType& partialAssignment,
                                                        const VariableSetType& forgottenVariableSet,
                                                        ConsistencyCheckCacheType& cache) {
        // The node has already been processed
        if (auto itTmp = cache.find(id_); itTmp != cache.end())
            return itTmp->second;

        bool result = processConsistencyCheck(partialAssignment, forgottenVariableSet, cache);

        // Update the cache
        cache[id_] = result;

        return result;
    }

    template <typename VarT, typename LiteralT>
    void NodeAbstract<VarT, LiteralT>::modelCounting(const PartialAssignmentType& partialAssignment,
                                                     ModelCountingCacheType& cache) const {
        // The node has already been processed
        if (auto itTmp = cache.find(id_); itTmp != cache.end())
            return;

        NumberOfModelsType result = processModelCounting(partialAssignment, cache);

        // Update the cache
        cache[id_] = std::move(result);
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    void NodeAbstract<VarT, LiteralT>::printLiteralsInCircuitDebug(std::ostream& out) const {
        out << "Literals in circuit: ";
        for (const LiteralType& lit : getSortedLiteralsInCircuitDebug())
            out << lit << " ";
    }

    template <typename VarT, typename LiteralT>
    void NodeAbstract<VarT, LiteralT>::printVariablesInCircuitDebug(std::ostream& out) const {
        out << "Variables in circuit: ";
        for (VarT var : getSortedVariablesInCircuitDebug())
            out << std::to_string(var) << " ";
    }

    template <typename VarT, typename LiteralT>
    void NodeAbstract<VarT, LiteralT>::printNodeDebug(std::ostream& out) {
        out << "Node - ID: " << std::to_string(this->getId()) << " "
            << "Size: " << std::to_string(this->getSize()) << " ";

        printVariablesInCircuitDebug(out);
        out << " ";
        printLiteralsInCircuitDebug(out);

        out << std::endl;
    }

    template <typename VarT, typename LiteralT>
    const typename NodeAbstract<VarT, LiteralT>::LiteralSortedVectorType&
    NodeAbstract<VarT, LiteralT>::getSortedLiteralsInCircuitDebug() const {
        // Not initialized
        if (!d_sortedLiteralsInCircuit_.has_value())
            d_sortedLiteralsInCircuit_ = computeAndReturnSortedLiteralsInCircuitDebug();

        return *d_sortedLiteralsInCircuit_;
    }

    template <typename VarT, typename LiteralT>
    const typename NodeAbstract<VarT, LiteralT>::VariableSortedVectorType&
    NodeAbstract<VarT, LiteralT>::getSortedVariablesInCircuitDebug() const {
        // Not initialized
        if (!d_sortedVariablesInCircuit_.has_value())
            d_sortedVariablesInCircuit_ = computeAndReturnSortedVariablesInCircuitDebug();

        return *d_sortedVariablesInCircuit_;
    }

    template <typename VarT, typename LiteralT>
    void NodeAbstract<VarT, LiteralT>::insertLiteralsInCircuitToSetDebug(LiteralSetType& literalsInCircuit) const {
        for (const LiteralType& lit : getSortedLiteralsInCircuitDebug())
            literalsInCircuit.emplace(lit.getVariable(), lit.isPositive());
    }

    template <typename VarT, typename LiteralT>
    void NodeAbstract<VarT, LiteralT>::insertVariablesInCircuitToSetDebug(VariableSetType& variablesInCircuit) const {
        for (VarT var : getSortedVariablesInCircuitDebug())
            variablesInCircuit.emplace(var);
    }
    #endif
}   // namespace Hydra::Circuit::Node
