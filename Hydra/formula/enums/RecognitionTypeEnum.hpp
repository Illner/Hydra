#pragma once

#include <string>

namespace Hydra::Formula::Representation {

    enum class RecognitionTypeEnum {
        KROM_C,
        HORN_C,
        ANTI_HORN_C,
        NONE
    };

    inline std::string recognitionTypeEnumToString(RecognitionTypeEnum recognitionType) noexcept {
        switch (recognitionType) {
            case RecognitionTypeEnum::KROM_C:
                return "Krom-C";
            case RecognitionTypeEnum::HORN_C:
                return "Horn-C";
            case RecognitionTypeEnum::ANTI_HORN_C:
                return "anti-Horn-C";
            case RecognitionTypeEnum::NONE:
                return "none";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Formula::Representation
