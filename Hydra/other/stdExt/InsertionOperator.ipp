#pragma once

#include "./InsertionOperator.hpp"

namespace Hydra::Other::StdExt::InsertionOperator {

    std::ostream& operator<<(std::ostream& out, char8_t c) {
        out << std::to_string(c);
        return out;
    }

    std::ostream& operator<<(std::ostream& out, char16_t c) {
        out << std::to_string(c);
        return out;
    }

    std::ostream& operator<<(std::ostream& out, char32_t c) {
        out << std::to_string(c);
        return out;
    }

    template <typename TypeT1, typename TypeT2>
    std::ostream& operator<<(std::ostream& out, const std::pair<TypeT1, TypeT2>& element) {
        out << "(" << element.first << ", " << element.second << ")";
        return out;
    }
}   // namespace Hydra::Other::StdExt::InsertionOperator
