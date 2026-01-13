#pragma once

#include <string>

namespace Hydra::Formula {

    enum class ClauseStatusWatchedLiteralEnum {
        SATISFIED,
        EMPTY,       // UNSATISFIED
        UNDEFINED,   // UNRESOLVED or SATISFIED
        UNIT_CLAUSE_1,
        UNIT_CLAUSE_2
    };

    inline std::string clauseStatusWatchedLiteralEnumToString(ClauseStatusWatchedLiteralEnum clauseStatusWatchedLiteral) noexcept {
        switch (clauseStatusWatchedLiteral) {
            case ClauseStatusWatchedLiteralEnum::SATISFIED:
                return "satisfied";
            case ClauseStatusWatchedLiteralEnum::EMPTY:
                return "empty";
            case ClauseStatusWatchedLiteralEnum::UNDEFINED:
                return "undefined";
            case ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_1:
            case ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_2:
                return "unit clause";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Formula
