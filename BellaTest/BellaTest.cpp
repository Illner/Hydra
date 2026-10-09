#include <iostream>
#include <string>

#include "HydraTest/RunSession.hpp"

#include "BellaTest/compiler/Compiler.hpp"

#include "Hydra/other/Other.hpp"

int main(int argc, char* argv[]) {
    // Title
    Hydra::Other::printTitle(std::cout, "BellaTest", 49, ' ');

    return HydraTest::runSession(argc, argv, BellaTest::Compiler::generatedSeed);
}
