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
                                                                                              FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr,
                                                                                              Hydra::Parser::Cnf::CnfParserStatistics::CnfParserStatisticsPtrType cnfParserStatisticsPtr) {
        Cara::ModelCountingTypeEnum dummyModelCountingType = Cara::ModelCountingTypeEnum::UNDEFINED;

        return parseCnfFormula<VarT, LiteralT, ClauseIdT, InputIteratorT>(begin, end,
                                                                          static_cast<VarT>(dimacsCnfHeaderStruct.numberOfVariables),
                                                                          static_cast<ClauseIdT>(dimacsCnfHeaderStruct.numberOfClauses),
                                                                          dimacsCnfHeaderStruct.size,
                                                                          line, dummyModelCountingType, forbidClausesContainingComplementaryLiterals,
                                                                          configuration, formulaRepresentationStatisticsPtr, cnfParserStatisticsPtr);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIteratorT>
    std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseCnfFormula(InputIteratorT& begin, const InputIteratorT& end,
                                                                                              const Other::Parser::DimacsCnfHeaderStruct& dimacsCnfHeaderStruct,
                                                                                              unsigned int& line, Cara::ModelCountingTypeEnum& modelCountingType,
                                                                                              bool forbidClausesContainingComplementaryLiterals,
                                                                                              const ContiguousFormulaRepresentationConfiguration& configuration,
                                                                                              FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr,
                                                                                              Hydra::Parser::Cnf::CnfParserStatistics::CnfParserStatisticsPtrType cnfParserStatisticsPtr) {
        return parseCnfFormula<VarT, LiteralT, ClauseIdT, InputIteratorT>(begin, end,
                                                                          static_cast<VarT>(dimacsCnfHeaderStruct.numberOfVariables),
                                                                          static_cast<ClauseIdT>(dimacsCnfHeaderStruct.numberOfClauses),
                                                                          dimacsCnfHeaderStruct.size,
                                                                          line, modelCountingType, forbidClausesContainingComplementaryLiterals,
                                                                          configuration, formulaRepresentationStatisticsPtr, cnfParserStatisticsPtr);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIteratorT>
    std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseCnfFormula(InputIteratorT& begin, const InputIteratorT& end,
                                                                                              VarT numberOfVariables, ClauseIdT numberOfClauses,
                                                                                              LargeNumberType size, unsigned int& line,
                                                                                              Cara::ModelCountingTypeEnum& modelCountingType,
                                                                                              bool forbidClausesContainingComplementaryLiterals,
                                                                                              const ContiguousFormulaRepresentationConfiguration& configuration,
                                                                                              FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr,
                                                                                              Hydra::Parser::Cnf::CnfParserStatistics::CnfParserStatisticsPtrType cnfParserStatisticsPtr) {
        using ParsedFormulaStruct = Hydra::Parser::Cnf::ParsedFormulaStruct<VarT, LiteralT, ClauseIdT>;
        using ContiguousFormulaRepresentationType = ContiguousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;

        ParsedFormulaStruct parsedFormulaStruct = Hydra::Parser::Cnf::parseCnfFormula<VarT, LiteralT, ClauseIdT>(begin, end,
                                                                                                                 numberOfVariables, numberOfClauses, size,
                                                                                                                 line, modelCountingType,
                                                                                                                 forbidClausesContainingComplementaryLiterals,
                                                                                                                 cnfParserStatisticsPtr);

        return std::make_unique<ContiguousFormulaRepresentationType>(std::move(parsedFormulaStruct), configuration, formulaRepresentationStatisticsPtr);
    }
}   // namespace Hydra::Formula::Representation::Contiguous::Parser::Cnf
