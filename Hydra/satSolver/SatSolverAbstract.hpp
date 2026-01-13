#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/reusableVector/ReusableVector.hpp"
#include "Hydra/other/container/vectorSet/VectorSet.hpp"
#include "Hydra/satSolver/EquivalencePreprocessingStructure.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/satSolver/exceptions/SatSolverException.hpp"

#include "Hydra/satSolver/enums/ImplicitBcpVariableOrderTypeEnum.hpp"
#include "Hydra/satSolver/enums/SatSolverTypeEnum.hpp"

#include "Hydra/satSolver/SatSolverAbstract.hxx"

namespace Hydra::SatSolver {

    using VsidsScoreType = long double;   // 128 bits

    /**
     * SAT solver representation (abstract class)
     * Copy and move methods are disabled!
     * Exception:
     *      SatSolverDoesNotSupportVsidsException
     *      SatSolverDoesNotSupportUnitPropagationException
     *      IthElementOfAssignmentDoesNotCorrespondToIthElementOfPartialAssignmentException (debug)
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class SatSolverAbstract {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");
        static_assert(Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isValidClauseT::value, "Invalid ClauseIdT type!");

    public:
        using LiteralType = typename Formula::Literal<VarT, LiteralT>::LiteralType;
        using VariableSetType = typename Formula::Literal<VarT, LiteralT>::VariableSetType;
        using LiteralVectorType = typename Formula::Literal<VarT, LiteralT>::LiteralVectorType;
        using VariableVectorType = typename Formula::Literal<VarT, LiteralT>::VariableVectorType;
        using SatSolverStatisticsPtrType = typename SatSolverStatistics::SatSolverStatisticsPtrType;

    public:
        using LiteralReusableVectorType = Container::ReusableVector::ReusableVector<LiteralType>;
        using FormulaRepresentationAbstractPtrType = const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;

    public:
        using EquivalencePreprocessingStruct = SatSolver::EquivalencePreprocessingStruct<VarT, LiteralT>;

    private:
        using VariableReusableVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableReusableVectorType;

    private:
        using VectorSetType = Container::VectorSet::VectorSet;

    public:
        SatSolverAbstract(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, SatSolverTypeEnum satSolverType,
                          SatSolverStatisticsPtrType satSolverStatisticsPtr) noexcept
            : satSolverType_(satSolverType), l_firstCall_unitPropagation_(true), l_impliedLiteralReusableVector_unitPropagation_(),
              l_firstCall_createEquivalencePreprocessingStruct_(true), l_ignoredVariableVectorSet_createEquivalencePreprocessingStruct_(),
              l_positiveLiteralTVectorSet_createEquivalencePreprocessingStruct_(), l_variableOrderReusableVector_createEquivalencePreprocessingStruct_(),
              l_positiveUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_(),
              l_negativeUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_(), initiallyImpliedLiterals_(),
              formulaRepresentationAbstractPtr_(formulaRepresentationAbstractPtr), satSolverStatisticsPtr_(satSolverStatisticsPtr) { }

        SatSolverAbstract(const SatSolverAbstract&) = delete;
        SatSolverAbstract(SatSolverAbstract&&) noexcept = delete;

        SatSolverAbstract& operator=(const SatSolverAbstract&) = delete;
        SatSolverAbstract& operator=(SatSolverAbstract&&) noexcept = delete;

        virtual ~SatSolverAbstract() noexcept = default;

    private:
        SatSolverTypeEnum satSolverType_;

        // Local auxiliary data structures for unitPropagation
        bool l_firstCall_unitPropagation_;
        LiteralReusableVectorType l_impliedLiteralReusableVector_unitPropagation_;

        // Local auxiliary data structures for createEquivalencePreprocessingStruct
        bool l_firstCall_createEquivalencePreprocessingStruct_;
        VectorSetType l_ignoredVariableVectorSet_createEquivalencePreprocessingStruct_;
        VectorSetType l_positiveLiteralTVectorSet_createEquivalencePreprocessingStruct_;
        VariableReusableVectorType l_variableOrderReusableVector_createEquivalencePreprocessingStruct_;
        LiteralReusableVectorType l_positiveUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_;
        LiteralReusableVectorType l_negativeUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_;

    protected:
        LiteralVectorType initiallyImpliedLiterals_;
        FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr_;

        SatSolverStatisticsPtrType satSolverStatisticsPtr_;

        inline static constexpr int S_ESTIMATED_SIZE_OF_CLAUSE_ = 4;

    protected:
        virtual void processInitializeSatSolver() = 0;

        virtual void processInitialSimplification() = 0;

        virtual void processComputeAndSetInitiallyImpliedLiterals() = 0;

        virtual void processAssignLiteral(const LiteralType& lit) = 0;

        virtual void processUnassignLiteral(const LiteralType& lit) = 0;

        virtual bool processIsSatisfiable() = 0;

        virtual bool processIsSatisfiable(const VariableSetType& restrictedVariableSet) = 0;

        virtual bool processUnitPropagation(const VariableSetType& restrictedVariableSet, LiteralReusableVectorType& impliedLiteralReusableVector,
                                            bool includeAssumptions) = 0;

        /**
         * Assign the literal and do unit propagation (that is, boolean constraint propagation)
         * Assert: the literal MUST NOT be assigned
         * Note: the implied literals are NOT assigned
         * Note: impliedLiteralReusableVector will be cleared at the beginning
         * @param lit a literal
         * @param restrictedVariableSet a restriction
         * @param impliedLiteralReusableVector a reusable vector of implied literals
         * @return true if NO contradiction was derived. Otherwise, false is returned.
         * @throw SatSolverDoesNotSupportUnitPropagationException if the SAT solver does not support unit propagation
         */
        virtual bool unitPropagation(const LiteralType& lit, const VariableSetType& restrictedVariableSet,
                                     LiteralReusableVectorType& impliedLiteralReusableVector) = 0;

