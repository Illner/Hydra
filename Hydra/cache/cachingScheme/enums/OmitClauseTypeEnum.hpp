#pragma once

#include <string>

namespace Hydra::Cache::CachingScheme {

    enum class OmitClauseTypeEnum {
        NONE,
        ORIGINAL_BINARY,
        UNTOUCHED
    };

    inline std::string omitClauseTypeEnumToString(OmitClauseTypeEnum omitClauseType) noexcept {
        switch (omitClauseType) {
            case OmitClauseTypeEnum::NONE:
                return "none";
            case OmitClauseTypeEnum::ORIGINAL_BINARY:
                return "original binary clauses";
            case OmitClauseTypeEnum::UNTOUCHED:
                return "untouched clauses";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Cache::CachingScheme
