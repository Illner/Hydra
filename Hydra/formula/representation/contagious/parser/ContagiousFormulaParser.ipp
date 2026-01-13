#pragma once

#include "./ContagiousFormulaParser.hpp"

namespace Hydra::Formula::Representation::Contagious::Parser {

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIterator>
    std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseFormula(InputIterator& begin, const InputIterator& end,
                                                                                           const Other::Parser::DimacsCnfHeaderStruct& dimacsCnfHeaderStruct,
                                                                                           unsigned int& line,
                                                                                           bool forbidClausesContainingComplementaryLiterals,
                                                                                           const ContagiousFormulaRepresentationConfiguration& configuration,
                                                                                           FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr) {
        Cara::ModelCountingTypeEnum dummyModelCountingType = Cara::ModelCountingTypeEnum::UNDEFINED;

        return parseFormula<VarT, LiteralT, ClauseIdT, InputIterator>(begin, end,
                                                                      static_cast<VarT>(dimacsCnfHeaderStruct.numberOfVariables),
                                                                      static_cast<ClauseIdT>(dimacsCnfHeaderStruct.numberOfClauses),
                                                                      static_cast<FormulaSizeType>(dimacsCnfHeaderStruct.size),
                                                                      line, dummyModelCountingType, forbidClausesContainingComplementaryLiterals,
                                                                      configuration, formulaRepresentationStatisticsPtr);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIterator>
    std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseFormula(InputIterator& begin, const InputIterator& end,
                                                                                           const Other::Parser::DimacsCnfHeaderStruct& dimacsCnfHeaderStruct,
                                                                                           unsigned int& line, Cara::ModelCountingTypeEnum& modelCountingType,
                                                                                           bool forbidClausesContainingComplementaryLiterals,
                                                                                           const ContagiousFormulaRepresentationConfiguration& configuration,
                                                                                           FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr) {
        return parseFormula<VarT, LiteralT, ClauseIdT, InputIterator>(begin, end,
                                                                      static_cast<VarT>(dimacsCnfHeaderStruct.numberOfVariables),
                                                                      static_cast<ClauseIdT>(dimacsCnfHeaderStruct.numberOfClauses),
                                                                      static_cast<FormulaSizeType>(dimacsCnfHeaderStruct.size),
                                                                      line, modelCountingType, forbidClausesContainingComplementaryLiterals,
                                                                      configuration, formulaRepresentationStatisticsPtr);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT, std::input_iterator InputIterator>
    std::unique_ptr<FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> parseFormula(InputIterator& begin, const InputIterator& end,
                                                                                           VarT numberOfVariables, ClauseIdT numberOfClauses,
                                                                                           FormulaSizeType size, unsigned int& line,
                                                                                           Cara::ModelCountingTypeEnum& modelCountingType,
                                                                                           bool forbidClausesContainingComplementaryLiterals,
                                                                                           const ContagiousFormulaRepresentationConfiguration& configuration,
                                                                                           FormulaRepresentationStatistics::FormulaRepresentationStatisticsPtrType formulaRepresentationStatisticsPtr) {
        using LiteralType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using FormulaType = typename ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>::FormulaType;
        using ClauseSizeType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeType;
        using VariableSetType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using ClauseIdVectorType = typename FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;

        using ContagiousFormulaRepresentationType = ContagiousFormulaRepresentation<VarT, LiteralT, ClauseIdT>;
        using FormulaRepresentationAbstractUniquePtrType = std::unique_ptr<Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>>;

        // The formula size + the clauses cannot be saved as std::size_t
        LargeNumberType tmp = (LargeNumberType)size + (LargeNumberType)numberOfClauses;
        if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(tmp))
            throw Exception::SomethingCannotBeSavedAsStdSizeTException("formula size + clauses", tmp);

        // Statistics
        if (formulaRepresentationStatisticsPtr)
            formulaRepresentationStatisticsPtr->initializeTimer.startStopwatch();

        const ClauseSizeType S_ESTIMATED_SIZE_OF_CLAUSE_ = 4;

        // Size is not set
        if (size == 0)
            size = S_ESTIMATED_SIZE_OF_CLAUSE_ * numberOfClauses;

        FormulaType formula;
        formula.reserve(size + numberOfClauses);
        ClauseIdVectorType literalNumberOfOccurrences(static_cast<typename ClauseIdVectorType::size_type>(LiteralT(2) + LiteralT(2) * static_cast<LiteralT>(numberOfVariables)), 0);

        ClauseIdT realNumberOfClauses = 0;
        ClauseIdT numberOfClausesContainingComplementaryLiterals = 0;

        // Auxiliary data structures
        VariableSetType positiveLiteralSet(numberOfVariables);
        VariableSetType negativeLiteralSet(numberOfVariables);

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
            positiveLiteralSet.clear();
            negativeLiteralSet.clear();
            ClauseSizeType clauseSize = 0;
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
                    // The literal is already in the clause
                    if (Other::containInSet(positiveLiteralSet, parsedVariable))
                        continue;

                    // Complementary literal
                    if (Other::containInSet(negativeLiteralSet, parsedVariable)) {
                        if (forbidClausesContainingComplementaryLiterals)
                            throw Exception::Parser::ClauseContainsPairOfComplementaryLiteralsException(line);

                        clauseContainsComplementaryLiterals = true;
                    }

                    positiveLiteralSet.emplace(parsedVariable);
                }

                // Negative literal
                else {
                    // The literal is already in the clause
                    if (Other::containInSet(negativeLiteralSet, parsedVariable))
                        continue;

                    // Complementary literal
                    if (Other::containInSet(positiveLiteralSet, parsedVariable)) {
                        if (forbidClausesContainingComplementaryLiterals)
                            throw Exception::Parser::ClauseContainsPairOfComplementaryLiteralsException(line);

                        clauseContainsComplementaryLiterals = true;
                    }

                    negativeLiteralSet.emplace(parsedVariable);
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
                formula.push_back(std::move(createZeroLiteral<VarT, LiteralT>()));
            }
        }

        FormulaRepresentationAbstractUniquePtrType formulaRepresentation = std::make_unique<ContagiousFormulaRepresentationType>(std::move(formula),
                                                                                                                                 numberOfVariables,
                                                                                                                                 realNumberOfClauses,
                                                                                                                                 literalNumberOfOccurrences,
                                                                                                                                 configuration,
                                                                                                                                 formulaRepresentationStatisticsPtr);

        if ((realNumberOfClauses + numberOfClausesContainingComplementaryLiterals) != numberOfClauses)
            std::cerr << "WARNING: the number of clauses does not match the header value!" << std::endl
                      << std::endl;

        #if !defined(TEST)
        if (numberOfClausesContainingComplementaryLiterals > 0) {
            std::cerr << "WARNING: " << std::to_string(numberOfClausesContainingComplementaryLiterals) << " ";
            std::cerr << ((numberOfClausesContainingComplementaryLiterals == 1) ? "clause contains" : "clauses contain");
            std::cerr << " complementary literals!" << std::endl
                      << std::endl;
        }
        #endif

        // Statistics
        if (formulaRepresentationStatisticsPtr)
            formulaRepresentationStatisticsPtr->initializeTimer.stopStopwatch();

        return formulaRepresentation;
    }
}   // namespace Hydra::Formula::Representation::Contagious::Parser