        /**
         * Initialize the SAT solver
         * Note: used for statistics
         */
        void initializeSatSolver();

        /**
         * Compute and set the initially implied literals
         * Note: used for statistics
         */
        void computeAndSetInitiallyImpliedLiterals();

        /**
         * @param variable a variable
         * @return true if the variable is assigned. Otherwise, false is returned.
         */
        virtual bool isVariableAssigned(VarT variable) const = 0;

    public:
        /**
         * Initial simplification
         * Assert: MUST be called at most once
         * Note: used for statistics
         * Note: called only once at the beginning of the compilation
         */
        void initialSimplification();

        /**
         * Assign the literal
         * Assert: the literal MUST NOT be assigned
         * @param lit a literal
         * @param checkLiteral check if the literal corresponds to the partial assignment in the formula representation
         * @throw IthElementOfAssignmentDoesNotCorrespondToIthElementOfPartialAssignmentException (debug) (checkLiteral) if the literal does not correspond to the partial assignment
         */
        void assignLiteral(const LiteralType& lit, bool checkLiteral = true);
        void assignLiteralVector(const LiteralVectorType& literalVector, bool checkLiterals = true);

        /**
         * Unassign the literal
         * Assert: the literal MUST be assigned
         * @param lit a literal
         */
        void unassignLiteral(const LiteralType& lit);
        void unassignLiteralVector(const LiteralVectorType& literalVector, bool reverse = true);

        /**
         * Check if the current formula is satisfiable
         * Note: called only once at the beginning of the compilation
         * @return true if the initial formula is satisfiable. Otherwise, false is returned.
         */
        bool isSatisfiable();

        /**
         * Check if the current formula is satisfiable
         * Assert: restrictedVariableSet MUST NOT be empty
         * @param restrictedVariableSet a restriction
         * @return true if the current formula is satisfiable. Otherwise, false is returned.
         */
        bool isSatisfiable(const VariableSetType& restrictedVariableSet);

        /**
         * Do unit propagation (that is, boolean constraint propagation)
         * Note: the implied literals are assigned in the SAT solver
         * Local auxiliary data structures:
         *      l_firstCall_unitPropagation_
         *      l_impliedLiteralReusableVector_unitPropagation_
         * @param restrictedVariableSet a restriction
         * @param includeAssumptions should the assumptions be included in the result
         * @return true if NO contradiction was derived. Otherwise, false is returned.
         * @throw SatSolverDoesNotSupportUnitPropagationException if the SAT solver does not support unit propagation
         */
        bool unitPropagation(const VariableSetType& restrictedVariableSet, bool includeAssumptions = false);

        /**
         * Note: unitPropagation MUST be called beforehand
         * Note: if a contradiction was derived during the previous call of unitPropagation, the returned (reusable) vector is empty
         * @param sort should the implied literals be sorted
         * @return a (reusable) vector of implied literals filled by the previous call of unitPropagation
         */
        LiteralVectorType getImpliedLiteralVectorFromPreviousCallOfUnitPropagation(bool sort = false) const;
        const LiteralReusableVectorType& getImpliedLiteralReusableVectorFromPreviousCallOfUnitPropagation() const;

        /**
         * @param variable a variable
         * @return the VSIDS score of the variable
         * @throw SatSolverDoesNotSupportVsidsException if the SAT solver does not support VSIDS
         */
        virtual VsidsScoreType getVsidsScore(VarT variable) const = 0;

        /**
         * Create an equivalence preprocessing structure
         * Assert: the current formula MUST be satisfiable
         * Note: unit propagation is NOT done beforehand
         * Note: the implicit implied literals are assigned in the SAT solver
         * Local auxiliary data structures:
         *      l_firstCall_createEquivalencePreprocessingStruct_
         *      l_ignoredVariableVectorSet_createEquivalencePreprocessingStruct_
         *      l_positiveLiteralTVectorSet_createEquivalencePreprocessingStruct_
         *      l_variableOrderReusableVector_createEquivalencePreprocessingStruct_
         *      l_positiveUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_
         *      l_negativeUnitPropagationLiteralReusableVector_createEquivalencePreprocessingStruct_
         * @param selectedVariableSet a set of variables for which BCP will be computed
         * @param ignoreMultiOccurrentIgnoredVariables should multi-occurrent ignored variables be ignored
         * @param implicitBcpVariableOrderType what order will be used for the variables
         * @return an equivalence preprocessing structure
         * @throw SatSolverDoesNotSupportUnitPropagationException if the SAT solver does not support unit propagation
         */
        EquivalencePreprocessingStruct createEquivalencePreprocessingStruct(const VariableSetType& selectedVariableSet,
                                                                            bool ignoreMultiOccurrentIgnoredVariables,
                                                                            ImplicitBcpVariableOrderTypeEnum implicitBcpVariableOrderType);

        /**
         * @return a vector of initially implied literals
         */
        const LiteralVectorType& getInitiallyImpliedLiterals() const noexcept;

    #ifndef NDEBUG
    private:
        bool d_initialSimplification_ = false;
        VarT d_numberOfAssignedVariables_ = 0;

    public:
        void printSatSolverDebug(std::ostream& out, bool printCoreSatSolver = true, bool printCurrentFormula = false, bool printLearntClauses = false) const;

    protected:
        virtual void processPrintSatSolverDebug(std::ostream& out, bool printCoreSatSolver, bool printLearntClauses) const = 0;
    #endif
    };
}   // namespace Hydra::SatSolver

#include "./SatSolverAbstract.ipp"
