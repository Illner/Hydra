#pragma once

#include "Bella/commandLineArguments/CommandLineArgumentsStructure.hpp"
#include "Hydra/other/parser/CommandLineArgumentsParser.hpp"

#include "Hydra/compiler/Compiler.tpp"

namespace Bella::CommandLineArguments {

    using ArgumentsType = typename Hydra::Other::Parser::CommandLineArguments::ArgumentsType;
    using ArgumentNameType = typename Hydra::Other::Parser::CommandLineArguments::ArgumentNameType;
    using ArgumentValueType = typename Hydra::Other::Parser::CommandLineArguments::ArgumentValueType;

    // Circuit types - standard
    inline constexpr ArgumentNameType dDNNF_ARGUMENT = "-d";
    inline constexpr ArgumentNameType sdDNNF_ARGUMENT = "-sd";

    // Circuit types - weak and variants
    inline constexpr ArgumentNameType wDNNF_ARGUMENT = "-w";
    inline constexpr ArgumentNameType pwDNNF_ARGUMENT = "-pw";
    inline constexpr ArgumentNameType nwDNNF_ARGUMENT = "-nw";

    // Circuit types - Bella
    inline constexpr ArgumentNameType Bella_ARGUMENT = "-b";
    inline constexpr ArgumentNameType posBella_ARGUMENT = "-pb";
    inline constexpr ArgumentNameType negBella_ARGUMENT = "-nb";
    inline constexpr ArgumentNameType Krom_Bella_ARGUMENT = "-kb";

    // Files
    inline constexpr ArgumentNameType INPUT_ARGUMENT = "-i";
    inline constexpr ArgumentNameType OUTPUT_ARGUMENT = "-o";
    inline constexpr ArgumentNameType STATISTICS_ARGUMENT = "-s";

    // Component caching schemes
    inline constexpr ArgumentNameType NONE_COMPONENT_CACHING_SCHEME_ARGUMENT = "-n_ccs";
    inline constexpr ArgumentNameType STANDARD_COMPONENT_CACHING_SCHEME_ARGUMENT = "-s_ccs";
    inline constexpr ArgumentNameType HYBRID_COMPONENT_CACHING_SCHEME_ARGUMENT = "-h_ccs";
    inline constexpr ArgumentNameType BASIC_COMPONENT_CACHING_SCHEME_ARGUMENT = "-b_ccs";
    inline constexpr ArgumentNameType I_COMPONENT_CACHING_SCHEME_ARGUMENT = "-i_ccs";
    inline constexpr ArgumentNameType CARA_COMPONENT_CACHING_SCHEME_ARGUMENT = "-c_ccs";

    // Component cache cleaning strategies
    inline constexpr ArgumentNameType NONE_COMPONENT_CACHE_CLEANING_STRATEGY_ARGUMENT = "-n_cccs";
    inline constexpr ArgumentNameType SHARP_SAT_COMPONENT_CACHE_CLEANING_STRATEGY_ARGUMENT = "-s_cccs";
    inline constexpr ArgumentNameType CARA_COMPONENT_CACHE_CLEANING_STRATEGY_ARGUMENT = "-c_cccs";

    // Hypergraph cut caching schemes
    inline constexpr ArgumentNameType NONE_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT = "-n_hccs";
    inline constexpr ArgumentNameType STANDARD_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT = "-s_hccs";
    inline constexpr ArgumentNameType HYBRID_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT = "-h_hccs";
    inline constexpr ArgumentNameType BASIC_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT = "-b_hccs";
    inline constexpr ArgumentNameType CARA_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT = "-c_hccs";

    // Hypergraph cut cache cleaning strategies
    inline constexpr ArgumentNameType NONE_HYPERGRAPH_CUT_CACHE_CLEANING_STRATEGY_ARGUMENT = "-n_hcccs";
    inline constexpr ArgumentNameType SHARP_SAT_HYPERGRAPH_CUT_CACHE_CLEANING_STRATEGY_ARGUMENT = "-s_hcccs";
    inline constexpr ArgumentNameType CARA_HYPERGRAPH_CUT_CACHE_CLEANING_STRATEGY_ARGUMENT = "-c_hcccs";

    // Decision heuristics
    inline constexpr ArgumentNameType RANDOM_DECISION_HEURISTIC_ARGUMENT = "-r_dh";
    inline constexpr ArgumentNameType DLCS_DECISION_HEURISTIC_ARGUMENT = "-dlcs_dh";
    inline constexpr ArgumentNameType DLIS_DECISION_HEURISTIC_ARGUMENT = "-dlis_dh";
    inline constexpr ArgumentNameType EUPC_DECISION_HEURISTIC_ARGUMENT = "-eupc_dh";
    inline constexpr ArgumentNameType AUPC_DECISION_HEURISTIC_ARGUMENT = "-aupc_dh";
    inline constexpr ArgumentNameType VSIDS_DECISION_HEURISTIC_ARGUMENT = "-vsids_dh";
    inline constexpr ArgumentNameType VSADS_DECISION_HEURISTIC_ARGUMENT = "-vsads_dh";
    inline constexpr ArgumentNameType DLCS_DLIS_DECISION_HEURISTIC_ARGUMENT = "-dlcs_dlis_dh";
    inline constexpr ArgumentNameType JEROSLOW_WANG_ONE_SIDED_DECISION_HEURISTIC_ARGUMENT = "-jwos_dh";
    inline constexpr ArgumentNameType JEROSLOW_WANG_TWO_SIDED_DECISION_HEURISTIC_ARGUMENT = "-jwts_dh";

