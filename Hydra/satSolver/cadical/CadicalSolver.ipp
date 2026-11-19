#pragma once

#include "./CadicalSolver.hpp"

namespace Hydra::SatSolver::Cadical {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    CadicalSolver<VarT, LiteralT, ClauseIdT>::VariableCadicalType
    CadicalSolver<VarT, LiteralT, ClauseIdT>::convertVariableToVariableCadical(VarT variable) {
        assert(variable > 0);   // valid variable

        return static_cast<VariableCadicalType>(variable);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT CadicalSolver<VarT, LiteralT, ClauseIdT>::convertVariableCadicalToVariable(VariableCadicalType variableCadical) {
        assert(variableCadical > 0);   // valid variable

        return static_cast<VarT>(variableCadical);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    CadicalSolver<VarT, LiteralT, ClauseIdT>::LiteralCadicalType
    CadicalSolver<VarT, LiteralT, ClauseIdT>::convertLiteralToLiteralCadical(const LiteralType& literal) {
        // Positive literal
        if (literal.isPositive())
            return convertVariableToVariableCadical(literal.getVariable());

        // Negative literal
        return -convertVariableToVariableCadical(literal.getVariable());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    CadicalSolver<VarT, LiteralT, ClauseIdT>::LiteralType
    CadicalSolver<VarT, LiteralT, ClauseIdT>::convertLiteralCadicalToLiteral(LiteralCadicalType literalCadical) {
        return LiteralType(convertVariableCadicalToVariable(convertLiteralCadicalToVariableCadical(literalCadical)), literalCadical > 0);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    CadicalSolver<VarT, LiteralT, ClauseIdT>::VariableCadicalType
    CadicalSolver<VarT, LiteralT, ClauseIdT>::convertLiteralCadicalToVariableCadical(LiteralCadicalType literalCadical) {
        assert(literalCadical != 0);   // valid literal

        return std::abs(literalCadical);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::bumpHydraVsidsScore() {
        if (configuration_.vsidsScoreType != VsidsScoreTypeEnum::HYDRA)
            return;

        // The trail when the unsatisfiability was found
        solver_.trail_above_root(l_trailLiteralCadicalVector_bumpHydraVsidsScore_);

        for (LiteralCadicalType litCadical : l_trailLiteralCadicalVector_bumpHydraVsidsScore_) {
            VarT var = convertVariableCadicalToVariable(convertLiteralCadicalToVariableCadical(litCadical));

            assert(var < hydraVsidsScoreVector_.size());

            ++hydraVsidsScoreVector_[var];
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::setSatSolverOptions() {
        assert((configuration_.reduceIntCadical >= 2) && (configuration_.reduceIntCadical <= 1'000'000));
        assert((configuration_.scoreFactorCadical >= 500) && (configuration_.scoreFactorCadical <= 1'000));

        // Default options
        // Reason: CaDiCaL's environment variables (CADICAL_<OPTION>) are not supported
        [[maybe_unused]] bool configured = solver_.configure("default");
        assert(configured);

        // Stable mode
        // Reason: VSIDS scores
        [[maybe_unused]] bool optionSet = solver_.set("stabilizeonly", 1);
        assert(optionSet);

        // No profiling
        // Reason: no time measurements due to performance
        optionSet = solver_.set("profile", 0);
        assert(optionSet);

        // No vivification of irredundant clauses
        // Reason: weak unit propagation, that is, it would be incomplete on the original clauses
        optionSet = solver_.set("vivifyirred", 0);
        assert(optionSet);

        // reduceOpt
        optionSet = solver_.set("reduceopt", static_cast<int>(configuration_.reduceOptTypeCadical));
        assert(optionSet);

        // reduceInt
        optionSet = solver_.set("reduceint", configuration_.reduceIntCadical);
        assert(optionSet);

        // reluctant
        optionSet = solver_.set("reluctant", configuration_.reluctantCadical ? 1 : 0);
        assert(optionSet);

        // scoreFactor
        optionSet = solver_.set("scorefactor", configuration_.scoreFactorCadical);
        assert(optionSet);

        // shrink
        optionSet = solver_.set("shrink", static_cast<int>(configuration_.shrinkTypeCadical));
        assert(optionSet);

        // targetPhases
        optionSet = solver_.set("target", configuration_.targetPhasesCadical ? 1 : 0);
        assert(optionSet);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processInitializeSatSolver() {
        VariableCadicalType numberOfVariables = static_cast<VariableCadicalType>(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());

        // Declare the variables
        [[maybe_unused]] VariableCadicalType maximumVariableIndex = solver_.declare_more_variables(numberOfVariables);
        assert(maximumVariableIndex == numberOfVariables);

        // Add the clauses
        const ClauseIdT numberOfOriginalClauses = this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses();
        for (ClauseIdT clauseId = 0; clauseId < numberOfOriginalClauses; ++clauseId) {
            for (auto clauseIt = this->formulaRepresentationAbstractPtr_->beginClause(clauseId);
                 clauseIt != this->formulaRepresentationAbstractPtr_->endClause(); ++clauseIt) {
                assert(convertVariableToVariableCadical(clauseIt->getVariable()) <= numberOfVariables);

                solver_.add(convertLiteralToLiteralCadical(*clauseIt));
            }

            solver_.add(0);   // end of the clause
        }

        // Freeze the variables
        // Reason: the variables MUST NOT be eliminated or substituted
        for (VariableCadicalType varCadical = 1; varCadical <= numberOfVariables; ++varCadical)
            solver_.freeze(varCadical);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processInitialSimplification() {
        assert(configuration_.maximumNumberOfPreprocessingRoundsForSimplificationCadical >= 0);

        [[maybe_unused]] int returnStatus = solver_.simplify(configuration_.maximumNumberOfPreprocessingRoundsForSimplificationCadical);
        assert(returnStatus != ReturnStatusEnum::UNSATISFIABLE);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processComputeAndSetInitiallyImpliedLiterals() {
        std::int64_t numberOfFixedVariables = solver_.get_statistic_value("fixed");
        assert(numberOfFixedVariables >= 0);   // statistics is supported

        this->initiallyImpliedLiterals_.reserve(static_cast<typename LiteralVectorType::size_type>(numberOfFixedVariables));

        VariableCadicalType numberOfVariables = static_cast<VariableCadicalType>(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());
        for (VariableCadicalType varCadical = 1; varCadical <= numberOfVariables; ++varCadical) {
            int value = solver_.fixed(varCadical);

            // The variable is not initially implied
            if (value == 0)
                continue;

            this->initiallyImpliedLiterals_.emplace_back(convertVariableCadicalToVariable(varCadical), value > 0);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processAssignLiteral(const LiteralType& lit) {
        solver_.push_assumption(convertLiteralToLiteralCadical(lit));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processUnassignLiteral(const LiteralType& lit) {
        // It is also checked whether the literal is the last pushed assumption
        solver_.pop_assumption(convertLiteralToLiteralCadical(lit));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool CadicalSolver<VarT, LiteralT, ClauseIdT>::processIsSatisfiable() {
        int returnStatus = solver_.solve();
        assert((returnStatus == ReturnStatusEnum::SATISFIABLE) || (returnStatus == ReturnStatusEnum::UNSATISFIABLE));   // since no limit is set

        // The current formula is NOT satisfiable => bump the Hydra VSIDS scores
        if (returnStatus == ReturnStatusEnum::UNSATISFIABLE)
            bumpHydraVsidsScore();

        return (returnStatus == ReturnStatusEnum::SATISFIABLE);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool CadicalSolver<VarT, LiteralT, ClauseIdT>::processIsSatisfiable(const VariableSetType& restrictedVariableSet) {
        l_restrictedVariableCadicalVector_processIsSatisfiable_.clear();

        for (VarT var : restrictedVariableSet)
            l_restrictedVariableCadicalVector_processIsSatisfiable_.emplace_back(convertVariableToVariableCadical(var));

        int returnStatus = solver_.solve_restricted(l_restrictedVariableCadicalVector_processIsSatisfiable_);
        assert((returnStatus == ReturnStatusEnum::SATISFIABLE) || (returnStatus == ReturnStatusEnum::UNSATISFIABLE));   // since no limit is set

        // The current formula is NOT satisfiable => bump the Hydra VSIDS scores
        if (returnStatus == ReturnStatusEnum::UNSATISFIABLE)
            bumpHydraVsidsScore();

        return (returnStatus == ReturnStatusEnum::SATISFIABLE);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processGetDecisionVariableIsCalled([[maybe_unused]] const VariableSetType& currentComponentVariableSet) {
        // Hydra
        if (configuration_.vsidsScoreType == VsidsScoreTypeEnum::HYDRA) {
            // Decay the variable scores
            if (configuration_.frequencyDecayHydraVsidsScore && !(this->numberOfGetDecisionVariableCalls_ % configuration_.frequencyDecayHydraVsidsScore)) {
                const std::size_t vectorSize = hydraVsidsScoreVector_.size();
                for (std::size_t i = 0; i < vectorSize; ++i)
                    hydraVsidsScoreVector_[i] /= 2;
            }
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool CadicalSolver<VarT, LiteralT, ClauseIdT>::processUnitPropagation(const VariableSetType& restrictedVariableSet,
                                                                          LiteralReusableVectorType& impliedLiteralReusableVector, bool includeAssumptions) {
        assert(impliedLiteralReusableVector.empty());

        // A contradiction was derived
        if (solver_.propagate() == ReturnStatusEnum::UNSATISFIABLE)
            return false;

        for (VarT var : restrictedVariableSet) {
            // It is an assumption
            if (!includeAssumptions && this->isVariableAssigned(var))
                continue;

            LiteralCadicalType value = solver_.trail_value(convertVariableToVariableCadical(var));

            // The variable is NOT implied
            if (value == 0)
                continue;

            impliedLiteralReusableVector.push_back(convertLiteralCadicalToLiteral(value));
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool CadicalSolver<VarT, LiteralT, ClauseIdT>::processUnitPropagation(const LiteralType& lit, const VariableSetType& restrictedVariableSet,
                                                                          LiteralReusableVectorType& impliedLiteralReusableVector) {
        // Initialize local auxiliary data structures
        if (l_firstCall_processUnitPropagation_) {
            l_impliedLiteralCadicalVector_processUnitPropagation_.reserve(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());

            l_firstCall_processUnitPropagation_ = false;
        }

        LiteralCadicalType litCadical = convertLiteralToLiteralCadical(lit);

        // Temporarily assume the literal
        solver_.push_assumption(litCadical);

        // A contradiction was derived
        if (solver_.propagate() == ReturnStatusEnum::UNSATISFIABLE) {
            solver_.pop_assumption(litCadical);

            return false;
        }

        // Get the implied literals
        solver_.implied_by_last_assumption(l_impliedLiteralCadicalVector_processUnitPropagation_);

        solver_.pop_assumption(litCadical);

        // Iterate the implied literals
        for (LiteralCadicalType impliedLitCadical : l_impliedLiteralCadicalVector_processUnitPropagation_) {
            LiteralType impliedLit = convertLiteralCadicalToLiteral(impliedLitCadical);

            if (!Other::containInSet(restrictedVariableSet, impliedLit.getVariable()))
                continue;

            assert(impliedLit != ~lit);                                    // not a complementary literal
            assert(!this->isVariableAssigned(impliedLit.getVariable()));   // variable is not assigned

            if (impliedLit == lit)
                continue;

            impliedLiteralReusableVector.push_back(std::move(impliedLit));
        }

        return true;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VsidsScoreType CadicalSolver<VarT, LiteralT, ClauseIdT>::getVsidsScore(VarT variable) const {
        switch (configuration_.vsidsScoreType) {
            // Hydra
            case VsidsScoreTypeEnum::HYDRA:
                assert(variable < hydraVsidsScoreVector_.size());

                return static_cast<VsidsScoreType>(hydraVsidsScoreVector_[variable]);
            // CaDiCaL
            case VsidsScoreTypeEnum::CADICAL:
                return static_cast<VsidsScoreType>(solver_.get_vsids_score(convertVariableToVariableCadical(variable)));
            default:
                throw Exception::NotImplementedException(vsidsScoreTypeEnumToString(configuration_.vsidsScoreType),
                                                         "Hydra::SatSolver::Cadical::CadicalSolver::getVsidsScore");
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool CadicalSolver<VarT, LiteralT, ClauseIdT>::CurrentFormulaPrinter::clause(const LiteralCadicalVectorType& clauseCadical) {
        for (LiteralCadicalType litCadical : clauseCadical) {
            // The clause is satisfied
            if (cadicalSolver_.assumption_trail_value(litCadical) == litCadical)
                return true;
        }

        for (LiteralCadicalType litCadical : clauseCadical) {
            // The literal is not assigned
            if (cadicalSolver_.assumption_trail_value(litCadical) == 0)
                out_ << convertLiteralCadicalToLiteral(litCadical) << " ";
        }

        // Print the end of the clause
        out_ << "0 ";

        return true;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processPrintSatSolverDebug(std::ostream& out, bool printCoreSatSolver, bool printLearntClauses) const {
        // Configuration
        out << "VSIDS score type: " << vsidsScoreTypeEnumToString(configuration_.vsidsScoreType) << std::endl;
        if (configuration_.vsidsScoreType == VsidsScoreTypeEnum::HYDRA)
            out << "Frequency decay for VSIDS score: " << std::to_string(configuration_.frequencyDecayHydraVsidsScore) << std::endl;
        out << "Reduce opt: " << reduceOptTypeEnumToString(configuration_.reduceOptTypeCadical) << std::endl;
        out << "Reduce interval: " << std::to_string(configuration_.reduceIntCadical) << std::endl;
        out << "Maximum number of preprocessing rounds for simplification: " << std::to_string(configuration_.maximumNumberOfPreprocessingRoundsForSimplificationCadical) << std::endl;
        out << "Stable reluctant doubling restarts: " << (configuration_.reluctantCadical ? "true" : "false") << std::endl;
        out << "Score factor per mille: " << std::to_string(configuration_.scoreFactorCadical) << std::endl;
        out << "Shrink conflict clause: " << shrinkTypeEnumToString(configuration_.shrinkTypeCadical) << std::endl;
        out << "Target phases: " << (configuration_.targetPhasesCadical ? "true" : "false") << std::endl;
        out << std::endl;

        if (!printCoreSatSolver)
            return;

        Other::printTitle(out, " CaDiCaL ", 19, '-');

        out << "Number of active variables: " << std::to_string(solver_.active()) << std::endl;
        out << "Number of irredundant clauses: " << std::to_string(solver_.irredundant()) << std::endl;
        if (printLearntClauses)
            out << "Number of redundant clauses: " << std::to_string(solver_.redundant()) << std::endl;

        // Number of assigned literals
        VarT numberOfAssignedLiterals = 0;
        const VarT numberOfVariables = this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula();
        for (VarT var = 1; var <= numberOfVariables; ++var) {
            if (solver_.assumption_trail_value(convertVariableToVariableCadical(var)) != 0)
                ++numberOfAssignedLiterals;
        }
        out << "Number of assigned literals: " << std::to_string(numberOfAssignedLiterals) << std::endl;

        printCurrentFormulaDebug(out);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::printCurrentFormulaDebug(std::ostream& out) const {
        out << "Current formula: ";

        // Print the current formula
        CurrentFormulaPrinter currentFormulaPrinter(solver_, out);
        bool ok = solver_.traverse_clauses(currentFormulaPrinter);
        assert(ok);

        out << "00" << std::endl;
    }
    #endif
}   // namespace Hydra::SatSolver::Cadical
