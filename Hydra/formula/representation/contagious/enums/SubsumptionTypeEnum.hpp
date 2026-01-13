#pragma once

#include <string>

#include "Hydra/other/hashMap/HashMap.hpp"

namespace Hydra::Formula::Representation::Contagious {

    enum class SubsumptionTypeEnum {
        BACKWARD_SUBSUMPTION_DETECTION,
        BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION,

        FORWARD_SUBSUMPTION_DETECTION,
        ONE_LITERAL_WATCHING_ALGORITHM
    };

    using SubsumptionTypeEnumSetType = Other::HashMap::SetType<SubsumptionTypeEnum>;

    const inline SubsumptionTypeEnumSetType backwardSubsumptionTypeSet { SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION,
                                                                         SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION };

    const inline SubsumptionTypeEnumSetType forwardSubsumptionTypeSet { SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION,
                                                                        SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM };

    inline std::string subsumptionTypeEnumToString(SubsumptionTypeEnum subsumptionType) noexcept {
        switch (subsumptionType) {
            case SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION:
                return "backward subsumption detection";
            case SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION:
                return "backward subsumption detection - intersection";
            case SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION:
                return "forward subsumption detection";
            case SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM:
                return "one-literal watching algorithm";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Formula::Representation::Contagious
