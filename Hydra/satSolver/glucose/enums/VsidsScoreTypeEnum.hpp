#pragma once

#include <string>

namespace Hydra::SatSolver::Glucose {

    enum class VsidsScoreTypeEnum {
        D4_V2,
        GLUCOSE
    };

    inline std::string vsidsScoreTypeEnumToString(VsidsScoreTypeEnum vsidsScoreType) noexcept {
        switch (vsidsScoreType) {
            case VsidsScoreTypeEnum::D4_V2:
                return "D4v2";
            case VsidsScoreTypeEnum::GLUCOSE:
                return "Glucose";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::SatSolver::Glucose
