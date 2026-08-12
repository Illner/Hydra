#pragma once

#include <ostream>
#include <string>
#include <utility>

namespace Hydra::Other::StdExt::InsertionOperator {

    /**
     * ostream << char8_t
     */
    inline std::ostream& operator<<(std::ostream& out, char8_t c);

    /**
     * ostream << char16_t
     */
    inline std::ostream& operator<<(std::ostream& out, char16_t c);

    /**
     * ostream << char32_t
     */
    inline std::ostream& operator<<(std::ostream& out, char32_t c);

    /**
     * ostream << std::pair<TypeT1, TypeT2>
     * Note: used for StackWithLevels
     */
    template <typename TypeT1, typename TypeT2>
    inline std::ostream& operator<<(std::ostream& out, const std::pair<TypeT1, TypeT2>& element);
}   // namespace Hydra::Other::StdExt::InsertionOperator

#include "./InsertionOperator.ipp"
