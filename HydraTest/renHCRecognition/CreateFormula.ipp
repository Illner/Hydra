#pragma once

#include "./CreateFormula.hpp"

namespace HydraTest::RenHCRecognition {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormula(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                            bool assignLitNeg4) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using VariableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, litNeg2, zeroLit,                    // 0
            litNeg2, litPos3, zeroLit,                    // 1
            litNeg1, litPos3, litNeg4, zeroLit,           // 2
            litPos1, litPos2, litNeg3, litPos4, zeroLit   // 3
        };

        VarT numberOfVariables = 4;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        // Assign -x_4
        if (assignLitNeg4) {
            variableSet.erase((VarT)4);
            VariableVectorType freeVariableVector;
            formulaRepresentation->addLiteralToPartialAssignment(litNeg4, freeVariableVector);
        }

        return formulaRepresentation;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createMonotoneFormula(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                    bool assignLitPos1) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using VariableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litPos2(2, true);
        LiteralType litNeg3(3, false);
        LiteralType litNeg4(4, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, litPos2, zeroLit,                    // 0
            litNeg3, litNeg4, zeroLit,                    // 1
            litPos2, litNeg3, litNeg4, zeroLit,           // 2
            litPos1, litPos2, litNeg3, litNeg4, zeroLit   // 3
        };

        VarT numberOfVariables = 4;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        // Assign x_1
        if (assignLitPos1) {
            variableSet.erase((VarT)1);
            VariableVectorType freeVariableVector;
            formulaRepresentation->addLiteralToPartialAssignment(litPos1, freeVariableVector);
        }

        return formulaRepresentation;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createCurrentComponentFormula(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                            bool assignLitPos1AndLitPos6) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using VariableVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, litNeg2, zeroLit,            // 0
            litNeg4, litNeg5, zeroLit,            // 1
            litNeg1, litPos2, litPos3, zeroLit,   // 2
            litPos4, litPos5, litNeg6, zeroLit    // 3
        };

        VarT numberOfVariables = 6;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4, 5, 6 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        // Assign x_1, x_6
        if (assignLitPos1AndLitPos6) {
            variableSet.erase((VarT)1);
            variableSet.erase((VarT)6);

            VariableVectorType freeVariableVector;
            formulaRepresentation->addLiteralVectorToPartialAssignment({ litPos1, litPos6 }, freeVariableVector);
        }

        return formulaRepresentation;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCPositive(Hydra::Other::HashMap::SetType<VarT>& variableSet) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos3, litPos4, zeroLit,            // 0
            litPos4, litNeg8, zeroLit,            // 1
            litPos4, litPos8, zeroLit,            // 2
            litNeg1, litPos2, litPos3, zeroLit,   // 3
            litPos1, litNeg2, litPos4, zeroLit,   // 4
            litPos3, litNeg5, litNeg6, zeroLit,   // 5
            litPos3, litNeg5, litNeg7, zeroLit,   // 6
            litPos3, litNeg6, litNeg7, zeroLit    // 7
        };

        VarT numberOfVariables = 8;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        return formulaRepresentation;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createNoRenHCPositive(Hydra::Other::HashMap::SetType<VarT>& variableSet) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litPos9(9, true);
        LiteralType litNeg9(9, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, litNeg5, litPos9, zeroLit,            // 0
            litNeg6, litNeg8, litPos9, zeroLit,            // 1
            litNeg7, litNeg8, litPos9, zeroLit,            // 2
            litPos1, litPos2, litPos3, litPos4, zeroLit,   // 3
            litPos1, litPos6, litPos7, litPos8, zeroLit,   // 4
            litNeg2, litNeg3, litNeg4, litPos9, zeroLit    // 5
        };

        VarT numberOfVariables = 9;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        return formulaRepresentation;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCPartialAssignmentPositive(Hydra::Other::HashMap::SetType<VarT>& variableSet) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litNeg2, litPos3, zeroLit,           // 0
            litNeg1, litPos3, litNeg4, zeroLit,           // 1
            litNeg2, litPos3, litNeg4, zeroLit,           // 2
            litPos1, litPos2, litPos3, litPos4, zeroLit   // 3
        };

        VarT numberOfVariables = 4;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        return formulaRepresentation;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCNegative(Hydra::Other::HashMap::SetType<VarT>& variableSet) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg3, litNeg4, zeroLit,            // 0
            litNeg4, litNeg8, zeroLit,            // 1
            litNeg4, litPos8, zeroLit,            // 2
            litNeg1, litPos2, litNeg3, zeroLit,   // 3
            litPos1, litNeg2, litNeg4, zeroLit,   // 4
            litNeg3, litPos5, litPos6, zeroLit,   // 5
            litNeg3, litPos5, litPos7, zeroLit,   // 6
            litNeg3, litPos6, litPos7, zeroLit    // 7
        };

        VarT numberOfVariables = 8;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        return formulaRepresentation;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createNoRenHCNegative(Hydra::Other::HashMap::SetType<VarT>& variableSet) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litPos9(9, true);
        LiteralType litNeg9(9, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litPos5, litNeg9, zeroLit,            // 0
            litNeg6, litNeg7, litNeg9, zeroLit,            // 1
            litNeg7, litNeg8, litNeg9, zeroLit,            // 2
            litNeg1, litPos2, litPos3, litPos4, zeroLit,   // 3
            litNeg1, litPos6, litPos7, litPos8, zeroLit,   // 4
            litNeg2, litNeg3, litNeg4, litNeg9, zeroLit    // 5
        };

        VarT numberOfVariables = 9;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        return formulaRepresentation;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCPartialAssignmentNegative(Hydra::Other::HashMap::SetType<VarT>& variableSet) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litNeg2, litNeg3, zeroLit,           // 0
            litNeg1, litNeg2, litNeg4, zeroLit,           // 1
            litNeg2, litNeg3, litNeg4, zeroLit,           // 2
            litPos1, litNeg2, litPos3, litPos4, zeroLit   // 3
        };

        VarT numberOfVariables = 4;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        return formulaRepresentation;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCBothPositiveAndNegative(Hydra::Other::HashMap::SetType<VarT>& variableSet) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, litNeg3, zeroLit,            // 0
            litPos1, litPos4, zeroLit,            // 1
            litPos1, litNeg5, zeroLit,            // 2
            litNeg3, litPos7, zeroLit,            // 3
            litNeg3, litNeg8, zeroLit,            // 4
            litPos1, litNeg2, litNeg3, zeroLit,   // 5
            litPos1, litPos2, litNeg3, zeroLit,   // 6
            litPos1, litNeg3, litNeg6, zeroLit,   // 7
            litPos1, litNeg3, litPos6, zeroLit    // 8
        };

        VarT numberOfVariables = 8;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        return formulaRepresentation;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createNoRenHCBothPositiveAndNegative(Hydra::Other::HashMap::SetType<VarT>& variableSet) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litPos9(9, true);
        LiteralType litNeg9(9, false);
        LiteralType litPos10(10, true);
        LiteralType litNeg10(10, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litNeg5, litPos10, zeroLit,           // 0
            litNeg1, litPos6, litPos10, zeroLit,           // 1
            litNeg7, litNeg8, litPos10, zeroLit,           // 2
            litNeg7, litNeg9, litPos10, zeroLit,           // 3
            litNeg1, litPos2, litPos3, litPos4, zeroLit,   // 4
            litNeg1, litPos7, litPos8, litPos9, zeroLit,   // 5
            litNeg2, litNeg3, litNeg4, litPos10, zeroLit   // 6
        };

        VarT numberOfVariables = 10;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        return formulaRepresentation;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCPartialAssignmentBothPositiveAndNegative(Hydra::Other::HashMap::SetType<VarT>& variableSet) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litNeg2, litNeg3, litPos4, zeroLit,            // 0
            litNeg1, litNeg2, litPos4, litNeg5, zeroLit,            // 1
            litNeg2, litNeg3, litPos4, litNeg5, zeroLit,            // 2
            litPos1, litNeg2, litPos3, litPos4, litPos5, zeroLit,   // 3
        };

        VarT numberOfVariables = 5;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4, 5 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        return formulaRepresentation;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHC(Hydra::Other::HashMap::SetType<VarT>& variableSet) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType litPos5(5, true);
        LiteralType litNeg5(5, false);
        LiteralType litPos6(6, true);
        LiteralType litNeg6(6, false);
        LiteralType litPos7(7, true);
        LiteralType litNeg7(7, false);
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litPos9(9, true);
        LiteralType litNeg9(9, false);
        LiteralType litPos10(10, true);
        LiteralType litNeg10(10, false);
        LiteralType litPos11(11, true);
        LiteralType litNeg11(11, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litNeg2, zeroLit,                    // 0
            litNeg2, litNeg3, zeroLit,                    // 1
            litNeg2, litNeg4, zeroLit,                    // 2
            litNeg5, litNeg6, zeroLit,                    // 3
            litNeg5, litNeg7, zeroLit,                    // 4
            litNeg6, litNeg7, zeroLit,                    // 5
            litPos8, litNeg9, zeroLit,                    // 6
            litNeg10, litNeg11, zeroLit,                  // 7
            litPos5, litPos6, litPos7, zeroLit,           // 8
            litPos1, litPos2, litPos3, litPos4, zeroLit   // 9
        };

        VarT numberOfVariables = 11;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        return formulaRepresentation;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createRenHCPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litNeg2, zeroLit,                    // 0
            litNeg1, litNeg3, zeroLit,                    // 1
            litNeg1, litNeg4, zeroLit,                    // 2
            litNeg2, litNeg3, zeroLit,                    // 3
            litNeg2, litNeg4, zeroLit,                    // 4
            litNeg3, litNeg4, zeroLit,                    // 5
            litPos1, litPos2, litPos3, litPos4, zeroLit   // 6
        };

        VarT numberOfVariables = 4;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4 };

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables, numberOfClauses,
                                                                                                                                 literalNumberOfOccurrences);

        return formulaRepresentation;
    }
}   // namespace HydraTest::RenHCRecognition
