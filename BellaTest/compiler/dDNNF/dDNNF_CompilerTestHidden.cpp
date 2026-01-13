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
     * Default
     */
    TEST_CASE(" [Compiler::dDNNF] default", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();

        process(configuration, true);
    }

    /**
     * Statistics
     */
    TEST_CASE(" [Compiler::dDNNF] statistics", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::IGNORE, true);
    }

    /**
     * No statistics
     */
    TEST_CASE(" [Compiler::dDNNF] no statistics", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::IGNORE, false);
    }

    //region Decision heuristic
    /**
     * Decision heuristic - random
     */
    TEST_CASE(" [Compiler::dDNNF] decision heuristic - random", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::RANDOM;

        process(configuration, true);
    }

    /**
     * Decision heuristic - Jeroslow-Wang one-sided
     */
    TEST_CASE(" [Compiler::dDNNF] decision heuristic - Jeroslow-Wang one-sided", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::JEROSLOW_WANG_ONE_SIDED;

        process(configuration, true);
    }

    /**
     * Decision heuristic - Jeroslow-Wang two-sided
     */
    TEST_CASE(" [Compiler::dDNNF] decision heuristic - Jeroslow-Wang two-sided", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::JEROSLOW_WANG_TWO_SIDED;

        process(configuration, true);
    }

    /**
     * Decision heuristic - DLCS
     */
    TEST_CASE(" [Compiler::dDNNF] decision heuristic - DLCS", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

        process(configuration, true);
    }

    /**
     * Decision heuristic - DLIS
     */
    TEST_CASE(" [Compiler::dDNNF] decision heuristic - DLIS", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLIS;

        process(configuration, true);
    }

    /**
     * Decision heuristic - DLCS-DLIS
     */
    TEST_CASE(" [Compiler::dDNNF] decision heuristic - DLCS-DLIS", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS_DLIS;

        process(configuration, true);
    }

    /**
     * Decision heuristic - VSIDS
     */
    TEST_CASE(" [Compiler::dDNNF] decision heuristic - VSIDS", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::VSIDS;

        process(configuration, true);
    }

    /**
     * Decision heuristic - VSADS
     */
    TEST_CASE(" [Compiler::dDNNF] decision heuristic - VSADS", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::VSADS;

        configuration.vsadsDecisionHeuristicConfiguration.p = 0.5;
        configuration.vsadsDecisionHeuristicConfiguration.q = 1;

        process(configuration, true);
    }

    /**
     * Decision heuristic - EUPC
     */
    TEST_CASE(" [Compiler::dDNNF] decision heuristic - EUPC", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::EUPC;

        configuration.upcDecisionHeuristicConfiguration.constant = 100;

        process(configuration, true);
    }

    /**
     * Decision heuristic - AUPC
     */
    TEST_CASE(" [Compiler::dDNNF] decision heuristic - AUPC", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::AUPC;

        configuration.upcDecisionHeuristicConfiguration.approximateNumberOfVariables = static_cast<char32_t>(2);

        process(configuration, true);
    }
    //endregion

    //region Caching scheme (component cache)
    /**
     * Caching scheme (component cache) - none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - none", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - standard
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - standard", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - hybrid
     *      omit clause type: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - hybrid (omit clause type: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - hybrid
     *      omit clause type: original binary clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - hybrid (omit clause type: original binary clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::ORIGINAL_BINARY;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - hybrid
     *      omit clause type: untouched clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - hybrid (omit clause type: untouched clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::UNTOUCHED;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - basic (omit clause type: none)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - basic (omit clause type: none, remove multi-occurrent clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - basic (omit clause type: original binary clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - basic (omit clause type: original binary clauses, remove multi-occurrent clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - basic (omit clause type: untouched clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - basic (omit clause type: untouched clauses, remove multi-occurrent clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
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
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (component cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeComponentCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeComponentCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeComponentCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }
    //endregion

    //region Caching scheme (hypergraph cut cache)
    /**
     * Caching scheme (hypergraph cut cache) - none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - none", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - standard
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - standard", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - hybrid
     *      omit clause type: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - hybrid (omit clause type: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeHypergraphCutCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - hybrid
     *      omit clause type: original binary clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - hybrid (omit clause type: original binary clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeHypergraphCutCachingConfiguration.omitClauseType = OmitClauseTypeEnum::ORIGINAL_BINARY;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - hybrid
     *      omit clause type: untouched clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - hybrid (omit clause type: untouched clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeHypergraphCutCachingConfiguration.omitClauseType = OmitClauseTypeEnum::UNTOUCHED;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - basic
     *      omit clause type: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - basic (omit clause type: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeHypergraphCutCachingConfiguration.removeMultiOccurrentClauses = false;
        configuration.basicCachingSchemeHypergraphCutCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - basic
     *      omit clause type: none
     *      remove multi-occurrent clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - basic (omit clause type: none, remove multi-occurrent clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeHypergraphCutCachingConfiguration.removeMultiOccurrentClauses = true;
        configuration.basicCachingSchemeHypergraphCutCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 3, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 3, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 4, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 4, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 5, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 5, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 6, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 6, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 7, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 7, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 8, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 8, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 9, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 9, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: none
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 10, preprocessing: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: none
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 10, preprocessing: none, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 3
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 3;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 4
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 4;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 5
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 5;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 6
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 6;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 7
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 7;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 8
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 8;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 9
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 9;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: not duplicate clauses
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 10
     *      preprocessing: not duplicate clauses
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 10;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_DUPLICATE_CLAUSES;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: backward subsumption detection - intersection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::BACKWARD_SUBSUMPTION_DETECTION_INTERSECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: forward subsumption detection
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::FORWARD_SUBSUMPTION_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 0
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 0;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 1
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 1;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = true;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Caching scheme (hypergraph cut cache) - Cara
     *      number of sample moments: 2
     *      preprocessing: not subsumed clauses
     *      subsumption type: one-literal watching algorithm
     *      variable to variable mapping
     *      discard invalid cache records
     */
    TEST_CASE(" [Compiler::dDNNF] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;

        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.numberOfSampleMoments = 2;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.useVariableToLiteralMapping = false;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NOT_SUBSUMED_CLAUSES;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.discardInvalidCacheRecordsNotSubsumedClausesPreprocessing = true;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.subsumptionType = SubsumptionTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }
    //endregion

    //region Cache cleaning strategy (component cache)
    /**
     * Cache cleaning strategy (component cache) - none
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - none", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Cache cleaning strategy (component cache) - none (mapping)
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - none (mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (component cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (component cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeComponentCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyComponentCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyComponentCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }
    //endregion

    //region Cache cleaning strategy (hypergraph cut cache)
    /**
     * Cache cleaning strategy (hypergraph cut cache) - none
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - none", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - none (mapping)
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - none (mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: low
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: low, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::LOW_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 25
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 25, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 25;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 50
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 50, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 50;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 75
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 75, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 75;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     *      reset time
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium, reset time)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = false;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }

    /**
     * Cache cleaning strategy (hypergraph cut cache) - sharpSAT
     *      percentage of deleted entries: 100
     *      maximum cache size: medium
     *      reset time
     *      mapping
     */
    TEST_CASE(" [Compiler::dDNNF] cache cleaning strategy (hypergraph cut cache) - sharpSAT (percentage of deleted entries: 100, maximum cache size: medium, reset time, mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::CARA;
        configuration.caraCachingSchemeHypergraphCutCachingConfiguration.preprocessingType = PreprocessingTypeEnum::NONE;
        configuration.cacheCleaningStrategyHypergraphCutCachingType = CacheCleaningStrategyTypeEnum::SHARP_SAT;

        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.resetTime = true;
        configuration.sharpSatCacheCleaningStrategyHypergraphCutCachingConfiguration.percentageOfDeletedEntries = 100;

        process(configuration, true, ContagiousFormulaRepresentationConfigurationType(), CacheSizeTypeEnum::MEDIUM_MAPPING);
    }
    //endregion

    //region Partitioning hypergraph
    //region KaHyPar
    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: allow
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: allow)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: allow
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: allow, variable subsumption)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: allow
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: allow, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: allow
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: allow, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: deny
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: deny)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: deny
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: deny, variable subsumption)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: deny
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: deny, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: deny
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (KaHyPar) (empty cut: deny, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::KAHYPAR;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }
    //endregion

    //region PaToH, hMETIS
    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: allow
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: allow
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow, variable subsumption)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: allow
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: allow
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: deny
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: deny
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny, variable subsumption)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: deny
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: allow
     *      singleton hyperedge: deny
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: allow
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: allow
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow, variable subsumption)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: allow
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: allow
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = true;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: deny
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: deny
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny, variable subsumption)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: deny
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (PaToH, hMETIS)
     *      empty cut: deny
     *      singleton hyperedge: deny
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::PATOH_OR_HMETIS;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }
    //endregion

    //region Cara
    #if OPERATING_SYSTEM_MACOS || OPERATING_SYSTEM_LINUX
    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: allow
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: allow)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: allow
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: allow, variable subsumption)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: allow
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: allow, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: allow
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: allow, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = true;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: deny
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: deny)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: deny
     *      variable subsumption
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: deny, variable subsumption)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: deny
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: deny, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph (Cara)
     *      empty cut: deny
     *      variable subsumption
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (Cara) (empty cut: deny, variable subsumption, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.allowEmptyHypergraphCut = false;
        configuration.allowSingletonHyperedge = false;
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.partitioningHypergraphType = PartitioningHypergraphTypeEnum::CARA;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }
    #endif
    //endregion

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: always
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (recomputing hypergraph cut: always)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::ALWAYS;

        process(configuration, true);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: immense unit propagation - 0.2
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (recomputing hypergraph cut: immense unit propagation - 0.2)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.percentageThresholdOfImmenseUnitPropagationRecomputingHypergraphCut = 0.2;
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION;

        process(configuration, true);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: immense unit propagation - 0.5
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (recomputing hypergraph cut: immense unit propagation - 0.5)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.percentageThresholdOfImmenseUnitPropagationRecomputingHypergraphCut = 0.5;
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION;

        process(configuration, true);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: immense unit propagation - 0.8
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (recomputing hypergraph cut: immense unit propagation - 0.8)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.percentageThresholdOfImmenseUnitPropagationRecomputingHypergraphCut = 0.8;
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION;

        process(configuration, true);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: when current formula is split
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (recomputing hypergraph cut: when current formula is split)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_FORMULA_IS_SPLIT;

        process(configuration, true);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: when current hypergraph cut is empty
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (recomputing hypergraph cut: when current hypergraph cut is empty)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY;

        process(configuration, true);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: none
     *      variable subsumption type: forward variable subsumption with mapping detection
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (vertex weight type: none, variable subsumption type: forward variable subsumption with mapping detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::NONE;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: standard
     *      variable subsumption type: forward variable subsumption with mapping detection
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (vertex weight type: standard, variable subsumption type: forward variable subsumption with mapping detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::STANDARD;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: clause length
     *      variable subsumption type: forward variable subsumption with mapping detection
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (vertex weight type: clause length, variable subsumption type: forward variable subsumption with mapping detection)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::CLAUSE_LENGTH;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: none
     *      variable subsumption type: forward variable subsumption with mapping detection
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (vertex weight type: none, variable subsumption type: forward variable subsumption with mapping detection, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::NONE;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: standard
     *      variable subsumption type: forward variable subsumption with mapping detection
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (vertex weight type: standard, variable subsumption type: forward variable subsumption with mapping detection, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::STANDARD;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: clause length
     *      variable subsumption type: forward variable subsumption with mapping detection
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (vertex weight type: clause length, variable subsumption type: forward variable subsumption with mapping detection, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::CLAUSE_LENGTH;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::FORWARD_VARIABLE_SUBSUMPTION_WITH_MAPPING_DETECTION;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: none
     *      variable subsumption type: one-literal watching algorithm with mapping
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (vertex weight type: none, variable subsumption type: one-literal watching algorithm with mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::NONE;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: standard
     *      variable subsumption type: one-literal watching algorithm with mapping
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (vertex weight type: standard, variable subsumption type: one-literal watching algorithm with mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::STANDARD;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: clause length
     *      variable subsumption type: one-literal watching algorithm with mapping
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (vertex weight type: clause length, variable subsumption type: one-literal watching algorithm with mapping)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;
        configuration.vertexWeightType = VertexWeightTypeEnum::CLAUSE_LENGTH;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: none
     *      variable subsumption type: one-literal watching algorithm with mapping
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (vertex weight type: none, variable subsumption type: one-literal watching algorithm with mapping, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::NONE;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: standard
     *      variable subsumption type: one-literal watching algorithm with mapping
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (vertex weight type: standard, variable subsumption type: one-literal watching algorithm with mapping, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::STANDARD;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: clause length
     *      variable subsumption type: one-literal watching algorithm with mapping
     *      equivalence simplification method
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (vertex weight type: clause length, variable subsumption type: one-literal watching algorithm with mapping, equivalence simplification method)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.vertexWeightType = VertexWeightTypeEnum::CLAUSE_LENGTH;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      variable subsumption type: none
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (variable subsumption type: none)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = false;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      equivalence simplification method
     *      implicit BCP variable order type: random
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (equivalence simplification method, implicit BCP variable order type: random)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::RANDOM;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      equivalence simplification method
     *      implicit BCP variable order type: variable index
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (equivalence simplification method, implicit BCP variable order type: variable index)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      equivalence simplification method
     *      implicit BCP variable order type: clause reduction heuristic (ascending)
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (ascending))", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_ASCENDING;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      equivalence simplification method
     *      implicit BCP variable order type: clause reduction heuristic (descending)
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (descending))", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_DESCENDING;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::NONE;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      variable subsumption
     *      equivalence simplification method
     *      implicit BCP variable order type: random
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (variable subsumption, equivalence simplification method, implicit BCP variable order type: random)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::RANDOM;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      variable subsumption
     *      equivalence simplification method
     *      implicit BCP variable order type: variable index
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (variable subsumption, equivalence simplification method, implicit BCP variable order type: variable index)", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::VARIABLE_INDEX;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      variable subsumption
     *      equivalence simplification method
     *      implicit BCP variable order type: clause reduction heuristic (ascending)
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (variable subsumption, equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (ascending))", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_ASCENDING;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }

    /**
     * Partitioning hypergraph
     *      variable subsumption
     *      equivalence simplification method
     *      implicit BCP variable order type: clause reduction heuristic (descending)
     */
    TEST_CASE(" [Compiler::dDNNF] partitioning hypergraph (variable subsumption, equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (descending))", "[Compiler::dDNNF] [.dDNNF]") {
        CompilerConfigurationType configuration = createDefaultCompilerConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_DESCENDING;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }
    //endregion
}   // namespace BellaTest::Compiler::dDNNF
