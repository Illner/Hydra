#include <iostream>
#include <string>

#include "HydraTest/RunSession.hpp"

#include "Hydra/other/Other.hpp"

int main(int argc, char* argv[]) {
    // Title
    Hydra::Other::printTitle(std::cout, "HydraTest", 49, ' ');

    return HydraTest::runSession(argc, argv);
}
