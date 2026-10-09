#include "./RunSession.hpp"

#define CATCH_CONFIG_RUNNER

#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/external/unitTesting/Catch2/catch.hpp"

#include "Hydra/other/Other.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/other/parser/commandLineArgument/exceptions/CommandLineArgumentParserException.hpp"

namespace HydraTest {

    void createLogFile(SeedType seed) {
        std::ofstream logFile(logFilePath, std::ios::out);

        if (!logFile.is_open())
            throw Hydra::Exception::CannotCreateFileException(logFilePath);

        // The seed is provided
        if (seed != Hydra::Other::Seed::NOT_DEFINED_SEED) {
            logFile << "Seed: " << std::to_string(seed) << std::endl;
            logFile << std::endl;
        }

        // Print
        std::cout << "Log file: " << logFilePath << std::endl;
        std::cout << std::endl;
    }

    int runSession(int argc, char* argv[]) {
        // Hydra::Other::printBuildType(std::cout);
        // Hydra::Other::printMacros(std::cout);

        try {
            Catch::Session session;
            const Catch::ConfigData& configData = session.configData();

            // Invalid arguments
            int returnCode = session.applyCommandLine(argc, argv);
            if (returnCode != 0)
                return returnCode;

            if (!configData.showHelp && !configData.libIdentify && !configData.listTests &&
                !configData.listTags && !configData.listReporters && !configData.listTestNamesOnly) {
                // Create the log file
                createLogFile();
            }

            return session.run();
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;

            return Catch::MaxExitCode;
        }
    }

    int runSession(int argc, char* argv[], SeedType& seed) {
        // Hydra::Other::printBuildType(std::cout);
        // Hydra::Other::printMacros(std::cout);

        try {
            seed = Hydra::Other::Seed::NOT_DEFINED_SEED;

            Catch::Session session;
            const Catch::ConfigData& configData = session.configData();
            session.cli(session.cli() | Catch::clara::Opt(seed, "seed")["--seed"]("seed for the tests"));

            // Invalid arguments
            int returnCode = session.applyCommandLine(argc, argv);
            if (returnCode != 0)
                return returnCode;

            if (!configData.showHelp && !configData.libIdentify && !configData.listTests &&
                !configData.listTags && !configData.listReporters && !configData.listTestNamesOnly) {
                // The seed is NOT provided
                if (seed == Hydra::Other::Seed::NOT_DEFINED_SEED)
                    seed = Hydra::Other::Seed::generateSeed();

                // The seed is invalid
                if (!Hydra::Other::Seed::isSeedValid(seed))
                    throw Hydra::Exception::Other::Parser::CommandLineArgument::InvalidSeedException(seed);

                // Print
                std::cout << "Seed: " << std::to_string(seed) << std::endl;

                // Create the log file
                createLogFile(seed);
            }

            return session.run();
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;

            return Catch::MaxExitCode;
        }
    }
}   // namespace HydraTest
