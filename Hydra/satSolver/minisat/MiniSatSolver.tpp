#pragma once

#include "Hydra/satSolver/minisat/enums/VsidsScoreTypeEnum.hpp"

namespace Hydra::SatSolver::MiniSat {

    /**
     * MiniSat solver - configuration
     */
    struct MiniSatSolverConfiguration {
    public:
        /**
         * VSIDS score type
         */
        VsidsScoreTypeEnum vsidsScoreType = VsidsScoreTypeEnum::D4;
    };
}   // namespace Hydra::SatSolver::MiniSat
