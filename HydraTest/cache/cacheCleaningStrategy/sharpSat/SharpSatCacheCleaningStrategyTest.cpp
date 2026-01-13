#include <vector>

#include "HydraTest/TemplateTest.hpp"
#include "HydraTest/cache/cacheCleaningStrategy/CacheCleaningStrategy.hpp"
#include "HydraTest/cache/cacheCleaningStrategy/CreateFormula.hpp"
#include "HydraTest/cache/cacheCleaningStrategy/sharpSat/SharpSatCacheCleaningStrategyTestResult.hpp"
#include "HydraTest/catch.hpp"

#include "Hydra/cache/cacheCleaningStrategy/sharpSat/SharpSatCacheCleaningStrategy.hpp"
#include "Hydra/cache/cacheCleaningStrategy/sharpSat/SharpSatCacheCleaningStrategy.tpp"

#include "Hydra/cache/exceptions/CacheException.hpp"

#include "Hydra/cache/enums/CacheTypeEnum.hpp"

namespace HydraTest::Cache::CacheCleaningStrategy::SharpSat {

    using LargeNumberType = Hydra::Cache::CacheCleaningStrategy::SharpSat::LargeNumberType;

    //region Types
    using VarT = HydraTest::Cache::CacheCleaningStrategy::VarT;
    using LiteralT = HydraTest::Cache::CacheCleaningStrategy::LiteralT;
    using ClauseIdT = HydraTest::Cache::CacheCleaningStrategy::ClauseIdT;
    using CacheValueT = HydraTest::Cache::CacheCleaningStrategy::CacheValueT;

    using SharpSatCacheCleaningStrategyConfigurationType = Hydra::Cache::CacheCleaningStrategy::SharpSat::SharpSatCacheCleaningStrategyConfiguration;
    using SharpSatCacheCleaningStrategyType = Hydra::Cache::CacheCleaningStrategy::SharpSat::SharpSatCacheCleaningStrategy<VarT, LiteralT, ClauseIdT, CacheValueT>;

    using CacheTypeEnum = Hydra::Cache::CacheTypeEnum;
    //endregion

    //region Functions
    CacheCleaningStrategyAbstractUniquePtrType createSharpSatCacheCleaningStrategy(bool resetTime, int percentageOfDeletedEntries,
                                                                                   LargeNumberType maxByteSizeCache) {
        // Configuration
        SharpSatCacheCleaningStrategyConfigurationType configuration;
        configuration.resetTime = resetTime;
        configuration.maxByteSizeCache = maxByteSizeCache;
        configuration.percentageOfDeletedEntries = percentageOfDeletedEntries;

        return std::make_unique<SharpSatCacheCleaningStrategyType>(configuration);
    }
    //endregion

