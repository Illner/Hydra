#pragma once

#include "./SatSolverAbstract.hpp"

namespace Hydra::SatSolver {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void SatSolverAbstract<VarT, LiteralT, ClauseIdT>::initializeSatSolver() {
        // Statistics
        if (satSolverStatisticsPtr_)
            satSolverStatisticsPtr_->initializeTimer.startStopwatch();

        processInitializeSatSolver();

        // Statistics
        if (satSolverStatisticsPtr_)
            satSolverStatisticsPtr_->initializeTimer.stopStopwatch();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void SatSolverAbstract<VarT, LiteralT, ClauseIdT>::initialSimplification() {
        assert(!d_initialSimplification_);   // has not yet been called

        // Statistics
        if (satSolverStatisticsPtr_)
            satSolverStatisticsPtr_->initialSimplificationTimer.startStopwatch();

        processInitialSimplification();

        // Statistics
        if (satSolverStatisticsPtr_)
            satSolverStatisticsPtr_->initialSimplificationTimer.stopStopwatch();

        #ifndef NDEBUG
        d_initialSimplification_ = true;
        #endif
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void SatSolverAbstract<VarT, LiteralT, ClauseIdT>::computeAndSetInitiallyImpliedLiterals() {
        // Statistics
        if (satSolverStatisticsPtr_)
            satSolverStatisticsPtr_->initiallyImpliedLiteralsTimer.startStopwatch();

        processComputeAndSetInitiallyImpliedLiterals();

        // Statistics
        if (satSolverStatisticsPtr_) {
            satSolverStatisticsPtr_->numberOfInitiallyImpliedLiteralsNumber.setNumber(static_cast<Statistics::LargeNumberType>(initiallyImpliedLiterals_.size()));
            satSolverStatisticsPtr_->ratioOfNumberOfInitiallyImpliedLiteralsToNumberOfVariablesNumber.setNumber(static_cast<Statistics::LargeFloatingNumberType>(initiallyImpliedLiterals_.size()) / static_cast<Statistics::LargeFloatingNumberType>(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula()));

            satSolverStatisticsPtr_->initiallyImpliedLiteralsTimer.stopStopwatch();
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void SatSolverAbstract<VarT, LiteralT, ClauseIdT>::assignLiteral(const LiteralType& lit,
                                                                     [[maybe_unused]] bool checkLiteral) {
        processAssignLiteral(lit);

        #ifndef NDEBUG
        // Check if the added literal corresponds to the partial assignment in the formula representation
        if (checkLiteral) {
            const LiteralType& litInPartialAssignment = formulaRepresentationAbstractPtr_->getIthElementOfPartialAssignmentDebug(d_numberOfAssignedVariables_);

            if (lit != litInPartialAssignment)
                throw Exception::SatSolver::IthElementOfAssignmentDoesNotCorrespondToIthElementOfPartialAssignmentException(d_numberOfAssignedVariables_,
                                                                                                                            lit, litInPartialAssignment);
        }

        ++d_numberOfAssignedVariables_;
        #endif
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void SatSolverAbstract<VarT, LiteralT, ClauseIdT>::assignLiteralVector(const LiteralVectorType& literalVector, bool checkLiterals) {
        for (const LiteralType& lit : literalVector)
            assignLiteral(lit, checkLiterals);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void SatSolverAbstract<VarT, LiteralT, ClauseIdT>::unassignLiteral(const LiteralType& lit) {
        processUnassignLiteral(lit);

        #ifndef NDEBUG
        assert(d_numberOfAssignedVariables_ > 0);
        --d_numberOfAssignedVariables_;
        #endif
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void SatSolverAbstract<VarT, LiteralT, ClauseIdT>::unassignLiteralVector(const LiteralVectorType& literalVector, bool reverse) {
        // Remove literals in the reverse order
        if (reverse) {
            for (auto it = literalVector.rbegin(); it != literalVector.rend(); ++it)
                unassignLiteral(*it);
        }

        // Remove literals in the standard order
        else {
            for (const LiteralType& lit : literalVector)
                unassignLiteral(lit);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool SatSolverAbstract<VarT, LiteralT, ClauseIdT>::isSatisfiable() {
        assert(d_numberOfAssignedVariables_ == 0);   // no assignment

        // Statistics
        if (satSolverStatisticsPtr_)
            satSolverStatisticsPtr_->isSatisfiableTimer.startStopwatch();

        bool isSatisfiable = processIsSatisfiable();

        // Statistics
        if (satSolverStatisticsPtr_)
            satSolverStatisticsPtr_->isSatisfiableTimer.stopStopwatch();

        return isSatisfiable;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool SatSolverAbstract<VarT, LiteralT, ClauseIdT>::isSatisfiable(const VariableSetType& restrictedVariableSet) {
        assert(!restrictedVariableSet.empty());   // at least one variable

        // Statistics
        if (satSolverStatisticsPtr_)
            satSolverStatisticsPtr_->isSatisfiableTimer.startStopwatch();

        bool isSatisfiable = processIsSatisfiable(restrictedVariableSet);

        // Statistics
        if (satSolverStatisticsPtr_)
            satSolverStatisticsPtr_->isSatisfiableTimer.stopStopwatch();

        return isSatisfiable;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool SatSolverAbstract<VarT, LiteralT, ClauseIdT>::unitPropagation(const VariableSetType& restrictedVariableSet, bool includeAssumptions) {
        // Initialize local auxiliary data structures
        if (l_firstCall_unitPropagation_) {
            l_impliedLiteralReusableVector_unitPropagation_ = LiteralReusableVectorType(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());

            l_firstCall_unitPropagation_ = false;
        }

        // Can happen
        if (restrictedVariableSet.empty())
            return true;

        // Statistics
        if (satSolverStatisticsPtr_)
            satSolverStatisticsPtr_->unitPropagationTimer.startStopwatch();

        l_impliedLiteralReusableVector_unitPropagation_.clear();

        bool isSatisfiable = processUnitPropagation(restrictedVariableSet, l_impliedLiteralReusableVector_unitPropagation_, includeAssumptions);

        assert(isSatisfiable || l_impliedLiteralReusableVector_unitPropagation_.empty());   // contradiction -> not implied literals

        // Statistics
        if (satSolverStatisticsPtr_) {
            // The formula is satisfiable
            if (isSatisfiable) {
                satSolverStatisticsPtr_->numberOfImpliedLiteralsCounter.addCount(static_cast<Statistics::LargeNumberType>(l_impliedLiteralReusableVector_unitPropagation_.size()));
                satSolverStatisticsPtr_->ratioOfNumberOfImpliedLiteralsToNumberOfVariablesCounter.addCount(static_cast<Statistics::LargeFloatingNumberType>(l_impliedLiteralReusableVector_unitPropagation_.size()) / static_cast<Statistics::LargeFloatingNumberType>(restrictedVariableSet.size()));
            }

            satSolverStatisticsPtr_->unitPropagationTimer.stopStopwatch();
        }

        return isSatisfiable;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType
    SatSolverAbstract<VarT, LiteralT, ClauseIdT>::getImpliedLiteralVectorFromPreviousCallOfUnitPropagation(bool sort) const {
        assert(!l_firstCall_unitPropagation_);   // reusable vector has been initialized

        LiteralVectorType impliedLiteralVector(l_impliedLiteralReusableVector_unitPropagation_.cbegin(), l_impliedLiteralReusableVector_unitPropagation_.cend());

        if (sort)
            std::sort(impliedLiteralVector.begin(), impliedLiteralVector.end());

        return impliedLiteralVector;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    const SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralReusableVectorType&
    SatSolverAbstract<VarT, LiteralT, ClauseIdT>::getImpliedLiteralReusableVectorFromPreviousCallOfUnitPropagation() const {
        assert(!l_firstCall_unitPropagation_);   // reusable vector has been initialized

        return l_impliedLiteralReusableVector_unitPropagation_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::EquivalencePreprocessingStruct
    SatSolverAbstract<VarT, LiteralT, ClauseIdT>::createEquivalencePreprocessingStruct(const VariableSetType& selectedVariableSet,
                                                                                       bool ignoreMultiOccurrentIgnoredVariables,
                                                                                       ImplicitBcpVariableOrderTypeEnum implicitBcpVariableOrderType) {
        // Statistics
        if (satSolverStatisticsPtr_)
            satSolverStatisticsPtr_->createEquivalencePreprocessingStructTimer.startStopwatch();

        // Initialize local auxiliary data structures
        if (l_firstCall_createEquivalencePreprocessingStruct_) {
            l_variableOrderReusableVector_createEquivalencePreprocessingStruct_ = VariableReusableVectorType(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());
            l_ignoredVariableVectorSet_createEquivalencePreprocessingStruct_ = VectorSetType(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing());
            l_positiveUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_ = LiteralReusableVectorType(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());
            l_negativeUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_ = LiteralReusableVectorType(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());
            l_positiveLiteralTVectorSet_createEquivalencePreprocessingStruct_ = VectorSetType(Formula::getNegativeLiteralT<VarT, LiteralT>(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula()));

            l_firstCall_createEquivalencePreprocessingStruct_ = false;
        }

        // Initialize equivalence preprocessing structure
        EquivalencePreprocessingStruct equivalencePreprocessingStruct;
        equivalencePreprocessingStruct.implicitImpliedLiteralVector.reserve(selectedVariableSet.size());
        equivalencePreprocessingStruct.equivalencePreprocessingStructure.reserve(selectedVariableSet.size());
        equivalencePreprocessingStruct.ignoreMultiOccurrentIgnoredVariables = ignoreMultiOccurrentIgnoredVariables;

        l_ignoredVariableVectorSet_createEquivalencePreprocessingStruct_.clear();
        l_variableOrderReusableVector_createEquivalencePreprocessingStruct_.copySet(selectedVariableSet);

        // Order the variables for implicit BCP
        switch (implicitBcpVariableOrderType) {
            case ImplicitBcpVariableOrderTypeEnum::RANDOM:
                break;
            case ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX:
                l_variableOrderReusableVector_createEquivalencePreprocessingStruct_.sort();
                break;
            case ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_ASCENDING:
                formulaRepresentationAbstractPtr_->sortVariablesBasedOnClauseReductionHeuristic(selectedVariableSet,
                                                                                                l_variableOrderReusableVector_createEquivalencePreprocessingStruct_,
                                                                                                true);
                break;
            case ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_DESCENDING:
                formulaRepresentationAbstractPtr_->sortVariablesBasedOnClauseReductionHeuristic(selectedVariableSet,
                                                                                                l_variableOrderReusableVector_createEquivalencePreprocessingStruct_,
                                                                                                false);
                break;
            default:
                throw Exception::NotImplementedException(implicitBcpVariableOrderTypeEnumToString(implicitBcpVariableOrderType),
                                                         "Hydra::SatSolver::SatSolverAbstract::createEquivalencePreprocessingStruct");
        }

        for (VarT var : l_variableOrderReusableVector_createEquivalencePreprocessingStruct_) {
            // The variable is ignored
            if (l_ignoredVariableVectorSet_createEquivalencePreprocessingStruct_.contains(var))
                continue;

            // The variable is implicit implied
            if (isVariableAssigned(var)) {
                assert(Other::containInVector(equivalencePreprocessingStruct.implicitImpliedLiteralVector, LiteralType(var, true)) ||
                       Other::containInVector(equivalencePreprocessingStruct.implicitImpliedLiteralVector, LiteralType(var, false)));

                continue;
            }

            LiteralType posLit(var, true);
            LiteralType negLit(var, false);

            // Positive literal
            // Contradiction -> negative literal is implied
            if (!unitPropagation(posLit, selectedVariableSet, l_positiveUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_)) {
                assignLiteral(negLit, false);
                equivalencePreprocessingStruct.implicitImpliedLiteralVector.emplace_back(var, false);

                continue;
            }

            // Negative literal
            // Contradiction -> positive literal is implied
            if (!unitPropagation(negLit, selectedVariableSet, l_negativeUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_)) {
                assignLiteral(posLit, false);
                equivalencePreprocessingStruct.implicitImpliedLiteralVector.emplace_back(var, true);

                continue;
            }

            if (l_positiveUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_.empty() ||
                l_negativeUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_.empty())
                continue;

            equivalencePreprocessingStruct.equivalencePreprocessingStructure.emplace_back();
            equivalencePreprocessingStruct.equivalencePreprocessingStructure.back().emplace_back(var);   // reflexivity

            l_positiveLiteralTVectorSet_createEquivalencePreprocessingStruct_.clear();

            for (const LiteralType& lit : l_positiveUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_) {
                assert(Other::containInSet(selectedVariableSet, lit.getVariable()));   // is a selected variable
                assert(!isVariableAssigned(lit.getVariable()));                        // not an implicit implied literal

                // The variable is already ignored
                if (ignoreMultiOccurrentIgnoredVariables && l_ignoredVariableVectorSet_createEquivalencePreprocessingStruct_.contains(lit.getVariable()))
                    continue;

                l_positiveLiteralTVectorSet_createEquivalencePreprocessingStruct_.emplace(lit.getLiteralT() - 1);   // "-1" due to indexing
            }

            for (const LiteralType& lit : l_negativeUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_) {
                assert(Other::containInSet(selectedVariableSet, lit.getVariable()));   // is a selected variable
                assert(!isVariableAssigned(lit.getVariable()));                        // not an implicit implied literal

                // Opposite sign -> ignored variable
                if (l_positiveLiteralTVectorSet_createEquivalencePreprocessingStruct_.contains(lit.getComplementaryLiteralT() - 1)) {
                    assert(!l_positiveLiteralTVectorSet_createEquivalencePreprocessingStruct_.contains(lit.getLiteralT() - 1));

                    l_ignoredVariableVectorSet_createEquivalencePreprocessingStruct_.emplace(lit.getVariable(), ignoreMultiOccurrentIgnoredVariables);

                    equivalencePreprocessingStruct.equivalencePreprocessingStructure.back().emplace_back(lit.getVariable());

                    continue;
                }

                // Same sign -> literal is implicit implied
                if (l_positiveLiteralTVectorSet_createEquivalencePreprocessingStruct_.contains(lit.getLiteralT() - 1)) {
                    assignLiteral(lit, false);
                    equivalencePreprocessingStruct.implicitImpliedLiteralVector.emplace_back(lit.getVariable(), lit.isPositive());

                    continue;
                }
            }

            // Singleton
            if (equivalencePreprocessingStruct.equivalencePreprocessingStructure.back().size() == 1)
                equivalencePreprocessingStruct.equivalencePreprocessingStructure.pop_back();
        }

        assert(equivalencePreprocessingStruct.equivalencePreprocessingStructure.size() <= selectedVariableSet.size());

        #ifndef NDEBUG
        for (const VariableVectorType& variableVector : equivalencePreprocessingStruct.equivalencePreprocessingStructure)
            assert(variableVector.size() > 1);
        #endif

        // Statistics
        if (satSolverStatisticsPtr_) {
            satSolverStatisticsPtr_->ratioOfNumberOfIgnoredVariablesToNumberOfVariablesCounter.addCount(static_cast<Statistics::LargeFloatingNumberType>(l_ignoredVariableVectorSet_createEquivalencePreprocessingStruct_.size()) / static_cast<Statistics::LargeFloatingNumberType>(selectedVariableSet.size()));
            satSolverStatisticsPtr_->ratioOfNumberOfImplicitImpliedLiteralsToNumberOfVariablesCounter.addCount(static_cast<Statistics::LargeFloatingNumberType>(equivalencePreprocessingStruct.implicitImpliedLiteralVector.size()) / static_cast<Statistics::LargeFloatingNumberType>(selectedVariableSet.size()));

            satSolverStatisticsPtr_->createEquivalencePreprocessingStructTimer.stopStopwatch();
        }

        return equivalencePreprocessingStruct;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    const typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType&
    SatSolverAbstract<VarT, LiteralT, ClauseIdT>::getInitiallyImpliedLiterals() const noexcept {
        return initiallyImpliedLiterals_;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void SatSolverAbstract<VarT, LiteralT, ClauseIdT>::printSatSolverDebug(std::ostream& out, bool printCoreSatSolver,
                                                                           bool printCurrentFormula, bool printLearntClauses) const {
        out << "SAT solver" << std::endl;
        out << "Type: " << satSolverTypeEnumToString(satSolverType_) << std::endl;

        // Initially implied literals
        out << "Initially implied literals:";
        for (const LiteralType& lit : initiallyImpliedLiterals_)
            out << " " << lit;
        out << std::endl;

        // Current formula
        if (printCurrentFormula) {
            out << "Current formula: ";
            formulaRepresentationAbstractPtr_->printCurrentFormulaDebug(out);
            out << std::endl;
        }

        // SAT solver
        this->processPrintSatSolverDebug(out, printCoreSatSolver, printLearntClauses);

        out << std::endl;
    }
    #endif
}   // namespace Hydra::SatSolver
