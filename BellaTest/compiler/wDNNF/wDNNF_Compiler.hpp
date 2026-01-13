#pragma once

#include <sstream>
#include <stdexcept>
#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/formulaInstance/FormulaInstanceNumberOfModelsResult.hpp"

#include "BellaTest/compiler/Compiler.hpp"

#include "Hydra/circuit/enums/CircuitTypeEnum.hpp"

namespace BellaTest::Compiler::wDNNF {

    inline const std::string COMPILED_STRING = "compiled";

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

        configuration.circuitType = CircuitTypeEnum::wDNNF;

        return configuration;
    }

    inline void compile(FormulaInstanceEnum formulaInstance, CompilerConfigurationType compilerConfiguration,
                        const ContagiousFormulaRepresentationConfigurationType& contagiousFormulaRepresentationConfiguration,
                        bool useStatistics) {
        FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = parseFormula(formulaInstance,
                                                                                                         contagiousFormulaRepresentationConfiguration);

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
    }

    inline NumberOfModelsType computeNumberOfModelsWithPolynomialDelay(FormulaInstanceEnum formulaInstance, CompilerConfigurationType compilerConfiguration,
                                                                       const ContagiousFormulaRepresentationConfigurationType& contagiousFormulaRepresentationConfiguration,
                                                                       bool useStatistics) {
        FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = parseFormula(formulaInstance,
                                                                                                         contagiousFormulaRepresentationConfiguration);

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

        NumberOfModelsType numberOfModels = circuitPtr->modelCountingWithPolynomialDelay({}, {}, false);

        return numberOfModels;
    }

    inline void process2(const CompilerConfigurationType& compilerConfiguration, bool timeConsuming,
                         const ContagiousFormulaRepresentationConfigurationType& contagiousFormulaRepresentationConfiguration,
                         bool useStatistics) {
        // 4step
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::_4step)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::_4step;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              timeConsuming ? HydraTest::FormulaInstance::formulaInstance4stepNumberOfModelsResult : COMPILED_STRING);
            std::stringstream& actualResult = test.getStringStream();

            try {
                if (timeConsuming) {
                    NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                                 contagiousFormulaRepresentationConfiguration,
                                                                                                 useStatistics);
                    actualResult << numberOfModels << std::endl;
                }
                else {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
                }
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

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              timeConsuming ? HydraTest::FormulaInstance::formulaInstance5stepNumberOfModelsResult : COMPILED_STRING);
            std::stringstream& actualResult = test.getStringStream();

            try {
                if (timeConsuming) {
                    NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                                 contagiousFormulaRepresentationConfiguration,
                                                                                                 useStatistics);
                    actualResult << numberOfModels << std::endl;
                }
                else {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
                }
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

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceAis6NumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                             contagiousFormulaRepresentationConfiguration,
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

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceAnomalyNumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                             contagiousFormulaRepresentationConfiguration,
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

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              COMPILED_STRING);
            std::stringstream& actualResult = test.getStringStream();

            try {
                compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                actualResult << COMPILED_STRING;
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

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceCnt06_shuffledNumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                             contagiousFormulaRepresentationConfiguration,
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

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              timeConsuming ? HydraTest::FormulaInstance::formulaInstanceD1119_M20NumberOfModelsResult : COMPILED_STRING);
            std::stringstream& actualResult = test.getStringStream();

            try {
                if (timeConsuming) {
                    NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                                 contagiousFormulaRepresentationConfiguration,
                                                                                                 useStatistics);
                    actualResult << numberOfModels << std::endl;
                }
                else {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
                }
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

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceFs_01_netNumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                             contagiousFormulaRepresentationConfiguration,
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

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              COMPILED_STRING);
            std::stringstream& actualResult = test.getStringStream();

            try {
                compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                actualResult << COMPILED_STRING;
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

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              timeConsuming ? HydraTest::FormulaInstance::formulaInstanceS400_benchNumberOfModelsResult : COMPILED_STRING);
            std::stringstream& actualResult = test.getStringStream();

            try {
                if (timeConsuming) {
                    NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                                 contagiousFormulaRepresentationConfiguration,
                                                                                                 useStatistics);
                    actualResult << numberOfModels << std::endl;
                }
                else {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
                }
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

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceWff_3_75_315NumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                             contagiousFormulaRepresentationConfiguration,
                                                                                             useStatistics);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        if (timeConsuming) {
            // ais12
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::ais12)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::ais12;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                          " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                          " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceAis12NumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                                 contagiousFormulaRepresentationConfiguration,
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

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                          " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                          " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  COMPILED_STRING);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
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

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                          " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                          " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  COMPILED_STRING);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
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

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                          " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                          " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  COMPILED_STRING);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
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

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                          " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                          " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  COMPILED_STRING);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
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

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                          " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                          " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  COMPILED_STRING);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }

            // C220_FV
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::C220_FV)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::C220_FV;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                          " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                          " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  COMPILED_STRING);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
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

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                          " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                          " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  COMPILED_STRING);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
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

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                          " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                          " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  COMPILED_STRING);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }

            /*
            // sat-grid-pbl-0030
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::sat_grid_pbl_0030)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::sat_grid_pbl_0030;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                          " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                          " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  COMPILED_STRING);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }
            */

            // sum.32
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::sum_32)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::sum_32;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                          " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                          " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  COMPILED_STRING);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
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

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                          " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                          " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  COMPILED_STRING);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    compile(formulaInstance, compilerConfiguration, contagiousFormulaRepresentationConfiguration, useStatistics);
                    actualResult << COMPILED_STRING;
                }
                catch (const std::exception& e) {
                    actualResult << e.what() << std::endl;
                }

                // test.saveActualResultToFile();
                REQUIRE(test.checkTest());
            }
        }
    }

    inline void process(const CompilerConfigurationType& compilerConfiguration, bool timeConsuming,
                        const ContagiousFormulaRepresentationConfigurationType& contagiousFormulaRepresentationConfiguration = ContagiousFormulaRepresentationConfigurationType(),
                        bool useStatistics = true) {
        // wDNNF
        SECTION("wDNNF") {
            CompilerConfigurationType WDnnfCompilerConfiguration = compilerConfiguration;
            WDnnfCompilerConfiguration.circuitType = CircuitTypeEnum::wDNNF;
            process2(WDnnfCompilerConfiguration, timeConsuming, contagiousFormulaRepresentationConfiguration, useStatistics);
        }

        // Cara caching scheme: a variable to literal mapping is FORBIDDEN for pwDNNF and nwDNNF circuits
        if ((compilerConfiguration.cachingSchemeComponentCachingType == CachingSchemeTypeEnum::CARA) &&
            compilerConfiguration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping)
            return;

        // pwDNNF
        SECTION("pwDNNF") {
            CompilerConfigurationType PWDnnfCompilerConfiguration = compilerConfiguration;
            PWDnnfCompilerConfiguration.circuitType = CircuitTypeEnum::pwDNNF;
            process2(PWDnnfCompilerConfiguration, timeConsuming, contagiousFormulaRepresentationConfiguration, useStatistics);
        }

        // nwDNNF
        SECTION("nwDNNF") {
            CompilerConfigurationType NWDnnfCompilerConfiguration = compilerConfiguration;
            NWDnnfCompilerConfiguration.circuitType = CircuitTypeEnum::nwDNNF;
            process2(NWDnnfCompilerConfiguration, timeConsuming, contagiousFormulaRepresentationConfiguration, useStatistics);
        }
    }

    inline void processConfiguration2(const CompilerConfigurationType& compilerConfiguration, bool timeConsuming,
                                      const ContagiousFormulaRepresentationConfigurationType& contagiousFormulaRepresentationConfiguration,
                                      bool useStatistics) {
        // configuration 1
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::configuration_1)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::configuration_1;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceConfiguration1NumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                             contagiousFormulaRepresentationConfiguration,
                                                                                             useStatistics);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // configuration 2
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::configuration_2)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::configuration_2;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceConfiguration2NumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                             contagiousFormulaRepresentationConfiguration,
                                                                                             useStatistics);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // configuration 3
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::configuration_3)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::configuration_3;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceConfiguration3NumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                             contagiousFormulaRepresentationConfiguration,
                                                                                             useStatistics);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        // configuration 4
        SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::configuration_4)) {
            FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::configuration_4;

            TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                      " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                      " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                              HydraTest::FormulaInstance::formulaInstanceConfiguration4NumberOfModelsResult);
            std::stringstream& actualResult = test.getStringStream();

            try {
                NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                             contagiousFormulaRepresentationConfiguration,
                                                                                             useStatistics);
                actualResult << numberOfModels << std::endl;
            }
            catch (const std::exception& e) {
                actualResult << e.what() << std::endl;
            }

            // test.saveActualResultToFile();
            REQUIRE(test.checkTest());
        }

        if (timeConsuming) {
            // configuration 5
            SECTION(formulaInstanceEnumToString(FormulaInstanceEnum::configuration_5)) {
                FormulaInstanceEnum formulaInstance = FormulaInstanceEnum::configuration_5;

                TemplateTest test(Catch::getResultCapture().getCurrentTestName() +
                                          " {" + Hydra::Circuit::circuitTypeEnumToString(compilerConfiguration.circuitType) + "}" +
                                          " (" + formulaInstanceEnumToString(formulaInstance) + ")",
                                  HydraTest::FormulaInstance::formulaInstanceConfiguration5NumberOfModelsResult);
                std::stringstream& actualResult = test.getStringStream();

                try {
                    NumberOfModelsType numberOfModels = computeNumberOfModelsWithPolynomialDelay(formulaInstance, compilerConfiguration,
                                                                                                 contagiousFormulaRepresentationConfiguration,
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

    inline void processConfiguration(const CompilerConfigurationType& compilerConfiguration, bool timeConsuming,
                                     const ContagiousFormulaRepresentationConfigurationType& contagiousFormulaRepresentationConfiguration = ContagiousFormulaRepresentationConfigurationType(),
                                     bool useStatistics = true) {
        // wDNNF
        SECTION("wDNNF") {
            CompilerConfigurationType WDnnfCompilerConfiguration = compilerConfiguration;
            WDnnfCompilerConfiguration.circuitType = CircuitTypeEnum::wDNNF;
            processConfiguration2(WDnnfCompilerConfiguration, timeConsuming, contagiousFormulaRepresentationConfiguration, useStatistics);
        }

        // pwDNNF
        SECTION("pwDNNF") {
            CompilerConfigurationType PWDnnfCompilerConfiguration = compilerConfiguration;
            PWDnnfCompilerConfiguration.circuitType = CircuitTypeEnum::pwDNNF;
            processConfiguration2(PWDnnfCompilerConfiguration, timeConsuming, contagiousFormulaRepresentationConfiguration, useStatistics);
        }

        // nwDNNF
        SECTION("nwDNNF") {
            CompilerConfigurationType NWDnnfCompilerConfiguration = compilerConfiguration;
            NWDnnfCompilerConfiguration.circuitType = CircuitTypeEnum::nwDNNF;
            processConfiguration2(NWDnnfCompilerConfiguration, timeConsuming, contagiousFormulaRepresentationConfiguration, useStatistics);
        }
    }
}   // namespace BellaTest::Compiler::wDNNF
