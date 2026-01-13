#include <memory>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/cache/cachingScheme/CachingScheme.hpp"
#include "HydraTest/cache/cachingScheme/CreateFormula.hpp"
#include "HydraTest/cache/cachingScheme/basic/BasicCachingSchemeTestResult.hpp"
#include "HydraTest/catch.hpp"

#include "Hydra/cache/Cache.hpp"
#include "Hydra/cache/cachingScheme/basic/BasicCachingScheme.hpp"

#include "Hydra/cache/exceptions/CacheException.hpp"

#include "Hydra/cache/cachingScheme/enums/CachingSchemeTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/OmitClauseTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"

#include "Hydra/cache/cachingScheme/basic/BasicCachingScheme.tpp"

namespace HydraTest::Cache::CachingScheme::Basic {

    //region Types
    using VarT = HydraTest::Cache::CachingScheme::VarT;
    using LiteralT = HydraTest::Cache::CachingScheme::LiteralT;
    using ClauseIdT = HydraTest::Cache::CachingScheme::ClauseIdT;

    using CacheValuePtrAndIdPairOptionalType = typename Hydra::Cache::Cache<VarT, LiteralT, ClauseIdT, CacheValueT>::CacheValuePtrAndIdPairOptionalType;

    using BasicCachingSchemeType = Hydra::Cache::CachingScheme::Basic::BasicCachingScheme<VarT, LiteralT, ClauseIdT>;

    using ConnectedComponentStructure = HydraTest::Cache::CachingScheme::ConnectedComponentStructure;

    using CacheTypeEnum = Hydra::Cache::CacheTypeEnum;
    using OmitClauseTypeEnum = Hydra::Cache::CachingScheme::OmitClauseTypeEnum;
    using CachingSchemeTypeEnum = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum;
    using IgnorePureLiteralTypeEnum = HydraTest::Cache::CachingScheme::IgnorePureLiteralTypeEnum;

    using BasicCachingSchemeConfigurationType = Hydra::Cache::CachingScheme::Basic::BasicCachingSchemeConfiguration;
    //endregion

    //region Functions
    CachingSchemeAbstractUniquePtrType createBasicCachingScheme(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CacheTypeEnum cacheType,
                                                                OmitClauseTypeEnum omitClauseType, bool removeMultiOccurrentClauses) {
        BasicCachingSchemeConfigurationType configuration;
        configuration.omitClauseType = omitClauseType;
        configuration.removeMultiOccurrentClauses = removeMultiOccurrentClauses;

        return std::make_unique<BasicCachingSchemeType>(formulaRepresentationAbstractPtr, cacheType, configuration);
    }
    //endregion

