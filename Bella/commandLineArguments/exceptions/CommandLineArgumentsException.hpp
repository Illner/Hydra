#pragma once

#include <string>

#include "Hydra/compiler/exceptions/CommandLineArgumentsException.hpp"

namespace Bella::Exception::CommandLineArguments {

    using CommandLineArgumentsException = Hydra::Exception::CommandLineArguments::CommandLineArgumentsException;

    /**
     * Timeout is not a number
     */
    class TimeoutIsNotNumberException : public CommandLineArgumentsException {
    public:
        explicit TimeoutIsNotNumberException(const std::string& timeoutString)
            : CommandLineArgumentsException("The timeout is not a number (" + timeoutString + ")!") { }
    };

    /**
     * More circuit types are mentioned
     */
    class MoreCircuitTypesAreMentionedException : public CommandLineArgumentsException {
    public:
        MoreCircuitTypesAreMentionedException()
            : CommandLineArgumentsException("More circuit types are mentioned!") { }
    };

    /**
     * No circuit type is mentioned
     */
    class NoCircuitTypeIsMentionedException : public CommandLineArgumentsException {
    public:
        NoCircuitTypeIsMentionedException()
            : CommandLineArgumentsException("No circuit type is mentioned!") { }
    };

    /**
     * More decision heuristics are mentioned
     */
    class MoreDecisionHeuristicsAreMentionedException : public CommandLineArgumentsException {
    public:
        MoreDecisionHeuristicsAreMentionedException()
            : CommandLineArgumentsException("More decision heuristics are mentioned!") { }
    };

    /**
     * More component caching schemes are mentioned
     */
    class MoreComponentCachingSchemesAreMentionedException : public CommandLineArgumentsException {
    public:
        MoreComponentCachingSchemesAreMentionedException()
            : CommandLineArgumentsException("More component caching schemes are mentioned!") { }
    };

    /**
     * More component cache cleaning strategies are mentioned
     */
    class MoreComponentCacheCleaningStrategiesAreMentionedException : public CommandLineArgumentsException {
    public:
        MoreComponentCacheCleaningStrategiesAreMentionedException()
            : CommandLineArgumentsException("More component cache cleaning strategies are mentioned!") { }
    };

    /**
     * More hypergraph cut caching schemes are mentioned
     */
    class MoreHypergraphCutCachingSchemesAreMentionedException : public CommandLineArgumentsException {
    public:
        MoreHypergraphCutCachingSchemesAreMentionedException()
            : CommandLineArgumentsException("More hypergraph cut caching schemes are mentioned!") { }
    };

    /**
     * More hypergraph cut cache cleaning strategies are mentioned
     */
    class MoreHypergraphCutCacheCleaningStrategiesAreMentionedException : public CommandLineArgumentsException {
    public:
        MoreHypergraphCutCacheCleaningStrategiesAreMentionedException()
            : CommandLineArgumentsException("More hypergraph cut cache cleaning strategies are mentioned!") { }
    };

    /**
     * More hypergraph node weight types are mentioned
     */
    class MoreHypergraphNodeWeightTypesAreMentionedException : public CommandLineArgumentsException {
    public:
        MoreHypergraphNodeWeightTypesAreMentionedException()
            : CommandLineArgumentsException("More hypergraph node weight types are mentioned!") { }
    };

    /**
     * More recomputing hypergraph cut types are mentioned
     */
    class MoreRecomputingHypergraphCutTypesAreMentionedException : public CommandLineArgumentsException {
    public:
        MoreRecomputingHypergraphCutTypesAreMentionedException()
            : CommandLineArgumentsException("More recomputing hypergraph cut types are mentioned!") { }
    };
}   // namespace Bella::Exception::CommandLineArguments
