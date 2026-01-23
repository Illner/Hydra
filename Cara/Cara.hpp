#pragma once

#include <iostream>
#include <stdexcept>
#include <string_view>

#include "Cara/commandLineArguments/CommandLineArguments.hpp"
#include "Cara/commandLineArguments/CommandLineArgumentsStructure.hpp"
#include "Hydra/Hydra.hpp"
#include "Hydra/other/Other.hpp"

#include "Hydra/formula/exceptions/FormulaRepresentationException.hpp"

using MpzIntType = Cara::CommandLineArguments::MpzIntType;
using LargeFloatingNumberType = Hydra::Other::LargeFloatingNumberType;

inline constexpr std::string_view COMMENT_FOR_MODEL_COUNTING_COMPETITION = "c o";

/**
 * Print out the output respecting the format for the model counting competition
 * Model counting type: mc (model counting)
 * @param numberOfModels the number of models
 * @param computingTime [optional] the computing time
 */
void printModelCountingOutputForModelCountingCompetition(const MpzIntType& numberOfModels, LargeFloatingNumberType computingTime = 0);

int main(int argc, char* argv[]) {
    using CommandLineArgumentsStruct = typename Cara::CommandLineArguments::CommandLineArgumentsStruct;

    // Hydra::Other::printBuildType(std::cout);
    // Hydra::Other::printMacros(std::cout);

    try {
        CommandLineArgumentsStruct commandLineArgumentsStruct = Cara::CommandLineArguments::parseCommandLineArguments(argc, argv);

        // Exit - help, version
        if (commandLineArgumentsStruct.exit)
            return 0;

        // Title
        Hydra::Other::printTitle(std::cout, " Cara ", 20, '-', COMMENT_FOR_MODEL_COUNTING_COMPETITION);
        std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << std::endl;

        try {
            coreMain(commandLineArgumentsStruct, nullptr, nullptr);
        }
        // The formula is empty
        catch (const Hydra::Exception::Formula::Representation::FormulaIsEmptyException& e) {
            modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
            printConfigurationBeforeCompilation(commandLineArgumentsStruct);

            // Compute the number of models
            MpzIntType numberOfModels = MpzIntType(1) << commandLineArgumentsStruct.numberOfVariables;   // 2^|V|
            numberOfModels *= commandLineArgumentsStruct.mustMultiplyByFactor;

            printModelCountingOutputForModelCountingCompetition(numberOfModels);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