    /**
     * Basic - component caching
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - component caching", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 3, 4, 5, 6, 7 }, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic (no multi-occurrent clauses) - component caching
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic (no multi-occurrent clauses) - component caching", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingNoMultiOccurrentClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         true);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, true), LiteralType(7, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 4, 5, 6 }, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - component caching (current component variables)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - component caching (current component variables)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingCurrentComponentVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);

            std::vector<VariableSetType> currentComponentVariablesVector { { 1, 2, 3 }, { 4, 5, 6, 7 } };

            for (const VariableSetType& currentComponentVariables : currentComponentVariablesVector) {
                ConnectedComponentStructure connectedComponentStructure(currentComponentVariables.size());
                connectedComponentStructure.variableSet.insert(currentComponentVariables.cbegin(), currentComponentVariables.cend());

                formulaRepresentation->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

                processCachingScheme(cache, currentComponentVariables, actualResult);

                formulaRepresentation->popPreviousComponent(connectedComponentStructure, {});
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - component caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - component caching (assignment)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, true), LiteralType(7, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 4, 5, 6 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - component caching (unit clause)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - component caching (unit clause)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingUnitClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaUnitClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - component caching (char8)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - component caching (char8)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingChar8Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaLiteralChar8<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - component caching (char16 low)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - component caching (char16 low)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingChar16LowResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaLiteralChar16Low<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - component caching (char16 high)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - component caching (char16 high)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingChar16HighResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaLiteralChar16High<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - component caching (char32)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - component caching (char32)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingChar32Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaLiteralChar32<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - hypergraph cut caching
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - hypergraph cut caching", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 3, 4, 5, 6, 7 }, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic (no multi-occurrent clauses) - hypergraph cut caching
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic (no multi-occurrent clauses) - hypergraph cut caching", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingNoMultiOccurrentClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         true);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 3, 4, 5, 6, 7 }, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - hypergraph cut caching (current component variables)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - hypergraph cut caching (current component variables)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingCurrentComponentVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);

            std::vector<VariableSetType> currentComponentVariablesVector { { 1, 2, 3 }, { 4, 5, 6, 7 } };

            for (const VariableSetType& currentComponentVariables : currentComponentVariablesVector) {
                ConnectedComponentStructure connectedComponentStructure(currentComponentVariables.size());
                connectedComponentStructure.variableSet.insert(currentComponentVariables.cbegin(), currentComponentVariables.cend());

                formulaRepresentation->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

                processCachingScheme(cache, currentComponentVariables, actualResult);

                formulaRepresentation->popPreviousComponent(connectedComponentStructure, {});
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic (no multi-occurrent clauses) - hypergraph cut caching (current component variables)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic (no multi-occurrent clauses) - hypergraph cut caching (current component variables)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingNoMultiOccurrentClausesCurrentComponentVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         true);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);

            std::vector<VariableSetType> currentComponentVariablesVector { { 1, 2, 3 }, { 4, 5, 6, 7 } };

            for (const VariableSetType& currentComponentVariables : currentComponentVariablesVector) {
                ConnectedComponentStructure connectedComponentStructure(currentComponentVariables.size());
                connectedComponentStructure.variableSet.insert(currentComponentVariables.cbegin(), currentComponentVariables.cend());

                formulaRepresentation->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

                processCachingScheme(cache, currentComponentVariables, actualResult);

                formulaRepresentation->popPreviousComponent(connectedComponentStructure, {});
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - hypergraph cut caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - hypergraph cut caching (assignment)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, true), LiteralType(7, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 4, 5, 6 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic (no multi-occurrent clauses) - hypergraph cut caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic (no multi-occurrent clauses) - hypergraph cut caching (assignment)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingNoMultiOccurrentClausesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         true);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, true), LiteralType(7, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 4, 5, 6 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - hypergraph cut caching (unit clause)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - hypergraph cut caching (unit clause)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingUnitClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaUnitClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic (no multi-occurrent clauses) - hypergraph cut caching (unit clause)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic (no multi-occurrent clauses) - hypergraph cut caching (unit clause)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingNoMultiOccurrentClausesUnitClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaUnitClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         true);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - hypergraph cut caching (char8)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - hypergraph cut caching (char8)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingChar8Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar8<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - hypergraph cut caching (char16 low)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - hypergraph cut caching (char16 low)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingChar16LowResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar16Low<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - hypergraph cut caching (char16 high)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - hypergraph cut caching (char16 high)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingChar16HighResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar16High<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic - hypergraph cut caching (char32)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic - hypergraph cut caching (char32)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingChar32Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar32<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, variableSet, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic omitting binary clauses - component caching
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic omitting binary clauses - component caching", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingOmittingBinaryClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::ORIGINAL_BINARY,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 3, 4, 5, 6, 7 }, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic omitting binary clauses - hypergraph cut caching
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic omitting binary clauses - hypergraph cut caching", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingOmittingBinaryClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::ORIGINAL_BINARY,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 3, 4, 5, 6, 7 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic omitting binary clauses - component caching (current component variables)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic omitting binary clauses - component caching (current component variables)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingOmittingBinaryClausesCurrentComponentVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::ORIGINAL_BINARY,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);

            std::vector<VariableSetType> currentComponentVariablesVector { { 1, 2, 3 }, { 4, 5, 6, 7 } };

            for (const VariableSetType& currentComponentVariables : currentComponentVariablesVector) {
                ConnectedComponentStructure connectedComponentStructure(currentComponentVariables.size());
                connectedComponentStructure.variableSet.insert(currentComponentVariables.cbegin(), currentComponentVariables.cend());

                formulaRepresentation->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

                processCachingScheme(cache, currentComponentVariables, actualResult);

                formulaRepresentation->popPreviousComponent(connectedComponentStructure, {});
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic omitting binary clauses - component caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic omitting binary clauses - component caching (assignment)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingOmittingBinaryClausesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::ORIGINAL_BINARY,
                                                                                                         false);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, true), LiteralType(7, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 4, 5, 6 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic omitting binary clauses (no multi-occurrent clauses) - component caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic omitting binary clauses (no multi-occurrent clauses) - component caching (assignment)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingOmittingBinaryClausesNoMultiOccurrentClausesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::ORIGINAL_BINARY,
                                                                                                         true);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, true), LiteralType(7, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 4, 5, 6 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic omitting binary clauses - component caching (unit clause)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic omitting binary clauses - component caching (unit clause)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingOmittingBinaryClausesUnitClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaUnitClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::ORIGINAL_BINARY,
                                                                                                         false);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic omitting untouched clauses - component caching
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic omitting untouched clauses - component caching", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingOmittingUntouchedClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::UNTOUCHED,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 3, 4, 5, 6, 7 }, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic omitting untouched clauses - hypergraph cut caching
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic omitting untouched clauses - hypergraph cut caching", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeHypergraphCutCachingOmittingUntouchedClausesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::HYPERGRAPH_CUT,
                                                                                                         OmitClauseTypeEnum::UNTOUCHED,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 3, 4, 5, 6, 7 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic omitting untouched clauses - component caching (current component variables)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic omitting untouched clauses - component caching (current component variables)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingOmittingUntouchedClausesCurrentComponentVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::UNTOUCHED,
                                                                                                         false);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);

            std::vector<VariableSetType> currentComponentVariablesVector { { 1, 2, 3 }, { 4, 5, 6, 7 } };

            for (const VariableSetType& currentComponentVariables : currentComponentVariablesVector) {
                ConnectedComponentStructure connectedComponentStructure(currentComponentVariables.size());
                connectedComponentStructure.variableSet.insert(currentComponentVariables.cbegin(), currentComponentVariables.cend());

                formulaRepresentation->setNewComponent(connectedComponentStructure, IgnorePureLiteralTypeEnum::NONE);

                processCachingScheme(cache, currentComponentVariables, actualResult);

                formulaRepresentation->popPreviousComponent(connectedComponentStructure, {});
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic omitting untouched clauses - component caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic omitting untouched clauses - component caching (assignment)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingOmittingUntouchedClausesAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaForMultiOccurrentClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::UNTOUCHED,
                                                                                                         false);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, true), LiteralType(7, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2, 4, 5, 6 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Basic omitting untouched clauses - component caching (unit clause)
     */
    TEST_CASE("[Cache::CachingScheme::Basic] basic omitting untouched clauses - component caching (unit clause)", "[Cache::CachingScheme::Basic]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          basicCachingSchemeComponentCachingOmittingUntouchedClausesUnitClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaUnitClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::UNTOUCHED,
                                                                                                         false);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(3, false) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 2 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Cache - variable vector
     */
    TEST_CASE("[Cache] cache - variable vector", "[Cache]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          cacheVariableVectorResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createBasicCachingScheme(formulaRepresentation.get(),
                                                                                                         CacheTypeEnum::COMPONENT,
                                                                                                         OmitClauseTypeEnum::NONE,
                                                                                                         false);

