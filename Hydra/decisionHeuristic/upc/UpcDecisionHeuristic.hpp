#pragma once

#include <algorithm>
#include <cassert>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "Hydra/decisionHeuristic/DecisionHeuristicAbstract.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"

#include "Hydra/decisionHeuristic/enums/DecisionHeuristicTypeEnum.hpp"

#include "Hydra/decisionHeuristic/upc/UpcDecisionHeuristic.tpp"

#ifndef NDEBUG
    #include "Hydra/other/Other.hpp"
#endif

namespace Hydra::DecisionHeuristic::Upc {

    /**
     * Unit Propagation Count (UPC) decision heuristic representation (final class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class UpcDecisionHeuristic final : public DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using LiteralType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using VariableSetType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using SatSolverAbstractPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::SatSolverAbstractPtrType;
        using DecisionHeuristicStatisticsPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::DecisionHeuristicStatisticsPtrType;
        using FormulaRepresentationAbstractPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    private:
        using UpcScoreType = long long int;
        using ApproximateScorePairType = std::pair<VarT, UpcScoreType>;
        using ApproximateScoreVectorType = std::vector<ApproximateScorePairType>;

    public:
        UpcDecisionHeuristic(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, SatSolverAbstractPtrType satSolverAbstractPtr,
                             IgnorePureLiteralTypeEnum ignorePureLiteralType,
                             const UpcDecisionHeuristicConfiguration& configuration = UpcDecisionHeuristicConfiguration(),
                             DecisionHeuristicStatisticsPtrType decisionHeuristicStatisticsPtr = nullptr) noexcept
            : DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, satSolverAbstractPtr, ignorePureLiteralType,
                                                                   configuration.exactVariant ? DecisionHeuristicTypeEnum::EUPC : DecisionHeuristicTypeEnum::AUPC,
                                                                   decisionHeuristicStatisticsPtr),
              configuration_(configuration) { }

    private:
        UpcDecisionHeuristicConfiguration configuration_;

    private:
        /**
         * @param var a variable
         * @param selectedVariableSet a selected variable set
         * @return the UPC score for the variable. Return -1 if a contradiction was derived.
         */
        UpcScoreType computeUpcScoreForVariable(VarT var, const VariableSetType& selectedVariableSet) const;

        VarT computeExactVariant(const VariableSetType& selectedVariableSet) const;

        VarT computeApproximateVariant(const VariableSetType& selectedVariableSet) const;

        VarT processGetDecisionVariable(const VariableSetType& selectedVariableSet) const override;

    #ifndef NDEBUG
    private:
        void processPrintDecisionHeuristicDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::DecisionHeuristic::Upc

#include "./UpcDecisionHeuristic.ipp"
