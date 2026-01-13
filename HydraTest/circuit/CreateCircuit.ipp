#pragma once

#include "./CreateCircuit.hpp"

namespace HydraTest::Circuit {

    template <typename VarT, typename LiteralT>
    IdNodeType createNnf(bool smooth, Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot) {
        using LiteralType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralType;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litNeg2(2, false);

        IdNodeType id2 = circuit.createLiteralLeaf(litPos1);
        IdNodeType id3 = circuit.createLiteralLeaf(litNeg1);
        IdNodeType id5 = circuit.createLiteralLeaf(litNeg2);

        IdNodeType id10;
        if (smooth)
            id10 = circuit.createDecisionInnerNode(3, id5, id2, { (VarT)1 }, { (VarT)2 });
        else
            id10 = circuit.createDecisionInnerNode(3, id5, id2);

        IdNodeType rootId = circuit.createAndInnerNode({ id10, id3 },
                                                       DecomposabilityTypeEnum::NONE);

        if (setRoot)
            circuit.setRoot();

        return rootId;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType createDnnf(Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot) {
        using LiteralType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralType;

        LiteralType litPos1(1, true);
        LiteralType litNeg2(2, false);

        IdNodeType rootId = circuit.createOrInnerNode({ litPos1, litNeg2 });

        if (setRoot)
            circuit.setRoot();

        return rootId;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType createSDnnf(Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot) {
        using LiteralType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralType;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);

        IdNodeType rootId = circuit.createOrInnerNode({ litPos1, litNeg1 });

        if (setRoot)
            circuit.setRoot();

        return rootId;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType createPWDnnf(Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot) {
        using LiteralType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralType;

        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litPos4(4, true);
        LiteralType litPos5(5, true);
        LiteralType litPos6(6, true);

        IdNodeType id2 = circuit.createLiteralLeaf(litPos1);

        IdNodeType id14 = circuit.createOrInnerNode({ litPos1, litPos2, litPos4 });
        IdNodeType id15 = circuit.createOrInnerNode({ litPos1, litPos2, litPos5 });
        IdNodeType id16 = circuit.createOrInnerNode({ litPos2, litPos6 });

        IdNodeType id19 = circuit.createDecisionInnerNode(3, id14, id2);

        IdNodeType rootId = circuit.createAndInnerNode({ id15, id16, id19 },
                                                       DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY);

        if (setRoot)
            circuit.setRoot();

        return rootId;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType createNWDnnf(Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot) {
        using LiteralType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralType;

        LiteralType litPos1(1, true);
        LiteralType litNeg2(2, false);

        IdNodeType id1 = circuit.createConstantLeaf(true);
        IdNodeType id5 = circuit.createLiteralLeaf(litNeg2);

        IdNodeType id8 = circuit.createOrInnerNode({ litPos1, litNeg2 });
        IdNodeType id11 = circuit.createDecisionInnerNode(3, id1, id5);

        IdNodeType rootId = circuit.createAndInnerNode({ id8, id11 },
                                                       DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY);

        if (setRoot)
            circuit.setRoot();

        return rootId;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType createWDnnf1(Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot) {
        using LiteralType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralType;

        LiteralType litPos1(1, true);
        LiteralType litNeg2(2, false);

        IdNodeType id2 = circuit.createLiteralLeaf(litPos1);
        IdNodeType id5 = circuit.createLiteralLeaf(litNeg2);

        IdNodeType id6 = circuit.createOrInnerNode({ litPos1, litNeg2 });
        IdNodeType rootId = circuit.createAndInnerNode({ id2, id5, id6 },
                                                       DecomposabilityTypeEnum::BELLA_DECOMPOSABILITY);

        if (setRoot)
            circuit.setRoot();

        return rootId;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType createWDnnf2(Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot) {
        using LiteralType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralType;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);

        IdNodeType id2 = circuit.createLiteralLeaf(litPos1);
        IdNodeType id3 = circuit.createLiteralLeaf(litNeg1);

        IdNodeType id8 = circuit.createOrInnerNode({ litPos1, litNeg2 });
        IdNodeType id9 = circuit.createAndInnerNode({ id2, id8 },
                                                    DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY);

        IdNodeType id10 = circuit.createOrInnerNode({ litNeg1, litPos2 });
        IdNodeType id11 = circuit.createAndInnerNode({ id3, id10 },
                                                     DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY);

        IdNodeType rootId = circuit.createDecisionInnerNode(3, id9, id11);

        if (setRoot)
            circuit.setRoot();

        return rootId;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType createDDnnf(bool smooth, Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot) {
        using LiteralType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralType;

        LiteralType litPos1(1, true);
        LiteralType litPos3(3, true);
        LiteralType litPos4(4, true);
        LiteralType litPos6(6, true);

        IdNodeType id2 = circuit.createLiteralLeaf(litPos1);
        IdNodeType id6 = circuit.createLiteralLeaf(litPos3);
        IdNodeType id8 = circuit.createLiteralLeaf(litPos4);
        IdNodeType id12 = circuit.createLiteralLeaf(litPos6);

        IdNodeType id16;
        if (smooth)
            id16 = circuit.createDecisionInnerNode(2, id2, id6, { (VarT)3 }, { (VarT)1 });
        else
            id16 = circuit.createDecisionInnerNode(2, id2, id6);

        IdNodeType id19;
        if (smooth)
            id19 = circuit.createDecisionInnerNode(5, id8, id12, { (VarT)6 }, { (VarT)4 });
        else
            id19 = circuit.createDecisionInnerNode(5, id8, id12);

        IdNodeType rootId = circuit.createAndInnerNode({ id16, id19 },
                                                       DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);

        if (setRoot)
            circuit.setRoot();

        return rootId;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType createKromCDBdmc(bool smooth, Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot) {
        using ClauseType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::ClauseType;
        using FormulaType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::FormulaType;
        using LiteralType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralType;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);

        ClauseType clause1({ litPos2, litNeg3 });
        ClauseType clause2({ litNeg2, litPos3 });
        ClauseType clause3({ litPos1 });
        ClauseType clause4({ litNeg1, litPos2 });

        FormulaType formula1 { clause1, clause2 };
        FormulaType formula2 { clause3, clause4 };

        IdNodeType id10 = circuit.createKromCLeaf(formula1);
        IdNodeType id11 = circuit.createKromCLeaf(std::move(formula2));

        IdNodeType rootId;
        if (smooth)
            rootId = circuit.createDecisionInnerNode(4, id10, id11, { (VarT)1 }, { (VarT)3 });
        else
            rootId = circuit.createDecisionInnerNode(4, id10, id11);

        if (setRoot)
            circuit.setRoot();

        return rootId;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType createRenHCDBdmc(bool smooth, Hydra::Circuit::Circuit<VarT, LiteralT>& circuit, bool setRoot) {
        using ClauseType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::ClauseType;
        using FormulaType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::FormulaType;
        using LiteralType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::LiteralType;
        using VariableSetType = typename Hydra::Circuit::Circuit<VarT, LiteralT>::VariableSetType;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);

        ClauseType clause1({ litPos2, litNeg3, litPos5 });
        ClauseType clause2({ litNeg2, litPos3 });
        ClauseType clause3({ litNeg5 });
        ClauseType clause4({ litPos1, litNeg5 });
        ClauseType clause5({ litNeg1, litPos2 });

        FormulaType formula1 { clause1, clause2, clause3 };
        FormulaType formula2 { clause4, clause5 };

        VariableSetType switchedVariables1 { 2, 3, 5 };
        VariableSetType switchedVariables2 { 2 };

        IdNodeType id12 = circuit.createRenHCLeaf(formula1, std::move(switchedVariables1));
        IdNodeType id13 = circuit.createRenHCLeaf(std::move(formula2), switchedVariables2);

        IdNodeType rootId;
        if (smooth)
            rootId = circuit.createDecisionInnerNode(4, id12, id13, { (VarT)1 }, { (VarT)3 });
        else
            rootId = circuit.createDecisionInnerNode(4, id12, id13);

        if (setRoot)
            circuit.setRoot();

        return rootId;
    }
}   // namespace HydraTest::Circuit
