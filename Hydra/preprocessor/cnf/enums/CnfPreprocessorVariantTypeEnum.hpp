#pragma once

#include <string>

#include "Hydra/other/hashMap/HashMap.hpp"

namespace Hydra::Preprocessor::Cnf {

    enum class CnfPreprocessorVariantTypeEnum {
        NONE,

        // Bipe
        BIPE_EQUIV_LIGHT,
        BIPE_EQUIV_FULL,
        BIPE_SHARP_EQUIV,

        // Arjun
        ARJUN,

        // Wrapper
        WRAPPER
    };

    using CnfPreprocessorVariantTypeEnumSetType = Other::HashMap::SetType<CnfPreprocessorVariantTypeEnum>;

    const inline CnfPreprocessorVariantTypeEnumSetType bipeCnfPreprocessorVariantTypeSet { CnfPreprocessorVariantTypeEnum::BIPE_EQUIV_LIGHT,
                                                                                           CnfPreprocessorVariantTypeEnum::BIPE_EQUIV_FULL,
                                                                                           CnfPreprocessorVariantTypeEnum::BIPE_SHARP_EQUIV };

    const inline CnfPreprocessorVariantTypeEnumSetType arjunCnfPreprocessorVariantTypeSet { CnfPreprocessorVariantTypeEnum::ARJUN };

    inline std::string cnfPreprocessorVariantTypeEnumToString(CnfPreprocessorVariantTypeEnum cnfPreprocessorVariantType) noexcept {
        switch (cnfPreprocessorVariantType) {
            case CnfPreprocessorVariantTypeEnum::NONE:
                return "none";
            // Bipe
            case CnfPreprocessorVariantTypeEnum::BIPE_EQUIV_LIGHT:
                return "bipe (equiv-light)";
            case CnfPreprocessorVariantTypeEnum::BIPE_EQUIV_FULL:
                return "bipe (equiv-full)";
            case CnfPreprocessorVariantTypeEnum::BIPE_SHARP_EQUIV:
                return "bipe (sharp-equiv)";
            // Arjun
            case CnfPreprocessorVariantTypeEnum::ARJUN:
                return "Arjun";
            // Wrapper
            case CnfPreprocessorVariantTypeEnum::WRAPPER:
                return "wrapper";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Preprocessor::Cnf
