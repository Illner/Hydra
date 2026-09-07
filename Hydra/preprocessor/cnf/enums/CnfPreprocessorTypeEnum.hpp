#pragma once

#include <string>

namespace Hydra::Preprocessor::Cnf {

    enum class CnfPreprocessorTypeEnum {
        NONE,
        BIPE,
        ARJUN,
        WRAPPER
    };

    inline std::string cnfPreprocessorTypeEnumToString(CnfPreprocessorTypeEnum cnfPreprocessorType) noexcept {
        switch (cnfPreprocessorType) {
            case CnfPreprocessorTypeEnum::NONE:
                return "none";
            case CnfPreprocessorTypeEnum::BIPE:
                return "bipe";
            case CnfPreprocessorTypeEnum::ARJUN:
                return "Arjun";
            case CnfPreprocessorTypeEnum::WRAPPER:
                return "wrapper";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Preprocessor::Cnf
