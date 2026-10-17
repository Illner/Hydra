#pragma once

#include <iostream>

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/satSolver/exceptions/SatSolverException.hpp"

#include "Hydra/satSolver/enums/SatSolverTypeEnum.hpp"

#include "Hydra/satSolver/cadical/CadicalSolver.tpp"

namespace Hydra::SatSolver::Cadical {

    using VsidsScoreType = Hydra::SatSolver::VsidsScoreType;

    /**
     * CaDiCaL solver (final class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class CadicalSolver final : public SatSolverAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using LiteralType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using VariableSetType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using LiteralReusableVectorType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralReusableVectorType;
        using SatSolverStatisticsPtrType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::SatSolverStatisticsPtrType;
        using FormulaRepresentationAbstractPtrType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    public:
        explicit CadicalSolver(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                               const CadicalSolverConfiguration& configuration = CadicalSolverConfiguration(),
                               SatSolverStatisticsPtrType satSolverStatisticsPtr = nullptr)
            : SatSolverAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, SatSolverTypeEnum::CADICAL, satSolverStatisticsPtr),
              configuration_(configuration) { }

    private:
        CadicalSolverConfiguration configuration_;

    private:
        void processInitializeSatSolver() override;

        void processInitialSimplification() override;

        void processComputeAndSetInitiallyImpliedLiterals() override;

        void processAssignLiteral(const LiteralType& lit) override;

        void processUnassignLiteral(const LiteralType& lit) override;

        bool processIsSatisfiable() override;

        bool processIsSatisfiable(const VariableSetType& restrictedVariableSet) override;

        void processGetDecisionVariableIsCalled(const VariableSetType& currentComponentVariableSet) override;

        bool processUnitPropagation(const VariableSetType& restrictedVariableSet, LiteralReusableVectorType& impliedLiteralReusableVector,
                                    bool includeAssumptions) override;

        bool processUnitPropagation(const LiteralType& lit, const VariableSetType& restrictedVariableSet,
                                    LiteralReusableVectorType& impliedLiteralReusableVector) override;

    public:
        VsidsScoreType getVsidsScore(VarT variable) const override;

    #ifndef NDEBUG
    private:
        void processPrintSatSolverDebug(std::ostream& out, bool printCoreSatSolver, bool printLearntClauses) const override;
    #endif
    };
}   // namespace Hydra::SatSolver::Cadical

#include "./CadicalSolver.ipp"
