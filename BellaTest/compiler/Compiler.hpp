#pragma once

#include <cassert>
#include <iterator>
#include <memory>
#include <sstream>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/formulaInstance/FormulaInstance.hpp"

#include "Hydra/circuit/Circuit.hpp"
#include "Hydra/compiler/Compiler.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/parser/ContagiousFormulaParser.hpp"
#include "Hydra/other/operatingSystem/OperatingSystem.hpp"
#include "Hydra/other/parser/Parser.hpp"
#include "Hydra/statistics/Statistics.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "HydraTest/formulaInstance/enums/FormulaInstanceEnum.hpp"

#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/PreprocessingTypeEnum.hpp"
#include "Hydra/formula/representation/contagious/enums/SubsumptionTypeEnum.hpp"
#include "Hydra/formula/representation/contagious/enums/VariableSubsumptionWithMappingTypeEnum.hpp"

#include "Hydra/compiler/Compiler.tpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.tpp"

namespace BellaTest::Compiler {

    #if OPERATING_SYSTEM_WINDOWS
    inline std::string PATOH_HMETIS_TEST_NAME = "hMETIS";
    #else
    inline std::string PATOH_HMETIS_TEST_NAME = "PaToH";
    #endif

    using TemplateTest = HydraTest::TemplateTest;

    //region Types
    using VarT = char32_t;
    using LiteralT = char32_t;
    using ClauseIdT = char32_t;

    using StringPtrType = const std::string*;
    using StatisticsType = Hydra::Statistics::Statistics;
    using CompilerConfigurationType = Hydra::CompilerConfiguration;
    using CompilerType = Hydra::Compiler<VarT, LiteralT, ClauseIdT>;
    using ContagiousFormulaRepresentationConfigurationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration;
    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

    using CircuitPtrType = typename Hydra::Compiler<VarT, LiteralT, ClauseIdT>::CircuitPtrType;
    using NumberOfModelsType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::NumberOfModelsType;

    using CircuitTypeEnum = Hydra::CompilerConfiguration::CircuitTypeEnum;
    using SatSolverTypeEnum = Hydra::CompilerConfiguration::SatSolverTypeEnum;
    using OmitClauseTypeEnum = Hydra::Cache::CachingScheme::OmitClauseTypeEnum;
    using FormulaInstanceEnum = HydraTest::FormulaInstance::FormulaInstanceEnum;
    using PartitioningHypergraphTypeEnum = Hydra::PartitioningHypergraphTypeEnum;
    using VertexWeightTypeEnum = Hydra::CompilerConfiguration::VertexWeightTypeEnum;
    using PreprocessingTypeEnum = Hydra::Cache::CachingScheme::PreprocessingTypeEnum;
    using RecomputingHypergraphCutTypeEnum = Hydra::RecomputingHypergraphCutTypeEnum;
    using CachingSchemeTypeEnum = Hydra::CompilerConfiguration::CachingSchemeTypeEnum;
    using DecisionHeuristicTypeEnum = Hydra::CompilerConfiguration::DecisionHeuristicTypeEnum;
    using SubsumptionTypeEnum = Hydra::Formula::Representation::Contagious::SubsumptionTypeEnum;
    using CacheCleaningStrategyTypeEnum = Hydra::CompilerConfiguration::CacheCleaningStrategyTypeEnum;
    using ImplicitBcpVariableOrderTypeEnum = Hydra::CompilerConfiguration::ImplicitBcpVariableOrderTypeEnum;
    using VariableSubsumptionWithMappingTypeEnum = Hydra::Formula::Representation::Contagious::VariableSubsumptionWithMappingTypeEnum;
    //endregion

    inline CompilerConfigurationType createDefaultCompilerConfiguration() {
        CompilerConfigurationType configuration;

        // Randomness
        configuration.caraPartitioningHypergraphConfiguration.seed = -1;
        configuration.patohPartitioningHypergraphConfiguration.seedPatohLibrary = -1;
        configuration.kahyparPartitioningHypergraphConfiguration.seedKahyparLibrary = -1;

        // Cache cleaning strategy
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::NONE;

        // Caching scheme
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::NONE;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = false;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        // Circuit
        configuration.circuitType = CircuitTypeEnum::NNF;

        // SAT solver
        configuration.satSolverType = SatSolverTypeEnum::MINISAT;

        // Decision heuristic
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::VSADS;

        configuration.vsadsDecisionHeuristicConfiguration.p = 1;
        configuration.vsadsDecisionHeuristicConfiguration.q = 0.5;

        // Partitioning hypergraph
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY;

        #if OPERATING_SYSTEM_WINDOWS
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;
        #else
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;
        #endif

        return configuration;
    }

