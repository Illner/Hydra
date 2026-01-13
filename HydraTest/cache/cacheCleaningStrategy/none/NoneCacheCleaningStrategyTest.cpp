#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/cache/cacheCleaningStrategy/CacheCleaningStrategy.hpp"
#include "HydraTest/cache/cacheCleaningStrategy/CreateFormula.hpp"
#include "HydraTest/cache/cacheCleaningStrategy/none/NoneCacheCleaningStrategyTestResult.hpp"
#include "HydraTest/catch.hpp"

#include "Hydra/cache/cacheCleaningStrategy/none/NoneCacheCleaningStrategy.hpp"

#include "Hydra/cache/exceptions/CacheException.hpp"

#include "Hydra/cache/enums/CacheTypeEnum.hpp"

namespace HydraTest::Cache::CacheCleaningStrategy::None {
    //region Types
    using VarT = HydraTest::Cache::CacheCleaningStrategy::VarT;
    using LiteralT = HydraTest::Cache::CacheCleaningStrategy::LiteralT;
    using ClauseIdT = HydraTest::Cache::CacheCleaningStrategy::ClauseIdT;
    using CacheValueT = HydraTest::Cache::CacheCleaningStrategy::CacheValueT;

    using NoneCacheCleaningStrategyType = Hydra::Cache::CacheCleaningStrategy::None::NoneCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>;

    using CacheTypeEnum = Hydra::Cache::CacheTypeEnum;
    //endregion

    //region Functions
    CacheCleaningStrategyAbstractUniquePtrType createNoneCacheCleaningStrategy() {
        return std::make_unique<NoneCacheCleaningStrategyType>();
    }
    //endregion

    /**
     * None with mapping
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::None] none with mapping", "[Cache::CacheCleaningStrategy::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCacheCleaningStrategyWithMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createNoneCacheCleaningStrategy();
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::COMPONENT, true);
            printCache(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * None with mapping - component caching (byte size)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::None] none with mapping - component caching (byte size)", "[Cache::CacheCleaningStrategy::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCacheCleaningStrategyWithMappingComponentCachingByteSizeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createNoneCacheCleaningStrategy();
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::COMPONENT, true);

            fillCache(cache, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * None without mapping
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::None] none without mapping", "[Cache::CacheCleaningStrategy::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCacheCleaningStrategyWithoutMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createNoneCacheCleaningStrategy();
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::COMPONENT, false);
            printCache(cache, actualResult);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * None without mapping - component caching (byte size)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::None] none without mapping - component caching (byte size)", "[Cache::CacheCleaningStrategy::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCacheCleaningStrategyWithoutMappingComponentCachingByteSizeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createNoneCacheCleaningStrategy();
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::COMPONENT, false);

            fillCache(cache, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * None with mapping - hypergraph cut caching (byte size)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::None] none with mapping - hypergraph cut caching (byte size)", "[Cache::CacheCleaningStrategy::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCacheCleaningStrategyWithMappingHypergraphCutCachingByteSizeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createNoneCacheCleaningStrategy();
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT, true);

            fillCache(cache, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * None without mapping - hypergraph cut caching (byte size)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::None] none without mapping - hypergraph cut caching (byte size)", "[Cache::CacheCleaningStrategy::None]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          noneCacheCleaningStrategyWithoutMappingHypergraphCutCachingByteSizeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createNoneCacheCleaningStrategy();
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT, false);

            fillCache(cache, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Cache::CacheCleaningStrategy::None
