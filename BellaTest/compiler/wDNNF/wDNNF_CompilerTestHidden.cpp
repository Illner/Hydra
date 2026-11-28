#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/external/unitTesting/Catch2/catch.hpp"

#include "BellaTest/compiler/CreateFormula.hpp"
#include "BellaTest/compiler/wDNNF/wDNNF_Compiler.hpp"
#include "BellaTest/compiler/wDNNF/wDNNF_CompilerTestResult.hpp"

namespace BellaTest::Compiler::wDNNF {

    /**
     * Default
     */
    TEST_CASE(" [Compiler::wDNNF] default", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();

        process(configuration, true);
    }

    /**
     * Statistics
     */
    TEST_CASE(" [Compiler::wDNNF] statistics", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();

        process(configuration, true, ContiguousFormulaRepresentationConfigurationType(), true);
    }

    /**
     * No statistics
     */
    TEST_CASE(" [Compiler::wDNNF] no statistics", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();

        process(configuration, true, ContiguousFormulaRepresentationConfigurationType(), false);
    }

    /**
     * Seed MIN_SEED
     */
    TEST_CASE(" [Compiler::wDNNF] seed MIN_SEED", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.setSeed(Hydra::Other::Seed::MIN_SEED);

        process(configuration, true);
    }

    /**
     * Seed MAX_SEED
     */
    TEST_CASE(" [Compiler::wDNNF] seed MAX_SEED", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.setSeed(Hydra::Other::Seed::MAX_SEED);

        process(configuration, true);
    }

    //region SAT solver
    //region MiniSat
    /**
     * SAT solver - MiniSat
     *      VSIDS score: MiniSat
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - MiniSat (VSIDS score: MiniSat)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::MINISAT;
        configuration.miniSatSolverConfiguration.vsidsScoreType = MiniSatVsidsScoreTypeEnum::MINISAT;

        process(configuration, true);
    }

    /**
     * SAT solver - MiniSat
     *      VSIDS score: D4
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - MiniSat (VSIDS score: D4)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::MINISAT;
        configuration.miniSatSolverConfiguration.vsidsScoreType = MiniSatVsidsScoreTypeEnum::D4;

        process(configuration, true);
    }

    /**
     * SAT solver - MiniSat
     *      VSIDS score: D4v2
     *      frequency decay: 0
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - MiniSat (VSIDS score: D4v2, frequency decay: 0)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::MINISAT;
        configuration.miniSatSolverConfiguration.frequencyDecayD4v2VsidsScore = 0;
        configuration.miniSatSolverConfiguration.vsidsScoreType = MiniSatVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - MiniSat
     *      VSIDS score: D4v2
     *      frequency decay: 2
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - MiniSat (VSIDS score: D4v2, frequency decay: 2)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::MINISAT;
        configuration.miniSatSolverConfiguration.frequencyDecayD4v2VsidsScore = 2;
        configuration.miniSatSolverConfiguration.vsidsScoreType = MiniSatVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - MiniSat
     *      VSIDS score: D4v2
     *      frequency decay: 8
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - MiniSat (VSIDS score: D4v2, frequency decay: 8)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::MINISAT;
        configuration.miniSatSolverConfiguration.frequencyDecayD4v2VsidsScore = 8;
        configuration.miniSatSolverConfiguration.vsidsScoreType = MiniSatVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - MiniSat
     *      VSIDS score: D4v2
     *      frequency decay: 32
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - MiniSat (VSIDS score: D4v2, frequency decay: 32)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::MINISAT;
        configuration.miniSatSolverConfiguration.frequencyDecayD4v2VsidsScore = 32;
        configuration.miniSatSolverConfiguration.vsidsScoreType = MiniSatVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - MiniSat
     *      VSIDS score: D4v2
     *      frequency decay: 128
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - MiniSat (VSIDS score: D4v2, frequency decay: 128)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::MINISAT;
        configuration.miniSatSolverConfiguration.frequencyDecayD4v2VsidsScore = 128;
        configuration.miniSatSolverConfiguration.vsidsScoreType = MiniSatVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - MiniSat
     *      VSIDS score: D4v2
     *      frequency decay: 512
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - MiniSat (VSIDS score: D4v2, frequency decay: 512)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::MINISAT;
        configuration.miniSatSolverConfiguration.frequencyDecayD4v2VsidsScore = 512;
        configuration.miniSatSolverConfiguration.vsidsScoreType = MiniSatVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - MiniSat
     *      VSIDS score: D4v2
     *      frequency decay: 2'048
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - MiniSat (VSIDS score: D4v2, frequency decay: 2'048)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::MINISAT;
        configuration.miniSatSolverConfiguration.frequencyDecayD4v2VsidsScore = 2'048;
        configuration.miniSatSolverConfiguration.vsidsScoreType = MiniSatVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - MiniSat
     *      VSIDS score: D4v2
     *      frequency decay: 8'192
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - MiniSat (VSIDS score: D4v2, frequency decay: 8'192)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::MINISAT;
        configuration.miniSatSolverConfiguration.frequencyDecayD4v2VsidsScore = 8'192;
        configuration.miniSatSolverConfiguration.vsidsScoreType = MiniSatVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }
    //endregion

    //region Glucose
    /**
     * SAT solver - Glucose
     *      VSIDS score: Glucose
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - Glucose (VSIDS score: Glucose)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::GLUCOSE;
        configuration.glucoseSolverConfiguration.vsidsScoreType = GlucoseVsidsScoreTypeEnum::GLUCOSE;

        process(configuration, true);
    }

    /**
     * SAT solver - Glucose
     *      VSIDS score: D4v2
     *      frequency decay: 0
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - Glucose (VSIDS score: D4v2, frequency decay: 0)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::GLUCOSE;
        configuration.glucoseSolverConfiguration.frequencyDecayD4v2VsidsScore = 0;
        configuration.glucoseSolverConfiguration.vsidsScoreType = GlucoseVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - Glucose
     *      VSIDS score: D4v2
     *      frequency decay: 2
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - Glucose (VSIDS score: D4v2, frequency decay: 2)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::GLUCOSE;
        configuration.glucoseSolverConfiguration.frequencyDecayD4v2VsidsScore = 2;
        configuration.glucoseSolverConfiguration.vsidsScoreType = GlucoseVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - Glucose
     *      VSIDS score: D4v2
     *      frequency decay: 8
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - Glucose (VSIDS score: D4v2, frequency decay: 8)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::GLUCOSE;
        configuration.glucoseSolverConfiguration.frequencyDecayD4v2VsidsScore = 8;
        configuration.glucoseSolverConfiguration.vsidsScoreType = GlucoseVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - Glucose
     *      VSIDS score: D4v2
     *      frequency decay: 32
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - Glucose (VSIDS score: D4v2, frequency decay: 32)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::GLUCOSE;
        configuration.glucoseSolverConfiguration.frequencyDecayD4v2VsidsScore = 32;
        configuration.glucoseSolverConfiguration.vsidsScoreType = GlucoseVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - Glucose
     *      VSIDS score: D4v2
     *      frequency decay: 128
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - Glucose (VSIDS score: D4v2, frequency decay: 128)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::GLUCOSE;
        configuration.glucoseSolverConfiguration.frequencyDecayD4v2VsidsScore = 128;
        configuration.glucoseSolverConfiguration.vsidsScoreType = GlucoseVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - Glucose
     *      VSIDS score: D4v2
     *      frequency decay: 512
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - Glucose (VSIDS score: D4v2, frequency decay: 512)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::GLUCOSE;
        configuration.glucoseSolverConfiguration.frequencyDecayD4v2VsidsScore = 512;
        configuration.glucoseSolverConfiguration.vsidsScoreType = GlucoseVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - Glucose
     *      VSIDS score: D4v2
     *      frequency decay: 2'048
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - Glucose (VSIDS score: D4v2, frequency decay: 2'048)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::GLUCOSE;
        configuration.glucoseSolverConfiguration.frequencyDecayD4v2VsidsScore = 2'048;
        configuration.glucoseSolverConfiguration.vsidsScoreType = GlucoseVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }

    /**
     * SAT solver - Glucose
     *      VSIDS score: D4v2
     *      frequency decay: 8'192
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - Glucose (VSIDS score: D4v2, frequency decay: 8'192)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::GLUCOSE;
        configuration.glucoseSolverConfiguration.frequencyDecayD4v2VsidsScore = 8'192;
        configuration.glucoseSolverConfiguration.vsidsScoreType = GlucoseVsidsScoreTypeEnum::D4_V2;

        process(configuration, true);
    }
    //endregion

    //region CaDiCaL
    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: CaDiCaL
     *      score factor per mille: 500
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: CaDiCaL, score factor per mille: 500)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.scoreFactorCadical = 500;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::CADICAL;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: CaDiCaL
     *      score factor per mille: 550
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: CaDiCaL, score factor per mille: 550)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.scoreFactorCadical = 550;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::CADICAL;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: CaDiCaL
     *      score factor per mille: 600
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: CaDiCaL, score factor per mille: 600)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.scoreFactorCadical = 600;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::CADICAL;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: CaDiCaL
     *      score factor per mille: 650
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: CaDiCaL, score factor per mille: 650)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.scoreFactorCadical = 650;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::CADICAL;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: CaDiCaL
     *      score factor per mille: 700
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: CaDiCaL, score factor per mille: 700)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.scoreFactorCadical = 700;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::CADICAL;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: CaDiCaL
     *      score factor per mille: 750
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: CaDiCaL, score factor per mille: 750)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.scoreFactorCadical = 750;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::CADICAL;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: CaDiCaL
     *      score factor per mille: 800
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: CaDiCaL, score factor per mille: 800)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.scoreFactorCadical = 800;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::CADICAL;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: CaDiCaL
     *      score factor per mille: 850
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: CaDiCaL, score factor per mille: 850)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.scoreFactorCadical = 850;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::CADICAL;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: CaDiCaL
     *      score factor per mille: 900
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: CaDiCaL, score factor per mille: 900)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.scoreFactorCadical = 900;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::CADICAL;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: CaDiCaL
     *      score factor per mille: 950
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: CaDiCaL, score factor per mille: 950)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.scoreFactorCadical = 950;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::CADICAL;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: CaDiCaL
     *      score factor per mille: 1'000
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: CaDiCaL, score factor per mille: 1'000)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.scoreFactorCadical = 1'000;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::CADICAL;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: Hydra
     *      frequency decay: 0
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: Hydra, frequency decay: 0)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.frequencyDecayHydraVsidsScore = 0;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::HYDRA;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: Hydra
     *      frequency decay: 2
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: Hydra, frequency decay: 2)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.frequencyDecayHydraVsidsScore = 2;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::HYDRA;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: Hydra
     *      frequency decay: 8
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: Hydra, frequency decay: 8)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.frequencyDecayHydraVsidsScore = 8;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::HYDRA;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: Hydra
     *      frequency decay: 32
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: Hydra, frequency decay: 32)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.frequencyDecayHydraVsidsScore = 32;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::HYDRA;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: Hydra
     *      frequency decay: 128
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: Hydra, frequency decay: 128)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.frequencyDecayHydraVsidsScore = 128;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::HYDRA;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: Hydra
     *      frequency decay: 512
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: Hydra, frequency decay: 512)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.frequencyDecayHydraVsidsScore = 512;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::HYDRA;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: Hydra
     *      frequency decay: 2'048
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: Hydra, frequency decay: 2'048)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.frequencyDecayHydraVsidsScore = 2'048;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::HYDRA;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      VSIDS score: Hydra
     *      frequency decay: 8'192
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (VSIDS score: Hydra, frequency decay: 8'192)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.frequencyDecayHydraVsidsScore = 8'192;
        configuration.cadicalSolverConfiguration.vsidsScoreType = CadicalVsidsScoreTypeEnum::HYDRA;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 2
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 2)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 2;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 25
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 25)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 25;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 50
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 50)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 50;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 75
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 75)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 75;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 100
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 100)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 100;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 200
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 200)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 200;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 300
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 300)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 300;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 400
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 400)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 400;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 500
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 500)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 500;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 600
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 600)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 600;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 700
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 700)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 700;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 800
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 800)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 800;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 900
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 900)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 900;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 1'000
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 1'000)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 1'000;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 10'000
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 10'000)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 10'000;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 100'000
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 100'000)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 100'000;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1)
     *      reduce interval: 1'000'000
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt^2 / 2 * (number of reductions so far + 1), reduce interval: 1'000'000)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 1'000'000;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::NUMBER_OF_REDUCTIONS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 2
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 2)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 2;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 25
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 25)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 25;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 50
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 50)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 50;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 75
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 75)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 75;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 100
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 100)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 100;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 200
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 200)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 200;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 300
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 300)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 300;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 400
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 400)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 400;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 500
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 500)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 500;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 600
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 600)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 600;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 700
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 700)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 700;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 800
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 800)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 800;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 900
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 900)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 900;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 1'000
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 1'000)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 1'000;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 10'000
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 10'000)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 10'000;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 100'000
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 100'000)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 100'000;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * SQRT(number of conflicts)
     *      reduce interval: 1'000'000
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * SQRT(number of conflicts), reduce interval: 1'000'000)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 1'000'000;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::SQRT_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 2
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 2)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 2;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 25
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 25)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 25;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 50
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 50)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 50;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 75
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 75)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 75;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 100
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 100)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 100;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 200
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 200)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 200;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 300
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 300)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 300;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 400
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 400)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 400;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 500
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 500)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 500;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 600
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 600)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 600;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 700
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 700)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 700;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 800
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 800)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 800;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 900
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 900)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 900;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 1'000
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 1'000)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 1'000;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 10'000
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 10'000)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 10'000;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 100'000
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 100'000)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 100'000;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      reduce opt: reduceInt * LOG(number of conflicts)
     *      reduce interval: 1'000'000
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (reduce opt: reduceInt * LOG(number of conflicts), reduce interval: 1'000'000)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reduceIntCadical = 1'000'000;
        configuration.cadicalSolverConfiguration.reduceOptTypeCadical = CadicalReduceOptTypeEnum::LOG_OF_CONFLICTS;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      maximum number of preprocessing rounds for simplification: 0
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (maximum number of preprocessing rounds for simplification: 0)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.maximumNumberOfPreprocessingRoundsForSimplificationCadical = 0;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      maximum number of preprocessing rounds for simplification: 1
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (maximum number of preprocessing rounds for simplification: 1)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.maximumNumberOfPreprocessingRoundsForSimplificationCadical = 1;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      maximum number of preprocessing rounds for simplification: 2
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (maximum number of preprocessing rounds for simplification: 2)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.maximumNumberOfPreprocessingRoundsForSimplificationCadical = 2;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      maximum number of preprocessing rounds for simplification: 3
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (maximum number of preprocessing rounds for simplification: 3)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.maximumNumberOfPreprocessingRoundsForSimplificationCadical = 3;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      maximum number of preprocessing rounds for simplification: 4
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (maximum number of preprocessing rounds for simplification: 4)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.maximumNumberOfPreprocessingRoundsForSimplificationCadical = 4;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      maximum number of preprocessing rounds for simplification: 5
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (maximum number of preprocessing rounds for simplification: 5)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.maximumNumberOfPreprocessingRoundsForSimplificationCadical = 5;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      maximum number of preprocessing rounds for simplification: 6
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (maximum number of preprocessing rounds for simplification: 6)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.maximumNumberOfPreprocessingRoundsForSimplificationCadical = 6;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      maximum number of preprocessing rounds for simplification: 7
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (maximum number of preprocessing rounds for simplification: 7)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.maximumNumberOfPreprocessingRoundsForSimplificationCadical = 7;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      maximum number of preprocessing rounds for simplification: 8
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (maximum number of preprocessing rounds for simplification: 8)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.maximumNumberOfPreprocessingRoundsForSimplificationCadical = 8;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      maximum number of preprocessing rounds for simplification: 9
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (maximum number of preprocessing rounds for simplification: 9)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.maximumNumberOfPreprocessingRoundsForSimplificationCadical = 9;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      maximum number of preprocessing rounds for simplification: 10
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (maximum number of preprocessing rounds for simplification: 10)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.maximumNumberOfPreprocessingRoundsForSimplificationCadical = 10;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      stable reluctant doubling restarts: true
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (stable reluctant doubling restarts: true)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reluctantCadical = true;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      stable reluctant doubling restarts: false
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (stable reluctant doubling restarts: false)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.reluctantCadical = false;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      shrink conflict clause: no shrinking
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (shrink conflict clause: no shrinking)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.shrinkTypeCadical = CadicalShrinkTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      shrink conflict clause: shrinking using only binary reason clauses
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (shrink conflict clause: shrinking using only binary reason clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.shrinkTypeCadical = CadicalShrinkTypeEnum::BINARY_REASON_CLAUSES;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      shrink conflict clause: shrinking using all reason clauses
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (shrink conflict clause: shrinking using all reason clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.shrinkTypeCadical = CadicalShrinkTypeEnum::ALL_REASON_CLAUSES;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      shrink conflict clause: shrinking using all reason clauses, trying to minimize pulled-in lower-level literals
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (shrink conflict clause: shrinking using all reason clauses, trying to minimize pulled-in lower-level literals)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.shrinkTypeCadical = CadicalShrinkTypeEnum::ALL_REASON_CLAUSES_MINIMIZING_PULLED_IN;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      target phases: true
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (target phases: true)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.targetPhasesCadical = true;

        process(configuration, true);
    }

    /**
     * SAT solver - CaDiCaL
     *      target phases: false
     */
    TEST_CASE(" [Compiler::wDNNF] SAT solver - CaDiCaL (target phases: false)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.satSolverType = SatSolverTypeEnum::CADICAL;
        configuration.cadicalSolverConfiguration.targetPhasesCadical = false;

        process(configuration, true);
    }
    //endregion
    //endregion

