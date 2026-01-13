#pragma once

#include <string>

#include "Hydra/other/Other.hpp"

#include "Hydra/cache/exceptions/CacheException.hpp"

#include "Hydra/cache/enums/CacheTypeEnum.hpp"

#include "Hydra/cache/cachingScheme/cara/CaraCachingScheme.tpp"

namespace Hydra::Exception::Cache::CachingScheme {

    /**
     * Caching scheme exception (main)
     */
    class CachingSchemeException : public CacheException {
    public:
        explicit CachingSchemeException(const std::string& message)
            : CacheException(message) { }

        explicit CachingSchemeException(std::string&& message)
            : CacheException(std::move(message)) { }

        CachingSchemeException(const std::string& message, const std::string& functionName)
            : CacheException(message, functionName) { }
    };

    /**
     * Caching unit clauses is forbidden
     */
    class CachingUnitClausesIsForbiddenException : public CachingSchemeException {
    public:
        CachingUnitClausesIsForbiddenException()
            : CachingSchemeException("Caching unit clauses is forbidden!") { }
    };

    /**
     * Invalid number of sample moments (Cara caching scheme)
     */
    class InvalidNumberOfSampleMomentsCaraCachingSchemeException : public CachingSchemeException {
    public:
        InvalidNumberOfSampleMomentsCaraCachingSchemeException(Hydra::Other::LargeNumberType numberOfSampleMoments, Hydra::Cache::CacheTypeEnum cacheType)
            : CachingSchemeException("Cara caching scheme (" + Hydra::Cache::cacheTypeEnumToString(cacheType) + ") - the number of sample moments (" + std::to_string(numberOfSampleMoments) +
                                     ") is invalid! The valid number must be between " + std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MINIMUM) +
                                     " and " + std::to_string(Hydra::Cache::CachingScheme::Cara::CaraCachingSchemeConfiguration::S_NUMBER_OF_SAMPLE_MOMENTS_MAXIMUM) + ".") { }
    };
}   // namespace Hydra::Exception::Cache::CachingScheme
