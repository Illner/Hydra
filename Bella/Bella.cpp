#include "./Bella.hpp"

#include <cassert>
#include <fstream>
#include <ios>
#include <string>

#include "Hydra/circuit/Circuit.hpp"
#include "Hydra/compiler/Compiler.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/memory/Memory.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/circuit/node/enums/NodeTypeEnum.hpp"
#include "Hydra/other/enums/TemplateTypeEnum.hpp"

#include "Hydra/compiler/Compiler.tpp"

void printTemplateTypes(TemplateTypeEnum varT, TemplateTypeEnum literalT, TemplateTypeEnum clauseIdT) {
    std::cout << "Variable: " << Hydra::Other::templateTypeEnumToString(varT) << std::endl;
    std::cout << "Literal: " << Hydra::Other::templateTypeEnumToString(literalT) << std::endl;
    std::cout << "Clause identifier: " << Hydra::Other::templateTypeEnumToString(clauseIdT) << std::endl;
    std::cout << std::endl;
}

template <typename CommandLineArgumentsStructT>
void printConfigurationBeforeCompilation(const CommandLineArgumentsStructT& commandLineArgumentsStruct) {
    // Files
    std::cout << "Input file: " << commandLineArgumentsStruct.inputFilePath << std::endl;
    if (!commandLineArgumentsStruct.outputFilePath.empty())
        std::cout << "Output file: " << commandLineArgumentsStruct.outputFilePath << std::endl;
    if (!commandLineArgumentsStruct.statisticsFilePath.empty())
        std::cout << "Statistics file: " << commandLineArgumentsStruct.statisticsFilePath << std::endl;
    std::cout << std::endl;

    // Configuration
    std::cout << "Timeout: " << std::to_string(commandLineArgumentsStruct.timeout) << " s" << std::endl;
    std::cout << "Decision heuristic: " << Hydra::DecisionHeuristic::decisionHeuristicTypeEnumToString(commandLineArgumentsStruct.compilerConfiguration.decisionHeuristicType) << std::endl;
    std::cout << "Partitioning hypergraph type: " << Hydra::partitioningHypergraphTypeEnumToString(commandLineArgumentsStruct.compilerConfiguration.partitioningHypergraphType) << std::endl;
    std::cout << "Hypergraph node weight type: " << Hydra::PartitioningHypergraph::vertexWeightTypeEnumToString(commandLineArgumentsStruct.compilerConfiguration.vertexWeightType) << std::endl;
    std::cout << "Recomputing hypergraph cut type: " << Hydra::recomputingHypergraphCutTypeEnumToString(commandLineArgumentsStruct.compilerConfiguration.recomputingHypergraphCutType) << std::endl;
    std::cout << "Component caching scheme: " << Hydra::Cache::CachingScheme::cachingSchemeVariantTypeEnumToString(commandLineArgumentsStruct.compilerConfiguration.cachingSchemeVariantComponentCachingType);
    // Cara caching scheme
    if (commandLineArgumentsStruct.compilerConfiguration.cachingSchemeVariantComponentCachingType == Hydra::Cache::CachingScheme::CachingSchemeVariantTypeEnum::CARA)
        std::cout << " (" << Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::getNumberOfSampleMomentsAsStringStatic(commandLineArgumentsStruct.compilerConfiguration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments) << ")";
    std::cout << std::endl;
    std::cout << "Component cache cleaning strategy: " << Hydra::Cache::CacheCleaningStrategy::cacheCleaningStrategyTypeEnumToString(commandLineArgumentsStruct.compilerConfiguration.cacheCleaningStrategyComponentCachingType) << std::endl;
    std::cout << "Hypergraph cut caching scheme: " << Hydra::Cache::CachingScheme::cachingSchemeTypeEnumToString(commandLineArgumentsStruct.compilerConfiguration.cachingSchemeHypergraphCutCachingType);
    // Cara caching scheme
    if (commandLineArgumentsStruct.compilerConfiguration.cachingSchemeHypergraphCutCachingType == Hydra::Cache::CachingScheme::CachingSchemeTypeEnum::CARA)
        std::cout << " (" << Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::getNumberOfSampleMomentsAsStringStatic(commandLineArgumentsStruct.compilerConfiguration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments) << ")";
    std::cout << std::endl;
    std::cout << "Hypergraph cut cache cleaning strategy: " << Hydra::Cache::CacheCleaningStrategy::cacheCleaningStrategyTypeEnumToString(commandLineArgumentsStruct.compilerConfiguration.cacheCleaningStrategyHypergraphCutCachingType) << std::endl;
    std::cout << std::endl;
}

template <typename CommandLineArgumentsStructT>
void modifyConfigurationAfterParsingFormula([[maybe_unused]] CommandLineArgumentsStructT& commandLineArgumentsStruct) { }

