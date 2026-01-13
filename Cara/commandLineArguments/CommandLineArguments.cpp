#include "./CommandLineArguments.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

#include "Hydra/other/Other.hpp"
#include "Hydra/other/parser/CommandLineArgumentsParser.hpp"

#include "Cara/commandLineArguments/exceptions/CommandLineArgumentsException.hpp"
#include "Hydra/other/parser/exceptions/CommandLineArgumentsParserException.hpp"

#include "Hydra/cache/cachingScheme/enums/PreprocessingTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"
#include "Hydra/satSolver/minisat/enums/VsidsScoreTypeEnum.hpp"

#include "Hydra/compiler/Compiler.tpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.tpp"

namespace Cara::CommandLineArguments {

    CommandLineArgumentsStruct parseCommandLineArguments(int argc, char* argv[]) {
        CommandLineArgumentsStruct commandLineArgumentsStruct;
        commandLineArgumentsStruct.compilerConfiguration = Hydra::CompilerConfiguration();
        commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration();

        // Arguments
        ArgumentsType arguments(argv, argv + argc);

        // Help
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, HELP_ARGUMENT)) {
            // program -h
            if (argc > 2) {
                std::cerr << "WARNING: only the argument \"-h\" is considered; the remaining arguments are ignored!" << std::endl;
                std::cerr << std::endl;
            }

            commandLineArgumentsStruct.help = true;

            printHelp();

            return commandLineArgumentsStruct;
        }

        // program < -ph | -ka | -cd | -cs > -i input_file -nsm integer [ -n | -ndc | -nsc ] [ -mmbf positive_integer ]
        if (argc < 6 || argc > 9)
            throw Hydra::Exception::Other::Parser::CommandLineArguments::InvalidNumberOfArgumentsException();

        // Initialize the configurations
        initializeConfigurations(commandLineArgumentsStruct);

        // Input
        commandLineArgumentsStruct.inputFilePath = Hydra::Other::Parser::CommandLineArguments::getArgumentValue(arguments, INPUT_ARGUMENT, true);

        // Partitioning hypergraph type
        commandLineArgumentsStruct.compilerConfiguration.partitioningHypergraphType = getPartitioningHypergraphType(arguments);

        // Cara vs Cara (speed)
        switch (commandLineArgumentsStruct.compilerConfiguration.partitioningHypergraphType) {
            // Cara - KaHyPar + PaToH (DEFAULT) + PaToH (SPEED)
            case Hydra::PartitioningHypergraphTypeEnum::CARA:
                commandLineArgumentsStruct.compilerConfiguration.caraPartitioningHypergraphConfiguration.imbalanceFactorKahyparLibrary = 0.1;
                commandLineArgumentsStruct.compilerConfiguration.caraPartitioningHypergraphConfiguration.lowNumberOfVariablesSuggestByProblemTypePatohLibrary = PATOH_SUGPARAM_SPEED;
                commandLineArgumentsStruct.compilerConfiguration.caraPartitioningHypergraphConfiguration.highNumberOfVariablesSuggestByProblemTypePatohLibrary = PATOH_SUGPARAM_DEFAULT;
                break;
            // Cara - KaHyPar + PaToH (SPEED)
            case Hydra::PartitioningHypergraphTypeEnum::CARA_SPEED:
                commandLineArgumentsStruct.compilerConfiguration.caraPartitioningHypergraphConfiguration.imbalanceFactorKahyparLibrary = 0.05;
                commandLineArgumentsStruct.compilerConfiguration.caraPartitioningHypergraphConfiguration.lowNumberOfVariablesSuggestByProblemTypePatohLibrary = PATOH_SUGPARAM_SPEED;
                commandLineArgumentsStruct.compilerConfiguration.caraPartitioningHypergraphConfiguration.highNumberOfVariablesSuggestByProblemTypePatohLibrary = PATOH_SUGPARAM_SPEED;
                break;
            default:
                break;
        }

        // Preprocessing type
        commandLineArgumentsStruct.compilerConfiguration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = getPreprocessingType(arguments);

        // Cara caching scheme - number of sample moments
        Hydra::Other::Parser::CommandLineArguments::getNumberOfSampleMomentsAndSetInCaraCachingSchemeConfiguration(arguments, NUMBER_OF_SAMPLE_MOMENTS_ARGUMENT,
                                                                                                                   commandLineArgumentsStruct.compilerConfiguration.caraCachingSchemeComponentCachingConfiguration,
                                                                                                                   Hydra::Cache::CacheTypeEnum::COMPONENT, true);

        // Must-multiply-by factor
        ArgumentValueType mustMultiplyByFactorString = Hydra::Other::Parser::CommandLineArguments::getArgumentValue(arguments, MUST_MULTIPLY_BY_FACTOR_ARGUMENT, false);
        if (!mustMultiplyByFactorString.empty()) {
            try {
                commandLineArgumentsStruct.mustMultiplyByFactor = MpzIntType(mustMultiplyByFactorString);
            }
            catch (const std::exception& e) {
                throw Exception::CommandLineArguments::MustMultiplyByFactorIsInvalidException(mustMultiplyByFactorString);
            }

            // Must-multiply-by factor is 0
            if (commandLineArgumentsStruct.mustMultiplyByFactor == 0)
                throw Exception::CommandLineArguments::MustMultiplyByFactorIsZeroException();
        }

        return commandLineArgumentsStruct;
    }

    void initializeConfigurations(CommandLineArgumentsStruct& commandLineArgumentsStruct) {
        /**
         * Contagious formula representation configuration
         */
        // Subsumption
        commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration.subsumptionType = Hydra::Formula::Representation::Contagious::SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;
        commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = Hydra::Formula::Representation::Contagious::VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        // Recognitions
        commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration.recognitionTypeStruct.kromC = false;       // Krom-C
        commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration.recognitionTypeStruct.hornC = false;       // Horn-C
        commandLineArgumentsStruct.contagiousFormulaRepresentationConfiguration.recognitionTypeStruct.antiHornC = false;   // anti-Horn-C

        /**
         * Compiler configuration
         */
        // Circuit type
        commandLineArgumentsStruct.compilerConfiguration.circuitType = Hydra::Circuit::CircuitTypeEnum::sd_DNNF;

        // Decision heuristic
        commandLineArgumentsStruct.compilerConfiguration.decisionHeuristicType = Hydra::DecisionHeuristic::DecisionHeuristicTypeEnum::VSADS;

        // Component caching
        commandLineArgumentsStruct.compilerConfiguration.cachingSchemeComponentCachingType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::CARA;
        commandLineArgumentsStruct.compilerConfiguration.cachingSchemeVariantComponentCachingType = Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::CARA;
        commandLineArgumentsStruct.compilerConfiguration.cacheCleaningStrategyComponentCachingType = Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::CARA;

        commandLineArgumentsStruct.compilerConfiguration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        commandLineArgumentsStruct.compilerConfiguration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = Hydra::Cache::CachingScheme::PreprocessingTypeEnum::NONE;

        commandLineArgumentsStruct.compilerConfiguration.caraCacheCleaningStrategyComponentCachingConfiguration.maxByteSizeCache = Hydra::Cache::SIXTEEN_GIGABYTES_IN_BYTES;

        // Hypergraph cut caching
        commandLineArgumentsStruct.compilerConfiguration.cachingSchemeHypergraphCutCachingType = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::NONE;
        commandLineArgumentsStruct.compilerConfiguration.cacheCleaningStrategyHypergraphCutCachingType = Hydra::Cache::CacheCleaningStrategy::CacheCleaningStrategyTypeEnum::NONE;

        // Partitioning hypergraph
        commandLineArgumentsStruct.compilerConfiguration.useEquivalenceSimplificationMethod = true;
        commandLineArgumentsStruct.compilerConfiguration.ignoreMultiOccurrentIgnoredVariables = true;
        commandLineArgumentsStruct.compilerConfiguration.caraPartitioningHypergraphConfiguration.seed = -1;
        commandLineArgumentsStruct.compilerConfiguration.patohPartitioningHypergraphConfiguration.seedPatohLibrary = -1;
        commandLineArgumentsStruct.compilerConfiguration.kahyparPartitioningHypergraphConfiguration.seedKahyparLibrary = -1;
        commandLineArgumentsStruct.compilerConfiguration.implicitBcpVariableOrderType = Hydra::SatSolver::ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_DESCENDING;

        // SAT solver
        commandLineArgumentsStruct.compilerConfiguration.satSolverType = Hydra::SatSolver::SatSolverTypeEnum::MINISAT;
        commandLineArgumentsStruct.compilerConfiguration.miniSatSolverConfiguration.vsidsScoreType = Hydra::SatSolver::MiniSat::VsidsScoreTypeEnum::D4_V2;

        // Others
        commandLineArgumentsStruct.compilerConfiguration.vertexWeightType = Hydra::PartitioningHypergraph::VertexWeightTypeEnum::STANDARD;
        commandLineArgumentsStruct.compilerConfiguration.recomputingHypergraphCutType = Hydra::RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY;
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

        // Cara (speed)
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, CARA_SPEED_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MorePartitioningHypergraphTypesAreMentionedException();

            exists = true;
            partitioningHypergraphType = Hydra::PartitioningHypergraphTypeEnum::CARA_SPEED;
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

    Hydra::Cache::CachingScheme::PreprocessingTypeEnum getPreprocessingType(const ArgumentsType& arguments) {
        using PreprocessingTypeEnum = Hydra::Cache::CachingScheme::PreprocessingTypeEnum;

        bool exists = false;
        PreprocessingTypeEnum preprocessingType;

        // None
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, NONE_PREPROCESSING_TYPE_ARGUMENT)) {
            exists = true;
            preprocessingType = PreprocessingTypeEnum::NONE;
        }

        // Not duplicate clauses
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, NOT_DUPLICATE_CLAUSES_PREPROCESSING_TYPE_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MorePreprocessingTypesAreMentionedException();

            exists = true;
            preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;
        }

        // Not subsumed clauses
        if (Hydra::Other::Parser::CommandLineArguments::argumentExists(arguments, NOT_SUBSUMED_CLAUSES_PREPROCESSING_TYPE_ARGUMENT)) {
            if (exists)
                throw Exception::CommandLineArguments::MorePreprocessingTypesAreMentionedException();

            exists = true;
            preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        }

        // No preprocessing type is mentioned
        if (!exists)
            preprocessingType = PreprocessingTypeEnum::NONE;

        return preprocessingType;
    }

    void printHelp() {
        // Title
        Hydra::Other::printTitle(std::cout, "Cara", (int)DESCRIPTION.size(), ' ');

        // Description
        std::cout << DESCRIPTION << std::endl;
        std::cout << std::endl
                  << std::endl;

        // Command
        std::cout << "./Cara";

        // Partitioning hypergraph types
        std::cout << " < " << PATOH_HMETIS_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT << " | " << KAHYPAR_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT << " | " << CARA_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT << " >";

        // Files
        std::cout << " " << INPUT_ARGUMENT << " input_file" << " ";

        // Others
        std::cout << NUMBER_OF_SAMPLE_MOMENTS_ARGUMENT << " integer (min: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MINIMUM) << ", max: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MAXIMUM) << ")";
        std::cout << " [ " << MUST_MULTIPLY_BY_FACTOR_ARGUMENT << " positive_integer (default: 1) ]";

        // Preprocessing types
        std::cout << " [ " << NONE_PREPROCESSING_TYPE_ARGUMENT << " | " << NOT_DUPLICATE_CLAUSES_PREPROCESSING_TYPE_ARGUMENT << " | " << NOT_SUBSUMED_CLAUSES_PREPROCESSING_TYPE_ARGUMENT << " ]";
        std::cout << std::endl;
        std::cout << std::endl;

        // Arguments
        std::cout << "Partitioning hypergraph types:" << std::endl;
        std::cout << "\t" << PATOH_HMETIS_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT << " — PaToH (Linux, macOS), hMETIS (Windows)" << std::endl;
        std::cout << "\t" << KAHYPAR_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT << " — KaHyPar (Linux, macOS, Windows)" << std::endl;
        std::cout << "\t" << CARA_PARTITIONING_HYPERGRAPH_TYPE_ARGUMENT << " — Cara (Linux, macOS)" << std::endl;
        std::cout << std::endl;

        std::cout << "Files:" << std::endl;
        std::cout << "\t" << INPUT_ARGUMENT << " — specifies the CNF file name" << std::endl;
        std::cout << std::endl;

        std::cout << "Preprocessing types of Cara caching scheme:" << std::endl;
        std::cout << "\t" << NONE_PREPROCESSING_TYPE_ARGUMENT << " — " << Hydra::Cache::CachingScheme::preprocessingTypeEnumToString(Hydra::Cache::CachingScheme::PreprocessingTypeEnum::NONE) << " (default)" << std::endl;
        std::cout << "\t" << NOT_DUPLICATE_CLAUSES_PREPROCESSING_TYPE_ARGUMENT << " — " << Hydra::Cache::CachingScheme::preprocessingTypeEnumToString(Hydra::Cache::CachingScheme::PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES) << std::endl;
        std::cout << "\t" << NOT_SUBSUMED_CLAUSES_PREPROCESSING_TYPE_ARGUMENT << " — " << Hydra::Cache::CachingScheme::preprocessingTypeEnumToString(Hydra::Cache::CachingScheme::PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES) << std::endl;
        std::cout << std::endl;

        std::cout << NUMBER_OF_SAMPLE_MOMENTS_ARGUMENT << " — sets the number of sample moments (min: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MINIMUM) << ", max: " << std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MAXIMUM) << ")" << std::endl;
        std::cout << MUST_MULTIPLY_BY_FACTOR_ARGUMENT << " — multiplies the model count by this factor (for example, Arjun's \"MUST MULTIPLY BY\" factor) (default: 1)" << std::endl;
        std::cout << std::endl;
    }
}   // namespace Cara::CommandLineArguments
