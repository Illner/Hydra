#pragma once

#include <string>

namespace Hydra::SatSolver::Cadical {

    enum class VsidsScoreTypeEnum {
        HYDRA,
        CADICAL
    };

    inline std::string vsidsScoreTypeEnumToString(VsidsScoreTypeEnum vsidsScoreType) noexcept {
        switch (vsidsScoreType) {
            case VsidsScoreTypeEnum::HYDRA:
                return "Hydra";
            case VsidsScoreTypeEnum::CADICAL:
                return "CaDiCaL";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::SatSolver::Cadical
