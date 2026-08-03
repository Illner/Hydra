#pragma once

#include <string>
#include <utility>

#include "Hydra/formula/Literal.hpp"

// Forward declaration
namespace Hydra::Formula {
    template <typename VarT2, typename LiteralT2>
    class Literal;
}

namespace std {

    /**
     * An overloading for std::to_string so it can also print pairs
     * Note: used for StackWithLevels
     * Note: TypeT1 and TypeT2 are expected to be types which can be quickly copied
     */
    template <typename TypeT1, typename TypeT2>
    inline std::string to_string(std::pair<TypeT1, TypeT2> element);

    /**
     * An overloading for std::to_string so it can also print literals
     * Note: used for ReusableVector
     */
    template <typename VarT, typename LiteralT>
    inline std::string to_string(const Hydra::Formula::Literal<VarT, LiteralT>& literal);

    /**
     * Hash for literals
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    struct hash<Hydra::Formula::Literal<VarT, LiteralT>> {
        std::size_t operator()(const Hydra::Formula::Literal<VarT, LiteralT>& lit) const noexcept;
    };
}   // namespace std

#include "./Std.ipp"
