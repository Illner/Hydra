#include "./Cache.hxx"

namespace Hydra::Cache {

    void CacheStatistics::processPrintStatistics(std::ostream& out, const std::string& statisticsName, bool addLabels) const {
        ratioOfNumberOfPositiveHitsToNumberOfHitsCounter.printCounterStatistics(out, statisticsName, addLabels);

        numberOfCurrentEntriesNumber.printNumberStatistics(out, statisticsName, addLabels);

        numberOfDeletedEntriesNumber.printNumberStatistics(out, statisticsName, addLabels);

        numberOfCacheCleaningsNumber.printNumberStatistics(out, statisticsName, addLabels);

        createCacheRecordStructTimer.printTimerStatistics(out, statisticsName, addLabels);

        searchCacheRecordStructTimer.printTimerStatistics(out, statisticsName, addLabels);

        addCacheRecordStructTimer.printTimerStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfEmptyCacheRecordsToNumberOfCacheRecordsCounter.printCounterStatistics(out, statisticsName, addLabels);

        formulaSizeCacheRecordStructCounter.printCounterStatistics(out, statisticsName, addLabels);

        formulaSizePositiveHitCounter.printCounterStatistics(out, statisticsName, addLabels);

        formulaSizeNegativeHitCounter.printCounterStatistics(out, statisticsName, addLabels);

        numberOfVariablesCacheRecordStructCounter.printCounterStatistics(out, statisticsName, addLabels);

        numberOfVariablesPositiveHitCounter.printCounterStatistics(out, statisticsName, addLabels);

        numberOfVariablesNegativeHitCounter.printCounterStatistics(out, statisticsName, addLabels);

        numberOfClausesCacheRecordStructCounter.printCounterStatistics(out, statisticsName, addLabels);

        numberOfClausesPositiveHitCounter.printCounterStatistics(out, statisticsName, addLabels);

        numberOfClausesNegativeHitCounter.printCounterStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfRemovedClausesToNumberOfClausesCounter.printCounterStatistics(out, statisticsName, addLabels);

        ratioOfNumberOfIdenticalMappingsToNumberOfMappingsCounter.printCounterStatistics(out, statisticsName, addLabels);

        cleanCacheTimer.printTimerStatistics(out, statisticsName, addLabels);

        // Debug
        if (debugTimer.atLeastOneCall())
            debugTimer.printTimerStatistics(out, statisticsName, addLabels);

        if (debugCounter.atLeastOneCall())
            debugCounter.printCounterStatistics(out, statisticsName, addLabels);
    }
}   // namespace Hydra::Cache
