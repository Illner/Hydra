#pragma once

#include "./LiteralCountDecisionHeuristic.hpp"

namespace Hydra::DecisionHeuristic::LiteralCount {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT LiteralCountDecisionHeuristic<VarT, LiteralT, ClauseIdT>::processGetDecisionVariable(const VariableSetType& selectedVariableSet) const {
        assert(!selectedVariableSet.empty());

        bool set = false;
        ClauseIdT score = 0;
        ClauseIdT bestScore = 0;
        ClauseIdT tieBreakerScore = 0;
        ClauseIdT tieBreakerBestScore = 0;
        VarT decisionVariable = static_cast<VarT>(0);

        #ifndef NDEBUG
        for (VarT var : Other::sortUnorderedSet(selectedVariableSet)) {
        #else
        for (VarT var : selectedVariableSet) {
        #endif
            // Positive literal
            ClauseIdT posScore = this->formulaRepresentationAbstractPtr_->getNumberOfCurrentClauses(Formula::getPositiveLiteralT<VarT, LiteralT>(var));

            // Negative literal
            ClauseIdT negScore = this->formulaRepresentationAbstractPtr_->getNumberOfCurrentClauses(Formula::getNegativeLiteralT<VarT, LiteralT>(var));

            switch (configuration_.decisionHeuristicType) {
                // DLCS
                case DecisionHeuristicTypeEnum::DLCS:
                    score = posScore + negScore;

                    if ((score > bestScore) || !set) {
                        set = true;
                        decisionVariable = var;
                        bestScore = score;
                    }

                    break;

                // DLIS
                case DecisionHeuristicTypeEnum::DLIS:
                    score = std::max(posScore, negScore);

                    if ((score > bestScore) || !set) {
                        set = true;
                        decisionVariable = var;
                        bestScore = score;
                    }

                    break;

                // DLCS-DLIS
                case DecisionHeuristicTypeEnum::DLCS_DLIS:
                    score = posScore + negScore;                      // DLCS
                    tieBreakerScore = std::max(posScore, negScore);   // DLIS

                    if ((score > bestScore) || !set || ((score == bestScore) && (tieBreakerScore > tieBreakerBestScore))) {
                        set = true;
                        decisionVariable = var;
                        bestScore = score;
                        tieBreakerBestScore = tieBreakerScore;
                    }

                    break;

                default:
                    throw Exception::NotImplementedException(decisionHeuristicTypeEnumToString(configuration_.decisionHeuristicType),
                                                             "Hydra::DecisionHeuristic::LiteralCount::LiteralCountDecisionHeuristic::getDecisionVariable");
            }
        }

        assert(set);
        assert(decisionVariable > 0);   // decision variable has been selected

        return decisionVariable;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void LiteralCountDecisionHeuristic<VarT, LiteralT, ClauseIdT>::processPrintDecisionHeuristicDebug(std::ostream& out) const {
        out << "";
    }
    #endif
}   // namespace Hydra::DecisionHeuristic::LiteralCount
