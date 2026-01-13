#pragma once

#include <string>

#include "Hydra/other/hashMap/HashMap.hpp"

namespace Hydra::Formula {

    enum class ClauseStatusEnum {
        SATISFIED,
        UNRESOLVED,
        UNIT_CLAUSE,
        EMPTY   // UNSATISFIED
    };

    using ClauseStatusEnumSetType = Other::HashMap::SetType<ClauseStatusEnum>;

    const inline ClauseStatusEnumSetType unresolvedClauseStatusSet { ClauseStatusEnum::UNRESOLVED,
                                                                     ClauseStatusEnum::UNIT_CLAUSE };

    inline std::string clauseStatusEnumToString(ClauseStatusEnum clauseStatus) noexcept {
        switch (clauseStatus) {
            case ClauseStatusEnum::SATISFIED:
                return "satisfied";
            case ClauseStatusEnum::UNRESOLVED:
                return "unresolved";
            case ClauseStatusEnum::UNIT_CLAUSE:
                return "unit clause";
            case ClauseStatusEnum::EMPTY:
                return "empty";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Formula
