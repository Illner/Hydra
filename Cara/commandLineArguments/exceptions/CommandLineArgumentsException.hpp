#pragma once

#include <string>

#include "Hydra/other/parser/exceptions/CommandLineArgumentsParserException.hpp"

namespace Cara::Exception::CommandLineArguments {

    using CommandLineArgumentsParserException = Hydra::Exception::Other::Parser::CommandLineArguments::CommandLineArgumentsParserException;

    /**
     * More partitioning hypergraph types are mentioned
     */
    class MorePartitioningHypergraphTypesAreMentionedException : public CommandLineArgumentsParserException {
    public:
        MorePartitioningHypergraphTypesAreMentionedException()
            : CommandLineArgumentsParserException("More partitioning hypergraph types are mentioned!") { }
    };

    /**
     * No partitioning hypergraph type is mentioned
     */
    class NoPartitioningHypergraphTypeIsMentionedException : public CommandLineArgumentsParserException {
    public:
        NoPartitioningHypergraphTypeIsMentionedException()
            : CommandLineArgumentsParserException("No partitioning hypergraph type is mentioned!") { }
    };

    /**
     * More preprocessing types are mentioned
     */
    class MorePreprocessingTypesAreMentionedException : public CommandLineArgumentsParserException {
    public:
        MorePreprocessingTypesAreMentionedException()
            : CommandLineArgumentsParserException("More preprocessing types are mentioned!") { }
    };

    /**
     * The must-multiply-by factor is zero
     */
    class MustMultiplyByFactorIsZeroException : public CommandLineArgumentsParserException {
    public:
        MustMultiplyByFactorIsZeroException()
            : CommandLineArgumentsParserException("The must-multiply-by factor is zero!") { }
    };

    /**
     * The must-multiply-by factor is invalid
     */
    class MustMultiplyByFactorIsInvalidException : public CommandLineArgumentsParserException {
    public:
        explicit MustMultiplyByFactorIsInvalidException(const std::string& mustMultiplyByFactorString)
            : CommandLineArgumentsParserException("The must-multiply-by factor (" + mustMultiplyByFactorString + ") is invalid!") { }
    };
}   // namespace Cara::Exception::CommandLineArguments
