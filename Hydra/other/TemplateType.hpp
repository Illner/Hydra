#pragma once

#include <type_traits>

namespace Hydra::Other {

    template <typename VarT>
    inline constexpr bool isValidVarT = std::is_same_v<VarT, char8_t> ||
                                        std::is_same_v<VarT, char16_t> ||
                                        std::is_same_v<VarT, char32_t>;

    template <typename LiteralT>
    inline constexpr bool isValidLiteralT = std::is_same_v<LiteralT, char8_t> ||
                                            std::is_same_v<LiteralT, char16_t> ||
                                            std::is_same_v<LiteralT, char32_t>;

    template <typename ClauseIdT>
    inline constexpr bool isValidClauseIdT = std::is_same_v<ClauseIdT, char8_t> ||
                                             std::is_same_v<ClauseIdT, char16_t> ||
                                             std::is_same_v<ClauseIdT, char32_t>;
}   // namespace Hydra::Other
