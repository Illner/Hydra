#pragma once

#include <string>

#include "Hydra/other/Other.hpp"

#include "Hydra/compiler/Compiler.tpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.tpp"

namespace Bella::CommandLineArguments {

    using LargeNumberType = Hydra::Other::LargeNumberType;

    /**
     * Command line arguments structure
     * Copy and move methods (default) are allowed!
     */
    struct CommandLineArgumentsStruct {
    public:
        using CompilerConfigurationType = typename Hydra::CompilerConfiguration;
        using ContagiousFormulaRepresentationConfigurationType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration;

    public:
        bool exit = false;   // help, version

        bool numberOfModels;
        LargeNumberType timeout;
        bool clausalEntailmentCheck;

        // Input
        std::string inputFilePath;

        // Output
        std::string outputFilePath;

        // Statistics
        bool statisticsAddLabels;
        std::string statisticsFilePath;

        CompilerConfigurationType compilerConfiguration;
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
    };
}   // namespace Bella::CommandLineArguments
