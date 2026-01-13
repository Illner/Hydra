#pragma once

#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>

#include "Bella/commandLineArguments/CommandLineArguments.hpp"
#include "Bella/commandLineArguments/CommandLineArgumentsStructure.hpp"
#include "Hydra/Hydra.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/statistics/Statistics.hpp"

int main(int argc, char* argv[]) {
    using CommandLineArgumentsStruct = typename Bella::CommandLineArguments::CommandLineArgumentsStruct;

    // Hydra::Other::printBuildType(std::cout);
    // Hydra::Other::printMacros(std::cout);

    try {
        CommandLineArgumentsStruct commandLineArgumentsStruct = Bella::CommandLineArguments::parseCommandLineArguments(argc, argv);

        // Help
        if (commandLineArgumentsStruct.help)
            return 0;

        // Title
        Hydra::Other::printTitle(std::cout, "Bella", 50, ' ');
        std::cout << std::endl;

        Hydra::Statistics::Statistics statistics;

        // Atomic
        AtomicBoolType killedByMainThread = false;

        // Future
        std::packaged_task<void(CommandLineArgumentsStruct&, StatisticsPtrType, AtomicBoolPtrType)> task(coreMain<CommandLineArgumentsStruct>);
        auto future = task.get_future();

        std::thread thread(std::move(task), std::ref(commandLineArgumentsStruct),
                           commandLineArgumentsStruct.statisticsFilePath.empty() ? nullptr : &statistics, &killedByMainThread);

        // Waiting
        if (future.wait_for(std::chrono::seconds(commandLineArgumentsStruct.timeout)) == std::future_status::timeout)
            killedByMainThread.store(true, std::memory_order::relaxed);

        thread.join();
        future.get();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
