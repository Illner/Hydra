#pragma once

#include "./DecisionHeuristicAbstract.hpp"

namespace Hydra::DecisionHeuristic {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::getDecisionVariable(const VariableSetType& selectedVariableSet,
                                                                                   bool removeIgnoredPureVariables) const {
        assert(!selectedVariableSet.empty());   // at least one variable

        // Statistics
        if (decisionHeuristicStatisticsPtr_) {
            decisionHeuristicStatisticsPtr_->getDecisionVariableTimer.startStopwatch();
            decisionHeuristicStatisticsPtr_->numberOfPreselectedVariablesCounter.addCount(static_cast<Statistics::LargeNumberType>(selectedVariableSet.size()));
        }

        // No restriction is needed
        if (!removeIgnoredPureVariables || (ignorePureLiteralType_ == IgnorePureLiteralTypeEnum::NONE)) {
            #ifndef NDEBUG
            // Check if all variables are not ignored pure
            for (VarT var : selectedVariableSet)
                assert(!formulaRepresentationAbstractPtr_->isPureLiteralInCurrentFormula(var, ignorePureLiteralType_));
            #endif

            VarT decisionVariable = processGetDecisionVariable(selectedVariableSet);

            // Statistics
            if (decisionHeuristicStatisticsPtr_)
                decisionHeuristicStatisticsPtr_->getDecisionVariableTimer.stopStopwatch();

            return decisionVariable;
        }

        // Initialize local auxiliary data structures
        if (l_firstCall_getDecisionVariable_) {
            l_restrictedSelectedVariableSet_getDecisionVariable_ = VariableSetType(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());

            l_firstCall_getDecisionVariable_ = false;
        }

        l_restrictedSelectedVariableSet_getDecisionVariable_.clear();

        for (VarT var : selectedVariableSet) {
            // Not ignored pure variable
            if (!formulaRepresentationAbstractPtr_->isPureLiteralInCurrentFormula(var, ignorePureLiteralType_))
                l_restrictedSelectedVariableSet_getDecisionVariable_.emplace(var);
        }

        assert(!l_restrictedSelectedVariableSet_getDecisionVariable_.empty());   // at least one variable

        // Statistics
        if (decisionHeuristicStatisticsPtr_)
            decisionHeuristicStatisticsPtr_->ratioOfNumberOfRestrictedVariablesToNumberOfPreselectedVariablesCounter.addCount(static_cast<Statistics::LargeFloatingNumberType>(l_restrictedSelectedVariableSet_getDecisionVariable_.size()) / static_cast<Statistics::LargeFloatingNumberType>(selectedVariableSet.size()));

        VarT decisionVariable = processGetDecisionVariable(l_restrictedSelectedVariableSet_getDecisionVariable_);

        // Statistics
        if (decisionHeuristicStatisticsPtr_)
            decisionHeuristicStatisticsPtr_->getDecisionVariableTimer.stopStopwatch();

        return decisionVariable;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::printDecisionHeuristicDebug(std::ostream& out, bool printCurrentFormula) const {
        out << "Decision heuristic" << std::endl;
        out << "Type: " << decisionHeuristicTypeEnumToString(decisionHeuristicType_) << std::endl;
        out << "Ignore pure literal type: " << ignorePureLiteralTypeEnumToString(ignorePureLiteralType_) << std::endl;

        // Current formula
        if (printCurrentFormula) {
            out << "Current formula: ";
            formulaRepresentationAbstractPtr_->printCurrentFormulaDebug(out);
            out << std::endl;
        }

        this->processPrintDecisionHeuristicDebug(out);

        out << std::endl;
    }
    #endif
}   // namespace Hydra::DecisionHeuristic
