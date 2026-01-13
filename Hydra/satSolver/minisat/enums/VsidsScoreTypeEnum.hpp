#pragma once

#include <string>

namespace Hydra::SatSolver::MiniSat {

    enum class VsidsScoreTypeEnum {
        D4,
        D4_V2,
        MINISAT
    };

    inline std::string vsidsScoreTypeEnumToString(VsidsScoreTypeEnum vsidsScoreType) noexcept {
        switch (vsidsScoreType) {
            case VsidsScoreTypeEnum::D4:
                return "D4";
            case VsidsScoreTypeEnum::D4_V2:
                return "D4v2";
            case VsidsScoreTypeEnum::MINISAT:
                return "MiniSat";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::SatSolver::MiniSat
