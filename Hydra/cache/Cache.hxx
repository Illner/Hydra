#pragma once

#include <string>

#include "Hydra/statistics/StatisticsAbstract.hpp"

#include "Hydra/cache/enums/CacheTypeEnum.hpp"

namespace Hydra::Cache {

    /**
     * Cache - statistics
     */
    struct CacheStatistics : Statistics::StatisticsAbstract {
    public:
        using CacheStatisticsPtrType = CacheStatistics*;

    public:
        explicit CacheStatistics(CacheTypeEnum cacheType)
            : Statistics::StatisticsAbstract("Cache - " + cacheTypeEnumToString(cacheType)) { }

    public:
        NumberCounterStatisticsType ratioOfNumberOfPositiveHitsToNumberOfHitsCounter = NumberCounterStatisticsType("#positive hits / #hits");

        NumberStatisticsType numberOfCurrentEntriesNumber = NumberStatisticsType("#current entries", false);

        NumberStatisticsType numberOfDeletedEntriesNumber = NumberStatisticsType("#deleted entries", false);

        NumberStatisticsType numberOfCacheCleaningsNumber = NumberStatisticsType("#cache cleanings", false);

        NanoTimerStatisticsType createCacheRecordStructTimer = NanoTimerStatisticsType("create cache record structure");

        NanoTimerStatisticsType searchCacheRecordStructTimer = NanoTimerStatisticsType("search cache record structure");

        NanoTimerStatisticsType addCacheRecordStructTimer = NanoTimerStatisticsType("add cache record structure");

        NumberCounterStatisticsType ratioOfNumberOfEmptyCacheRecordsToNumberOfCacheRecordsCounter = NumberCounterStatisticsType("#empty cache records / #cache records");

        NumberCounterStatisticsType formulaSizeCacheRecordStructCounter = NumberCounterStatisticsType("formula size (cache record structure)");

        NumberCounterStatisticsType formulaSizePositiveHitCounter = NumberCounterStatisticsType("formula size (positive hit)");

        NumberCounterStatisticsType formulaSizeNegativeHitCounter = NumberCounterStatisticsType("formula size (negative hit)");

        NumberCounterStatisticsType numberOfVariablesCacheRecordStructCounter = NumberCounterStatisticsType("#variables (cache record structure)");

        NumberCounterStatisticsType numberOfVariablesPositiveHitCounter = NumberCounterStatisticsType("#variables (positive hit)");

        NumberCounterStatisticsType numberOfVariablesNegativeHitCounter = NumberCounterStatisticsType("#variables (negative hit)");

        NumberCounterStatisticsType numberOfClausesCacheRecordStructCounter = NumberCounterStatisticsType("#clauses (cache record structure)");

        NumberCounterStatisticsType numberOfClausesPositiveHitCounter = NumberCounterStatisticsType("#clauses (positive hit)");

        NumberCounterStatisticsType numberOfClausesNegativeHitCounter = NumberCounterStatisticsType("#clauses (negative hit)");

        RealNumberCounterStatisticsType ratioOfNumberOfRemovedClausesToNumberOfClausesCounter = RealNumberCounterStatisticsType("#removed clauses / #clauses");

        NumberCounterStatisticsType ratioOfNumberOfIdenticalMappingsToNumberOfMappingsCounter = NumberCounterStatisticsType("#identical mappings / #mappings");

        NanoTimerStatisticsType cleanCacheTimer = NanoTimerStatisticsType("clean cache");

    public:
        NanoTimerStatisticsType debugTimer = NanoTimerStatisticsType("debug timer");

        RealNumberCounterStatisticsType debugCounter = RealNumberCounterStatisticsType("debug counter");

    private:
        void processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const override;
    };
}   // namespace Hydra::Cache
