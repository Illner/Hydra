#pragma once

#include "Hydra/formula/representation/RecognitionTypeStructure.hpp"

#include "Hydra/formula/representation/contiguous/enums/SubsumptionTypeEnum.hpp"
#include "Hydra/formula/representation/contiguous/enums/VariableSubsumptionWithMappingTypeEnum.hpp"

namespace Hydra::Formula::Representation::Contiguous {

    /**
     * Contiguous formula representation - configuration
     */
    struct ContiguousFormulaRepresentationConfiguration {
    public:
        /**
         * Recognition type
         */
        RecognitionTypeStruct recognitionTypeStruct;

        /**
         * Subsumption type
         */
        SubsumptionTypeEnum subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        /**
         * Variable subsumption with mapping type
         */
        VariableSubsumptionWithMappingTypeEnum variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;
    };
}   // namespace Hydra::Formula::Representation::Contiguous
