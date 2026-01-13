#pragma once

#include <cassert>
#include <iterator>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/formulaInstance/FormulaInstance.hpp"
#include "HydraTest/formulaInstance/FormulaInstanceNumberOfModelsResult.hpp"

#include "Hydra/compiler/Compiler.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/parser/ContagiousFormulaParser.hpp"
#include "Hydra/other/operatingSystem/OperatingSystem.hpp"
#include "Hydra/other/parser/Parser.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "HydraTest/formulaInstance/enums/FormulaInstanceEnum.hpp"

#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/PreprocessingTypeEnum.hpp"
#include "Hydra/formula/representation/contagious/enums/SubsumptionTypeEnum.hpp"
#include "Hydra/formula/representation/contagious/enums/VariableSubsumptionWithMappingTypeEnum.hpp"

#include "Hydra/compiler/Compiler.tpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.tpp"

namespace CaraTest::SharpSolver {

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
    using SharpSolverConfigurationType = Hydra::CompilerConfiguration;
    using SharpSolverType = Hydra::Compiler<VarT, LiteralT, ClauseIdT>;
    using ContagiousFormulaRepresentationConfigurationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration;
    using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

    using NumberOfModelsType = typename Hydra::Compiler<VarT, LiteralT, ClauseIdT>::NumberOfModelsType;

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

    inline SharpSolverConfigurationType createDefaultSharpSolverConfiguration() {
        SharpSolverConfigurationType configuration;

        // Randomness
        configuration.caraPartitioningHypergraphConfiguration.seed = -1;
        configuration.patohPartitioningHypergraphConfiguration.seedPatohLibrary = -1;
        configuration.kahyparPartitioningHypergraphConfiguration.seedKahyparLibrary = -1;

        // Cache cleaning strategy
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::NONE;

        // Caching scheme
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::NONE;

        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_DEFAULT;

        // Circuit
        configuration.circuitType = CircuitTypeEnum::sd_DNNF;

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

    inline void computeNumberOfModels(FormulaRepresentationAbstractUniquePtrType&& formulaRepresentationAbstractUniquePtr,
                                      SharpSolverConfigurationType sharpSolverConfiguration, std::stringstream& actualResult) {
        actualResult << "Current formula: ";
        formulaRepresentationAbstractUniquePtr->printCurrentFormulaDebug(actualResult);
        actualResult << std::endl
                     << std::endl;

        SharpSolverType sharpSolver(std::move(formulaRepresentationAbstractUniquePtr), sharpSolverConfiguration);
        sharpSolver.computeNumberOfModels();

        // The computing number of models failed
        if (!sharpSolver.isNumberOfModelsComputed())
            throw Hydra::Exception::ComputingNumberOfModelsFailedException();

        // Number of models
        NumberOfModelsType numberOfModels = sharpSolver.getComputedNumberOfModels();
        actualResult << "Number of models: " << numberOfModels << std::endl;
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
            default:
                throw Hydra::Exception::NotImplementedException(formulaInstanceEnumToString(formulaInstance),
                                                                "CaraTest::SharpSolver::parseFormula");
        }

        assert(formulaStringPtr);   // formula is set

        unsigned int line = 1;

        std::istringstream stringStream(*formulaStringPtr);
        std::istreambuf_iterator<char> begin(stringStream);
        std::istreambuf_iterator<char> end;

        auto header = Hydra::Other::Parser::parseDimacsCnfHeader(begin, end, line);
        return Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, header, line, false, contagiousFormulaRepresentationConfiguration);
    }

    inline NumberOfModelsType computeNumberOfModels(FormulaInstanceEnum formulaInstance, SharpSolverConfigurationType sharpSolverConfiguration,
                                                    const ContagiousFormulaRepresentationConfigurationType& contagiousFormulaRepresentationConfiguration) {
        FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = parseFormula(formulaInstance,
                                                                                                         contagiousFormulaRepresentationConfiguration);

        SharpSolverType sharpSolver(std::move(formulaRepresentationAbstractUniquePtr), sharpSolverConfiguration);
        sharpSolver.computeNumberOfModels();

        // The computing number of models failed
        if (!sharpSolver.isNumberOfModelsComputed())
            throw Hydra::Exception::ComputingNumberOfModelsFailedException();

        // Number of models
        NumberOfModelsType numberOfModels = sharpSolver.getComputedNumberOfModels();

        return numberOfModels;
    }

    inline void process(const SharpSolverConfigurationType& sharpSolverConfiguration, bool allInstances,
                        const ContagiousFormulaRepresentationConfigurationType& contagiousFormulaRepresentationConfiguration = ContagiousFormulaRepresentationConfigurationType()) {
        // 4step
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::_4step)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::_4step;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstance4stepNumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // 5step
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::_5step)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::_5step;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstance5stepNumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // ais6
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::ais6)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::ais6;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceAis6NumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // anomaly
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::anomaly)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::anomaly;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceAnomalyNumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // cnt06.shuffled
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::cnt06_shuffled)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::cnt06_shuffled;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceCnt06_shuffledNumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // D1119_M20
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::D1119_M20)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::D1119_M20;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceD1119_M20NumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // fs-01.net
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::fs_01_net)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::fs_01_net;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceFs_01_netNumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // mixdup
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::mixdup)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::mixdup;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceMixdupNumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // s400.bench
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::s400_bench)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::s400_bench;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceS400_benchNumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // wff.3.75.315
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::wff_3_75_315)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::wff_3_75_315;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceWff_3_75_315NumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        if (allInstances) {
            // ais12
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::ais12)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::ais12;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceAis12NumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration);
                    actualResult << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }

            // binsearch.16.pp
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::binsearch_16_pp)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::binsearch_16_pp;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceBinsearch_16_ppNumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration);
                    actualResult << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }

            // binsearch.32.pp
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::binsearch_32_pp)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::binsearch_32_pp;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceBinsearch_32_ppNumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration);
                    actualResult << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }

            // bmc-ibm-1
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::bmc_ibm_1)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::bmc_ibm_1;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceBmc_ibm_1NumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration);
                    actualResult << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }

            // bmc-ibm-2
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::bmc_ibm_2)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::bmc_ibm_2;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceBmc_ibm_2NumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration);
                    actualResult << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }

            // bomb_b10_t10_p_t5
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::bomb_b10_t10_p_t5)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::bomb_b10_t10_p_t5;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceBomb_b10_t10_p_t5NumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration);
                    actualResult << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }

            // C171_FR
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::C171_FR)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::C171_FR;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceC171_FRNumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration);
                    actualResult << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }

            // c499.isc
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::c499_isc)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::c499_isc;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceC499_iscNumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration);
                    actualResult << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }

            // or-60-10-7-UC-10
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::or_60_10_7_UC_10)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::or_60_10_7_UC_10;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceOr_60_10_7_UC_10NumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration);
                    actualResult << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }

            /**
            // sat-grid-pbl-0030
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::sat_grid_pbl_0030)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::sat_grid_pbl_0030;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceSat_grid_pbl_0030NumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration);
                    actualResult << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }
            **/

            // sum.32
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::sum_32)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::sum_32;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceSum_32NumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration);
                    actualResult << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }

            // uf250-04
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::uf250_04)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::uf250_04;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceUf250_04NumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, sharpSolverConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration);
                    actualResult << numberOfModels << std::endl;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }
        }
    }
}   // namespace CaraTest::SharpSolver
