#pragma once

#include "./ContagiousFormulaRepresentation.hpp"

namespace Hydra::Formula::Representation::Contagious {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::clauseSubsumesClause(ClauseIdT clauseId1, ClauseIdT clauseId2) const {
        assert(clauseId1 < this->numberOfOriginalClauses_);
        assert(clauseId2 < this->numberOfOriginalClauses_);
        assert(this->isClauseUnresolved(clauseId1));   // clause is unresolved
        assert(this->isClauseUnresolved(clauseId2));   // clause is unresolved

        // Clause_2 has fewer literals than Clause_1
        if (getCurrentClauseSize(clauseId2) < getCurrentClauseSize(clauseId1))
            return false;

        auto clause1It = beginSortedClause(clauseId1);
        auto clause2It = beginSortedClause(clauseId2);
        auto clauseEndIt = this->endSortedClause();

        while ((clause1It != clauseEndIt) && (clause2It != clauseEndIt)) {
            const LiteralType& lit1 = *clause1It;
            const LiteralType& lit2 = *clause2It;

            if (lit1 == lit2) {
                ++clause1It;
                ++clause2It;
                continue;
            }

            if (lit1 > lit2) {
                ++clause2It;
                continue;
            }

            // lit1 < lit2
            return false;
        }

        if (clause1It == clauseEndIt)
            return true;

        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::clauseVariableSubsumesClause(ClauseIdT clauseId1, ClauseIdT clauseId2) const {
        assert(clauseId1 < this->numberOfOriginalClauses_);
        assert(clauseId2 < this->numberOfOriginalClauses_);
        assert(this->isClauseUnresolved(clauseId1));   // clause is unresolved
        assert(this->isClauseUnresolved(clauseId2));   // clause is unresolved

        // Clause_2 has fewer literals than Clause_1
        if (getCurrentClauseSize(clauseId2) < getCurrentClauseSize(clauseId1))
            return false;

        auto clause1It = beginSortedClause(clauseId1);
        auto clause2It = beginSortedClause(clauseId2);
        auto clauseEndIt = this->endSortedClause();

        while ((clause1It != clauseEndIt) && (clause2It != clauseEndIt)) {
            VarT var1 = clause1It->getVariable();
            VarT var2 = clause2It->getVariable();

            if (var1 == var2) {
                ++clause1It;
                ++clause2It;
                continue;
            }

            if (var1 > var2) {
                ++clause2It;
                continue;
            }

            // var1 < var2
            return false;
        }

        if (clause1It == clauseEndIt)
            return true;

        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::backwardSubsumptionDetectionIntersection(VectorSetType& subsumedClauseVectorSet,
                                                                                                              bool considerOnlyVariables) const {
        assert(subsumedClauseVectorSet.empty());

        ClauseIdT numberOfClauses = static_cast<ClauseIdT>(currentComponentClausesFixedVector_.size());

        // Auxiliary data structures
        ClauseIdSetType newClauseIdSet(numberOfClauses);
        ClauseIdSetType currentClauseIdSet(numberOfClauses);

        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            assert(this->isClauseUnresolved(clauseId));   // clause is unresolved

            // The clause has already been detected as (variable) subsumed
            if (subsumedClauseVectorSet.contains(clauseId))
                continue;

            newClauseIdSet.clear();
            currentClauseIdSet.clear();
            bool firstIteration = true;

            // Clause iterating
            for (auto clauseIt = beginClause(clauseId); clauseIt != this->endClause(); ++clauseIt) {
                const LiteralType& lit = *clauseIt;

                // Occurrence list iterating
                for (auto it = contagiousOccurrenceList_.begin(lit.getLiteralT()); it != contagiousOccurrenceList_.end(lit.getLiteralT()); ++it) {
                    if (*it == clauseId)
                        continue;

                    // The clause has already been detected as (variable) subsumed
                    if (subsumedClauseVectorSet.contains(*it))
                        continue;

                    if (firstIteration || Other::containInSet(currentClauseIdSet, *it))
                        newClauseIdSet.emplace(*it);
                }

                // Variable subsumption
                // The complementary literal
                if (considerOnlyVariables) {
                    LiteralT complementaryLiteralT = lit.getComplementaryLiteralT();

                    // Occurrence list iterating
                    for (auto it = contagiousOccurrenceList_.begin(complementaryLiteralT); it != contagiousOccurrenceList_.end(complementaryLiteralT); ++it) {
                        // if (*it == clauseId)
                        //     continue;

                        // The clause has already been detected as variable subsumed
                        if (subsumedClauseVectorSet.contains(*it))
                            continue;

                        if (firstIteration || Other::containInSet(currentClauseIdSet, *it))
                            newClauseIdSet.emplace(*it);
                    }
                }

                currentClauseIdSet = std::move(newClauseIdSet);
                newClauseIdSet.clear();

                // No (variable) subsumed clauses
                if (currentClauseIdSet.empty())
                    break;

                firstIteration = false;
            }

            // ClauseSizeType clauseSize = getCurrentClauseSize(clauseId);

            for (ClauseIdT subsumedClauseId : currentClauseIdSet) {
                // Because of duplicate clauses
                // if (clauseSize != getCurrentClauseSize(subsumedClauseId))
                subsumedClauseVectorSet.emplace(subsumedClauseId);
            }
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::backwardSubsumptionDetection(VectorSetType& subsumedClauseVectorSet,
                                                                                                  bool considerOnlyVariables) const {
        assert(subsumedClauseVectorSet.empty());

        ClauseIdT numberOfClauses = static_cast<ClauseIdT>(currentComponentClausesFixedVector_.size());

        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            assert(this->isClauseUnresolved(clauseId));   // clause is unresolved

            // The clause has already been detected as (variable) subsumed
            if (subsumedClauseVectorSet.contains(clauseId))
                continue;

            // Find a literal/variable with the smallest number of occurrences
            LiteralT minLiteralT = 0;
            LiteralT minComplementaryLiteralT = 0;
            ClauseIdT minNumberOfOccurrences = numberOfClauses;

            for (auto clauseIt = beginClause(clauseId); clauseIt != this->endClause(); ++clauseIt) {
                const LiteralType& lit = *clauseIt;

                ClauseIdT numberOfOccurrencesTmp = 0;

                if (considerOnlyVariables)
                    numberOfOccurrencesTmp = contagiousOccurrenceList_.getNumberOfVariableOccurrences(lit.getVariable());
                else
                    numberOfOccurrencesTmp = contagiousOccurrenceList_.getNumberOfOccurrences(lit.getLiteralT());

                if (numberOfOccurrencesTmp <= minNumberOfOccurrences) {
                    minNumberOfOccurrences = numberOfOccurrencesTmp;
                    minLiteralT = lit.getLiteralT();
                    minComplementaryLiteralT = lit.getComplementaryLiteralT();
                }
            }

            assert(minLiteralT != 0);                // minLiteralT has been set
            assert(minComplementaryLiteralT != 0);   // minComplementaryLiteralT has been set

            // Occurrence list iterating
            for (auto it = contagiousOccurrenceList_.begin(minLiteralT); it != contagiousOccurrenceList_.end(minLiteralT); ++it) {
                if (*it == clauseId)
                    continue;

                // The clause has already been detected as (variable) subsumed
                if (subsumedClauseVectorSet.contains(*it))
                    continue;

                // Variable subsumption
                if (considerOnlyVariables) {
                    if (clauseVariableSubsumesClause(clauseId, *it))
                        subsumedClauseVectorSet.emplace(*it);
                }
                // Subsumption
                else {
                    if (clauseSubsumesClause(clauseId, *it))
                        subsumedClauseVectorSet.emplace(*it);
                }
            }

            // Variable subsumption
            // The complementary literal
            if (considerOnlyVariables) {
                // Occurrence list iterating
                for (auto it = contagiousOccurrenceList_.begin(minComplementaryLiteralT); it != contagiousOccurrenceList_.end(minComplementaryLiteralT); ++it) {
                    // if (*it == clauseId)
                    //     continue;

                    // The clause has already been detected as (variable) subsumed
                    if (subsumedClauseVectorSet.contains(*it))
                        continue;

                    if (clauseVariableSubsumesClause(clauseId, *it))
                        subsumedClauseVectorSet.emplace(*it);
                }
            }
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::forwardSubsumptionDetection(VectorSetType& subsumedClauseVectorSet,
                                                                                                 bool considerOnlyVariables) const {
        assert(subsumedClauseVectorSet.empty());

        for (ClauseIdT clauseId1 : currentComponentClausesFixedVector_) {
            assert(this->isClauseUnresolved(clauseId1));   // clause is unresolved

            for (ClauseIdT clauseId2 : currentComponentClausesFixedVector_) {
                assert(this->isClauseUnresolved(clauseId2));   // clause is unresolved

                if (clauseId1 == clauseId2)
                    continue;

                // Transitivity
                if (subsumedClauseVectorSet.contains(clauseId2))
                    continue;

                // Variable subsumption
                if (considerOnlyVariables) {
                    if (clauseVariableSubsumesClause(clauseId2, clauseId1)) {
                        subsumedClauseVectorSet.emplace(clauseId1);
                        break;
                    }
                }
                // Subsumption
                else {
                    if (clauseSubsumesClause(clauseId2, clauseId1)) {
                        subsumedClauseVectorSet.emplace(clauseId1);
                        break;
                    }
                }
            }
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::oneLiteralWatchingAlgorithmSubsumption(VectorSetType& subsumedClauseVectorSet) const {
        assert(subsumedClauseVectorSet.empty());

        // Initialize local auxiliary data structures
        if (l_firstCall_oneLiteralWatchingAlgorithmSubsumption_) {
            l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_ = VectorSetType(this->getNumberOfOriginalClauses());
            l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_ = ClauseSizeVectorType(this->getNumberOfOriginalClauses(), 0);

            l_firstCall_oneLiteralWatchingAlgorithmSubsumption_ = false;
        }

        // Initialize local auxiliary data structures
        if (l_firstCall_oneLiteralWatchingAlgorithmLiteralSubsumption_) {
            l_forbiddenLiteralTSet_oneLiteralWatchingAlgorithmLiteralSubsumption_ = LiteralTSetType(maxOriginalClauseSize_);
            l_removeLiteralTSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmLiteralSubsumption_ = VectorSetType(getNegativeLiteralT<VarT, LiteralT>(this->getNumberOfVariablesInOriginalFormula()));
            l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_ = SubsumptionWatcherVectorType(getNegativeLiteralT<VarT, LiteralT>(this->getNumberOfVariablesInOriginalFormula()), ClauseIdVectorType());

            // Reserve the literal watcher
            for (ClauseIdVectorType& clauseIdVector : l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_)
                clauseIdVector.reserve(S_ESTIMATED_NUMBER_OF_WATCHED_CLAUSES_FOR_SUBSUMPTION_);

            l_firstCall_oneLiteralWatchingAlgorithmLiteralSubsumption_ = false;
        }

        // Clear the literal watcher
        for (std::size_t index : l_removeLiteralTSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmLiteralSubsumption_.getAddedElementVector())
            l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_[index].clear();
        l_removeLiteralTSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmLiteralSubsumption_.clear();

        #ifndef NDEBUG
        // Check the literal watcher is empty
        for (const ClauseIdVectorType& clauseIdVector : l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_)
            assert(clauseIdVector.empty());
        #endif

        // Initialize the watcher
        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            ClauseSizeType indexTmp = getIndexOfUnassignedLiteralInClause(clauseId);
            LiteralT literalTTmp = getLiteralAtPositionInClause(clauseId, indexTmp).getLiteralT();

            // Index watcher
            l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_[clauseId] = indexTmp;

            // Literal watcher
            l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_[literalTTmp - 1].emplace_back(clauseId);   // "-1" due to indexing
            l_removeLiteralTSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmLiteralSubsumption_.emplace(literalTTmp - 1, false);
        }

        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            if (isClauseSubsumedOneLiteralWatchingAlgorithmSubsumption(clauseId, subsumedClauseVectorSet))
                subsumedClauseVectorSet.emplace(clauseId);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::isClauseSubsumedOneLiteralWatchingAlgorithmSubsumption(ClauseIdT clauseId,
                                                                                                                            const VectorSetType& subsumedClauseVectorSet) const {
        ClauseSizeType clauseSize = getCurrentClauseSize(clauseId);
        l_forbiddenLiteralTSet_oneLiteralWatchingAlgorithmLiteralSubsumption_.clear();

        for (auto clauseIt = beginClause(clauseId); clauseIt != this->endClause(); ++clauseIt) {
            LiteralT literalT = clauseIt->getLiteralT();
            l_forbiddenLiteralTSet_oneLiteralWatchingAlgorithmLiteralSubsumption_.emplace(literalT);

            // No update needed
            if (l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_[literalT - 1].empty())
                continue;

            l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_.clear();

            for (ClauseIdT clauseIdTmp : l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_[literalT - 1]) {
                if (clauseId == clauseIdTmp)
                    continue;

                // Transitivity
                if (subsumedClauseVectorSet.contains(clauseIdTmp))
                    continue;

                if (getCurrentClauseSize(clauseIdTmp) > clauseSize)
                    continue;

                // The watcher cannot be updated
                if (!updateWatcherOneLiteralWatchingAlgorithmSubsumption(clauseIdTmp)) {
                    Other::smartRemoveElementsFromVector(l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_[literalT - 1], l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_);
                    return true;
                }
                // The watcher has been updated
                else
                    l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_.emplace(clauseIdTmp);
            }

            Other::smartRemoveElementsFromVector(l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_[literalT - 1],
                                                 l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_);
        }

        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::updateWatcherOneLiteralWatchingAlgorithmSubsumption(ClauseIdT clauseId) const {
        ClauseSizeType index = l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_[clauseId];
        LiteralT oldLiteralT = getLiteralAtPositionInClause(clauseId, index).getLiteralT();
        LiteralT newLiteralT = oldLiteralT;

        assert(Other::containInVector(l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_[oldLiteralT - 1], clauseId));

        // (index + 1, endClause)
        for (ClauseSizeType i = index + 1; i < originalClauseSize_[clauseId]; ++i) {
            const LiteralType& lit = getLiteralAtPositionInClause(clauseId, i);

            // New watcher has been found
            if (!this->isVariableAssigned(lit.getVariable()) && !l_forbiddenLiteralTSet_oneLiteralWatchingAlgorithmLiteralSubsumption_.contains(lit.getLiteralT())) {
                newLiteralT = lit.getLiteralT();
                l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_[clauseId] = i;

                break;
            }
        }

        // (0, index - 1)
        if (oldLiteralT == newLiteralT) {
            for (ClauseSizeType i = 0; i < index; ++i) {
                const LiteralType& lit = getLiteralAtPositionInClause(clauseId, i);

                // New watcher has been found
                if (!this->isVariableAssigned(lit.getVariable()) && !l_forbiddenLiteralTSet_oneLiteralWatchingAlgorithmLiteralSubsumption_.contains(lit.getLiteralT())) {
                    newLiteralT = lit.getLiteralT();
                    l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_[clauseId] = i;

                    break;
                }
            }
        }

        // No literal can be used as a watcher
        if (oldLiteralT == newLiteralT)
            return false;

        // Literal watcher
        l_literalTSubsumptionWatcherVector_oneLiteralWatchingAlgorithmLiteralSubsumption_[newLiteralT - 1].emplace_back(clauseId);
        l_removeLiteralTSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmLiteralSubsumption_.emplace(newLiteralT - 1, false);

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::oneLiteralWatchingAlgorithmVariableSubsumption(VectorSetType& variableSubsumedClauseVectorSet) const {
        assert(variableSubsumedClauseVectorSet.empty());

        // Initialize local auxiliary data structures
        if (l_firstCall_oneLiteralWatchingAlgorithmSubsumption_) {
            l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_ = VectorSetType(this->getNumberOfOriginalClauses());
            l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_ = ClauseSizeVectorType(this->getNumberOfOriginalClauses(), 0);

            l_firstCall_oneLiteralWatchingAlgorithmSubsumption_ = false;
        }

        // Initialize local auxiliary data structures
        if (l_firstCall_oneLiteralWatchingAlgorithmVariableSubsumption_) {
            l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_ = VariableSetType(maxOriginalClauseSize_);
            l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_ = VectorSetType(this->getNumberOfVariablesInOriginalFormulaUsedForIndexing());
            l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_ = SubsumptionWatcherVectorType(this->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), ClauseIdVectorType());

            // Reserve the variable watcher
            for (ClauseIdVectorType& clauseIdVector : l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_)
                clauseIdVector.reserve(S_ESTIMATED_NUMBER_OF_WATCHED_CLAUSES_FOR_SUBSUMPTION_);

            l_firstCall_oneLiteralWatchingAlgorithmVariableSubsumption_ = false;
        }

        // Clear the variable watcher
        for (std::size_t index : l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_.getAddedElementVector())
            l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[index].clear();
        l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_.clear();

        #ifndef NDEBUG
        // Check the variable watcher is empty
        for (const ClauseIdVectorType& clauseIdVector : l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_)
            assert(clauseIdVector.empty());
        #endif

        // Initialize the watcher
        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            ClauseSizeType indexTmp = getIndexOfUnassignedLiteralInClause(clauseId);
            VarT variableTmp = getLiteralAtPositionInClause(clauseId, indexTmp).getVariable();

            // Index watcher
            l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_[clauseId] = indexTmp;

            // Variable watcher
            l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[variableTmp].emplace_back(clauseId);
            l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_.emplace(variableTmp, false);
        }

        for (ClauseIdT clauseId : currentComponentClausesFixedVector_) {
            if (isClauseVariableSubsumedOneLiteralWatchingAlgorithmVariableSubsumption(clauseId, variableSubsumedClauseVectorSet))
                variableSubsumedClauseVectorSet.emplace(clauseId);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::isClauseVariableSubsumedOneLiteralWatchingAlgorithmVariableSubsumption(ClauseIdT clauseId,
                                                                                                                                            const VectorSetType& variableSubsumedClauseVectorSet) const {
        ClauseSizeType clauseSize = getCurrentClauseSize(clauseId);
        l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_.clear();

        for (auto clauseIt = beginClause(clauseId); clauseIt != this->endClause(); ++clauseIt) {
            VarT var = clauseIt->getVariable();
            l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_.emplace(var);

            // No update needed
            if (l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[var].empty())
                continue;

            l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_.clear();

            for (ClauseIdT clauseIdTmp : l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[var]) {
                if (clauseId == clauseIdTmp)
                    continue;

                // Transitivity
                if (variableSubsumedClauseVectorSet.contains(clauseIdTmp))
                    continue;

                if (getCurrentClauseSize(clauseIdTmp) > clauseSize)
                    continue;

                // The watcher cannot be updated
                if (!updateWatcherOneLiteralWatchingAlgorithmVariableSubsumption(clauseIdTmp)) {
                    Other::smartRemoveElementsFromVector(l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[var],
                                                         l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_);
                    return true;
                }
                // The watcher has been updated
                else
                    l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_.emplace(clauseIdTmp);
            }

            Other::smartRemoveElementsFromVector(l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[var],
                                                 l_removeClauseIdVectorSet_oneLiteralWatchingAlgorithmSubsumption_);
        }

        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::updateWatcherOneLiteralWatchingAlgorithmVariableSubsumption(ClauseIdT clauseId) const {
        ClauseSizeType index = l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_[clauseId];
        VarT oldVariable = getLiteralAtPositionInClause(clauseId, index).getVariable();
        VarT newVariable = oldVariable;

        assert(Other::containInVector(l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[oldVariable], clauseId));

        // (index + 1, endClause)
        for (ClauseSizeType i = index + 1; i < originalClauseSize_[clauseId]; ++i) {
            VarT var = getLiteralAtPositionInClause(clauseId, i).getVariable();

            // New watcher has been found
            if (!this->isVariableAssigned(var) && !l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_.contains(var)) {
                newVariable = var;
                l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_[clauseId] = i;

                break;
            }
        }

        // (0, index - 1)
        if (oldVariable == newVariable) {
            for (ClauseSizeType i = 0; i < index; ++i) {
                VarT var = getLiteralAtPositionInClause(clauseId, i).getVariable();

                // New watcher has been found
                if (!this->isVariableAssigned(var) && !l_forbiddenVariableSet_oneLiteralWatchingAlgorithmVariableSubsumption_.contains(var)) {
                    newVariable = var;
                    l_indexSubsumptionWatcherVector_oneLiteralWatchingAlgorithmSubsumption_[clauseId] = i;

                    break;
                }
            }
        }

        // No variable can be used as a watcher
        if (oldVariable == newVariable)
            return false;

        // Variable watcher
        l_variableSubsumptionWatcherVector_oneLiteralWatchingAlgorithmVariableSubsumption_[newVariable].emplace_back(clauseId);
        l_removeVariableSubsumptionWatcherVectorSet_oneLiteralWatchingAlgorithmVariableSubsumption_.emplace(newVariable, false);

        return true;
    }
}   // namespace Hydra::Formula::Representation::Contagious
