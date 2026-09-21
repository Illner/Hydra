#pragma once

#include "Hydra/other/seed/Seed.hpp"

namespace HydraTest {

    using SeedType = Hydra::Other::Seed::SeedType;

    /**
     * Create a log file.
     * If the seed is provided, it will be saved in the log file.
     * Note: print the log file name
     * @param seed [optional] a seed
     * @throw CannotCreateFileException if the log file cannot be created
     */
    void createLogFile(SeedType seed = Hydra::Other::Seed::NOT_DEFINED_SEED);

    int runSession(int argc, char* argv[]);

    int runSession(int argc, char* argv[], SeedType& seed);
}   // namespace HydraTest
