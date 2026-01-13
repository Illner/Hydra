#pragma once

#include <string>

#include "Hydra/other/parser/exceptions/CommandLineArgumentsParserException.hpp"

namespace Bella::Exception::CommandLineArguments {

    using CommandLineArgumentsParserException = Hydra::Exception::Other::Parser::CommandLineArguments::CommandLineArgumentsParserException;

    /**
     * Timeout is not a number
     */
    class TimeoutIsNotNumberException : public CommandLineArgumentsParserException {
    public:
        explicit TimeoutIsNotNumberException(const std::string& timeoutString)
            : CommandLineArgumentsParserException("The timeout is not a number (" + timeoutString + ")!") { }
    };

    /**
     * More circuit types are mentioned
     */
    class MoreCircuitTypesAreMentionedException : public CommandLineArgumentsParserException {
    public:
        MoreCircuitTypesAreMentionedException()
            : CommandLineArgumentsParserException("More circuit types are mentioned!") { }
    };

    /**
     * More partitioning hypergraph types are mentioned
     */
    class MorePartitioningHypergraphTypesAreMentionedException : public CommandLineArgumentsParserException {
    public:
        MorePartitioningHypergraphTypesAreMentionedException()
            : CommandLineArgumentsParserException("More partitioning hypergraph types are mentioned!") { }
    };

    /**
     * More decision heuristics are mentioned
     */
    class MoreDecisionHeuristicsAreMentionedException : public CommandLineArgumentsParserException {
    public:
        MoreDecisionHeuristicsAreMentionedException()
            : CommandLineArgumentsParserException("More decision heuristics are mentioned!") { }
    };

    /**
     * More component caching schemes are mentioned
     */
    class MoreComponentCachingSchemesAreMentionedException : public CommandLineArgumentsParserException {
    public:
        MoreComponentCachingSchemesAreMentionedException()
            : CommandLineArgumentsParserException("More component caching schemes are mentioned!") { }
    };

    /**
     * More component cache cleaning strategies are mentioned
     */
    class MoreComponentCacheCleaningStrategiesAreMentionedException : public CommandLineArgumentsParserException {
    public:
        MoreComponentCacheCleaningStrategiesAreMentionedException()
            : CommandLineArgumentsParserException("More component cache cleaning strategies are mentioned!") { }
    };

    /**
     * More hypergraph cut caching schemes are mentioned
     */
    class MoreHypergraphCutCachingSchemesAreMentionedException : public CommandLineArgumentsParserException {
    public:
        MoreHypergraphCutCachingSchemesAreMentionedException()
            : CommandLineArgumentsParserException("More hypergraph cut caching schemes are mentioned!") { }
    };

    /**
     * More hypergraph cut cache cleaning strategies are mentioned
     */
    class MoreHypergraphCutCacheCleaningStrategiesAreMentionedException : public CommandLineArgumentsParserException {
    public:
        MoreHypergraphCutCacheCleaningStrategiesAreMentionedException()
            : CommandLineArgumentsParserException("More hypergraph cut cache cleaning strategies are mentioned!") { }
    };

    /**
     * More hypergraph node weight types are mentioned
     */
    class MoreHypergraphNodeWeightTypesAreMentionedException : public CommandLineArgumentsParserException {
    public:
        MoreHypergraphNodeWeightTypesAreMentionedException()
            : CommandLineArgumentsParserException("More hypergraph node weight types are mentioned!") { }
    };

    /**
     * More recomputing hypergraph cut types are mentioned
     */
    class MoreRecomputingHypergraphCutTypesAreMentionedException : public CommandLineArgumentsParserException {
    public:
        MoreRecomputingHypergraphCutTypesAreMentionedException()
            : CommandLineArgumentsParserException("More recomputing hypergraph cut types are mentioned!") { }
    };

    /**
     * No circuit type is mentioned
     */
    class NoCircuitTypeIsMentionedException : public CommandLineArgumentsParserException {
    public:
        NoCircuitTypeIsMentionedException()
            : CommandLineArgumentsParserException("No circuit type is mentioned!") { }
    };

    /**
     * No partitioning hypergraph type is mentioned
     */
    class NoPartitioningHypergraphTypeIsMentionedException : public CommandLineArgumentsParserException {
    public:
        NoPartitioningHypergraphTypeIsMentionedException()
            : CommandLineArgumentsParserException("No partitioning hypergraph type is mentioned!") { }
    };
}   // namespace Bella::Exception::CommandLineArguments
