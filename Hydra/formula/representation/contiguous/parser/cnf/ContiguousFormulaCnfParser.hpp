#pragma once

#include <iterator>
#include <memory>

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/parser/Parser.hpp"
#include "Hydra/parser/cnf/CnfParser.hpp"

#include "Cara/sharpSolver/enums/ModelCountingTypeEnum.hpp"

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hxx"
#include "Hydra/formula/representation/contiguous/ContiguousFormulaRepresentation.tpp"

namespace Hydra::Formula::Representation::Contiguous::Parser::Cnf {

    using LargeNumberType = Hydra::Parser::Cnf::LargeNumberType;

    /**
     * Parse a formula in the DIMACS CNF format
     * Note: DIMACS CNF header must already be processed
     * Cara: if a model counting header is presented in the stream, modelCountingType is set appropriately
     * @return the parsed formula
     * @throw ClauseIsEmptyException if a clause is empty
     * @throw ParsedVariableOutOfRangeException if a parsed variable is out of range
     * @throw InvalidModelCountingHeaderException [Cara] if the model counting header is invalid
     * @throw MoreDifferentModelCountingHeadersExistException [Cara] if more different model counting headers exist
     * @throw HeaderValueMentionsFewerClausesThanDeclaredException if the header value mentions fewer clauses than declared
     * @throw ClauseContainsPairOfComplementaryLiteralsException [forbidClausesContainingComplementaryLiterals] if a clause contains a pair of complementary literals
     * @throw SomethingIsExpectedButEndOfStreamIsDetectedException, SomethingIsExpectedButAnotherSymbolIsDetectedException if the DIMACS CNF format is invalid
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIteratorT>
    inline std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseCnfFormula(InputIteratorT& begin, const InputIteratorT& end,
                                                                                                     const Other::Parser::DimacsCnfHeaderStruct& dimacsCnfHeaderStruct,
                                                                                                     unsigned int& line, bool forbidClausesContainingComplementaryLiterals = true,
                                                                                                     const ContiguousFormulaRepresentationConfiguration& configuration = ContiguousFormulaRepresentationConfiguration(),
                                                                                                     FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr = nullptr);

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIteratorT>
    inline std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseCnfFormula(InputIteratorT& begin, const InputIteratorT& end,
                                                                                                     const Other::Parser::DimacsCnfHeaderStruct& dimacsCnfHeaderStruct,
                                                                                                     unsigned int& line, Cara::ModelCountingTypeEnum& modelCountingType,
                                                                                                     bool forbidClausesContainingComplementaryLiterals = true,
                                                                                                     const ContiguousFormulaRepresentationConfiguration& configuration = ContiguousFormulaRepresentationConfiguration(),
                                                                                                     FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr = nullptr);

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIteratorT>
    inline std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseCnfFormula(InputIteratorT& begin, const InputIteratorT& end,
                                                                                                     VarT numberOfVariables, ClauseIdT numberOfClauses,
                                                                                                     LargeNumberType size, unsigned int& line,
                                                                                                     Cara::ModelCountingTypeEnum& modelCountingType,
                                                                                                     bool forbidClausesContainingComplementaryLiterals = true,
                                                                                                     const ContiguousFormulaRepresentationConfiguration& configuration = ContiguousFormulaRepresentationConfiguration(),
                                                                                                     FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr = nullptr);
}   // namespace Hydra::Formula::Representation::Contiguous::Parser::Cnf

#include "./ContiguousFormulaCnfParser.ipp"
