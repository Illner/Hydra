#pragma once

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

#include "Hydra/circuit/Circuit.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/type/arbitraryPrecisionInteger/ArbitraryPrecisionInteger.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Cache {

    using IdType = unsigned long long int;   // at least 64 bits
    using IdNodeType = Hydra::Circuit::IdNodeType;

    /**
     * Cache bucket structure
     * Copy methods are disabled! Move methods (default) are allowed!
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam CacheValueT type used for a cache value
     */
    template <typename VarT, typename LiteralT, typename CacheValueT>
    struct CacheBucketStruct {
    public:
        using VariableVectorType = typename Hydra::Formula::Literal<VarT, LiteralT>::VariableVectorType;

    public:
        using IdVectorType = std::vector<IdType>;
        using IdSortedVectorType = std::vector<IdType>;
        using MpzIntType = Hydra::Type::ArbitraryPrecisionInteger::MpzIntType;
        using CustomType = Hydra::Type::ArbitraryPrecisionInteger::CustomType;

    public:
        using isValidCacheValueT = std::bool_constant<(std::is_same<CacheValueT, IdNodeType>::value ||           // component caching
                                                       std::is_same<CacheValueT, CustomType>::value ||           // #SAT solver (custom)
                                                       std::is_same<CacheValueT, MpzIntType>::value ||           // #SAT solver (mpz_int)
                                                       std::is_same<CacheValueT, VariableVectorType>::value)>;   // hypergraph cut caching

        static_assert(isValidCacheValueT::value, "Invalid CacheValueT type!");

    public:
        explicit CacheBucketStruct(IdType id) noexcept
            : id(id), value() { };

        CacheBucketStruct(const CacheBucketStruct&) = delete;
        CacheBucketStruct(CacheBucketStruct&&) noexcept = default;

        CacheBucketStruct& operator=(const CacheBucketStruct&) = delete;
        CacheBucketStruct& operator=(CacheBucketStruct&&) noexcept = default;

    public:
        IdType id;
        // bool flag;

        CacheValueT value;

    public:
        void printCacheBucketStruct(std::ostream& out) const;
    };
}   // namespace Hydra::Cache

#include "./CacheBucketStructure.ipp"
