#pragma once

#include <ostream>
#include <string_view>

namespace Hydra::Other::Version {

    /**
     * @return the Hydra version
     */
    std::string_view getHydraVersion() noexcept;

    /**
     * @return the Hydra version - major
     */
    std::string_view getHydraVersionMajor() noexcept;

    /**
     * @return the Hydra version - minor
     */
    std::string_view getHydraVersionMinor() noexcept;

    /**
     * @return the Hydra version - patch
     */
    std::string_view getHydraVersionPatch() noexcept;

    /**
     * Print the Hydra version
     */
    void printHydraVersion(std::ostream& out);
}   // namespace Hydra::Other::Version
