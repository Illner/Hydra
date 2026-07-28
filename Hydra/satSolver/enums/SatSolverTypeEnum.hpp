#pragma once

#include <string>

namespace Hydra::SatSolver {

    enum class SatSolverTypeEnum {
        MINISAT,
        GLUCOSE,
        CADICAL
    };

    inline std::string satSolverTypeEnumToString(SatSolverTypeEnum satSolverType) noexcept {
        switch (satSolverType) {
            case SatSolverTypeEnum::MINISAT:
                return "MiniSat";
            case SatSolverTypeEnum::GLUCOSE:
                return "Glucose";
            case SatSolverTypeEnum::CADICAL:
                return "CaDiCaL";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::SatSolver
