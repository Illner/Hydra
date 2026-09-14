#pragma once

#include <string>

#include "Hydra/other/seed/Seed.hpp"
#include "Hydra/other/type/arbitraryPrecisionInteger/ArbitraryPrecisionInteger.hpp"

#include "Cara/sharpSolver/enums/ModelCountingTypeEnum.hpp"

#include "Hydra/compiler/Compiler.tpp"
#include "Hydra/formula/representation/contiguous/ContiguousFormulaRepresentation.tpp"

namespace Cara::CommandLineArguments {

    using MpzIntType = Hydra::Type::ArbitraryPrecisionInteger::MpzIntType;

    /**
     * Command line arguments structure
     * Copy and move methods (default) are allowed!
     */
    struct CommandLineArgumentsStruct {
    public:
        using SeedType = Hydra::Other::Seed::SeedType;
        using SharpSolverConfigurationType = Hydra::CompilerConfiguration;
        using ContiguousFormulaRepresentationConfigurationType = Hydra::Formula::Representation::Contiguous::ContiguousFormulaRepresentationConfiguration;

    public:
        using ModelCountingTypeEnum = typename Cara::ModelCountingTypeEnum;

    public:
        bool exit = false;   // help, version

        // Input
        std::string inputFilePath;

        // Seed
        SeedType seed = Hydra::Other::Seed::NOT_DEFINED_SEED;

        // Others
        std::size_t numberOfVariables;   // used to compute the number of models when the formula is empty
        MpzIntType mustMultiplyByFactor = MpzIntType(1);
        ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;

        // Configuration
        SharpSolverConfigurationType compilerConfiguration;
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
    };
}   // namespace Cara::CommandLineArguments
