#pragma once

#include <string>

namespace Hydra {

    enum class IgnorePureLiteralTypeEnum {
        NONE,
        ONLY_POSITIVE,
        ONLY_NEGATIVE,
        BOTH_POSITIVE_AND_NEGATIVE
    };

    inline std::string ignorePureLiteralTypeEnumToString(IgnorePureLiteralTypeEnum ignorePureLiteralType) noexcept {
        switch (ignorePureLiteralType) {
            case IgnorePureLiteralTypeEnum::NONE:
                return "pure literals are not ignored";
            case IgnorePureLiteralTypeEnum::ONLY_POSITIVE:
                return "only positive pure literals are ignored";
            case IgnorePureLiteralTypeEnum::ONLY_NEGATIVE:
                return "only negative pure literals are ignored";
            case IgnorePureLiteralTypeEnum::BOTH_POSITIVE_AND_NEGATIVE:
                return "both positive and negative pure literals are ignored";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra
