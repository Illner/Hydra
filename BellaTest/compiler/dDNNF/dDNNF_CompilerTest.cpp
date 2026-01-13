#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/formulaInstance/CreateFormula.hpp"

#include "BellaTest/compiler/dDNNF/dDNNF_Compiler.hpp"
#include "BellaTest/compiler/dDNNF/dDNNF_CompilerTestResult.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "BellaTest/compiler/enums/CacheSizeTypeEnum.hpp"

namespace BellaTest::Compiler::dDNNF {

    /**
     * Empty formula
     */
    TEST_CASE("[Compiler::dDNNF] empty formula", "[Compiler::dDNNF]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          dDnnfCompilerEmptyFormulaResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = HydraTest::FormulaInstance::createEmptyFormula<VarT, LiteralT, ClauseIdT>();

            CompilerConfigurationType compilerConfiguration = createDefaultCompilerConfiguration();
            compilerConfiguration.circuitType = CircuitTypeEnum::d_DNNF;
            compilerConfiguration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

            compileAndPrintCircuit(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Unsatisfiable formula
     */
    TEST_CASE("[Compiler::dDNNF] unsatisfiable formula", "[Compiler::dDNNF]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          dDnnfCompilerUnsatisfiableFormulaResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = HydraTest::FormulaInstance::createUnsatisfiableFormula<VarT, LiteralT, ClauseIdT>();

            CompilerConfigurationType compilerConfiguration = createDefaultCompilerConfiguration();
            compilerConfiguration.circuitType = CircuitTypeEnum::d_DNNF;
            compilerConfiguration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

            compileAndPrintCircuit(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One unit clause
     */
    TEST_CASE("[Compiler::dDNNF] one unit clause", "[Compiler::dDNNF]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          dDnnfCompilerOneUnitClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = HydraTest::FormulaInstance::createFormulaOneUnitClause<VarT, LiteralT, ClauseIdT>();

            CompilerConfigurationType compilerConfiguration = createDefaultCompilerConfiguration();
            compilerConfiguration.circuitType = CircuitTypeEnum::d_DNNF;
            compilerConfiguration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

            compileAndPrintCircuit(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One clause
     */
    TEST_CASE("[Compiler::dDNNF] one clause", "[Compiler::dDNNF]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          dDnnfCompilerOneClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = HydraTest::FormulaInstance::createFormulaOneClause<VarT, LiteralT, ClauseIdT>();

            CompilerConfigurationType compilerConfiguration = createDefaultCompilerConfiguration();
            compilerConfiguration.circuitType = CircuitTypeEnum::d_DNNF;
            compilerConfiguration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

            compileAndPrintCircuit(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * One clause (smooth)
     */
    TEST_CASE("[Compiler::dDNNF] one clause (smooth)", "[Compiler::dDNNF]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          dDnnfCompilerOneClauseSmoothResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = HydraTest::FormulaInstance::createFormulaOneClause<VarT, LiteralT, ClauseIdT>();

            CompilerConfigurationType compilerConfiguration = createDefaultCompilerConfiguration();
            compilerConfiguration.circuitType = CircuitTypeEnum::sd_DNNF;
            compilerConfiguration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

            compileAndPrintCircuit(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Free variables
     */
    TEST_CASE("[Compiler::dDNNF] free variables", "[Compiler::dDNNF]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          dDnnfCompilerFreeVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = HydraTest::FormulaInstance::createFormulaFreeVariables<VarT, LiteralT, ClauseIdT>();

            CompilerConfigurationType compilerConfiguration = createDefaultCompilerConfiguration();
            compilerConfiguration.circuitType = CircuitTypeEnum::d_DNNF;
            compilerConfiguration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

            compileAndPrintCircuit(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Free variables (smooth)
     */
    TEST_CASE("[Compiler::dDNNF] free variables (smooth)", "[Compiler::dDNNF]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          dDnnfCompilerFreeVariablesSmoothResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = HydraTest::FormulaInstance::createFormulaFreeVariables<VarT, LiteralT, ClauseIdT>();

            CompilerConfigurationType compilerConfiguration = createDefaultCompilerConfiguration();
            compilerConfiguration.circuitType = CircuitTypeEnum::sd_DNNF;
            compilerConfiguration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

            compileAndPrintCircuit(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Free variables in decision node
     */
    TEST_CASE("[Compiler::dDNNF] free variables in decision node", "[Compiler::dDNNF]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          dDnnfCompilerFreeVariablesInDecisionNodeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = HydraTest::FormulaInstance::createFormulaForFreeVariablesInDecisionNode<VarT, LiteralT, ClauseIdT>();

            CompilerConfigurationType compilerConfiguration = createDefaultCompilerConfiguration();
            compilerConfiguration.circuitType = CircuitTypeEnum::d_DNNF;
            compilerConfiguration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

            compileAndPrintCircuit(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Free variables in decision node (smooth)
     */
    TEST_CASE("[Compiler::dDNNF] free variables in decision node (smooth)", "[Compiler::dDNNF]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          dDnnfCompilerFreeVariablesInDecisionNodeSmoothResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = HydraTest::FormulaInstance::createFormulaForFreeVariablesInDecisionNode<VarT, LiteralT, ClauseIdT>();

            CompilerConfigurationType compilerConfiguration = createDefaultCompilerConfiguration();
            compilerConfiguration.circuitType = CircuitTypeEnum::sd_DNNF;
            compilerConfiguration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

            compileAndPrintCircuit(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Two disjoint clauses
     */
    TEST_CASE("[Compiler::dDNNF] two disjoint clauses", "[Compiler::dDNNF]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          dDnnfCompilerTwoDisjointClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = HydraTest::FormulaInstance::createFormulaTwoDisjointClauses<VarT, LiteralT, ClauseIdT>();

            CompilerConfigurationType compilerConfiguration = createDefaultCompilerConfiguration();
            compilerConfiguration.circuitType = CircuitTypeEnum::d_DNNF;
            compilerConfiguration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

            compileAndPrintCircuit(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Two disjoint clauses (smooth)
     */
    TEST_CASE("[Compiler::dDNNF] two disjoint clauses (smooth)", "[Compiler::dDNNF]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          dDnnfCompilerTwoDisjointClausesSmoothResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = HydraTest::FormulaInstance::createFormulaTwoDisjointClauses<VarT, LiteralT, ClauseIdT>();

            CompilerConfigurationType compilerConfiguration = createDefaultCompilerConfiguration();
            compilerConfiguration.circuitType = CircuitTypeEnum::sd_DNNF;
            compilerConfiguration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

            compileAndPrintCircuit(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Initially implied literals
     */
    TEST_CASE("[Compiler::dDNNF] initially implied literals", "[Compiler::dDNNF]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          dDnnfCompilerInitiallyImpliedLiteralsResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentationAbstractUniquePtr = HydraTest::FormulaInstance::createFormulaForInitiallyImpliedLiterals<VarT, LiteralT, ClauseIdT>();

            CompilerConfigurationType compilerConfiguration = createDefaultCompilerConfiguration();
            compilerConfiguration.circuitType = CircuitTypeEnum::d_DNNF;
            compilerConfiguration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

            compileAndPrintCircuit(std::move(formulaRepresentationAbstractUniquePtr), compilerConfiguration, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Default
     */
    TEST_CASE("[Compiler::dDNNF] default", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();

        process(configuration, false);
    }

    /**
     * Statistics
     */
    TEST_CASE("[Compiler::dDNNF] statistics", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::IGNORE, true);
    }

    /**
     * No statistics
     */
    TEST_CASE("[Compiler::dDNNF] no statistics", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::IGNORE, false);
    }

    //region Decision heuristic
    /**
     * Decision heuristic - random
     */
    TEST_CASE("[Compiler::dDNNF] decision heuristic - random", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::RANDOM;

        process(configuration, false);
    }

    /**
     * Decision heuristic - Jeroslow-Wang one-sided
     */
    TEST_CASE("[Compiler::dDNNF] decision heuristic - Jeroslow-Wang one-sided", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::JEROSLOW_WANG_ONE_SIDED;

        process(configuration, false);
    }

    /**
     * Decision heuristic - Jeroslow-Wang two-sided
     */
    TEST_CASE("[Compiler::dDNNF] decision heuristic - Jeroslow-Wang two-sided", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::JEROSLOW_WANG_TWO_SIDED;

        process(configuration, false);
    }

    /**
     * Decision heuristic - DLCS
     */
    TEST_CASE("[Compiler::dDNNF] decision heuristic - DLCS", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

        process(configuration, false);
    }

    /**
     * Decision heuristic - DLIS
     */
    TEST_CASE("[Compiler::dDNNF] decision heuristic - DLIS", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLIS;

        process(configuration, false);
    }

    /**
     * Decision heuristic - DLCS-DLIS
     */
    TEST_CASE("[Compiler::dDNNF] decision heuristic - DLCS-DLIS", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS_DLIS;

        process(configuration, false);
    }

    /**
     * Decision heuristic - VSIDS
     */
    TEST_CASE("[Compiler::dDNNF] decision heuristic - VSIDS", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::VSIDS;

        process(configuration, false);
    }

    /**
     * Decision heuristic - VSADS
     */
    TEST_CASE("[Compiler::dDNNF] decision heuristic - VSADS", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::VSADS;

        configuration.vsadsDecisionHeuristicConfiguration.p = 0.5;
        configuration.vsadsDecisionHeuristicConfiguration.q = 1;

        process(configuration, false);
    }

    /**
     * Decision heuristic - EUPC
     */
    TEST_CASE("[Compiler::dDNNF] decision heuristic - EUPC", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::EUPC;

        configuration.upcDecisionHeuristicConfiguration.constant = 100;

        process(configuration, false);
    }

    /**
     * Decision heuristic - AUPC
     */
    TEST_CASE("[Compiler::dDNNF] decision heuristic - AUPC", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::AUPC;

        configuration.upcDecisionHeuristicConfiguration.approximateNumberOfVariables = static_cast<char32_t>(2);

        process(configuration, false);
    }
    //endregion

    //region Caching scheme (component cache)
    /**
     * Caching scheme (component cache) - none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - none", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - standard
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - standard", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - hybrid
     *      omit clause type: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - hybrid (omit clause type: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - hybrid
     *      omit clause type: original binary clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - hybrid (omit clause type: original binary clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::ORIGINAL_BINARY;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - hybrid
     *      omit clause type: untouched clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - hybrid (omit clause type: untouched clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::UNTOUCHED;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - basic (omit clause type: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = false;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: none
     *      remove multi-occurrent clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - basic (omit clause type: none, remove multi-occurrent clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = true;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: original binary clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - basic (omit clause type: original binary clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = false;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::ORIGINAL_BINARY;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: original binary clauses
     *      remove multi-occurrent clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - basic (omit clause type: original binary clauses, remove multi-occurrent clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = true;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::ORIGINAL_BINARY;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: untouched clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - basic (omit clause type: untouched clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = false;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::UNTOUCHED;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: untouched clauses
     *      remove multi-occurrent clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - basic (omit clause type: untouched clauses, remove multi-occurrent clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = true;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::UNTOUCHED;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }
    //endregion

    //region Caching scheme (hypergraph cut cache)
    /**
     * Caching scheme (hypergraph cut cache) - none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - none", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - standard
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - standard", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - hybrid
     *      omit clause type: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - hybrid (omit clause type: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeHypergraphCutCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - hybrid
     *      omit clause type: original binary clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - hybrid (omit clause type: original binary clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeHypergraphCutCachingConfiguration.omitClauseType = OmitClauseTypeEnum::ORIGINAL_BINARY;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - hybrid
     *      omit clause type: untouched clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - hybrid (omit clause type: untouched clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeHypergraphCutCachingConfiguration.omitClauseType = OmitClauseTypeEnum::UNTOUCHED;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - basic
     *      omit clause type: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - basic (omit clause type: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeHypergraphCutCachingConfiguration.removeMultiOccurrentClauses = false;
        configuration.basicCachingSchemeHypergraphCutCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - basic
     *      omit clause type: none
     *      remove multi-occurrent clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - basic (omit clause type: none, remove multi-occurrent clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeHypergraphCutCachingConfiguration.removeMultiOccurrentClauses = true;
        configuration.basicCachingSchemeHypergraphCutCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 3, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 3, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 4, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 4, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 5, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 5, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 6, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 6, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 7, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 7, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 8, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 8, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 9, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 9, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: none
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 10, preprocessing: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 10, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, false);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE("[Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }
    //endregion

    //region Cache cleaning strategy (component cache)
    /**
     * Cache cleaning strategy (component cache) - none
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - none", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Cache cleaning strategy (component cache) - none (mapping)
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - none (mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }
    //endregion

    //region Cache cleaning strategy (hypergraph cut cache)
    /**
     * Cache cleaning strategy (hypergraph cut cache) - none
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - none", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - none (mapping)
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - none (mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium, reset time)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE("[Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, false, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }
    //endregion

    //region Partitioning hypergraph
    //region KaHyPar
    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: allow
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: allow)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: allow
     *      variable subsumption
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: allow, variable subsumption)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: allow
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: allow, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: allow
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: allow, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: deny
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: deny)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: deny
     *      variable subsumption
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: deny, variable subsumption)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: deny
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: deny, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: deny
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: deny, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }
    //endregion

    //region PaToH, hMETIS
    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: allow
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: allow
     *      variable subsumption
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow, variable subsumption)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: allow
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: allow
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: deny
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: deny
     *      variable subsumption
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny, variable subsumption)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: deny
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: deny
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: allow
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: allow
     *      variable subsumption
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow, variable subsumption)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: allow
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: allow
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: deny
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: deny
     *      variable subsumption
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny, variable subsumption)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: deny
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: deny
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }
    //endregion

    //region Cara
    #if OPERATING_SYSTEM_MACOS || OPERATING_SYSTEM_LINUX
    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: allow
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: allow)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: allow
     *      variable subsumption
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: allow, variable subsumption)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: allow
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: allow, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: allow
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: allow, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: deny
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: deny)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: deny
     *      variable subsumption
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: deny, variable subsumption)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: deny
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: deny, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: deny
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: deny, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }
    #endif
    //endregion

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: always
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (recomputing hypergraph cut: always)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::ALWAYS;

        process(configuration, false);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: immense unit propagation - 0.2
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (recomputing hypergraph cut: immense unit propagation - 0.2)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.percentageThresholdOfImmenseUnitPropagationRecomputingHypergraphCut = 0.2;
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION;

        process(configuration, false);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: immense unit propagation - 0.5
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (recomputing hypergraph cut: immense unit propagation - 0.5)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.percentageThresholdOfImmenseUnitPropagationRecomputingHypergraphCut = 0.5;
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION;

        process(configuration, false);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: immense unit propagation - 0.8
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (recomputing hypergraph cut: immense unit propagation - 0.8)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.percentageThresholdOfImmenseUnitPropagationRecomputingHypergraphCut = 0.8;
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION;

        process(configuration, false);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: when current formula is split
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (recomputing hypergraph cut: when current formula is split)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_FORMULA_IS_SPLIT;

        process(configuration, false);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: when current hypergraph cut is empty
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (recomputing hypergraph cut: when current hypergraph cut is empty)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY;

        process(configuration, false);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: none
     *      variable subsumption type: forward variable subsumption with mapping detection
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (vertex weight type: none, variable subsumption type: forward variable subsumption with mapping detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::NONE;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: standard
     *      variable subsumption type: forward variable subsumption with mapping detection
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (vertex weight type: standard, variable subsumption type: forward variable subsumption with mapping detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::STANDARD;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: clause length
     *      variable subsumption type: forward variable subsumption with mapping detection
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (vertex weight type: clause length, variable subsumption type: forward variable subsumption with mapping detection)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::CLAUSE_LENGTH;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: none
     *      variable subsumption type: forward variable subsumption with mapping detection
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (vertex weight type: none, variable subsumption type: forward variable subsumption with mapping detection, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::NONE;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: standard
     *      variable subsumption type: forward variable subsumption with mapping detection
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (vertex weight type: standard, variable subsumption type: forward variable subsumption with mapping detection, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::STANDARD;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: clause length
     *      variable subsumption type: forward variable subsumption with mapping detection
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (vertex weight type: clause length, variable subsumption type: forward variable subsumption with mapping detection, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::CLAUSE_LENGTH;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: none
     *      variable subsumption type: one-literal watching algorithm with mapping
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (vertex weight type: none, variable subsumption type: one-literal watching algorithm with mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::NONE;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: standard
     *      variable subsumption type: one-literal watching algorithm with mapping
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (vertex weight type: standard, variable subsumption type: one-literal watching algorithm with mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::STANDARD;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: clause length
     *      variable subsumption type: one-literal watching algorithm with mapping
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (vertex weight type: clause length, variable subsumption type: one-literal watching algorithm with mapping)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::CLAUSE_LENGTH;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: none
     *      variable subsumption type: one-literal watching algorithm with mapping
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (vertex weight type: none, variable subsumption type: one-literal watching algorithm with mapping, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::NONE;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: standard
     *      variable subsumption type: one-literal watching algorithm with mapping
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (vertex weight type: standard, variable subsumption type: one-literal watching algorithm with mapping, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::STANDARD;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: clause length
     *      variable subsumption type: one-literal watching algorithm with mapping
     *      equivalence simplification method
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (vertex weight type: clause length, variable subsumption type: one-literal watching algorithm with mapping, equivalence simplification method)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::CLAUSE_LENGTH;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      variable subsumption type: none
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (variable subsumption type: none)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      equivalence simplification method
     *      implicit BCP variable order type: random
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (equivalence simplification method, implicit BCP variable order type: random)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::RANDOM;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      equivalence simplification method
     *      implicit BCP variable order type: variable index
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (equivalence simplification method, implicit BCP variable order type: variable index)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      equivalence simplification method
     *      implicit BCP variable order type: clause reduction heuristic (ascending)
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (ascending))", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_ASCENDING;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      equivalence simplification method
     *      implicit BCP variable order type: clause reduction heuristic (descending)
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (descending))", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_DESCENDING;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      variable subsumption
     *      equivalence simplification method
     *      implicit BCP variable order type: random
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (variable subsumption, equivalence simplification method, implicit BCP variable order type: random)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::RANDOM;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      variable subsumption
     *      equivalence simplification method
     *      implicit BCP variable order type: variable index
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (variable subsumption, equivalence simplification method, implicit BCP variable order type: variable index)", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      variable subsumption
     *      equivalence simplification method
     *      implicit BCP variable order type: clause reduction heuristic (ascending)
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (variable subsumption, equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (ascending))", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_ASCENDING;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      variable subsumption
     *      equivalence simplification method
     *      implicit BCP variable order type: clause reduction heuristic (descending)
     */
    TEST_CASE("[Compiler::dDNNF] partitioning hypergraph (variable subsumption, equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (descending))", "[Compiler::dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_DESCENDING;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, false, contagiousFormulaRepresentationConfiguration);
    }
    //endregion
}   // namespace BellaTest::Compiler::dDNNF
