#include "./Version.hpp"

namespace Hydra::Other::Version {

    std::string_view getHydraVersion() noexcept {
        return HYDRA_VERSION;
    }

    std::string_view getHydraVersionMajor() noexcept {
        return HYDRA_VERSION_MAJOR;
    }

    std::string_view getHydraVersionMinor() noexcept {
        return HYDRA_VERSION_MINOR;
    }

    std::string_view getHydraVersionPatch() noexcept {
        return HYDRA_VERSION_PATCH;
    }

    void printHydraVersion(std::ostream& out) {
        out << "Hydra v" << getHydraVersion();
    }
}   // namespace Hydra::Other::Version
