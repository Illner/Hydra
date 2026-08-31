#pragma once

#include <cassert>
#include <string>
#include <vector>

#include "Hydra/hypergraphPartitioning/HypergraphPartitioningAbstract.hpp"
#include "Hydra/hypergraphPartitioning/kahypar/Kahypar.h"
#include "Hydra/hypergraphPartitioning/kahypar/KahyparContext.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/hypergraphPartitioning/enums/HypergraphPartitioningSoftwareEnum.hpp"

#include "Hydra/hypergraphPartitioning/kahypar/KahyparHypergraphPartitioning.tpp"

// Forward declaration
namespace Hydra::HypergraphPartitioning::Cara {
    template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
    class CaraHypergraphPartitioning;
}

namespace Hydra::HypergraphPartitioning::Kahypar {

    /**
     * KaHyPar (final class)
     * Supported operating systems: Linux, macOS, Windows
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class KahyparHypergraphPartitioning final : public HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using VariableSetType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using VertexWeightVectorType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightVectorType;
        using PartitionNumberVectorMapType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::PartitionNumberVectorMapType;
        using FormulaRepresentationAbstractPtrType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;
        using HypergraphPartitioningStatisticsPtrType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::HypergraphPartitioningStatisticsPtrType;

    private:
        using OccurrenceListStruct = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::OccurrenceListStruct;
        using ModulePointersStruct = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::ModulePointersStruct;

    private:
        using XpinVectorType = std::vector<std::size_t>;
        using KahyparContextPtrType = kahypar_context_t*;
        using PinVectorType = std::vector<kahypar_hyperedge_id_t>;

    public:
        KahyparHypergraphPartitioning(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                      bool allowEmptyHypergraphCut, bool allowSingletonHyperedge,
                                      IgnorePureLiteralTypeEnum ignorePureLiteralType, VertexWeightTypeEnum vertexWeightType,
                                      const KahyparHypergraphPartitioningConfiguration& configuration = KahyparHypergraphPartitioningConfiguration(),
                                      HypergraphPartitioningStatisticsPtrType hypergraphPartitioningStatisticsPtr = nullptr,
                                      ModulePointersStruct modulePointersStruct = ModulePointersStruct())
            : HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr,
                                                                        allowEmptyHypergraphCut, allowSingletonHyperedge,
                                                                        HypergraphPartitioningSoftwareEnum::KAHYPAR,
                                                                        ignorePureLiteralType, vertexWeightType,
                                                                        hypergraphPartitioningStatisticsPtr, modulePointersStruct),
              pins_(), xpins_(), kahyparContextPtr_(nullptr), configuration_(configuration) {
            assert(!allowSingletonHyperedge);

            // Initialize KaHyPar context
            kahyparContextPtr_ = kahypar_context_new();
            kahypar_configure_context_from_string(kahyparContextPtr_, d4v2_KahyparContext);
            kahypar_set_seed(kahyparContextPtr_, configuration_.seedKahyparLibrary);

            pins_.reserve(this->formulaRepresentationAbstractPtr_->getOriginalFormulaSize());
            xpins_.reserve(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing());
        }

        ~KahyparHypergraphPartitioning() noexcept override {
            kahypar_context_free(kahyparContextPtr_);
        }

    private:
        PinVectorType pins_;
        XpinVectorType xpins_;
        KahyparContextPtrType kahyparContextPtr_;

        KahyparHypergraphPartitioningConfiguration configuration_;

    private:
        VariableSetType computeCut(const OccurrenceListStruct& occurrenceListStruct) override;

    private:
        template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
        friend class Cara::CaraHypergraphPartitioning;

    #ifndef NDEBUG
    private:
        void processPrintHypergraphPartitioningDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::HypergraphPartitioning::Kahypar

#include "./KahyparHypergraphPartitioning.ipp"
