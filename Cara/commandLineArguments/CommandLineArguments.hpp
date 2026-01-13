#pragma once

#include <string_view>

#include "Cara/commandLineArguments/CommandLineArgumentsStructure.hpp"
#include "Hydra/other/parser/CommandLineArgumentsParser.hpp"

#include "Hydra/compiler/Compiler.tpp"

namespace Cara::CommandLineArguments {

    using ArgumentsType = typename Hydra::Other::Parser::CommandLineArguments::ArgumentsType;
    using ArgumentNameType = typename Hydra::Other::Parser::CommandLineArguments::ArgumentNameType;
    using ArgumentValueType = typename Hydra::Other::Parser::CommandLineArguments::ArgumentValueType;

    inline constexpr std::string_view DESCRIPTION = "     A #SAT solver.     ";

    // Files
    inline constexpr ArgumentNameType INPUT_ARGUMENT = "-i";

    // Partitioning hypergraph types
    inline constexpr ArgumentNameType CARA_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT = "-cd";
    inline constexpr ArgumentNameType KAHYPAR_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT = "-ka";
    inline constexpr ArgumentNameType CARA_SPEED_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT = "-cs";
    inline constexpr ArgumentNameType PATOH_HMETIS_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT = "-ph";

    // Preprocessing types
    inline constexpr ArgumentNameType NONE_PREPROCESSING_TYPE_ARGUMENT = "-n";
    inline constexpr ArgumentNameType NOT_SUBSUMED_CLAUSES_PREPROCESSING_TYPE_ARGUMENT = "-nsc";
    inline constexpr ArgumentNameType NOT_DUPLICATE_CLAUSES_PREPROCESSING_TYPE_ARGUMENT = "-ndc";

    // Others
    inline constexpr ArgumentNameType HELP_ARGUMENT = "-h";
    inline constexpr ArgumentNameType MUST_MULTIPLY_BY_FACTOR_ARGUMENT = "-mmbf";
    inline constexpr ArgumentNameType NUMBER_OF_SAMPLE_MOMENTS_ARGUMENT = "-nsm";

    /**
     * Parse the arguments
     */
    CommandLineArgumentsStruct parseCommandLineArguments(int argc, char* argv[]);

    /**
     * Initialize all the configurations in the command line arguments structure
     * @param commandLineArgumentsStruct a command line arguments structure
     */
    void initializeConfigurations(CommandLineArgumentsStruct& commandLineArgumentsStruct);

    /**
     * @param arguments the arguments
     * @return the partitioning hypergraph type
     * @throw MorePartitioningHypergraphTypesAreMentionedException if more partitioning hypergraph types are mentioned
     * @throw NoPartitioningHypergraphTypeIsMentionedException if no partitioning hypergraph type is mentioned
     */
    Hydra::PartitioningHypergraphTypeEnum getPartitioningHypergraphType(const ArgumentsType& arguments);

    /**
     * @param arguments the arguments
     * @return the preprocessing type
     * @throw MorePreprocessingTypesAreMentionedException if more preprocessing types are mentioned
     */
    Hydra::Cache::CachingScheme::PreprocessingTypeEnum getPreprocessingType(const ArgumentsType& arguments);

    /**
     * Print the help
     */
    void printHelp();
}   // namespace Cara::CommandLineArguments
