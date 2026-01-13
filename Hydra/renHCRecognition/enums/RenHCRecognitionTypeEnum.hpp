#pragma once

#include <string>

namespace Hydra::RenHCRecognition {

    enum class RenHCRecognitionTypeEnum {
        ASPVALL
    };

    inline std::string renHCRecognitionTypeEnumToString(RenHCRecognitionTypeEnum renHCRecognitionType) noexcept {
        switch (renHCRecognitionType) {
            case RenHCRecognitionTypeEnum::ASPVALL:
                return "Aspvall";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::RenHCRecognition
