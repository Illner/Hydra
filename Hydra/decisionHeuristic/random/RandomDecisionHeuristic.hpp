#pragma once

#include <cassert>
#include <iostream>
#include <iterator>
#include <random>

#include "Hydra/decisionHeuristic/DecisionHeuristicAbstract.hpp"

#include "Hydra/decisionHeuristic/enums/DecisionHeuristicTypeEnum.hpp"

#include "Hydra/decisionHeuristic/random/RandomDecisionHeuristic.tpp"

namespace Hydra::DecisionHeuristic::Random {

    /**
     * Random decision heuristic representation (final class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class RandomDecisionHeuristic final : public DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using VariableSetType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using SatSolverAbstractPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::SatSolverAbstractPtrType;
        using DecisionHeuristicStatisticsPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::DecisionHeuristicStatisticsPtrType;
        using FormulaRepresentationAbstractPtrType = typename DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    public:
        RandomDecisionHeuristic(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, SatSolverAbstractPtrType satSolverAbstractPtr,
                                IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                const RandomDecisionHeuristicConfiguration& configuration = RandomDecisionHeuristicConfiguration(),
                                DecisionHeuristicStatisticsPtrType decisionHeuristicStatisticsPtr = nullptr)
            : DecisionHeuristicAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, satSolverAbstractPtr, ignorePureLiteralType,
                                                                   DecisionHeuristicTypeEnum::RANDOM, decisionHeuristicStatisticsPtr),
              configuration_(configuration) {
            #ifdef __CYGWIN__
            std::random_device rd { "/dev/urandom" };
            #else
            std::random_device rd;
            #endif

            r_generator_processGetDecisionVariable_.seed(rd());
        }

    private:
        RandomDecisionHeuristicConfiguration configuration_;

        // Random auxiliary data structures for processGetDecisionVariable
        mutable std::mt19937 r_generator_processGetDecisionVariable_;

    private:
        /**
         * Random auxiliary data structures:
         *      r_generator_processGetDecisionVariable_
         */
        VarT processGetDecisionVariable(const VariableSetType& selectedVariableSet) const override;

    #ifndef NDEBUG
    private:
        void processPrintDecisionHeuristicDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::DecisionHeuristic::Random

#include "./RandomDecisionHeuristic.ipp"
