#pragma once

#include "./AspvallRenHCRecognition.hpp"

namespace Hydra::RenHCRecognition::Aspvall {

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    void AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::processInitialize() {
        ClauseIdAspT aspvallClauseId = 0;
        FormulaSizeType formulaPosition = 0;

        for (const LiteralAspType& lit : formula_) {
            contagiousOccurrenceList_.addOccurrence(lit.getLiteralT(), aspvallClauseId);

            // The end of the clause
            if ((++formulaPosition % 2) == 0)
                ++aspvallClauseId;
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    void AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::processSetAssignedLiteral(const LiteralType& lit,
                                                                                                                           const VariableSetType& currentComponentVariableSet,
                                                                                                                           [[maybe_unused]] bool firstAssignment,
                                                                                                                           bool lastAssignment) {
        #ifndef NDEBUG
        // Check if the local auxiliary data structures are clear
        if (firstAssignment) {
            assert(l_processedOriginalClauseStack_.empty());
            for (bool b : l_processedOriginalClauseVector_)
                assert(!b);
        }
        #endif

        // Set the new current level
        l_removedOccurrenceStackWithLevels_.addNewLevel();

        LiteralAspT literalAspT = static_cast<LiteralAspT>(lit.getLiteralT());

        // lit
        for (auto it = contagiousOccurrenceList_.begin(literalAspT); it != contagiousOccurrenceList_.end(literalAspT); ++it) {
            ClauseIdAspT aspvallClauseId = *it;

            assert(formula_[getIndexOfClauseInFormula(aspvallClauseId, true)].getLiteralT() == literalAspT);
            assert(aspvallClauseId < aspvallRenHCRecognitionStruct_.mappingFromAspvallClauseIdToOriginalClauseIdVector.size());

            ClauseIdT originalClauseId = aspvallRenHCRecognitionStruct_.mappingFromAspvallClauseIdToOriginalClauseIdVector[aspvallClauseId];

            assert(originalClauseId < l_processedOriginalClauseVector_.size());
            assert(this->formulaRepresentationAbstractPtr_->isClauseSatisfied(originalClauseId));   // clause is satisfied

            // The clause has been processed
            if (l_processedOriginalClauseVector_[originalClauseId])
                continue;

            // Set the clause as processed
            l_processedOriginalClauseVector_[originalClauseId] = true;
            l_processedOriginalClauseStack_.emplace_back(originalClauseId);

            ClauseIdAspT aspvallClauseIdTmp = aspvallRenHCRecognitionStruct_.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector[originalClauseId];
            FormulaSizeType beginIndex = getIndexOfClauseInFormula(aspvallClauseIdTmp, true, true);
            FormulaSizeType endIndex = getIndexOfClauseInFormula(aspvallRenHCRecognitionStruct_.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector[originalClauseId + 1], true, false);

            for (FormulaSizeType i = beginIndex; i < endIndex; i += 2, ++aspvallClauseIdTmp) {
                const LiteralAspType& litAsp = formula_[i];
                VarAspT varAsp = litAsp.getVariable();

                // Auxiliary clause (-y_p v y_n)
                if (varAsp > numberOfOriginalVariables_) {
                    assert(litAsp.isNegative());

                    continue;
                }

                // Assigned literal
                if (!Other::containInSet(currentComponentVariableSet, static_cast<VarT>(varAsp)))
                    continue;

                contagiousOccurrenceList_.removeOccurrence(litAsp.getLiteralT(), aspvallClauseIdTmp);
                l_removedOccurrenceStackWithLevels_.addElement(std::make_pair(litAsp.getLiteralT(), aspvallClauseIdTmp));
            }
        }

        LiteralAspT complementaryLiteralAspT = static_cast<LiteralAspT>(lit.getComplementaryLiteralT());

        // ~lit
        for (auto it = contagiousOccurrenceList_.begin(complementaryLiteralAspT); it != contagiousOccurrenceList_.end(complementaryLiteralAspT); ++it) {
            ClauseIdAspT aspvallClauseId = *it;

            assert(formula_[getIndexOfClauseInFormula(aspvallClauseId, true)].getLiteralT() == complementaryLiteralAspT);

            const LiteralAspType& auxLitAsp = formula_[getIndexOfClauseInFormula(aspvallClauseId, false)];

            assert(auxLitAsp.getVariable() > numberOfOriginalVariables_);   // auxiliary variable

            contagiousOccurrenceList_.removeOccurrence(auxLitAsp.getLiteralT(), aspvallClauseId);
        }

        // Clear the local auxiliary data structures
        if (lastAssignment) {
            for (ClauseIdT clauseId : l_processedOriginalClauseStack_) {
                assert(l_processedOriginalClauseVector_[clauseId]);

                l_processedOriginalClauseVector_[clauseId] = false;
            }

            l_processedOriginalClauseStack_.clear();
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    void AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::processSetUnassignedLiteral(const LiteralType& lit) {
        // lit (using l_removedOccurrenceStackWithLevels_)
        assert(l_removedOccurrenceStackWithLevels_.levelExists());

        l_removedOccurrenceStackWithLevels_.removeCurrentLevel([this](const OccurrencePairAspType& occurrencePairAsp) -> void { this->contagiousOccurrenceList_.addOccurrence(occurrencePairAsp.first, occurrencePairAsp.second); });

        LiteralAspT complementaryLiteralAspT = static_cast<LiteralAspT>(lit.getComplementaryLiteralT());

        // ~lit
        for (auto it = contagiousOccurrenceList_.begin(complementaryLiteralAspT); it != contagiousOccurrenceList_.end(complementaryLiteralAspT); ++it) {
            ClauseIdAspT aspvallClauseId = *it;

            assert(formula_[getIndexOfClauseInFormula(aspvallClauseId, true)].getLiteralT() == complementaryLiteralAspT);

            const LiteralAspType& auxLitAsp = formula_[getIndexOfClauseInFormula(aspvallClauseId, false)];

            assert(auxLitAsp.getVariable() > numberOfOriginalVariables_);   // auxiliary variable

            contagiousOccurrenceList_.addOccurrence(auxLitAsp.getLiteralT(), aspvallClauseId);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    void AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::processSetInactiveClause(ClauseIdT clauseId) {
        assert(clauseId < (aspvallRenHCRecognitionStruct_.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector.size() - 1));

        ClauseIdAspT beginAspvallClauseId = aspvallRenHCRecognitionStruct_.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector[clauseId];
        ClauseIdAspT endAspvallClauseId = aspvallRenHCRecognitionStruct_.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector[clauseId + 1];

        for (auto clauseIt = this->formulaRepresentationAbstractPtr_->beginClause(clauseId);
             clauseIt != this->formulaRepresentationAbstractPtr_->endClause(); ++clauseIt) {
            [[maybe_unused]] bool removedAtLeastOneOccurrence = contagiousOccurrenceList_.removeOccurrence(static_cast<LiteralAspT>(clauseIt->getLiteralT()),
                                                                                                           beginAspvallClauseId, endAspvallClauseId, true);
            assert(removedAtLeastOneOccurrence);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    void AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::processSetActiveClause(ClauseIdT clauseId,
                                                                                                                        const VariableSetType& currentComponentVariableSet) {
        assert(clauseId < (aspvallRenHCRecognitionStruct_.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector.size() - 1));

        ClauseIdAspT aspvallClauseId = aspvallRenHCRecognitionStruct_.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector[clauseId];
        FormulaSizeType beginIndex = getIndexOfClauseInFormula(aspvallClauseId, true, true);
        FormulaSizeType endIndex = getIndexOfClauseInFormula(aspvallRenHCRecognitionStruct_.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector[clauseId + 1], true, false);

        for (FormulaSizeType i = beginIndex; i < endIndex; i += 2, ++aspvallClauseId) {
            const LiteralAspType& lit = formula_[i];
            VarAspT var = lit.getVariable();

            // Auxiliary clause (-y_p v y_n)
            if (var > numberOfOriginalVariables_) {
                assert(lit.isNegative());

                continue;
            }

            // Assigned literal
            if (!Other::containInSet(currentComponentVariableSet, static_cast<VarT>(var)))
                continue;

            contagiousOccurrenceList_.addOccurrence(lit.getLiteralT(), aspvallClauseId);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    typename AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::VariableSetOptionalType
    AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::processIsRenHC(const ConnectedComponentStruct& connectedComponentStruct) {
        #ifndef NDEBUG
        // The local auxiliary data structures are empty
        for (bool b : l_satisfiedClauseVector_)
            assert(!b);

        assert(l_literalNeedToBeProcessedVector_.empty());
        assert(l_satisfiedClauseStackWithLevels_.isEmpty());
        assert(l_assignedVariableStackWithLevels_.isEmpty());
        assert(l_variableStateVector_.areAllVariablesUnassigned());
        #endif

        // Pure literals
        if (!connectedComponentStruct.pureLiteralVector.empty()) {
            // Set the new levels for pure literals
            l_satisfiedClauseStackWithLevels_.addNewLevel();
            l_assignedVariableStackWithLevels_.addNewLevel();

            // Set the pure literals
            for (const LiteralType& lit : connectedComponentStruct.pureLiteralVector) {
                // Assign the pure literal
                l_assignedVariableStackWithLevels_.addElement(lit.getVariable());
                l_variableStateVector_.assignVariable(lit.getVariable(), lit.isPositive());

                // Satisfy the clauses containing the pure literal
                for (auto it = contagiousOccurrenceList_.begin(lit.getLiteralT()); it != contagiousOccurrenceList_.end(lit.getLiteralT()); ++it) {
                    ClauseIdAspT aspvallClauseId = *it;

                    assert(aspvallClauseId < l_satisfiedClauseVector_.size());
                    assert(!l_satisfiedClauseVector_[aspvallClauseId]);   // not satisfied

                    l_satisfiedClauseVector_[aspvallClauseId] = true;
                    l_satisfiedClauseStackWithLevels_.addElement(aspvallClauseId);
                }

                assert(contagiousOccurrenceList_.begin(lit.getComplementaryLiteralT()) == contagiousOccurrenceList_.end(lit.getComplementaryLiteralT()));   // pure literal
            }
        }

        bool conflict = false;

        #ifndef NDEBUG
        for (VarT var : Other::sortUnorderedSet(connectedComponentStruct.variableSet)) {
        #else
        for (VarT var : connectedComponentStruct.variableSet) {
        #endif
            // The variable is already assigned
            if (l_variableStateVector_.isAssigned(var))
                continue;

            // Assign negative - no conflict
            if (assignLiteralAndDoUnitPropagation(LiteralAspType(var, false), true))
                continue;

            // Assign positive - no conflict
            if (assignLiteralAndDoUnitPropagation(LiteralAspType(var, true), true))
                continue;

            // Conflict - the residual Aspvall formula is not satisfiable
            conflict = true;
            break;
        }

        VariableSetOptionalType switchedVariableSet;

        // No conflict - the residual formula is renamable Horn
        if (!conflict) {
            switchedVariableSet = VariableSetOptionalType(connectedComponentStruct.variableSet.size());

            // Get the switched variables
            for (VarT var : connectedComponentStruct.variableSet) {
                // Switched variable
                if (l_variableStateVector_.getSignOfAssignedVariable(var))
                    switchedVariableSet->emplace(var);
            }
        }

        // Clear the local auxiliary data structures
        assert(l_literalNeedToBeProcessedVector_.empty());
        // Satisfied clauses
        while (l_satisfiedClauseStackWithLevels_.levelExists())
            removeCurrentLevelSatisfiedClauseStackWithLevels();
        // Assigned variables
        while (l_assignedVariableStackWithLevels_.levelExists())
            removeCurrentLevelAssignedVariableStackWithLevels();

        return switchedVariableSet;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    bool AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::assignLiteralAndDoUnitPropagation(const LiteralAspType& lit,
                                                                                                                                   bool firstCall) {
        // First call
        if (firstCall) {
            assert(l_literalNeedToBeProcessedVector_.empty());
            assert(lit.getVariable() <= numberOfOriginalVariables_);         // original variable
            assert(!l_variableStateVector_.isAssigned(lit.getVariable()));   // variable is NOT assigned

            // Set the new levels
            l_satisfiedClauseStackWithLevels_.addNewLevel();
            l_assignedVariableStackWithLevels_.addNewLevel();

            // Assign the literal
            l_variableStateVector_.assignVariable(lit);
            l_assignedVariableStackWithLevels_.addElement(lit.getVariable());
        }
        #ifndef NDEBUG
        // Recursion
        else {
            assert(l_variableStateVector_.isAssigned(lit.getVariable()));   // variable is assigned
        }
        #endif

        // lit
        for (auto it = contagiousOccurrenceList_.begin(lit.getLiteralT()); it != contagiousOccurrenceList_.end(lit.getLiteralT()); ++it) {
            ClauseIdAspT aspvallClauseId = *it;

            assert(aspvallClauseId < l_satisfiedClauseVector_.size());

            // The clause is already satisfied
            if (l_satisfiedClauseVector_[aspvallClauseId])
                continue;

            l_satisfiedClauseVector_[aspvallClauseId] = true;
            l_satisfiedClauseStackWithLevels_.addElement(aspvallClauseId);
        }

        // ~lit
        for (auto it = contagiousOccurrenceList_.begin(lit.getComplementaryLiteralT()); it != contagiousOccurrenceList_.end(lit.getComplementaryLiteralT()); ++it) {
            ClauseIdAspT aspvallClauseId = *it;

            assert(aspvallClauseId < l_satisfiedClauseVector_.size());

            // The clause is satisfied
            if (l_satisfiedClauseVector_[aspvallClauseId])
                continue;

            LiteralAspType otherLit = formula_[getIndexOfClauseInFormula(aspvallClauseId, false)];
            if (otherLit.getVariable() == lit.getVariable())
                otherLit = formula_[getIndexOfClauseInFormula(aspvallClauseId, true)];

            assert(otherLit.getVariable() != lit.getVariable());   // other literal

            // The other literal is NOT assigned
            if (!l_variableStateVector_.isAssigned(otherLit)) {
                #ifndef NDEBUG
                // The variable has not yet been added to be processed
                for (const LiteralAspType& litTmp : l_literalNeedToBeProcessedVector_)
                    assert(litTmp.getVariable() != otherLit.getVariable());
                #endif

                l_variableStateVector_.assignVariable(otherLit);
                l_assignedVariableStackWithLevels_.addElement(otherLit.getVariable());
                l_literalNeedToBeProcessedVector_.emplace_back(otherLit);

                continue;
            }

            assert(!l_variableStateVector_.isLiteralSatisfied(otherLit));   // other literal does not satisfy the clause

            // Remove the current levels in the local auxiliary data structures
            removeCurrentLevelSatisfiedClauseStackWithLevels();
            removeCurrentLevelAssignedVariableStackWithLevels();

            l_literalNeedToBeProcessedVector_.clear();

            return false;
        }

        // Process all the literals that need to be processed
        while (!l_literalNeedToBeProcessedVector_.empty()) {
            LiteralAspType litTmp = l_literalNeedToBeProcessedVector_.back();
            l_literalNeedToBeProcessedVector_.pop_back();

            // Contradiction
            if (!assignLiteralAndDoUnitPropagation(litTmp, false))
                return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    void AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::removeCurrentLevelSatisfiedClauseStackWithLevels() {
        l_satisfiedClauseStackWithLevels_.removeCurrentLevel([this](ClauseIdAspT aspvallClauseId) -> void {
            assert(aspvallClauseId < this->l_satisfiedClauseVector_.size());
            assert(this->l_satisfiedClauseVector_[aspvallClauseId]);   // is satisfied

            this->l_satisfiedClauseVector_[aspvallClauseId] = false;
        });
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    void AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::removeCurrentLevelAssignedVariableStackWithLevels() {
        l_assignedVariableStackWithLevels_.removeCurrentLevel([this](VarAspT var) -> void { this->l_variableStateVector_.unassignVariable(var); });
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    FormulaSizeType AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::getIndexOfClauseInFormula(ClauseIdAspT aspvallClauseId,
                                                                                                                                      bool firstIndex,
                                                                                                                                      [[maybe_unused]] bool assert) const {
        assert(!assert || aspvallClauseId < aspvallRenHCRecognitionStruct_.numberOfClauses);
        assert(assert || aspvallClauseId <= aspvallRenHCRecognitionStruct_.numberOfClauses);

        FormulaSizeType formulaIndex = (FormulaSizeType)2 * static_cast<FormulaSizeType>(aspvallClauseId);

        // Second index
        if (!firstIndex)
            ++formulaIndex;

        assert(!assert || formulaIndex < formula_.size());
        assert(assert || formulaIndex <= formula_.size());

        return formulaIndex;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    void AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::processPrintRenHCRecognitionDebug(std::ostream& out) const {
        out << "Formula:";
        FormulaSizeType formulaPosition = 0;
        for (const LiteralAspType& lit : formula_) {
            out << " " << lit;

            // The end of the clause
            if ((++formulaPosition % 2) == 0)
                out << " O";
        }
        out << std::endl;

        // Aspvall renH-C recognition structure
        out << "Number of Aspvall variables: " << std::to_string(aspvallRenHCRecognitionStruct_.numberOfVariables) << std::endl;
        out << "Number of Aspvall literals: " << std::to_string(aspvallRenHCRecognitionStruct_.numberOfLiterals) << std::endl;
        out << "Number of Aspvall clauses: " << std::to_string(aspvallRenHCRecognitionStruct_.numberOfClauses) << std::endl;
        out << "Aspvall formula size: " << std::to_string(aspvallRenHCRecognitionStruct_.formulaSize) << std::endl;
        out << "Mapping from original clause to first Aspvall clause:";
        for (ClauseIdAspT aspvallClauseId : aspvallRenHCRecognitionStruct_.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector)
            out << " " << std::to_string(aspvallClauseId);
        out << std::endl;
        out << "Mapping from Aspvall clause to original clause:";
        for (ClauseIdT clauseId : aspvallRenHCRecognitionStruct_.mappingFromAspvallClauseIdToOriginalClauseIdVector)
            out << " " << std::to_string(clauseId);
        out << std::endl;

        // Only for the initial formula
        if (this->d_initialFormula_) {
            // Removed occurrences
            out << "Removed occurrences: ";
            l_removedOccurrenceStackWithLevels_.printStackWithLevelsDebug(out, [](const OccurrencePairAspType& removedOccurrence) -> std::string { return "(" + Formula::createLiteralFromLiteralT<VarAspT>(removedOccurrence.first).toString() + ", " + std::to_string(removedOccurrence.second) + ")"; });

            // Occurrence list
            contagiousOccurrenceList_.printContagiousOccurrenceListDebug(out);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    bool AspvallRenHCRecognition<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::processVerifyRenHCDebug(const VariableSetType& switchedVariableSet) const {
        d_variableStateVector_.clear();   // clear the structure

        // Assign the original variables
        for (VarT var = 1; var <= numberOfOriginalVariables_; ++var) {
            // Switched variable
            if (Other::containInSet(switchedVariableSet, var))
                d_variableStateVector_.assignVariable(var, true);
            else
                d_variableStateVector_.assignVariable(var, false);
        }

        for (FormulaSizeType i = 0; i < formula_.size(); i += 2) {
            const LiteralAspType& firstLiteral = formula_[i];
            const LiteralAspType& secondLiteral = formula_[i + 1];

            assert(secondLiteral.getVariable() > numberOfOriginalVariables_);   // auxiliary variable

            // Auxiliary clause (-y_p v y_n)
            if (firstLiteral.getVariable() > numberOfOriginalVariables_) {
                assert(firstLiteral.isNegative());
                assert(secondLiteral.isPositive());
                assert(!d_variableStateVector_.isAssigned(secondLiteral.getVariable()));   // second literal is NOT assigned

                // First literal is NOT assigned
                if (!d_variableStateVector_.isAssigned(firstLiteral.getVariable())) {
                    d_variableStateVector_.assignVariable(firstLiteral.getVariable(), false);

                    continue;
                }

                // First literal satisfies the clause
                if (!d_variableStateVector_.getSignOfAssignedVariable(firstLiteral.getVariable()))
                    continue;

                // Second literal must satisfy the clause
                d_variableStateVector_.assignVariable(secondLiteral.getVariable(), true);

                continue;
            }

            assert(firstLiteral.getVariable() <= numberOfOriginalVariables_);        // original variable
            assert(d_variableStateVector_.isAssigned(firstLiteral.getVariable()));   // first literal is assigned

            // First literal satisfies the clause
            if (d_variableStateVector_.isLiteralSatisfied(firstLiteral)) {
                continue;
            }
            // First literal does NOT satisfy the clause
            else {
                // Second literal is NOT assigned
                if (!d_variableStateVector_.isAssigned(secondLiteral.getVariable())) {
                    d_variableStateVector_.assignVariable(secondLiteral.getVariable(), secondLiteral.isPositive());

                    continue;
                }

                // The clause cannot be satisfied
                if (!d_variableStateVector_.isLiteralSatisfied(secondLiteral))
                    return false;
            }
        }

        return true;
    }
    #endif
}   // namespace Hydra::RenHCRecognition::Aspvall
