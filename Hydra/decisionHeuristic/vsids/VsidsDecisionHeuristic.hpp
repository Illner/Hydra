#pragma once

#include <cassert>
#include <ostream>

#include "Hydra/decisionHeuristic/DecisionHeuristicAbstract.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"

#include "Hydra/decisionHeuristic/enums/DecisionHeuristicTypeEnum.hpp"

#include "Hydra/decisionHeuristic/vsids/VsidsDecisionHeuristic.tpp"

#ifndef NDEBUG
    #include "Hydra/other/Other.hpp"
#endif

namespace Hydra::DecisionHeuristic::Vsids {

    using VsidsScoreType = Hydra::SatSolver::VsidsScoreType;

    /**
     * Variable State Independent Decaying Sum (VSIDS) decision heuristic representation (final class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class VsidsDecisionHeuristic final : public DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using VariableSetType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using SatSolverAbstractPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::SatSolverAbstractPtrType;
        using DecisionHeuristicStatisticsPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::DecisionHeuristicStatisticsPtrType;
        using FormulaRepresentationAbstractPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    public:
        VsidsDecisionHeuristic(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, SatSolverAbstractPtrType satSolverAbstractPtr,
                               IgnorePureLiteralTypeEnum ignorePureLiteralType,
                               const VsidsDecisionHeuristicConfiguration& configuration = VsidsDecisionHeuristicConfiguration(),
                               DecisionHeuristicStatisticsPtrType decisionHeuristicStatisticsPtr = nullptr) noexcept
            : DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, satSolverAbstractPtr, ignorePureLiteralType,
                                                                   DecisionHeuristicTypeEnum::VSIDS, decisionHeuristicStatisticsPtr),
              configuration_(configuration) { }

    private:
        VsidsDecisionHeuristicConfiguration configuration_;

    private:
        VarT processGetDecisionVariable(const VariableSetType& selectedVariableSet) const override;

    #ifndef NDEBUG
    private:
        void processPrintDecisionHeuristicDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::DecisionHeuristic::Vsids

#include "./VsidsDecisionHeuristic.ipp"
