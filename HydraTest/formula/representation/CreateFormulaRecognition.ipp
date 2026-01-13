#pragma once

#include "./CreateFormulaRecognition.hpp"

namespace HydraTest::Formula::Representation::Recognition {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaWithConnectedComponents(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                                   const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

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
            litPos1, litPos2, zeroLit,                     // 0
            litNeg2, litNeg9, zeroLit,                     // 1
            litPos1, litNeg6, litPos7, zeroLit,            // 2
            litPos3, litNeg4, litNeg9, zeroLit,            // 3
            litPos1, litPos6, litPos7, litPos8, zeroLit,   // 4
            litNeg3, litNeg4, litNeg5, litNeg9, zeroLit    // 5
        };

        VarT numberOfVariables = 9;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaWithConnectedComponentsPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                                                    const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

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
            litPos1, litNeg2, litNeg3, zeroLit,            // 0
            litPos1, litPos2, litPos3, zeroLit,            // 1
            litPos4, litPos5, litPos6, zeroLit,            // 2
            litNeg7, litNeg8, litNeg9, zeroLit,            // 3
            litNeg1, litNeg4, litNeg5, litNeg6, zeroLit,   // 4
            litNeg1, litPos7, litPos8, litPos9, zeroLit    // 5
        };

        VarT numberOfVariables = 9;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createTrivialFormula(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                   const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litPos2, zeroLit,   // 0
            litPos1, litNeg2, zeroLit    // 1
        };

        VarT numberOfVariables = 2;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaWithPureClauses(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                           const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

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
            litPos1, litNeg2, zeroLit,                    // 0
            litNeg2, litPos5, zeroLit,                    // 1
            litPos2, litNeg3, zeroLit,                    // 2
            litNeg4, litPos5, zeroLit,                    // 3
            litNeg5, litPos6, zeroLit,                    // 4
            litPos1, litNeg3, litNeg4, litPos6, zeroLit   // 5
        };

        VarT numberOfVariables = 6;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4, 5, 6 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createKromC(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                          const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

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
            litNeg1, litNeg4, zeroLit,   // 0
            litPos1, litPos2, zeroLit,   // 1
            litNeg2, litPos3, zeroLit,   // 2
            litPos3, litNeg4, zeroLit    // 3
        };

        VarT numberOfVariables = 4;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createKromCPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                           const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

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
            litNeg1, litNeg4, litNeg5, zeroLit,                    // 0
            litPos1, litPos2, litNeg5, zeroLit,                    // 1
            litNeg2, litPos3, litNeg5, zeroLit,                    // 2
            litPos3, litNeg4, litNeg5, zeroLit,                    // 3
            litNeg1, litPos2, litPos3, litNeg4, litPos5, zeroLit   // 4
        };

        VarT numberOfVariables = 5;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4, 5 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createNotKromC(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                             const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litNeg3, zeroLit,           // 0
            litPos1, litPos2, zeroLit,           // 1
            litNeg2, litPos3, zeroLit,           // 2
            litPos1, litNeg2, litPos3, zeroLit   // 3
        };

        VarT numberOfVariables = 3;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createHornC(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                          const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, zeroLit,                     // 0
            litNeg2, zeroLit,                     // 1
            litNeg1, litNeg2, zeroLit,            // 2
            litNeg1, litPos2, zeroLit,            // 3
            litPos1, litNeg2, zeroLit,            // 4
            litNeg1, litNeg2, litNeg3, zeroLit,   // 5
            litNeg1, litNeg2, litPos3, zeroLit,   // 6
            litNeg1, litPos2, litNeg3, zeroLit,   // 7
            litPos1, litNeg2, litNeg3, zeroLit    // 8
        };

        VarT numberOfVariables = 3;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createHornCPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                           const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

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
            litPos1, litPos3, zeroLit,                     // 0
            litNeg2, litPos3, zeroLit,                     // 1
            litNeg1, litNeg2, litPos3, zeroLit,            // 2
            litNeg1, litPos2, litPos3, zeroLit,            // 3
            litPos1, litNeg2, litPos3, zeroLit,            // 4
            litPos1, litPos2, litNeg3, zeroLit,            // 5
            litNeg1, litNeg2, litPos3, litNeg4, zeroLit,   // 6
            litNeg1, litNeg2, litPos3, litPos4, zeroLit,   // 7
            litNeg1, litPos2, litPos3, litNeg4, zeroLit,   // 8
            litPos1, litNeg2, litPos3, litNeg4, zeroLit    // 9
        };

        VarT numberOfVariables = 4;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createNotHornC(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                             const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litNeg2, zeroLit,            // 0
            litNeg1, litPos2, zeroLit,            // 1
            litPos1, litNeg2, zeroLit,            // 2
            litPos1, litPos2, zeroLit,            // 3
            litNeg1, litNeg2, litNeg3, zeroLit,   // 4
            litNeg1, litNeg2, litPos3, zeroLit,   // 5
            litNeg1, litPos2, litNeg3, zeroLit,   // 6
            litPos1, litNeg2, litNeg3, zeroLit    // 7
        };

        VarT numberOfVariables = 3;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createAntiHornC(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                              const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, zeroLit,                     // 0
            litNeg2, zeroLit,                     // 1
            litNeg1, litPos2, zeroLit,            // 2
            litPos1, litNeg2, zeroLit,            // 3
            litPos1, litPos2, zeroLit,            // 4
            litNeg1, litPos2, litPos3, zeroLit,   // 5
            litPos1, litNeg2, litPos3, zeroLit,   // 6
            litPos1, litPos2, litNeg3, zeroLit,   // 7
            litPos1, litPos2, litPos3, zeroLit    // 8
        };

        VarT numberOfVariables = 3;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createAntiHornCPartialAssignment(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                               const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

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
            litPos1, litNeg2, zeroLit,                     // 0
            litNeg2, litNeg3, zeroLit,                     // 1
            litNeg1, litNeg2, litPos3, zeroLit,            // 2
            litNeg1, litPos2, litNeg3, zeroLit,            // 3
            litPos1, litNeg2, litNeg3, zeroLit,            // 4
            litPos1, litNeg2, litPos3, zeroLit,            // 5
            litNeg1, litNeg2, litPos3, litPos4, zeroLit,   // 6
            litPos1, litNeg2, litNeg3, litPos4, zeroLit,   // 7
            litPos1, litNeg2, litPos3, litNeg4, zeroLit,   // 8
            litPos1, litNeg2, litPos3, litPos4, zeroLit    // 9
        };

        VarT numberOfVariables = 4;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3, 4 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createNotAntiHornC(Hydra::Other::HashMap::SetType<VarT>& variableSet,
                                                                                                                                 const Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentationConfiguration& configuration) {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litNeg2, zeroLit,            // 0
            litNeg1, litPos2, zeroLit,            // 1
            litPos1, litNeg2, zeroLit,            // 2
            litPos1, litPos2, zeroLit,            // 3
            litNeg1, litPos2, litPos3, zeroLit,   // 4
            litPos1, litNeg2, litPos3, zeroLit,   // 5
            litPos1, litPos2, litNeg3, zeroLit,   // 6
            litPos1, litPos2, litPos3, zeroLit    // 7
        };

        VarT numberOfVariables = 3;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 3 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences,
                                                                     configuration);
    }
}   // namespace HydraTest::Formula::Representation::Recognition
