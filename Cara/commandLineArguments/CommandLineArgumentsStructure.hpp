#pragma once

#include <string>

#include "Hydra/other/type/arbitraryPrecisionInteger/ArbitraryPrecisionInteger.hpp"

#include "Cara/sharpSolver/enums/ModelCountingTypeEnum.hpp"

#include "Hydra/compiler/Compiler.tpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.tpp"

namespace Cara::CommandLineArguments {

    using MpzIntType = Hydra::Type::ArbitraryPrecisionInteger::MpzIntType;

    /**
     * Command line arguments structure
     * Copy and move methods (default) are allowed!
     */
    struct CommandLineArgumentsStruct {
    public:
        using SharpSolverConfigurationType = typename Hydra::CompilerConfiguration;
        using ContagiousFormulaRepresentationConfigurationType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration;

    public:
        using ModelCountingTypeEnum = typename Cara::ModelCountingTypeEnum;

    public:
        bool exit = false;   // help, version

        // Input
        std::string inputFilePath;

        std::size_t numberOfVariables;   // used to compute the number of models when the formula is empty
        MpzIntType mustMultiplyByFactor = MpzIntType(1);
        ModelCountingTypeEnum modelCountingType = ModelCountingTypeEnum::UNDEFINED;

        SharpSolverConfigurationType compilerConfiguration;
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
    };
}   // namespace Cara::CommandLineArguments
