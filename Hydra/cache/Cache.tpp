#pragma once

#include <limits>

namespace Hydra::Cache {

    /**
     * Cache representation - configuration
     */
    struct CacheConfiguration {
    public:
        inline static constexpr std::size_t S_NUMBER_OF_VARIABLES_MINIMUM = 0;
        inline static constexpr std::size_t S_NUMBER_OF_VARIABLES_MAXIMUM = std::numeric_limits<std::size_t>::max();

    public:
        /**
         * Not enough variables for caching
         */
        std::size_t notEnoughVariablesForCaching = S_NUMBER_OF_VARIABLES_MINIMUM;

        /**
         * Too many variables for caching
         */
        std::size_t tooManyVariablesForCaching = S_NUMBER_OF_VARIABLES_MAXIMUM;
    };
}   // namespace Hydra::Cache