template <typename VarT, typename LiteralT, typename ClauseIdT, typename CommandLineArgumentsStructT>
void core(Hydra::Compiler<VarT, LiteralT, ClauseIdT>& compiler, const CommandLineArgumentsStructT& commandLineArgumentsStruct) {
    using TimePointType = std::chrono::steady_clock::time_point;
    using MemorySizeType = Hydra::Other::Memory::MemorySizeType;
    using LargeFloatingNumberType = Hydra::Other::LargeFloatingNumberType;
    using CircuitPtrType = typename Hydra::Compiler<VarT, LiteralT, ClauseIdT>::CircuitPtrType;
    using NumberOfModelsType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::NumberOfModelsType;
    using NodeTypeCounterType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::NodeTypeCounterType;

    TimePointType startTime = std::chrono::steady_clock::now();
    compiler.compile();
    TimePointType endTime = std::chrono::steady_clock::now();

    // The compilation failed
    if (!compiler.isCircuitCompiled())
        throw Hydra::Exception::CompilationFailedException();

    CircuitPtrType circuitPtr = compiler.getCompiledCircuitPtr();

    // Compilation time
    std::cout << "Compilation time: ";
    LargeFloatingNumberType compilationTime = 0;
    // With statistics
    if (!commandLineArgumentsStruct.statisticsFilePath.empty()) {
        assert(compiler.getStatisticsPtr());   // statistics exists

        // compilationTime += static_cast<LargeFloatingNumberType>(compiler.getStatisticsPtr()->getFormulaRepresentationStatisticsPtr()->initializeTimer.getSumTime());
        compilationTime += static_cast<LargeFloatingNumberType>(compiler.getStatisticsPtr()->getCompilerStatisticsPtr()->initializeTimer.getSumTime());
        compilationTime += static_cast<LargeFloatingNumberType>(compiler.getStatisticsPtr()->getCompilerStatisticsPtr()->compileTimer.getSumTime());
    }
    // Without statistics
    else
        compilationTime = static_cast<LargeFloatingNumberType>(duration_cast<std::chrono::nanoseconds>(endTime - startTime).count());

    compilationTime /= 1'000'000'000;   // nanoseconds -> seconds
    std::cout << std::to_string(compilationTime) << " s" << std::endl;

    // Used memory
    std::cout << "Used memory: ";
    try {
        MemorySizeType peakUsedMemorySize = Hydra::Other::Memory::getPeakVirtualMemorySize();
        if (peakUsedMemorySize >= 0)
            std::cout << std::to_string(peakUsedMemorySize) << " MB" << std::endl;
        else
            std::cout << "not supported" << std::endl;
    }
    catch (...) {
        std::cout << "something wrong" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Circuit type: " << Hydra::Circuit::circuitTypeEnumToString(circuitPtr->getCircuitType()) << std::endl;
    std::cout << "Circuit size: " << std::to_string(circuitPtr->getCircuitSize()) << std::endl;
    std::cout << std::endl;

    std::cout << "Number of edges: " << std::to_string(circuitPtr->getNumberOfEdges()) << std::endl;
    std::cout << "Number of nodes: " << std::to_string(circuitPtr->getNumberOfNodes()) << std::endl;
    std::cout << "Number of variables: " << std::to_string(circuitPtr->getNumberOfUsedVariables()) << std::endl;
    std::cout << std::endl;

    // Node types
    const NodeTypeCounterType& nodeTypeCounter = circuitPtr->getNodeTypeCounter();
    for (Hydra::Circuit::Node::NodeTypeEnum nodeType : Hydra::Other::extractKeysFromMap(nodeTypeCounter, true)) {
        Hydra::Circuit::Node::IdNodeType numberOfNodeType = nodeTypeCounter.at(nodeType);

        // No occurrence
        if (numberOfNodeType == 0)
            continue;

        std::cout << Hydra::Circuit::Node::nodeTypeEnumToString(nodeType) << ": " << std::to_string(numberOfNodeType) << std::endl;
    }
    std::cout << std::endl;

    // Check if the compiled circuit implies the input CNF formula
    if (false && commandLineArgumentsStruct.clausalEntailmentCheck) {
        std::cout << "Checking if circuit |= CNF formula" << std::endl;
        bool doesCircuitImplyCnfFormula = circuitPtr->clausalEntailmentCheck(compiler.getFormulaPtr());
        if (!doesCircuitImplyCnfFormula)
            throw Hydra::Exception::CircuitDoesNotImplyCnfFormulaException();

        std::cout << std::endl;
    }

    // Statistics
    if (!commandLineArgumentsStruct.statisticsFilePath.empty()) {
        assert(compiler.getStatisticsPtr());   // statistics exists

        std::cout << "Statistics: ";

        {
            std::ofstream statisticsFile(commandLineArgumentsStruct.statisticsFilePath, std::ios::out);

            // Statistics file cannot be open
            if (!statisticsFile.is_open())
                throw Hydra::Exception::FileCannotBeOpenedException(commandLineArgumentsStruct.statisticsFilePath);

            compiler.getStatisticsPtr()->printStatistics(statisticsFile, commandLineArgumentsStruct.statisticsAddLabels);
        }

        std::cout << "saved" << std::endl;
    }

    // Output
    if (!commandLineArgumentsStruct.outputFilePath.empty()) {
        std::cout << "Compiled circuit: ";

        {
            std::ofstream outputFile(commandLineArgumentsStruct.outputFilePath, std::ios::out);

            // Output file cannot be open
            if (!outputFile.is_open())
                throw Hydra::Exception::FileCannotBeOpenedException(commandLineArgumentsStruct.outputFilePath);

            circuitPtr->printCircuit(outputFile);
        }

        std::cout << "saved" << std::endl;
    }

    if (!commandLineArgumentsStruct.statisticsFilePath.empty() || !commandLineArgumentsStruct.outputFilePath.empty())
        std::cout << std::endl;

    // Number of models
    if (commandLineArgumentsStruct.numberOfModels) {
        NumberOfModelsType numberOfModels;

        if (Hydra::Other::containInSet(Hydra::Circuit::supportModelCountingCircuitTypeSet, circuitPtr->getCircuitType()))
            numberOfModels = circuitPtr->modelCounting({});
        else {
            std::cerr << "WARNING: the number of models is being computed using enumeration!" << std::endl;

            numberOfModels = circuitPtr->modelCountingWithPolynomialDelay({}, {});
        }

        std::cout << "Number of models: " << numberOfModels << std::endl;
    }
}
