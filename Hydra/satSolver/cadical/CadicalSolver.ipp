#pragma once

#include "./CadicalSolver.hpp"

namespace Hydra::SatSolver::Cadical {

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
    bool CadicalSolver<VarT, LiteralT, ClauseIdT>::processUnitPropagation([[maybe_unused]] const VariableSetType& restrictedVariableSet,
                                                                          [[maybe_unused]] LiteralReusableVectorType& impliedLiteralReusableVector,
                                                                          [[maybe_unused]] bool includeAssumptions) {
        throw Exception::NotImplementedException("", "processUnitPropagation");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool CadicalSolver<VarT, LiteralT, ClauseIdT>::unitPropagation([[maybe_unused]] const LiteralType& lit,
                                                                   [[maybe_unused]] const VariableSetType& restrictedVariableSet,
                                                                   LiteralReusableVectorType& impliedLiteralReusableVector) {
        impliedLiteralReusableVector.clear();

        throw Exception::NotImplementedException("", "unitPropagation");
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool CadicalSolver<VarT, LiteralT, ClauseIdT>::isVariableAssigned([[maybe_unused]] VarT variable) const {
        throw Exception::NotImplementedException("", "isVariableAssigned");
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
    #endif
}   // namespace Hydra::SatSolver::Cadical
