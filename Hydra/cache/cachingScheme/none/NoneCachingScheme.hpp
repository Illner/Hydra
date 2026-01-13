#pragma once

#include <iostream>

#include "Hydra/cache/CacheRecordStructure.hpp"
#include "Hydra/cache/cachingScheme/CachingSchemeAbstract.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"

#include "Hydra/cache/cachingScheme/enums/CachingSchemeTypeEnum.hpp"
#include "Hydra/cache/cachingScheme/enums/SaveTypeEnum.hpp"
#include "Hydra/cache/enums/CacheTypeEnum.hpp"

namespace Hydra::Cache::CachingScheme::None {

    using LargeNumberType = Hydra::Cache::CachingScheme::LargeNumberType;

    /**
     * None caching scheme (final class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class NoneCachingScheme final : public CachingSchemeAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using VariableSetType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using FormulaRepresentationAbstractPtrType = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    private:
        using CacheRecordStruct = typename CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>::CacheRecordStruct;

    public:
        NoneCachingScheme(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr, CacheTypeEnum cacheType) noexcept
            : CachingSchemeAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr, CachingSchemeTypeEnum::NONE,
                                                               cacheType, SaveTypeEnum::NONE, false) { }

    private:
        LargeNumberType maxByteSizeKey() const override;

        CacheRecordStruct createCacheRecordStruct(const VariableSetType& currentComponentVariableSet) const override;

    #ifndef NDEBUG
    private:
        void processPrintCachingSchemeDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::Cache::CachingScheme::None

#include "./NoneCachingScheme.ipp"
