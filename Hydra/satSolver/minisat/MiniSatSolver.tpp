#pragma once

#include "Hydra/other/Other.hpp"

#include "Hydra/satSolver/minisat/enums/VsidsScoreTypeEnum.hpp"

namespace Hydra::SatSolver::MiniSat {

    using LargeNumberType = Hydra::Other::LargeNumberType;

    /**
     * MiniSat solver - configuration
     */
    struct MiniSatSolverConfiguration {
    public:
        /**
         * VSIDS score type
         */
        VsidsScoreTypeEnum vsidsScoreType = VsidsScoreTypeEnum::D4;

        /**
         * Frequency decay for D4v2 VSIDS score
         */
        LargeNumberType frequencyDecayD4v2VsidsScore = 2048;
    };
}   // namespace Hydra::SatSolver::MiniSat
