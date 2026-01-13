#pragma once

#include "./CreateFormula.hpp"

namespace HydraTest::Cache::CacheCleaningStrategy {

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
        LiteralType litPos8(8, true);
        LiteralType litNeg8(8, false);
        LiteralType litPos9(9, true);
        LiteralType zeroLit = Hydra::Formula::createZeroLiteral<VarT, LiteralT>();

        FormulaType formula {
            litPos1, zeroLit,                                                                           // 0
            litNeg1, litPos2, zeroLit,                                                                  // 1
            litNeg1, litNeg2, litPos3, zeroLit,                                                         // 2
            litNeg1, litNeg2, litNeg3, litPos4, zeroLit,                                                // 3
            litNeg1, litNeg2, litNeg3, litNeg4, litPos5, zeroLit,                                       // 4
            litNeg1, litNeg2, litNeg3, litNeg4, litNeg5, litPos6, zeroLit,                              // 5
            litNeg1, litNeg2, litNeg3, litNeg4, litNeg5, litNeg6, litPos7, zeroLit,                     // 6
            litNeg1, litNeg2, litNeg3, litNeg4, litNeg5, litNeg6, litNeg7, litPos8, zeroLit,            // 7
            litNeg1, litNeg2, litNeg3, litNeg4, litNeg5, litNeg6, litNeg7, litNeg8, litPos9, zeroLit,   // 8
        };

        VarT numberOfVariables = 9;
        ClauseIdVectorType literalNumberOfOccurrences = Hydra::Formula::Representation::Contagious::createLiteralNumberOfOccurrences<VarT, LiteralT, ClauseIdT>(numberOfVariables, formula);
        ClauseIdT numberOfClauses = Hydra::Formula::Representation::Contagious::getNumberOfClauses<VarT, LiteralT, ClauseIdT>(formula);

        return std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                     numberOfVariables, numberOfClauses,
                                                                     literalNumberOfOccurrences);
    }
}   // namespace HydraTest::Cache::CacheCleaningStrategy
