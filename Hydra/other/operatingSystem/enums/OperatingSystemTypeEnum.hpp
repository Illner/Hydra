#pragma once

#include <string>

#include "Hydra/other/hashMap/HashMap.hpp"

namespace Hydra::Other::OperatingSystem {

    enum class OperatingSystemTypeEnum {
        LINUX,

        MAC_OS_APPLE_SILICON,
        MAC_OS_INTEL,

        WINDOWS_32,
        WINDOWS_64,

        UNDEFINED
    };

    using OperatingSystemTypeEnumSetType = Other::HashMap::SetType<OperatingSystemTypeEnum>;

    const inline OperatingSystemTypeEnumSetType windowsOperatingSystemSet { OperatingSystemTypeEnum::WINDOWS_32,
                                                                            OperatingSystemTypeEnum::WINDOWS_64 };
    const inline OperatingSystemTypeEnumSetType macOsOperatingSystemSet { OperatingSystemTypeEnum::MAC_OS_INTEL,
                                                                          OperatingSystemTypeEnum::MAC_OS_APPLE_SILICON };
    const inline OperatingSystemTypeEnumSetType linuxOperatingSystemSet { OperatingSystemTypeEnum::LINUX };

    inline std::string operatingSystemTypeEnumToString(OperatingSystemTypeEnum operatingSystemType, bool detailed = false) noexcept {
        // Detailed
        if (detailed) {
            switch (operatingSystemType) {
                case OperatingSystemTypeEnum::LINUX:
                    return "Linux";
                case OperatingSystemTypeEnum::MAC_OS_APPLE_SILICON:
                    return "macOS (Apple Silicon)";
                case OperatingSystemTypeEnum::MAC_OS_INTEL:
                    return "macOS (Intel)";
                case OperatingSystemTypeEnum::WINDOWS_32:
                    return "Windows (32 bit)";
                case OperatingSystemTypeEnum::WINDOWS_64:
                    return "Windows (64 bit)";
                case OperatingSystemTypeEnum::UNDEFINED:
                    return "undefined";
                default:
                    return "name not set";
            }
        }

        // Not detailed
        switch (operatingSystemType) {
            case OperatingSystemTypeEnum::LINUX:
                return "Linux";
            case OperatingSystemTypeEnum::MAC_OS_APPLE_SILICON:
            case OperatingSystemTypeEnum::MAC_OS_INTEL:
                return "macOS";
            case OperatingSystemTypeEnum::WINDOWS_32:
            case OperatingSystemTypeEnum::WINDOWS_64:
                return "Windows";
            case OperatingSystemTypeEnum::UNDEFINED:
                return "undefined";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Other::OperatingSystem
