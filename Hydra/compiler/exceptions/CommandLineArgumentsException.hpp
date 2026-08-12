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
     * More hypergraph partitioning types are mentioned
     */
    class MoreHypergraphPartitioningTypesAreMentionedException : public CommandLineArgumentsException {
    public:
        MoreHypergraphPartitioningTypesAreMentionedException()
            : CommandLineArgumentsException("More hypergraph partitioning types are mentioned!") { }
    };

    /**
     * No hypergraph partitioning type is mentioned
     */
    class NoHypergraphPartitioningTypeIsMentionedException : public CommandLineArgumentsException {
    public:
        NoHypergraphPartitioningTypeIsMentionedException()
            : CommandLineArgumentsException("No hypergraph partitioning type is mentioned!") { }
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
