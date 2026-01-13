#pragma once

#include <cassert>
#include <iterator>
#include <memory>
#include <string>

#include "Hydra/circuit/node/NodeAbstract.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/parser/Parser.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/compiler/exceptions/ParserException.hpp"

#include "Cara/sharpSolver/enums/ModelCountingTypeEnum.hpp"

#include "Hydra/formula/representation/FormulaRepresentationAbstract.hxx"
#include "Hydra/formula/representation/contagious/ContagiousFormulaRepresentation.tpp"

namespace Hydra::Formula::Representation::Contagious::Parser {

    using LargeNumberType = Hydra::Circuit::Node::LargeNumberType;
    using FormulaSizeType = Hydra::Formula::Representation::FormulaSizeType;

    /**
     * Parse a formula in the DIMACS CNF format
     * Note: DIMACS CNF header must be already processed
     * Cara: if a model counting header is presented in the stream, modelCountingType is appropriately set
     * @return the parsed formula
     * @throw ClauseIsEmptyException if a clause is empty
     * @throw ParsedVariableOutOfRangeException if a parsed variable is out of range
     * @throw InvalidModelCountingHeaderException [Cara] if the model counting header is invalid
     * @throw MoreDifferentModelCountingHeadersExistException [Cara] if more different model counting headers exist
     * @throw HeaderValueMentionsFewerClausesThanDeclaredException if the header value mentions fewer clauses than declared
     * @throw ClauseContainsPairOfComplementaryLiteralsException [forbidClausesContainingComplementaryLiterals] if a clause contains a pair of complementary literals
     * @throw SomethingIsExpectedButEndOfStreamIsDetectedException, SomethingIsExpectedButAnotherSymbolIsDetectedException if the DIMACS CNF format is invalid
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIterator>
    inline std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseFormula(InputIterator& begin, const InputIterator& end,
                                                                                                  const Other::Parser::DimacsCnfHeaderStruct& dimacsCnfHeaderStruct,
                                                                                                  unsigned int& line, bool forbidClausesContainingComplementaryLiterals = true,
                                                                                                  const ContagiousFormulaRepresentationConfiguration& configuration = ContagiousFormulaRepresentationConfiguration(),
                                                                                                  FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr = nullptr);

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIterator>
    inline std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseFormula(InputIterator& begin, const InputIterator& end,
                                                                                                  const Other::Parser::DimacsCnfHeaderStruct& dimacsCnfHeaderStruct,
                                                                                                  unsigned int& line, Cara::ModelCountingTypeEnum& modelCountingType,
                                                                                                  bool forbidClausesContainingComplementaryLiterals = true,
                                                                                                  const ContagiousFormulaRepresentationConfiguration& configuration = ContagiousFormulaRepresentationConfiguration(),
                                                                                                  FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr = nullptr);

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIterator>
    inline std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseFormula(InputIterator& begin, const InputIterator& end,
                                                                                                  VarT numberOfVariables, ClauseIdT numberOfClauses,
                                                                                                  FormulaSizeType size, unsigned int& line,
                                                                                                  Cara::ModelCountingTypeEnum& modelCountingType,
                                                                                                  bool forbidClausesContainingComplementaryLiterals = true,
                                                                                                  const ContagiousFormulaRepresentationConfiguration& configuration = ContagiousFormulaRepresentationConfiguration(),
                                                                                                  FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr = nullptr);
}   // namespace Hydra::Formula::Representation::Contagious::Parser

#include "./ContagiousFormulaParser.ipp"
