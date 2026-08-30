#pragma once

#include "./ContiguousFormulaCnfParser.hpp"

#include "Hydra/formula/representation/contiguous/ContiguousFormulaRepresentation.hpp"
#include "Hydra/parser/cnf/ParsedFormulaStructure.hpp"

namespace Hydra::Formula::Representation::Contiguous::Parser::Cnf {

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIteratorT>
    std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseCnfFormula(InputIteratorT& begin, const InputIteratorT& end,
                                                                                              const Other::Parser::DimacsCnfHeaderStruct& dimacsCnfHeaderStruct,
                                                                                              unsigned int& line,
                                                                                              bool forbidClausesContainingComplementaryLiterals,
                                                                                              const ContiguousFormulaRepresentationConfiguration& configuration,
                                                                                              FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr) {
        Cara::ModelCountingTypeEnum dummyModelCountingType = Cara::ModelCountingTypeEnum::UNDEFINED;

        return parseCnfFormula<VarT, LiteralT, ClauseIdT, InputIteratorT>(begin, end,
                                                                          static_cast<VarT>(dimacsCnfHeaderStruct.numberOfVariables),
                                                                          static_cast<ClauseIdT>(dimacsCnfHeaderStruct.numberOfClauses),
                                                                          dimacsCnfHeaderStruct.size,
                                                                          line, dummyModelCountingType, forbidClausesContainingComplementaryLiterals,
                                                                          configuration, formulaRepresentationStatisticsPtr);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIteratorT>
    std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseCnfFormula(InputIteratorT& begin, const InputIteratorT& end,
                                                                                              const Other::Parser::DimacsCnfHeaderStruct& dimacsCnfHeaderStruct,
                                                                                              unsigned int& line, Cara::ModelCountingTypeEnum& modelCountingType,
                                                                                              bool forbidClausesContainingComplementaryLiterals,
                                                                                              const ContiguousFormulaRepresentationConfiguration& configuration,
                                                                                              FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr) {
        return parseCnfFormula<VarT, LiteralT, ClauseIdT, InputIteratorT>(begin, end,
                                                                          static_cast<VarT>(dimacsCnfHeaderStruct.numberOfVariables),
                                                                          static_cast<ClauseIdT>(dimacsCnfHeaderStruct.numberOfClauses),
                                                                          dimacsCnfHeaderStruct.size,
                                                                          line, modelCountingType, forbidClausesContainingComplementaryLiterals,
                                                                          configuration, formulaRepresentationStatisticsPtr);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIteratorT>
    std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseCnfFormula(InputIteratorT& begin, const InputIteratorT& end,
                                                                                              VarT numberOfVariables, ClauseIdT numberOfClauses,
                                                                                              LargeNumberType size, unsigned int& line,
                                                                                              Cara::ModelCountingTypeEnum& modelCountingType,
                                                                                              bool forbidClausesContainingComplementaryLiterals,
                                                                                              const ContiguousFormulaRepresentationConfiguration& configuration,
                                                                                              FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr) {
        using ParsedFormulaStruct = Hydra::Parser::Cnf::ParsedFormulaStruct<VarT, LiteralT, ClauseIdT>;
        using ContiguousFormulaRepresentationType = ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        // Statistics
        if (formulaRepresentationStatisticsPtr)
            formulaRepresentationStatisticsPtr->initializeTimer.startStopwatch();

        ParsedFormulaStruct parsedFormulaStruct = Hydra::Parser::Cnf::parseCnfFormula<VarT, LiteralT, ClauseIdT>(begin, end,
                                                                                                                 numberOfVariables, numberOfClauses, size,
                                                                                                                 line, modelCountingType,
                                                                                                                 forbidClausesContainingComplementaryLiterals);

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContiguousFormulaRepresentationType>(std::move(parsedFormulaStruct.formula),
                                                                                                                                 parsedFormulaStruct.numberOfVariables,
                                                                                                                                 parsedFormulaStruct.numberOfClauses,
                                                                                                                                 parsedFormulaStruct.literalNumberOfOccurrences,
                                                                                                                                 configuration,
                                                                                                                                 formulaRepresentationStatisticsPtr);

        // Statistics
        if (formulaRepresentationStatisticsPtr)
            formulaRepresentationStatisticsPtr->initializeTimer.stopStopwatch();

        return formulaRepresentation;
    }
}   // namespace Hydra::Formula::Representation::Contiguous::Parser::Cnf
