#pragma once

#include "./MiniSatSolver.hpp"

namespace Hydra::SatSolver::MiniSat {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool MiniSatSolver<VarT, LiteralT, ClauseIdT>::lboolIsTrue(const MiniSatCore::lbool& b) {
        return b == MiniSatCore::l_True;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool MiniSatSolver<VarT, LiteralT, ClauseIdT>::lboolIsFalse(const MiniSatCore::lbool& b) {
        return b == MiniSatCore::l_False;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool MiniSatSolver<VarT, LiteralT, ClauseIdT>::lboolIsUndef(const MiniSatCore::lbool& b) {
        return b == MiniSatCore::l_Undef;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    MiniSatSolver<VarT, LiteralT, ClauseIdT>::VariableMiniSatType
    MiniSatSolver<VarT, LiteralT, ClauseIdT>::convertVariableToVariableMiniSat(VarT variable) {
        assert(variable > 0);   // valid variable

        return static_cast<VariableMiniSatType>(variable - 1);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT MiniSatSolver<VarT, LiteralT, ClauseIdT>::convertVariableMiniSatToVariable(VariableMiniSatType variableMiniSat) {
        assert(variableMiniSat >= 0);   // valid variable

        return static_cast<VarT>(variableMiniSat + 1);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    MiniSatSolver<VarT, LiteralT, ClauseIdT>::LiteralMiniSatType
    MiniSatSolver<VarT, LiteralT, ClauseIdT>::convertLiteralToLiteralMiniSat(const LiteralType& literal) {
        return MiniSatCore::mkLit(convertVariableToVariableMiniSat(literal.getVariable()), literal.isNegative());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename MiniSatSolver<VarT, LiteralT, ClauseIdT>::LiteralType
    MiniSatSolver<VarT, LiteralT, ClauseIdT>::convertLiteralMiniSatToLiteral(const LiteralMiniSatType& literalMiniSat) {
        return LiteralType(convertVariableMiniSatToVariable(MiniSatCore::var(literalMiniSat)), !MiniSatCore::sign(literalMiniSat));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::processInitializeSatSolver() {
        LiteralMiniSatVectorType clause;
        clause.capacity(static_cast<int>(this->formulaRepresentationAbstractPtr_->getMaxOriginalClauseSize()));

        // Add the variables
        for (VarT var = 1; var <= this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula(); ++var)
            solver_.newVar();

        for (ClauseIdT clauseId = 0; clauseId < this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses(); ++clauseId) {
            for (auto clauseIt = this->formulaRepresentationAbstractPtr_->beginClause(clauseId);
                 clauseIt != this->formulaRepresentationAbstractPtr_->endClause(); ++clauseIt) {
                assert(convertVariableToVariableMiniSat(clauseIt->getVariable()) < solver_.nVars());

                clause.push(convertLiteralToLiteralMiniSat(*clauseIt));
            }

            solver_.addClause(clause);   // add the clause

            clause.clear();   // clear the clause
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::processInitialSimplification() {
        solver_.simplify();
        solver_.remove_satisfied = false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::processComputeAndSetInitiallyImpliedLiterals() {
        this->initiallyImpliedLiterals_.reserve(static_cast<typename LiteralVectorType::size_type>(solver_.nAssigns()));

        for (int i = 0; i < solver_.trail.size(); ++i) {
            const LiteralMiniSatType& litMiniSat = solver_.trail[i];

            this->initiallyImpliedLiterals_.emplace_back(convertLiteralMiniSatToLiteral(litMiniSat));
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::processAssignLiteral(const LiteralType& lit) {
        LiteralMiniSatType litMiniSat = convertLiteralToLiteralMiniSat(lit);
        activeModel_ = activeModel_ && !solver_.isAssigned(MiniSatCore::var(litMiniSat));

        solver_.assumptions.push(litMiniSat);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::processUnassignLiteral([[maybe_unused]] const LiteralType& lit) {
        assert(solver_.assumptions.last() == convertLiteralToLiteralMiniSat(lit));

        solver_.assumptions.pop();
        solver_.cancelUntil(solver_.assumptions.size());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool MiniSatSolver<VarT, LiteralT, ClauseIdT>::processIsSatisfiable() {
        // solver_.rebuildWithAllVar();

        return solver_.solveWithAssumptions();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool MiniSatSolver<VarT, LiteralT, ClauseIdT>::processIsSatisfiable(const VariableSetType& restrictedVariableSet) {
        l_restrictedVariableMiniSatVector_processIsSatisfiable_.clear();

        for (VarT var : restrictedVariableSet)
            l_restrictedVariableMiniSatVector_processIsSatisfiable_.push(convertVariableToVariableMiniSat(var));

        solver_.rebuildWithConnectedComponent(l_restrictedVariableMiniSatVector_processIsSatisfiable_);

        activeModel_ = solver_.solveWithAssumptions();
        return activeModel_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::processGetDecisionVariableIsCalled([[maybe_unused]] const VariableSetType& currentComponentVariableSet) {
        // D4v2
        if (configuration_.vsidsScoreType == VsidsScoreTypeEnum::D4_V2) {
            // Decay the variable scores
            if (configuration_.frequencyDecayD4v2VsidsScore && !(this->numberOfGetDecisionVariableCalls_ % configuration_.frequencyDecayD4v2VsidsScore)) {
                for (int i = 0; i < solver_.scoreActivityD4v2.size(); ++i)
                    solver_.scoreActivityD4v2[i] /= 2;
            }
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool MiniSatSolver<VarT, LiteralT, ClauseIdT>::processUnitPropagation(const VariableSetType& restrictedVariableSet,
                                                                          LiteralReusableVectorType& impliedLiteralReusableVector, bool includeAssumptions) {
        assert(impliedLiteralReusableVector.empty());

        // The current formula is satisfiable
        if (solver_.propagateAssumption()) {
            // Iterating trail
            if (solver_.trail.size() < static_cast<int>(restrictedVariableSet.size())) {
                for (int i = 0; i < solver_.trail.size(); ++i) {
                    const LiteralMiniSatType& litMiniSat = solver_.trail[i];

                    VarT var = convertVariableMiniSatToVariable(MiniSatCore::var(litMiniSat));

                    // It is an assumption
                    if (!includeAssumptions && this->isVariableAssigned(var))
                        continue;

                    if (!Other::containInSet(restrictedVariableSet, var))
                        continue;

                    impliedLiteralReusableVector.emplace_back(var, !MiniSatCore::sign(litMiniSat));
                }
            }
            // Iterating restricted variables
            else {
                for (VarT var : restrictedVariableSet) {
                    // It is an assumption
                    if (!includeAssumptions && this->isVariableAssigned(var))
                        continue;

                    VariableMiniSatType varMiniSat = convertVariableToVariableMiniSat(var);

                    if (!solver_.isAssigned(varMiniSat))
                        continue;

                    impliedLiteralReusableVector.push_back(convertLiteralMiniSatToLiteral(solver_.litAssigned(varMiniSat)));
                }
            }

            return true;
        }

        // The current formula is NOT satisfiable
        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool MiniSatSolver<VarT, LiteralT, ClauseIdT>::processUnitPropagation(const LiteralType& lit, const VariableSetType& restrictedVariableSet,
                                                                          LiteralReusableVectorType& impliedLiteralReusableVector) {
        // Initialize local auxiliary data structures
        if (l_firstCall_processUnitPropagation_) {
            l_impliedLiteralMiniSatReusableVector_processUnitPropagation_ = LiteralMiniSatReusableVectorType(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());

            l_firstCall_processUnitPropagation_ = false;
        }

        l_impliedLiteralMiniSatReusableVector_processUnitPropagation_.clear();

        solver_.refillAssums();

        // No contradiction was derived
        if (solver_.decideAndComputeUnit(convertLiteralToLiteralMiniSat(lit), l_impliedLiteralMiniSatReusableVector_processUnitPropagation_)) {
            // Iterate the implied literals
            for (const LiteralMiniSatType& impliedLitMiniSat : l_impliedLiteralMiniSatReusableVector_processUnitPropagation_) {
                LiteralType impliedLit = convertLiteralMiniSatToLiteral(impliedLitMiniSat);

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

        // A contradiction was derived
        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VsidsScoreType MiniSatSolver<VarT, LiteralT, ClauseIdT>::getVsidsScore(VarT variable) const {
        switch (configuration_.vsidsScoreType) {
            // D4
            case VsidsScoreTypeEnum::D4:
                return static_cast<VsidsScoreType>(solver_.scoreActivityD4[convertVariableToVariableMiniSat(variable)]);
            // D4v2
            case VsidsScoreTypeEnum::D4_V2:
                return static_cast<VsidsScoreType>(solver_.scoreActivityD4v2[convertVariableToVariableMiniSat(variable)]);
            // MiniSat
            case VsidsScoreTypeEnum::MINISAT:
                return static_cast<VsidsScoreType>(solver_.activity[convertVariableToVariableMiniSat(variable)]);
            default:
                throw Exception::NotImplementedException(vsidsScoreTypeEnumToString(configuration_.vsidsScoreType),
                                                         "Hydra::SatSolver::MiniSat::MiniSatSolver::getVsidsScore");
        }
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::processPrintSatSolverDebug(std::ostream& out, bool printCoreSatSolver, bool printLearntClauses) const {
        // Configuration
        out << "VSIDS score type: " << vsidsScoreTypeEnumToString(configuration_.vsidsScoreType) << std::endl;
        if (configuration_.vsidsScoreType == VsidsScoreTypeEnum::D4_V2)
            out << "Frequency decay for VSIDS score: " << std::to_string(configuration_.frequencyDecayD4v2VsidsScore) << std::endl;
        out << std::endl;

        if (!printCoreSatSolver)
            return;

        Other::printTitle(out, " MiniSat ", 19, '-');

        out << "Number of variables: " << std::to_string(solver_.nVars()) << std::endl;
        out << "Number of clauses: " << std::to_string(solver_.nClauses()) << std::endl;
        if (printLearntClauses)
            out << "Number of learnt clauses: " << std::to_string(solver_.nLearnts()) << std::endl;
        out << "Number of assigned literals: " << std::to_string(solver_.nAssigns()) << std::endl;

        printAssumptionsDebug(out);
        printCurrentFormulaDebug(out, printLearntClauses);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::printAssumptionsDebug(std::ostream& out) const {
        out << "Assumptions: ";

        for (int i = 0; i < solver_.assumptions.size(); ++i) {
            if (MiniSatCore::sign(solver_.assumptions[i]))
                out << "-";

            out << std::to_string(convertVariableMiniSatToVariable(MiniSatCore::var(solver_.assumptions[i]))) << " ";
        }

        out << std::endl;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::printCurrentFormulaDebug(std::ostream& out, bool printLearntClauses) const {
        out << "Current formula: ";

        for (int i = 0; i < solver_.clauses.size(); ++i) {
            const auto& clause = solver_.ca[solver_.clauses[i]];

            if (solver_.satisfied(clause))
                continue;

            for (int j = 0; j < clause.size(); ++j) {
                const LiteralMiniSatType& lit = clause[j];

                // The literal is not assigned
                if (lboolIsUndef(solver_.value(lit))) {
                    if (MiniSatCore::sign(lit))
                        out << "-";

                    out << std::to_string(convertVariableMiniSatToVariable(MiniSatCore::var(lit))) << " ";
                }
            }

            out << "0 ";
        }

        out << "00" << std::endl;

        // Learnt clauses
        if (printLearntClauses) {
            out << "Learnt clauses: ";

            for (int i = 0; i < solver_.learnts.size(); ++i) {
                const auto& clause = solver_.ca[solver_.learnts[i]];

                if (solver_.satisfied(clause))
                    continue;

                for (int j = 0; j < clause.size(); ++j) {
                    const LiteralMiniSatType& lit = clause[j];

                    // The literal is not assigned
                    if (lboolIsUndef(solver_.value(lit))) {
                        if (MiniSatCore::sign(lit))
                            out << "-";

                        out << std::to_string(convertVariableMiniSatToVariable(MiniSatCore::var(lit))) << " ";
                    }
                }

                out << "0 ";
            }

            out << "00" << std::endl;
        }
    }
    #endif
}   // namespace Hydra::SatSolver::MiniSat
