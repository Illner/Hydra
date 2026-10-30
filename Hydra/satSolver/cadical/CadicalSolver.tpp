#pragma once

#include "Hydra/other/Other.hpp"

#include "Hydra/satSolver/cadical/enums/VsidsScoreTypeEnum.hpp"

namespace Hydra::SatSolver::Cadical {

    using LargeNumberType = Hydra::Other::LargeNumberType;

    /**
     * CaDiCaL solver - configuration
     */
    struct CadicalSolverConfiguration {
    public:
        /**
         * VSIDS score type
         */
        VsidsScoreTypeEnum vsidsScoreType = VsidsScoreTypeEnum::CADICAL;

        /**
         * Frequency decay for Hydra VSIDS score
         */
        LargeNumberType frequencyDecayHydraVsidsScore = 2048;

        /**
         * The schedule for learned-clause reduction, that is, the number of conflicts after a reduction until the next one. Set to
         * (0) for reduceInt^2 / 2 * (number of reductions so far + 1),
         * (1) for reduceInt * SQRT(number of conflicts),
         * (2) for reduceInt * LOG(number of conflicts), that is, fewer learned clauses are kept.
         * CaDiCaL option (default): reduceopt (1)
         */
        int reduceOptCadical = 2;

        /**
         * The base interval for learned-clause reduction, that is, the constant in the schedule selected by reduceOpt.
         * Values: from 2 to 1'000'000
         * Note: larger values mean fewer reductions, that is, more learned clauses are kept
         * CaDiCaL option (default): reduceint (25)
         */
        int reduceIntCadical = 25;

        /**
         * The maximum number of preprocessing rounds for simplification. Set to
         * (0) for unit propagation on the root level,
         * (1) for one round of probing, equivalent literal detection, ternary resolution, backbones, SAT sweeping, vivification of the learned clauses, transitive reduction, and subsumption,
         * (2) for two rounds (each one works on the result of the previous one),
         * ... .
         * Note: CaDiCaL stops early only after the 6th round, if a round fixes no further variables (each of the first six rounds raises its elimination bound, which counts as progress although nothing is eliminated)
         * Note: no variable is eliminated or substituted, since all variables are frozen
         * CaDiCaL function, argument (default): simplify, rounds (3)
         */
        int maximumNumberOfPreprocessingRoundsForSimplificationCadical = 3;

        /**
         * Restart schedule. Set to
         * (false) for restarts depending on the glue of the recently learned clauses (Glucose-style),
         * (true) for restarts following the reluctant doubling sequence, that is, the Luby sequence (1, 1, 2, 1, 1, 2, 4, ...) times reluctantint (that is, 1024) conflicts, where the sequence starts over when it reaches reluctantmax (that is, 1048576).
         * Note: the sequence starts over with every call of CaDiCaL, so with true, a call with fewer than 1024 conflicts never restarts
         * CaDiCaL option (default): reluctant (true)
         */
        bool reluctantCadical = true;

        /**
         * The decay factor (per mille) of the variable scores (EVSIDS) per conflict for VsidsScoreTypeEnum::CADICAL
         * Values: from 500 to 1'000 (1'000 = no decay)
         * Note: smaller values focus the decisions more on the recent conflicts
         * CaDiCaL option (default): scorefactor (950)
         */
        int scoreFactorCadical = 950;

        /**
         * Shrinking of the learned clauses, that is, the literals of each decision level are replaced by a single literal if possible. Set to
         * (0) for no shrinking (only minimization, if enabled),
         * (1) for shrinking using only binary reason clauses,
         * (2) for shrinking using all reason clauses,
         * (3) for shrinking using all reason clauses, and minimizing literals of lower decision levels instead of giving up.
         * CaDiCaL option (default): shrink (3)
         */
        int shrinkCadical = 3;

        /**
         * Phases used for the decisions. Set to
         * (false) for saved phases, that is, the last values of the variables,
         * (true) for target phases, that is, the values of the largest conflict-free assignment since the last rephasing.
         * CaDiCaL option (default): target (true)
         */
        bool targetPhasesCadical = false;
    };
}   // namespace Hydra::SatSolver::Cadical
