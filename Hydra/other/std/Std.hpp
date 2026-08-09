#pragma once

// Forward declaration
namespace Hydra::Formula {
    template <typename VarT2, typename LiteralT2>
    class Literal;
}

namespace std {

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
