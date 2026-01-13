#pragma once

#include <string>

namespace Hydra::Other {

    enum class TemplateTypeEnum {
        CHAR8_T,
        CHAR16_T,
        CHAR32_T
    };

    inline std::string templateTypeEnumToString(TemplateTypeEnum templateType) noexcept {
        switch (templateType) {
            case TemplateTypeEnum::CHAR8_T:
                return "1 byte";
            case TemplateTypeEnum::CHAR16_T:
                return "2 bytes";
            case TemplateTypeEnum::CHAR32_T:
                return "4 bytes";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Other