    // Hypergraph node weight types
    inline constexpr ArgumentNameType NONE_HYPERGRAPH_NODE_WEIGHT_ARGUMENT = "-n_hnw";
    inline constexpr ArgumentNameType STANDARD_HYPERGRAPH_NODE_WEIGHT_ARGUMENT = "-s_hnw";
    inline constexpr ArgumentNameType CLAUSE_LENGTH_HYPERGRAPH_NODE_WEIGHT_ARGUMENT = "-cl_hnw";

    // Recomputing hypergraph cut types
    inline constexpr ArgumentNameType ALWAYS_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT = "-a_rhc";
    inline constexpr ArgumentNameType IMMENSE_UNIT_PROPAGATION_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT = "-iup_rhc";
    inline constexpr ArgumentNameType FORMULA_SPLIT_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT = "-fs_rhc";
    inline constexpr ArgumentNameType EMPTY_HYPERGRAPH_CUT_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT = "-ehc_rhc";
    inline constexpr ArgumentNameType IMMENSE_UNIT_PROPAGATION_OR_FORMULA_SPLIT_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT = "-iup_fs_rhc";

    // Partitioning hypergraph types
    inline constexpr ArgumentNameType CARA_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT = "-cd";
    inline constexpr ArgumentNameType KAHYPAR_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT = "-ka";
    inline constexpr ArgumentNameType PATOH_HMETIS_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT = "-ph";

    // Others
    inline constexpr ArgumentNameType HELP_ARGUMENT = "-h";
    inline constexpr ArgumentNameType COUNT_ARGUMENT = "-c";
    inline constexpr ArgumentNameType TIMEOUT_ARGUMENT = "-t";
    inline constexpr ArgumentNameType METACENTRUM_ARGUMENT = "-m";
    inline constexpr ArgumentNameType READABLE_STATISTICS_ARGUMENT = "-r";
    inline constexpr ArgumentNameType EQUIVALENCE_SIMPLIFICATION_METHOD_ARGUMENT = "-e";

    inline constexpr LargeNumberType TIMEOUT_DEFAULT = LargeNumberType(24 * 60 * 60);   // 24 hours

    /**
     * Parse the arguments
     */
    CommandLineArgumentsStruct parseCommandLineArguments(int argc, char* argv[]);

    /**
     * @param arguments the arguments
     * @param required is timeout required
     * @return the timeout. If the timeout is not mentioned, TIMEOUT_DEFAULT is returned.
     * @throw TimeoutIsNotNumberException if the timeout is not a number
     */
    LargeNumberType getTimeout(const ArgumentsType& arguments, bool required);

    /**
     * @param arguments the arguments
     * @return the circuit type
     * @throw MoreCircuitTypesAreMentionedException if more circuit types are mentioned
     * @throw NoCircuitTypeIsMentionedException if no circuit type is mentioned
     */
    Hydra::Circuit::CircuitTypeEnum getCircuitType(const ArgumentsType& arguments);

    /**
     * @param arguments the arguments
     * @return the partitioning hypergraph type
     * @throw MorePartitioningHypergraphTypesAreMentionedException if more partitioning hypergraph types are mentioned
     * @throw NoPartitioningHypergraphTypeIsMentionedException if no partitioning hypergraph type is mentioned
     */
    Hydra::PartitioningHypergraphTypeEnum getPartitioningHypergraphType(const ArgumentsType& arguments);

    /**
     * @param arguments the arguments
     * @return the decision heuristic
     * @throw MoreDecisionHeuristicsAreMentionedException if more decision heuristics are mentioned
     */
    Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum getDecisionHeuristicType(const ArgumentsType& arguments);

    /**
     * @param arguments the arguments
     * @return the component caching scheme
     * @throw MoreComponentCachingSchemesAreMentionedException if more component caching schemes are mentioned
     */
    Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum getComponentCachingSchemeType(const ArgumentsType& arguments);

    /**
     * @param arguments the arguments
     * @return the component cache cleaning strategy
     * @throw MoreComponentCacheCleaningStrategiesAreMentionedException if more component cache cleaning strategies are mentioned
     */
    Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum getComponentCacheCleaningStrategyType(const ArgumentsType& arguments);

    /**
     * @param arguments the arguments
     * @return the hypergraph cut caching scheme
     * @throw MoreHypergraphCutCachingSchemesAreMentionedException if more hypergraph cut caching schemes are mentioned
     */
    Hydra::Cache::CachingScheme::CachingSchemeTypeEnum getHypergraphCutCachingSchemeType(const ArgumentsType& arguments);

    /**
     * @param arguments the arguments
     * @return the hypergraph cut cache cleaning strategy
     * @throw MoreHypergraphCutCacheCleaningStrategiesAreMentionedException if more hypergraph cut cache cleaning strategies are mentioned
     */
    Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum getHypergraphCutCacheCleaningStrategyType(const ArgumentsType& arguments);

    /**
     * @param arguments the arguments
     * @return the hypergraph node weight type
     * @throw MoreHypergraphNodeWeightTypesAreMentionedException if more hypergraph node weight types are mentioned
     */
    Hydra::PartitioningHypergraph::VertexWeightTypeEnum getHypergraphNodeWeightType(const ArgumentsType& arguments);

    /**
     * @param arguments the arguments
     * @return the recomputing hypergraph cut type
     * @throw MoreRecomputingHypergraphCutTypesAreMentionedException if more recomputing hypergraph cut types are mentioned
     */
    Hydra::RecomputingHypergraphCutTypeEnum getRecomputingHypergraphCutType(const ArgumentsType& arguments);

    /**
     * Print the help
     */
    void printHelp();
}   // namespace Bella::CommandLineArguments
