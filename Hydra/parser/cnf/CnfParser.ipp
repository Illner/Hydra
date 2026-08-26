#pragma once

#include "./CnfParser.hpp"

#include <cassert>
#include <iostream>
#include <string>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/vectorSet/VectorSet.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/compiler/exceptions/ParserException.hpp"

namespace Hydra::Parser::Cnf {

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIteratorT>
    ParsedFormulaStruct<VarT, LiteralT, ClauseIdT> parseCnfFormula(InputIteratorT& begin, const InputIteratorT& end,
                                                                   const Other::Parser::DimacsCnfHeaderStruct& dimacsCnfHeaderStruct,
                                                                   unsigned int& line, bool forbidClausesContainingComplementaryLiterals) {
        Cara::ModelCountingTypeEnum dummyModelCountingType = Cara::ModelCountingTypeEnum::UNDEFINED;

        return parseCnfFormula<VarT, LiteralT, ClauseIdT, InputIteratorT>(begin, end,
                                                                          static_cast<VarT>(dimacsCnfHeaderStruct.numberOfVariables),
                                                                          static_cast<ClauseIdT>(dimacsCnfHeaderStruct.numberOfClauses),
                                                                          dimacsCnfHeaderStruct.size,
                                                                          line, dummyModelCountingType, forbidClausesContainingComplementaryLiterals);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIteratorT>
    ParsedFormulaStruct<VarT, LiteralT, ClauseIdT> parseCnfFormula(InputIteratorT& begin, const InputIteratorT& end,
                                                                   const Other::Parser::DimacsCnfHeaderStruct& dimacsCnfHeaderStruct,
                                                                   unsigned int& line, Cara::ModelCountingTypeEnum& modelCountingType,
                                                                   bool forbidClausesContainingComplementaryLiterals) {
        return parseCnfFormula<VarT, LiteralT, ClauseIdT, InputIteratorT>(begin, end,
                                                                          static_cast<VarT>(dimacsCnfHeaderStruct.numberOfVariables),
                                                                          static_cast<ClauseIdT>(dimacsCnfHeaderStruct.numberOfClauses),
                                                                          dimacsCnfHeaderStruct.size,
                                                                          line, modelCountingType, forbidClausesContainingComplementaryLiterals);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIteratorT>
    ParsedFormulaStruct<VarT, LiteralT, ClauseIdT> parseCnfFormula(InputIteratorT& begin, const InputIteratorT& end,
                                                                   VarT numberOfVariables, ClauseIdT numberOfClauses,
                                                                   LargeNumberType size, unsigned int& line,
                                                                   Cara::ModelCountingTypeEnum& modelCountingType,
                                                                   bool forbidClausesContainingComplementaryLiterals) {
        using ParsedFormulaStruct = ParsedFormulaStruct<VarT, LiteralT, ClauseIdT>;

        using LiteralType = ParsedFormulaStruct::LiteralType;
        using FormulaType = ParsedFormulaStruct::FormulaType;
        using VectorSetType = Container::VectorSet::VectorSet;
        using ClauseSizeType = ParsedFormulaStruct::ClauseSizeType;
        using ClauseIdVectorType = ParsedFormulaStruct::ClauseIdVectorType;

        // The formula size + the number of clauses cannot be saved as std::size_t
        LargeNumberType tmp = size + static_cast<LargeNumberType>(numberOfClauses);
        if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(tmp))
            throw Exception::SomethingCannotBeSavedAsStdSizeTException("formula size + number of clauses", tmp);

        // Size
        bool setSize = true;
        LargeNumberType realSize = 0;
        LargeNumberType sizeContainingDuplicateLiterals = 0;
        LargeNumberType sizeContainingComplementaryLiterals = 0;

        // Number of clauses
        ClauseIdT realNumberOfClauses = 0;
        ClauseIdT numberOfClausesContainingComplementaryLiterals = 0;

        // Data structures to detect complementary and duplicate literals in a clause
        VectorSetType positiveLiteralVectorSet(numberOfVariables + 1);
        VectorSetType negativeLiteralVectorSet(numberOfVariables + 1);

        constexpr ClauseSizeType S_ESTIMATED_SIZE_OF_CLAUSE_ = 4;

        // Size is not set
        if (size == 0) {
            setSize = false;
            size = S_ESTIMATED_SIZE_OF_CLAUSE_ * numberOfClauses;
        }

        FormulaType formula;
        formula.reserve(size + numberOfClauses);
        ClauseIdVectorType literalNumberOfOccurrences(static_cast<typename ClauseIdVectorType::size_type>(LiteralT(2) + LiteralT(2) * static_cast<LiteralT>(numberOfVariables)), 0);

        while (begin != end) {
            if (Other::Parser::skipWhitespacesExcludingNewLineSymbol(begin, end))
                break;

            // New line
            if (*begin == '\n') {
                ++line;
                ++begin;
                continue;
            }

            // Comment
            if (Other::Parser::toLowercase(*begin) == Other::Parser::COMMENT) {
                Other::Parser::parseCommentLines(begin, end, line, modelCountingType);
                continue;
            }

            // Clear data structures
            bool clauseIsEmpty = true;
            ClauseSizeType clauseSize = 0;
            positiveLiteralVectorSet.clear();
            negativeLiteralVectorSet.clear();
            bool clauseContainsComplementaryLiterals = false;

            // Parse a clause
            while (begin != end) {
                if (Other::Parser::skipWhitespacesExcludingNewLineSymbol(begin, end))
                    break;

                // The end of the clause
                if (*begin == '0')
                    break;

                // New line
                if (*begin == '\n') {
                    ++line;
                    ++begin;
                    continue;
                }

                LiteralType parsedLiteral = Other::Parser::parseLiteral<VarT, LiteralT>(begin, end, line, {});
                VarT parsedVariable = parsedLiteral.getVariable();

                // The parsed variable is out of range
                if (parsedVariable > numberOfVariables)
                    throw Exception::Parser::ParsedVariableOutOfRangeException<VarT>(parsedVariable);

                // Positive literal
                if (parsedLiteral.isPositive()) {
                    // Duplicate literal
                    if (positiveLiteralVectorSet.contains(parsedVariable)) {
                        ++sizeContainingDuplicateLiterals;

                        continue;
                    }

                    // Complementary literal
                    if (negativeLiteralVectorSet.contains(parsedVariable)) {
                        if (forbidClausesContainingComplementaryLiterals)
                            throw Exception::Parser::ClauseContainsPairOfComplementaryLiteralsException(line);

                        clauseContainsComplementaryLiterals = true;
                    }

                    positiveLiteralVectorSet.emplace(parsedVariable);
                }

                // Negative literal
                else {
                    // Duplicate literal
                    if (negativeLiteralVectorSet.contains(parsedVariable)) {
                        ++sizeContainingDuplicateLiterals;

                        continue;
                    }

                    // Complementary literal
                    if (positiveLiteralVectorSet.contains(parsedVariable)) {
                        if (forbidClausesContainingComplementaryLiterals)
                            throw Exception::Parser::ClauseContainsPairOfComplementaryLiteralsException(line);

                        clauseContainsComplementaryLiterals = true;
                    }

                    negativeLiteralVectorSet.emplace(parsedVariable);
                }

                ++clauseSize;
                clauseIsEmpty = false;
                ++literalNumberOfOccurrences[parsedLiteral.getLiteralT()];
                formula.push_back(std::move(parsedLiteral));
            }

            // The end of the clause is missing
            if (begin == end)
                throw Exception::Parser::SomethingIsExpectedButEndOfStreamIsDetectedException("The end of the clause (0)");

            ++begin;   // 0

            // The clause is empty
            if (clauseIsEmpty)
                throw Exception::Parser::ClauseIsEmptyException(line);

            // The clause contains complementary literals
            if (clauseContainsComplementaryLiterals) {
                assert(formula.size() >= clauseSize);

                ++numberOfClausesContainingComplementaryLiterals;
                sizeContainingComplementaryLiterals += clauseSize;

                for (ClauseSizeType i = 0; i < clauseSize; ++i) {
                    const LiteralType& lit = formula.back();

                    assert(literalNumberOfOccurrences[lit.getLiteralT()] > 0);

                    --literalNumberOfOccurrences[lit.getLiteralT()];

                    formula.pop_back();
                }

                assert(formula.empty() || formula.back().isZeroLiteral());
            }
            else {
                // More clauses than declared
                if (realNumberOfClauses == numberOfClauses)
                    throw Exception::Parser::HeaderValueMentionsFewerClausesThanDeclaredException();

                ++realNumberOfClauses;
                realSize += clauseSize;

                formula.push_back(std::move(Formula::createZeroLiteral<VarT, LiteralT>()));
            }
        }

        if (!setSize)
            formula.shrink_to_fit();

        // The number of clauses does not match the header
        if ((realNumberOfClauses + numberOfClausesContainingComplementaryLiterals) != numberOfClauses)
            std::cerr << "WARNING: the number of clauses does not match the header value." << std::endl
                      << std::endl;

        // The size does not match the header
        if (setSize && ((realSize + sizeContainingComplementaryLiterals + sizeContainingDuplicateLiterals) != size))
            std::cerr << "WARNING: the size does not match the header value." << std::endl
                      << std::endl;

        #if !defined(TEST)
        if (numberOfClausesContainingComplementaryLiterals > 0) {
            std::cerr << "WARNING: " << std::to_string(numberOfClausesContainingComplementaryLiterals) << " ";
            std::cerr << ((numberOfClausesContainingComplementaryLiterals == 1) ? "clause contains" : "clauses contain");
            std::cerr << " complementary literals." << std::endl
                      << std::endl;
        }
        #endif

        return ParsedFormulaStruct(numberOfVariables, realNumberOfClauses,
                                   std::move(formula), std::move(literalNumberOfOccurrences));
    }
}   // namespace Hydra::Parser::Cnf
