#pragma once

#include "./FormulaRepresentationAbstract.hpp"

namespace Hydra::Formula::Representation {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::processIsCurrentComponentFormulaKromC([[maybe_unused]] const VariableSetType& currentComponentVariableSet) const {
        throw Exception::Formula::Representation::RecognitionOfSomethingIsNotSupportedException(RecognitionTypeEnum::KROM_C);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::processIsCurrentComponentFormulaHornC([[maybe_unused]] const VariableSetType& currentComponentVariableSet) const {
        throw Exception::Formula::Representation::RecognitionOfSomethingIsNotSupportedException(RecognitionTypeEnum::HORN_C);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::processIsCurrentComponentFormulaAntiHornC([[maybe_unused]] const VariableSetType& currentComponentVariableSet) const {
        throw Exception::Formula::Representation::RecognitionOfSomethingIsNotSupportedException(RecognitionTypeEnum::ANTI_HORN_C);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightType
    FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::combineVertexWeights(VertexWeightType vertexWeight1, VertexWeightType vertexWeight2,
                                                                                   VertexWeightTypeEnum vertexWeightType) const {
        assert(PartitioningHypergraph::isVertexWeightUsed(vertexWeightType));

        switch (vertexWeightType) {
            case VertexWeightTypeEnum::STANDARD:
            case VertexWeightTypeEnum::CLAUSE_LENGTH:
                return vertexWeight1 + vertexWeight2;
            default:
                throw Exception::NotImplementedException(PartitioningHypergraph::vertexWeightTypeEnumToString(vertexWeightType),
                                                         "Hydra::Formula::Representation::FormulaRepresentationAbstract::combineVertexWeights");
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    FormulaRepresentationTypeEnum FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::getFormulaRepresentationType() const noexcept {
        return formulaRepresentationType_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::getNumberOfVariablesInOriginalFormula() const noexcept {
        return partialAssignment_.getMaxNumberOfVariables();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::getNumberOfVariablesInOriginalFormulaUsedForIndexing() const noexcept {
        return static_cast<VarT>(1) + partialAssignment_.getMaxNumberOfVariables();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    LiteralT FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::getNumberOfLiteralsInOriginalFormula() const noexcept {
        return (LiteralT)2 * partialAssignment_.getMaxNumberOfVariables();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseIdT FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::getNumberOfOriginalClauses() const noexcept {
        return numberOfOriginalClauses_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    FormulaSizeType FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::getOriginalFormulaSize() const noexcept {
        return originalFormulaSize_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isVariableAssigned(VarT var) const noexcept {
        return partialAssignment_.variableExists(var);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isLiteralSetToTrue(const LiteralType& lit) const noexcept {
        return partialAssignment_.literalExists(lit);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isLiteralSetToFalse(const LiteralType& lit) const noexcept {
        return partialAssignment_.complementaryLiteralExists(lit);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isClauseSatisfied(ClauseIdT clauseId) const {
        assert(clauseId < numberOfOriginalClauses_);

        return getCurrentClauseStatus(clauseId) == ClauseStatusEnum::SATISFIED;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isClauseEmpty(ClauseIdT clauseId) const {
        assert(clauseId < numberOfOriginalClauses_);

        return getCurrentClauseStatus(clauseId) == ClauseStatusEnum::EMPTY;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isClauseUnresolved(ClauseIdT clauseId) const {
        assert(clauseId < numberOfOriginalClauses_);

        return Other::containInSet(unresolvedClauseStatusSet, getCurrentClauseStatus(clauseId));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isClauseUnit(ClauseIdT clauseId) const {
        assert(clauseId < numberOfOriginalClauses_);

        return getCurrentClauseStatus(clauseId) == ClauseStatusEnum::UNIT_CLAUSE;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    int FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::compareClauses(ClauseIdT clauseId1, ClauseIdT clauseId2) const {
        assert(clauseId1 < numberOfOriginalClauses_);
        assert(clauseId2 < numberOfOriginalClauses_);
        assert(!isClauseSatisfied(clauseId1));
        assert(!isClauseSatisfied(clauseId2));

        ClauseSizeType clause1Size = getCurrentClauseSize(clauseId1);
        ClauseSizeType clause2Size = getCurrentClauseSize(clauseId2);

        if (clause1Size < clause2Size)
            return -1;

        if (clause1Size > clause2Size)
            return 1;

        ClauseIterator clause1BeginIt = beginSortedClause(clauseId1);
        ClauseIterator clause2BeginIt = beginSortedClause(clauseId2);
        ClauseIterator clauseEndIt = endSortedClause();

        while ((clause1BeginIt != clauseEndIt) && (clause2BeginIt != clauseEndIt)) {
            const LiteralType& lit1 = *clause1BeginIt;
            const LiteralType& lit2 = *clause2BeginIt;

            if (lit1 == lit2) {
                ++clause1BeginIt;
                ++clause2BeginIt;
                continue;
            }

            if (lit1 < lit2) {
                return -1;
            }

            // lit1 > lit2
            return 1;
        }

        return 0;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::addLiteralToPartialAssignment(const LiteralType& lit,
                                                                                                 VariableVectorType& freeVariableVector) {
        partialAssignment_.addLiteral(lit);

        #ifndef NDEBUG
        d_assignmentStack_.emplace_back(lit.getVariable(), lit.isPositive());
        #endif

        processAddLiteralToPartialAssignment(lit, freeVariableVector, true, true);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::addLiteralVectorToPartialAssignment(const LiteralVectorType& literalVector,
                                                                                                       VariableVectorType& freeVariableVector) {
        if (literalVector.empty())
            return;

        std::size_t indexOfLastAssignment = literalVector.size() - 1;

        for (std::size_t i = 0; i < literalVector.size(); ++i) {
            const LiteralType& lit = literalVector[i];

            partialAssignment_.addLiteral(lit);

            #ifndef NDEBUG
            d_assignmentStack_.emplace_back(lit.getVariable(), lit.isPositive());
            #endif

            processAddLiteralToPartialAssignment(lit, freeVariableVector, (i == 0), (i == indexOfLastAssignment));
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::removeLiteralFromPartialAssignment(const LiteralType& lit,
                                                                                                      VariableVectorType& unfreeVariableVector) {
        #ifndef NDEBUG
        // The literal is not the last assigned literal in the assignment stack
        if (d_assignmentStack_.empty() || d_assignmentStack_.back() != lit) {
            std::stringstream stringStreamTmp = Other::createStringStreamFromContainer(d_assignmentStack_.cbegin(), d_assignmentStack_.cend());
            throw Exception::Formula::Representation::AttemptRemoveNotLastAssignedLiteralFromAssignmentStackException(lit, stringStreamTmp.str());
        }

        d_assignmentStack_.pop_back();
        #endif

        partialAssignment_.removeLiteral(lit);

        processRemoveLiteralFromPartialAssignment(lit, unfreeVariableVector);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::removeLiteralVectorFromPartialAssignment(const LiteralVectorType& literalVector,
                                                                                                            VariableVectorType& unfreeVariableVector, bool reverse) {
        if (literalVector.empty())
            return;

        // Remove literals in the reverse order
        if (reverse) {
            for (auto it = literalVector.rbegin(); it != literalVector.rend(); ++it)
                removeLiteralFromPartialAssignment(*it, unfreeVariableVector);
        }

        // Remove literals in the standard order
        else {
            for (const LiteralType& lit : literalVector)
                removeLiteralFromPartialAssignment(lit, unfreeVariableVector);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseStringType
    FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::getClauseString(ClauseIdT clauseId, bool considerOnlyVariables) const {
        assert(clauseId < numberOfOriginalClauses_);
        assert(!isClauseSatisfied(clauseId));

        ClauseStringType clauseString;
        clauseString.reserve(getCurrentClauseSize(clauseId));

        for (auto clauseIt = beginSortedClause(clauseId); clauseIt != endSortedClause(); ++clauseIt) {
            if (considerOnlyVariables)
                clauseString.push_back(static_cast<LiteralT>(clauseIt->getVariable()));
            else
                clauseString.push_back(clauseIt->getLiteralT());
        }

        return clauseString;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isClauseUntouchedAndBinary(ClauseIdT clauseId) const {
        assert(clauseId < numberOfOriginalClauses_);

        return (isClauseUntouched(clauseId) && (getCurrentClauseSize(clauseId) == 2));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isPureLiteralInCurrentFormula(VarT var) const {
        assert(!isVariableAssigned(var));   // variable is not assigned
        assert(!isVariableFree(var));       // variable is not free

        ClauseIdT litPosNumber = getNumberOfCurrentClauses(getPositiveLiteralT<VarT, LiteralT>(var));
        ClauseIdT litNegNumber = getNumberOfCurrentClauses(getNegativeLiteralT<VarT, LiteralT>(var));

        if (litPosNumber == 0 || litNegNumber == 0)
            return true;

        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isPositivePureLiteralInCurrentFormula(VarT var) const {
        assert(!isVariableAssigned(var));   // variable is not assigned
        assert(!isVariableFree(var));       // variable is not free

        ClauseIdT litNegNumber = getNumberOfCurrentClauses(getNegativeLiteralT<VarT, LiteralT>(var));

        if (litNegNumber == 0)
            return true;

        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isNegativePureLiteralInCurrentFormula(VarT var) const {
        assert(!isVariableAssigned(var));   // variable is not assigned
        assert(!isVariableFree(var));       // variable is not free

        ClauseIdT litPosNumber = getNumberOfCurrentClauses(getPositiveLiteralT<VarT, LiteralT>(var));

        if (litPosNumber == 0)
            return true;

        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isPureLiteralInCurrentFormula([[maybe_unused]] VarT var,
                                                                                                 [[maybe_unused]] IgnorePureLiteralTypeEnum ignorePureLiteralType) const {
        #if defined(BELLA_COMPILER)
        switch (ignorePureLiteralType) {
            case IgnorePureLiteralTypeEnum::NONE:
                break;
            case IgnorePureLiteralTypeEnum::ONLY_POSITIVE:
                // Positive pure literal or a singleton
                if (isPositivePureLiteralInCurrentFormula(var) || isVariableSingleton(var))
                    return true;
                break;
            case IgnorePureLiteralTypeEnum::ONLY_NEGATIVE:
                // Negative pure literal or a singleton
                if (isNegativePureLiteralInCurrentFormula(var) || isVariableSingleton(var))
                    return true;
                break;
            case IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE:
                // Pure literal
                if (isPureLiteralInCurrentFormula(var))
                    return true;
                break;
            default:
                throw Exception::NotImplementedException(ignorePureLiteralTypeEnumToString(ignorePureLiteralType),
                                                         "Hydra::Formula::Representation::FormulaRepresentationAbstract::isPureLiteralInCurrentFormula");
        }

        return false;
        #endif

        #if defined(CARA_SOLVER)
        assert(ignorePureLiteralType == IgnorePureLiteralTypeEnum::NONE);

        return false;
        #endif
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::arePureLiteralsInCurrentFormula(const VariableSetType& variableSet,
                                                                                                   IgnorePureLiteralTypeEnum ignorePureLiteralType) const {
        for (VarT var : variableSet) {
            if (!isPureLiteralInCurrentFormula(var, ignorePureLiteralType))
                return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::doesClauseContainOnlyPureLiteralsOfIgnoredType(ClauseIdT clauseId,
                                                                                                                  IgnorePureLiteralTypeEnum ignorePureLiteralType) const {
        assert(clauseId < numberOfOriginalClauses_);
        assert(!isClauseSatisfied(clauseId));

        if (ignorePureLiteralType == IgnorePureLiteralTypeEnum::NONE)
            return false;

        for (auto clauseIt = beginClause(clauseId); clauseIt != endClause(); ++clauseIt) {
            // The variable is not a pure literal of the ignored type
            if (!isPureLiteralInCurrentFormula(clauseIt->getVariable(), ignorePureLiteralType))
                return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::addClausesContainingOnlyPureLiteralsOfIgnoredType(const ClauseIdSetType& pureClauseSet,
                                                                                                                     [[maybe_unused]] IgnorePureLiteralTypeEnum ignorePureLiteralType) {
        if (pureClauseSet.empty())
            return;

        processAddClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet);

        #ifndef NDEBUG
        // Check if the clauses are pure
        for (ClauseIdT clauseId : pureClauseSet) {
            assert(isClauseUnresolved(clauseId));                                                      // clause is unresolved
            assert(doesClauseContainOnlyPureLiteralsOfIgnoredType(clauseId, ignorePureLiteralType));   // clause contains only pure literals
        }
        #endif
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::removeClausesContainingOnlyPureLiteralsOfIgnoredType(const ClauseIdSetType& pureClauseSet,
                                                                                                                        [[maybe_unused]] IgnorePureLiteralTypeEnum ignorePureLiteralType) {
        if (pureClauseSet.empty())
            return;

        #ifndef NDEBUG
        // Check if the clauses are pure
        for (ClauseIdT clauseId : pureClauseSet) {
            assert(isClauseUnresolved(clauseId));                                                      // clause is unresolved
            assert(doesClauseContainOnlyPureLiteralsOfIgnoredType(clauseId, ignorePureLiteralType));   // clause contains only pure literals
        }
        #endif

        processRemoveClausesContainingOnlyPureLiteralsOfIgnoredType(pureClauseSet);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseIdT FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::getNumberOfCurrentClauses(const LiteralType& lit) const {
        return getNumberOfCurrentClauses(lit.getLiteralT());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeCounterType
    FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::getCurrentClauseSizeCounter(const LiteralType& lit) const {
        return getCurrentClauseSizeCounter(lit.getLiteralT());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseIdT FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::getNumberOfCurrentBinaryClauses(const LiteralType& lit) const {
        return getNumberOfCurrentBinaryClauses(lit.getLiteralT());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentType
    FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::computeConnectedComponents(const VariableSetType& currentComponentVariableSet) const {
        // Statistics
        if (formulaRepresentationStatisticsPtr_)
            formulaRepresentationStatisticsPtr_->computeConnectedComponentsTimer.startStopwatch();

        ConnectedComponentType connectedComponent = processComputeConnectedComponents(currentComponentVariableSet);

        // Statistics
        if (formulaRepresentationStatisticsPtr_)
            formulaRepresentationStatisticsPtr_->computeConnectedComponentsTimer.stopStopwatch();

        return connectedComponent;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentType
    FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::computeConnectedComponents(const VariableSetType& currentComponentVariableSet,
                                                                                         ClauseIdSetType& pureClauseSet,
                                                                                         IgnorePureLiteralTypeEnum ignorePureLiteralType) {
        // Statistics
        if (formulaRepresentationStatisticsPtr_)
            formulaRepresentationStatisticsPtr_->computeConnectedComponentsTimer.startStopwatch();

        ConnectedComponentType connectedComponent = processComputeConnectedComponents(currentComponentVariableSet, pureClauseSet, ignorePureLiteralType);

        // Statistics
        if (formulaRepresentationStatisticsPtr_)
            formulaRepresentationStatisticsPtr_->computeConnectedComponentsTimer.stopStopwatch();

        return connectedComponent;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::setStatisticsBeforeCompilation() const {
        // Statistics
        if (formulaRepresentationStatisticsPtr_) {
            formulaRepresentationStatisticsPtr_->formulaSizeNumber.setNumber(static_cast<Statistics::LargeNumberType>(getOriginalFormulaSize()));
            formulaRepresentationStatisticsPtr_->numberOfVariablesNumber.setNumber(static_cast<Statistics::LargeNumberType>(getNumberOfVariablesInOriginalFormula()));
            formulaRepresentationStatisticsPtr_->numberOfClausesNumber.setNumber(static_cast<Statistics::LargeNumberType>(getNumberOfOriginalClauses()));
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::sortVariablesBasedOnClauseReductionHeuristic([[maybe_unused]] const VariableSetType& currentComponentVariableSet,
                                                                                                                VariableReusableVectorType& variableReusableVector,
                                                                                                                bool ascendingOrder) const {
        using ScoreType = ClauseReductionHeuristicScoreType;

        // Initialize local auxiliary data structures
        if (l_firstCall_sortVariablesBasedOnClauseReductionHeuristic_) {
            l_variableClauseReductionHeuristicScoreVector_sortVariablesBasedOnClauseReductionHeuristic_ = ClauseReductionHeuristicScoreVectorType(getNumberOfVariablesInOriginalFormulaUsedForIndexing(), 0);

            l_firstCall_sortVariablesBasedOnClauseReductionHeuristic_ = false;
        }

        // Compute the clause reduction heuristic score for each variable
        for (VarT var : variableReusableVector) {
            assert(var < l_variableClauseReductionHeuristicScoreVector_sortVariablesBasedOnClauseReductionHeuristic_.size());

            ClauseIdT numberOfOccurrencesPosLit = getNumberOfCurrentClauses(getPositiveLiteralT<VarT, LiteralT>(var));
            ClauseIdT numberOfOccurrencesNegLit = getNumberOfCurrentClauses(getNegativeLiteralT<VarT, LiteralT>(var));

            ClauseIdT numberOfBinaryOccurrencesPosLit = getNumberOfCurrentBinaryClauses(getPositiveLiteralT<VarT, LiteralT>(var));
            ClauseIdT numberOfBinaryOccurrencesNegLit = getNumberOfCurrentBinaryClauses(getNegativeLiteralT<VarT, LiteralT>(var));

            ScoreType posLitScore = static_cast<ScoreType>(numberOfBinaryOccurrencesPosLit) +
                                    static_cast<ScoreType>(0.2) * static_cast<ScoreType>(numberOfOccurrencesPosLit - numberOfBinaryOccurrencesPosLit);
            ScoreType negLitScore = static_cast<ScoreType>(numberOfBinaryOccurrencesNegLit) +
                                    static_cast<ScoreType>(0.2) * static_cast<ScoreType>(numberOfOccurrencesNegLit - numberOfBinaryOccurrencesNegLit);

            l_variableClauseReductionHeuristicScoreVector_sortVariablesBasedOnClauseReductionHeuristic_[var] = posLitScore * negLitScore;
        }

        std::sort(variableReusableVector.begin(), variableReusableVector.end(), [this, ascendingOrder](VarT var1, VarT var2) -> bool {
            assert(var1 < l_variableClauseReductionHeuristicScoreVector_sortVariablesBasedOnClauseReductionHeuristic_.size());
            assert(var2 < l_variableClauseReductionHeuristicScoreVector_sortVariablesBasedOnClauseReductionHeuristic_.size());

            ScoreType var1Score = l_variableClauseReductionHeuristicScoreVector_sortVariablesBasedOnClauseReductionHeuristic_[var1];
            ScoreType var2Score = l_variableClauseReductionHeuristicScoreVector_sortVariablesBasedOnClauseReductionHeuristic_[var2];

            if (var1Score < var2Score)
                return ascendingOrder;

            if (var1Score > var2Score)
                return !ascendingOrder;

            return (var1 < var2);
        });
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isCurrentComponentFormulaKromC(const VariableSetType& currentComponentVariableSet) const {
        // Statistics
        if (formulaRepresentationStatisticsPtr_)
            formulaRepresentationStatisticsPtr_->recognitionOfKromCTimer.startStopwatch();

        bool isKromC = processIsCurrentComponentFormulaKromC(currentComponentVariableSet);

        // Statistics
        if (formulaRepresentationStatisticsPtr_)
            formulaRepresentationStatisticsPtr_->recognitionOfKromCTimer.stopStopwatch();

        return isKromC;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isCurrentComponentFormulaHornC(const VariableSetType& currentComponentVariableSet) const {
        // Statistics
        if (formulaRepresentationStatisticsPtr_)
            formulaRepresentationStatisticsPtr_->recognitionOfHornCTimer.startStopwatch();

        bool isHornC = processIsCurrentComponentFormulaHornC(currentComponentVariableSet);

        // Statistics
        if (formulaRepresentationStatisticsPtr_)
            formulaRepresentationStatisticsPtr_->recognitionOfHornCTimer.stopStopwatch();

        return isHornC;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isCurrentComponentFormulaAntiHornC(const VariableSetType& currentComponentVariableSet) const {
        // Statistics
        if (formulaRepresentationStatisticsPtr_)
            formulaRepresentationStatisticsPtr_->recognitionOfAntiHornCTimer.startStopwatch();

        bool isAntiHornC = processIsCurrentComponentFormulaAntiHornC(currentComponentVariableSet);

        // Statistics
        if (formulaRepresentationStatisticsPtr_)
            formulaRepresentationStatisticsPtr_->recognitionOfAntiHornCTimer.stopStopwatch();

        return isAntiHornC;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::saveCurrentComponentFormulaToVector(const VariableSetType& currentComponentVariableSet,
                                                                                                       LiteralVectorType& formula,
                                                                                                       ClauseOffsetVectorType& clauseOffsetVector, bool sort) const {
        assert(formula.empty());
        assert(clauseOffsetVector.empty());

        processSaveCurrentComponentFormulaToVector(currentComponentVariableSet, formula, clauseOffsetVector, sort);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::saveFormulaDefinedByClausesToVector(const ClauseIdReusableVectorType& clauseIdReusableVector,
                                                                                                       LiteralVectorType& formula,
                                                                                                       ClauseOffsetVectorType& clauseOffsetVector, bool sort) const {
        assert(formula.empty());
        assert(clauseOffsetVector.empty());

        FormulaSizeType formulaSize = 0;
        for (ClauseIdT clauseId : clauseIdReusableVector) {
            assert(isClauseUnresolved(clauseId));

            formulaSize += static_cast<FormulaSizeType>(getCurrentClauseSize(clauseId));
        }

        clauseOffsetVector.reserve(clauseIdReusableVector.size());
        formula.reserve(formulaSize + clauseIdReusableVector.size());

        FormulaSizeType currentIndex = 0;
        for (ClauseIdT clauseId : clauseIdReusableVector) {
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

        assert(currentIndex == formulaSize + static_cast<FormulaSizeType>(clauseIdReusableVector.size()));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::getNumberOfSingletonVariables(const VariableSetType& variableSet) const {
        VarT numberOfSingletonVariables = 0;

        for (VarT var : variableSet) {
            if (isVariableSingleton(var))
                ++numberOfSingletonVariables;
        }

        return numberOfSingletonVariables;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator::next() {
        ++ptr_;

        while (true) {
            // The end of the clause
            if (ptr_->isZeroLiteral()) {
                ptr_ = nullptr;
                return;
            }

            #ifndef NDEBUG
            // The clause is satisfied
            if (d_checkSat_ && formulaRepresentationAbstractPtr_->isLiteralSetToTrue(*ptr_))
                throw Exception::Formula::Representation::IteratingOverSatisfiedClauseException(d_clauseId_, *ptr_);
            #endif

            // The variable is unassigned
            if (!formulaRepresentationAbstractPtr_->isVariableAssigned(ptr_->getVariable()))
                return;

            ++ptr_;
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator::initialize() {
        while (true) {
            // The end of the clause
            if (ptr_->isZeroLiteral()) {
                ptr_ = nullptr;
                return;
            }

            #ifndef NDEBUG
            // The clause is satisfied
            if (d_checkSat_ && formulaRepresentationAbstractPtr_->isLiteralSetToTrue(*ptr_))
                throw Exception::Formula::Representation::IteratingOverSatisfiedClauseException(d_clauseId_, *ptr_);
            #endif

            // The variable is unassigned
            if (!formulaRepresentationAbstractPtr_->isVariableAssigned(ptr_->getVariable()))
                return;

            ++ptr_;
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator::ReferenceType
    FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator::operator*() const {
        return *ptr_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator::PointerType
    FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator::operator->() const {
        return ptr_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator&
    FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator::operator++() {
        next();
        return *this;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator
    FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::endClause() const noexcept {
        return ClauseIterator();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIterator
    FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::endSortedClause() const noexcept {
        return ClauseIterator();
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::printFormulaRepresentationDebug(std::ostream& out) const {
        out << "Formula representation" << std::endl;
        out << "Type: " << formulaRepresentationEnumToString(formulaRepresentationType_) << std::endl;
        out << "Original formula size: " << std::to_string(originalFormulaSize_) << std::endl;
        out << "Number of original clauses: " << std::to_string(numberOfOriginalClauses_) << std::endl;
        out << "Maximum original clause size: " << std::to_string(getMaxOriginalClauseSize()) << std::endl;

        out << "Assignment stack:";
        for (const LiteralType& lit : d_assignmentStack_)
            out << " " << lit;
        out << std::endl;

        out << "Partial assignment: " << partialAssignment_ << std::endl;
        out << "Number of assigned variables: " << std::to_string(partialAssignment_.getNumberOfAssignedVariables()) << std::endl;
        out << "Is full assignment: " << std::to_string(partialAssignment_.areAllVariablesAssigned());
        out << std::endl;

        out << "--------------------" << std::endl;
        this->processPrintFormulaRepresentationDebug(out);

        out << "--------------------" << std::endl;
        out << "Current formula: " << std::endl;
        this->printCurrentFormulaDebug(out, false, false);
        out << std::endl;

        out << "--------------------" << std::endl;
        out << "Current formula (no duplicate clauses): " << std::endl;
        this->printCurrentFormulaDebug(out, true, false);
        out << std::endl;

        out << "--------------------" << std::endl;
        out << "Current formula (no duplicate and subsumed clauses): " << std::endl;
        this->printCurrentFormulaDebug(out, true, true);
        out << std::endl;
        out << std::endl;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    const typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType&
    FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::getIthElementOfPartialAssignmentDebug(VarT i) const {
        // The i-th element of the partial assignment does not exist
        if (d_assignmentStack_.size() <= i)
            throw Exception::Formula::Representation::IthElementOfPartialAssignmentDoesNotExistException<VarT>(i, static_cast<VarT>(d_assignmentStack_.size()));

        return d_assignmentStack_[i];
    }
    #endif
}   // namespace Hydra::Formula::Representation