    //region Decision heuristic
    /**
     * Decision heuristic - random
     */
    TEST_CASE(" [Compiler::wDNNF] decision heuristic - random", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::RANDOM;

        process(configuration, true);
    }

    /**
     * Decision heuristic - Jeroslow-Wang one-sided
     */
    TEST_CASE(" [Compiler::wDNNF] decision heuristic - Jeroslow-Wang one-sided", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::JEROSLOW_WANG_ONE_SIDED;

        process(configuration, true);
    }

    /**
     * Decision heuristic - Jeroslow-Wang two-sided
     */
    TEST_CASE(" [Compiler::wDNNF] decision heuristic - Jeroslow-Wang two-sided", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::JEROSLOW_WANG_TWO_SIDED;

        process(configuration, true);
    }

    /**
     * Decision heuristic - DLCS
     */
    TEST_CASE(" [Compiler::wDNNF] decision heuristic - DLCS", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

        process(configuration, true);
    }

    /**
     * Decision heuristic - DLIS
     */
    TEST_CASE(" [Compiler::wDNNF] decision heuristic - DLIS", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLIS;

        process(configuration, true);
    }

    /**
     * Decision heuristic - DLCS-DLIS
     */
    TEST_CASE(" [Compiler::wDNNF] decision heuristic - DLCS-DLIS", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS_DLIS;

        process(configuration, true);
    }

