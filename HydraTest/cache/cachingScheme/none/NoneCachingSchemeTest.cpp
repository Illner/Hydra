#include <memory>
#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/cache/cachingScheme/CachingScheme.hpp"
#include "HydraTest/cache/cachingScheme/CreateFormula.hpp"
#include "HydraTest/cache/cachingScheme/none/NoneCachingSchemeTestResult.hpp"
#include "HydraTest/catch.hpp"

#include "Hydra/cache/cachingScheme/none/NoneCachingScheme.hpp"

#include "Hydra/cache/exceptions/CacheException.hpp"

#include "Hydra/cache/cachingScheme/enums/CachingSchemeTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"

namespace HydraTest::Cache::CachingScheme::None {

    //region Types
    using VarT = HydraTest::Cache::CachingScheme::VarT;
    using LiteralT = HydraTest::Cache::CachingScheme::LiteralT;
    using ClauseIdT = HydraTest::Cache::CachingScheme::ClauseIdT;

    using NoneCachingSchemeType = Hydra::Cache::CachingScheme::None::NoneCachingScheme<VarT, LiteralT, ClauseIdT>;

    using ConnectedComponentStructure = HydraTest::Cache::CachingScheme::ConnectedComponentStructure;

    using CacheTypeEnum = Hydra::Cache::CacheTypeEnum;
    using CachingSchemeTypeEnum = Hydra::Cache::CachingScheme::CachingSchemeTypeEnum;
    using IgnorePureLiteralTypeEnum = HydraTest::Cache::CachingScheme::IgnorePureLiteralTypeEnum;
    //endregion

    //region Functions
    CachingSchemeAbstractUniquePtrType createNoneCachingScheme(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CacheTypeEnum cacheType) {
        return std::make_unique<NoneCachingSchemeType>(formulaRepresentationAbstractPtr, cacheType);
    }
    //endregion

    /**
     * None - component caching
     */
    TEST_CASE("[Cache::CachingScheme::None] none - component caching", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeComponentCachingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
     * None - component caching (current component variables)
     */
    TEST_CASE("[Cache::CachingScheme::None] none - component caching (current component variables)", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeComponentCachingCurrentComponentVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
     * None - component caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::None] none - component caching (assignment)", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeComponentCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
     * None - component caching (char8)
     */
    TEST_CASE("[Cache::CachingScheme::None] none - component caching (char8)", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeComponentCachingChar8Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaLiteralChar8<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
     * None - component caching (char16 low)
     */
    TEST_CASE("[Cache::CachingScheme::None] none - component caching (char16 low)", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeComponentCachingChar16LowResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaLiteralChar16Low<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
     * None - component caching (char16 high)
     */
    TEST_CASE("[Cache::CachingScheme::None] none - component caching (char16 high)", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeComponentCachingChar16HighResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaLiteralChar16High<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
     * None - component caching (char32)
     */
    TEST_CASE("[Cache::CachingScheme::None] none - component caching (char32)", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeComponentCachingChar32Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaLiteralChar32<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
     * None - hypergraph cut caching
     */
    TEST_CASE("[Cache::CachingScheme::None] none - hypergraph cut caching", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeHypergraphCutCachingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
     * None - hypergraph cut caching (current component variables)
     */
    TEST_CASE("[Cache::CachingScheme::None] none - hypergraph cut caching (current component variables)", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeHypergraphCutCachingCurrentComponentVariablesResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
     * None - hypergraph cut caching (assignment)
     */
    TEST_CASE("[Cache::CachingScheme::None] none - hypergraph cut caching (assignment)", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeHypergraphCutCachingAssignmentResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
     * None - hypergraph cut caching (char8)
     */
    TEST_CASE("[Cache::CachingScheme::None] none - hypergraph cut caching (char8)", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeHypergraphCutCachingChar8Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar8<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
     * None - hypergraph cut caching (char16 low)
     */
    TEST_CASE("[Cache::CachingScheme::None] none - hypergraph cut caching (char16 low)", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeHypergraphCutCachingChar16LowResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar16Low<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
     * None - hypergraph cut caching (char16 high)
     */
    TEST_CASE("[Cache::CachingScheme::None] none - hypergraph cut caching (char16 high)", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeHypergraphCutCachingChar16HighResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar16High<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
     * None - hypergraph cut caching (char32)
     */
    TEST_CASE("[Cache::CachingScheme::None] none - hypergraph cut caching (char32)", "[Cache::CachingScheme::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCachingSchemeHypergraphCutCachingChar32Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            VariableSetType variableSet;
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormulaVariableChar32<VarT, LiteralT, ClauseIdT>(variableSet);
            CachingSchemeAbstractUniquePtrType cachingSchemeAbstractUniquePtr = createNoneCachingScheme(formulaRepresentation.get(),
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
}   // namespace HydraTest::Cache::CachingScheme::None
