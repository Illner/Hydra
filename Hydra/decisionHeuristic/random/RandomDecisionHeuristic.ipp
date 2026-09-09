#pragma once

#include "./RandomDecisionHeuristic.hpp"

namespace Hydra::DecisionHeuristic::Random {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT RandomDecisionHeuristic<VarT, LiteralT, ClauseIdT>::processGetDecisionVariable(const VariableSetType& selectedVariableSet) const {
        assert(!selectedVariableSet.empty());

        // Generate a random number
        std::uniform_int_distribution<std::size_t> distribution(0, selectedVariableSet.size() - 1);
        std::size_t randomNumber = distribution(r_generator_processGetDecisionVariable_);

        auto it = selectedVariableSet.cbegin();
        std::advance(it, randomNumber);

        return *it;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void RandomDecisionHeuristic<VarT, LiteralT, ClauseIdT>::processPrintDecisionHeuristicDebug(std::ostream& out) const {
        out << "";
    }
    #endif
}   // namespace Hydra::DecisionHeuristic::Random
