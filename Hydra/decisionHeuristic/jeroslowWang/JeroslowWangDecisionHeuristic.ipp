#pragma once

#include "./JeroslowWangDecisionHeuristic.hpp"

namespace Hydra::DecisionHeuristic::JeroslowWang {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT JeroslowWangDecisionHeuristic<VarT, LiteralT, ClauseIdT>::processGetDecisionVariable(const VariableSetType& selectedVariableSet) const {
        assert(!selectedVariableSet.empty());

        JeroslowWangScoreType bestScore = -1;
        VarT decisionVariable = static_cast<VarT>(0);

        #ifndef NDEBUG
        for (VarT var : Other::sortUnorderedSet(selectedVariableSet)) {
        #else
        for (VarT var : selectedVariableSet) {
        #endif
            // Positive literal
            JeroslowWangScoreType posScore = 0;
            ClauseSizeCounterType posClauseSizeCounter = this->formulaRepresentationAbstractPtr_->getCurrentClauseSizeCounter(Formula::getPositiveLiteralT<VarT, LiteralT>(var));

            for (const auto& [key, value] : posClauseSizeCounter)
                posScore += (JeroslowWangScoreType)value * std::pow((JeroslowWangScoreType)2, -key);   // value * 2 ^ (-key)

            // Negative literal
            JeroslowWangScoreType negScore = 0;
            ClauseSizeCounterType negClauseSizeCounter = this->formulaRepresentationAbstractPtr_->getCurrentClauseSizeCounter(Formula::getNegativeLiteralT<VarT, LiteralT>(var));

            for (const auto& [key, value] : negClauseSizeCounter)
                negScore += (JeroslowWangScoreType)value * std::pow((JeroslowWangScoreType)2, -key);   // value * 2 ^ (-key)

            JeroslowWangScoreType score = 0;

            // One-sided
            if (!configuration_.twoSidedVariant)
                score = std::max(posScore, negScore);
            // Two-sided
            else
                score = posScore + negScore;

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
    void JeroslowWangDecisionHeuristic<VarT, LiteralT, ClauseIdT>::processPrintDecisionHeuristicDebug(std::ostream& out) const {
        out << "";
    }
    #endif
}   // namespace Hydra::DecisionHeuristic::JeroslowWang
