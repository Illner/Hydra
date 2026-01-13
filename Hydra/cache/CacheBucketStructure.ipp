#pragma once

#include "./CacheBucketStructure.hpp"

namespace Hydra::Cache {

    template <typename VarT, typename LiteralT, typename CacheValueT>
    void CacheBucketStruct<VarT, LiteralT, CacheValueT>::printCacheBucketStruct(std::ostream& out) const {
        out << "ID: " << std::to_string(id) << std::endl;

        out << "Value:";
        // ID node
        if constexpr (std::is_same<CacheValueT, IdNodeType>::value)
            out << " " << std::to_string(value);
        // mpz_int
        else if constexpr (std::is_same<CacheValueT, MpzIntType>::value)
            out << " " << value;
        // Custom
        else if constexpr (std::is_same<CacheValueT, CustomType>::value)
            out << " " << value;
        // Variable vector
        else if constexpr (std::is_same<CacheValueT, VariableVectorType>::value) {
            for (VarT var : static_cast<VariableVectorType>(value))
                out << " " << std::to_string(var);
        }
        else
            throw Exception::NotImplementedException("CacheValueT",
                                                     "Hydra::Cache::CacheBucketStruct::printCacheBucketStruct");
        out << std::endl;
    }
}   // namespace Hydra::Cache
