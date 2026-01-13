#pragma once

#include "Hydra/circuit/Circuit.hpp"
#include "Hydra/formula/Literal.hpp"

#include "Hydra/circuit/node/enums/DecomposabilityTypeEnum.hpp"

namespace HydraTest::Circuit {

    //region Types
    using IdNodeType = Hydra::Circuit::IdNodeType;
    using DecomposabilityTypeEnum = Hydra::Circuit::Node::DecomposabilityTypeEnum;
    //endregion

    /**
     * (s-)NNF
     */
    template <typename VarT, typename LiteralT>
    inline IdNodeType createNnf(bool smooth, Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot = true);

    /**
     * DNNF
     */
    template <typename VarT, typename LiteralT>
    inline IdNodeType createDnnf(Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot = true);

    /**
     * s-DNNF
     */
    template <typename VarT, typename LiteralT>
    inline IdNodeType createSDnnf(Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot = true);

    /**
     * pwDNNF
     */
    template <typename VarT, typename LiteralT>
    inline IdNodeType createPWDnnf(Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot = true);

    /**
     * nwDNNF
     */
    template <typename VarT, typename LiteralT>
    inline IdNodeType createNWDnnf(Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot = true);

    /**
     * wDNNF 1
     */
    template <typename VarT, typename LiteralT>
    inline IdNodeType createWDnnf1(Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot = true);

    /**
     * wDNNF 2
     */
    template <typename VarT, typename LiteralT>
    inline IdNodeType createWDnnf2(Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot = true);

    /**
     * (s)d-DNNF
     */
    template <typename VarT, typename LiteralT>
    inline IdNodeType createDDnnf(bool smooth, Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot = true);

    /**
     * {Krom-C}-(s)d-BDMC
     */
    template <typename VarT, typename LiteralT>
    inline IdNodeType createKromCDBdmc(bool smooth, Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot = true);

    /**
     * {renH-C}-(s)d-BDMC
     */
    template <typename VarT, typename LiteralT>
    inline IdNodeType createRenHCDBdmc(bool smooth, Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot = true);
}   // namespace HydraTest::Circuit

#include "./CreateCircuit.ipp"
