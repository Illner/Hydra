#pragma once

#include <atomic>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iterator>

#include "Hydra/compiler/Compiler.hpp"
#include "Hydra/formula/representation/contagious/parser/ContagiousFormulaParser.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/parser/Parser.hpp"
#include "Hydra/statistics/Statistics.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Cara/sharpSolver/enums/ModelCountingTypeEnum.hpp"
#include "Hydra/compiler/enums/PartitioningHypergraphTypeEnum.hpp"
#include "Hydra/formula/representation/contagious/enums/VariableSubsumptionWithMappingTypeEnum.hpp"
#include "Hydra/other/enums/TemplateTypeEnum.hpp"
#include "Hydra/partitioningHypergraph/enums/VertexWeightTypeEnum.hpp"

#include "Hydra/compiler/Compiler.tpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.tpp"

using AtomicBoolType = std::atomic<bool>;
using AtomicBoolPtrType = const AtomicBoolType*;
using TemplateTypeEnum = Hydra::Other::TemplateTypeEnum;
using StatisticsPtrType = typename Hydra::Statistics::Statistics::StatisticsPtrType;

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
 * Note: DECLARED BUT NOT DEFINED FUNCTION
 */
template <typename VarT, typename LiteralT, typename ClauseIdT, typename CommandLineArgumentsStructT>
void core(Hydra::Compiler<VarT, LiteralT, ClauseIdT>& compiler, const CommandLineArgumentsStructT& commandLineArgumentsStruct);

template <typename CommandLineArgumentsStructT>
void coreMain(CommandLineArgumentsStructT& commandLineArgumentsStruct, StatisticsPtrType statisticsPtr, AtomicBoolPtrType killedByMainThread = nullptr);

#include "./Hydra.ipp"
