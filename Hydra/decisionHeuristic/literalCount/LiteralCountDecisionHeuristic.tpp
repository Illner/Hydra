#pragma once

#include "Hydra/decisionHeuristic/enums/DecisionHeuristicTypeEnum.hpp"

namespace Hydra::DecisionHeuristic::LiteralCount {

    /**
     * Literal count decision heuristic - configuration
     */
    struct LiteralCountDecisionHeuristicConfiguration {
    public:
        /**
         * Decision heuristic type
         * Supported heuristics: DLCS, DLIS, and DLCS-DLIS
         */
        DecisionHeuristicTypeEnum decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS_DLIS;
    };
}   // namespace Hydra::DecisionHeuristic::LiteralCount
