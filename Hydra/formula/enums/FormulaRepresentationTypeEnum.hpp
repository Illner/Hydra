#pragma once

#include <string>

namespace Hydra::Formula::Representation {

    enum class FormulaRepresentationTypeEnum {
        STANDARD,
        CONTIGUOUS
    };

    inline std::string formulaRepresentationEnumToString(FormulaRepresentationTypeEnum formulaRepresentationType) noexcept {
        switch (formulaRepresentationType) {
            case FormulaRepresentationTypeEnum::STANDARD:
                return "standard";
            case FormulaRepresentationTypeEnum::CONTIGUOUS:
                return "contiguous";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Formula::Representation
