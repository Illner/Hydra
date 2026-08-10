#pragma once

#include <string>

#include "Hydra/other/hashMap/HashMap.hpp"

namespace Hydra {

    enum class HypergraphCutRecomputationStrategyTypeEnum {
        ALWAYS,
        IMMENSE_UNIT_PROPAGATION,
        WHEN_CURRENT_FORMULA_IS_SPLIT,
        WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY,
        IMMENSE_UNIT_PROPAGATION_OR_WHEN_CURRENT_FORMULA_IS_SPLIT
    };

    using HypergraphCutRecomputationStrategyTypeEnumSetType = Other::HashMap::SetType<HypergraphCutRecomputationStrategyTypeEnum>;

    const inline HypergraphCutRecomputationStrategyTypeEnumSetType formulaSplitHypergraphCutRecomputationStrategyTypeSet { HypergraphCutRecomputationStrategyTypeEnum::WHEN_CURRENT_FORMULA_IS_SPLIT,
                                                                                                                           HypergraphCutRecomputationStrategyTypeEnum::IMMENSE_UNIT_PROPAGATION_OR_WHEN_CURRENT_FORMULA_IS_SPLIT };

    const inline HypergraphCutRecomputationStrategyTypeEnumSetType emptyCutHypergraphCutRecomputationStrategyTypeSet { HypergraphCutRecomputationStrategyTypeEnum::IMMENSE_UNIT_PROPAGATION,
                                                                                                                       HypergraphCutRecomputationStrategyTypeEnum::WHEN_CURRENT_FORMULA_IS_SPLIT,
                                                                                                                       HypergraphCutRecomputationStrategyTypeEnum::WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY,
                                                                                                                       HypergraphCutRecomputationStrategyTypeEnum::IMMENSE_UNIT_PROPAGATION_OR_WHEN_CURRENT_FORMULA_IS_SPLIT };

    inline std::string hypergraphCutRecomputationStrategyTypeEnumToString(HypergraphCutRecomputationStrategyTypeEnum hypergraphCutRecomputationStrategyType) noexcept {
        switch (hypergraphCutRecomputationStrategyType) {
            case HypergraphCutRecomputationStrategyTypeEnum::ALWAYS:
                return "hypergraph cuts are computed at each node";
            case HypergraphCutRecomputationStrategyTypeEnum::IMMENSE_UNIT_PROPAGATION:
                return "a new hypergraph cut is computed when immense unit propagation is performed";
            case HypergraphCutRecomputationStrategyTypeEnum::WHEN_CURRENT_FORMULA_IS_SPLIT:
                return "a new hypergraph cut is computed when the current formula is split";
            case HypergraphCutRecomputationStrategyTypeEnum::WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY:
                return "a new hypergraph cut is computed when the current hypergraph cut is empty";
            case HypergraphCutRecomputationStrategyTypeEnum::IMMENSE_UNIT_PROPAGATION_OR_WHEN_CURRENT_FORMULA_IS_SPLIT:
                return "a new hypergraph cut is computed when immense unit propagation is performed, or the current formula is split";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra
