#pragma once

#include <atomic>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iterator>
#include <memory>

#include "Hydra/compiler/Compiler.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/parser/Parser.hpp"
#include "Hydra/preprocessor/cnf/CnfPreprocessorAbstract.hpp"
#include "Hydra/statistics/Statistics.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Cara/sharpSolver/enums/ModelCountingTypeEnum.hpp"
#include "Hydra/compiler/enums/HypergraphPartitioningTypeEnum.hpp"
#include "Hydra/formula/representation/contiguous/enums/VariableSubsumptionWithMappingTypeEnum.hpp"
#include "Hydra/hypergraphPartitioning/enums/VertexWeightTypeEnum.hpp"
#include "Hydra/other/enums/TemplateTypeEnum.hpp"
#include "Hydra/preprocessor/cnf/enums/CnfPreprocessorVariantTypeEnum.hpp"

#include "Hydra/compiler/Compiler.tpp"
#include "Hydra/formula/representation/contiguous/ContiguousFormulaRepresentation.tpp"

namespace Hydra {

    using AtomicBoolType = std::atomic<bool>;
    using AtomicBoolPtrType = const AtomicBoolType*;
    using TemplateTypeEnum = Other::TemplateTypeEnum;
    using StatisticsPtrType = Statistics::Statistics::StatisticsPtrType;
    using CnfPreprocessorVariantTypeEnum = Preprocessor::Cnf::CnfPreprocessorVariantTypeEnum;
    using CnfPreprocessorAbstractUniquePtrType = std::unique_ptr<Preprocessor::Cnf::CnfPreprocessorAbstract>;
    using CnfPreprocessorStatisticsPtrType = Preprocessor::Cnf::CnfPreprocessorAbstract::CnfPreprocessorStatisticsPtrType;

    template <typename CommandLineArgumentsStructT>
    void initialAdjustmentToConfiguration(CommandLineArgumentsStructT& commandLineArgumentsStruct);

    /**
     * Note: DECLARED BUT NOT DEFINED FUNCTION
     */
    void printTemplateTypes(TemplateTypeEnum varT, TemplateTypeEnum literalT, TemplateTypeEnum clauseIdT);

    /**
     * Note: DECLARED BUT NOT DEFINED FUNCTION
     */
    template <typename CommandLineArgumentsStructT>
    void printConfigurationBeforeCompilation(const CommandLineArgumentsStructT& commandLineArgumentsStruct);

    /**
     * Note: DECLARED BUT NOT DEFINED FUNCTION
     */
    template <typename CommandLineArgumentsStructT>
    void modifyConfigurationAfterParsingFormula(CommandLineArgumentsStructT& commandLineArgumentsStruct);

    /**
     * Initialize the CNF preprocessor
     * Note: DECLARED BUT NOT DEFINED FUNCTION
     * @return the CNF preprocessor
     */
    template <typename CnfPreprocessorStructT>
    CnfPreprocessorAbstractUniquePtrType initializeCnfPreprocessor(CnfPreprocessorStructT& cnfPreprocessorStruct,
                                                                   CnfPreprocessorStatisticsPtrType cnfPreprocessorStatisticsPtr);

    /**
     * Note: DECLARED BUT NOT DEFINED FUNCTION
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename CommandLineArgumentsStructT>
    void core(Compiler<VarT, LiteralT, ClauseIdT>& compiler, const CommandLineArgumentsStructT& commandLineArgumentsStruct);

    template <typename CommandLineArgumentsStructT>
    void coreMain(CommandLineArgumentsStructT& commandLineArgumentsStruct, StatisticsPtrType statisticsPtr, AtomicBoolPtrType killedByMainThread = nullptr);
}   // namespace Hydra

#include "./Hydra.ipp"
