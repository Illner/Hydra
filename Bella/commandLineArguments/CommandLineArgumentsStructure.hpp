#pragma once

#include <string>

#include "Hydra/other/Other.hpp"

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
        using CompilerConfigurationType = typename Hydra::CompilerConfiguration;
        using ContiguousFormulaRepresentationConfigurationType = typename Hydra::Formula::Representation::Contiguous::ContiguousFormulaRepresentationConfiguration;

    public:
        bool exit = false;   // help, version

        bool numberOfModels;
        LargeNumberType timeout;
        bool checkWhetherCircuitEntailsCnfFormula;

        // Input
        std::string inputFilePath;

        // Output
        std::string outputFilePath;

        // Statistics
        bool statisticsAddLabels;
        std::string statisticsFilePath;

        CompilerConfigurationType compilerConfiguration;
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
    };
}   // namespace Bella::CommandLineArguments
