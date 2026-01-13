#pragma once

#include <iostream>

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/satSolver/exceptions/SatSolverException.hpp"

#include "Hydra/satSolver/enums/SatSolverTypeEnum.hpp"

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
        using LiteralType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using VariableSetType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using LiteralReusableVectorType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralReusableVectorType;
        using SatSolverStatisticsPtrType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::SatSolverStatisticsPtrType;
        using FormulaRepresentationAbstractPtrType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    public:
        explicit CadicalSolver(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                               SatSolverStatisticsPtrType satSolverStatisticsPtr = nullptr)
            : SatSolverAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, SatSolverTypeEnum::CADICAL, satSolverStatisticsPtr) { }

    private:
        void processInitializeSatSolver() override;

        void processInitialSimplification() override;

        void processComputeAndSetInitiallyImpliedLiterals() override;

        void processAssignLiteral(const LiteralType& lit) override;

        void processUnassignLiteral(const LiteralType& lit) override;

        bool processIsSatisfiable() override;

        bool processIsSatisfiable(const VariableSetType& restrictedVariableSet) override;

        bool processUnitPropagation(const VariableSetType& restrictedVariableSet, LiteralReusableVectorType& impliedLiteralReusableVector,
                                    bool includeAssumptions) override;

        bool unitPropagation(const LiteralType& lit, const VariableSetType& restrictedVariableSet,
                             LiteralReusableVectorType& impliedLiteralReusableVector) override;

        bool isVariableAssigned(VarT variable) const override;

    public:
        VsidsScoreType getVsidsScore(VarT variable) const override;

    #ifndef NDEBUG
    private:
        void processPrintSatSolverDebug(std::ostream& out, bool printCoreSatSolver, bool printLearntClauses) const override;
    #endif
    };
}   // namespace Hydra::SatSolver::Cadical

#include "./CadicalSolver.ipp"
