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
        return LiteralType(convertVariableCadicalToVariable(std::abs(literalCadical)), literalCadical > 0);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::bumpHydraVsidsScore() {
        throw Exception::NotImplementedException("", "bumpHydraVsidsScore");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processInitializeSatSolver() {
        throw Exception::NotImplementedException("", "processInitializeSatSolver");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processInitialSimplification() {
        throw Exception::NotImplementedException("", "processInitialSimplification");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processComputeAndSetInitiallyImpliedLiterals() {
        throw Exception::NotImplementedException("", "processComputeAndSetInitiallyImpliedLiterals");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processAssignLiteral([[maybe_unused]] const LiteralType& lit) {
        throw Exception::NotImplementedException("", "processAssignLiteral");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processUnassignLiteral([[maybe_unused]] const LiteralType& lit) {
        throw Exception::NotImplementedException("", "processUnassignLiteral");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool CadicalSolver<VarT, LiteralT, ClauseIdT>::processIsSatisfiable() {
        throw Exception::NotImplementedException("", "processIsSatisfiable");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool CadicalSolver<VarT, LiteralT, ClauseIdT>::processIsSatisfiable([[maybe_unused]] const VariableSetType& restrictedVariableSet) {
        throw Exception::NotImplementedException("", "processIsSatisfiable (restriction)");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processGetDecisionVariableIsCalled([[maybe_unused]] const VariableSetType& currentComponentVariableSet) {
        throw Exception::NotImplementedException("", "processGetDecisionVariableIsCalled");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool CadicalSolver<VarT, LiteralT, ClauseIdT>::processUnitPropagation([[maybe_unused]] const VariableSetType& restrictedVariableSet,
                                                                          [[maybe_unused]] LiteralReusableVectorType& impliedLiteralReusableVector,
                                                                          [[maybe_unused]] bool includeAssumptions) {
        throw Exception::NotImplementedException("", "processUnitPropagation");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool CadicalSolver<VarT, LiteralT, ClauseIdT>::processUnitPropagation([[maybe_unused]] const LiteralType& lit,
                                                                          [[maybe_unused]] const VariableSetType& restrictedVariableSet,
                                                                          [[maybe_unused]] LiteralReusableVectorType& impliedLiteralReusableVector) {
        throw Exception::NotImplementedException("", "processUnitPropagation");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VsidsScoreType CadicalSolver<VarT, LiteralT, ClauseIdT>::getVsidsScore([[maybe_unused]] VarT variable) const {
        throw Exception::NotImplementedException("", "getVsidsScore");
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::processPrintSatSolverDebug([[maybe_unused]] std::ostream& out, [[maybe_unused]] bool printCoreSatSolver,
                                                                              [[maybe_unused]] bool printLearntClauses) const {
        throw Exception::NotImplementedException("", "processPrintSatSolverDebug");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CadicalSolver<VarT, LiteralT, ClauseIdT>::printCurrentFormulaDebug([[maybe_unused]] std::ostream& out) const {
        throw Exception::NotImplementedException("", "printCurrentFormulaDebug");
    }
    #endif
}   // namespace Hydra::SatSolver::Cadical
