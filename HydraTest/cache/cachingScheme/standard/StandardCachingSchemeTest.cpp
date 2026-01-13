#include <memory>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/cache/cachingScheme/CachingScheme.hpp"
#include "HydraTest/cache/cachingScheme/CreateFormula.hpp"
#include "HydraTest/cache/cachingScheme/standard/StandardCachingSchemeTestResult.hpp"
#include "HydraTest/catch.hpp"

#include "Hydra/cache/cachingScheme/standard/StandardCachingScheme.hpp"

#include "Hydra/cache/exceptions/CacheException.hpp"

#include "Hydra/cache/cachingScheme/enums/CachingSchemeTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"

#include "Hydra/cache/cachingScheme/standard/StandardCachingScheme.tpp"

namespace HydraTest::Cache::CachingScheme::Standard {

    //region Types
    using VarT = HydraTest::Cache::CachingScheme::VarT;
    using LiteralT = HydraTest::Cache::CachingScheme::LiteralT;
    using ClauseIdT = HydraTest::Cache::CachingScheme::ClauseIdT;

    using StandardCachingSchemeType = Hydra::Cache::CachingScheme::Standard::StandardCachingScheme<VarT, LiteralT, ClauseIdT>;

    using ConnectedComponentStructure = HydraTest::Cache::CachingScheme::ConnectedComponentStructure;

    using CacheTypeEnum = Hydra::Cache::CacheTypeEnum;
    using CachingSchemeTypeEnum = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum;
    using IgnorePureLiteralTypeEnum = HydraTest::Cache::CachingScheme::IgnorePureLiteralTypeEnum;

    using StandardCachingSchemeConfigurationType = Hydra::Cache::CachingScheme::Standard::StandardCachingSchemeConfiguration;
    //endregion

    //region Functions
    CachingSchemeAbstractUniquePtrType createStandardCachingScheme(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CacheTypeEnum cacheType) {
        StandardCachingSchemeConfigurationType configuration;

        return std::make_unique<StandardCachingSchemeType>(formulaRepresentationAbstractPtr, cacheType, configuration);
    }
    //endregion

    /**
     * Standard - component caching
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - component caching", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeComponentCachingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::COMPONENT);

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
     * Standard - component caching (current component variables)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - component caching (current component variables)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeComponentCachingCurrentComponentVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::COMPONENT);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);

            std::vector<VariableSetType> currentComponentVariablesVector { { 1, 2, 3, 4 }, { 5, 6, 7 } };

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
     * Standard - component caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - component caching (assignment)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeComponentCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::COMPONENT);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(2, false), LiteralType(6, true) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 3, 4, 5, 7 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Standard - component caching (unit clause)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - component caching (unit clause)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeComponentCachingUnitClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaUnitClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::COMPONENT);

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
     * Standard - component caching (char8)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - component caching (char8)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeComponentCachingChar8Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaLiteralChar8<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::COMPONENT);

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
     * Standard - component caching (char16 low)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - component caching (char16 low)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeComponentCachingChar16LowResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaLiteralChar16Low<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::COMPONENT);

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
     * Standard - component caching (char16 high)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - component caching (char16 high)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeComponentCachingChar16HighResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaLiteralChar16High<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::COMPONENT);

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
     * Standard - component caching (char32)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - component caching (char32)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeComponentCachingChar32Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaLiteralChar32<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::COMPONENT);

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
     * Standard - hypergraph cut caching
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - hypergraph cut caching", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeHypergraphCutCachingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::HYPERGRAPH_CUT);

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
     * Standard - hypergraph cut caching (current component variables)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - hypergraph cut caching (current component variables)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeHypergraphCutCachingCurrentComponentVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::HYPERGRAPH_CUT);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);

            std::vector<VariableSetType> currentComponentVariablesVector { { 1, 2, 3, 4 }, { 5, 6, 7 } };

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
     * Standard - hypergraph cut caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - hypergraph cut caching (assignment)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeHypergraphCutCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::HYPERGRAPH_CUT);

            // Assignment
            VariableVectorType tmp;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ LiteralType(2, false), LiteralType(6, true) }, tmp);

            CacheType cache = createCache(std::move(cachingSchemeAbstractUniquePtr));
            printCachingScheme(cache, actualResult);
            processCachingScheme(cache, { 1, 3, 4, 5, 7 }, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * Standard - hypergraph cut caching (unit clause)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - hypergraph cut caching (unit clause)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeHypergraphCutCachingUnitClauseResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaUnitClauses<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::HYPERGRAPH_CUT);

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
     * Standard - hypergraph cut caching (char8)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - hypergraph cut caching (char8)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeHypergraphCutCachingChar8Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar8<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::HYPERGRAPH_CUT);

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
     * Standard - hypergraph cut caching (char16 low)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - hypergraph cut caching (char16 low)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeHypergraphCutCachingChar16LowResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar16Low<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::HYPERGRAPH_CUT);

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
     * Standard - hypergraph cut caching (char16 high)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - hypergraph cut caching (char16 high)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeHypergraphCutCachingChar16HighResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar16High<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::HYPERGRAPH_CUT);

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
     * Standard - hypergraph cut caching (char32)
     */
    TEST_CASE("[Cache::CachingScheme::Standard] standard - hypergraph cut caching (char32)", "[Cache::CachingScheme::Standard]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          standardCachingSchemeHypergraphCutCachingChar32Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar32<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createStandardCachingScheme(formulaRepresentation.get(),
                                                                                                            CacheTypeEnum::HYPERGRAPH_CUT);

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
}   // namespace HydraTest::Cache::CachingScheme::Standard