    /**
     * sharpSAT with mapping
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT with mapping", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 50, 100);
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
     * sharpSAT with mapping - component caching (byte size)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT with mapping - component caching (byte size)", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithMappingComponentCachingByteSizeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 50, 1000);
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
     * sharpSAT without mapping
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT without mapping", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithoutMappingResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 50, 100);
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
     * sharpSAT without mapping - component caching (byte size)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT without mapping - component caching (byte size)", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithoutMappingComponentCachingByteSizeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 50, 1000);
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
     * sharpSAT with mapping - hypergraph cut caching (byte size)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT with mapping - hypergraph cut caching (byte size)", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithMappingHypergraphCutCachingByteSizeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 50, 1000);
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
     * sharpSAT without mapping - hypergraph cut caching (byte size)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT without mapping - hypergraph cut caching (byte size)", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithoutMappingHypergraphCutCachingByteSizeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 50, 1000);
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT, false);

            fillCache(cache, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sharpSAT - no reset time
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT - no reset time", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyNoResetTimeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(false, 50, 1000);
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::COMPONENT, true);

            fillCache(cache, actualResult, false);
            fillCache(cache, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sharpSAT - reset time
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT - reset time", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyResetTimeResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 50, 1000);
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::COMPONENT, true);

            fillCache(cache, actualResult, false);
            fillCache(cache, actualResult, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sharpSAT - reset time (even)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT - reset time (even)", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyResetTimeEvenResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 50, 1000);
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::COMPONENT, true);

            fillCache(cache, actualResult, false);
            fillCache(cache, actualResult, true, true, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sharpSAT - reset time (odd)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT - reset time (odd)", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyResetTimeOddResult);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 50, 1000);
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::COMPONENT, true);

            fillCache(cache, actualResult, false);
            fillCache(cache, actualResult, true, false, true);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sharpSAT with mapping - delete entries (25)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT with mapping - delete entries (25) ", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithMappingDeleteEntries25Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 25, 700);
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT, true);

            fillCache(cache, actualResult, false, true, true, false);
            fillCache(cache, actualResult, false, true, false, false);

            printCache(cache, actualResult, false, false);
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
            cache.addCacheRecordToCache(std::move(cacheRecordStruct), (CacheValueT)1);

            printCache(cache, actualResult, false, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sharpSAT with mapping - delete entries (50)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT with mapping - delete entries (50) ", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithMappingDeleteEntries50Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 50, 700);
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT, true);

            fillCache(cache, actualResult, false, true, true, false);
            fillCache(cache, actualResult, false, true, false, false);

            printCache(cache, actualResult, false, false);
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
            cache.addCacheRecordToCache(std::move(cacheRecordStruct), (CacheValueT)1);

            printCache(cache, actualResult, false, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sharpSAT with mapping - delete entries (75)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT with mapping - delete entries (75) ", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithMappingDeleteEntries75Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 75, 700);
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT, true);

            fillCache(cache, actualResult, false, true, true, false);
            fillCache(cache, actualResult, false, true, false, false);

            printCache(cache, actualResult, false, false);
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
            cache.addCacheRecordToCache(std::move(cacheRecordStruct), (CacheValueT)1);

            printCache(cache, actualResult, false, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sharpSAT with mapping - delete entries (100)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT with mapping - delete entries (100) ", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithMappingDeleteEntries100Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 100, 700);
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT, true);

            fillCache(cache, actualResult, false, true, true, false);
            fillCache(cache, actualResult, false, true, false, false);

            printCache(cache, actualResult, false, false);
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
            cache.addCacheRecordToCache(std::move(cacheRecordStruct), (CacheValueT)1);

            printCache(cache, actualResult, false, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sharpSAT without mapping - delete entries (25)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT without mapping - delete entries (25) ", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithoutMappingDeleteEntries25Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 25, 500);
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT, false);

            fillCache(cache, actualResult, false, true, true, false);
            fillCache(cache, actualResult, false, true, false, false);

            printCache(cache, actualResult, false, false);
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
            cache.addCacheRecordToCache(std::move(cacheRecordStruct), (CacheValueT)1);

            printCache(cache, actualResult, false, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sharpSAT without mapping - delete entries (50)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT without mapping - delete entries (50) ", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithoutMappingDeleteEntries50Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 50, 500);
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT, false);

            fillCache(cache, actualResult, false, true, true, false);
            fillCache(cache, actualResult, false, true, false, false);

            printCache(cache, actualResult, false, false);
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
            cache.addCacheRecordToCache(std::move(cacheRecordStruct), (CacheValueT)1);

            printCache(cache, actualResult, false, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sharpSAT without mapping - delete entries (75)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT without mapping - delete entries (75) ", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithoutMappingDeleteEntries75Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 75, 500);
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT, false);

            fillCache(cache, actualResult, false, true, true, false);
            fillCache(cache, actualResult, false, true, false, false);

            printCache(cache, actualResult, false, false);
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
            cache.addCacheRecordToCache(std::move(cacheRecordStruct), (CacheValueT)1);

            printCache(cache, actualResult, false, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }

    /**
     * sharpSAT without mapping - delete entries (100)
     */
    TEST_CASE("[Cache::CacheCleaningStrategy::SharpSat] sharpSAT without mapping - delete entries (100) ", "[Cache::CacheCleaningStrategy::SharpSat]") {
        TemplateTest test(Catch::getResultCapture().getCurrentTestName(),
                          sharpSatCacheCleaningStrategyWithoutMappingDeleteEntries100Result);
        std::stringstream& actualResult = test.getStringStream();

        try {
            FormulaRepresentationAbstractUniquePtrType formulaRepresentation = createFormula<VarT, LiteralT, ClauseIdT>();

            CacheCleaningStrategyAbstractUniquePtrType cacheCleaningStrategy = createSharpSatCacheCleaningStrategy(true, 100, 500);
            CacheType cache = createCache(std::move(cacheCleaningStrategy), formulaRepresentation.get(), CacheTypeEnum::HYPERGRAPH_CUT, false);

            fillCache(cache, actualResult, false, true, true, false);
            fillCache(cache, actualResult, false, true, false, false);

            printCache(cache, actualResult, false, false);
            actualResult << "----------------------------------------" << std::endl
                         << std::endl;

            CacheRecordStruct cacheRecordStruct = cache.createCacheRecordStruct({ 1, 2, 3, 4, 5, 6, 7, 8, 9 });
            cache.addCacheRecordToCache(std::move(cacheRecordStruct), (CacheValueT)1);

            printCache(cache, actualResult, false, false);
        }
        catch (const std::exception& e) {
            actualResult << e.what() << std::endl;
        }

        // test.saveActualResultToFile();
        REQUIRE(test.checkTest());
    }
}   // namespace HydraTest::Cache::CacheCleaningStrategy::SharpSat
