#pragma once

#include <string>

namespace Hydra::SatSolver::Cadical {

    /**
     * The schedule for learned-clause reduction, that is, the number of conflicts after a reduction until the next one
     * CaDiCaL option: reduceopt
     */
    enum class ReduceOptTypeEnum {
        NUMBER_OF_REDUCTIONS = 0,   // reduceInt^2 / 2 * (number of reductions so far + 1)
        SQRT_OF_CONFLICTS = 1,      // reduceInt * SQRT(number of conflicts)
        LOG_OF_CONFLICTS = 2        // reduceInt * LOG(number of conflicts)
    };

    inline std::string reduceOptTypeEnumToString(ReduceOptTypeEnum reduceOptType) noexcept {
        switch (reduceOptType) {
            case ReduceOptTypeEnum::NUMBER_OF_REDUCTIONS:
                return "reduceInt^2 / 2 * (number of reductions so far + 1)";
            case ReduceOptTypeEnum::SQRT_OF_CONFLICTS:
                return "reduceInt * SQRT(number of conflicts)";
            case ReduceOptTypeEnum::LOG_OF_CONFLICTS:
                return "reduceInt * LOG(number of conflicts)";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::SatSolver::Cadical
