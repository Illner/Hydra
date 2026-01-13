#pragma once

#include <string>
#include <string_view>

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Cara {

    enum class ModelCountingTypeEnum {
        MC,     // model counting
        WMC,    // weighted model counting
        PMC,    // projected model counting
        PWMC,   // projected weighted model counting

        UNDEFINED
    };

    inline std::string modelCountingTypeEnumToString(ModelCountingTypeEnum modelCountingType) noexcept {
        switch (modelCountingType) {
            case ModelCountingTypeEnum::MC:
                return "model counting";
            case ModelCountingTypeEnum::WMC:
                return "weighted model counting";
            case ModelCountingTypeEnum::PMC:
                return "projected model counting";
            case ModelCountingTypeEnum::PWMC:
                return "projected weighted model counting";
            case ModelCountingTypeEnum::UNDEFINED:
                return "undefined";
            default:
                return "name not set";
        }
    }

    /**
     * @param modelCountingType a model counting type
     * @return a string view used in the model counting header to define that model counting type
     */
    inline constexpr std::string_view modelCountingTypeEnumToStringViewUsedInModelCountingHeader(ModelCountingTypeEnum modelCountingType) {
        switch (modelCountingType) {
            case ModelCountingTypeEnum::MC:
                return "mc";
            case ModelCountingTypeEnum::WMC:
                return "wmc";
            case ModelCountingTypeEnum::PMC:
                return "pmc";
            case ModelCountingTypeEnum::PWMC:
                return "pwmc";
            default:
                throw Hydra::Exception::NotImplementedException(modelCountingTypeEnumToString(modelCountingType),
                                                                "Cara::modelCountingTypeEnumToStringViewUsedInModelCountingHeader");
        }
    }
}   // namespace Cara
