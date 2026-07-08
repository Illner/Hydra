#pragma once

#include <cassert>
#include <iostream>
#include <string>

#include "Hydra/external/satSolvers/MiniSat_d4/Solver.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/reusableVector/ReusableVector.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/satSolver/exceptions/SatSolverException.hpp"

#include "Hydra/satSolver/enums/SatSolverTypeEnum.hpp"
#include "Hydra/satSolver/minisat/enums/VsidsScoreTypeEnum.hpp"

#include "Hydra/satSolver/minisat/MiniSatSolver.tpp"

namespace Hydra::SatSolver::MiniSat {

    using VsidsScoreType = Hydra::SatSolver::VsidsScoreType;
    using FormulaSizeType = Hydra::Formula::Representation::FormulaSizeType;

    /**
     * MiniSat solver (final class)
     * Exceptions:
     *      SomethingCannotBeSavedAsIntException
     *      SomethingCannotBeSavedAsStdSizeTException
     *      SomethingWentWrongWhileInitializingSatSolverException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class MiniSatSolver final : public SatSolverAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using LiteralType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using BoolVectorType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::BoolVectorType;
        using VariableSetType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using LiteralVectorType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
        using LiteralReusableVectorType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralReusableVectorType;
        using SatSolverStatisticsPtrType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::SatSolverStatisticsPtrType;
        using FormulaRepresentationAbstractPtrType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    private:
        using MiniSatSolverType = minisat::Solver;
        using LiteralMiniSatVectorType = minisat::vec<minisat::Lit>;
        using VariableMiniSatVectorType = minisat::vec<minisat::Var>;
        using LiteralMiniSatReusableVectorType = Container::ReusableVector::ReusableVector<minisat::Lit>;

    public:
        MiniSatSolver(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, bool computeInitiallyImpliedLiterals,
                      const MiniSatSolverConfiguration& configuration = MiniSatSolverConfiguration(),
                      SatSolverStatisticsPtrType satSolverStatisticsPtr = nullptr)
            : SatSolverAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, SatSolverTypeEnum::MINISAT, satSolverStatisticsPtr),
              activeModel_(false), solver_(),
              variableAssumptionVector_(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), false),
              numberOfGetDecisionVariableCalls_(0), configuration_(configuration),
              l_restrictedVariableMiniSatVector_processIsSatisfiable_(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula()),
              l_firstCall_unitPropagation_(true), l_impliedLiteralMiniSatReusableVector_unitPropagation_() {
            // The variables cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<VarT>(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula(), 1))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("variables", this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());

            // The literals cannot be saved as int
            if (!Other::unsignedValueCanBeSavedAsInt<LiteralT>(this->formulaRepresentationAbstractPtr_->getNumberOfLiteralsInOriginalFormula()))
                throw Exception::SomethingCannotBeSavedAsIntException("literals", this->formulaRepresentationAbstractPtr_->getNumberOfLiteralsInOriginalFormula());

            // The clauses cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<ClauseIdT>(this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses()))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("clauses", this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses());

            this->initializeSatSolver();

            solver_.setNeedModel(false);

            // Compute initially implied literals
            if (computeInitiallyImpliedLiterals)
                this->computeAndSetInitiallyImpliedLiterals();
        }

    private:
        bool activeModel_;
        MiniSatSolverType solver_;
        BoolVectorType variableAssumptionVector_;
        LargeNumberType numberOfGetDecisionVariableCalls_;

        MiniSatSolverConfiguration configuration_;

        // Local auxiliary data structures for processIsSatisfiable
        VariableMiniSatVectorType l_restrictedVariableMiniSatVector_processIsSatisfiable_;

        // Local auxiliary data structures for unitPropagation
        bool l_firstCall_unitPropagation_;
        LiteralMiniSatReusableVectorType l_impliedLiteralMiniSatReusableVector_unitPropagation_;

    private:
        static bool lboolIsTrue(const minisat::lbool& b);
        static bool lboolIsFalse(const minisat::lbool& b);
        static bool lboolIsUndef(const minisat::lbool& b);

        static minisat::Var convertVariableToVariableMiniSat(VarT variable);
        static VarT convertVariableMiniSatToVariable(minisat::Var variableMiniSat);
        static minisat::Lit convertLiteralToLiteralMiniSat(const LiteralType& literal);
        static LiteralType convertLiteralMiniSatToLiteral(const minisat::Lit& literalMiniSat);

        /**
         * Initialize the SAT solver
         * @throw SomethingWentWrongWhileInitializingSatSolverException if something went wrong while initializing the SAT solver
         */
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

        void getDecisionVariableIsCalled() override;

        VsidsScoreType getVsidsScore(VarT variable) const override;

    #ifndef NDEBUG
    private:
        void processPrintSatSolverDebug(std::ostream& out, bool printCoreSatSolver, bool printLearntClauses) const override;

        /**
         * Print the assumptions
         * Note: prefix
         */
        void printAssumptionsDebug(std::ostream& out) const;

        /**
         * Print the current formula
         * Note: prefix
         */
        void printCurrentFormulaDebug(std::ostream& out, bool printLearntClauses = false) const;
    #endif
    };
}   // namespace Hydra::SatSolver::MiniSat

#include "./MiniSatSolver.ipp"
