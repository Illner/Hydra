#pragma once

#include <string_view>

#include "Cara/commandLineArguments/CommandLineArgumentsStructure.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/parser/CommandLineArgumentsParser.hpp"
#include "Hydra/other/version/Version.hpp"

#include "Cara/commandLineArguments/exceptions/CommandLineArgumentsException.hpp"
#include "Hydra/other/parser/exceptions/CommandLineArgumentsParserException.hpp"

#include "Hydra/compiler/Compiler.tpp"

namespace Cara::CommandLineArguments {

    using ArgumentsType = typename Hydra::Other::Parser::CommandLineArguments::ArgumentsType;
    using ArgumentNameType = typename Hydra::Other::Parser::CommandLineArguments::ArgumentNameType;
    using ArgumentValueType = typename Hydra::Other::Parser::CommandLineArguments::ArgumentValueType;

    inline constexpr std::string_view DESCRIPTION = "     An isomorphism-aware #SAT solver.     ";

    // Files
    inline constexpr ArgumentNameType INPUT_ARGUMENT = "-i";

    // Hypergraph partitioning
    inline constexpr ArgumentNameType CARA_HYPERGRAPH_PARTITIONING_ARGUMENT = "-cd";
    inline constexpr ArgumentNameType KAHYPAR_HYPERGRAPH_PARTITIONING_ARGUMENT = "-ka";
    inline constexpr ArgumentNameType CARA_SPEED_HYPERGRAPH_PARTITIONING_ARGUMENT = "-cs";
    inline constexpr ArgumentNameType PATOH_HMETIS_HYPERGRAPH_PARTITIONING_ARGUMENT = "-ph";

    // SAT solvers
    inline constexpr ArgumentNameType MINISAT_SAT_SOLVER_ARGUMENT = "-m";
    inline constexpr ArgumentNameType GLUCOSE_SAT_SOLVER_ARGUMENT = "-g";

    // Preprocessing types of Cara caching scheme
    inline constexpr ArgumentNameType NONE_PREPROCESSING_TYPE_ARGUMENT = "-n";
    inline constexpr ArgumentNameType NOT_SUBSUMED_CLAUSES_PREPROCESSING_TYPE_ARGUMENT = "-nsc";
    inline constexpr ArgumentNameType NOT_DUPLICATE_CLAUSES_PREPROCESSING_TYPE_ARGUMENT = "-ndc";

    // Other options
    inline constexpr ArgumentNameType HELP_ARGUMENT = "-h";
    inline constexpr ArgumentNameType VERSION_ARGUMENT = "-v";
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
     * @return the SAT solver
     * @throw MoreSatSolversAreMentionedException if more SAT solvers are mentioned
     */
    Hydra::SatSolver::SatSolverTypeEnum getSatSolverType(const ArgumentsType& arguments);

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
