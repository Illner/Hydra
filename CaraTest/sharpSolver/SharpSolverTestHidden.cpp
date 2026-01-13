#include <string>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/catch.hpp"
#include "HydraTest/formulaInstance/CreateFormula.hpp"

#include "CaraTest/sharpSolver/SharpSolver.hpp"
#include "CaraTest/sharpSolver/SharpSolverTestResult.hpp"

namespace CaraTest::SharpSolver {

    /**
     * Default
     */
    TEST_CASE(" [SharpSolver] default", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();

        process(configuration, true);
    }

    //region Decision heuristic
    /**
     * Decision heuristic - random
     */
    TEST_CASE(" [SharpSolver] decision heuristic - random", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::RANDOM;

        process(configuration, true);
    }

    /**
     * Decision heuristic - Jeroslow-Wang one-sided
     */
    TEST_CASE(" [SharpSolver] decision heuristic - Jeroslow-Wang one-sided", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::JEROSLOW_WANG_ONE_SIDED;

        process(configuration, true);
    }

    /**
     * Decision heuristic - Jeroslow-Wang two-sided
     */
    TEST_CASE(" [SharpSolver] decision heuristic - Jeroslow-Wang two-sided", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::JEROSLOW_WANG_TWO_SIDED;

        process(configuration, true);
    }

    /**
     * Decision heuristic - DLCS
     */
    TEST_CASE(" [SharpSolver] decision heuristic - DLCS", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS;

        process(configuration, true);
    }

    /**
     * Decision heuristic - DLIS
     */
    TEST_CASE(" [SharpSolver] decision heuristic - DLIS", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLIS;

        process(configuration, true);
    }

    /**
     * Decision heuristic - DLCS-DLIS
     */
    TEST_CASE(" [SharpSolver] decision heuristic - DLCS-DLIS", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::DLCS_DLIS;

        process(configuration, true);
    }

    /**
     * Decision heuristic - VSIDS
     */
    TEST_CASE(" [SharpSolver] decision heuristic - VSIDS", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::VSIDS;

        process(configuration, true);
    }

    /**
     * Decision heuristic - VSADS
     */
    TEST_CASE(" [SharpSolver] decision heuristic - VSADS", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::VSADS;

        configuration.vsadsDecisionHeuristicConfiguration.p = 0.5;
        configuration.vsadsDecisionHeuristicConfiguration.q = 1;

        process(configuration, true);
    }

    /**
     * Decision heuristic - EUPC
     */
    TEST_CASE(" [SharpSolver] decision heuristic - EUPC", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::EUPC;

        configuration.upcDecisionHeuristicConfiguration.constant = 100;

        process(configuration, true);
    }

    /**
     * Decision heuristic - AUPC
     */
    TEST_CASE(" [SharpSolver] decision heuristic - AUPC", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.decisionHeuristicType = DecisionHeuristicTypeEnum::AUPC;

        configuration.upcDecisionHeuristicConfiguration.approximateNumberOfVariables = static_cast<char32_t>(2);

        process(configuration, true);
    }
    //endregion

    //region Caching scheme (component cache)
    /**
     * Caching scheme (component cache) - none
     */
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - none", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::NONE;

