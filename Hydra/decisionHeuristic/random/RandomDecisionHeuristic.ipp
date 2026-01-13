#pragma once

#include "./RandomDecisionHeuristic.hpp"

namespace Hydra::DecisionHeuristic::Random {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT RandomDecisionHeuristic<VarT, LiteralT, ClauseIdT>::processGetDecisionVariable(const VariableSetType& selectedVariableSet) const {
        assert(!selectedVariableSet.empty());

        // Generate a random number
        #ifdef __CYGWIN__
        std::random_device rd { "/dev/urandom" };
        #else
        std::random_device rd;
        #endif
        std::mt19937 generator(rd());
        std::uniform_int_distribution<std::size_t> distribution(0, selectedVariableSet.size() - 1);
        std::size_t randomNumber = distribution(generator);

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
