#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

#include "Hydra/hypergraphPartitioning/HypergraphPartitioningAbstract.hpp"
#include "Hydra/hypergraphPartitioning/patoh/Patoh.h"
#include "Hydra/other/operatingSystem/OperatingSystem.hpp"

#include "Hydra/hypergraphPartitioning/exceptions/HypergraphPartitioningException.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/hypergraphPartitioning/enums/HypergraphPartitioningSoftwareEnum.hpp"

#include "Hydra/hypergraphPartitioning/patoh/PatohHypergraphPartitioning.tpp"

// Forward declaration
namespace Hydra::HypergraphPartitioning::Cara {
    template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
    class CaraHypergraphPartitioning;
}

namespace Hydra::HypergraphPartitioning::Patoh {

    /**
     * PaToH (final class)
     * Supported operating systems: Linux, macOS
     * Exceptions:
     *      HypergraphPartitioningSoftwareDoesNotSupportThisOperatingSystemException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class PatohHypergraphPartitioning final : public HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using VariableSetType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using VariableVectorType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
        using PartitionNumberType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::PartitionNumberType;
        using VertexWeightVectorType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightVectorType;
        using PartitionNumberVectorMapType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::PartitionNumberVectorMapType;
        using FormulaRepresentationAbstractPtrType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;
        using HypergraphPartitioningStatisticsPtrType = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::HypergraphPartitioningStatisticsPtrType;

    private:
        using OccurrenceListStruct = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::OccurrenceListStruct;
        using ModulePointersStruct = typename HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>::ModulePointersStruct;

    private:
        using PinVectorType = std::vector<int>;
        using XpinVectorType = std::vector<int>;
        using PartweightVectorType = std::vector<int>;

    public:
        PatohHypergraphPartitioning(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                    bool allowEmptyHypergraphCut, bool allowSingletonHyperedge,
                                    IgnorePureLiteralTypeEnum ignorePureLiteralType, VertexWeightTypeEnum vertexWeightType,
                                    const PatohHypergraphPartitioningConfiguration& configuration = PatohHypergraphPartitioningConfiguration(),
                                    HypergraphPartitioningStatisticsPtrType hypergraphPartitioningStatisticsPtr = nullptr,
                                    ModulePointersStruct modulePointersStruct = ModulePointersStruct())
            : HypergraphPartitioningAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr,
                                                                        allowEmptyHypergraphCut, allowSingletonHyperedge,
                                                                        HypergraphPartitioningSoftwareEnum::PATOH,
                                                                        ignorePureLiteralType, vertexWeightType,
                                                                        hypergraphPartitioningStatisticsPtr, modulePointersStruct),
              pins_(), xpins_(), partweights_(static_cast<PartweightVectorType::size_type>(configuration.kPatohLibrary), 0), configuration_(configuration) {
            // This operating system is not supported
            if (!Other::OperatingSystem::isLinux() && !Other::OperatingSystem::isMacOs())
                throw Exception::HypergraphPartitioning::HypergraphPartitioningSoftwareDoesNotSupportThisOperatingSystemException(HypergraphPartitioningSoftwareEnum::PATOH);

            pins_.reserve(this->formulaRepresentationAbstractPtr_->getOriginalFormulaSize());
            xpins_.reserve(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing());
        }

    private:
        PinVectorType pins_;
        XpinVectorType xpins_;
        PartweightVectorType partweights_;

        PatohHypergraphPartitioningConfiguration configuration_;

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
}   // namespace Hydra::HypergraphPartitioning::Patoh

#include "./PatohHypergraphPartitioning.ipp"
