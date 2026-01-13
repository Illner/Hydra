#pragma once

#include <sstream>
#include <stdexcept>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/formulaInstance/FormulaInstanceNumberOfModelsResult.hpp"

#include "BellaTest/compiler/Compiler.hpp"

#include "Hydra/cache/Cache.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "BellaTest/compiler/enums/CacheSizeTypeEnum.hpp"

namespace BellaTest::Compiler::dDNNF {

    using LargeNumberType = Hydra::Cache::LargeNumberType;
    using FormulaSizeType = Hydra::Cache::FormulaSizeType;

    //region Types
    using VarT = Compiler::VarT;
    using LiteralT = Compiler::LiteralT;
    using ClauseIdT = Compiler::ClauseIdT;

    using CompilerType = Compiler::CompilerType;
    using CircuitPtrType = Compiler::CircuitPtrType;
    using NumberOfModelsType = Compiler::NumberOfModelsType;
    using CompilerConfigurationType = Compiler::CompilerConfigurationType;
    using FormulaRepresentationAbstractUniquePtrType = Compiler::FormulaRepresentationAbstractUniquePtrType;
    using ContagiousFormulaRepresentationConfigurationType = Compiler::ContagiousFormulaRepresentationConfigurationType;

    using CircuitTypeEnum = Compiler::CircuitTypeEnum;
    using SatSolverTypeEnum = Compiler::SatSolverTypeEnum;
    using OmitClauseTypeEnum = Compiler::OmitClauseTypeEnum;
    using SubsumptionTypeEnum = Compiler::SubsumptionTypeEnum;
    using VertexWeightTypeEnum = Compiler::VertexWeightTypeEnum;
    using PreprocessingTypeEnum = Compiler::PreprocessingTypeEnum;
    using CachingSchemeTypeEnum = Compiler::CachingSchemeTypeEnum;
    using DecisionHeuristicTypeEnum = Compiler::DecisionHeuristicTypeEnum;
    using CacheCleaningStrategyTypeEnum = Compiler::CacheCleaningStrategyTypeEnum;
    using RecomputingHypergraphCutTypeEnum = Compiler::RecomputingHypergraphCutTypeEnum;
    using ImplicitBcpVariableOrderTypeEnum = Compiler::ImplicitBcpVariableOrderTypeEnum;
    using VariableSubsumptionWithMappingTypeEnum = Compiler::VariableSubsumptionWithMappingTypeEnum;
    //endregion

    inline CompilerConfigurationType createDefaultCompilerConfiguration() {
        CompilerConfigurationType configuration = Compiler::createDefaultCompilerConfiguration();

        configuration.circuitType = CircuitTypeEnum::sd_DNNF;

        return configuration;
    }

