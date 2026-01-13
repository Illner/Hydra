#pragma once

#include "Hydra/formula/representation/RecognitionTypeStructure.hpp"

#include "Hydra/formula/representation/contagious/enums/SubsumptionTypeEnum.hpp"
#include "Hydra/formula/representation/contagious/enums/VariableSubsumptionWithMappingTypeEnum.hpp"

namespace Hydra::Formula::Representation::Contagious {

    /**
     * Contagious formula representation - configuration
     */
    struct ContagiousFormulaRepresentationConfiguration {
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
}   // namespace Hydra::Formula::Representation::Contagious
