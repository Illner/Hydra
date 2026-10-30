#pragma once

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "Hydra/external/satSolvers/CaDiCaL/src/cadical.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/satSolver/cadical/enums/VsidsScoreTypeEnum.hpp"
#include "Hydra/satSolver/enums/SatSolverTypeEnum.hpp"

#include "Hydra/satSolver/cadical/CadicalSolver.tpp"

namespace Hydra::SatSolver::Cadical {

    namespace CadicalCore = CaDiCaL;

    using VsidsScoreType = Hydra::SatSolver::VsidsScoreType;

    /**
     * CaDiCaL solver (final class)
     * Exceptions:
     *      SomethingCannotBeSavedAsIntException
     *      SomethingCannotBeSavedAsStdSizeTException
     *      SomethingCannotBeSavedAsTypeNameException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class CadicalSolver final : public SatSolverAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using LiteralType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using VariableSetType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using LiteralVectorType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralVectorType;
        using LiteralReusableVectorType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::LiteralReusableVectorType;
        using SatSolverStatisticsPtrType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::SatSolverStatisticsPtrType;
        using FormulaRepresentationAbstractPtrType = SatSolverAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    private:
        using LiteralCadicalType = int;
        using VariableCadicalType = int;
        using CadicalSolverType = CadicalCore::Solver;
        using HydraVsidsScoreVectorType = std::vector<double>;
        using LiteralCadicalVectorType = std::vector<LiteralCadicalType>;
        using VariableCadicalVectorType = std::vector<VariableCadicalType>;

    private:
        using ReturnStatusEnum = CadicalCore::Status;

    public:
        explicit CadicalSolver(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                               const CadicalSolverConfiguration& configuration = CadicalSolverConfiguration(),
                               SatSolverStatisticsPtrType satSolverStatisticsPtr = nullptr)
            : SatSolverAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, SatSolverTypeEnum::CADICAL, satSolverStatisticsPtr),
              hydraVsidsScoreVector_((configuration.vsidsScoreType == VsidsScoreTypeEnum::HYDRA ? this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing() : 0), 1),
              configuration_(configuration), l_firstCall_processUnitPropagation_(true) {
            // The literals cannot be saved as int
            if (!Other::unsignedValueCanBeSavedAsInt<LiteralT>(this->formulaRepresentationAbstractPtr_->getNumberOfLiteralsInOriginalFormula(), 3))
                throw Exception::SomethingCannotBeSavedAsIntException("literals", this->formulaRepresentationAbstractPtr_->getNumberOfLiteralsInOriginalFormula());

            // The clauses cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<ClauseIdT>(this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses()))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("clauses", this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses());

            // The clauses cannot be saved as std::int64_t
            if (!Other::unsignedValueCanBeSavedAsTypeT<std::int64_t>(this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses()))
                throw Exception::SomethingCannotBeSavedAsTypeNameException("clauses", this->formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses(), "std::int64_t");

            if (configuration_.vsidsScoreType == VsidsScoreTypeEnum::HYDRA)
                l_trailLiteralCadicalVector_bumpHydraVsidsScore_.reserve(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());

            l_restrictedVariableCadicalVector_processIsSatisfiable_.reserve(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());

            setSatSolverOptions();
            this->initializeSatSolver();
        }

    private:
        CadicalSolverType solver_;
        HydraVsidsScoreVectorType hydraVsidsScoreVector_;

        CadicalSolverConfiguration configuration_;

        // Local auxiliary data structures for bumpHydraVsidsScore
        LiteralCadicalVectorType l_trailLiteralCadicalVector_bumpHydraVsidsScore_;

        // Local auxiliary data structures for processIsSatisfiable
        VariableCadicalVectorType l_restrictedVariableCadicalVector_processIsSatisfiable_;

        // Local auxiliary data structures for processUnitPropagation
        bool l_firstCall_processUnitPropagation_;
        LiteralCadicalVectorType l_impliedLiteralCadicalVector_processUnitPropagation_;

    private:
        static VariableCadicalType convertVariableToVariableCadical(VarT variable);
        static VarT convertVariableCadicalToVariable(VariableCadicalType variableCadical);
        static LiteralCadicalType convertLiteralToLiteralCadical(const LiteralType& literal);
        static LiteralType convertLiteralCadicalToLiteral(LiteralCadicalType literalCadical);
        static VariableCadicalType convertLiteralCadicalToVariableCadical(LiteralCadicalType literalCadical);

        /**
         * Bump the Hydra VSIDS score of the variables on the trail when unsatisfiability is found
         * Local auxiliary data structures:
         *      l_trailLiteralCadicalVector_bumpHydraVsidsScore_
         */
        void bumpHydraVsidsScore();

        /**
         * Set options of the SAT solver
         * Note: options MUST be set at the beginning
         */
        void setSatSolverOptions();

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
         *      l_restrictedVariableCadicalVector_processIsSatisfiable_
         */
        bool processIsSatisfiable(const VariableSetType& restrictedVariableSet) override;

        void processGetDecisionVariableIsCalled(const VariableSetType& currentComponentVariableSet) override;

        bool processUnitPropagation(const VariableSetType& restrictedVariableSet, LiteralReusableVectorType& impliedLiteralReusableVector,
                                    bool includeAssumptions) override;

        /**
         * Local auxiliary data structures:
         *      l_firstCall_processUnitPropagation_
         *      l_impliedLiteralCadicalVector_processUnitPropagation_
         */
        bool processUnitPropagation(const LiteralType& lit, const VariableSetType& restrictedVariableSet,
                                    LiteralReusableVectorType& impliedLiteralReusableVector) override;

        VsidsScoreType getVsidsScore(VarT variable) const override;

    #ifndef NDEBUG
    private:
        /**
         * Note: CaDiCaL cannot traverse the learnt clauses
         */
        void processPrintSatSolverDebug(std::ostream& out, bool printCoreSatSolver, bool printLearntClauses) const override;

        /**
         * Print the current formula
         * Note: prefix
         * Note: CaDiCaL cannot traverse the learnt clauses
         */
        void printCurrentFormulaDebug(std::ostream& out) const;
    #endif
    };
}   // namespace Hydra::SatSolver::Cadical

#include "./CadicalSolver.ipp"
