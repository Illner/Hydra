#pragma once

#include <cassert>
#include <string>
#include <vector>

#include "Hydra/partitioningHypergraph/PartitioningHypergraphAbstract.hpp"
#include "Hydra/partitioningHypergraph/kahypar/Kahypar.h"
#include "Hydra/partitioningHypergraph/kahypar/KahyparContext.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/partitioningHypergraph/enums/PartitioningHypergraphSoftwareEnum.hpp"

#include "Hydra/partitioningHypergraph/kahypar/KahyparPartitioningHypergraph.tpp"

// Forward declaration
namespace Hydra::PartitioningHypergraph::Cara {
    template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
    class CaraPartitioningHypergraph;
}

namespace Hydra::PartitioningHypergraph::Kahypar {

    /**
     * KaHyPar (final class)
     * Supported operating systems: Linux, macOS, Windows
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class KahyparPartitioningHypergraph final : public PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using VariableSetType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using VertexWeightVectorType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightVectorType;
        using PartitionNumberVectorMapType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::PartitionNumberVectorMapType;
        using FormulaRepresentationAbstractPtrType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;
        using PartitioningHypergraphStatisticsPtrType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::PartitioningHypergraphStatisticsPtrType;

    private:
        using OccurrenceListStruct = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::OccurrenceListStruct;
        using ModulePointersStruct = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::ModulePointersStruct;

    private:
        using XpinVectorType = std::vector<std::size_t>;
        using KahyparContextPtrType = kahypar_context_t*;
        using PinVectorType = std::vector<kahypar_hyperedge_id_t>;

    public:
        KahyparPartitioningHypergraph(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                      bool allowEmptyHypergraphCut, bool allowSingletonHyperedge,
                                      IgnorePureLiteralTypeEnum ignorePureLiteralType, VertexWeightTypeEnum vertexWeightType,
                                      const KahyparPartitioningHypergraphConfiguration& configuration = KahyparPartitioningHypergraphConfiguration(),
                                      PartitioningHypergraphStatisticsPtrType partitioningHypergraphStatisticsPtr = nullptr,
                                      ModulePointersStruct modulePointersStruct = ModulePointersStruct())
            : PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr,
                                                                        allowEmptyHypergraphCut, allowSingletonHyperedge,
                                                                        PartitioningHypergraphSoftwareEnum::KAHYPAR,
                                                                        ignorePureLiteralType, vertexWeightType,
                                                                        partitioningHypergraphStatisticsPtr, modulePointersStruct),
              pins_(), xpins_(), kahyparContextPtr_(nullptr), configuration_(configuration) {
            assert(!allowSingletonHyperedge);

            // Initialize KaHyPar context
            kahyparContextPtr_ = kahypar_context_new();
            kahypar_configure_context_from_string(kahyparContextPtr_, d4v2_KahyparContext);
            kahypar_set_seed(kahyparContextPtr_, configuration_.seedKahyparLibrary);

            pins_.reserve(this->formulaRepresentationAbstractPtr_->getOriginalFormulaSize());
            xpins_.reserve(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing());
        }

        virtual ~KahyparPartitioningHypergraph() {
            kahypar_context_free(kahyparContextPtr_);
        }

    private:
        PinVectorType pins_;
        XpinVectorType xpins_;
        KahyparContextPtrType kahyparContextPtr_;

        KahyparPartitioningHypergraphConfiguration configuration_;

    private:
        VariableSetType computeCut(const OccurrenceListStruct& occurrenceListStruct) override;

    private:
        template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
        friend class Cara::CaraPartitioningHypergraph;

    #ifndef NDEBUG
    private:
        void processPrintPartitioningHypergraphDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::PartitioningHypergraph::Kahypar

#include "./KahyparPartitioningHypergraph.ipp"
