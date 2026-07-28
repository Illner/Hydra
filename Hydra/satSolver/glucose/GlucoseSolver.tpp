#pragma once

#include "Hydra/other/Other.hpp"

#include "Hydra/satSolver/glucose/enums/VsidsScoreTypeEnum.hpp"

namespace Hydra::SatSolver::Glucose {

    using LargeNumberType = Hydra::Other::LargeNumberType;

    /**
     * Glucose solver - configuration
     */
    struct GlucoseSolverConfiguration {
    public:
        /**
         * VSIDS score type
         */
        VsidsScoreTypeEnum vsidsScoreType = VsidsScoreTypeEnum::GLUCOSE;

        /**
         * Frequency decay for D4v2 VSIDS score
         */
        LargeNumberType frequencyDecayD4v2VsidsScore = 2048;
    };
}   // namespace Hydra::SatSolver::Glucose
