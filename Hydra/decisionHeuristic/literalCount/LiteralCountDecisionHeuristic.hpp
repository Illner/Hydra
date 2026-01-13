#pragma once

#include <algorithm>
#include <cassert>
#include <ostream>

#include "Hydra/decisionHeuristic/DecisionHeuristicAbstract.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/decisionHeuristic/enums/DecisionHeuristicTypeEnum.hpp"

#include "Hydra/decisionHeuristic/literalCount/LiteralCountDecisionHeuristic.tpp"

namespace Hydra::DecisionHeuristic::LiteralCount {

    /**
     * Literal count decision heuristic representation (final class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class LiteralCountDecisionHeuristic final : public DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using LiteralType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using VariableSetType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using SatSolverAbstractPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::SatSolverAbstractPtrType;
        using DecisionHeuristicStatisticsPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::DecisionHeuristicStatisticsPtrType;
        using FormulaRepresentationAbstractPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    public:
        LiteralCountDecisionHeuristic(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, SatSolverAbstractPtrType satSolverAbstractPtr,
                                      IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                      const LiteralCountDecisionHeuristicConfiguration& configuration = LiteralCountDecisionHeuristicConfiguration(),
                                      DecisionHeuristicStatisticsPtrType decisionHeuristicStatisticsPtr = nullptr)
            : DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, satSolverAbstractPtr, ignorePureLiteralType,
                                                                   configuration.decisionHeuristicType, decisionHeuristicStatisticsPtr),
              configuration_(configuration) {
            assert(Other::containInSet(literalCountDecisionHeuristicTypeSet, configuration_.decisionHeuristicType));   // valid decision heuristic type
        }

    private:
        LiteralCountDecisionHeuristicConfiguration configuration_;

    private:
        VarT processGetDecisionVariable(const VariableSetType& selectedVariableSet) const override;

    #ifndef NDEBUG
    private:
        void processPrintDecisionHeuristicDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::DecisionHeuristic::LiteralCount

#include "./LiteralCountDecisionHeuristic.ipp"
