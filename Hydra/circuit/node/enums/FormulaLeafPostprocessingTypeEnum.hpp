#pragma once

#include <string>

namespace Hydra::Circuit::Node {

    enum class FormulaLeafPostprocessingTypeEnum {
        NONE,
        NO_SUBSUMED_CLAUSES,
        NO_DUPLICATE_CLAUSES
    };

    inline std::string formulaLeafPostprocessingTypeEnumToString(FormulaLeafPostprocessingTypeEnum formulaLeafPostprocessingType) noexcept {
        switch (formulaLeafPostprocessingType) {
            case FormulaLeafPostprocessingTypeEnum::NONE:
                return "none";
            case FormulaLeafPostprocessingTypeEnum::NO_SUBSUMED_CLAUSES:
                return "no subsumed clauses";
            case FormulaLeafPostprocessingTypeEnum::NO_DUPLICATE_CLAUSES:
                return "no duplicate clauses";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Circuit::Node