    /**
     * Decision heuristic - VSIDS
     */
    TEST_CASE(" [Compiler::wDNNF] decision heuristic - VSIDS", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::VSIDS;

        process(configuration, true);
    }

    /**
     * Decision heuristic - VSADS
     */
    TEST_CASE(" [Compiler::wDNNF] decision heuristic - VSADS", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::VSADS;

        configuration.vsadsDecisionHeuristicConfiguration.p = 0.5;
        configuration.vsadsDecisionHeuristicConfiguration.q = 1;

        process(configuration, true);
    }

    /**
     * Decision heuristic - EUPC
     */
    TEST_CASE(" [Compiler::wDNNF] decision heuristic - EUPC", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::EUPC;

        configuration.upcDecisionHeuristicConfiguration.constant = 100;

        process(configuration, true);
    }

    /**
     * Decision heuristic - AUPC
     */
    TEST_CASE(" [Compiler::wDNNF] decision heuristic - AUPC", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::AUPC;

        configuration.upcDecisionHeuristicConfiguration.approximateNumberOfVariables = static_cast<char32_t>(2);

        process(configuration, true);
    }
    //endregion

    //region Caching scheme (component cache)
    /**
     * Caching scheme (component cache)
     *      not enough variables for caching: 0
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (not enough variables for caching: 0)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.notEnoughVariablesForCaching = 0;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      not enough variables for caching: 2
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (not enough variables for caching: 2)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.notEnoughVariablesForCaching = 2;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      not enough variables for caching: 8
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (not enough variables for caching: 8)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.notEnoughVariablesForCaching = 8;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      not enough variables for caching: 32
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (not enough variables for caching: 32)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.notEnoughVariablesForCaching = 32;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      not enough variables for caching: 128
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (not enough variables for caching: 128)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.notEnoughVariablesForCaching = 128;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      not enough variables for caching: 512
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (not enough variables for caching: 512)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.notEnoughVariablesForCaching = 512;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      not enough variables for caching: 2'048
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (not enough variables for caching: 2'048)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.notEnoughVariablesForCaching = 2'048;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      not enough variables for caching: 8'192
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (not enough variables for caching: 8'192)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.notEnoughVariablesForCaching = 8'192;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      too many variables for caching: 0
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (too many variables for caching: 0)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.tooManyVariablesForCaching = 0;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      too many variables for caching: 2
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (too many variables for caching: 2)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.tooManyVariablesForCaching = 2;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      too many variables for caching: 8
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (too many variables for caching: 8)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.tooManyVariablesForCaching = 8;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      too many variables for caching: 32
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (too many variables for caching: 32)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.tooManyVariablesForCaching = 32;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      too many variables for caching: 128
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (too many variables for caching: 128)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.tooManyVariablesForCaching = 128;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      too many variables for caching: 512
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (too many variables for caching: 512)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.tooManyVariablesForCaching = 512;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      too many variables for caching: 2'048
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (too many variables for caching: 2'048)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.tooManyVariablesForCaching = 2'048;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache)
     *      too many variables for caching: 8'192
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) (too many variables for caching: 8'192)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cacheComponentCachingConfiguration.tooManyVariablesForCaching = 8'192;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - none", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - standard
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - standard", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - hybrid
     *      omit clause type: none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - hybrid (omit clause type: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - hybrid
     *      omit clause type: original binary clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - hybrid (omit clause type: original binary clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::ORIGINAL_BINARY;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - hybrid
     *      omit clause type: untouched clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - hybrid (omit clause type: untouched clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::UNTOUCHED;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - basic (omit clause type: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = false;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: none
     *      remove multi-occurrent clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - basic (omit clause type: none, remove multi-occurrent clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = true;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: original binary clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - basic (omit clause type: original binary clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = false;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::ORIGINAL_BINARY;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: original binary clauses
     *      remove multi-occurrent clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - basic (omit clause type: original binary clauses, remove multi-occurrent clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = true;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::ORIGINAL_BINARY;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: untouched clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - basic (omit clause type: untouched clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = false;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::UNTOUCHED;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: untouched clauses
     *      remove multi-occurrent clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - basic (omit clause type: untouched clauses, remove multi-occurrent clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = true;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::UNTOUCHED;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: none, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: none, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: none, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: none, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: none, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: none, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: none, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: none, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: none, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: none, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: none, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::wDNNF] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }
    //endregion

    //region Hypergraph partitioning
    //region KaHyPar
    /**
     * Hypergraph partitioning (KaHyPar)
     *      empty cut: allow
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (KaHyPar) (empty cut: allow)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::KAHYPAR;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (KaHyPar)
     *      empty cut: allow
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (KaHyPar) (empty cut: allow, variable subsumption)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::KAHYPAR;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (KaHyPar)
     *      empty cut: allow
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (KaHyPar) (empty cut: allow, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::KAHYPAR;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (KaHyPar)
     *      empty cut: allow
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (KaHyPar) (empty cut: allow, variable subsumption, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::KAHYPAR;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (KaHyPar)
     *      empty cut: deny
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (KaHyPar) (empty cut: deny)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::KAHYPAR;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (KaHyPar)
     *      empty cut: deny
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (KaHyPar) (empty cut: deny, variable subsumption)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::KAHYPAR;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (KaHyPar)
     *      empty cut: deny
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (KaHyPar) (empty cut: deny, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::KAHYPAR;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (KaHyPar)
     *      empty cut: deny
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (KaHyPar) (empty cut: deny, variable subsumption, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::KAHYPAR;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }
    //endregion

    //region PaToH, hMETIS
    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: allow
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: allow
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow, variable subsumption)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: allow
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: allow
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow, variable subsumption, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: deny
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: deny
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny, variable subsumption)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: deny
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: deny
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny, variable subsumption, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: allow
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: allow
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow, variable subsumption)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: allow
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: allow
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow, variable subsumption, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: deny
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: deny
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny, variable subsumption)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: deny
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: deny
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny, variable subsumption, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::PATOH_OR_HMETIS;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }
    //endregion

    //region Cara
    #if OPERATING_SYSTEM_MACOS || OPERATING_SYSTEM_LINUX
    /**
     * Hypergraph partitioning (Cara)
     *      empty cut: allow
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (Cara) (empty cut: allow)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::CARA;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (Cara)
     *      empty cut: allow
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (Cara) (empty cut: allow, variable subsumption)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::CARA;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (Cara)
     *      empty cut: allow
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (Cara) (empty cut: allow, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::CARA;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (Cara)
     *      empty cut: allow
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (Cara) (empty cut: allow, variable subsumption, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::CARA;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (Cara)
     *      empty cut: deny
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (Cara) (empty cut: deny)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::CARA;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (Cara)
     *      empty cut: deny
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (Cara) (empty cut: deny, variable subsumption)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::CARA;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (Cara)
     *      empty cut: deny
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (Cara) (empty cut: deny, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::CARA;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning (Cara)
     *      empty cut: deny
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (Cara) (empty cut: deny, variable subsumption, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.hypergraphPartitioningType = HypergraphPartitioningTypeEnum::CARA;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }
    #endif
    //endregion

    /**
     * Hypergraph partitioning
     *      hypergraph cut recomputation strategy: always
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (hypergraph cut recomputation strategy: always)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.hypergraphCutRecomputationStrategyType = HypergraphCutRecomputationStrategyTypeEnum::ALWAYS;

        process(configuration, true);
    }

    /**
     * Hypergraph partitioning
     *      hypergraph cut recomputation strategy: immense unit propagation - 0.2
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (hypergraph cut recomputation strategy: immense unit propagation - 0.2)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.percentageThresholdOfImmenseUnitPropagationHypergraphCutRecomputationStrategy = 0.2;
        configuration.hypergraphCutRecomputationStrategyType = HypergraphCutRecomputationStrategyTypeEnum::IMMENSE_UNIT_PROPAGATION;

        process(configuration, true);
    }

    /**
     * Hypergraph partitioning
     *      hypergraph cut recomputation strategy: immense unit propagation - 0.5
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (hypergraph cut recomputation strategy: immense unit propagation - 0.5)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.percentageThresholdOfImmenseUnitPropagationHypergraphCutRecomputationStrategy = 0.5;
        configuration.hypergraphCutRecomputationStrategyType = HypergraphCutRecomputationStrategyTypeEnum::IMMENSE_UNIT_PROPAGATION;

        process(configuration, true);
    }

    /**
     * Hypergraph partitioning
     *      hypergraph cut recomputation strategy: immense unit propagation - 0.8
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (hypergraph cut recomputation strategy: immense unit propagation - 0.8)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.percentageThresholdOfImmenseUnitPropagationHypergraphCutRecomputationStrategy = 0.8;
        configuration.hypergraphCutRecomputationStrategyType = HypergraphCutRecomputationStrategyTypeEnum::IMMENSE_UNIT_PROPAGATION;

        process(configuration, true);
    }

    /**
     * Hypergraph partitioning
     *      hypergraph cut recomputation strategy: when current formula is split
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (hypergraph cut recomputation strategy: when current formula is split)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.hypergraphCutRecomputationStrategyType = HypergraphCutRecomputationStrategyTypeEnum::WHEN_CURRENT_FORMULA_IS_SPLIT;

        process(configuration, true);
    }

    /**
     * Hypergraph partitioning
     *      hypergraph cut recomputation strategy: when current hypergraph cut is empty
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (hypergraph cut recomputation strategy: when current hypergraph cut is empty)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.hypergraphCutRecomputationStrategyType = HypergraphCutRecomputationStrategyTypeEnum::WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY;

        process(configuration, true);
    }

    /**
     * Hypergraph partitioning
     *      vertex weight type: none
     *      variable subsumption type: forward variable subsumption with mapping detection
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (vertex weight type: none, variable subsumption type: forward variable subsumption with mapping detection)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::NONE;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      vertex weight type: standard
     *      variable subsumption type: forward variable subsumption with mapping detection
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (vertex weight type: standard, variable subsumption type: forward variable subsumption with mapping detection)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::STANDARD;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      vertex weight type: clause length
     *      variable subsumption type: forward variable subsumption with mapping detection
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (vertex weight type: clause length, variable subsumption type: forward variable subsumption with mapping detection)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::CLAUSE_LENGTH;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      vertex weight type: none
     *      variable subsumption type: forward variable subsumption with mapping detection
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (vertex weight type: none, variable subsumption type: forward variable subsumption with mapping detection, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::NONE;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      vertex weight type: standard
     *      variable subsumption type: forward variable subsumption with mapping detection
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (vertex weight type: standard, variable subsumption type: forward variable subsumption with mapping detection, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::STANDARD;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      vertex weight type: clause length
     *      variable subsumption type: forward variable subsumption with mapping detection
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (vertex weight type: clause length, variable subsumption type: forward variable subsumption with mapping detection, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::CLAUSE_LENGTH;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      vertex weight type: none
     *      variable subsumption type: one-literal watching algorithm with mapping
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (vertex weight type: none, variable subsumption type: one-literal watching algorithm with mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::NONE;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      vertex weight type: standard
     *      variable subsumption type: one-literal watching algorithm with mapping
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (vertex weight type: standard, variable subsumption type: one-literal watching algorithm with mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::STANDARD;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      vertex weight type: clause length
     *      variable subsumption type: one-literal watching algorithm with mapping
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (vertex weight type: clause length, variable subsumption type: one-literal watching algorithm with mapping)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::CLAUSE_LENGTH;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      vertex weight type: none
     *      variable subsumption type: one-literal watching algorithm with mapping
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (vertex weight type: none, variable subsumption type: one-literal watching algorithm with mapping, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::NONE;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      vertex weight type: standard
     *      variable subsumption type: one-literal watching algorithm with mapping
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (vertex weight type: standard, variable subsumption type: one-literal watching algorithm with mapping, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::STANDARD;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      vertex weight type: clause length
     *      variable subsumption type: one-literal watching algorithm with mapping
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (vertex weight type: clause length, variable subsumption type: one-literal watching algorithm with mapping, equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::CLAUSE_LENGTH;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      variable subsumption type: none
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (variable subsumption type: none)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      equivalence simplification method
     *      implicit BCP variable order type: random
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (equivalence simplification method, implicit BCP variable order type: random)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::RANDOM;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      equivalence simplification method
     *      implicit BCP variable order type: variable index
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (equivalence simplification method, implicit BCP variable order type: variable index)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      equivalence simplification method
     *      implicit BCP variable order type: clause reduction heuristic (ascending)
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (ascending))", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_ASCENDING;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      equivalence simplification method
     *      implicit BCP variable order type: clause reduction heuristic (descending)
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (descending))", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_DESCENDING;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      variable subsumption
     *      equivalence simplification method
     *      implicit BCP variable order type: random
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (variable subsumption, equivalence simplification method, implicit BCP variable order type: random)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::RANDOM;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      variable subsumption
     *      equivalence simplification method
     *      implicit BCP variable order type: variable index
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (variable subsumption, equivalence simplification method, implicit BCP variable order type: variable index)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      variable subsumption
     *      equivalence simplification method
     *      implicit BCP variable order type: clause reduction heuristic (ascending)
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (variable subsumption, equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (ascending))", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_ASCENDING;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Hypergraph partitioning
     *      variable subsumption
     *      equivalence simplification method
     *      implicit BCP variable order type: clause reduction heuristic (descending)
     */
    TEST_CASE(" [Compiler::wDNNF] hypergraph partitioning (variable subsumption, equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (descending))", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_DESCENDING;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contiguousFormulaRepresentationConfiguration);
    }
    //endregion

    //region Number of models
    /**
     * Number of models
     */
    TEST_CASE(" [Compiler::wDNNF] number of models", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        processConfiguration(configuration, true, contiguousFormulaRepresentationConfiguration);
    }

    /**
     * Number of models (equivalence simplification method)
     */
    TEST_CASE(" [Compiler::wDNNF] number of models (equivalence simplification method)", "[Compiler::wDNNF] [.wDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;

        // Contiguous formula representation configuration
        ContiguousFormulaRepresentationConfigurationType contiguousFormulaRepresentationConfiguration;
        contiguousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        processConfiguration(configuration, true, contiguousFormulaRepresentationConfiguration);
    }
    //endregion
}   // namespace BellaTest::Compiler::wDNNF
