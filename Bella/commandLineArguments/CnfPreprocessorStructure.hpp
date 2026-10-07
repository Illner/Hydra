#pragma once

#include "Hydra/preprocessor/cnf/enums/CnfPreprocessorVariantTypeEnum.hpp"

namespace Bella::CommandLineArguments {

    /**
     * CNF preprocessor structure
     * Copy and move methods (default) are allowed!
     */
    struct CnfPreprocessorStruct {
    public:
        using CnfPreprocessorVariantTypeEnum = Hydra::Preprocessor::Cnf::CnfPreprocessorVariantTypeEnum;

    public:
        CnfPreprocessorVariantTypeEnum cnfPreprocessorVariantType = CnfPreprocessorVariantTypeEnum::NONE;
    };
}   // namespace Bella::CommandLineArguments
