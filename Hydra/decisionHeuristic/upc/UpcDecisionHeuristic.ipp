#pragma once

#include "./UpcDecisionHeuristic.hpp"

namespace Hydra::DecisionHeuristic::Upc {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename UpcDecisionHeuristic<VarT, LiteralT, ClauseIdT>::UpcScoreType
    UpcDecisionHeuristic<VarT, LiteralT, ClauseIdT>::computeUpcScoreForVariable(VarT var, const VariableSetType& selectedVariableSet) const {
        // Positive literal
        LiteralType posLit(var, true);
        this->satSolverAbstractPtr_->assignLiteral(posLit, false);
        bool isSatisfiable = this->satSolverAbstractPtr_->unitPropagation(selectedVariableSet, false);
        this->satSolverAbstractPtr_->unassignLiteral(posLit);

        // Contradiction
        if (!isSatisfiable)
            return -1;

        UpcScoreType posUnitPropagationSize = static_cast<UpcScoreType>(this->satSolverAbstractPtr_->getImpliedLiteralReusableVectorFromPreviousCallOfUnitPropagation().size());

        // Negative literal
        LiteralType negLit(var, false);
        this->satSolverAbstractPtr_->assignLiteral(negLit, false);
        isSatisfiable = this->satSolverAbstractPtr_->unitPropagation(selectedVariableSet, false);
        this->satSolverAbstractPtr_->unassignLiteral(negLit);

        // Contradiction
        if (!isSatisfiable)
            return -1;

        UpcScoreType negUnitPropagationSize = static_cast<UpcScoreType>(this->satSolverAbstractPtr_->getImpliedLiteralReusableVectorFromPreviousCallOfUnitPropagation().size());

        UpcScoreType score = configuration_.constant * posUnitPropagationSize * negUnitPropagationSize +
                             posUnitPropagationSize + negUnitPropagationSize;

        assert(score >= 0);   // score is not negative

        return score;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT UpcDecisionHeuristic<VarT, LiteralT, ClauseIdT>::computeExactVariant(const VariableSetType& selectedVariableSet) const {
        UpcScoreType bestScore = -1;
        VarT decisionVariable = static_cast<VarT>(0);

        #ifndef NDEBUG
        for (VarT var : Other::sortUnorderedSet(selectedVariableSet)) {
        #else
        for (VarT var : selectedVariableSet) {
        #endif
            UpcScoreType score = computeUpcScoreForVariable(var, selectedVariableSet);

            // Contradiction
            if (score == -1)
                return var;

            if (score > bestScore) {
                decisionVariable = var;
                bestScore = score;
            }
        }

        assert(decisionVariable > 0);   // decision variable has been selected

        return decisionVariable;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT UpcDecisionHeuristic<VarT, LiteralT, ClauseIdT>::computeApproximateVariant(const VariableSetType& selectedVariableSet) const {
        assert(selectedVariableSet.size() > configuration_.approximateNumberOfVariables);

        ApproximateScoreVectorType approximateScoreVector;
        approximateScoreVector.reserve(selectedVariableSet.size());

        // Compute approximate scores
        #ifndef NDEBUG
        for (VarT var : Other::sortUnorderedSet(selectedVariableSet)) {
        #else
        for (VarT var : selectedVariableSet) {
        #endif
            // Positive literal
            UpcScoreType posNumberOfBinaryClauses = static_cast<UpcScoreType>(this->formulaRepresentationAbstractPtr_->getNumberOfCurrentBinaryClauses(Formula::getPositiveLiteralT<VarT, LiteralT>(var)));

            // Negative literal
            UpcScoreType negNumberOfBinaryClauses = static_cast<UpcScoreType>(this->formulaRepresentationAbstractPtr_->getNumberOfCurrentBinaryClauses(Formula::getNegativeLiteralT<VarT, LiteralT>(var)));

            UpcScoreType approximateScore = configuration_.constant * posNumberOfBinaryClauses * negNumberOfBinaryClauses +
                                            posNumberOfBinaryClauses + negNumberOfBinaryClauses;

            assert(approximateScore >= 0);   // approximate score is not negative

            approximateScoreVector.push_back(std::make_pair(var, approximateScore));
        }

        // Sort
        auto comparatorLambda = [](const ApproximateScorePairType& a, const ApproximateScorePairType& b) -> bool { return a.second > b.second; };
        #ifndef NDEBUG
        std::stable_sort(approximateScoreVector.begin(), approximateScoreVector.end(), comparatorLambda);
        #else
        std::sort(approximateScoreVector.begin(), approximateScoreVector.end(), comparatorLambda);
        #endif

        UpcScoreType bestScore = -1;
        VarT decisionVariable = static_cast<VarT>(0);

        for (VarT i = 0; i < configuration_.approximateNumberOfVariables; ++i) {
            VarT var = approximateScoreVector[i].first;

            UpcScoreType score = computeUpcScoreForVariable(var, selectedVariableSet);

            // Contradiction
            if (score == -1)
                return var;

            if (score > bestScore) {
                decisionVariable = var;
                bestScore = score;
            }
        }

        assert(decisionVariable > 0);   // decision variable has been selected

        return decisionVariable;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT UpcDecisionHeuristic<VarT, LiteralT, ClauseIdT>::processGetDecisionVariable(const VariableSetType& selectedVariableSet) const {
        assert(!selectedVariableSet.empty());

        // EUPC
        if (configuration_.exactVariant || (selectedVariableSet.size() <= configuration_.approximateNumberOfVariables))
            return computeExactVariant(selectedVariableSet);
        // AUPC
        else
            return computeApproximateVariant(selectedVariableSet);
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void UpcDecisionHeuristic<VarT, LiteralT, ClauseIdT>::processPrintDecisionHeuristicDebug(std::ostream& out) const {
        // Configuration
        if (!configuration_.exactVariant)
            out << "Approximate number of variables: " << std::to_string(configuration_.approximateNumberOfVariables) << std::endl;
        out << "Constant: " << std::to_string(configuration_.constant) << std::endl;
    }
    #endif
}   // namespace Hydra::DecisionHeuristic::Upc
