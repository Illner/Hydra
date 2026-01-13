#pragma once

#include "./StructuralRestrictedFormulaRepresentation.hpp"

namespace Hydra::Formula::StructuralRestrictedRepresentation {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::initializeFormula(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                                                                                 const VariableSetType& currentComponentVariableSet,
                                                                                                 FormulaLeafPostprocessingTypeEnum formulaLeafPostprocessingType) {
        assert(!currentComponentVariableSet.empty());   // at least one variable

        #ifndef NDEBUG
        bool sort = true;
        #else
        bool sort = false;
        #endif

        VarT maxVar = *(std::max_element(currentComponentVariableSet.cbegin(), currentComponentVariableSet.cend()));

        VectorSetType variableVectorSet((formulaLeafPostprocessingType != FormulaLeafPostprocessingTypeEnum::NO_SUBSUMED_CLAUSES) ? 0 : (VarT)1 + maxVar);
        ClauseIdReusableVectorType clauseIdReusableVector((formulaLeafPostprocessingType == FormulaLeafPostprocessingTypeEnum::NONE) ? 0 : formulaRepresentationAbstractPtr->getNumberOfCurrentComponentClauses(currentComponentVariableSet));

        switch (formulaLeafPostprocessingType) {
            // None
            case FormulaLeafPostprocessingTypeEnum::NONE:
                variableSortedVector_ = Other::sortUnorderedSet(currentComponentVariableSet);
                formulaRepresentationAbstractPtr->saveCurrentComponentFormulaToVector(currentComponentVariableSet, formula_, clauseOffsetVector_, sort);
                break;
            // No duplicate clauses
            case FormulaLeafPostprocessingTypeEnum::NO_DUPLICATE_CLAUSES:
                // Get clauses
                formulaRepresentationAbstractPtr->getCurrentComponentNotDuplicateClauses(currentComponentVariableSet, clauseIdReusableVector, false, sort);

                variableSortedVector_ = Other::sortUnorderedSet(currentComponentVariableSet);
                formulaRepresentationAbstractPtr->saveFormulaDefinedByClausesToVector(clauseIdReusableVector, formula_, clauseOffsetVector_, sort);
                break;
            // No subsumed clauses
            case FormulaLeafPostprocessingTypeEnum::NO_SUBSUMED_CLAUSES:
                // Get clauses
                formulaRepresentationAbstractPtr->getCurrentComponentNotSubsumedClauses(currentComponentVariableSet, clauseIdReusableVector,
                                                                                        variableVectorSet, true, false, sort);

                variableSortedVector_.reserve(variableVectorSet.size());
                for (std::size_t var : variableVectorSet.getAddedElementVector(true))
                    variableSortedVector_.emplace_back(static_cast<VarT>(var));

                formulaRepresentationAbstractPtr->saveFormulaDefinedByClausesToVector(clauseIdReusableVector, formula_, clauseOffsetVector_, sort);
                break;
            default:
                throw Exception::NotImplementedException(Circuit::Node::formulaLeafPostprocessingTypeEnumToString(formulaLeafPostprocessingType),
                                                         "Hydra::Formula::StructuralRestrictedRepresentation::StructuralRestrictedFormulaRepresentation::initializeFormula");
        }

        numberOfClauses_ = static_cast<ClauseIdT>(clauseOffsetVector_.size());
        formulaSize_ = static_cast<FormulaSizeType>(formula_.size()) - static_cast<FormulaSizeType>(numberOfClauses_);

        #ifndef NDEBUG
        // Filter out the switched variables
        if (!variableVectorSet.empty() && !switchedVariables_.empty()) {
            for (auto it = switchedVariables_.begin(); it != switchedVariables_.end();) {
                if ((maxVar < *it) || !variableVectorSet.contains(*it))
                    it = switchedVariables_.erase(it);
                else
                    ++it;
            }
        }
        #endif

        #ifndef NDEBUG
        // Check the variable set is correct
        VariableSetType variableSetTmp;

        for (const LiteralType& lit : formula_) {
            if (lit.isZeroLiteral())
                continue;

            variableSetTmp.emplace(lit.getVariable());
        }

        assert(variableSetTmp.size() == variableSortedVector_.size());

        for (VarT var : variableSortedVector_)
            assert(Other::containInSet(variableSetTmp, var));

        // Check the switched variables
        for (VarT var : switchedVariables_)
            assert(Other::containInSet(variableSetTmp, var));
        #endif
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::noUnitClause() const noexcept {
        ClauseSizeType clauseSize = 0;

        for (const LiteralType& lit : formula_) {
            // The end of a clause
            if (lit.isZeroLiteral()) {
                // The clause is unit
                if (clauseSize == 1)
                    return false;

                clauseSize = 0;
                continue;
            }

            ++clauseSize;
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::formulaIsKromC() const noexcept {
        ClauseSizeType clauseSize = 0;

        for (const LiteralType& lit : formula_) {
            // The end of a clause
            if (lit.isZeroLiteral()) {
                // The clause is NOT Krom
                if (clauseSize > 2)
                    return false;

                clauseSize = 0;
                continue;
            }

            ++clauseSize;
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::formulaIsHornC() const noexcept {
        ClauseSizeType numberOfPositiveLiterals = 0;

        for (const LiteralType& lit : formula_) {
            // The end of a clause
            if (lit.isZeroLiteral()) {
                numberOfPositiveLiterals = 0;
                continue;
            }

            if (lit.isPositive())
                ++numberOfPositiveLiterals;

            // The clause is NOT Horn
            if (numberOfPositiveLiterals > 1)
                return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::formulaIsAntiHornC() const noexcept {
        ClauseSizeType numberOfNegativeLiterals = 0;

        for (const LiteralType& lit : formula_) {
            // The end of a clause
            if (lit.isZeroLiteral()) {
                numberOfNegativeLiterals = 0;
                continue;
            }

            if (lit.isNegative())
                ++numberOfNegativeLiterals;

            // The clause is NOT anti-Horn
            if (numberOfNegativeLiterals > 1)
                return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::formulaIsRenHC() const noexcept {
        ClauseSizeType numberOfPositiveLiteralsAfterSwitching = 0;

        for (const LiteralType& lit : formula_) {
            // The end of a clause
            if (lit.isZeroLiteral()) {
                numberOfPositiveLiteralsAfterSwitching = 0;
                continue;
            }

            bool isSwitched = Other::containInSet(switchedVariables_, lit.getVariable());

            // The literal is positive after switching
            if ((isSwitched && lit.isNegative()) || (!isSwitched && lit.isPositive())) {
                ++numberOfPositiveLiteralsAfterSwitching;

                // The clause is NOT renamable Horn given the switched variables
                if (numberOfPositiveLiteralsAfterSwitching > 1)
                    return false;
            }
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::formulaSatisfiesStructuralRestriction() const {
        switch (structuralRestrictedFormulaRepresentationType_) {
            // Krom-C
            case StructuralRestrictedFormulaRepresentationTypeEnum::Krom_C:
                return formulaIsKromC();
            // Horn-C
            case StructuralRestrictedFormulaRepresentationTypeEnum::Horn_C:
                return formulaIsHornC();
            // anti-Horn-C
            case StructuralRestrictedFormulaRepresentationTypeEnum::anti_Horn_C:
                return formulaIsAntiHornC();
            // renH-C
            case StructuralRestrictedFormulaRepresentationTypeEnum::renH_C:
                return formulaIsRenHC();
            default:
                throw Exception::NotImplementedException(structuralRestrictedFormulaRepresentationTypeEnumToString(structuralRestrictedFormulaRepresentationType_),
                                                         "Hydra::Formula::StructuralRestrictedRepresentation::StructuralRestrictedFormulaRepresentation::formulaSatisfiesStructuralRestriction");
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseStatusWatchedLiteralEnum StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::initializeClauseWatchedLiterals(ClauseIdT clauseId,
                                                                                                                                         ClauseWatchedLiteralsType& clauseWatchedLiterals,
                                                                                                                                         const PartialAssignmentType& partialAssignment) const {
        assert(clauseId < clauseOffsetVector_.size());
        assert(!clauseWatchedLiterals.first.has_value());    // the first watched literal is NOT set
        assert(!clauseWatchedLiterals.second.has_value());   // the second watched literal is NOT set

        ClauseSizeType positionInClause = 0;
        FormulaSizeType currentPosition = clauseOffsetVector_[clauseId];

        while (true) {
            const LiteralType& lit = formula_[currentPosition];

            // The end of the clause
            if (lit.isZeroLiteral())
                break;

            // The clause is satisfied
            if (partialAssignment.literalExists(lit)) {
                assert(!clauseWatchedLiterals.second.has_value());   // the second watched literal is NOT set

                clauseWatchedLiterals.first.reset();

                return ClauseStatusWatchedLiteralEnum::SATISFIED;
            }

            // The complementary literal is satisfied
            if (partialAssignment.complementaryLiteralExists(lit)) {
                ++currentPosition;
                ++positionInClause;

                continue;
            }

            // The variable is not assigned
            // The second watched literal is about to be set
            if (clauseWatchedLiterals.first.has_value()) {
                clauseWatchedLiterals.second.emplace(positionInClause);

                break;
            }

            // The first watched literal is about to be set
            clauseWatchedLiterals.first.emplace(positionInClause);

            ++currentPosition;
            ++positionInClause;
        }

        // Both watched literals are set
        if (clauseWatchedLiterals.first.has_value() && clauseWatchedLiterals.second.has_value())
            return ClauseStatusWatchedLiteralEnum::UNDEFINED;

        // Only the first watched literal is set
        if (clauseWatchedLiterals.first.has_value())
            return ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_1;

        // Both watched literals are NOT set
        return ClauseStatusWatchedLiteralEnum::EMPTY;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseStatusWatchedLiteralEnum StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::updateClauseWatchedLiterals(ClauseIdT clauseId,
                                                                                                                                     ClauseWatchedLiteralsType& clauseWatchedLiterals,
                                                                                                                                     const PartialAssignmentType& partialAssignment) const {
        assert(clauseId < clauseOffsetVector_.size());
        assert(clauseWatchedLiterals.first.has_value());                             // the first watched literal is set
        assert(clauseWatchedLiterals.second.has_value());                            // the second watched literal is set
        assert(*(clauseWatchedLiterals.first) != *(clauseWatchedLiterals.second));   // the watched literals are different

        FormulaSizeType clauseOffset = clauseOffsetVector_[clauseId];
        const LiteralType& firstWatchedLiteral = formula_[clauseOffset + *(clauseWatchedLiterals.first)];
        const LiteralType& secondWatchedLiteral = formula_[clauseOffset + *(clauseWatchedLiterals.second)];

        // At least one of the watched literals is satisfied
        if (partialAssignment.literalExists(firstWatchedLiteral) || partialAssignment.literalExists(secondWatchedLiteral)) {
            clauseWatchedLiterals.first.reset();
            clauseWatchedLiterals.second.reset();

            return ClauseStatusWatchedLiteralEnum::SATISFIED;
        }

        // Both watched literals are valid
        if (!partialAssignment.complementaryLiteralExists(firstWatchedLiteral) && !partialAssignment.complementaryLiteralExists(secondWatchedLiteral))
            return ClauseStatusWatchedLiteralEnum::UNDEFINED;

        // Both watched literals are invalid
        if (partialAssignment.complementaryLiteralExists(firstWatchedLiteral) && partialAssignment.complementaryLiteralExists(secondWatchedLiteral)) {
            // Reset the watched literals
            clauseWatchedLiterals.first.reset();
            clauseWatchedLiterals.second.reset();

            return initializeClauseWatchedLiterals(clauseId, clauseWatchedLiterals, partialAssignment);
        }

        assert(partialAssignment.complementaryLiteralExists(firstWatchedLiteral) && !partialAssignment.complementaryLiteralExists(secondWatchedLiteral));
        assert(!partialAssignment.complementaryLiteralExists(firstWatchedLiteral) && partialAssignment.complementaryLiteralExists(secondWatchedLiteral));

        bool firstWatchedLiteralIsInvalid = partialAssignment.complementaryLiteralExists(firstWatchedLiteral);
        const LiteralType& ignoredLiteral = firstWatchedLiteralIsInvalid ? secondWatchedLiteral : firstWatchedLiteral;

        bool updated = false;
        ClauseSizeType positionInClause = firstWatchedLiteralIsInvalid ? *(clauseWatchedLiterals.first) : *(clauseWatchedLiterals.second);
        FormulaSizeType endPosition = clauseOffset + static_cast<FormulaSizeType>(positionInClause);
        FormulaSizeType currentPosition = endPosition;

        ++currentPosition;
        ++positionInClause;

        while (true) {
            // The end of the iteration
            if (currentPosition == endPosition)
                break;

            const LiteralType& lit = formula_[currentPosition];

            // The end of the clause
            if (lit.isZeroLiteral()) {
                positionInClause = 0;
                currentPosition = clauseOffset;

                continue;
            }

            // The clause is satisfied
            if (partialAssignment.literalExists(lit)) {
                clauseWatchedLiterals.first.reset();
                clauseWatchedLiterals.second.reset();

                return ClauseStatusWatchedLiteralEnum::SATISFIED;
            }

            // The complementary literal is satisfied, or the literal is already used for the other watched literal
            if (partialAssignment.complementaryLiteralExists(lit) || (lit == ignoredLiteral)) {
                ++currentPosition;
                ++positionInClause;

                continue;
            }

            // The variable is not assigned, and the literal can be used as a watched literal
            if (firstWatchedLiteralIsInvalid)
                clauseWatchedLiterals.first.emplace(positionInClause);
            else
                clauseWatchedLiterals.second.emplace(positionInClause);

            updated = true;
            break;
        }

        // The invalid watched literal has been successfully updated
        if (updated)
            return ClauseStatusWatchedLiteralEnum::UNDEFINED;

        if (firstWatchedLiteralIsInvalid)
            return ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_2;

        return ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_1;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    FormulaSizeType StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getFormulaSize() const noexcept {
        return formulaSize_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseIdT StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getNumberOfClauses() const noexcept {
        return numberOfClauses_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    const typename StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::VariableSortedVectorType&
    StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getVariableSortedVector() const noexcept {
        return variableSortedVector_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::getNumberOfVariables() const noexcept {
        return static_cast<VarT>(variableSortedVector_.size());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::isSatisfiableUnderCompleteAssignment(const PartialAssignmentType& completeAssignment) const {
        #ifndef NDEBUG
        // Check all the variables are assigned
        for (const LiteralType& lit : formula_) {
            // The end of a clause
            if (lit.isZeroLiteral())
                continue;

            assert(completeAssignment.variableExists(lit.getVariable()));   // the variable is assigned
        }
        #endif

        for (FormulaSizeType clauseOffset : clauseOffsetVector_) {
            while (true) {
                const LiteralType& lit = formula_[clauseOffset];

                // The end of a clause
                if (lit.isZeroLiteral())
                    return false;

                // The clause is satisfied
                if (completeAssignment.literalExists(lit))
                    break;

                ++clauseOffset;
            }
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::unitPropagation(PartialAssignmentType& partialAssignment) const {
        BoolVectorType tmp(0);
        return unitPropagation(partialAssignment, tmp);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::unitPropagation(PartialAssignmentType& partialAssignment,
                                                                                               BoolVectorType& satisfiedClauseVector) const {
        assert(satisfiedClauseVector.empty() || satisfiedClauseVector.size() == numberOfClauses_);   // the correct size

        ClauseIdSetType clausesNeedToBeProcessed(numberOfClauses_);
        ClauseWatchedLiteralsVectorType clauseWatchedLiteralsVector(numberOfClauses_);
        MappingFromLiteralTToClauseIdVectorType mappingFromWatchedLiteralTToClauseIdVector((LiteralT)2 * (LiteralT)getNumberOfVariables());

        for (VarT var : variableSortedVector_) {
            if (partialAssignment.variableExists(var))
                continue;

            mappingFromWatchedLiteralTToClauseIdVector[getPositiveLiteralT<VarT, LiteralT>(var)] = {};
            mappingFromWatchedLiteralTToClauseIdVector[getNegativeLiteralT<VarT, LiteralT>(var)] = {};
        }

        // Initialize the watched literals
        for (ClauseIdT clauseId = 0; clauseId < numberOfClauses_; ++clauseId) {
            // Satisfied clause
            if (!satisfiedClauseVector.empty() && satisfiedClauseVector[clauseId])
                continue;

            ClauseWatchedLiteralsType& clauseWatchedLiterals = clauseWatchedLiteralsVector[clauseId];
            ClauseStatusWatchedLiteralEnum clauseStatusWatchedLiteral = initializeClauseWatchedLiterals(clauseId, clauseWatchedLiterals, partialAssignment);

            LiteralT firstWatchedLiteralT = 0;
            LiteralT secondWatchedLiteralT = 0;

            FormulaSizeType clauseOffset = clauseOffsetVector_[clauseId];

            switch (clauseStatusWatchedLiteral) {
                case ClauseStatusWatchedLiteralEnum::SATISFIED:
                    // Set the clause as satisfied
                    if (!satisfiedClauseVector.empty()) {
                        assert(!satisfiedClauseVector[clauseId]);   // not satisfied

                        satisfiedClauseVector[clauseId] = true;
                    }

                    break;
                case ClauseStatusWatchedLiteralEnum::EMPTY:
                    partialAssignment.clear();
                    return false;
                case ClauseStatusWatchedLiteralEnum::UNDEFINED:
                    assert(clauseWatchedLiterals.first.has_value());
                    assert(clauseWatchedLiterals.second.has_value());

                    // clausesNeedToBeProcessed.emplace(clauseId);

                    firstWatchedLiteralT = (formula_[clauseOffset + *(clauseWatchedLiterals.first)]).getLiteralT();
                    secondWatchedLiteralT = (formula_[clauseOffset + *(clauseWatchedLiterals.second)]).getLiteralT();

                    mappingFromWatchedLiteralTToClauseIdVector[firstWatchedLiteralT].emplace_back(clauseId);
                    mappingFromWatchedLiteralTToClauseIdVector[secondWatchedLiteralT].emplace_back(clauseId);
                    break;
                // Should NOT happen
                case ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_2:
                    assert(false);
                    break;
                case ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_1:
                    assert(clauseWatchedLiterals.first.has_value());
                    assert(!clauseWatchedLiterals.second.has_value());
                    assert(!partialAssignment.variableExists((formula_[clauseOffset + *(clauseWatchedLiterals.first)]).getVariable()));

                    const LiteralType& impliedLiteral = formula_[clauseOffset + *(clauseWatchedLiterals.first)];

                    partialAssignment.addLiteral(impliedLiteral);

                    if (auto itTmp = mappingFromWatchedLiteralTToClauseIdVector.find(impliedLiteral.getComplementaryLiteralT());
                        itTmp != mappingFromWatchedLiteralTToClauseIdVector.end()) {
                        for (ClauseIdT clauseIdTmp : itTmp->second)
                            clausesNeedToBeProcessed.emplace(clauseIdTmp);
                    }

                    // Set the clause as satisfied
                    if (!satisfiedClauseVector.empty()) {
                        assert(!satisfiedClauseVector[clauseId]);   // not satisfied

                        satisfiedClauseVector[clauseId] = true;
                    }

                    break;
            }
        }

        while (!clausesNeedToBeProcessed.empty()) {
            auto tmp = clausesNeedToBeProcessed.cbegin();
            ClauseIdT clauseId = *tmp;
            clausesNeedToBeProcessed.erase(tmp);

            FormulaSizeType clauseOffset = clauseOffsetVector_[clauseId];
            ClauseWatchedLiteralsType& clauseWatchedLiterals = clauseWatchedLiteralsVector[clauseId];

            assert(clauseWatchedLiterals.first.has_value());    // the first watched literal is set
            assert(clauseWatchedLiterals.second.has_value());   // the second watched literal is set

            LiteralT oldFirstWatchedLiteralT = (formula_[clauseOffset + *(clauseWatchedLiterals.first)]).getLiteralT();
            LiteralT oldSecondWatchedLiteralT = (formula_[clauseOffset + *(clauseWatchedLiterals.second)]).getLiteralT();

            assert(Other::containInVector(mappingFromWatchedLiteralTToClauseIdVector[oldFirstWatchedLiteralT], clauseId));
            assert(Other::containInVector(mappingFromWatchedLiteralTToClauseIdVector[oldSecondWatchedLiteralT], clauseId));

            ClauseStatusWatchedLiteralEnum clauseStatusWatchedLiteral = updateClauseWatchedLiterals(clauseId, clauseWatchedLiterals, partialAssignment);

            LiteralT newFirstWatchedLiteralT = 0;
            LiteralT newSecondWatchedLiteralT = 0;

            switch (clauseStatusWatchedLiteral) {
                case ClauseStatusWatchedLiteralEnum::SATISFIED:
                    Other::smartRemoveElementFromVector(mappingFromWatchedLiteralTToClauseIdVector[oldFirstWatchedLiteralT], clauseId);
                    Other::smartRemoveElementFromVector(mappingFromWatchedLiteralTToClauseIdVector[oldSecondWatchedLiteralT], clauseId);

                    // Set the clause as satisfied
                    if (!satisfiedClauseVector.empty()) {
                        assert(!satisfiedClauseVector[clauseId]);   // not satisfied

                        satisfiedClauseVector[clauseId] = true;
                    }

                    break;
                case ClauseStatusWatchedLiteralEnum::EMPTY:
                    partialAssignment.clear();
                    return false;
                case ClauseStatusWatchedLiteralEnum::UNDEFINED:
                    assert(clauseWatchedLiterals.first.has_value());
                    assert(clauseWatchedLiterals.second.has_value());

                    newFirstWatchedLiteralT = (formula_[clauseOffset + *(clauseWatchedLiterals.first)]).getLiteralT();
                    newSecondWatchedLiteralT = (formula_[clauseOffset + *(clauseWatchedLiterals.second)]).getLiteralT();

                    // The first watched literal has been changed
                    if (oldFirstWatchedLiteralT != newFirstWatchedLiteralT) {
                        Other::smartRemoveElementFromVector(mappingFromWatchedLiteralTToClauseIdVector[oldFirstWatchedLiteralT], clauseId);
                        mappingFromWatchedLiteralTToClauseIdVector[newFirstWatchedLiteralT].emplace_back(clauseId);
                    }

                    // The second watched literal has been changed
                    if (oldSecondWatchedLiteralT != newSecondWatchedLiteralT) {
                        Other::smartRemoveElementFromVector(mappingFromWatchedLiteralTToClauseIdVector[oldSecondWatchedLiteralT], clauseId);
                        mappingFromWatchedLiteralTToClauseIdVector[newSecondWatchedLiteralT].emplace_back(clauseId);
                    }

                    break;
                case ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_1:
                case ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_2:
                    Other::smartRemoveElementFromVector(mappingFromWatchedLiteralTToClauseIdVector[oldFirstWatchedLiteralT], clauseId);
                    Other::smartRemoveElementFromVector(mappingFromWatchedLiteralTToClauseIdVector[oldSecondWatchedLiteralT], clauseId);

                    const LiteralType& impliedLiteral = (clauseStatusWatchedLiteral == ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_1) ? formula_[clauseOffset + *(clauseWatchedLiterals.first)] : formula_[clauseOffset + *(clauseWatchedLiterals.second)];

                    partialAssignment.addLiteral(impliedLiteral);

                    if (auto itTmp = mappingFromWatchedLiteralTToClauseIdVector.find(impliedLiteral.getComplementaryLiteralT());
                        itTmp != mappingFromWatchedLiteralTToClauseIdVector.end()) {
                        for (ClauseIdT clauseIdTmp : itTmp->second)
                            clausesNeedToBeProcessed.emplace(clauseIdTmp);
                    }

                    clauseWatchedLiterals.first.reset();
                    clauseWatchedLiterals.second.reset();

                    // Set the clause as satisfied
                    if (!satisfiedClauseVector.empty()) {
                        assert(!satisfiedClauseVector[clauseId]);   // not satisfied

                        satisfiedClauseVector[clauseId] = true;
                    }

                    break;
            }
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::printFormulaInDimacsCnfFormat(std::ostream& out,
                                                                                                             const MappingFromVariableToVariableType& mappingFromVarToIndex) const {
        // Header
        out << Other::Parser::PROBLEM << " " << Other::Parser::CNF_HEADER_STRING << " " << std::to_string(variableSortedVector_.size()) << " " << std::to_string(numberOfClauses_) << std::endl;

        // Formula
        for (const LiteralType& lit : formula_) {
            // The end of a clause
            if (lit.isZeroLiteral()) {
                out << "0" << std::endl;

                continue;
            }

            VarT var = lit.getVariable();

            // Mapping function is used
            if (auto itTmp = mappingFromVarToIndex.find(var); itTmp != mappingFromVarToIndex.end())
                var = itTmp->second;

            if (lit.isPositive())
                out << std::to_string(var) << " ";
            else
                out << "-" << std::to_string(var) << " ";
        }
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void StructuralRestrictedFormulaRepresentation<VarT, LiteralT, ClauseIdT>::printStructuralRestrictedFormulaRepresentationDebug(std::ostream& out) const {
        out << "Structural restricted formula representation" << std::endl;
        out << "Type: " << structuralRestrictedFormulaRepresentationTypeEnumToString(structuralRestrictedFormulaRepresentationType_) << std::endl;
        out << "Formula size: " << std::to_string(formulaSize_) << std::endl;
        out << "Number of clauses: " << std::to_string(numberOfClauses_) << std::endl;

        // Variables
        out << "Variables:";
        for (VarT var : variableSortedVector_)
            out << " " << std::to_string(var);
        out << std::endl;

        // Switched variables
        if (structuralRestrictedFormulaRepresentationType_ == StructuralRestrictedFormulaRepresentationTypeEnum::renH_C) {
            out << "Switched variables:";
            for (VarT var : Other::sortUnorderedSet(switchedVariables_))
                out << " " << std::to_string(var);
            out << std::endl;
        }

        // Formula
        out << "Formula:";
        for (const LiteralType& lit : formula_) {
            // The end of a clause
            if (lit.isZeroLiteral())
                out << " 0";
            else
                out << " " << lit;
        }
        out << std::endl;

        // Clause offsets
        out << "Clause offsets:";
        for (FormulaSizeType clauseOffset : clauseOffsetVector_)
            out << " " << std::to_string(clauseOffset);
        out << std::endl;
    }
    #endif
}   // namespace Hydra::Formula::StructuralRestrictedRepresentation
