#pragma once

#include "./CreateFormula.hpp"

namespace HydraTest::Cache::CachingScheme {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaVariableChar8(VariableSetType& variableSet) {
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos254(254, true);
        LiteralType litNeg254(254, false);
        LiteralType litPos255(255, true);
        LiteralType litNeg255(255, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litPos254, zeroLit,   // 0
            litPos1, litNeg254, zeroLit,   // 1
            litNeg2, litNeg255, zeroLit,   // 2
            litPos2, litPos255, zeroLit    // 3
        };

        VarT numberOfVariables = 255;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 254, 255 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaVariableChar16Low(VariableSetType& variableSet) {
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos255(255, true);
        LiteralType litNeg255(255, false);
        LiteralType litPos256(256, true);
        LiteralType litNeg256(256, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litPos255, zeroLit,   // 0
            litPos1, litNeg255, zeroLit,   // 1
            litNeg2, litNeg256, zeroLit,   // 2
            litPos2, litPos256, zeroLit    // 3
        };

        VarT numberOfVariables = 256;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 255, 256 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaVariableChar16High(VariableSetType& variableSet) {
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos65534(65534, true);
        LiteralType litNeg65534(65534, false);
        LiteralType litPos65535(65535, true);
        LiteralType litNeg65535(65535, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litPos65534, zeroLit,   // 0
            litPos1, litNeg65534, zeroLit,   // 1
            litNeg2, litNeg65535, zeroLit,   // 2
            litPos2, litPos65535, zeroLit    // 3
        };

        VarT numberOfVariables = 65535;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 65534, 65535 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaVariableChar32(VariableSetType& variableSet) {
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos65535(65535, true);
        LiteralType litNeg65535(65535, false);
        LiteralType litPos65536(65536, true);
        LiteralType litNeg65536(65536, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litPos65535, zeroLit,   // 0
            litPos1, litNeg65535, zeroLit,   // 1
            litNeg2, litNeg65536, zeroLit,   // 2
            litPos2, litPos65536, zeroLit    // 3
        };

        VarT numberOfVariables = 65536;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 65535, 65536 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaLiteralChar8(VariableSetType& variableSet) {
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos126(126, true);
        LiteralType litNeg126(126, false);
        LiteralType litPos127(127, true);
        LiteralType litNeg127(127, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litPos126, zeroLit,   // 0
            litPos1, litNeg126, zeroLit,   // 1
            litNeg2, litNeg127, zeroLit,   // 2
            litPos2, litPos127, zeroLit    // 3
        };

        VarT numberOfVariables = 127;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 126, 127 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaLiteralChar16Low(VariableSetType& variableSet) {
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos127(127, true);
        LiteralType litNeg127(127, false);
        LiteralType litPos128(128, true);
        LiteralType litNeg128(128, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litPos127, zeroLit,   // 0
            litPos1, litNeg127, zeroLit,   // 1
            litNeg2, litNeg128, zeroLit,   // 2
            litPos2, litPos128, zeroLit    // 3
        };

        VarT numberOfVariables = 128;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 127, 128 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaLiteralChar16High(VariableSetType& variableSet) {
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos32766(32766, true);
        LiteralType litNeg32766(32766, false);
        LiteralType litPos32767(32767, true);
        LiteralType litNeg32767(32767, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litPos32766, zeroLit,   // 0
            litPos1, litNeg32766, zeroLit,   // 1
            litNeg2, litNeg32767, zeroLit,   // 2
            litPos2, litPos32767, zeroLit    // 3
        };

        VarT numberOfVariables = 32767;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 32766, 32767 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>
    createFormulaLiteralChar32(VariableSetType& variableSet) {
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos32767(32767, true);
        LiteralType litNeg32767(32767, false);
        LiteralType litPos32768(32768, true);
        LiteralType litNeg32768(32768, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litNeg1, litPos32767, zeroLit,   // 0
            litPos1, litNeg32767, zeroLit,   // 1
            litNeg2, litNeg32768, zeroLit,   // 2
            litPos2, litPos32768, zeroLit    // 3
        };

        VarT numberOfVariables = 32768;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        variableSet = { 1, 2, 32767, 32768 };

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormula() {
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
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, litNeg2, litPos3, zeroLit,            // 6
            litPos2, litNeg4, zeroLit,                     // 2
            litNeg1, litPos3, zeroLit,                     // 0
            litPos1, litPos2, zeroLit,                     // 1
            litNeg3, litNeg4, zeroLit,                     // 3
            litNeg1, litPos2, litNeg3, litPos4, zeroLit,   // 9

            litNeg5, litNeg6, litNeg7, zeroLit,   // 7
            litPos5, litPos6, litPos7, zeroLit,   // 8
            litPos5, litPos6, zeroLit,            // 4
            litNeg6, litNeg7, zeroLit             // 5
        };

        VarT numberOfVariables = 7;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForOmittingClauses() {
        LiteralType litPos1(1, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
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
            litNeg2, litPos3, litNeg4, zeroLit,            // 3
            litPos1, litNeg2, litPos3, litPos5, zeroLit,   // 6
            litPos6, litPos8, litPos9, zeroLit,            // 5
            litNeg6, litNeg7, litNeg8, litNeg9, zeroLit,   // 7
            litPos1, litPos3, litNeg5, zeroLit,            // 2
            litPos1, litNeg2, zeroLit,                     // 0
            litPos6, litNeg7, litPos8, zeroLit,            // 4
            litNeg6, litPos7, zeroLit                      // 1
        };

        VarT numberOfVariables = 9;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForMultiOccurrentClauses() {
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
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, litPos2, zeroLit,                     // 2
            litPos4, litPos5, litPos6, zeroLit,            // 10
            litNeg1, litNeg2, zeroLit,                     // 0
            litNeg4, litNeg5, litNeg6, zeroLit,            // 7
            litNeg1, litPos2, zeroLit,                     // 1
            litPos1, litNeg2, litPos3, zeroLit,            // 6
            litPos1, litNeg2, litNeg3, zeroLit,            // 5
            litNeg1, litPos2, litPos3, zeroLit,            // 4
            litNeg1, litPos2, litNeg3, zeroLit,            // 3
            litNeg4, litNeg5, litPos6, zeroLit,            // 8
            litPos4, litNeg5, litNeg6, zeroLit,            // 9
            litNeg4, litNeg5, litPos6, litPos7, zeroLit,   // 11
            litPos4, litNeg5, litNeg6, litNeg7, zeroLit,   // 14
            litNeg4, litPos5, litNeg6, litPos7, zeroLit,   // 13
            litNeg4, litPos5, litNeg6, litNeg7, zeroLit    // 12
        };

        VarT numberOfVariables = 7;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaUnitClauses() {
        LiteralType litPos1(1, true);
        LiteralType litNeg1(1, false);
        LiteralType litPos2(2, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, zeroLit,            // 0
            litNeg2, zeroLit,            // 1
            litNeg1, litPos3, zeroLit,   // 2
            litPos2, litPos3, zeroLit    // 3
        };

        VarT numberOfVariables = 3;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }
}   // namespace HydraTest::Cache::CachingScheme
