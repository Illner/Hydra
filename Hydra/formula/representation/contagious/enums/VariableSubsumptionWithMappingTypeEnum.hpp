#pragma once

#include <string>

#include "Hydra/other/hashMap/HashMap.hpp"

namespace Hydra::Formula::Representation::Contagious {

    enum class VariableSubsumptionWithMappingTypeEnum {
        FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
        ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING,

        NONE
    };

    using VariableSubsumptionWithMappingTypeEnumSetType = Other::HashMap::SetType<VariableSubsumptionWithMappingTypeEnum>;

    const inline VariableSubsumptionWithMappingTypeEnumSetType backwardVariableSubsumptionWithMappingTypeSet {};

    const inline VariableSubsumptionWithMappingTypeEnumSetType forwardVariableSubsumptionWithMappingTypeSet { VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION,
                                                                                                              VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING };

    inline std::string variableSubsumptionWithMappingTypeEnumToString(VariableSubsumptionWithMappingTypeEnum variableSubsumptionWithMappingType) noexcept {
        switch (variableSubsumptionWithMappingType) {
            case VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION:
                return "forward variable subsumption with mapping detection";
            case VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING:
                return "one-literal watching algorithm with mapping";
            case VariableSubsumptionWithMappingTypeEnum::NONE:
                return "none";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Formula::Representation::Contagious
