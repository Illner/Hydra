#pragma once

#include <limits>

namespace Hydra::Other::Seed {

    using SeedType = int;   // NOT_DEFINED_SEED and MIN_SEED, ..., MAX_SEED

    inline constexpr SeedType NOT_DEFINED_SEED = -1;
    inline constexpr SeedType MIN_SEED = 0;
    inline constexpr SeedType MAX_SEED = std::numeric_limits<SeedType>::max() - 1;   // "-1" because of PaToH

    /**
     * Generate a random seed
     * Note: the generated seed is between MIN_SEED and MAX_SEED
     * @return the generated seed
     */
    SeedType generateSeed();

    /**
     * Check if the seed is valid (that is, MIN_SEED <= seed <= MAX_SEED)
     * @param seed a seed
     * @return true if the seed is valid. Otherwise, false is returned.
     */
    bool isSeedValid(SeedType seed) noexcept;
}   // namespace Hydra::Other::Seed
