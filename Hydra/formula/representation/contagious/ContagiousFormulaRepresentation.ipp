#pragma once

#include "./ContagiousFormulaRepresentation.hpp"

namespace Hydra::Formula::Representation::Contagious {

    template <typename VarT2, typename LiteralT2, typename ClauseIdT2>
    std::vector<ClauseIdT2> createLiteralNumberOfOccurrences(VarT2 numberOfVariables,
                                                             const std::vector<Literal<VarT2, LiteralT2>>& formula) noexcept {
        using LiteralType = Literal<VarT2, LiteralT2>;
        using ClauseIdVectorType = std::vector<ClauseIdT2>;

        ClauseIdVectorType literalNumberOfOccurrences(static_cast<typename ClauseIdVectorType::size_type>(LiteralT2(2) + LiteralT2(2) * static_cast<LiteralT2>(numberOfVariables)), 0);

        for (const LiteralType& lit : formula) {
            if (lit.isZeroLiteral())
                continue;

            ++literalNumberOfOccurrences[lit.getLiteralT()];
        }

        return literalNumberOfOccurrences;
    }

    template <typename VarT2, typename LiteralT2, typename ClauseIdT2>
    ClauseIdT2 getNumberOfClauses(const std::vector<Literal<VarT2, LiteralT2>>& formula) noexcept {
        ClauseIdT2 numberOfClauses = 0;

        for (const Literal<VarT2, LiteralT2>& lit : formula) {
            if (lit.isZeroLiteral())
                ++numberOfClauses;
        }

        return numberOfClauses;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::initializeDataStructures() {
        currentComponentFormulaSize_ = this->originalFormulaSize_;

        // Clause offset
        originalClauseOffset_.reserve(this->numberOfOriginalClauses_);

        // Clause size
        ClauseSizeType clauseSize = 0;
        originalClauseSize_.reserve(this->numberOfOriginalClauses_);

        // Clause - number of (un)satisfied literals
        clauseNumberOfSatisfiedLiterals_.reserve(this->numberOfOriginalClauses_);
        clauseNumberOfUnsatisfiedLiterals_.reserve(this->numberOfOriginalClauses_);

        // Clause watcher
        clauseIdWatcher_.reserve(this->numberOfOriginalClauses_);

        // Current component clauses - stack
        currentComponentClausesStack_.reserve(this->numberOfOriginalClauses_);

        // Recognition
        ClauseSizeType numberOfPositiveLiterals = 0;
        ClauseSizeType numberOfNegativeLiterals = 0;
        // Recognition of Horn-C
        if (configuration_.recognitionTypeStruct.hornC)
            numberOfPositiveLiteralsInClauseVector_.reserve(this->numberOfOriginalClauses_);
        // Recognition of anti-Horn-C
        if (configuration_.recognitionTypeStruct.antiHornC)
            numberOfNegativeLiteralsInClauseVector_.reserve(this->numberOfOriginalClauses_);

        bool newClause = true;
        ClauseIdT clauseId = 0;

        for (FormulaSizeType i = 0; i < originalFormula_.size(); ++i) {
            // A new clause has been found
            if (newClause) {
                assert(!originalFormula_[i].isZeroLiteral());   // not empty clause

                // Clause offset
                originalClauseOffset_.emplace_back(static_cast<FormulaSizeType>(i));

                // Clause - number of (un)satisfied literals
                clauseNumberOfSatisfiedLiterals_.emplace_back(0);
                clauseNumberOfUnsatisfiedLiterals_.emplace_back(0);

                // Clause watcher
                clauseIdWatcher_.emplace_back(0);

                newClause = false;
            }

            // Zero literal = end of the clause
            if (originalFormula_[i].isZeroLiteral()) {
                assert(numberOfPositiveLiterals + numberOfNegativeLiterals == clauseSize);

                // Sort the clause
                auto beginIt = originalFormula_.begin();
                std::advance(beginIt, originalClauseOffset_[clauseId]);
                auto endIt = beginIt;
                std::advance(endIt, clauseSize);

                std::sort(beginIt, endIt);

                // Max clause size
                if (maxOriginalClauseSize_ < clauseSize)
                    maxOriginalClauseSize_ = clauseSize;

                // Clause size
                originalClauseSize_.emplace_back(clauseSize);
                clauseSize = 0;

                // Recognition of Horn-C
                if (configuration_.recognitionTypeStruct.hornC)
                    numberOfPositiveLiteralsInClauseVector_.emplace_back(numberOfPositiveLiterals);
                // Recognition of anti-Horn-C
                if (configuration_.recognitionTypeStruct.antiHornC)
                    numberOfNegativeLiteralsInClauseVector_.emplace_back(numberOfNegativeLiterals);

                numberOfPositiveLiterals = 0;
                numberOfNegativeLiterals = 0;

                ++clauseId;
                newClause = true;
            }
            // Standard literal
            else {
                const LiteralType& lit = originalFormula_[i];

                // Occurrence list
                contagiousOccurrenceList_.addOccurrence(lit.getLiteralT(), clauseId);

                // Positive literal
                if (lit.isPositive())
                    ++numberOfPositiveLiterals;
                // Negative literal
                else
                    ++numberOfNegativeLiterals;

                // Clause size
                ++clauseSize;
            }
        }

        assert(clauseId == this->numberOfOriginalClauses_);
        assert(configuration_.recognitionTypeStruct.hornC != numberOfPositiveLiteralsInClauseVector_.empty());
        assert(configuration_.recognitionTypeStruct.antiHornC != numberOfNegativeLiteralsInClauseVector_.empty());
        assert(numberOfPositiveLiteralsInClauseVector_.empty() || (numberOfPositiveLiteralsInClauseVector_.size() == clauseId));
        assert(numberOfNegativeLiteralsInClauseVector_.empty() || (numberOfNegativeLiteralsInClauseVector_.size() == clauseId));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::sortClauseIdReusableVectorWithGroupingBySizes(ClauseIdReusableVectorType& clauseIdReusableVector,
                                                                                                                   bool considerOnlyVariables) const {
        // Sort the clauses based on their sizes
        std::sort(clauseIdReusableVector.begin(), clauseIdReusableVector.end(), ClauseSizeComparator(this));

        auto beginGroupIterator = clauseIdReusableVector.begin();

        while (beginGroupIterator != clauseIdReusableVector.end()) {
            ClauseSizeType clauseSize = getCurrentClauseSize(*beginGroupIterator);

            // Find the last clause in the current group
            auto endGroupIterator = std::find_if(beginGroupIterator, clauseIdReusableVector.end(),
                                                 [this, clauseSize](ClauseIdT clauseId) { return (getCurrentClauseSize(clauseId) != clauseSize); });

            // Sort the group
            // Consider variables
            if (considerOnlyVariables)
                std::sort(beginGroupIterator, endGroupIterator, SameClauseSizeVariableComparatorFunctor(this));
            // Consider literals
            else
                std::sort(beginGroupIterator, endGroupIterator, SameClauseSizeComparatorFunctor(this));

            beginGroupIterator = endGroupIterator;
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::removeDuplicateClausesFromClauseIdReusableVector(ClauseIdReusableVectorType& clauseIdReusableVector,
                                                                                                                      bool considerOnlyVariables, bool alreadySorted) const {
        // Sort the clauses
        if (!alreadySorted)
            sortClauseIdReusableVectorWithGroupingBySizes(clauseIdReusableVector, considerOnlyVariables);

        // Consider variables
        if (considerOnlyVariables) {
            auto newEndIterator = std::unique(clauseIdReusableVector.begin(), clauseIdReusableVector.end(), ClauseEqualVariableComparatorFunctor(this));
            clauseIdReusableVector.erase(newEndIterator);
        }
        // Consider literals
        else {
            auto newEndIterator = std::unique(clauseIdReusableVector.begin(), clauseIdReusableVector.end(), ClauseEqualComparatorFunctor(this));
            clauseIdReusableVector.erase(newEndIterator);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::sortClauses(ClauseIdReusableVectorType& clauseIdReusableVector,
                                                                                 bool removeDuplicateClauses, const VectorSetType& ignoredClauseVectorSet,
                                                                                 bool considerOnlyVariables, OmitClauseTypeEnum omitClauseType) const {
        assert(ignoredClauseVectorSet.size() <= currentComponentClausesFixedVector_.size());

        bool areIgnoredClausesUsed = (ignoredClauseVectorSet.capacity() > 0);   // consider ignored clauses

        clauseIdReusableVector.clear();

        // Add the clauses satisfying the requirements
        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            assert(this->isClauseUnresolved(clauseId));   // clause is unresolved

            // The clause is ignored
            if (areIgnoredClausesUsed && ignoredClauseVectorSet.contains(clauseId))
                continue;

            // Omit clause type
            switch (omitClauseType) {
                case OmitClauseTypeEnum::NONE:
                    break;
                case OmitClauseTypeEnum::ORIGINAL_BINARY:
                    if (this->isClauseUntouchedAndBinary(clauseId))
                        continue;
                    break;
                case OmitClauseTypeEnum::UNTOUCHED:
                    if (this->isClauseUntouched(clauseId))
                        continue;
                    break;
                default:
                    throw Exception::NotImplementedException(Cache::CachingScheme::omitClauseTypeEnumToString(omitClauseType),
                                                             "Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation::sortClauses");
            }

            clauseIdReusableVector.emplace_back(clauseId);
        }

        // Sort the clauses
        sortClauseIdReusableVectorWithGroupingBySizes(clauseIdReusableVector, considerOnlyVariables);

        // Remove the duplicate clauses
        if (removeDuplicateClauses)
            removeDuplicateClausesFromClauseIdReusableVector(clauseIdReusableVector, considerOnlyVariables, true);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::ClauseSizeType
    ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getIndexOfUnassignedLiteralInClause(ClauseIdT clauseId,
                                                                                                    IgnorePureLiteralTypeEnum ignorePureLiteralType) const {
        assert(clauseId < this->numberOfOriginalClauses_);
        assert(this->isClauseUnresolved(clauseId));   // clause is unresolved

        ClauseSizeType backupIndex = 0;

        for (ClauseSizeType i = 0; i < originalClauseSize_[clauseId]; ++i) {
            VarT var = getLiteralAtPositionInClause(clauseId, i).getVariable();

            if (!this->isVariableAssigned(var)) {
                if (this->isPureLiteralInCurrentFormula(var, ignorePureLiteralType))
                    backupIndex = i;
                else
                    return i;
            }
        }

        // The clause contains only pure literals of the ignored type
        if (ignorePureLiteralType != IgnorePureLiteralTypeEnum::NONE)
            return backupIndex;

        throw Exception::SomethingIsWrongException();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::updateClauseWatcher(ClauseIdT clauseId,
                                                                                         IgnorePureLiteralTypeEnum ignorePureLiteralType) {
        assert(this->isClauseUnresolved(clauseId));   // clause is unresolved

        bool changed = false;
        ClauseSizeType watcherPosition = clauseIdWatcher_[clauseId];

        // (position + 1, endClause)
        for (ClauseSizeType i = watcherPosition + 1; i < originalClauseSize_[clauseId]; ++i) {
            VarT var = getLiteralAtPositionInClause(clauseId, i).getVariable();

            if (!this->isVariableAssigned(var) && !this->isPureLiteralInCurrentFormula(var, ignorePureLiteralType)) {
                clauseIdWatcher_[clauseId] = i;
                changed = true;
                break;
            }
        }

        // (0, position - 1)
        if (!changed) {
            for (ClauseSizeType i = 0; i < watcherPosition; ++i) {
                VarT var = getLiteralAtPositionInClause(clauseId, i).getVariable();

                if (!this->isVariableAssigned(var) && !this->isPureLiteralInCurrentFormula(var, ignorePureLiteralType)) {
                    clauseIdWatcher_[clauseId] = i;
                    changed = true;
                    break;
                }
            }
        }

        return changed;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::processAddLiteralToPartialAssignment(const LiteralType& lit,
                                                                                                          VariableVectorType& freeVariableVector,
                                                                                                          [[maybe_unused]] bool firstAssignment,
                                                                                                          bool lastAssignment) {
        assert(!firstAssignment || l_clauseNeedsToBeDeactivatedVectorSet_processAddLiteralToPartialAssignment_.empty());

        LiteralType complementaryLit = ~lit;

        // Current component clauses
        currentComponentClausesStack_.emplace_back(static_cast<ClauseIdT>(currentComponentClausesFixedVector_.size()));

        // lit
        for (auto it = contagiousOccurrenceList_.begin(lit.getLiteralT()); it != contagiousOccurrenceList_.end(lit.getLiteralT()); ++it) {
            ClauseIdT clauseId = *it;

            assert(!this->isClauseSatisfied(clauseId));   // clause is not satisfied

            currentComponentFormulaSize_ -= getCurrentClauseSize(clauseId);
            ++clauseNumberOfSatisfiedLiterals_[clauseId];

            // The clause needs to be deactivated
            assert(!l_clauseNeedsToBeDeactivatedVectorSet_processAddLiteralToPartialAssignment_.contains(clauseId));
            l_clauseNeedsToBeDeactivatedVectorSet_processAddLiteralToPartialAssignment_.emplace(clauseId);

            for (auto clauseIt = beginClause(clauseId, false); clauseIt != this->endClause(); ++clauseIt) {
                const LiteralType& litTmp = *clauseIt;
                VarT varTmp = litTmp.getVariable();

                assert(lit != litTmp);

                contagiousOccurrenceList_.removeOccurrence(litTmp.getLiteralT(), clauseId);

                // The variable is free
                if (isVariableFree(varTmp))
                    freeVariableVector.emplace_back(varTmp);
            }
        }

        if (lastAssignment) {
            currentComponentClausesFixedVector_.swapWithoutRemovingElementsFromVectorSet(l_clauseNeedsToBeDeactivatedVectorSet_processAddLiteralToPartialAssignment_);

            l_clauseNeedsToBeDeactivatedVectorSet_processAddLiteralToPartialAssignment_.clear();
        }

        // ~lit
        for (auto it = contagiousOccurrenceList_.begin(complementaryLit.getLiteralT()); it != contagiousOccurrenceList_.end(complementaryLit.getLiteralT()); ++it) {
            ClauseIdT clauseId = *it;

            assert(!this->isClauseSatisfied(clauseId));   // clause is not satisfied

            --currentComponentFormulaSize_;
            ++clauseNumberOfUnsatisfiedLiterals_[clauseId];

            assert(!this->isClauseEmpty(clauseId));   // clause is not empty

            // Watcher
            if (getLiteralAtPositionInClause(clauseId, clauseIdWatcher_[clauseId]) == complementaryLit) {
                [[maybe_unused]] bool changed = updateClauseWatcher(clauseId, IgnorePureLiteralTypeEnum::NONE);

                assert(changed);   // watcher has been changed
            }

            // Recognition of Horn-C
            if (configuration_.recognitionTypeStruct.hornC && complementaryLit.isPositive()) {
                assert(numberOfPositiveLiteralsInClauseVector_[clauseId] > 0);   // at least one positive literal

                --numberOfPositiveLiteralsInClauseVector_[clauseId];
            }

            // Recognition of anti-Horn-C
            if (configuration_.recognitionTypeStruct.antiHornC && complementaryLit.isNegative()) {
                assert(numberOfNegativeLiteralsInClauseVector_[clauseId] > 0);   // at least one negative literal

                --numberOfNegativeLiteralsInClauseVector_[clauseId];
            }
        }

        assert(!lastAssignment || l_clauseNeedsToBeDeactivatedVectorSet_processAddLiteralToPartialAssignment_.empty());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::processRemoveLiteralFromPartialAssignment(const LiteralType& lit,
                                                                                                               VariableVectorType& unfreeVariableVector) {
        LiteralType complementaryLit = ~lit;

        // lit
        for (auto it = contagiousOccurrenceList_.begin(lit.getLiteralT()); it != contagiousOccurrenceList_.end(lit.getLiteralT()); ++it) {
            ClauseIdT clauseId = *it;

            assert(this->isClauseSatisfied(clauseId));   // clause is satisfied

            --clauseNumberOfSatisfiedLiterals_[clauseId];
            currentComponentFormulaSize_ += getCurrentClauseSize(clauseId);

            for (auto clauseIt = beginClause(clauseId, false); clauseIt != this->endClause(); ++clauseIt) {
                const LiteralType& litTmp = *clauseIt;
                VarT varTmp = litTmp.getVariable();

                if (litTmp == lit)
                    continue;

                // The variable is unfree
                if (isVariableFree(varTmp))
                    unfreeVariableVector.emplace_back(varTmp);

                contagiousOccurrenceList_.addOccurrence(litTmp.getLiteralT(), clauseId);
            }
        }

        // Current component clauses
        currentComponentClausesFixedVector_.changeNumberOfActiveElements(currentComponentClausesStack_.back());
        currentComponentClausesStack_.pop_back();

        // ~lit
        for (auto it = contagiousOccurrenceList_.begin(complementaryLit.getLiteralT()); it != contagiousOccurrenceList_.end(complementaryLit.getLiteralT()); ++it) {
            ClauseIdT clauseId = *it;

            assert(!this->isClauseSatisfied(clauseId));   // clause is not satisfied

            ++currentComponentFormulaSize_;
            --clauseNumberOfUnsatisfiedLiterals_[clauseId];

            // Recognition of Horn-C
            if (configuration_.recognitionTypeStruct.hornC && complementaryLit.isPositive())
                ++numberOfPositiveLiteralsInClauseVector_[clauseId];

            // Recognition of anti-Horn-C
            if (configuration_.recognitionTypeStruct.antiHornC && complementaryLit.isNegative())
                ++numberOfNegativeLiteralsInClauseVector_[clauseId];
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::processAddClausesContainingOnlyPureLiteralsOfIgnoredType(const ClauseIdSetType& pureClauseSet) {
        for (ClauseIdT clauseId : pureClauseSet) {
            currentComponentFormulaSize_ += getCurrentClauseSize(clauseId);

            for (auto clauseIt = beginClause(clauseId); clauseIt != this->endClause(); ++clauseIt)
                contagiousOccurrenceList_.addOccurrence(clauseIt->getLiteralT(), clauseId);
        }

        // Current component clauses
        currentComponentClausesFixedVector_.changeNumberOfActiveElements(currentComponentClausesStack_.back());
        currentComponentClausesStack_.pop_back();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::processRemoveClausesContainingOnlyPureLiteralsOfIgnoredType(const ClauseIdSetType& pureClauseSet) {
        // Current component clauses
        currentComponentClausesStack_.emplace_back(static_cast<ClauseIdT>(currentComponentClausesFixedVector_.size()));

        for (ClauseIdT clauseId : pureClauseSet) {
            currentComponentFormulaSize_ -= getCurrentClauseSize(clauseId);

            for (auto clauseIt = beginClause(clauseId); clauseIt != this->endClause(); ++clauseIt)
                contagiousOccurrenceList_.removeOccurrence(clauseIt->getLiteralT(), clauseId);
        }

        // Current component clauses
        currentComponentClausesFixedVector_.swapWithoutRemovingElementsFromSet(pureClauseSet);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::ConnectedComponentType
    ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::processComputeConnectedComponents(const VariableSetType& currentComponentVariableSet) const {
        assert(l_computeConnectedComponents_processComputeConnectedComponents_.isEmpty());   // data structure is empty

        // Precompute watched variables for clauses
        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            assert(this->isClauseUnresolved(clauseId));   // clause is unresolved

            VarT watchedVariable = getLiteralAtPositionInClause(clauseId, clauseIdWatcher_[clauseId]).getVariable();

            assert(Other::containInSet(currentComponentVariableSet, watchedVariable));   // variable in the current component

            l_watchedVariableVector_processComputeConnectedComponents_[clauseId] = watchedVariable;
        }

        for (VarT var : currentComponentVariableSet) {
            LiteralT posLiteralT = getPositiveLiteralT<VarT, LiteralT>(var);
            LiteralT negLiteralT = getNegativeLiteralT<VarT, LiteralT>(var);

            // Positive literal
            for (auto it = contagiousOccurrenceList_.begin(posLiteralT); it != contagiousOccurrenceList_.end(posLiteralT); ++it)
                l_computeConnectedComponents_processComputeConnectedComponents_.addConnection(l_watchedVariableVector_processComputeConnectedComponents_[*it], var);

            // Negative literal
            for (auto it = contagiousOccurrenceList_.begin(negLiteralT); it != contagiousOccurrenceList_.end(negLiteralT); ++it)
                l_computeConnectedComponents_processComputeConnectedComponents_.addConnection(l_watchedVariableVector_processComputeConnectedComponents_[*it], var);
        }

        /*
        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            assert(this->isClauseUnresolved(clauseId));   // clause is unresolved

            VarT watchedVariable = getLiteralAtPositionInClause(clauseId, clauseIdWatcher_[clauseId]).getVariable();

            assert(Other::containInSet(currentComponentVariableSet, watchedVariable));   // variable in the current component

            for (auto clauseIt = beginClause(clauseId); clauseIt != this->endClause(); ++clauseIt) {
                VarT var = clauseIt->getVariable();

                assert(Other::containInSet(currentComponentVariableSet, var));   // variable in the current component

                l_computeConnectedComponents_processComputeConnectedComponents_.addConnection(watchedVariable, var);
            }
        }
        */

        return l_computeConnectedComponents_processComputeConnectedComponents_.computeConnectedComponents(currentComponentVariableSet);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::ConnectedComponentType
    ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::processComputeConnectedComponents(const VariableSetType& currentComponentVariableSet,
                                                                                                  ClauseIdSetType& pureClauseSet,
                                                                                                  IgnorePureLiteralTypeEnum ignorePureLiteralType) {
        assert(pureClauseSet.empty());
        assert(l_computeConnectedComponents_processComputeConnectedComponents_.isEmpty());   // data structure is empty

        // TODO l_watchedVariableVector_processComputeConnectedComponents_

        pureClauseSet = ClauseIdSetType(currentComponentClausesFixedVector_.size());

        MappingFromVariableToVariableSetType mappingFromWatcherToPureVariableSet(currentComponentVariableSet.size());

        // Get the pure variables
        VariableSetType pureVariableSet(currentComponentVariableSet.size());
        for (VarT var : currentComponentVariableSet) {
            if (this->isPureLiteralInCurrentFormula(var, ignorePureLiteralType))
                pureVariableSet.emplace(var);
        }

        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            assert(this->isClauseUnresolved(clauseId));   // clause is unresolved

            VarT watchedVariable = getLiteralAtPositionInClause(clauseId, clauseIdWatcher_[clauseId]).getVariable();

            // Invalid watcher
            if (Other::containInSet(pureVariableSet, watchedVariable)) {
                // Pure clause
                if (!updateClauseWatcher(clauseId, ignorePureLiteralType)) {
                    pureClauseSet.emplace(clauseId);

                    continue;
                }

                watchedVariable = getLiteralAtPositionInClause(clauseId, clauseIdWatcher_[clauseId]).getVariable();
            }

            assert(Other::containInSet(currentComponentVariableSet, watchedVariable));   // variable in the current component

            for (auto clauseIt = beginClause(clauseId); clauseIt != this->endClause(); ++clauseIt) {
                VarT var = clauseIt->getVariable();

                assert(Other::containInSet(currentComponentVariableSet, var));   // variable in the current component

                // Pure variable
                if (Other::containInSet(pureVariableSet, var)) {
                    if (auto itTmp = mappingFromWatcherToPureVariableSet.find(watchedVariable); itTmp != mappingFromWatcherToPureVariableSet.end())
                        itTmp->second.emplace(var);
                    else {
                        mappingFromWatcherToPureVariableSet[watchedVariable] = VariableSetType(currentComponentVariableSet.size());
                        mappingFromWatcherToPureVariableSet[watchedVariable].emplace(var);
                    }

                    continue;
                }

                l_computeConnectedComponents_processComputeConnectedComponents_.addConnection(watchedVariable, var);
            }
        }

        ConnectedComponentType connectedComponents = l_computeConnectedComponents_processComputeConnectedComponents_.computeConnectedComponents(currentComponentVariableSet, pureVariableSet);

        VariableSetType variableSetTmp(currentComponentVariableSet.size());

        // Add pure variables to the data structure
        for (ConnectedComponentStruct& connectedComponentStruct : connectedComponents) {
            variableSetTmp.clear();

            for (VarT var : connectedComponentStruct.variableSet) {
                if (auto itTmp = mappingFromWatcherToPureVariableSet.find(var); itTmp != mappingFromWatcherToPureVariableSet.end())
                    variableSetTmp.insert(itTmp->second.cbegin(), itTmp->second.cend());
            }

            connectedComponentStruct.variableSet.insert(variableSetTmp.cbegin(), variableSetTmp.cend());

            // Pure literal vector
            connectedComponentStruct.pureLiteralVector.reserve(variableSetTmp.size());
            for (VarT var : variableSetTmp)
                connectedComponentStruct.pureLiteralVector.emplace_back(var, this->isPositivePureLiteralInCurrentFormula(var));

            #ifndef NDEBUG
            std::sort(connectedComponentStruct.pureLiteralVector.begin(), connectedComponentStruct.pureLiteralVector.end());
            #endif
        }

        return connectedComponents;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::processIsCurrentComponentFormulaKromC([[maybe_unused]] const VariableSetType& currentComponentVariableSet) const {
        assert(configuration_.recognitionTypeStruct.kromC);

        #ifndef NDEBUG
        // Check if there is no unit clause
        for (ClauseIdT clauseId : currentComponentClausesFixedVector_)
            assert(!this->isClauseUnit(clauseId));
        #endif

        // |F| = 2 * |C| => Krom-C
        if ((static_cast<FormulaSizeType>(currentComponentClausesFixedVector_.size()) * (FormulaSizeType)2) == currentComponentFormulaSize_)
            return true;

        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::processIsCurrentComponentFormulaHornC([[maybe_unused]] const VariableSetType& currentComponentVariableSet) const {
        assert(configuration_.recognitionTypeStruct.hornC);

        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            assert(clauseId < numberOfPositiveLiteralsInClauseVector_.size());

            // The clause is NOT Horn
            if (numberOfPositiveLiteralsInClauseVector_[clauseId] > 1)
                return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::processIsCurrentComponentFormulaAntiHornC([[maybe_unused]] const VariableSetType& currentComponentVariableSet) const {
        assert(configuration_.recognitionTypeStruct.antiHornC);

        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            assert(clauseId < numberOfNegativeLiteralsInClauseVector_.size());

            // The clause is NOT anti-Horn
            if (numberOfNegativeLiteralsInClauseVector_[clauseId] > 1)
                return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::processSaveCurrentComponentFormulaToVector(const VariableSetType& currentComponentVariableSet,
                                                                                                                LiteralVectorType& formula,
                                                                                                                ClauseOffsetVectorType& clauseOffsetVector,
                                                                                                                bool sort) const {
        // Formula
        formula.reserve(getCurrentComponentFormulaSize(currentComponentVariableSet) + (FormulaSizeType)getNumberOfCurrentComponentClauses(currentComponentVariableSet));

        // Offsets
        clauseOffsetVector.reserve(getNumberOfCurrentComponentClauses(currentComponentVariableSet));

        FormulaSizeType currentIndex = 0;
        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            clauseOffsetVector.emplace_back(currentIndex);   // offset

            for (auto clauseIt = (sort ? beginSortedClause(clauseId) : beginClause(clauseId));
                 clauseIt != (sort ? this->endSortedClause() : this->endClause()); ++clauseIt) {
                formula.push_back(*clauseIt);
                ++currentIndex;
            }

            // The end of the clause
            formula.push_back(std::move(createZeroLiteral<VarT, LiteralT>()));
            ++currentIndex;
        }

        assert(currentIndex == getCurrentComponentFormulaSize(currentComponentVariableSet) + (FormulaSizeType)getNumberOfCurrentComponentClauses(currentComponentVariableSet));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::ClauseSizeType
    ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getMaxOriginalClauseSize() const noexcept {
        return maxOriginalClauseSize_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    const typename ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::LiteralType&
    ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getLiteralAtPositionInClause(ClauseIdT clauseId, ClauseSizeType position) const {
        assert(clauseId < this->numberOfOriginalClauses_);
        assert(position < originalClauseSize_[clauseId]);

        return originalFormula_[originalClauseOffset_[clauseId] + position];
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseStatusEnum ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getCurrentClauseStatus(ClauseIdT clauseId) const {
        assert(clauseId < this->numberOfOriginalClauses_);

        // SATISFIED
        if (clauseNumberOfSatisfiedLiterals_[clauseId] > 0)
            return ClauseStatusEnum::SATISFIED;

        switch (originalClauseSize_[clauseId] - clauseNumberOfUnsatisfiedLiterals_[clauseId]) {
            // EMPTY
            case 0:
                return ClauseStatusEnum::EMPTY;
            // UNIT_CLAUSE
            case 1:
                return ClauseStatusEnum::UNIT_CLAUSE;
            // UNRESOLVED
            default:
                return ClauseStatusEnum::UNRESOLVED;
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::ClauseSizeType
    ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getCurrentClauseSize(ClauseIdT clauseId) const {
        assert(clauseId < this->numberOfOriginalClauses_);
        assert(!this->isClauseSatisfied(clauseId));   // clause is not satisfied

        return originalClauseSize_[clauseId] - clauseNumberOfUnsatisfiedLiterals_[clauseId];
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::isClauseUntouched(ClauseIdT clauseId) const {
        assert(clauseId < this->numberOfOriginalClauses_);

        return (clauseNumberOfSatisfiedLiterals_[clauseId] + clauseNumberOfUnsatisfiedLiterals_[clauseId]) == 0;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::isLiteralInUnitClause(const LiteralType& lit) const {
        assert(!this->isVariableAssigned(lit.getVariable()));           // variable is not assigned
        assert(isVariableInCurrentComponentDebug(lit.getVariable()));   // variable is in the current component

        for (auto it = contagiousOccurrenceList_.begin(lit.getLiteralT()); it != contagiousOccurrenceList_.end(lit.getLiteralT()); ++it) {
            // Unit clause
            if (getCurrentClauseSize(*it) == 1)
                return true;
        }

        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::isVariableFree(VarT var) const {
        assert(!this->isVariableAssigned(var));           // variable is not assigned
        assert(isVariableInCurrentComponentDebug(var));   // variable is in the current component

        // Positive literal
        if (getNumberOfCurrentClauses(getPositiveLiteralT<VarT, LiteralT>(var)) > 0)
            return false;

        // Negative literal
        if (getNumberOfCurrentClauses(getNegativeLiteralT<VarT, LiteralT>(var)) > 0)
            return false;

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::isVariableSingleton(VarT var) const {
        assert(!this->isVariableFree(var));               // variable is not free
        assert(!this->isVariableAssigned(var));           // variable is not assigned
        assert(isVariableInCurrentComponentDebug(var));   // variable is in the current component

        ClauseIdT numberOfOccurrences = getNumberOfCurrentClauses(getPositiveLiteralT<VarT, LiteralT>(var)) +
                                        getNumberOfCurrentClauses(getNegativeLiteralT<VarT, LiteralT>(var));

        return (numberOfOccurrences == 1);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseIdT ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getNumberOfCurrentClauses(LiteralT literalT) const {
        assert(!this->isVariableAssigned(createLiteralFromLiteralT<VarT, LiteralT>(literalT).getVariable()));           // variable is not assigned
        assert(isVariableInCurrentComponentDebug(createLiteralFromLiteralT<VarT, LiteralT>(literalT).getVariable()));   // variable is in the current component

        return contagiousOccurrenceList_.getNumberOfOccurrences(literalT);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::ClauseSizeCounterType
    ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getCurrentClauseSizeCounter(LiteralT literalT) const {
        assert(!this->isVariableAssigned(createLiteralFromLiteralT<VarT, LiteralT>(literalT).getVariable()));           // variable is not assigned
        assert(isVariableInCurrentComponentDebug(createLiteralFromLiteralT<VarT, LiteralT>(literalT).getVariable()));   // variable is in the current component

        ClauseSizeCounterType clauseSizeCounter(this->S_ESTIMATED_NUMBER_OF_CLAUSE_SIZES_);

        for (auto it = contagiousOccurrenceList_.begin(literalT); it != contagiousOccurrenceList_.end(literalT); ++it) {
            ClauseSizeType clauseSize = getCurrentClauseSize(*it);

            if (auto itTmp = clauseSizeCounter.find(clauseSize); itTmp != clauseSizeCounter.end())
                ++(itTmp->second);
            else
                clauseSizeCounter[clauseSize] = 1;
        }

        return clauseSizeCounter;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseIdT ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getNumberOfCurrentBinaryClauses(LiteralT literalT) const {
        assert(!this->isVariableAssigned(createLiteralFromLiteralT<VarT, LiteralT>(literalT).getVariable()));           // variable is not assigned
        assert(isVariableInCurrentComponentDebug(createLiteralFromLiteralT<VarT, LiteralT>(literalT).getVariable()));   // variable is in the current component

        ClauseIdT numberOfBinaryClauses = 0;

        for (auto it = contagiousOccurrenceList_.begin(literalT); it != contagiousOccurrenceList_.end(literalT); ++it) {
            ClauseSizeType clauseSize = getCurrentClauseSize(*it);

            if (clauseSize == 2)
                ++numberOfBinaryClauses;
        }

        return numberOfBinaryClauses;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    FormulaSizeType ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getCurrentComponentFormulaSize([[maybe_unused]] const VariableSetType& currentComponentVariableSet) const noexcept {
        return currentComponentFormulaSize_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::PureVariableRemovedClausesVectorType
    ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::setNewComponent(const ConnectedComponentStruct& newConnectedComponentStruct,
                                                                                IgnorePureLiteralTypeEnum ignorePureLiteralType) {
        assert(!currentComponentClausesFixedVector_.empty());   // at least one current clause

        #ifndef NDEBUG
        for (VarT var : newConnectedComponentStruct.variableSet)
            assert(isVariableInCurrentComponentDebug(var));

        d_currentComponentVariableSetStack_.push_back(newConnectedComponentStruct.variableSet);
        #endif

        currentComponentClausesStack_.emplace_back(static_cast<ClauseIdT>(currentComponentClausesFixedVector_.size()));

        bool usedIgnoredPureVariables = !newConnectedComponentStruct.pureLiteralVector.empty();
        ClauseIdSetType newCurrentComponentClauseSet(usedIgnoredPureVariables ? currentComponentClausesFixedVector_.size() : 0);

        std::size_t i = 0;

        while (true) {
            if (i == currentComponentClausesFixedVector_.size())
                break;

            ClauseIdT clauseId = currentComponentClausesFixedVector_[i];

            VarT watchedVariable = getLiteralAtPositionInClause(clauseId, clauseIdWatcher_[clauseId]).getVariable();

            // The clause is out of the new component
            if (!Other::containInSet(newConnectedComponentStruct.variableSet, watchedVariable) ||
                this->isPureLiteralInCurrentFormula(watchedVariable, ignorePureLiteralType)) {
                currentComponentFormulaSize_ -= getCurrentClauseSize(clauseId);
                currentComponentClausesFixedVector_.swap(i);
                currentComponentClausesFixedVector_.decreaseNumberOfActiveElements();
            }
            // The clause is in the new component
            else {
                assert(!this->isPureLiteralInCurrentFormula(watchedVariable, ignorePureLiteralType));   // watcher is not an ignored pure variable

                if (usedIgnoredPureVariables)
                    newCurrentComponentClauseSet.emplace(clauseId);

                ++i;
            }
        }

        // No ignored pure variables
        if (!usedIgnoredPureVariables)
            return {};

        PureVariableRemovedClausesVectorType pureVariableRemovedClausesVector;
        pureVariableRemovedClausesVector.reserve(newConnectedComponentStruct.pureLiteralVector.size());

        // Occurrence list
        for (const LiteralType& lit : newConnectedComponentStruct.pureLiteralVector) {
            pureVariableRemovedClausesVector.push_back(contagiousOccurrenceList_.removeOccurrence(lit.getLiteralT(), newCurrentComponentClauseSet));
        }

        assert(pureVariableRemovedClausesVector.size() == newConnectedComponentStruct.pureLiteralVector.size());

        return pureVariableRemovedClausesVector;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::popPreviousComponent(const ConnectedComponentStruct& currentConnectedComponentStruct,
                                                                                          const PureVariableRemovedClausesVectorType& pureVariableRemovedClausesVector) {
        #ifndef NDEBUG
        assert(!d_currentComponentVariableSetStack_.empty());
        assert(d_currentComponentVariableSetStack_.back() == currentConnectedComponentStruct.variableSet);
        assert(currentConnectedComponentStruct.pureLiteralVector.size() == pureVariableRemovedClausesVector.size());

        d_currentComponentVariableSetStack_.pop_back();
        #endif

        ClauseIdT previousSize = static_cast<ClauseIdT>(currentComponentClausesFixedVector_.size());

        // Current component clauses
        currentComponentClausesFixedVector_.changeNumberOfActiveElements(currentComponentClausesStack_.back());
        currentComponentClausesStack_.pop_back();

        for (ClauseIdT i = previousSize; i < currentComponentClausesFixedVector_.size(); ++i)
            currentComponentFormulaSize_ += getCurrentClauseSize(currentComponentClausesFixedVector_[i]);

        // Occurrence list
        for (VarT i = 0; i < currentConnectedComponentStruct.pureLiteralVector.size(); ++i) {
            LiteralT literalT = currentConnectedComponentStruct.pureLiteralVector[i].getLiteralT();

            for (ClauseIdT clauseId : pureVariableRemovedClausesVector[i])
                contagiousOccurrenceList_.addOccurrence(literalT, clauseId);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseIdT ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getNumberOfCurrentComponentClauses([[maybe_unused]] const VariableSetType& currentComponentVariableSet) const noexcept {
        return static_cast<ClauseIdT>(currentComponentClausesFixedVector_.size());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getCurrentComponentClauses([[maybe_unused]] const VariableSetType& currentComponentVariableSet,
                                                                                                ClauseIdReusableVectorType& clauseIdReusableVector,
                                                                                                bool sortIds) const {
        clauseIdReusableVector.clear();

        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            assert(this->isClauseUnresolved(clauseId));   // clause is unresolved

            clauseIdReusableVector.emplace_back(clauseId);
        }

        if (sortIds)
            clauseIdReusableVector.sort();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getCurrentComponentNotDuplicateClauses([[maybe_unused]] const VariableSetType& currentComponentVariableSet,
                                                                                                            ClauseIdReusableVectorType& clauseIdReusableVector,
                                                                                                            bool considerOnlyVariables, bool sortIds) const {
        clauseIdReusableVector.copyVector(currentComponentClausesFixedVector_);

        // Remove the duplicate clauses and sort the clauses
        removeDuplicateClausesFromClauseIdReusableVector(clauseIdReusableVector, considerOnlyVariables, false);

        if (sortIds)
            clauseIdReusableVector.sort();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getSortedCurrentComponentClauses([[maybe_unused]] const VariableSetType& currentComponentVariableSet,
                                                                                                      ClauseIdReusableVectorType& clauseIdReusableVector,
                                                                                                      bool removeDuplicateClauses, bool considerOnlyVariables,
                                                                                                      OmitClauseTypeEnum omitClauseType) const {
        sortClauses(clauseIdReusableVector, removeDuplicateClauses, VectorSetType(), considerOnlyVariables, omitClauseType);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getCurrentComponentNotSubsumedClauses([[maybe_unused]] const VariableSetType& currentComponentVariableSet,
                                                                                                           ClauseIdReusableVectorType& clauseIdReusableVector,
                                                                                                           VectorSetType& usedVariableVectorSet, bool fillUsedVariables,
                                                                                                           bool considerOnlyVariables, bool sortIds) const {
        // Initialize local auxiliary data structures
        if (l_firstCall_getCurrentComponentNotSubsumedClauses_) {
            l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_ = VectorSetType(this->getNumberOfOriginalClauses());

            l_firstCall_getCurrentComponentNotSubsumedClauses_ = false;
        }

        l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_.clear();

        switch (configuration_.subsumptionType) {
            case SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION:
                backwardSubsumptionDetection(l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_, considerOnlyVariables);
                break;
            case SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION:
                backwardSubsumptionDetectionIntersection(l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_, considerOnlyVariables);
                break;
            case SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION:
                forwardSubsumptionDetection(l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_, considerOnlyVariables);
                break;
            case SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM:
                if (considerOnlyVariables)
                    oneLiteralWatchingAlgorithmVariableSubsumption(l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_);
                else
                    oneLiteralWatchingAlgorithmSubsumption(l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_);
                break;
            default:
                throw Exception::NotImplementedException(subsumptionTypeEnumToString(configuration_.subsumptionType),
                                                         "Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation::getCurrentComponentNotSubsumedClauses");
        }

        clauseIdReusableVector.clear();
        if (fillUsedVariables)
            usedVariableVectorSet.clear();

        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            // The clause is subsumed
            if (l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_.contains(clauseId))
                continue;

            clauseIdReusableVector.emplace_back(clauseId);

            // Update the used variables
            if (fillUsedVariables) {
                for (auto clauseIt = beginClause(clauseId); clauseIt != this->endClause(); ++clauseIt)
                    usedVariableVectorSet.emplace(clauseIt->getVariable(), false);
            }
        }

        if (sortIds)
            clauseIdReusableVector.sort();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getSortedCurrentComponentNotSubsumedClauses([[maybe_unused]] const VariableSetType& currentComponentVariableSet,
                                                                                                                 ClauseIdReusableVectorType& clauseIdReusableVector) const {
        // Initialize local auxiliary data structures
        if (l_firstCall_getCurrentComponentNotSubsumedClauses_) {
            l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_ = VectorSetType(this->getNumberOfOriginalClauses());

            l_firstCall_getCurrentComponentNotSubsumedClauses_ = false;
        }

        l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_.clear();

        switch (configuration_.subsumptionType) {
            case SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION:
                backwardSubsumptionDetection(l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_, false);
                break;
            case SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION:
                backwardSubsumptionDetectionIntersection(l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_, false);
                break;
            case SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION:
                forwardSubsumptionDetection(l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_, false);
                break;
            case SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM:
                oneLiteralWatchingAlgorithmSubsumption(l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_);
                break;
            default:
                throw Exception::NotImplementedException(subsumptionTypeEnumToString(configuration_.subsumptionType),
                                                         "Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation::getSortedCurrentComponentNotSubsumedClauses");
        }

        sortClauses(clauseIdReusableVector, false, l_subsumedClauseVectorSet_getCurrentComponentNotSubsumedClauses_, false, OmitClauseTypeEnum::NONE);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getCurrentComponentClausesThatVariableSubsumeSomeClause([[maybe_unused]] const VariableSetType& currentComponentVariableSet,
                                                                                                                             VectorSetType& clauseThatVariableSubsumesSomeClauseVectorSet,
                                                                                                                             const VariableVectorMapType& variableVectorMap,
                                                                                                                             IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                                                                                                             VertexWeightTypeEnum vertexWeightType,
                                                                                                                             VertexWeightVectorType& vertexWeightVector) const {
        // Set the vertex weights
        if (PartitioningHypergraph::isVertexWeightUsed(vertexWeightType)) {
            assert(vertexWeightType != VertexWeightTypeEnum::NONE);

            for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
                assert(clauseId < vertexWeightVector.size());

                switch (vertexWeightType) {
                    case VertexWeightTypeEnum::STANDARD:
                        vertexWeightVector[clauseId] = 1;
                        break;
                    case VertexWeightTypeEnum::CLAUSE_LENGTH:
                        vertexWeightVector[clauseId] = 1 + static_cast<VertexWeightType>(maxOriginalClauseSize_ - getCurrentClauseSize(clauseId));
                        break;
                    default:
                        throw Exception::NotImplementedException(PartitioningHypergraph::vertexWeightTypeEnumToString(vertexWeightType),
                                                                 "Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation::getCurrentComponentClausesThatVariableSubsumeSomeClause");
                }
            }
        }

        clauseThatVariableSubsumesSomeClauseVectorSet.clear();

        switch (configuration_.variableSubsumptionWithMappingType) {
            case VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION:
                forwardVariableSubsumptionWithMappingDetection(clauseThatVariableSubsumesSomeClauseVectorSet,
                                                               variableVectorMap, ignorePureLiteralType, vertexWeightType, vertexWeightVector);
                break;
            case VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING:
                oneLiteralWatchingAlgorithmVariableSubsumptionWithMapping(clauseThatVariableSubsumesSomeClauseVectorSet,
                                                                          variableVectorMap, ignorePureLiteralType, vertexWeightType, vertexWeightVector);
                break;
            case VariableSubsumptionWithMappingTypeEnum::NONE:
                break;
            default:
                throw Exception::NotImplementedException(variableSubsumptionWithMappingTypeEnumToString(configuration_.variableSubsumptionWithMappingType),
                                                         "Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation::getCurrentComponentClausesThatVariableSubsumeSomeClause");
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getCurrentClauses([[maybe_unused]] const VariableSetType& currentComponentVariableSet,
                                                                                       VarT var, ClauseIdReusableVectorType& clauseIdReusableVector,
                                                                                       const VectorSetType& ignoredClauseVectorSet) const {
        assert(!this->isVariableAssigned(var));           // variable is not assigned
        assert(isVariableInCurrentComponentDebug(var));   // variable is in the current component

        bool areIgnoredClausesUsed = (ignoredClauseVectorSet.capacity() > 0);   // consider ignored clauses

        LiteralT posLiteralT = getPositiveLiteralT<VarT, LiteralT>(var);
        LiteralT negLiteralT = getNegativeLiteralT<VarT, LiteralT>(var);

        clauseIdReusableVector.clear();

        // Positive literal
        for (auto it = contagiousOccurrenceList_.begin(posLiteralT); it != contagiousOccurrenceList_.end(posLiteralT); ++it) {
            ClauseIdT clauseId = *it;

            // Ignored clause
            if (areIgnoredClausesUsed && ignoredClauseVectorSet.contains(clauseId))
                continue;

            clauseIdReusableVector.emplace_back(clauseId);
        }

        // Negative literal
        for (auto it = contagiousOccurrenceList_.begin(negLiteralT); it != contagiousOccurrenceList_.end(negLiteralT); ++it) {
            ClauseIdT clauseId = *it;

            // Ignored clause
            if (areIgnoredClausesUsed && ignoredClauseVectorSet.contains(clauseId))
                continue;

            clauseIdReusableVector.emplace_back(clauseId);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getCurrentClauses([[maybe_unused]] const VariableSetType& currentComponentVariableSet,
                                                                                       const VariableVectorType& variableVector,
                                                                                       ClauseIdReusableVectorType& clauseIdReusableVector,
                                                                                       const VectorSetType& ignoredClauseVectorSet) const {
        // Initialize local auxiliary data structures
        if (l_firstCall_getCurrentClauses_) {
            l_addedClauseVectorSet_getCurrentClauses_ = VectorSetType(this->getNumberOfOriginalClauses());

            l_firstCall_getCurrentClauses_ = false;
        }

        bool areIgnoredClausesUsed = (ignoredClauseVectorSet.capacity() > 0);   // consider ignored clauses

        clauseIdReusableVector.clear();
        l_addedClauseVectorSet_getCurrentClauses_.clear();

        for (VarT var : variableVector) {
            assert(!this->isVariableAssigned(var));           // variable is not assigned
            assert(isVariableInCurrentComponentDebug(var));   // variable is in the current component

            LiteralT posLiteralT = getPositiveLiteralT<VarT, LiteralT>(var);

            // Positive literal
            for (auto it = contagiousOccurrenceList_.begin(posLiteralT); it != contagiousOccurrenceList_.end(posLiteralT); ++it) {
                ClauseIdT clauseId = *it;

                // The clause has already been added
                if (l_addedClauseVectorSet_getCurrentClauses_.contains(clauseId))
                    continue;

                // Ignored clause
                if (areIgnoredClausesUsed && ignoredClauseVectorSet.contains(clauseId))
                    continue;

                clauseIdReusableVector.emplace_back(clauseId);
                l_addedClauseVectorSet_getCurrentClauses_.emplace(clauseId);
            }

            LiteralT negLiteralT = getNegativeLiteralT<VarT, LiteralT>(var);

            // Negative literal
            for (auto it = contagiousOccurrenceList_.begin(negLiteralT); it != contagiousOccurrenceList_.end(negLiteralT); ++it) {
                ClauseIdT clauseId = *it;

                // The clause has already been added
                if (l_addedClauseVectorSet_getCurrentClauses_.contains(clauseId))
                    continue;

                // Ignored clause
                if (areIgnoredClausesUsed && ignoredClauseVectorSet.contains(clauseId))
                    continue;

                clauseIdReusableVector.emplace_back(clauseId);
                l_addedClauseVectorSet_getCurrentClauses_.emplace(clauseId);
            }
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::VariableSetType
    ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getUnassignedVariablesInClause(ClauseIdT clauseId) const {
        assert(clauseId < this->numberOfOriginalClauses_);
        assert(!this->isClauseSatisfied(clauseId));   // clause is not satisfied

        VariableSetType variableSet(getCurrentClauseSize(clauseId));

        for (auto clauseIt = beginClause(clauseId); clauseIt != this->endClause(); ++clauseIt) {
            const LiteralType& lit = *clauseIt;

            variableSet.emplace(lit.getVariable());
        }

        return variableSet;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::printCurrentFormulaInDimacsCnfFormat(std::ostream& out, bool printProblemLine,
                                                                                                          ModelCountingTypeEnum modelCountingType) const {
        // Problem line
        if (printProblemLine)
            out << Other::Parser::PROBLEM << " " << Other::Parser::CNF_HEADER_STRING << " " << std::to_string(this->getNumberOfVariablesInOriginalFormula()) << " "
                << std::to_string(currentComponentClausesFixedVector_.size()) << std::endl;

        // Model counting header
        if (modelCountingType != ModelCountingTypeEnum::UNDEFINED)
            out << "c t " << Cara::modelCountingTypeEnumToStringViewUsedInModelCountingHeader(modelCountingType) << std::endl;

        // Formula
        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            for (auto clauseIt = beginClause(clauseId); clauseIt != this->endClause(); ++clauseIt)
                out << clauseIt->toString() << " ";

            out << "0" << std::endl;   // end of the clause
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::printSortedCurrentFormulaInDimacsCnfFormat(std::ostream& out,
                                                                                                                bool removeDuplicateClauses, bool removeSubsumedClauses,
                                                                                                                bool printProblemLine,
                                                                                                                ModelCountingTypeEnum modelCountingType) const {
        ClauseIdReusableVectorType clauseIdReusableVector(currentComponentClausesFixedVector_.size());

        if (removeSubsumedClauses)
            getSortedCurrentComponentNotSubsumedClauses({}, clauseIdReusableVector);
        else
            getSortedCurrentComponentClauses({}, clauseIdReusableVector, removeDuplicateClauses);

        // Problem line
        if (printProblemLine)
            out << Other::Parser::PROBLEM << " " << Other::Parser::CNF_HEADER_STRING << " " << std::to_string(this->getNumberOfVariablesInOriginalFormula()) << " "
                << std::to_string(clauseIdReusableVector.size()) << std::endl;

        // Model counting header
        if (modelCountingType != ModelCountingTypeEnum::UNDEFINED)
            out << "c t " << Cara::modelCountingTypeEnumToStringViewUsedInModelCountingHeader(modelCountingType) << std::endl;

        // Formula
        for (ClauseIdT clauseId : clauseIdReusableVector) {
            for (auto clauseIt = beginSortedClause(clauseId); clauseIt != this->endSortedClause(); ++clauseIt)
                out << clauseIt->toString() << " ";

            out << "0" << std::endl;   // end of the clause
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator
    ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::beginClause(ClauseIdT clauseId, [[maybe_unused]] bool checkSat) const {
        assert(clauseId < this->numberOfOriginalClauses_);

        #ifndef NDEBUG
        return typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator(&(originalFormula_[originalClauseOffset_[clauseId]]), this, clauseId, checkSat);
        #else
        return typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator(&(originalFormula_[originalClauseOffset_[clauseId]]), this);
        #endif
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator
    ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::beginSortedClause(ClauseIdT clauseId, [[maybe_unused]] bool checkSat) const {
        assert(clauseId < this->numberOfOriginalClauses_);

        #ifndef NDEBUG
        return typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator(&(originalFormula_[originalClauseOffset_[clauseId]]), this, clauseId, checkSat);
        #else
        return typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator(&(originalFormula_[originalClauseOffset_[clauseId]]), this);
        #endif
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::processPrintFormulaRepresentationDebug(std::ostream& out) const {
        out << "Original formula: ";
        for (const LiteralType& lit : originalFormula_)
            out << lit << " ";
        out << std::endl;

        out << "Original clause offset: ";
        for (FormulaSizeType originalClauseOffset : originalClauseOffset_)
            out << std::to_string(originalClauseOffset) << " ";
        out << std::endl;

        out << "Clause - number of satisfied literals: ";
        for (ClauseSizeType numberOfSatisfiedLiterals : clauseNumberOfSatisfiedLiterals_)
            out << std::to_string(numberOfSatisfiedLiterals) << " ";
        out << std::endl;

        out << "Clause - number of unsatisfied literals: ";
        for (ClauseSizeType numberOfUnsatisfiedLiterals : clauseNumberOfUnsatisfiedLiterals_)
            out << std::to_string(numberOfUnsatisfiedLiterals) << " ";
        out << std::endl;

        // Recognition of Horn-C
        if (configuration_.recognitionTypeStruct.hornC) {
            out << "Clause - number of positive literals: ";
            for (ClauseSizeType numberOfPositiveLiterals : numberOfPositiveLiteralsInClauseVector_)
                out << std::to_string(numberOfPositiveLiterals) << " ";
            out << std::endl;
        }

        // Recognition of anti-Horn-C
        if (configuration_.recognitionTypeStruct.antiHornC) {
            out << "Clause - number of negative literals: ";
            for (ClauseSizeType numberOfNegativeLiterals : numberOfNegativeLiteralsInClauseVector_)
                out << std::to_string(numberOfNegativeLiterals) << " ";
            out << std::endl;
        }

        out << "Original clause size: ";
        for (ClauseSizeType clauseSize : originalClauseSize_)
            out << std::to_string(clauseSize) << " ";
        out << std::endl;

        out << "Clause watcher: ";
        for (ClauseSizeType idWatcher : clauseIdWatcher_)
            out << std::to_string(idWatcher) << " ";
        out << std::endl;

        out << "Current component formula size: " << std::to_string(currentComponentFormulaSize_) << std::endl;

        out << "Current component variable set (stack): " << std::endl;
        for (const VariableSetType& currentComponentVariableSet : d_currentComponentVariableSetStack_) {
            VariableSortedVectorType currentComponentVariableSortedVector = Other::sortUnorderedSet(currentComponentVariableSet);
            out << "\t";
            for (VarT var : currentComponentVariableSortedVector)
                out << std::to_string(var) << " ";
            out << std::endl;
        }

        // Occurrence list
        contagiousOccurrenceList_.printContagiousOccurrenceListDebug(out);

        // Current component clauses
        out << "Current component clauses (fixed vector):" << std::endl;
        currentComponentClausesFixedVector_.printFixedVectorDebug(out);

        // Current component clauses - stack
        out << "Current component clauses (stack): ";
        for (ClauseIdT clauseId : currentComponentClausesStack_)
            out << std::to_string(clauseId) << " ";
        out << std::endl;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::isVariableInCurrentComponentDebug(VarT var) const {
        assert(!d_currentComponentVariableSetStack_.empty());

        return Other::containInSet(d_currentComponentVariableSetStack_.back(), var);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::printCurrentClauseDebug(std::ostream& out, ClauseIdT clauseId,
                                                                                             bool considerOnlyVariables) const {
        for (auto clauseIt = beginSortedClause(clauseId); clauseIt != this->endSortedClause(); ++clauseIt) {
            // Variables
            if (considerOnlyVariables)
                out << std::to_string(clauseIt->getVariable()) << " ";
            // Literals
            else
                out << clauseIt->toString() << " ";
        }
        out << "0 ";
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::printCurrentFormulaDebug(std::ostream& out, bool removeDuplicateClauses,
                                                                                              bool removeSubsumedClauses) const {
        ClauseIdReusableVectorType clauseIdReusableVector(currentComponentClausesFixedVector_.size());

        if (removeSubsumedClauses)
            getSortedCurrentComponentNotSubsumedClauses({}, clauseIdReusableVector);
        else
            getSortedCurrentComponentClauses({}, clauseIdReusableVector, removeDuplicateClauses);

        for (ClauseIdT clauseId : clauseIdReusableVector)
            printCurrentClauseDebug(out, clauseId);
    }
    #endif
}   // namespace Hydra::Formula::Representation::Contagious
