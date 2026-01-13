#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <ostream>

#include "Hydra/decisionHeuristic/DecisionHeuristicAbstract.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"

#include "Hydra/decisionHeuristic/enums/DecisionHeuristicTypeEnum.hpp"

#include "Hydra/decisionHeuristic/jeroslowWang/JeroslowWangDecisionHeuristic.tpp"

#ifndef NDEBUG
    #include "Hydra/other/Other.hpp"
#endif

namespace Hydra::DecisionHeuristic::JeroslowWang {

    /**
     * Jeroslow-Wang decision heuristic representation (final class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class JeroslowWangDecisionHeuristic final : public DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using JeroslowWangScoreType = long double;

    private:
        using LiteralType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using VariableSetType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using SatSolverAbstractPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::SatSolverAbstractPtrType;
        using DecisionHeuristicStatisticsPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::DecisionHeuristicStatisticsPtrType;
        using ClauseSizeCounterType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeCounterType;
        using FormulaRepresentationAbstractPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    public:
        JeroslowWangDecisionHeuristic(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, SatSolverAbstractPtrType satSolverAbstractPtr,
                                      IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                      const JeroslowWangDecisionHeuristicConfiguration& configuration = JeroslowWangDecisionHeuristicConfiguration(),
                                      DecisionHeuristicStatisticsPtrType decisionHeuristicStatisticsPtr = nullptr) noexcept
            : DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, satSolverAbstractPtr, ignorePureLiteralType,
                                                                   configuration.twoSidedVariant ? DecisionHeuristicTypeEnum::JEROSLOW_WANG_TWO_SIDED : DecisionHeuristicTypeEnum::JEROSLOW_WANG_ONE_SIDED,
                                                                   decisionHeuristicStatisticsPtr),
              configuration_(configuration) { }

    private:
        JeroslowWangDecisionHeuristicConfiguration configuration_;

    private:
        VarT processGetDecisionVariable(const VariableSetType& selectedVariableSet) const override;

    #ifndef NDEBUG
    private:
        void processPrintDecisionHeuristicDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::DecisionHeuristic::JeroslowWang

#include "./JeroslowWangDecisionHeuristic.ipp"
