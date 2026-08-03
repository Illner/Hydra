#pragma once

#include "./Std.hpp"

namespace std {

    template <typename TypeT1, typename TypeT2>
    std::string to_string(std::pair<TypeT1, TypeT2> element) {
        return "(" + std::to_string(element.first) + ", " + std::to_string(element.second) + ")";
    }

    template <typename VarT, typename LiteralT>
    std::string to_string(const Hydra::Formula::Literal<VarT, LiteralT>& literal) {
        return literal.toString();
    }

    template <typename VarT, typename LiteralT>
    std::size_t hash<Hydra::Formula::Literal<VarT, LiteralT>>::operator()(const Hydra::Formula::Literal<VarT, LiteralT>& lit) const noexcept {
        return static_cast<std::size_t>(lit.getLiteralT());
    }
}   // namespace std
