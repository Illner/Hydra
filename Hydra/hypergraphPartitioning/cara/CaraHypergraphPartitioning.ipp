#pragma once

#include "./CaraHypergraphPartitioning.hpp"

namespace Hydra::HypergraphPartitioning::Cara {

    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    typename CaraHypergraphPartitioning<VarT, LiteralT, ClauseIdT, CacheValueT>::VariableSetType
    CaraHypergraphPartitioning<VarT, LiteralT, ClauseIdT, CacheValueT>::computeCut(const OccurrenceListStruct& occurrenceListStruct) {
        VarT numberOfVariables = static_cast<VarT>(occurrenceListStruct.variableOrderReusableVector.size());
        const CacheStatisticsStruct& positiveHitCacheStatisticsStruct = cachePtr_->getPositiveHitCacheStatistics();

        // KaHyPar
        if (numberOfVariables >= positiveHitCacheStatisticsStruct.getMaxNumberOfVariables())
            return kahyparHypergraphPartitioning_.computeCut(occurrenceListStruct);
        // PaToH
        else {
            VarT averageNumberOfVariables = static_cast<VarT>(positiveHitCacheStatisticsStruct.averageNumberOfVariables());
            patohHypergraphPartitioning_.configuration_.numberOfVariablesThreshold = averageNumberOfVariables;

            return patohHypergraphPartitioning_.computeCut(occurrenceListStruct);
        }
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    void CaraHypergraphPartitioning<VarT, LiteralT, ClauseIdT, CacheValueT>::processPrintHypergraphPartitioningDebug(std::ostream& out) const {
        // Configuration
        out << "k: " << std::to_string(configuration_.k) << std::endl;
        out << "seed: " << std::to_string(configuration_.seed) << std::endl;
        out << "imbalanceFactorKahyparLibrary: " << std::to_string(configuration_.imbalanceFactorKahyparLibrary) << std::endl;
        out << "lowNumberOfVariablesSuggestByProblemTypePatohLibrary: " << std::to_string(configuration_.lowNumberOfVariablesSuggestByProblemTypePatohLibrary) << std::endl;
        out << "highNumberOfVariablesSuggestByProblemTypePatohLibrary: " << std::to_string(configuration_.highNumberOfVariablesSuggestByProblemTypePatohLibrary) << std::endl;
    }
    #endif
}   // namespace Hydra::HypergraphPartitioning::Cara
