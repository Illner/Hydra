#pragma once

#include <string>

#include "Hydra/other/hashMap/HashMap.hpp"

namespace Hydra::DecisionHeuristic {

    enum class DecisionHeuristicTypeEnum {
        RANDOM,
        JEROSLOW_WANG_ONE_SIDED,
        JEROSLOW_WANG_TWO_SIDED,
        DLCS,
        DLIS,
        DLCS_DLIS,
        VSIDS,
        VSADS,
        EUPC,
        AUPC
    };

    using DecisionHeuristicTypeEnumSetType = Other::HashMap::SetType<DecisionHeuristicTypeEnum>;

    const inline DecisionHeuristicTypeEnumSetType literalCountDecisionHeuristicTypeSet { DecisionHeuristicTypeEnum::DLCS,
                                                                                         DecisionHeuristicTypeEnum::DLIS,
                                                                                         DecisionHeuristicTypeEnum::DLCS_DLIS };

    const inline DecisionHeuristicTypeEnumSetType jeroslowWangDecisionHeuristicTypeSet { DecisionHeuristicTypeEnum::JEROSLOW_WANG_ONE_SIDED,
                                                                                         DecisionHeuristicTypeEnum::JEROSLOW_WANG_TWO_SIDED };

    const inline DecisionHeuristicTypeEnumSetType upcDecisionHeuristicTypeSet { DecisionHeuristicTypeEnum::EUPC,
                                                                                DecisionHeuristicTypeEnum::AUPC };

    inline std::string decisionHeuristicTypeEnumToString(DecisionHeuristicTypeEnum decisionHeuristicType) noexcept {
        switch (decisionHeuristicType) {
            case DecisionHeuristicTypeEnum::RANDOM:
                return "random";
            case DecisionHeuristicTypeEnum::JEROSLOW_WANG_ONE_SIDED:
                return "Jeroslow-Wang (one-sided)";
            case DecisionHeuristicTypeEnum::JEROSLOW_WANG_TWO_SIDED:
                return "Jeroslow-Wang (two-sided)";
            case DecisionHeuristicTypeEnum::DLCS:
                return "dynamic largest combined sum (DLCS)";
            case DecisionHeuristicTypeEnum::DLIS:
                return "dynamic largest individual sum (DLIS)";
            case DecisionHeuristicTypeEnum::DLCS_DLIS:
                return "DLCS + DLIS as a tie-breaker (DLCS-DLIS)";
            case DecisionHeuristicTypeEnum::VSIDS:
                return "variable state independent decaying sum (VSIDS)";
            case DecisionHeuristicTypeEnum::VSADS:
                return "variable state aware decaying sum (VSADS)";
            case DecisionHeuristicTypeEnum::EUPC:
                return "exact unit propagation count (EUPC)";
            case DecisionHeuristicTypeEnum::AUPC:
                return "approximate unit propagation count (AUPC)";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::DecisionHeuristic
