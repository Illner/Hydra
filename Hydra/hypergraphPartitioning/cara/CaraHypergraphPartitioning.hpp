#pragma once

#include <cassert>

#include "Hydra/cache/Cache.hpp"
#include "Hydra/hypergraphPartitioning/HypergraphPartitioningAbstract.hpp"
#include "Hydra/hypergraphPartitioning/kahypar/KahyparHypergraphPartitioning.hpp"
#include "Hydra/hypergraphPartitioning/patoh/PatohHypergraphPartitioning.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/hypergraphPartitioning/enums/HypergraphPartitioningSoftwareEnum.hpp"

#include "Hydra/hypergraphPartitioning/cara/CaraHypergraphPartitioning.tpp"
#include "Hydra/hypergraphPartitioning/kahypar/KahyparHypergraphPartitioning.tpp"
#include "Hydra/hypergraphPartitioning/patoh/PatohHypergraphPartitioning.tpp"

namespace Hydra::HypergraphPartitioning::Cara {

    /**
     * Cara (final class)
     * Supported operating systems: Linux, macOS
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    class CaraHypergraphPartitioning final : public HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using VariableSetType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using FormulaRepresentationAbstractPtrType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;
        using HypergraphPartitioningStatisticsPtrType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::HypergraphPartitioningStatisticsPtrType;

    private:
        using CacheStatisticsStruct = typename Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheStatisticsStruct;
        using OccurrenceListStruct = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::OccurrenceListStruct;
        using ModulePointersStruct = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::ModulePointersStruct;

    private:
        using PatohHypergraphPartitioningConfigurationType = HypergraphPartitioning::Patoh::PatohHypergraphPartitioningConfiguration;
        using PatohHypergraphPartitioningType = HypergraphPartitioning::Patoh::PatohHypergraphPartitioning<VarT, LiteralT, ClauseIdT>;
        using KahyparHypergraphPartitioningConfigurationType = HypergraphPartitioning::Kahypar::KahyparHypergraphPartitioningConfiguration;
        using KahyparHypergraphPartitioningType = HypergraphPartitioning::Kahypar::KahyparHypergraphPartitioning<VarT, LiteralT, ClauseIdT>;

    public:
        using CachePtrType = const Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>*;

    public:
        CaraHypergraphPartitioning(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CachePtrType cachePtr,
                                   bool allowEmptyHypergraphCut, bool allowSingletonHyperedge,
                                   IgnorePureLiteralTypeEnum ignorePureLiteralType, VertexWeightTypeEnum vertexWeightType,
                                   const CaraHypergraphPartitioningConfiguration& configuration = CaraHypergraphPartitioningConfiguration(),
                                   HypergraphPartitioningStatisticsPtrType hypergraphPartitioningStatisticsPtr = nullptr)
            : HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr,
                                                                        allowEmptyHypergraphCut, allowSingletonHyperedge,
                                                                        HypergraphPartitioningSoftwareEnum::WRAPPER,
                                                                        ignorePureLiteralType, vertexWeightType,
                                                                        hypergraphPartitioningStatisticsPtr, ModulePointersStruct()),
              cachePtr_(cachePtr),
              patohHypergraphPartitioning_(formulaRepresentationAbstractPtr, allowEmptyHypergraphCut, allowSingletonHyperedge, ignorePureLiteralType, vertexWeightType,
                                           PatohHypergraphPartitioningConfigurationType(), hypergraphPartitioningStatisticsPtr,
                                           { &(this->vertexWeightVector_), &(this->clauseVertexWeightVector_), &(this->partitionNumberVectorMap_) }),
              kahyparHypergraphPartitioning_(formulaRepresentationAbstractPtr, allowEmptyHypergraphCut, allowSingletonHyperedge, ignorePureLiteralType, vertexWeightType,
                                             KahyparHypergraphPartitioningConfigurationType(), hypergraphPartitioningStatisticsPtr,
                                             { &(this->vertexWeightVector_), &(this->clauseVertexWeightVector_), &(this->partitionNumberVectorMap_) }),
              configuration_(configuration) {
            assert(!allowSingletonHyperedge);

            PatohHypergraphPartitioningConfigurationType& patohConfiguration = patohHypergraphPartitioning_.configuration_;
            KahyparHypergraphPartitioningConfigurationType& kahyparConfiguration = kahyparHypergraphPartitioning_.configuration_;

            // K
            patohConfiguration.kPatohLibrary = configuration_.k;
            kahyparConfiguration.kKahyparLibrary = configuration_.k;

            // Seed
            patohConfiguration.seedPatohLibrary = configuration_.seed;
            kahyparConfiguration.seedKahyparLibrary = configuration_.seed;

            // KaHyPar
            kahyparConfiguration.imbalanceFactorKahyparLibrary = configuration_.imbalanceFactorKahyparLibrary;

            // PaToH
            patohConfiguration.balancePatohLibrary = configuration_.balancePatohLibrary;
            patohConfiguration.finalImbalPatohLibrary = configuration_.finalImbalPatohLibrary;
            patohConfiguration.lowNumberOfVariablesSuggestByProblemTypePatohLibrary = configuration_.lowNumberOfVariablesSuggestByProblemTypePatohLibrary;
            patohConfiguration.highNumberOfVariablesSuggestByProblemTypePatohLibrary = configuration_.highNumberOfVariablesSuggestByProblemTypePatohLibrary;
        }

    private:
        CachePtrType cachePtr_;

        PatohHypergraphPartitioningType patohHypergraphPartitioning_;
        KahyparHypergraphPartitioningType kahyparHypergraphPartitioning_;

        CaraHypergraphPartitioningConfiguration configuration_;

    private:
        VariableSetType computeCut(const OccurrenceListStruct& occurrenceListStruct) override;

    #ifndef NDEBUG
    private:
        void processPrintHypergraphPartitioningDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::HypergraphPartitioning::Cara

#include "./CaraHypergraphPartitioning.ipp"
