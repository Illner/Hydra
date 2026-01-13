#define CATCH_CONFIG_RUNNER

#include <fstream>
#include <iostream>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"

#include "Hydra/other/Other.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

int main(int argc, char* argv[]) {
    Hydra::Other::printBuildType(std::cout);
    Hydra::Other::printMacros(std::cout);

    // Create the log file
    {
        std::ofstream logFile(HydraTest::logFilePath, std::ios::out);

        if (!logFile.is_open())
            throw Hydra::Exception::CannotCreateFileException(HydraTest::logFilePath);
    }

    int result = Catch::Session().run(argc, argv);

    return result;
}
