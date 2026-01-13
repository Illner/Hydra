#include "./OperatingSystem.hpp"

namespace Hydra::Other::OperatingSystem {

    OperatingSystemTypeEnum getOperatingSystem() noexcept {
        #if OPERATING_SYSTEM_WINDOWS
            #ifdef _WIN64
                return OperatingSystemTypeEnum::WINDOWS_64;
            #else
                return OperatingSystemTypeEnum::WINDOWS_32;
            #endif
        #elif OPERATING_SYSTEM_MACOS
            #if defined(__arm64__) || defined(__arm__)
                return OperatingSystemTypeEnum::MAC_OS_APPLE_SILICON;
            #else
                return OperatingSystemTypeEnum::MAC_OS_INTEL;
            #endif
        #elif OPERATING_SYSTEM_LINUX
            return OperatingSystemTypeEnum::LINUX;
        #else
            return OperatingSystemTypeEnum::UNDEFINED;
        #endif
    }

    bool isWindows() noexcept {
        return containInSet(windowsOperatingSystemSet, getOperatingSystem());
    }

    bool isMacOs() noexcept {
        return containInSet(macOsOperatingSystemSet, getOperatingSystem());
    }

    bool isLinux() noexcept {
        return containInSet(linuxOperatingSystemSet, getOperatingSystem());
    }
}   // namespace Hydra::Other::OperatingSystem
