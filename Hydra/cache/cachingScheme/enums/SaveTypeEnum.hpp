#pragma once

#include <string>

namespace Hydra::Cache::CachingScheme {

    enum class SaveTypeEnum {
        NONE,
        CLAUSE_ID,
        LITERAL   // literal or variable
    };

    inline std::string saveTypeEnumToString(SaveTypeEnum saveType) noexcept {
        switch (saveType) {
            case SaveTypeEnum::NONE:
                return "none";
            case SaveTypeEnum::CLAUSE_ID:
                return "clause ID";
            case SaveTypeEnum::LITERAL:
                return "literal";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Cache::CachingScheme
