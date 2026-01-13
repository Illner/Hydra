#pragma once

#include "./VsadsDecisionHeuristic.hpp"

namespace Hydra::DecisionHeuristic::Vsads {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT VsadsDecisionHeuristic<VarT, LiteralT, ClauseIdT>::processGetDecisionVariable(const VariableSetType& selectedVariableSet) const {
        assert(!selectedVariableSet.empty());

        VsadsScoreType bestScore = -1;
        VarT decisionVariable = static_cast<VarT>(0);

        #ifndef NDEBUG
        for (VarT var : Other::sortUnorderedSet(selectedVariableSet)) {
        #else
        for (VarT var : selectedVariableSet) {
        #endif
            VsidsScoreType vsidsScore = this->satSolverAbstractPtr_->getVsidsScore(var);
            assert(vsidsScore >= 0);   // VSIDS score is not negative

            ClauseIdT dlcsScore = this->formulaRepresentationAbstractPtr_->getNumberOfCurrentClauses(Formula::getPositiveLiteralT<VarT, LiteralT>(var)) +
                                  this->formulaRepresentationAbstractPtr_->getNumberOfCurrentClauses(Formula::getNegativeLiteralT<VarT, LiteralT>(var));

            VsadsScoreType score = static_cast<VsadsScoreType>(configuration_.p) * static_cast<VsadsScoreType>(vsidsScore) +
                                   static_cast<VsadsScoreType>(configuration_.q) * static_cast<VsadsScoreType>(dlcsScore);

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
    void VsadsDecisionHeuristic<VarT, LiteralT, ClauseIdT>::processPrintDecisionHeuristicDebug(std::ostream& out) const {
        // Configuration
        out << "p: " << std::to_string(configuration_.p) << std::endl;
        out << "q: " << std::to_string(configuration_.q) << std::endl;
    }
    #endif
}   // namespace Hydra::DecisionHeuristic::Vsads
