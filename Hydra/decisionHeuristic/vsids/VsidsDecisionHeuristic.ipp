#pragma once

#include "./VsidsDecisionHeuristic.hpp"

namespace Hydra::DecisionHeuristic::Vsids {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT VsidsDecisionHeuristic<VarT, LiteralT, ClauseIdT>::processGetDecisionVariable(const VariableSetType& selectedVariableSet) const {
        assert(!selectedVariableSet.empty());

        VsidsScoreType bestScore = -1;
        VarT decisionVariable = static_cast<VarT>(0);

        #ifndef NDEBUG
        for (VarT var : Other::sortUnorderedSet(selectedVariableSet)) {
        #else
        for (VarT var : selectedVariableSet) {
        #endif
            VsidsScoreType score = this->satSolverAbstractPtr_->getVsidsScore(var);
            assert(score >= 0);   // score is not negative

            if (score > bestScore) {
                decisionVariable = var;
                bestScore = score;
            }
        }

        assert(decisionVariable > 0);   // decision variable has been selected

        return decisionVariable;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void VsidsDecisionHeuristic<VarT, LiteralT, ClauseIdT>::processPrintDecisionHeuristicDebug(std::ostream& out) const {
        out << "";
    }
    #endif
}   // namespace Hydra::DecisionHeuristic::Vsids
