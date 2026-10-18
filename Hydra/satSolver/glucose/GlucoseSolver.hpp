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

#include "Hydra/satSolver/enums/SatSolverTypeEnum.hpp"
#include "Hydra/satSolver/glucose/enums/VsidsScoreTypeEnum.hpp"

#include "Hydra/satSolver/glucose/GlucoseSolver.tpp"

namespace Hydra::SatSolver::Glucose {

    namespace GlucoseCore = glucose_d4;

    using VsidsScoreType = Hydra::SatSolver::VsidsScoreType;

    /**
     * Glucose solver (final class)
     * Exceptions:
     *      SomethingCannotBeSavedAsIntException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class GlucoseSolver final : public SatSolverAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using LiteralType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using VariableSetType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using LiteralVectorType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
        using LiteralReusableVectorType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralReusableVectorType;
        using SatSolverStatisticsPtrType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::SatSolverStatisticsPtrType;
        using FormulaRepresentationAbstractPtrType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    private:
        using GlucoseSolverType = GlucoseCore::Solver;
        using LiteralGlucoseVectorType = GlucoseCore::vec<GlucoseCore::Lit>;
        using VariableGlucoseVectorType = GlucoseCore::vec<GlucoseCore::Var>;
        using LiteralGlucoseReusableVectorType = Container::ReusableVector::ReusableVector<GlucoseCore::Lit>;

    public:
        explicit GlucoseSolver(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                               const GlucoseSolverConfiguration& configuration = GlucoseSolverConfiguration(),
                               SatSolverStatisticsPtrType satSolverStatisticsPtr = nullptr)
            : SatSolverAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, SatSolverTypeEnum::GLUCOSE, satSolverStatisticsPtr),
              activeModel_(false), configuration_(configuration),
              l_restrictedVariableGlucoseVector_processIsSatisfiable_(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula()),
              l_firstCall_processUnitPropagation_(true) {
            // The literals cannot be saved as int
            if (!Other::unsignedValueCanBeSavedAsInt<LiteralT>(this->formulaRepresentationAbstractPtr_->getNumberOfLiteralsInOriginalFormula()))
                throw Exception::SomethingCannotBeSavedAsIntException("literals", this->formulaRepresentationAbstractPtr_->getNumberOfLiteralsInOriginalFormula());

            // The clauses cannot be saved as int
            if (!Other::unsignedValueCanBeSavedAsInt<ClauseIdT>(this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses()))
                throw Exception::SomethingCannotBeSavedAsIntException("clauses", this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses());

            this->initializeSatSolver();

            solver_.setNeedModel(false);
        }

    private:
        bool activeModel_;
        GlucoseSolverType solver_;

        GlucoseSolverConfiguration configuration_;

        // Local auxiliary data structures for processIsSatisfiable
        VariableGlucoseVectorType l_restrictedVariableGlucoseVector_processIsSatisfiable_;

        // Local auxiliary data structures for processUnitPropagation
        bool l_firstCall_processUnitPropagation_;
        LiteralGlucoseReusableVectorType l_impliedLiteralGlucoseReusableVector_processUnitPropagation_;

    private:
        static bool lboolIsTrue(const GlucoseCore::lbool& b);
        static bool lboolIsFalse(const GlucoseCore::lbool& b);
        static bool lboolIsUndef(const GlucoseCore::lbool& b);

        static GlucoseCore::Var convertVariableToVariableGlucose(VarT variable);
        static VarT convertVariableGlucoseToVariable(GlucoseCore::Var variableGlucose);
        static GlucoseCore::Lit convertLiteralToLiteralGlucose(const LiteralType& literal);
        static LiteralType convertLiteralGlucoseToLiteral(const GlucoseCore::Lit& literalGlucose);

        /**
         * Initialize the SAT solver
         */
        void processInitializeSatSolver() override;

        void processInitialSimplification() override;

        void processComputeAndSetInitiallyImpliedLiterals() override;

        void processAssignLiteral(const LiteralType& lit) override;

        void processUnassignLiteral(const LiteralType& lit) override;

        bool processIsSatisfiable() override;

        /**
         * Local auxiliary data structures:
         *      l_restrictedVariableGlucoseVector_processIsSatisfiable_
         */
        bool processIsSatisfiable(const VariableSetType& restrictedVariableSet) override;

        void processGetDecisionVariableIsCalled(const VariableSetType& currentComponentVariableSet) override;

        bool processUnitPropagation(const VariableSetType& restrictedVariableSet, LiteralReusableVectorType& impliedLiteralReusableVector,
                                    bool includeAssumptions) override;

        /**
         * Local auxiliary data structures:
         *      l_firstCall_processUnitPropagation_
         *      l_impliedLiteralGlucoseReusableVector_processUnitPropagation_
         */
        bool processUnitPropagation(const LiteralType& lit, const VariableSetType& restrictedVariableSet,
                                    LiteralReusableVectorType& impliedLiteralReusableVector) override;

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