    inline NumberOfModelsType computeNumberOfModels(FormulaInstanceEnum formulaInstance, CompilerConfigurationType compilerConfiguration,
                                                    const ContagiousFormulaRepresentationConfigurationType& contagiousFormulaRepresentationConfiguration,
                                                    CacheSizeTypeEnum cacheSizeTypeSharpSatCacheCleaningStrategy, bool useStatistics) {
        FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = parseFormula(formulaInstance,
                                                                                                         contagiousFormulaRepresentationConfiguration);

        // Cache size
        if (cacheSizeTypeSharpSatCacheCleaningStrategy != CacheSizeTypeEnum::IGNORE) {
            FormulaSizeType cacheSize = static_cast<FormulaSizeType>(8) * (formulaRepresentationAbstractUniquePtr->getOriginalFormulaSize() +
                                                                           static_cast<FormulaSizeType>(formulaRepresentationAbstractUniquePtr->getNumberOfOriginalClauses()));

            // MAPPING
            if ((cacheSizeTypeSharpSatCacheCleaningStrategy == CacheSizeTypeEnum::LOW_MAPPING) ||
                (cacheSizeTypeSharpSatCacheCleaningStrategy == CacheSizeTypeEnum::MEDIUM_MAPPING))
                cacheSize += static_cast<FormulaSizeType>(sizeof(VarT)) * static_cast<FormulaSizeType>(formulaRepresentationAbstractUniquePtr->getNumberOfVariablesInOriginalFormula());

            // LOW
            if ((cacheSizeTypeSharpSatCacheCleaningStrategy == CacheSizeTypeEnum::LOW) ||
                (cacheSizeTypeSharpSatCacheCleaningStrategy == CacheSizeTypeEnum::LOW_MAPPING))
                cacheSize *= 2;

            // MEDIUM
            if ((cacheSizeTypeSharpSatCacheCleaningStrategy == CacheSizeTypeEnum::MEDIUM) ||
                (cacheSizeTypeSharpSatCacheCleaningStrategy == CacheSizeTypeEnum::MEDIUM_MAPPING))
                cacheSize *= 4;

            compilerConfiguration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.maxByteSizeCache = cacheSize;
            compilerConfiguration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.maxByteSizeCache = cacheSize;
        }

        StatisticsType statistics;
        CompilerType compiler(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration,
                              useStatistics ? &statistics : nullptr);

        compiler.compile();

        if (useStatistics)
            assert(statistics.getCompilerStatisticsPtr()->compileTimer.getNumberOfCalls() == 1);

        // The compilation failed
        if (!compiler.isCircuitCompiled())
            throw Hydra::Exception::CompilationFailedException();

        CircuitPtrType circuitPtr = compiler.getCompiledCircuitPtr();

        // Check if the compiled circuit implies the CNF formula
        bool doesCircuitImplyCnfFormula = circuitPtr->clausalEntailmentCheck(compiler.getFormulaPtr());
        if (!doesCircuitImplyCnfFormula)
            throw Hydra::Exception::CircuitDoesNotImplyCnfFormulaException();

        NumberOfModelsType numberOfModels = circuitPtr->modelCounting({});

        return numberOfModels;
    }

    inline void process(const CompilerConfigurationType& compilerConfiguration, bool allInstances,
                        const ContagiousFormulaRepresentationConfigurationType& contagiousFormulaRepresentationConfiguration = ContagiousFormulaRepresentationConfigurationType(),
                        CacheSizeTypeEnum cacheSizeTypeSharpSatCacheCleaningStrategy = CacheSizeTypeEnum::IGNORE,
                        bool useStatistics = true) {
        // 4step
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::_4step)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::_4step;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() + " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstance4stepNumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration,
                                                                          cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                          useStatistics);
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
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration,
                                                                          cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                          useStatistics);
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
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration,
                                                                          cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                          useStatistics);
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
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration,
                                                                          cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                          useStatistics);
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
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration,
                                                                          cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                          useStatistics);
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
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration,
                                                                          cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                          useStatistics);
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
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration,
                                                                          cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                          useStatistics);
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
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration,
                                                                          cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                          useStatistics);
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
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration,
                                                                          cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                          useStatistics);
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
                NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                          contagiousFormulaRepresentationConfiguration,
                                                                          cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                          useStatistics);
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
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration,
                                                                              cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                              useStatistics);
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
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration,
                                                                              cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                              useStatistics);
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
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration,
                                                                              cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                              useStatistics);
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
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration,
                                                                              cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                              useStatistics);
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
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration,
                                                                              cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                              useStatistics);
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
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration,
                                                                              cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                              useStatistics);
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
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration,
                                                                              cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                              useStatistics);
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
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration,
                                                                              cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                              useStatistics);
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
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration,
                                                                              cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                              useStatistics);
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
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration,
                                                                              cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                              useStatistics);
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
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration,
                                                                              cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                              useStatistics);
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
                    NumberOfModelsType numberOfModels = computeNumberOfModels(formulaInstance, compilerConfiguration,
                                                                              contagiousFormulaRepresentationConfiguration,
                                                                              cacheSizeTypeSharpSatCacheCleaningStrategy,
                                                                              useStatistics);
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
}   // namespace BellaTest::Compiler::dDNNF
