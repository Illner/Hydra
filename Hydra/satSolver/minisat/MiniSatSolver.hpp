#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

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
        using LiteralMiniSatVectorType = typename minisat::vec<minisat::Lit>;
        using LiteralType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using VariableSetType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using LiteralVectorType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
        using VariableVectorType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
        using LiteralReusableVectorType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralReusableVectorType;
        using SatSolverStatisticsPtrType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::SatSolverStatisticsPtrType;
        using FormulaRepresentationAbstractPtrType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    private:
        using BoolVectorType = std::vector<bool>;
        using MiniSatSolverType = minisat::Solver;
        using LiteralMiniSatReusableVectorType = Container::ReusableVector::ReusableVector<minisat::Lit>;

    public:
        MiniSatSolver(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, bool computeInitiallyImpliedLiterals,
                      const MiniSatSolverConfiguration& configuration = MiniSatSolverConfiguration(),
                      SatSolverStatisticsPtrType satSolverStatisticsPtr = nullptr)
            : SatSolverAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, SatSolverTypeEnum::MINISAT, satSolverStatisticsPtr),
              activeModel_(false), solver_(),
              variableAssumptionVector_(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), false),
              configuration_(configuration), l_firstCall_unitPropagation_(true), l_impliedLiteralMiniSatReusableVector_unitPropagation_() {
            // The variables cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<VarT>(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula(), 1))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("variables", this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());

            // The literals cannot be saved as int
            if (!Other::unsignedValueCanBeSavedAsInt<LiteralT>(this->formulaRepresentationAbstractPtr_->getNumberOfLiteralsInOriginalFormula()))
                throw Exception::SomethingCannotBeSavedAsIntException("literals", this->formulaRepresentationAbstractPtr_->getNumberOfLiteralsInOriginalFormula());

            // The clauses cannot be saved as int
            if (!Other::unsignedValueCanBeSavedAsInt<ClauseIdT>(this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses()))
                throw Exception::SomethingCannotBeSavedAsIntException("clauses", this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses());

            // The formula size cannot be saved as int
            if (!Other::unsignedValueCanBeSavedAsInt<FormulaSizeType>(this->formulaRepresentationAbstractPtr_->getOriginalFormulaSize()))
                throw Exception::SomethingCannotBeSavedAsIntException("formula size", this->formulaRepresentationAbstractPtr_->getOriginalFormulaSize());

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

        MiniSatSolverConfiguration configuration_;

        // Local auxiliary data structures for unitPropagation
        bool l_firstCall_unitPropagation_;
        LiteralMiniSatReusableVectorType l_impliedLiteralMiniSatReusableVector_unitPropagation_;

    private:
        bool lboolIsTrue(const minisat::lbool& b) const;
        bool lboolIsFalse(const minisat::lbool& b) const;
        bool lboolIsUndef(const minisat::lbool& b) const;

        minisat::Var convertVariableToVariableMiniSat(VarT variable) const;
        VarT convertVariableMiniSatToVariable(minisat::Var variableMiniSat) const;
        minisat::Lit convertLiteralToLiteralMiniSat(const LiteralType& literal) const;
        LiteralType convertLiteralMiniSatToLiteral(const minisat::Lit& literalMiniSat) const;

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

    public:
        VsidsScoreType getVsidsScore(VarT variable) const override;

    #ifndef NDEBUG
    private:
        void processPrintSatSolverDebug(std::ostream& out, bool printCoreSatSolver, bool printLearntClauses) const override;

        /**
         * Print the assumptions
         * Note: prefix
         */
        void printAssumptions(std::ostream& out) const;

        /**
         * Print the current formula
         * Note: prefix
         */
        void printCurrentFormula(std::ostream& out, bool printLearntClauses = false) const;
    #endif
    };
}   // namespace Hydra::SatSolver::MiniSat

#include "./MiniSatSolver.ipp"
