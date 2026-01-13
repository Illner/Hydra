#pragma once

#include <cassert>
#include <ostream>
#include <string>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"

#include "Hydra/decisionHeuristic/exceptions/DecisionHeuristicException.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/decisionHeuristic/enums/DecisionHeuristicTypeEnum.hpp"

#include "Hydra/decisionHeuristic/DecisionHeuristicAbstract.hxx"

namespace Hydra::DecisionHeuristic {

    /**
     * Decision heuristic representation (abstract class)
     * Copy and move methods are disabled!
     * Exception:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class DecisionHeuristicAbstract {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");
        static_assert(Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isValidClauseT::value, "Invalid ClauseIdT type!");

    public:
        using LiteralType = typename Formula::Literal<VarT, LiteralT>::LiteralType;
        using VariableSetType = typename Formula::Literal<VarT, LiteralT>::VariableSetType;
        using DecisionHeuristicStatisticsPtrType = typename DecisionHeuristicStatistics::DecisionHeuristicStatisticsPtrType;

    public:
        using SatSolverAbstractPtrType = SatSolver::SatSolverAbstract<VarT, LiteralT, ClauseIdT>*;
        using FormulaRepresentationAbstractPtrType = const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;

    public:
        DecisionHeuristicAbstract(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, SatSolverAbstractPtrType satSolverAbstractPtr,
                                  IgnorePureLiteralTypeEnum ignorePureLiteralType, DecisionHeuristicTypeEnum decisionHeuristicType,
                                  DecisionHeuristicStatisticsPtrType decisionHeuristicStatisticsPtr) noexcept
            : ignorePureLiteralType_(ignorePureLiteralType), decisionHeuristicType_(decisionHeuristicType),
              l_firstCall_getDecisionVariable_(true), l_restrictedSelectedVariableSet_getDecisionVariable_(0),
              satSolverAbstractPtr_(satSolverAbstractPtr), formulaRepresentationAbstractPtr_(formulaRepresentationAbstractPtr),
              decisionHeuristicStatisticsPtr_(decisionHeuristicStatisticsPtr) { }

        DecisionHeuristicAbstract(const DecisionHeuristicAbstract&) = delete;
        DecisionHeuristicAbstract(DecisionHeuristicAbstract&&) noexcept = delete;

        DecisionHeuristicAbstract& operator=(const DecisionHeuristicAbstract&) = delete;
        DecisionHeuristicAbstract& operator=(DecisionHeuristicAbstract&&) noexcept = delete;

        virtual ~DecisionHeuristicAbstract() noexcept = default;

    private:
        IgnorePureLiteralTypeEnum ignorePureLiteralType_;
        DecisionHeuristicTypeEnum decisionHeuristicType_;

        // Local auxiliary data structures for getDecisionVariable
        mutable bool l_firstCall_getDecisionVariable_;
        mutable VariableSetType l_restrictedSelectedVariableSet_getDecisionVariable_;

    protected:
        SatSolverAbstractPtrType satSolverAbstractPtr_;
        FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr_;

        DecisionHeuristicStatisticsPtrType decisionHeuristicStatisticsPtr_;

    protected:
        virtual VarT processGetDecisionVariable(const VariableSetType& selectedVariableSet) const = 0;

    public:
        /**
         * Compute a decision variable
         * Assert: selectedVariableSet MUST NOT be empty
         * Local auxiliary data structures:
         *      l_firstCall_getDecisionVariable_
         *      l_restrictedSelectedVariableSet_getDecisionVariable_
         * @param selectedVariableSet a set of (pre)selected variables
         * @param removeIgnoredPureVariables should ignored pure variables be removed
         * @return a decision variable
         */
        VarT getDecisionVariable(const VariableSetType& selectedVariableSet, bool removeIgnoredPureVariables = false) const;

    #ifndef NDEBUG
    public:
        void printDecisionHeuristicDebug(std::ostream& out, bool printCurrentFormula = false) const;

    protected:
        virtual void processPrintDecisionHeuristicDebug(std::ostream& out) const = 0;
    #endif
    };
}   // namespace Hydra::DecisionHeuristic

#include "./DecisionHeuristicAbstract.ipp"