    inline void compileAndPrintCircuit(FormulaRepresentationAbstractUniquePtrType&& formulaRepresentationAbstractUniquePtr,
                                       CompilerConfigurationType compilerConfiguration, std::stringstream& actualResult) {
        actualResult << "Current formula: ";
        formulaRepresentationAbstractUniquePtr->printCurrentFormulaDebug(actualResult);
        actualResult << std::endl
                     << std::endl;

        CompilerType compiler(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration);
        compiler.compile();

        // The compilation failed
        if (!compiler.isCircuitCompiled())
            throw Hydra::Exception::CompilationFailedException();

        CircuitPtrType circuitPtr = compiler.getCompiledCircuitPtr();
        circuitPtr->printCircuitDebug(actualResult);
    }

    inline FormulaRepresentationAbstractUniquePtrType parseFormula(FormulaInstanceEnum formulaInstance,
                                                                   const ContagiousFormulaRepresentationConfigurationType& contagiousFormulaRepresentationConfiguration) {
        StringPtrType formulaStringPtr = nullptr;

        switch (formulaInstance) {
            case FormulaInstanceEnum::_4step:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstance4step;
                break;
            case FormulaInstanceEnum::_5step:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstance5step;
                break;
            case FormulaInstanceEnum::ais6:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceAis6;
                break;
            case FormulaInstanceEnum::ais12:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceAis12;
                break;
            case FormulaInstanceEnum::anomaly:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceAnomaly;
                break;
            case FormulaInstanceEnum::binsearch_16_pp:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceBinsearch_16_pp;
                break;
            case FormulaInstanceEnum::binsearch_32_pp:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceBinsearch_32_pp;
                break;
            case FormulaInstanceEnum::bmc_ibm_1:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceBmc_ibm_1;
                break;
            case FormulaInstanceEnum::bmc_ibm_2:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceBmc_ibm_2;
                break;
            case FormulaInstanceEnum::bomb_b10_t10_p_t5:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceBomb_b10_t10_p_t5;
                break;
            case FormulaInstanceEnum::C171_FR:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceC171_FR;
                break;
            case FormulaInstanceEnum::C220_FV:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceC220_FV;
                break;
            case FormulaInstanceEnum::c499_isc:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceC499_isc;
                break;
            case FormulaInstanceEnum::cnt06_shuffled:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceCnt06_shuffled;
                break;
            case FormulaInstanceEnum::D1119_M20:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceD1119_M20;
                break;
            case FormulaInstanceEnum::fs_01_net:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceFs_01_net;
                break;
            case FormulaInstanceEnum::mixdup:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceMixdup;
                break;
            case FormulaInstanceEnum::or_60_10_7_UC_10:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceOr_60_10_7_UC_10;
                break;
            case FormulaInstanceEnum::s400_bench:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceS400_bench;
                break;
            case FormulaInstanceEnum::sat_grid_pbl_0030:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceSat_grid_pbl_0030;
                break;
            case FormulaInstanceEnum::sum_32:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceSum_32;
                break;
            case FormulaInstanceEnum::uf250_04:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceUf250_04;
                break;
            case FormulaInstanceEnum::wff_3_75_315:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceWff_3_75_315;
                break;
            case FormulaInstanceEnum::configuration_1:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceConfiguration1;
                break;
            case FormulaInstanceEnum::configuration_2:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceConfiguration2;
                break;
            case FormulaInstanceEnum::configuration_3:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceConfiguration3;
                break;
            case FormulaInstanceEnum::configuration_4:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceConfiguration4;
                break;
            case FormulaInstanceEnum::configuration_5:
                formulaStringPtr = &HydraTest::FormulaInstance::formulaInstanceConfiguration5;
                break;
            default:
                throw Hydra::Exception::NotImplementedException(formulaInstanceEnumToString(formulaInstance),
                                                                "BellaTest::Compiler::parseFormula");
        }

        assert(formulaStringPtr);   // formula is set

        unsigned int line = 1;

        std::istringstream stringStream(*formulaStringPtr);
        std::istreambuf_iterator<char> begin(stringStream);
        std::istreambuf_iterator<char> end;

        auto header = Hydra::Other::Parser::parseDimacsCnfHeader(begin, end, line);
        return Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, header, line, false, contagiousFormulaRepresentationConfiguration);
    }
}   // namespace BellaTest::Compiler
