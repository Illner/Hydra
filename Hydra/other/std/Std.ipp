#pragma once

#include "./Std.hpp"

namespace std {

    template <typename VarT, typename LiteralT>
    std::size_t hash<Hydra::Formula::Literal<VarT, LiteralT>>::operator()(const Hydra::Formula::Literal<VarT, LiteralT>& lit) const noexcept {
        return static_cast<std::size_t>(lit.getLiteralT());
    }
}   // namespace std
