#pragma once

#include <string>

#include "Hydra/other/hashMap/HashMap.hpp"

namespace Hydra::Circuit::Node {

    enum class DecomposabilityTypeEnum {
        NONE,
        CLASSICAL_DECOMPOSABILITY,

        // Bella
        BELLA_DECOMPOSABILITY,
        posBELLA_DECOMPOSABILITY,
        negBELLA_DECOMPOSABILITY
    };

    using DecomposabilityTypeEnumSetType = Other::HashMap::SetType<DecomposabilityTypeEnum>;

    const inline DecomposabilityTypeEnumSetType bellaDecomposabilityTypeSet { DecomposabilityTypeEnum::BELLA_DECOMPOSABILITY,
                                                                              DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY,
                                                                              DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY };

    // The decomposability properties that support consistency check
    const inline DecomposabilityTypeEnumSetType supportConsistencyCheckDecomposabilityTypeSet { DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY,
                                                                                                DecomposabilityTypeEnum::BELLA_DECOMPOSABILITY,
                                                                                                DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY,
                                                                                                DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY };

    // The decomposability properties that support model counting
    const inline DecomposabilityTypeEnumSetType supportModelCountingDecomposabilityTypeSet { DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY };

    inline std::string decomposabilityTypeEnumToString(DecomposabilityTypeEnum decomposabilityType) noexcept {
        switch (decomposabilityType) {
            case DecomposabilityTypeEnum::NONE:
                return "none decomposability";
            case DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY:
                return "(classical) decomposability";
            case DecomposabilityTypeEnum::BELLA_DECOMPOSABILITY:
                return "Bella decomposability";
            case DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY:
                return "posBella decomposability";
            case DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY:
                return "negBella decomposability";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Circuit::Node
