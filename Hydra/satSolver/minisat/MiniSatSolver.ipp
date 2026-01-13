#pragma once

#include "./MiniSatSolver.hpp"

namespace Hydra::SatSolver::MiniSat {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool MiniSatSolver<VarT, LiteralT, ClauseIdT>::lboolIsTrue(const minisat::lbool& b) const {
        return b == minisat::l_True;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool MiniSatSolver<VarT, LiteralT, ClauseIdT>::lboolIsFalse(const minisat::lbool& b) const {
        return b == minisat::l_False;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool MiniSatSolver<VarT, LiteralT, ClauseIdT>::lboolIsUndef(const minisat::lbool& b) const {
        return b == minisat::l_Undef;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    minisat::Var MiniSatSolver<VarT, LiteralT, ClauseIdT>::convertVariableToVariableMiniSat(VarT variable) const {
        assert(variable > 0);   // valid variable

        return static_cast<minisat::Var>(variable - 1);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT MiniSatSolver<VarT, LiteralT, ClauseIdT>::convertVariableMiniSatToVariable(minisat::Var variableMiniSat) const {
        assert(variableMiniSat >= 0);   // valid variable

        return static_cast<VarT>(variableMiniSat + 1);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    minisat::Lit MiniSatSolver<VarT, LiteralT, ClauseIdT>::convertLiteralToLiteralMiniSat(const LiteralType& literal) const {
        return minisat::mkLit(convertVariableToVariableMiniSat(literal.getVariable()), literal.isNegative());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename MiniSatSolver<VarT, LiteralT, ClauseIdT>::LiteralType
    MiniSatSolver<VarT, LiteralT, ClauseIdT>::convertLiteralMiniSatToLiteral(const minisat::Lit& literalMiniSat) const {
        return LiteralType(convertVariableMiniSatToVariable(minisat::var(literalMiniSat)), !minisat::sign(literalMiniSat));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::processInitializeSatSolver() {
        LiteralMiniSatVectorType clause;
        clause.capacity(this->S_ESTIMATED_SIZE_OF_CLAUSE_);

        // Add the variables
        for (VarT var = 1; var <= this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula(); ++var)
            solver_.newVar();

        for (ClauseIdT clauseId = 0; clauseId < this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses(); ++clauseId) {
            for (auto clauseIt = this->formulaRepresentationAbstractPtr_->beginClause(clauseId);
                 clauseIt != this->formulaRepresentationAbstractPtr_->endClause(); ++clauseIt) {
                assert(convertVariableToVariableMiniSat(clauseIt->getVariable()) < solver_.nVars());

                clause.push(convertLiteralToLiteralMiniSat(*clauseIt));
            }

            // Add the clause
            if (!solver_.addClause(clause))
                throw Exception::SatSolver::SomethingWentWrongWhileInitializingSatSolverException("adding clause " + std::to_string(clauseId));

            clause.clear();
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::processInitialSimplification() {
        assert(solver_.solveWithAssumptions());   // input formula is satisfiable

        solver_.simplify();
        solver_.remove_satisfied = false;

        this->computeAndSetInitiallyImpliedLiterals();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::processComputeAndSetInitiallyImpliedLiterals() {
        int numberOfAssignedLiterals = solver_.nAssigns();
        this->initiallyImpliedLiterals_.reserve(static_cast<typename LiteralVectorType::size_type>(numberOfAssignedLiterals));

        for (int i = 0; i < solver_.nVars(); ++i) {
            if (static_cast<int>(this->initiallyImpliedLiterals_.size()) == numberOfAssignedLiterals)
                break;

            minisat::Var var = static_cast<minisat::Var>(i);
            minisat::lbool value = solver_.value(var);

            // The variable is assigned
            if (!lboolIsUndef(value)) {
                if (lboolIsTrue(value))
                    this->initiallyImpliedLiterals_.emplace_back(convertVariableMiniSatToVariable(var), true);
                else
                    this->initiallyImpliedLiterals_.emplace_back(convertVariableMiniSatToVariable(var), false);
            }
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::processAssignLiteral(const LiteralType& lit) {
        assert(lit.getVariable() < variableAssumptionVector_.size());
        assert(!variableAssumptionVector_[lit.getVariable()]);   // variable is not assigned

        variableAssumptionVector_[lit.getVariable()] = true;

        minisat::Lit litMiniSat = convertLiteralToLiteralMiniSat(lit);
        activeModel_ = activeModel_ && !solver_.isAssigned(minisat::var(litMiniSat));

        solver_.assumptions.push(litMiniSat);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::processUnassignLiteral(const LiteralType& lit) {
        assert(lit.getVariable() < variableAssumptionVector_.size());
        assert(variableAssumptionVector_[lit.getVariable()]);   // variable is assigned
        assert(solver_.assumptions.last() == convertLiteralToLiteralMiniSat(lit));

        variableAssumptionVector_[lit.getVariable()] = false;

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
        minisat::vec<minisat::Var> restrictedVariableMiniSatVector;
        restrictedVariableMiniSatVector.capacity(restrictedVariableSet.size());

        for (VarT var : restrictedVariableSet)
            restrictedVariableMiniSatVector.push(convertVariableToVariableMiniSat(var));

        solver_.rebuildWithConnectedComponent(std::move(restrictedVariableMiniSatVector));

        activeModel_ = solver_.solveWithAssumptions();
        return activeModel_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool MiniSatSolver<VarT, LiteralT, ClauseIdT>::processUnitPropagation(const VariableSetType& restrictedVariableSet,
                                                                          LiteralReusableVectorType& impliedLiteralReusableVector, bool includeAssumptions) {
        assert(impliedLiteralReusableVector.empty());

        // The current formula is satisfiable
        if (solver_.propagateAssumption()) {
            // Iterating trail
            if (solver_.trail.size() < (int)restrictedVariableSet.size()) {
                for (int i = 0; i < solver_.trail.size(); ++i) {
                    const minisat::Lit& litMiniSat = solver_.trail[i];

                    VarT var = convertVariableMiniSatToVariable(minisat::var(litMiniSat));

                    assert(var < variableAssumptionVector_.size());

                    // It is an assumption
                    if (!includeAssumptions && variableAssumptionVector_[var])
                        continue;

                    if (!Other::containInSet(restrictedVariableSet, var))
                        continue;

                    impliedLiteralReusableVector.emplace_back(var, !minisat::sign(litMiniSat));
                }
            }
            // Iterating restricted variables
            else {
                for (VarT var : restrictedVariableSet) {
                    assert(var < variableAssumptionVector_.size());

                    // It is an assumption
                    if (!includeAssumptions && variableAssumptionVector_[var])
                        continue;

                    minisat::Var varMiniSat = convertVariableToVariableMiniSat(var);

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
    bool MiniSatSolver<VarT, LiteralT, ClauseIdT>::unitPropagation(const LiteralType& lit, const VariableSetType& restrictedVariableSet,
                                                                   LiteralReusableVectorType& impliedLiteralReusableVector) {
        assert(!variableAssumptionVector_[lit.getVariable()]);   // variable is not assigned

        // Initialize local auxiliary data structures
        if (l_firstCall_unitPropagation_) {
            l_impliedLiteralMiniSatReusableVector_unitPropagation_ = LiteralMiniSatReusableVectorType(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());

            l_firstCall_unitPropagation_ = false;
        }

        impliedLiteralReusableVector.clear();
        l_impliedLiteralMiniSatReusableVector_unitPropagation_.clear();

        solver_.refillAssums();

        // No contradiction was derived
        if (solver_.decideAndComputeUnit(convertLiteralToLiteralMiniSat(lit), l_impliedLiteralMiniSatReusableVector_unitPropagation_)) {
            // Iterate the implied literals
            for (const minisat::Lit& impliedLitMiniSat : l_impliedLiteralMiniSatReusableVector_unitPropagation_) {
                LiteralType impliedLit = convertLiteralMiniSatToLiteral(impliedLitMiniSat);

                if (!Other::containInSet(restrictedVariableSet, impliedLit.getVariable()))
                    continue;

                assert(impliedLit != ~lit);                                     // not a complementary literal
                assert(!variableAssumptionVector_[impliedLit.getVariable()]);   // variable is not assigned

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
    bool MiniSatSolver<VarT, LiteralT, ClauseIdT>::isVariableAssigned(VarT variable) const {
        assert(variable < variableAssumptionVector_.size());

        return variableAssumptionVector_[variable];
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

        out << "Assumption:";
        for (int i = 0; i < solver_.assumptions.size(); ++i)
            out << " " << convertLiteralMiniSatToLiteral(solver_.assumptions[i]);
        out << std::endl;

        out << "Variable assumption:";
        for (VarT var = 1; var < variableAssumptionVector_.size(); ++var) {
            if (variableAssumptionVector_[var])
                out << " " << std::to_string(var);
        }
        out << std::endl
            << std::endl;

        if (!printCoreSatSolver)
            return;

        Other::printTitle(out, " MiniSat ", 19, '-');

        out << "Number of variables: " << std::to_string(solver_.nVars()) << std::endl;
        out << "Number of clauses: " << std::to_string(solver_.nClauses()) << std::endl;
        if (printLearntClauses)
            out << "Number of learnt clauses: " << std::to_string(solver_.nLearnts()) << std::endl;
        out << "Number of assigned literals: " << std::to_string(solver_.nAssigns()) << std::endl;

        printAssumptions(out);
        printCurrentFormula(out, printLearntClauses);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::printAssumptions(std::ostream& out) const {
        out << "Assumptions: ";

        for (int i = 0; i < solver_.assumptions.size(); ++i) {
            if (minisat::sign(solver_.assumptions[i]))
                out << "-";

            out << std::to_string(convertVariableMiniSatToVariable(minisat::var(solver_.assumptions[i]))) << " ";
        }

        out << std::endl;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void MiniSatSolver<VarT, LiteralT, ClauseIdT>::printCurrentFormula(std::ostream& out, bool printLearntClauses) const {
        out << "Current formula: ";

        for (int i = 0; i < solver_.clauses.size(); ++i) {
            const auto& clause = solver_.ca[solver_.clauses[i]];

            if (solver_.satisfied(clause))
                continue;

            for (int j = 0; j < clause.size(); ++j) {
                const minisat::Lit& lit = clause[j];

                // The literal is not assigned
                if (lboolIsUndef(solver_.value(lit))) {
                    if (minisat::sign(lit))
                        out << "-";

                    out << std::to_string(convertVariableMiniSatToVariable(minisat::var(lit))) << " ";
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
                    const minisat::Lit& lit = clause[j];

                    // The literal is not assigned
                    if (lboolIsUndef(solver_.value(lit))) {
                        if (minisat::sign(lit))
                            out << "-";

                        out << std::to_string(convertVariableMiniSatToVariable(minisat::var(lit))) << " ";
                    }
                }

                out << "0 ";
            }

            out << "00" << std::endl;
        }
    }
    #endif
}   // namespace Hydra::SatSolver::MiniSat