        process(configuration, false);
    }

    /**
     * Caching scheme (component cache) - standard
     */
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - standard", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::STANDARD;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - hybrid
     *      omit clause type: none
     */
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - hybrid (omit clause type: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - hybrid
     *      omit clause type: original binary clauses
     */
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - hybrid (omit clause type: original binary clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::ORIGINAL_BINARY;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - hybrid
     *      omit clause type: untouched clauses
     */
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - hybrid (omit clause type: untouched clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::UNTOUCHED;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: none
     */
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - basic (omit clause type: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - basic (omit clause type: none, remove multi-occurrent clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = true;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: original binary clauses
     */
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - basic (omit clause type: original binary clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - basic (omit clause type: original binary clauses, remove multi-occurrent clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.cachingSchemeComponentCachingType = CachingSchemeTypeEnum::BASIC;

        configuration.basicCachingSchemeComponentCachingConfiguration.removeMultiOccurrentClauses = true;
        configuration.basicCachingSchemeComponentCachingConfiguration.omitClauseType = OmitClauseTypeEnum::ORIGINAL_BINARY;

        process(configuration, true);
    }

    /**
     * Caching scheme (component cache) - basic
     *      omit clause type: untouched clauses
     */
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - basic (omit clause type: untouched clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - basic (omit clause type: untouched clauses, remove multi-occurrent clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (component cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - none", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - standard
     */
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - standard", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::STANDARD;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - hybrid
     *      omit clause type: none
     */
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - hybrid (omit clause type: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeHypergraphCutCachingConfiguration.omitClauseType = OmitClauseTypeEnum::NONE;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - hybrid
     *      omit clause type: original binary clauses
     */
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - hybrid (omit clause type: original binary clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeHypergraphCutCachingConfiguration.omitClauseType = OmitClauseTypeEnum::ORIGINAL_BINARY;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - hybrid
     *      omit clause type: untouched clauses
     */
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - hybrid (omit clause type: untouched clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.cachingSchemeHypergraphCutCachingType = CachingSchemeTypeEnum::HYBRID;

        configuration.hybridCachingSchemeHypergraphCutCachingConfiguration.omitClauseType = OmitClauseTypeEnum::UNTOUCHED;

        process(configuration, true);
    }

    /**
     * Caching scheme (hypergraph cut cache) - basic
     *      omit clause type: none
     */
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - basic (omit clause type: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - basic (omit clause type: none, remove multi-occurrent clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 3, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 3, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 4, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 4, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 5, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 5, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 6, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 6, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 7, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 7, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 8, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 8, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 9, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 9, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 10, preprocessing: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 10, preprocessing: none, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 3, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 4, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 5, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 6, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 7, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 8, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 9, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 10, preprocessing: not duplicate clauses, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: backward subsumption detection - intersection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: forward subsumption detection, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 0, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 1, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] caching scheme (hypergraph cut cache) - Cara (number of sample moments: 2, preprocessing: not subsumed clauses, subsumption type: one-literal watching algorithm, variable to variable mapping, discard invalid cache records)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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

    //region Partitioning hypergraph
    //region KaHyPar
    /**
     * Partitioning hypergraph (KaHyPar)
     *      empty cut: allow
     */
    TEST_CASE(" [SharpSolver] partitioning hypergraph (KaHyPar) (empty cut: allow)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (KaHyPar) (empty cut: allow, variable subsumption)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (KaHyPar) (empty cut: allow, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (KaHyPar) (empty cut: allow, variable subsumption, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (KaHyPar) (empty cut: deny)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (KaHyPar) (empty cut: deny, variable subsumption)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (KaHyPar) (empty cut: deny, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (KaHyPar) (empty cut: deny, variable subsumption, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow, variable subsumption)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: allow, variable subsumption, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny, variable subsumption)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: allow, singleton hyperedge: deny, variable subsumption, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow, variable subsumption)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: allow, variable subsumption, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny, variable subsumption)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (" + PATOH_HMETIS_TEST_NAME + ") (empty cut: deny, singleton hyperedge: deny, variable subsumption, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (Cara) (empty cut: allow)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (Cara) (empty cut: allow, variable subsumption)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (Cara) (empty cut: allow, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (Cara) (empty cut: allow, variable subsumption, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (Cara) (empty cut: deny)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (Cara) (empty cut: deny, variable subsumption)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (Cara) (empty cut: deny, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (Cara) (empty cut: deny, variable subsumption, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (recomputing hypergraph cut: always)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::ALWAYS;

        process(configuration, true);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: immense unit propagation - 0.2
     */
    TEST_CASE(" [SharpSolver] partitioning hypergraph (recomputing hypergraph cut: immense unit propagation - 0.2)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.percentageThresholdOfImmenseUnitPropagationRecomputingHypergraphCut = 0.2;
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION;

        process(configuration, true);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: immense unit propagation - 0.5
     */
    TEST_CASE(" [SharpSolver] partitioning hypergraph (recomputing hypergraph cut: immense unit propagation - 0.5)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.percentageThresholdOfImmenseUnitPropagationRecomputingHypergraphCut = 0.5;
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION;

        process(configuration, true);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: immense unit propagation - 0.8
     */
    TEST_CASE(" [SharpSolver] partitioning hypergraph (recomputing hypergraph cut: immense unit propagation - 0.8)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.percentageThresholdOfImmenseUnitPropagationRecomputingHypergraphCut = 0.8;
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::IMMENSE_UNIT_PROPAGATION;

        process(configuration, true);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: when current formula is split
     */
    TEST_CASE(" [SharpSolver] partitioning hypergraph (recomputing hypergraph cut: when current formula is split)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_FORMULA_IS_SPLIT;

        process(configuration, true);
    }

    /**
     * Partitioning hypergraph
     *      recomputing hypergraph cut: when current hypergraph cut is empty
     */
    TEST_CASE(" [SharpSolver] partitioning hypergraph (recomputing hypergraph cut: when current hypergraph cut is empty)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.recomputingHypergraphCutType = RecomputingHypergraphCutTypeEnum::WHEN_CURRENT_HYPERGRAPH_CUT_IS_EMPTY;

        process(configuration, true);
    }

    /**
     * Partitioning hypergraph
     *      vertex weight type: none
     *      variable subsumption type: forward variable subsumption with mapping detection
     */
    TEST_CASE(" [SharpSolver] partitioning hypergraph (vertex weight type: none, variable subsumption type: forward variable subsumption with mapping detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (vertex weight type: standard, variable subsumption type: forward variable subsumption with mapping detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (vertex weight type: clause length, variable subsumption type: forward variable subsumption with mapping detection)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (vertex weight type: none, variable subsumption type: forward variable subsumption with mapping detection, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (vertex weight type: standard, variable subsumption type: forward variable subsumption with mapping detection, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (vertex weight type: clause length, variable subsumption type: forward variable subsumption with mapping detection, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (vertex weight type: none, variable subsumption type: one-literal watching algorithm with mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (vertex weight type: standard, variable subsumption type: one-literal watching algorithm with mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (vertex weight type: clause length, variable subsumption type: one-literal watching algorithm with mapping)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (vertex weight type: none, variable subsumption type: one-literal watching algorithm with mapping, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (vertex weight type: standard, variable subsumption type: one-literal watching algorithm with mapping, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (vertex weight type: clause length, variable subsumption type: one-literal watching algorithm with mapping, equivalence simplification method)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (variable subsumption type: none)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (equivalence simplification method, implicit BCP variable order type: random)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (equivalence simplification method, implicit BCP variable order type: variable index)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (ascending))", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (descending))", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (variable subsumption, equivalence simplification method, implicit BCP variable order type: random)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (variable subsumption, equivalence simplification method, implicit BCP variable order type: variable index)", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (variable subsumption, equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (ascending))", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
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
    TEST_CASE(" [SharpSolver] partitioning hypergraph (variable subsumption, equivalence simplification method, implicit BCP variable order type: clause reduction heuristic (descending))", "[SharpSolver] [.Cara]") {
        SharpSolverConfigurationType configuration = createDefaultSharpSolverConfiguration();
        configuration.useEquivalenceSimplificationMethod = true;
        configuration.implicitBcpVariableOrderType = ImplicitBcpVariableOrderTypeEnum::CLAUSE_REDUCTION_HEURISTIC_DESCENDING;

        // Contagious formula representation configuration
        ContagiousFormulaRepresentationConfigurationType contagiousFormulaRepresentationConfiguration;
        contagiousFormulaRepresentationConfiguration.variableSubsumptionWithMappingType = VariableSubsumptionWithMappingTypeEnum::ONE_LITERAL_WATCHING_ALGORITHM_WITH_MAPPING;

        process(configuration, true, contagiousFormulaRepresentationConfiguration);
    }
    //endregion
}   // namespace CaraTest::SharpSolver
