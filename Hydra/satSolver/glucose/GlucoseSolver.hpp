#pragma once

#include <cassert>
#include <iostream>
#include <string>

#include "Hydra/external/satSolvers/Glucose_d4/core/Solver.h"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/reusableVector/ReusableVector.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/satSolver/exceptions/SatSolverException.hpp"

#include "Hydra/satSolver/enums/SatSolverTypeEnum.hpp"
#include "Hydra/satSolver/glucose/enums/VsidsScoreTypeEnum.hpp"

#include "Hydra/satSolver/glucose/GlucoseSolver.tpp"

namespace Hydra::SatSolver::Glucose {

    using VsidsScoreType = Hydra::SatSolver::VsidsScoreType;

    /**
     * Glucose solver (final class)
     * Exceptions:
     *      SomethingCannotBeSavedAsIntException
     *      SomethingCannotBeSavedAsStdSizeTException
     *      SomethingWentWrongWhileInitializingSatSolverException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class GlucoseSolver final : public SatSolverAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using LiteralType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using BoolVectorType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::BoolVectorType;
        using VariableSetType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using LiteralVectorType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
        using LiteralReusableVectorType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralReusableVectorType;
        using SatSolverStatisticsPtrType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::SatSolverStatisticsPtrType;
        using FormulaRepresentationAbstractPtrType = typename SatSolverAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    private:
        using GlucoseSolverType = glucose_d4::Solver;
        using LiteralGlucoseVectorType = glucose_d4::vec<glucose_d4::Lit>;
        using VariableGlucoseVectorType = glucose_d4::vec<glucose_d4::Var>;
        using LiteralGlucoseReusableVectorType = Container::ReusableVector::ReusableVector<glucose_d4::Lit>;

    public:
        GlucoseSolver(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, bool computeInitiallyImpliedLiterals,
                      const GlucoseSolverConfiguration& configuration = GlucoseSolverConfiguration(),
                      SatSolverStatisticsPtrType satSolverStatisticsPtr = nullptr)
            : SatSolverAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, SatSolverTypeEnum::GLUCOSE, satSolverStatisticsPtr),
              activeModel_(false), solver_(),
              variableAssumptionVector_(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing(), false),
              numberOfGetDecisionVariableCalls_(0), configuration_(configuration),
              l_restrictedVariableGlucoseVector_processIsSatisfiable_(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula()),
              l_firstCall_unitPropagation_(true), l_impliedLiteralGlucoseReusableVector_unitPropagation_() {
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
        GlucoseSolverType solver_;
        BoolVectorType variableAssumptionVector_;
        LargeNumberType numberOfGetDecisionVariableCalls_;

        GlucoseSolverConfiguration configuration_;

        // Local auxiliary data structures for processIsSatisfiable
        VariableGlucoseVectorType l_restrictedVariableGlucoseVector_processIsSatisfiable_;

        // Local auxiliary data structures for unitPropagation
        bool l_firstCall_unitPropagation_;
        LiteralGlucoseReusableVectorType l_impliedLiteralGlucoseReusableVector_unitPropagation_;

    private:
        static bool lboolIsTrue(const glucose_d4::lbool& b);
        static bool lboolIsFalse(const glucose_d4::lbool& b);
        static bool lboolIsUndef(const glucose_d4::lbool& b);

        static glucose_d4::Var convertVariableToVariableGlucose(VarT variable);
        static VarT convertVariableGlucoseToVariable(glucose_d4::Var variableGlucose);
        static glucose_d4::Lit convertLiteralToLiteralGlucose(const LiteralType& literal);
        static LiteralType convertLiteralGlucoseToLiteral(const glucose_d4::Lit& literalGlucose);

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
}   // namespace Hydra::SatSolver::Glucose

#include "./GlucoseSolver.ipp"
