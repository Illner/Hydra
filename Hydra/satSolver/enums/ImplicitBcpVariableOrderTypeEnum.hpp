#pragma once

#include <string>

namespace Hydra::SatSolver {

    enum class ImplicitBcpVariableOrderTypeEnum {
        RANDOM,
        VARIABLE_INDEX,
        CLAUSE_REDUCTION_HEURISTIC_ASCENDING,
        CLAUSE_REDUCTION_HEURISTIC_DESCENDING
    };

    inline std::string implicitBcpVariableOrderTypeEnumToString(ImplicitBcpVariableOrderTypeEnum implicitBcpVariableOrderType) noexcept {
        switch (implicitBcpVariableOrderType) {
            case ImplicitBcpVariableOrderTypeEnum::RANDOM:
                return "random";
            case ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX:
                return "variable index";
            case ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_ASCENDING:
                return "clause reduction heuristic (ascending)";
            case ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_DESCENDING:
                return "clause reduction heuristic (descending)";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::SatSolver
