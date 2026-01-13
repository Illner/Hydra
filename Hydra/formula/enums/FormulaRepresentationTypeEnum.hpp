#pragma once

#include <string>

namespace Hydra::Formula::Representation {

    enum class FormulaRepresentationTypeEnum {
        STANDARD,
        CONTAGIOUS
    };

    inline std::string formulaRepresentationEnumToString(FormulaRepresentationTypeEnum formulaRepresentationType) noexcept {
        switch (formulaRepresentationType) {
            case FormulaRepresentationTypeEnum::STANDARD:
                return "standard";
            case FormulaRepresentationTypeEnum::CONTAGIOUS:
                return "contagious";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Formula::Representation
