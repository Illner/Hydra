#pragma once

#include "./CreateFormula.hpp"

namespace HydraTest::DecisionHeuristic {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForLiteralCount() {
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
            litNeg2, litNeg4, zeroLit,                     // 0
            litPos2, litNeg4, zeroLit,                     // 1
            litNeg3, litNeg5, zeroLit,                     // 2
            litPos1, litNeg3, litNeg6, zeroLit,            // 3
            litNeg2, litNeg3, litNeg6, zeroLit,            // 4
            litPos2, litNeg3, litPos5, zeroLit,            // 5
            litPos1, litNeg2, litPos4, litNeg6, zeroLit,   // 6
            litPos1, litPos2, litPos3, litNeg6, zeroLit,   // 7
            litPos1, litPos3, litPos5, litNeg6, zeroLit    // 8
        };

        VarT numberOfVariables = 6;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForLiteralCountIgnorePureLiterals() {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

        LiteralType litPos1(1, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, zeroLit,                     // 0
            litNeg2, zeroLit,                     // 1
            litPos1, litPos3, zeroLit,            // 2
            litPos1, litNeg4, zeroLit,            // 3
            litNeg2, litNeg3, zeroLit,            // 4
            litNeg2, litPos4, zeroLit,            // 5
            litPos3, litNeg4, zeroLit,            // 6
            litPos1, litNeg2, litNeg3, zeroLit,   // 7
            litPos1, litNeg2, litNeg4, zeroLit    // 8
        };

        VarT numberOfVariables = 4;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForJeroslowWang() {
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
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, litNeg2, zeroLit,                     // 0
            litNeg4, litPos5, zeroLit,                     // 1
            litPos5, litPos6, zeroLit,                     // 2
            litNeg1, litPos3, litNeg6, zeroLit,            // 3
            litPos2, litPos3, litNeg6, zeroLit,            // 4
            litPos1, litNeg3, litPos4, litNeg7, zeroLit,   // 5
            litNeg2, litNeg3, litNeg4, litPos7, zeroLit    // 6
        };

        VarT numberOfVariables = 7;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForJeroslowWangIgnorePureLiterals() {
        using LiteralType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseIdVectorType = typename Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using ContagiousFormulaRepresentationType = Hydra::Formula::Representation::Contagious::ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

        LiteralType litPos1(1, true);
        LiteralType litNeg2(2, false);
        LiteralType litPos3(3, true);
        LiteralType litNeg3(3, false);
        LiteralType litPos4(4, true);
        LiteralType litNeg4(4, false);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, zeroLit,                     // 0
            litNeg2, zeroLit,                     // 1
            litPos1, litPos3, zeroLit,            // 2
            litPos1, litNeg4, zeroLit,            // 3
            litNeg2, litNeg3, zeroLit,            // 4
            litNeg2, litPos4, zeroLit,            // 5
            litPos1, litNeg2, litPos3, zeroLit,   // 6
        };

        VarT numberOfVariables = 4;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createPigeonHoleFormula() {
        unsigned int line = 1;

        std::istringstream stringStream(decisionHeuristicHole6Formula);
        std::istreambuf_iterator<char> begin(stringStream);
        std::istreambuf_iterator<char> end;

        auto header = Hydra::Other::Parser::parseDimacsCnfHeader(begin, end, line);
        return Hydra::Formula::Representation::Contagious::Parser::parseFormula<VarT, LiteralT, ClauseIdT, std::istreambuf_iterator<char>>(begin, end, header, line);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormulaForUpc() {
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
            litNeg1, litNeg5, zeroLit,            // 0
            litPos1, litPos2, zeroLit,            // 1
            litNeg3, litPos4, zeroLit,            // 2
            litNeg3, litNeg5, zeroLit,            // 3
            litPos5, litPos6, zeroLit,            // 4
            litNeg1, litNeg2, litPos3, zeroLit,   // 5
            litPos1, litNeg2, litNeg3, zeroLit    // 6
        };

        VarT numberOfVariables = 6;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }
}   // namespace HydraTest::DecisionHeuristic
