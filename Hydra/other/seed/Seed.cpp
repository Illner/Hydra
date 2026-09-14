#include "./Seed.hpp"

#include <cassert>
#include <random>
#include <string>

namespace Hydra::Other::Seed {

    SeedType generateSeed() {
        #ifdef __CYGWIN__
        std::random_device rd { "/dev/urandom" };
        #else
        std::random_device rd;
        #endif

        std::uniform_int_distribution<SeedType> distribution(MIN_SEED, MAX_SEED);
        SeedType randomSeed = distribution(rd);

        assert(isSeedValid(randomSeed));

        return randomSeed;
    }

    bool isSeedValid(SeedType seed) noexcept {
        // Minimum check
        if (seed < MIN_SEED)
            return false;

        // Maximum check
        if (seed > MAX_SEED)
            return false;

        return true;
    }
}   // namespace Hydra::Other::Seed
