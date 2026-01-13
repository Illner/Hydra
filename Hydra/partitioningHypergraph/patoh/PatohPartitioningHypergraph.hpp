#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

#include "Hydra/other/operatingSystem/OperatingSystem.hpp"
#include "Hydra/partitioningHypergraph/PartitioningHypergraphAbstract.hpp"
#include "Hydra/partitioningHypergraph/patoh/Patoh.h"

#include "Hydra/partitioningHypergraph/exceptions/PartitioningHypergraphException.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/partitioningHypergraph/enums/PartitioningHypergraphSoftwareEnum.hpp"

#include "Hydra/partitioningHypergraph/patoh/PatohPartitioningHypergraph.tpp"

// Forward declaration
namespace Hydra::PartitioningHypergraph::Cara {
    template <typename VarT2, typename LiteralT2, typename ClauseIdT2, typename CacheValueT2>
    class CaraPartitioningHypergraph;
}

namespace Hydra::PartitioningHypergraph::Patoh {

    /**
     * PaToH (final class)
     * Supported operating systems: Linux, macOS
     * Exceptions:
     *      PartitioningHypergraphSoftwareDoesNotSupportThisOperatingSystemException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class PatohPartitioningHypergraph final : public PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using VariableSetType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using VariableVectorType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
        using PartitionNumberType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::PartitionNumberType;
        using VertexWeightVectorType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightVectorType;
        using PartitionNumberVectorMapType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::PartitionNumberVectorMapType;
        using FormulaRepresentationAbstractPtrType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;
        using PartitioningHypergraphStatisticsPtrType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::PartitioningHypergraphStatisticsPtrType;

    private:
        using OccurrenceListStruct = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::OccurrenceListStruct;
        using ModulePointersStruct = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::ModulePointersStruct;

    private:
        using PinVectorType = std::vector<int>;
        using XpinVectorType = std::vector<int>;
        using PartweightVectorType = std::vector<int>;

    public:
        PatohPartitioningHypergraph(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                    bool allowEmptyHypergraphCut, bool allowSingletonHyperedge,
                                    IgnorePureLiteralTypeEnum ignorePureLiteralType, VertexWeightTypeEnum vertexWeightType,
                                    const PatohPartitioningHypergraphConfiguration& configuration = PatohPartitioningHypergraphConfiguration(),
                                    PartitioningHypergraphStatisticsPtrType partitioningHypergraphStatisticsPtr = nullptr,
                                    ModulePointersStruct modulePointersStruct = ModulePointersStruct())
            : PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr,
                                                                        allowEmptyHypergraphCut, allowSingletonHyperedge,
                                                                        PartitioningHypergraphSoftwareEnum::PATOH,
                                                                        ignorePureLiteralType, vertexWeightType,
                                                                        partitioningHypergraphStatisticsPtr, modulePointersStruct),
              pins_(), xpins_(), partweights_(static_cast<PartweightVectorType::size_type>(configuration.kPatohLibrary), 0), configuration_(configuration) {
            // This operating system is not supported
            if (!Other::OperatingSystem::isLinux() && !Other::OperatingSystem::isMacOs())
                throw Exception::PartitioningHypergraph::PartitioningHypergraphSoftwareDoesNotSupportThisOperatingSystemException(PartitioningHypergraphSoftwareEnum::PATOH);

            pins_.reserve(this->formulaRepresentationAbstractPtr_->getOriginalFormulaSize());
            xpins_.reserve(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing());
        }

    private:
        PinVectorType pins_;
        XpinVectorType xpins_;
        PartweightVectorType partweights_;

        PatohPartitioningHypergraphConfiguration configuration_;

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
}   // namespace Hydra::PartitioningHypergraph::Patoh

#include "./PatohPartitioningHypergraph.ipp"
