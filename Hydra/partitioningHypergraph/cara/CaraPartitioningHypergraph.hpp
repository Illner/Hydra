#pragma once

#include <cassert>

#include "Hydra/cache/Cache.hpp"
#include "Hydra/partitioningHypergraph/PartitioningHypergraphAbstract.hpp"
#include "Hydra/partitioningHypergraph/kahypar/KahyparPartitioningHypergraph.hpp"
#include "Hydra/partitioningHypergraph/patoh/PatohPartitioningHypergraph.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/partitioningHypergraph/enums/PartitioningHypergraphSoftwareEnum.hpp"

#include "Hydra/partitioningHypergraph/cara/CaraPartitioningHypergraph.tpp"
#include "Hydra/partitioningHypergraph/kahypar/KahyparPartitioningHypergraph.tpp"
#include "Hydra/partitioningHypergraph/patoh/PatohPartitioningHypergraph.tpp"

namespace Hydra::PartitioningHypergraph::Cara {

    /**
     * Cara (final class)
     * Supported operating systems: Linux, macOS
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CacheValueT>
    class CaraPartitioningHypergraph final : public PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using VariableSetType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using FormulaRepresentationAbstractPtrType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;
        using PartitioningHypergraphStatisticsPtrType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::PartitioningHypergraphStatisticsPtrType;

    private:
        using CacheStatisticsStruct = typename Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheStatisticsStruct;
        using OccurrenceListStruct = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::OccurrenceListStruct;
        using ModulePointersStruct = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::ModulePointersStruct;

    private:
        using PatohPartitioningHypergraphConfigurationType = PartitioningHypergraph::Patoh::PatohPartitioningHypergraphConfiguration;
        using PatohPartitioningHypergraphType = PartitioningHypergraph::Patoh::PatohPartitioningHypergraph<VarT, LiteralT, ClauseIdT>;
        using KahyparPartitioningHypergraphConfigurationType = PartitioningHypergraph::Kahypar::KahyparPartitioningHypergraphConfiguration;
        using KahyparPartitioningHypergraphType = PartitioningHypergraph::Kahypar::KahyparPartitioningHypergraph<VarT, LiteralT, ClauseIdT>;

    public:
        using CachePtrType = const Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>*;

    public:
        CaraPartitioningHypergraph(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CachePtrType cachePtr,
                                   bool allowEmptyHypergraphCut, bool allowSingletonHyperedge,
                                   IgnorePureLiteralTypeEnum ignorePureLiteralType, VertexWeightTypeEnum vertexWeightType,
                                   const CaraPartitioningHypergraphConfiguration& configuration = CaraPartitioningHypergraphConfiguration(),
                                   PartitioningHypergraphStatisticsPtrType partitioningHypergraphStatisticsPtr = nullptr)
            : PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr,
                                                                        allowEmptyHypergraphCut, allowSingletonHyperedge,
                                                                        PartitioningHypergraphSoftwareEnum::WRAPPER,
                                                                        ignorePureLiteralType, vertexWeightType,
                                                                        partitioningHypergraphStatisticsPtr, ModulePointersStruct()),
              cachePtr_(cachePtr),
              patohPartitioningHypergraph_(formulaRepresentationAbstractPtr, allowEmptyHypergraphCut, allowSingletonHyperedge, ignorePureLiteralType, vertexWeightType,
                                           PatohPartitioningHypergraphConfigurationType(), partitioningHypergraphStatisticsPtr,
                                           { &(this->vertexWeightVector_), &(this->clauseVertexWeightVector_), &(this->partitionNumberVectorMap_) }),
              kahyparPartitioningHypergraph_(formulaRepresentationAbstractPtr, allowEmptyHypergraphCut, allowSingletonHyperedge, ignorePureLiteralType, vertexWeightType,
                                             KahyparPartitioningHypergraphConfigurationType(), partitioningHypergraphStatisticsPtr,
                                             { &(this->vertexWeightVector_), &(this->clauseVertexWeightVector_), &(this->partitionNumberVectorMap_) }),
              configuration_(configuration) {
            assert(!allowSingletonHyperedge);

            PatohPartitioningHypergraphConfigurationType& patohConfiguration = patohPartitioningHypergraph_.configuration_;
            KahyparPartitioningHypergraphConfigurationType& kahyparConfiguration = kahyparPartitioningHypergraph_.configuration_;

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

        PatohPartitioningHypergraphType patohPartitioningHypergraph_;
        KahyparPartitioningHypergraphType kahyparPartitioningHypergraph_;

        CaraPartitioningHypergraphConfiguration configuration_;

    private:
        VariableSetType computeCut(const OccurrenceListStruct& occurrenceListStruct) override;

    #ifndef NDEBUG
    private:
        void processPrintPartitioningHypergraphDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::PartitioningHypergraph::Cara

#include "./CaraPartitioningHypergraph.ipp"
