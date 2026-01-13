#pragma once

#include <string>

#include "Hydra/other/hashMap/HashMap.hpp"

namespace Hydra {

    enum class RecomputingHypergraphCutTypeEnum {
        ALWAYS,
        IMMENSE_UNIT_PROPAGATION,
        WHEN_CURRENT_FORMULA_IS_SPLIT,
        WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY,
        IMMENSE_UNIT_PROPAGATION_OR_WHEN_CURRENT_FORMULA_IS_SPLIT
    };

    using RecomputingHypergraphCutTypeEnumSetType = Other::HashMap::SetType<RecomputingHypergraphCutTypeEnum>;

    const inline RecomputingHypergraphCutTypeEnumSetType formulaSplitRecomputingHypergraphCutTypeSet { RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_FORMULA_IS_SPLIT,
                                                                                                       RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION_OR_WHEN_CURRENT_FORMULA_IS_SPLIT };

    const inline RecomputingHypergraphCutTypeEnumSetType emptyCutRecomputingHypergraphCutTypeSet { RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION,
                                                                                                   RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_FORMULA_IS_SPLIT,
                                                                                                   RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY,
                                                                                                   RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION_OR_WHEN_CURRENT_FORMULA_IS_SPLIT };

    inline std::string recomputingHypergraphCutTypeEnumToString(RecomputingHypergraphCutTypeEnum recomputingHypergraphCutType) noexcept {
        switch (recomputingHypergraphCutType) {
            case RecomputingHypergraphCutTypeEnum::ALWAYS:
                return "hypergraph cuts are computed at each node";
            case RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION:
                return "a new hypergraph cut is computed when immense unit propagation is performed";
            case RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_FORMULA_IS_SPLIT:
                return "a new hypergraph cut is computed when the current formula is split";
            case RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY:
                return "a new hypergraph cut is computed when the current hypergraph cut is empty";
            case RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION_OR_WHEN_CURRENT_FORMULA_IS_SPLIT:
                return "a new hypergraph cut is computed when immense unit propagation is performed, or the current formula is split";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra
