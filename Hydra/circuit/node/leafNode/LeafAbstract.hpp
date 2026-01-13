#pragma once

#include "Hydra/circuit/node/NodeAbstract.hpp"

namespace Hydra::Circuit::Node {

    /**
     * Leaf representation (abstract class)
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class LeafAbstract : public NodeAbstract<VarT, LiteralT> {
    protected:
        using BoolVectorType = typename NodeAbstract<VarT, LiteralT>::BoolVectorType;

    public:
        LeafAbstract(IdNodeType id, NodeTypeEnum nodeType, SizeNodeType size) noexcept
            : NodeAbstract<VarT, LiteralT>(id, nodeType, size) { }

    public:
        /**
         * All variables contained in the leaf will be set in the vector.
         * Moreover, the number of used variables will be correspondingly updated.
         */
        virtual void setUsedVariables(BoolVectorType& usedVariableVector, VarT& numberOfUsedVariables) const = 0;
    };
}   // namespace Hydra::Circuit::Node
