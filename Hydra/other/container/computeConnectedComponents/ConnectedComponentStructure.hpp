#pragma once

#include "Hydra/formula/Literal.hpp"

namespace Hydra::Container::ComputeConnectedComponents {

    /**
     * Connected component structure
     * Copy methods are disabled! Move methods (default) are allowed!
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    struct ConnectedComponentStruct {
    private:
        using VariableSetType = typename Formula::Literal<VarT, LiteralT>::VariableSetType;
        using LiteralVectorType = typename Formula::Literal<VarT, LiteralT>::LiteralVectorType;

    public:
        explicit ConnectedComponentStruct(std::size_t numberOfVariables) noexcept
            : variableSet(numberOfVariables), pureLiteralVector() { };

        ConnectedComponentStruct(const ConnectedComponentStruct&) = delete;
        ConnectedComponentStruct(ConnectedComponentStruct&&) noexcept = default;

        ConnectedComponentStruct& operator=(const ConnectedComponentStruct&) = delete;
        ConnectedComponentStruct& operator=(ConnectedComponentStruct&&) noexcept = default;

    public:
        VariableSetType variableSet;
        LiteralVectorType pureLiteralVector;
    };
}   // namespace Hydra::Container::ComputeConnectedComponents
