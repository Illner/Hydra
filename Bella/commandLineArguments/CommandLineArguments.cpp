#include "./CommandLineArguments.hpp"

#include <cassert>
#include <iostream>
#include <string>

#include "Hydra/other/Other.hpp"
#include "Hydra/other/parser/Parser.hpp"

#include "Bella/commandLineArguments/exceptions/CommandLineArgumentsException.hpp"
#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/compiler/exceptions/ParserException.hpp"
#include "Hydra/other/parser/exceptions/CommandLineArgumentsParserException.hpp"

#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"
#include "Hydra/satSolver/minisat/enums/VsidsScoreTypeEnum.hpp"

#include "Hydra/compiler/Compiler.tpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.tpp"

namespace Bella::CommandLineArguments {

    CommandLineArgumentsStruct parseCommandLineArguments(int argc, char* argv[]) {
        using CacheTypeEnum = Hydra::Cache::CacheTypeEnum;
        using SubsumptionTypeEnum = Hydra::Formula::Representation::Contagious::SubsumptionTypeEnum;
        using VariableSubsumptionWithMappingTypeEnum = Hydra::Formula::Representation::Contagious::VariableSubsumptionWithMappingTypeEnum;

        CommandLineArgumentsStruct commandLineArgumentsStruct;
        commandLineArgumentsStruct.compilerConfiguration = Hydra::CompilerConfiguration();
        commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration();

        // Arguments
        ArgumentsType arguments(argv, argv + argc);

        // Help
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, HELP_ARGUMENT)) {
            // program -h
            if (argc > 2)
                Hydra::Other::printWarningAboutIgnoringRemainingArgumentsExceptOne(HELP_ARGUMENT);

            commandLineArgumentsStruct.exit = true;

            printHelp();

            return commandLineArgumentsStruct;
        }

        // Version
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, VERSION_ARGUMENT)) {
            // program -v
            if (argc > 2)
                Hydra::Other::printWarningAboutIgnoringRemainingArgumentsExceptOne(VERSION_ARGUMENT);

            commandLineArgumentsStruct.exit = true;

            std::cout << "Bella (";
            Hydra::Other::Version::printHydraVersion(std::cout);
            std::cout << ")" << std::endl;

            return commandLineArgumentsStruct;
        }

        // program < -w | -pw | -nw | -b | -pb | -nb | -kb | -d | -sd > < -ph | -ka | -cd > -i input_file
        if (argc < 5)
            throw Hydra::Exception::Other::Parser::CommandLineArguments::InvalidNumberOfArgumentsException();

        // Input
        commandLineArgumentsStruct.inputFilePath = Hydra::Other::Parser::CommandLineArguments::getArgumentValue(arguments, INPUT_ARGUMENT, true);

        // Circuit type
        commandLineArgumentsStruct.compilerConfiguration.circuitType = getCircuitType(arguments);

        // Decision heuristic
        commandLineArgumentsStruct.compilerConfiguration.decisionHeuristicType = getDecisionHeuristicType(arguments);

        // Partitioning hypergraph type
        commandLineArgumentsStruct.compilerConfiguration.partitioningHypergraphType = getPartitioningHypergraphType(arguments);

        // Component caching
        commandLineArgumentsStruct.compilerConfiguration.cachingSchemeVariantComponentCachingType = getComponentCachingSchemeType(arguments);
        commandLineArgumentsStruct.compilerConfiguration.cacheCleaningStrategyComponentCachingType = getComponentCacheCleaningStrategyType(arguments);

        switch (commandLineArgumentsStruct.compilerConfiguration.cachingSchemeVariantComponentCachingType) {
            // None
            case Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::NONE:
                commandLineArgumentsStruct.compilerConfiguration.cachingSchemeComponentCachingType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::NONE;
                break;
            // Standard
            case Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::STANDARD:
                commandLineArgumentsStruct.compilerConfiguration.cachingSchemeComponentCachingType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::STANDARD;
                break;
            // Hybrid
            case Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::HYBRID:
                commandLineArgumentsStruct.compilerConfiguration.cachingSchemeComponentCachingType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::HYBRID;
                break;
            // Basic
            case Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::BASIC:
                commandLineArgumentsStruct.compilerConfiguration.cachingSchemeComponentCachingType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::BASIC;

                commandLineArgumentsStruct.compilerConfiguration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = true;
                commandLineArgumentsStruct.compilerConfiguration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = Hydra::Cache::CachingScheme::OmitClauseTypeEnum::NONE;
                break;
            // I
            case Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::I:
                commandLineArgumentsStruct.compilerConfiguration.cachingSchemeComponentCachingType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::BASIC;

                commandLineArgumentsStruct.compilerConfiguration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = true;
                commandLineArgumentsStruct.compilerConfiguration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = Hydra::Cache::CachingScheme::OmitClauseTypeEnum::UNTOUCHED;
                break;
            // Cara
            case Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::CARA:
                commandLineArgumentsStruct.compilerConfiguration.cachingSchemeComponentCachingType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::CARA;

                Hydra::Other::Parser::CommandLineArguments::getNumberOfSampleMomentsAndSetInCaraCachingSchemeConfiguration(arguments, CARA_COMPONENT_CACHING_SCHEME_ARGUMENT,
                                                                                                                           commandLineArgumentsStruct.compilerConfiguration.caraCachingSchemeComponentCachingConfiguration,
                                                                                                                           CacheTypeEnum::COMPONENT, false);

                // A variable to literal mapping
                if (Hydra::Other::containInSet(Hydra::Circuit::caraCachingSchemeVariableToLiteralMappingCircuitTypeSet, commandLineArgumentsStruct.compilerConfiguration.circuitType)) {
                    assert(!Hydra::Other::containInSet(Hydra::Circuit::caraCachingSchemeVariableToVariableMappingCircuitTypeSet, commandLineArgumentsStruct.compilerConfiguration.circuitType));

                    commandLineArgumentsStruct.compilerConfiguration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
                }
                // A variable to variable mapping
                else {
                    assert(Hydra::Other::containInSet(Hydra::Circuit::caraCachingSchemeVariableToVariableMappingCircuitTypeSet, commandLineArgumentsStruct.compilerConfiguration.circuitType));

                    commandLineArgumentsStruct.compilerConfiguration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
                }
                break;
            default:
                throw Hydra::Exception::NotImplementedException(Hydra::Cache::CachingScheme::cachingSchemeVariantTypeEnumToString(commandLineArgumentsStruct.compilerConfiguration.cachingSchemeVariantComponentCachingType),
                                                                "Hydra::Other::parseCommandLineArguments");
        }

        // Hypergraph cut caching
        commandLineArgumentsStruct.compilerConfiguration.cachingSchemeHypergraphCutCachingType = getHypergraphCutCachingSchemeType(arguments);
        commandLineArgumentsStruct.compilerConfiguration.cacheCleaningStrategyHypergraphCutCachingType = getHypergraphCutCacheCleaningStrategyType(arguments);

        // Cara caching scheme
        if (commandLineArgumentsStruct.compilerConfiguration.cachingSchemeHypergraphCutCachingType == Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::CARA)
            Hydra::Other::Parser::CommandLineArguments::getNumberOfSampleMomentsAndSetInCaraCachingSchemeConfiguration(arguments, CARA_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT,
                                                                                                                       commandLineArgumentsStruct.compilerConfiguration.caraCachingSchemeHypergraphCutCachingConfiguration,
                                                                                                                       CacheTypeEnum::HYPERGRAPH_CUT, false);

        // Others
        commandLineArgumentsStruct.compilerConfiguration.vertexWeightType = getHypergraphNodeWeightType(arguments);
        commandLineArgumentsStruct.compilerConfiguration.recomputingHypergraphCutType = getRecomputingHypergraphCutType(arguments);

        // Metacentrum
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, METACENTRUM_ARGUMENT)) {
            // program -m < -w | -pw | -nw | -b | -pb | -nb | -kb | -d | -sd > < -ph | -ka | -cd > [-e] -i input_file -s statistics_file -t positive_integer
            if (argc < 10)
                throw Hydra::Exception::Other::Parser::CommandLineArguments::InvalidNumberOfArgumentsException();

            commandLineArgumentsStruct.numberOfModels = false;
            commandLineArgumentsStruct.clausalEntailmentCheck = false;

            // Timeout
            commandLineArgumentsStruct.timeout = getTimeout(arguments, true);

            // Output
            commandLineArgumentsStruct.outputFilePath = "";

            // Statistics
            commandLineArgumentsStruct.statisticsAddLabels = false;
            commandLineArgumentsStruct.statisticsFilePath = Hydra::Other::Parser::CommandLineArguments::getArgumentValue(arguments, STATISTICS_ARGUMENT, true);
        }
        // Standard usage
        else {
            commandLineArgumentsStruct.clausalEntailmentCheck = true;

            commandLineArgumentsStruct.numberOfModels = Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, COUNT_ARGUMENT);

            // Timeout
            commandLineArgumentsStruct.timeout = getTimeout(arguments, false);

            // Output
            commandLineArgumentsStruct.outputFilePath = Hydra::Other::Parser::CommandLineArguments::getArgumentValue(arguments, OUTPUT_ARGUMENT, false);

            // Statistics
            commandLineArgumentsStruct.statisticsAddLabels = Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, READABLE_STATISTICS_ARGUMENT);
            commandLineArgumentsStruct.statisticsFilePath = Hydra::Other::Parser::CommandLineArguments::getArgumentValue(arguments, STATISTICS_ARGUMENT, false);
        }

        /**
         * Contagious formula representation configuration
         */
        commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;
        commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;
        // Recognition of Krom-C
        if (Hydra::Other::containInSet(Hydra::Circuit::kromCLeavesCircuitTypeSet, commandLineArgumentsStruct.compilerConfiguration.circuitType))
            commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration.recognitionTypeStruct.kromC = true;
        // Recognition of Horn-C
        if (Hydra::Other::containInSet(Hydra::Circuit::hornCLeavesCircuitTypeSet, commandLineArgumentsStruct.compilerConfiguration.circuitType))
            commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration.recognitionTypeStruct.hornC = true;
        // Recognition of anti-Horn-C
        if (Hydra::Other::containInSet(Hydra::Circuit::antiHornCLeavesCircuitTypeSet, commandLineArgumentsStruct.compilerConfiguration.circuitType))
            commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration.recognitionTypeStruct.antiHornC = true;

        /**
         * Compiler configuration
         */
        // Partitioning hypergraph
        commandLineArgumentsStruct.compilerConfiguration.ignoreMultiOccurrentIgnoredVariables = true;
        commandLineArgumentsStruct.compilerConfiguration.caraPartitioningHypergraphConfiguration.seed = -1;
        commandLineArgumentsStruct.compilerConfiguration.patohPartitioningHypergraphConfiguration.seedPatohLibrary = -1;
        commandLineArgumentsStruct.compilerConfiguration.kahyparPartitioningHypergraphConfiguration.seedKahyparLibrary = -1;
        commandLineArgumentsStruct.compilerConfiguration.implicitBcpVariableOrderType = Hydra::SatSolver::ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_DESCENDING;
        commandLineArgumentsStruct.compilerConfiguration.useEquivalenceSimplificationMethod = Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, EQUIVALENCE_SIMPLIFICATION_METHOD_ARGUMENT);

        // SAT solver
        commandLineArgumentsStruct.compilerConfiguration.miniSatSolverConfiguration.vsidsScoreType = Hydra::SatSolver::MiniSat::VsidsScoreTypeEnum::D4_V2;

        // Component caching
        commandLineArgumentsStruct.compilerConfiguration.caraCacheCleaningStrategyComponentCachingConfiguration.maxByteSizeCache = Hydra::Cache::EIGHT_GIGABYTES_IN_BYTES;

        // Hypergraph cut caching
        commandLineArgumentsStruct.compilerConfiguration.basicCachingSchemeHypergraphCutCachingConfiguration.removeMultiOccurrentClauses = true;

        return commandLineArgumentsStruct;
    }

    LargeNumberType getTimeout(const ArgumentsType& arguments, bool required) {
        ArgumentValueType timeoutString = Hydra::Other::Parser::CommandLineArguments::getArgumentValue(arguments, TIMEOUT_ARGUMENT, required);

        // The argument does not exist
        if (timeoutString.empty())
            return TIMEOUT_DEFAULT;

        LargeNumberType timeout = 0;

        try {
            timeout = Hydra::Other::Parser::convertStringToPositiveNumber(timeoutString);
        }
        // Invalid char
        catch (const Hydra::Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException& e) {
            throw Exception::CommandLineArguments::TimeoutIsNotNumberException(timeoutString);
        }

        return timeout;
    }

    Hydra::Circuit::CircuitTypeEnum getCircuitType(const ArgumentsType& arguments) {
        bool exists = false;
        Hydra::Circuit::CircuitTypeEnum circuitType = Hydra::Circuit::CircuitTypeEnum::NNF;

        // d-DNNF
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, dDNNF_ARGUMENT)) {
            exists = true;
            circuitType = Hydra::Circuit::CircuitTypeEnum::d_DNNF;
        }

        // sd-DNNF
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, sdDNNF_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreCircuitTypesAreMentionedException();

            exists = true;
            circuitType = Hydra::Circuit::CircuitTypeEnum::sd_DNNF;
        }

        // wDNNF
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, wDNNF_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreCircuitTypesAreMentionedException();

            exists = true;
            circuitType = Hydra::Circuit::CircuitTypeEnum::wDNNF;
        }

        // pwDNNF
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, pwDNNF_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreCircuitTypesAreMentionedException();

            exists = true;
            circuitType = Hydra::Circuit::CircuitTypeEnum::pwDNNF;
        }

        // nwDNNF
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, nwDNNF_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreCircuitTypesAreMentionedException();

            exists = true;
            circuitType = Hydra::Circuit::CircuitTypeEnum::nwDNNF;
        }

        // Bella
        if (false && Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, Bella_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreCircuitTypesAreMentionedException();

            exists = true;
            circuitType = Hydra::Circuit::CircuitTypeEnum::Bella;
        }

        // posBella
        if (false && Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, posBella_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreCircuitTypesAreMentionedException();

            exists = true;
            circuitType = Hydra::Circuit::CircuitTypeEnum::posBella;
        }

        // negBella
        if (false && Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, negBella_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreCircuitTypesAreMentionedException();

            exists = true;
            circuitType = Hydra::Circuit::CircuitTypeEnum::negBella;
        }

        // Krom-Bella
        if (false && Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, Krom_Bella_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreCircuitTypesAreMentionedException();

            exists = true;
            circuitType = Hydra::Circuit::CircuitTypeEnum::Krom_Bella;
        }

        // No circuit type is mentioned
        if (!exists)
            throw Exception::CommandLineArguments::NoCircuitTypeIsMentionedException();

        return circuitType;
    }

    Hydra::PartitioningHypergraphTypeEnum getPartitioningHypergraphType(const ArgumentsType& arguments) {
        bool exists = false;
        Hydra::PartitioningHypergraphTypeEnum partitioningHypergraphType;

        // KaHyPar
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, KAHYPAR_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT)) {
            exists = true;
            partitioningHypergraphType = Hydra::PartitioningHypergraphTypeEnum::KAHYPAR;
        }

        // Cara
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, CARA_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MorePartitioningHypergraphTypesAreMentionedException();

            exists = true;
            partitioningHypergraphType = Hydra::PartitioningHypergraphTypeEnum::CARA;
        }

        // PaToH or hMETIS
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, PATOH_HMETIS_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MorePartitioningHypergraphTypesAreMentionedException();

            exists = true;
            partitioningHypergraphType = Hydra::PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;
        }

        // No partitioning hypergraph type is mentioned
        if (!exists)
            throw Exception::CommandLineArguments::NoPartitioningHypergraphTypeIsMentionedException();

        return partitioningHypergraphType;
    }

    Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum getDecisionHeuristicType(const ArgumentsType& arguments) {
        bool exists = false;
        Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum decisionHeuristicType;

        // Random
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, RANDOM_DECISION_HEURISTIC_ARGUMENT)) {
            exists = true;
            decisionHeuristicType = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::RANDOM;
        }

        // Dynamic largest combined sum (DLCS)
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, DLCS_DECISION_HEURISTIC_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreDecisionHeuristicsAreMentionedException();

            exists = true;
            decisionHeuristicType = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::DLCS;
        }

        // Dynamic largest individual sum (DLIS)
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, DLIS_DECISION_HEURISTIC_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreDecisionHeuristicsAreMentionedException();

            exists = true;
            decisionHeuristicType = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::DLIS;
        }

        // Exact unit propagation count (EUPC)
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, EUPC_DECISION_HEURISTIC_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreDecisionHeuristicsAreMentionedException();

            exists = true;
            decisionHeuristicType = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::EUPC;
        }

        // Approximate unit propagation count (AUPC)
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, AUPC_DECISION_HEURISTIC_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreDecisionHeuristicsAreMentionedException();

            exists = true;
            decisionHeuristicType = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::AUPC;
        }

        // Variable state independent decaying sum (VSIDS)
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, VSIDS_DECISION_HEURISTIC_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreDecisionHeuristicsAreMentionedException();

            exists = true;
            decisionHeuristicType = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::VSIDS;
        }

        // Variable state aware decaying sum (VSADS)
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, VSADS_DECISION_HEURISTIC_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreDecisionHeuristicsAreMentionedException();

            exists = true;
            decisionHeuristicType = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::VSADS;
        }

        // DLCS + DLIS as a tie-breaker (DLCS-DLIS)
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, DLCS_DLIS_DECISION_HEURISTIC_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreDecisionHeuristicsAreMentionedException();

            exists = true;
            decisionHeuristicType = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::DLCS_DLIS;
        }

        // Jeroslow-Wang (one-sided)
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, JEROSLOW_WANG_ONE_SIDED_DECISION_HEURISTIC_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreDecisionHeuristicsAreMentionedException();

            exists = true;
            decisionHeuristicType = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::JEROSLOW_WANG_ONE_SIDED;
        }

        // Jeroslow-Wang (two-sided)
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, JEROSLOW_WANG_TWO_SIDED_DECISION_HEURISTIC_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreDecisionHeuristicsAreMentionedException();

            exists = true;
            decisionHeuristicType = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::JEROSLOW_WANG_TWO_SIDED;
        }

        // Default
        if (!exists)
            decisionHeuristicType = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::VSADS;

        return decisionHeuristicType;
    }

    Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum getComponentCachingSchemeType(const ArgumentsType& arguments) {
        bool exists = false;
        Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum componentCachingSchemeVariantType;

        // None
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, NONE_COMPONENT_CACHING_SCHEME_ARGUMENT)) {
            exists = true;
            componentCachingSchemeVariantType = Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::NONE;
        }

        // Standard
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, STANDARD_COMPONENT_CACHING_SCHEME_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreComponentCachingSchemesAreMentionedException();

            exists = true;
            componentCachingSchemeVariantType = Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::STANDARD;
        }

        // Hybrid
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, HYBRID_COMPONENT_CACHING_SCHEME_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreComponentCachingSchemesAreMentionedException();

            exists = true;
            componentCachingSchemeVariantType = Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::HYBRID;
        }

        // Basic
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, BASIC_COMPONENT_CACHING_SCHEME_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreComponentCachingSchemesAreMentionedException();

            exists = true;
            componentCachingSchemeVariantType = Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::BASIC;
        }

        // I
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, I_COMPONENT_CACHING_SCHEME_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreComponentCachingSchemesAreMentionedException();

            exists = true;
            componentCachingSchemeVariantType = Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::I;
        }

        // Cara
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, CARA_COMPONENT_CACHING_SCHEME_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreComponentCachingSchemesAreMentionedException();

            exists = true;
            componentCachingSchemeVariantType = Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::CARA;
        }

        // Default
        if (!exists)
            componentCachingSchemeVariantType = Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::I;

        return componentCachingSchemeVariantType;
    }

    Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum getComponentCacheCleaningStrategyType(const ArgumentsType& arguments) {
        bool exists = false;
        Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum cacheCleaningStrategyType;

        // None
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, NONE_COMPONENT_CACHE_CLEANING_STRATEGY_ARGUMENT)) {
            exists = true;
            cacheCleaningStrategyType = Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::NONE;
        }

        // sharpSAT
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, SHARP_SAT_COMPONENT_CACHE_CLEANING_STRATEGY_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreComponentCacheCleaningStrategiesAreMentionedException();

            exists = true;
            cacheCleaningStrategyType = Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::SHARP_SAT;
        }

        // Cara
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, CARA_COMPONENT_CACHE_CLEANING_STRATEGY_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreComponentCacheCleaningStrategiesAreMentionedException();

            exists = true;
            cacheCleaningStrategyType = Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::CARA;
        }

        // Default
        if (!exists)
            cacheCleaningStrategyType = Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::CARA;

        return cacheCleaningStrategyType;
    }

    Hydra::Cache::CachingScheme::CachingSchemeTypeEnum getHypergraphCutCachingSchemeType(const ArgumentsType& arguments) {
        bool exists = false;
        Hydra::Cache::CachingScheme::CachingSchemeTypeEnum hypergraphCutCachingSchemeType;

        // None
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, NONE_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT)) {
            exists = true;
            hypergraphCutCachingSchemeType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::NONE;
        }

        // Standard
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, STANDARD_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreHypergraphCutCachingSchemesAreMentionedException();

            exists = true;
            hypergraphCutCachingSchemeType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::STANDARD;
        }

        // Hybrid
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, HYBRID_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreHypergraphCutCachingSchemesAreMentionedException();

            exists = true;
            hypergraphCutCachingSchemeType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::HYBRID;
        }

        // Basic
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, BASIC_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreHypergraphCutCachingSchemesAreMentionedException();

            exists = true;
            hypergraphCutCachingSchemeType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::BASIC;
        }

        // Cara
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, CARA_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreHypergraphCutCachingSchemesAreMentionedException();

            exists = true;
            hypergraphCutCachingSchemeType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::CARA;
        }

        // Default
        if (!exists)
            hypergraphCutCachingSchemeType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::NONE;

        return hypergraphCutCachingSchemeType;
    }

    Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum getHypergraphCutCacheCleaningStrategyType(const ArgumentsType& arguments) {
        bool exists = false;
        Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum cacheCleaningStrategyType;

        // None
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, NONE_HYPERGRAPH_CUT_CACHE_CLEANING_STRATEGY_ARGUMENT)) {
            exists = true;
            cacheCleaningStrategyType = Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::NONE;
        }

        // sharpSAT
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, SHARP_SAT_HYPERGRAPH_CUT_CACHE_CLEANING_STRATEGY_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreHypergraphCutCacheCleaningStrategiesAreMentionedException();

            exists = true;
            cacheCleaningStrategyType = Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::SHARP_SAT;
        }

        // Cara
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, CARA_HYPERGRAPH_CUT_CACHE_CLEANING_STRATEGY_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreHypergraphCutCacheCleaningStrategiesAreMentionedException();

            exists = true;
            cacheCleaningStrategyType = Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::CARA;
        }

        // Default
        if (!exists)
            cacheCleaningStrategyType = Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::NONE;

        return cacheCleaningStrategyType;
    }

    Hydra::PartitioningHypergraph::VertexWeightTypeEnum getHypergraphNodeWeightType(const ArgumentsType& arguments) {
        bool exists = false;
        Hydra::PartitioningHypergraph::VertexWeightTypeEnum vertexWeightType;

        // None
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, NONE_HYPERGRAPH_NODE_WEIGHT_ARGUMENT)) {
            exists = true;
            vertexWeightType = Hydra::PartitioningHypergraph::VertexWeightTypeEnum::NONE;
        }

        // Standard
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, STANDARD_HYPERGRAPH_NODE_WEIGHT_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreHypergraphNodeWeightTypesAreMentionedException();

            exists = true;
            vertexWeightType = Hydra::PartitioningHypergraph::VertexWeightTypeEnum::STANDARD;
        }

        // Clause length
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, CLAUSE_LENGTH_HYPERGRAPH_NODE_WEIGHT_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreHypergraphNodeWeightTypesAreMentionedException();

            exists = true;
            vertexWeightType = Hydra::PartitioningHypergraph::VertexWeightTypeEnum::CLAUSE_LENGTH;
        }

        // Default
        if (!exists)
            vertexWeightType = Hydra::PartitioningHypergraph::VertexWeightTypeEnum::CLAUSE_LENGTH;

        return vertexWeightType;
    }

    Hydra::RecomputingHypergraphCutTypeEnum getRecomputingHypergraphCutType(const ArgumentsType& arguments) {
        bool exists = false;
        Hydra::RecomputingHypergraphCutTypeEnum recomputingHypergraphCutType;

        // Always
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, ALWAYS_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT)) {
            exists = true;
            recomputingHypergraphCutType = Hydra::RecomputingHypergraphCutTypeEnum::ALWAYS;
        }

        // Immense unit propagation
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, IMMENSE_UNIT_PROPAGATION_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreRecomputingHypergraphCutTypesAreMentionedException();

            exists = true;
            recomputingHypergraphCutType = Hydra::RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION;
        }

        // Formula split
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, FORMULA_SPLIT_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreRecomputingHypergraphCutTypesAreMentionedException();

            exists = true;
            recomputingHypergraphCutType = Hydra::RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_FORMULA_IS_SPLIT;
        }

        // Empty hypergraph cut
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, EMPTY_HYPERGRAPH_CUT_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreRecomputingHypergraphCutTypesAreMentionedException();

            exists = true;
            recomputingHypergraphCutType = Hydra::RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY;
        }

        // Immense unit propagation or formula split
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, IMMENSE_UNIT_PROPAGATION_OR_FORMULA_SPLIT_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MoreRecomputingHypergraphCutTypesAreMentionedException();

            exists = true;
            recomputingHypergraphCutType = Hydra::RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION_OR_WHEN_CURRENT_FORMULA_IS_SPLIT;
        }

        // Default
        if (!exists)
            recomputingHypergraphCutType = Hydra::RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION;

        return recomputingHypergraphCutType;
    }

    void printHelp() {
        const std::string description = "A knowledge compiler for " +
                                        // Weak and variants
                                        Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::wDNNF) + ", " +
                                        Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::pwDNNF) + ", " +
                                        Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::nwDNNF) + ", " +
                                        // Bella
                                        // Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::Bella) + ", " +
                                        // Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::posBella) + ", " +
                                        // Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::negBella) + ", " +
                                        // Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::Krom_Bella) + ", " +
                                        // Standard
                                        Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::d_DNNF) + " and " +
                                        Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::sd_DNNF) + " circuits.";

        // Title
        Hydra::Other::printTitle(std::cout, "Bella", (int)description.size(), ' ');

        // Description
        std::cout << description << std::endl;
        std::cout << std::endl
                  << std::endl;

        // Command
        std::cout << "./Bella " << VERSION_ARGUMENT << std::endl;
        std::cout << "./Bella";
        // Circuit types
        std::cout << " < "
                  // Weak and variants
                  << wDNNF_ARGUMENT << " | " << pwDNNF_ARGUMENT << " | " << nwDNNF_ARGUMENT << " | "
                  // Bella
                  // << Bella_ARGUMENT << " | " << posBella_ARGUMENT << " | " << negBella_ARGUMENT << " | " << Krom_Bella_ARGUMENT << " | "
                  // Standard
                  << dDNNF_ARGUMENT << " | " << sdDNNF_ARGUMENT
                  << " >";
        // Partitioning hypergraph types
        std::cout << " < " << PATOH_HMETIS_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT << " | " << KAHYPAR_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT << " | " << CARA_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT << " >";
        std::cout << " " << INPUT_ARGUMENT << " input_file";
        std::cout << std::endl;

        // Others and files
        std::cout << "       ";
        std::cout << " [" << COUNT_ARGUMENT << "]";
        std::cout << " [" << EQUIVALENCE_SIMPLIFICATION_METHOD_ARGUMENT << "]";
        std::cout << " [" << READABLE_STATISTICS_ARGUMENT << "]";

        std::cout << " [ " << STATISTICS_ARGUMENT << " statistics_file ]";
        std::cout << " [ " << OUTPUT_ARGUMENT << " output_file ]";
        std::cout << " [ " << TIMEOUT_ARGUMENT << " positive_integer (default: " << std::to_string(TIMEOUT_DEFAULT) << ") ]";
        std::cout << std::endl;

        // Decision heuristics
        std::cout << "       ";
        std::cout << " [ " << RANDOM_DECISION_HEURISTIC_ARGUMENT << " | " << DLCS_DECISION_HEURISTIC_ARGUMENT << " | " << DLIS_DECISION_HEURISTIC_ARGUMENT << " | " << DLCS_DLIS_DECISION_HEURISTIC_ARGUMENT << " | " << VSIDS_DECISION_HEURISTIC_ARGUMENT << " | " << VSADS_DECISION_HEURISTIC_ARGUMENT << " | " << JEROSLOW_WANG_ONE_SIDED_DECISION_HEURISTIC_ARGUMENT << " | " << JEROSLOW_WANG_TWO_SIDED_DECISION_HEURISTIC_ARGUMENT << " | " << EUPC_DECISION_HEURISTIC_ARGUMENT << " | " << AUPC_DECISION_HEURISTIC_ARGUMENT << " ]";
        std::cout << std::endl;

        // Component caching schemes and cache cleaning strategies
        std::cout << "       ";
        std::cout << " [ " << NONE_COMPONENT_CACHING_SCHEME_ARGUMENT << " | " << STANDARD_COMPONENT_CACHING_SCHEME_ARGUMENT << " | " << HYBRID_COMPONENT_CACHING_SCHEME_ARGUMENT << " | " << BASIC_COMPONENT_CACHING_SCHEME_ARGUMENT << " | " << I_COMPONENT_CACHING_SCHEME_ARGUMENT << " | "
                  << CARA_COMPONENT_CACHING_SCHEME_ARGUMENT << " [integer] (min: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MINIMUM) << ", max: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MAXIMUM) << ", default: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_DEFAULT) << ") ]";
        std::cout << " [ " << NONE_COMPONENT_CACHE_CLEANING_STRATEGY_ARGUMENT << " | " << SHARP_SAT_COMPONENT_CACHE_CLEANING_STRATEGY_ARGUMENT << " | " << CARA_COMPONENT_CACHE_CLEANING_STRATEGY_ARGUMENT << " ]";
        std::cout << std::endl;

        // Hypergraph cut caching schemes and cache cleaning strategies
        std::cout << "       ";
        std::cout << " [ " << NONE_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT << " | " << STANDARD_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT << " | " << HYBRID_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT << " | " << BASIC_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT << " | "
                  << CARA_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT << " [integer] (min: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MINIMUM) << ", max: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MAXIMUM) << ", default: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_DEFAULT) << ") ]";
        std::cout << " [ " << NONE_HYPERGRAPH_CUT_CACHE_CLEANING_STRATEGY_ARGUMENT << " | " << SHARP_SAT_HYPERGRAPH_CUT_CACHE_CLEANING_STRATEGY_ARGUMENT << " | " << CARA_HYPERGRAPH_CUT_CACHE_CLEANING_STRATEGY_ARGUMENT << " ]";
        std::cout << std::endl;

        std::cout << "       ";
        // Hypergraph node weight types
        std::cout << " [ " << NONE_HYPERGRAPH_NODE_WEIGHT_ARGUMENT << " | " << STANDARD_HYPERGRAPH_NODE_WEIGHT_ARGUMENT << " | " << CLAUSE_LENGTH_HYPERGRAPH_NODE_WEIGHT_ARGUMENT << " ]";
        // Recomputing hypergraph cut types
        std::cout << " [ " << ALWAYS_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT << " | " << IMMENSE_UNIT_PROPAGATION_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT << " | " << FORMULA_SPLIT_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT << " | " << EMPTY_HYPERGRAPH_CUT_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT << " | " << IMMENSE_UNIT_PROPAGATION_OR_FORMULA_SPLIT_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT << " ]";
        std::cout << std::endl;
        std::cout << std::endl;

        // Arguments
        std::cout << "Circuit types:" << std::endl;
        // Weak and variants
        std::cout << "\t" << wDNNF_ARGUMENT << " — " + Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::wDNNF, true) << std::endl;
        std::cout << "\t" << pwDNNF_ARGUMENT << " — " + Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::pwDNNF, true) << std::endl;
        std::cout << "\t" << nwDNNF_ARGUMENT << " — " + Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::nwDNNF, true) << std::endl;
        std::cout << std::endl;
        // Bella
        // std::cout << "\t" << Bella_ARGUMENT << " — " + Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::Bella, true) << std::endl;
        // std::cout << "\t" << posBella_ARGUMENT << " — " + Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::posBella, true) << std::endl;
        // std::cout << "\t" << negBella_ARGUMENT << " — " + Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::negBella, true) << std::endl;
        // std::cout << "\t" << Krom_Bella_ARGUMENT << " — " + Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::Krom_Bella, true) << std::endl;
        // std::cout << std::endl;
        // Standard
        std::cout << "\t" << dDNNF_ARGUMENT << " — " + Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::d_DNNF, true) << std::endl;
        std::cout << "\t" << sdDNNF_ARGUMENT << " — " + Hydra::Circuit::circuitTypeEnumToString(Hydra::Circuit::CircuitTypeEnum::sd_DNNF, true) << std::endl;
        std::cout << std::endl;

        std::cout << "Partitioning hypergraph types:" << std::endl;
        std::cout << "\t" << PATOH_HMETIS_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT << " — PaToH (Linux, macOS), hMETIS (Windows) (recommended)" << std::endl;
        std::cout << "\t" << KAHYPAR_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT << " — KaHyPar (Linux, macOS, Windows)" << std::endl;
        std::cout << "\t" << CARA_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT << " — Cara (Linux, macOS)" << std::endl;
        std::cout << std::endl;

        std::cout << "Files:" << std::endl;
        std::cout << "\t" << INPUT_ARGUMENT << " — specifies the CNF file name" << std::endl;
        std::cout << "\t" << STATISTICS_ARGUMENT << " — specifies the file name where the statistics will be saved" << std::endl;
        std::cout << "\t" << OUTPUT_ARGUMENT << " — specifies the file name where the compiled circuit will be saved" << std::endl;
        std::cout << std::endl;

        std::cout << "Decision heuristics:" << std::endl;
        std::cout << "\t" << RANDOM_DECISION_HEURISTIC_ARGUMENT << " — " << Hydra::DecisionHeuristic::decisionHeuristicTypeEnumToString(Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::RANDOM) << std::endl;
        std::cout << "\t" << DLCS_DECISION_HEURISTIC_ARGUMENT << " — " << Hydra::DecisionHeuristic::decisionHeuristicTypeEnumToString(Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::DLCS) << std::endl;
        std::cout << "\t" << DLIS_DECISION_HEURISTIC_ARGUMENT << " — " << Hydra::DecisionHeuristic::decisionHeuristicTypeEnumToString(Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::DLIS) << std::endl;
        std::cout << "\t" << DLCS_DLIS_DECISION_HEURISTIC_ARGUMENT << " — " << Hydra::DecisionHeuristic::decisionHeuristicTypeEnumToString(Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::DLCS_DLIS) << std::endl;
        std::cout << "\t" << VSIDS_DECISION_HEURISTIC_ARGUMENT << " — " << Hydra::DecisionHeuristic::decisionHeuristicTypeEnumToString(Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::VSIDS) << std::endl;
        std::cout << "\t" << VSADS_DECISION_HEURISTIC_ARGUMENT << " — " << Hydra::DecisionHeuristic::decisionHeuristicTypeEnumToString(Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::VSADS) << " (default)" << std::endl;
        std::cout << "\t" << JEROSLOW_WANG_ONE_SIDED_DECISION_HEURISTIC_ARGUMENT << " — " << Hydra::DecisionHeuristic::decisionHeuristicTypeEnumToString(Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::JEROSLOW_WANG_ONE_SIDED) << std::endl;
        std::cout << "\t" << JEROSLOW_WANG_TWO_SIDED_DECISION_HEURISTIC_ARGUMENT << " — " << Hydra::DecisionHeuristic::decisionHeuristicTypeEnumToString(Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::JEROSLOW_WANG_TWO_SIDED) << std::endl;
        std::cout << "\t" << EUPC_DECISION_HEURISTIC_ARGUMENT << " — " << Hydra::DecisionHeuristic::decisionHeuristicTypeEnumToString(Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::EUPC) << std::endl;
        std::cout << "\t" << AUPC_DECISION_HEURISTIC_ARGUMENT << " — " << Hydra::DecisionHeuristic::decisionHeuristicTypeEnumToString(Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::AUPC) << std::endl;
        std::cout << std::endl;

        std::cout << "Component caching schemes:" << std::endl;
        std::cout << "\t" << NONE_COMPONENT_CACHING_SCHEME_ARGUMENT << " — " << Hydra::Cache::CachingScheme::cachingSchemeVariantTypeEnumToString(Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::NONE) << std::endl;
        std::cout << "\t" << STANDARD_COMPONENT_CACHING_SCHEME_ARGUMENT << " — " << Hydra::Cache::CachingScheme::cachingSchemeVariantTypeEnumToString(Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::STANDARD) << std::endl;
        std::cout << "\t" << HYBRID_COMPONENT_CACHING_SCHEME_ARGUMENT << " — " << Hydra::Cache::CachingScheme::cachingSchemeVariantTypeEnumToString(Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::HYBRID) << std::endl;
        std::cout << "\t" << BASIC_COMPONENT_CACHING_SCHEME_ARGUMENT << " — " << Hydra::Cache::CachingScheme::cachingSchemeVariantTypeEnumToString(Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::BASIC) << std::endl;
        std::cout << "\t" << I_COMPONENT_CACHING_SCHEME_ARGUMENT << " — " << Hydra::Cache::CachingScheme::cachingSchemeVariantTypeEnumToString(Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::I) << " (default)" << std::endl;
        std::cout << "\t" << CARA_COMPONENT_CACHING_SCHEME_ARGUMENT << " — " << Hydra::Cache::CachingScheme::cachingSchemeVariantTypeEnumToString(Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::CARA) << ": optionally sets the number of sample moments (min: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MINIMUM) << ", max: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MAXIMUM) << ", default: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_DEFAULT) << ")" << std::endl;
        std::cout << std::endl;

        std::cout << "Component cache cleaning strategies:" << std::endl;
        std::cout << "\t" << NONE_COMPONENT_CACHE_CLEANING_STRATEGY_ARGUMENT << " — " << Hydra::Cache::CacheCleaningStrategy::cacheCleaningStrategyTypeEnumToString(Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::NONE) << std::endl;
        std::cout << "\t" << SHARP_SAT_COMPONENT_CACHE_CLEANING_STRATEGY_ARGUMENT << " — " << Hydra::Cache::CacheCleaningStrategy::cacheCleaningStrategyTypeEnumToString(Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::SHARP_SAT) << std::endl;
        std::cout << "\t" << CARA_COMPONENT_CACHE_CLEANING_STRATEGY_ARGUMENT << " — " << Hydra::Cache::CacheCleaningStrategy::cacheCleaningStrategyTypeEnumToString(Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::CARA) << " (default)" << std::endl;
        std::cout << std::endl;

        std::cout << "Hypergraph cut caching schemes:" << std::endl;
        std::cout << "\t" << NONE_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT << " — " << Hydra::Cache::CachingScheme::cachingSchemeTypeEnumToString(Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::NONE) << " (default)" << std::endl;
        std::cout << "\t" << STANDARD_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT << " — " << Hydra::Cache::CachingScheme::cachingSchemeTypeEnumToString(Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::STANDARD) << std::endl;
        std::cout << "\t" << HYBRID_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT << " — " << Hydra::Cache::CachingScheme::cachingSchemeTypeEnumToString(Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::HYBRID) << std::endl;
        std::cout << "\t" << BASIC_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT << " — " << Hydra::Cache::CachingScheme::cachingSchemeTypeEnumToString(Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::BASIC) << std::endl;
        std::cout << "\t" << CARA_HYPERGRAPH_CUT_CACHING_SCHEME_ARGUMENT << " — " << Hydra::Cache::CachingScheme::cachingSchemeTypeEnumToString(Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::CARA) << ": optionally sets the number of sample moments (min: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MINIMUM) << ", max: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MAXIMUM) << ", default: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_DEFAULT) << ")" << std::endl;
        std::cout << std::endl;

        std::cout << "Hypergraph cut cache cleaning strategies:" << std::endl;
        std::cout << "\t" << NONE_HYPERGRAPH_CUT_CACHE_CLEANING_STRATEGY_ARGUMENT << " — " << Hydra::Cache::CacheCleaningStrategy::cacheCleaningStrategyTypeEnumToString(Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::NONE) << " (default)" << std::endl;
        std::cout << "\t" << SHARP_SAT_HYPERGRAPH_CUT_CACHE_CLEANING_STRATEGY_ARGUMENT << " — " << Hydra::Cache::CacheCleaningStrategy::cacheCleaningStrategyTypeEnumToString(Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::SHARP_SAT) << std::endl;
        std::cout << "\t" << CARA_HYPERGRAPH_CUT_CACHE_CLEANING_STRATEGY_ARGUMENT << " — " << Hydra::Cache::CacheCleaningStrategy::cacheCleaningStrategyTypeEnumToString(Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::CARA) << std::endl;
        std::cout << std::endl;

        std::cout << "Hypergraph node weight types:" << std::endl;
        std::cout << "\t" << NONE_HYPERGRAPH_NODE_WEIGHT_ARGUMENT << " — " << Hydra::PartitioningHypergraph::vertexWeightTypeEnumToString(Hydra::PartitioningHypergraph::VertexWeightTypeEnum::NONE) << std::endl;
        std::cout << "\t" << STANDARD_HYPERGRAPH_NODE_WEIGHT_ARGUMENT << " — " << Hydra::PartitioningHypergraph::vertexWeightTypeEnumToString(Hydra::PartitioningHypergraph::VertexWeightTypeEnum::STANDARD) << std::endl;
        std::cout << "\t" << CLAUSE_LENGTH_HYPERGRAPH_NODE_WEIGHT_ARGUMENT << " — " << Hydra::PartitioningHypergraph::vertexWeightTypeEnumToString(Hydra::PartitioningHypergraph::VertexWeightTypeEnum::CLAUSE_LENGTH) << " (default)" << std::endl;
        std::cout << std::endl;

        std::cout << "Recomputing hypergraph cut types:" << std::endl;
        std::cout << "\t" << ALWAYS_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT << " — " << recomputingHypergraphCutTypeEnumToString(Hydra::RecomputingHypergraphCutTypeEnum::ALWAYS) << std::endl;
        std::cout << "\t" << IMMENSE_UNIT_PROPAGATION_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT << " — " << recomputingHypergraphCutTypeEnumToString(Hydra::RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION) << " (default)" << std::endl;
        std::cout << "\t" << FORMULA_SPLIT_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT << " — " << recomputingHypergraphCutTypeEnumToString(Hydra::RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_FORMULA_IS_SPLIT) << std::endl;
        std::cout << "\t" << EMPTY_HYPERGRAPH_CUT_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT << " — " << recomputingHypergraphCutTypeEnumToString(Hydra::RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY) << std::endl;
        std::cout << "\t" << IMMENSE_UNIT_PROPAGATION_OR_FORMULA_SPLIT_RECOMPUTING_HYPERGRAPH_CUT_ARGUMENT << " — " << recomputingHypergraphCutTypeEnumToString(Hydra::RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION_OR_WHEN_CURRENT_FORMULA_IS_SPLIT) << std::endl;
        std::cout << std::endl;

        std::cout << COUNT_ARGUMENT << " — counts the models" << std::endl;
        std::cout << VERSION_ARGUMENT << " — print version information" << std::endl;
        std::cout << EQUIVALENCE_SIMPLIFICATION_METHOD_ARGUMENT << " — uses the equivalence simplification method (highly recommended)" << std::endl;
        std::cout << TIMEOUT_ARGUMENT << " — sets the compilation timeout (default: 86400 s)" << std::endl;
        std::cout << READABLE_STATISTICS_ARGUMENT << " — the statistics file is in a form readable by a human" << std::endl;
        std::cout << std::endl;
    }
}   // namespace Bella::CommandLineArguments
