#pragma once

#include <string>

namespace Hydra::SatSolver::Cadical {

    /**
     * Shrinking of the learned clauses, that is, the literals of each decision level are replaced by a single literal if possible
     * CaDiCaL option: shrink
     */
    enum class ShrinkTypeEnum {
        NONE = 0,                                                     // no shrinking (only minimization, if enabled)
        BINARY_REASON_CLAUSES = 1,                                    // shrinking using only binary reason clauses
        ALL_REASON_CLAUSES = 2,                                       // shrinking using all reason clauses
        ALL_REASON_CLAUSES_AND_MINIMIZING_LOWER_DECISION_LEVELS = 3   // shrinking using all reason clauses, and minimizing literals of lower decision levels instead of giving up
    };

    inline std::string shrinkTypeEnumToString(ShrinkTypeEnum shrinkType) noexcept {
        switch (shrinkType) {
            case ShrinkTypeEnum::NONE:
                return "no shrinking (only minimization, if enabled)";
            case ShrinkTypeEnum::BINARY_REASON_CLAUSES:
                return "shrinking using only binary reason clauses";
            case ShrinkTypeEnum::ALL_REASON_CLAUSES:
                return "shrinking using all reason clauses";
            case ShrinkTypeEnum::ALL_REASON_CLAUSES_AND_MINIMIZING_LOWER_DECISION_LEVELS:
                return "shrinking using all reason clauses, and minimizing literals of lower decision levels instead of giving up";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::SatSolver::Cadical
