#pragma once

#include <string>

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Exception::CommandLineArguments {

    /**
     * Command line arguments exception (main)
     */
    class CommandLineArgumentsException : public CompilerException {
    public:
        explicit CommandLineArgumentsException(const std::string& message)
            : CompilerException(message) { }

        explicit CommandLineArgumentsException(std::string&& message)
            : CompilerException(std::move(message)) { }
    };

    /**
     * More partitioning hypergraph types are mentioned
     */
    class MorePartitioningHypergraphTypesAreMentionedException : public CommandLineArgumentsException {
    public:
        MorePartitioningHypergraphTypesAreMentionedException()
            : CommandLineArgumentsException("More partitioning hypergraph types are mentioned!") { }
    };

    /**
     * No partitioning hypergraph type is mentioned
     */
    class NoPartitioningHypergraphTypeIsMentionedException : public CommandLineArgumentsException {
    public:
        NoPartitioningHypergraphTypeIsMentionedException()
            : CommandLineArgumentsException("No partitioning hypergraph type is mentioned!") { }
    };

    /**
     * More SAT solvers are mentioned
     */
    class MoreSatSolversAreMentionedException : public CommandLineArgumentsException {
    public:
        MoreSatSolversAreMentionedException()
            : CommandLineArgumentsException("More SAT solvers are mentioned!") { }
    };
}   // namespace Hydra::Exception::CommandLineArguments
