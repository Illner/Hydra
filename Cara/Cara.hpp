#pragma once

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string_view>

#include "Cara/commandLineArguments/CommandLineArguments.hpp"
#include "Cara/commandLineArguments/CommandLineArgumentsStructure.hpp"
#include "Hydra/Hydra.hpp"
#include "Hydra/other/Other.hpp"

#include "Hydra/compiler/exceptions/ParserException.hpp"
#include "Hydra/formula/exceptions/FormulaRepresentationException.hpp"

namespace Cara {

    using MpzIntType = CommandLineArguments::MpzIntType;
    using LargeFloatingNumberType = Hydra::Other::LargeFloatingNumberType;

    inline constexpr std::string_view COMMENT_FOR_MODEL_COUNTING_COMPETITION = "c o";

    /**
     * Print out the output respecting the format for the model counting competition
     * Model counting type: mc (model counting)
     * @param numberOfModels the number of models
     * @param computingTime [optional] the computing time
     */
    void printModelCountingOutputForModelCountingCompetition(const MpzIntType& numberOfModels, LargeFloatingNumberType computingTime = 0);
}   // namespace Cara

int main(int argc, char* argv[]) {
    using MpzIntType = Cara::MpzIntType;
    using Cara::COMMENT_FOR_MODEL_COUNTING_COMPETITION;
    using CommandLineArgumentsStruct = typename Cara::CommandLineArguments::CommandLineArgumentsStruct;

    // Hydra::Other::printBuildType(std::cout);
    // Hydra::Other::printMacros(std::cout);

    try {
        CommandLineArgumentsStruct commandLineArgumentsStruct = Cara::CommandLineArguments::parseCommandLineArguments(argc, argv);

        // Exit - help, version
        if (commandLineArgumentsStruct.exit)
            return EXIT_SUCCESS;

        // Title
        Hydra::Other::printTitle(std::cout, " Cara ", 50, '-', COMMENT_FOR_MODEL_COUNTING_COMPETITION);
        std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << std::endl;

        try {
            Hydra::coreMain(commandLineArgumentsStruct, nullptr, nullptr);
        }
        // The formula is empty
        catch (const Hydra::Exception::Formula::Representation::FormulaIsEmptyException& e) {
            Hydra::modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
            Hydra::printConfigurationBeforeCompilation(commandLineArgumentsStruct);

            // Compute the number of models
            MpzIntType numberOfModels = MpzIntType(1) << commandLineArgumentsStruct.numberOfVariables;   // 2^|V|
            numberOfModels *= commandLineArgumentsStruct.mustMultiplyByFactor;

            Cara::printModelCountingOutputForModelCountingCompetition(numberOfModels);
        }
        // There is an empty clause
        catch (const Hydra::Exception::Parser::ClauseIsEmptyException& e) {
            Hydra::modifyConfigurationAfterParsingFormula(commandLineArgumentsStruct);
            Hydra::printConfigurationBeforeCompilation(commandLineArgumentsStruct);

            MpzIntType numberOfModels = MpzIntType(0);
            Cara::printModelCountingOutputForModelCountingCompetition(numberOfModels);
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
