#pragma once

#include <cassert>
#include <ostream>
#include <string>

#include "Hydra/decisionHeuristic/DecisionHeuristicAbstract.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/satSolver/SatSolverAbstract.hpp"

#include "Hydra/decisionHeuristic/enums/DecisionHeuristicTypeEnum.hpp"

#include "Hydra/decisionHeuristic/vsads/VsadsDecisionHeuristic.tpp"

#ifndef NDEBUG
    #include "Hydra/other/Other.hpp"
#endif

namespace Hydra::DecisionHeuristic::Vsads {

    using VsidsScoreType = Hydra::SatSolver::VsidsScoreType;

    /**
     * Variable State Aware Decaying Sum (VSADS) decision heuristic representation (final class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class VsadsDecisionHeuristic final : public DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using VsadsScoreType = long double;

    private:
        using VariableSetType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using SatSolverAbstractPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::SatSolverAbstractPtrType;
        using DecisionHeuristicStatisticsPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::DecisionHeuristicStatisticsPtrType;
        using FormulaRepresentationAbstractPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    public:
        VsadsDecisionHeuristic(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, SatSolverAbstractPtrType satSolverAbstractPtr,
                               IgnorePureLiteralTypeEnum ignorePureLiteralType,
                               const VsadsDecisionHeuristicConfiguration& configuration = VsadsDecisionHeuristicConfiguration(),
                               DecisionHeuristicStatisticsPtrType decisionHeuristicStatisticsPtr = nullptr)
            : DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, satSolverAbstractPtr, ignorePureLiteralType,
                                                                   DecisionHeuristicTypeEnum::VSADS, decisionHeuristicStatisticsPtr),
              configuration_(configuration) {
            // The constant factors are valid
            assert(configuration_.p >= 0);
            assert(configuration_.q >= 0);
        }

    private:
        VsadsDecisionHeuristicConfiguration configuration_;

    private:
        VarT processGetDecisionVariable(const VariableSetType& selectedVariableSet) const override;

    #ifndef NDEBUG
    private:
        void processPrintDecisionHeuristicDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::DecisionHeuristic::Vsads

#include "./VsadsDecisionHeuristic.ipp"
