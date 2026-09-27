#pragma once

#include <string>

#include "Hydra/other/Other.hpp"
#include "Hydra/other/seed/Seed.hpp"

#include "Hydra/preprocessor/cnf/enums/CnfPreprocessorVariantTypeEnum.hpp"

#include "Hydra/compiler/Compiler.tpp"
#include "Hydra/formula/representation/contiguous/ContiguousFormulaRepresentation.tpp"

namespace Bella::CommandLineArguments {

    using LargeNumberType = Hydra::Other::LargeNumberType;

    /**
     * Command line arguments structure
     * Copy and move methods (default) are allowed!
     */
    struct CommandLineArgumentsStruct {
    public:
        using SeedType = Hydra::Other::Seed::SeedType;
        using CompilerConfigurationType = Hydra::CompilerConfiguration;
        using ContiguousFormulaRepresentationConfigurationType = Hydra::Formula::Representation::Contiguous::ContiguousFormulaRepresentationConfiguration;

    public:
        using CnfPreprocessorVariantTypeEnum = Hydra::Preprocessor::Cnf::CnfPreprocessorVariantTypeEnum;

    public:
        bool exit = false;   // help, version

        // Input
        std::string inputFilePath;

        // Output
        std::string outputFilePath;

        // Seed
        SeedType seed = Hydra::Other::Seed::NOT_DEFINED_SEED;

        // CNF preprocessor
        CnfPreprocessorVariantTypeEnum cnfPreprocessorVariantType = CnfPreprocessorVariantTypeEnum::NONE;

        // Others
        bool numberOfModels;
        LargeNumberType timeout;
        bool checkWhetherCircuitEntailsCnfFormula;

        // Statistics
        bool statisticsAddLabels;
        std::string statisticsFilePath;

        // Configuration
        CompilerConfigurationType compilerConfiguration;
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
    };
}   // namespace Bella::CommandLineArguments
