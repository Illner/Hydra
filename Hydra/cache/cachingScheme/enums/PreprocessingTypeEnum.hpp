#pragma once

#include <string>

namespace Hydra::Cache::CachingScheme {

    enum class PreprocessingTypeEnum {
        NONE,
        NOT_DUPLICATE_CLAUSES,
        NOT_SUBSUMED_CLAUSES
    };

    inline std::string preprocessingTypeEnumToString(PreprocessingTypeEnum preprocessingType) noexcept {
        switch (preprocessingType) {
            case PreprocessingTypeEnum::NONE:
                return "none";
            case PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES:
                return "not duplicate clauses";
            case PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES:
                return "not subsumed clauses";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Cache::CachingScheme
