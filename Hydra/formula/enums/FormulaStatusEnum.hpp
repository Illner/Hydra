#pragma once

#include <string>

namespace Hydra::Formula {

    enum class FormulaStatusEnum {
        SATISFIED,
        UNSATISFIED,
        UNRESOLVED
    };

    inline std::string formulaStatusEnumToString(FormulaStatusEnum formulaStatus) noexcept {
        switch (formulaStatus) {
            case FormulaStatusEnum::SATISFIED:
                return "satisfied";
            case FormulaStatusEnum::UNSATISFIED:
                return "unsatisfied";
            case FormulaStatusEnum::UNRESOLVED:
                return "unresolved";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Formula
