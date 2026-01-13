#pragma once

#include "Hydra/other/Other.hpp"

#include "Hydra/other/operatingSystem/enums/OperatingSystemTypeEnum.hpp"

#define OPERATING_SYSTEM_LINUX __linux__
#define OPERATING_SYSTEM_MACOS __APPLE__ || __MACH__
#define OPERATING_SYSTEM_WINDOWS WIN32 || _WIN32 || __WIN32__ || __NT__ || __CYGWIN__

namespace Hydra::Other::OperatingSystem {

    /**
     * @return the operating system
     */
    OperatingSystemTypeEnum getOperatingSystem() noexcept;

    /**
     * @return true if the operating system is Windows (32 bit or 64 bit). Otherwise, false is returned.
     */
    bool isWindows() noexcept;

    /**
     * @return true if the operating system is macOS (Intel or Apple silicon). Otherwise, false is returned.
     */
    bool isMacOs() noexcept;

    /**
     * @return true if the operating system is Linux. Otherwise, false is returned.
     */
    bool isLinux() noexcept;
}   // namespace Hydra::Other::OperatingSystem