            VariableSetType currentComponentVariableSet { 1, 2, 3, 4, 5, 6, 7 };

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            actualResult << "---------- cache (before) ----------" << std::endl;
            cache.printCacheDebug(actualResult, true, true, true, false);

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct(currentComponentVariableSet);
            actualResult << "---------- cache record ----------" << std::endl;
            cacheRecordStruct.printCacheRecordStruct(actualResult);
            actualResult << std::endl;

            cache.addCacheRecordToCache(std::move(cacheRecordStruct), { 2, 4, 6 });
            actualResult << "---------- cache (after) ----------" << std::endl;
            cache.printCacheDebug(actualResult, true, true, true, false);

            cacheRecordStruct = cache.createCacheRecordStruct(currentComponentVariableSet);
            CacheValuePtrAndIdPairOptionalType cacheValuePtrAndIdPairOptional = cache.searchInCache(cacheRecordStruct);

            actualResult << "---------- search ----------" << std::endl;
            if (cacheValuePtrAndIdPairOptional.has_value()) {
                actualResult << "ID: " << std::to_string(cacheValuePtrAndIdPairOptional->second) << std::endl;

                actualResult << "Value:";
                for (VarT var : *(cacheValuePtrAndIdPairOptional->first))
                    actualResult << " " << std::to_string(var);
                actualResult << std::endl;
            }
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Cache::CachingScheme::Basic
