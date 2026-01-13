#include "./Cara.hpp"

#include <boost/multiprecision/cpp_dec_float.hpp>
#include <cassert>
#include <chrono>
#include <limits>
#include <string>

#include "Hydra/compiler/Compiler.hpp"

#include "Cara/sharpSolver/exceptions/SharpSolverException.hpp"
#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Cara/sharpSolver/enums/ModelCountingTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/PreprocessingTypeEnum.hpp"
#include "Hydra/other/enums/TemplateTypeEnum.hpp"

#include "Hydra/compiler/Compiler.tpp"

void printTemplateTypes(TemplateTypeEnum varT, TemplateTypeEnum literalT, TemplateTypeEnum clauseIdT) {
    std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << " Variable: " << Hydra::Other::templateTypeEnumToString(varT) << std::endl;
    std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << " Literal: " << Hydra::Other::templateTypeEnumToString(literalT) << std::endl;
    std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << " Clause identifier: " << Hydra::Other::templateTypeEnumToString(clauseIdT) << std::endl;
    std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << std::endl;
}

template <typename CommandLineArgumentsStructT>
void printConfigurationBeforeCompilation(const CommandLineArgumentsStructT& commandLineArgumentsStruct) {
    // Files
    std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << " Input file: " << commandLineArgumentsStruct.inputFilePath << std::endl;
    std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << std::endl;

    // Configuration
    std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << " Number of sample moments: " << std::to_string(commandLineArgumentsStruct.compilerConfiguration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments) << std::endl;
    std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << " Partitioning hypergraph type: " << Hydra::partitioningHypergraphTypeEnumToString(commandLineArgumentsStruct.compilerConfiguration.partitioningHypergraphType) << std::endl;
    std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << " Preprocessing type of Cara caching scheme: " << Hydra::Cache::CachingScheme::preprocessingTypeEnumToString(commandLineArgumentsStruct.compilerConfiguration.caraCachingSchemeComponentCachingConfiguration.preprocessingType) << std::endl;
    std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << std::endl;

    // Must-multiply-by factor
    if (commandLineArgumentsStruct.mustMultiplyByFactor > 1) {
        std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << " Must-multiply-by factor: " << commandLineArgumentsStruct.mustMultiplyByFactor << std::endl;
        std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << std::endl;
    }
}

template <typename CommandLineArgumentsStructT>
void modifyConfigurationAfterParsingFormula(CommandLineArgumentsStructT& commandLineArgumentsStruct) {
    using ModelCountingTypeEnum = Cara::ModelCountingTypeEnum;

    // Model counting type is NOT set
    if (commandLineArgumentsStruct.modelCountingType == ModelCountingTypeEnum::UNDEFINED) {
        commandLineArgumentsStruct.modelCountingType = ModelCountingTypeEnum::MC;

        std::cerr << "WARNING: the model counting type has been automatically set to "
                  << Cara::modelCountingTypeEnumToString(commandLineArgumentsStruct.modelCountingType) << "!" << std::endl;
    }
}

template <typename VarT, typename LiteralT, typename ClauseIdT, typename CommandLineArgumentsStructT>
void core(Hydra::Compiler<VarT, LiteralT, ClauseIdT>& sharpSolver, const CommandLineArgumentsStructT& commandLineArgumentsStruct) {
    using ModelCountingTypeEnum = Cara::ModelCountingTypeEnum;
    using TimePointType = std::chrono::steady_clock::time_point;
    using NumberOfModelsType = typename Hydra::Compiler<VarT, LiteralT, ClauseIdT>::NumberOfModelsType;

    assert(commandLineArgumentsStruct.modelCountingType != ModelCountingTypeEnum::UNDEFINED);   // model counting type is set

    // Model counting type is NOT supported
    if (commandLineArgumentsStruct.modelCountingType != ModelCountingTypeEnum::MC)
        throw Cara::Exception::ModelCountingTypeIsNotSupportedException(commandLineArgumentsStruct.modelCountingType);

    TimePointType startTime = std::chrono::steady_clock::now();
    sharpSolver.computeNumberOfModels();
    TimePointType endTime = std::chrono::steady_clock::now();

    // The computing number of models failed
    if (!sharpSolver.isNumberOfModelsComputed())
        throw Hydra::Exception::ComputingNumberOfModelsFailedException();

    // Computing time
    LargeFloatingNumberType computingTime = static_cast<LargeFloatingNumberType>(duration_cast<std::chrono::nanoseconds>(endTime - startTime).count());
    computingTime /= 1'000'000'000;   // nanoseconds -> seconds

    // Number of models
    NumberOfModelsType numberOfModels = sharpSolver.getComputedNumberOfModels();
    numberOfModels *= commandLineArgumentsStruct.mustMultiplyByFactor;

    printModelCountingOutputForModelCountingCompetition(numberOfModels, computingTime);
}

void printModelCountingOutputForModelCountingCompetition(const MpzIntType& numberOfModels, LargeFloatingNumberType computingTime) {
    bool satisfiable = (numberOfModels != 0);

    // Computing time
    if (computingTime != 0)
        std::cout << COMMENT_FOR_MODEL_COUNTING_COMPETITION << " COMPUTING_TIME_S=" << std::to_string(computingTime) << std::endl;

    // s SATISFIABLE|UNSATISFIABLE|UNKNOWN
    std::cout << "s ";
    if (satisfiable)
        std::cout << "SATISFIABLE";
    else
        std::cout << "UNSATISFIABLE";
    std::cout << std::endl;

    // c s type [mc|wmc|pmc|pwmc]
    std::cout << "c s type mc" << std::endl;

    // c s [log10-estimate|neglog10-estimate] VALUE
    std::cout << "c s log10-estimate ";
    if (satisfiable) {
        boost::multiprecision::mpf_float::default_precision(128);
        std::cout.precision(std::numeric_limits<boost::multiprecision::cpp_dec_float_50>::digits10);
        std::cout << boost::multiprecision::log10(boost::multiprecision::cpp_dec_float_100(numberOfModels));
    }
    else
        std::cout << "-inf";
    std::cout << std::endl;

    // c s SOLVERTYPE PRECISION NOTATION VALUE
    std::cout << "c s exact arb int ";
    if (satisfiable)
        std::cout << numberOfModels;
    else
        std::cout << "0";
    std::cout << std::endl;
}
