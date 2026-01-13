#pragma once

#include "./ComputeConnectedComponents.hpp"

namespace Hydra::Container::ComputeConnectedComponents {

    template <typename VarT, typename LiteralT>
    VarT ComputeConnectedComponents<VarT, LiteralT>::find(VarT var) noexcept {
        // Find the root
        VarT root = var;
        while (subsetVector_[root].parent != root)
            root = subsetVector_[root].parent;

        // The path compression technique
        VarT current = var;
        while (subsetVector_[current].parent != current) {
            VarT next = subsetVector_[current].parent;
            subsetVector_[current].parent = root;
            current = next;
        }

        return root;
    }

    template <typename VarT, typename LiteralT>
    void ComputeConnectedComponents<VarT, LiteralT>::unite(VarT root1, VarT root2) {
        assert(root1 != root2);                         // different roots
        assert(subsetVector_[root1].parent == root1);   // root
        assert(subsetVector_[root2].parent == root2);   // root

        // Union by rank
        if (subsetVector_[root1].rank < subsetVector_[root2].rank)
            subsetVector_[root1].parent = root2;
        else if (subsetVector_[root1].rank > subsetVector_[root2].rank)
            subsetVector_[root2].parent = root1;
        // Same rank
        else {
            subsetVector_[root2].parent = root1;
            ++subsetVector_[root1].rank;
        }
    }

    template <typename VarT, typename LiteralT>
    bool ComputeConnectedComponents<VarT, LiteralT>::isEmpty() const noexcept {
        for (VarT i = 0; i < subsetVector_.size(); ++i) {
            if ((subsetVector_[i].parent != i) ||
                (subsetVector_[i].rank != 0))
                return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT>
    void ComputeConnectedComponents<VarT, LiteralT>::addConnection(VarT var1, VarT var2) {
        assert((var1 > 0) && (var1 < subsetVector_.size()));   // valid variable
        assert((var2 > 0) && (var2 < subsetVector_.size()));   // valid variable

        if (var1 == var2)
            return;

        VarT root1 = find(var1);
        VarT root2 = find(var2);

        // Same component
        if (root1 == root2)
            return;

        unite(root1, root2);
    }

    template <typename VarT, typename LiteralT>
    typename ComputeConnectedComponents<VarT, LiteralT>::ConnectedComponentType
    ComputeConnectedComponents<VarT, LiteralT>::computeConnectedComponents(const VariableSetType& variableSet, const VariableSetType& ignoredVariableSet) {
        assert(ignoredVariableSet.size() <= variableSet.size());

        ConnectedComponentType connectedComponents;
        connectedComponents.reserve(S_ESTIMATED_NUMBER_OF_CONNECTED_COMPONENTS_);

        VarT componentCounter = 0;
        l_fromRootToComponentIndexVectorMap_computeConnectedComponents_.clear();

        // Create connected components
        #ifndef NDEBUG
        for (VarT var : Other::sortUnorderedSet(variableSet)) {
        #else
        for (VarT var : variableSet) {
        #endif
            assert((var > 0) && (var < subsetVector_.size()));   // valid variable

            VarT root = find(var);

            // Ignored variable
            if (Other::containInSet(ignoredVariableSet, var)) {
                assert(root == var);

                continue;
            }

            // Existing component
            if (l_fromRootToComponentIndexVectorMap_computeConnectedComponents_.contains(root)) {
                assert(l_fromRootToComponentIndexVectorMap_computeConnectedComponents_.find(root) < connectedComponents.size());

                connectedComponents[l_fromRootToComponentIndexVectorMap_computeConnectedComponents_.find(root)].variableSet.emplace(var);
            }
            // New component
            else {
                l_fromRootToComponentIndexVectorMap_computeConnectedComponents_.emplace(root, componentCounter);
                ++componentCounter;

                connectedComponents.emplace_back(variableSet.size());
                connectedComponents.back().variableSet.emplace(var);
            }
        }

        // Clean the data structure
        for (VarT var : variableSet) {
            subsetVector_[var].rank = 0;
            subsetVector_[var].parent = var;
        }

        return connectedComponents;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    void ComputeConnectedComponents<VarT, LiteralT>::printComputeConnectedComponents(std::ostream& out) const {
        out << "Compute connected components" << std::endl;

        for (VarT i = 1; i < subsetVector_.size(); ++i) {
            out << "\t" << std::to_string(i) << " - ";

            // Root
            if (subsetVector_[i].parent == i)
                out << "root, rank: " << std::to_string(subsetVector_[i].rank);
            // Inner node
            else
                out << std::to_string(subsetVector_[i].parent);

            out << std::endl;
        }
    }
    #endif
}   // namespace Hydra::Container::ComputeConnectedComponents
