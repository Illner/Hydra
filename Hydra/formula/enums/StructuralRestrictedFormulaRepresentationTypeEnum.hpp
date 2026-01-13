#pragma once

#include <string>

namespace Hydra::Formula::StructuralRestrictedRepresentation {

    enum class StructuralRestrictedFormulaRepresentationTypeEnum {
        Krom_C,       // Krom-C
        renH_C,       // renH-C
        Horn_C,       // Horn-C
        anti_Horn_C   // anti-Horn-C
    };

    inline std::string structuralRestrictedFormulaRepresentationTypeEnumToString(StructuralRestrictedFormulaRepresentationTypeEnum structuralRestrictedFormulaRepresentationType) noexcept {
        switch (structuralRestrictedFormulaRepresentationType) {
            case StructuralRestrictedFormulaRepresentationTypeEnum::Krom_C:
                return "Krom-C";
            case StructuralRestrictedFormulaRepresentationTypeEnum::renH_C:
                return "renH-C";
            case StructuralRestrictedFormulaRepresentationTypeEnum::Horn_C:
                return "Horn-C";
            case StructuralRestrictedFormulaRepresentationTypeEnum::anti_Horn_C:
                return "anti-Horn-C";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Formula::StructuralRestrictedRepresentation
