#pragma once

#include <string>

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/cache/enums/CacheSizeTypeEnum.hpp"

namespace Hydra::Exception::Cache {

    /**
     * Cache exception (main)
     */
    class CacheException : public CompilerException {
    public:
        explicit CacheException(const std::string& message)
            : CompilerException(message) { }

        explicit CacheException(std::string&& message)
            : CompilerException(std::move(message)) { }

        CacheException(const std::string& message, const std::string& functionName)
            : CompilerException(message, functionName) { }
    };

    /**
     * Cache is too big
     */
    class CacheIsTooBigException : public CacheException {
    public:
        CacheIsTooBigException()
            : CacheException("The cache is too big!") { }

        explicit CacheIsTooBigException(Hydra::Cache::CacheSizeTypeEnum cacheSizeType)
            : CacheException("The " + Hydra::Cache::cacheSizeTypeEnumToString(cacheSizeType) + " is too big!") { }
    };

    /**
     * The mapping cache is too big
     */
    class MappingCacheIsTooBigException : public CacheException {
    public:
        MappingCacheIsTooBigException()
            : CacheException("The mapping cache is too big!") { }
    };
}   // namespace Hydra::Exception::Cache
