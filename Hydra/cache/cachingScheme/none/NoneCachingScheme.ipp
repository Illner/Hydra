#pragma once

#include "./NoneCachingScheme.hpp"

namespace Hydra::Cache::CachingScheme::None {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    LargeNumberType NoneCachingScheme<VarT, LiteralT, ClauseIdT>::maxByteSizeKey() const {
        return (LargeNumberType)0;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename NoneCachingScheme<VarT, LiteralT, ClauseIdT>::CacheRecordStruct
    NoneCachingScheme<VarT, LiteralT, ClauseIdT>::createCacheRecordStruct([[maybe_unused]] const VariableSetType& currentComponentVariableSet) const {
        CacheRecordStruct cacheRecordStruct;
        cacheRecordStruct.empty = true;

        return cacheRecordStruct;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void NoneCachingScheme<VarT, LiteralT, ClauseIdT>::processPrintCachingSchemeDebug([[maybe_unused]] std::ostream& out) const { }
    #endif
}   // namespace Hydra::Cache::CachingScheme::None
