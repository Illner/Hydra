#pragma once

#include <cassert>
#include <cctype>
#include <iterator>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "Hydra/circuit/node/NodeAbstract.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/compiler/exceptions/ParserException.hpp"

#include "Cara/sharpSolver/enums/ModelCountingTypeEnum.hpp"

namespace Hydra::Other::Parser {

    using LargeNumberType = Hydra::Other::LargeNumberType;

    inline constexpr char COMMENT = 'c';
    inline constexpr char PROBLEM = 'p';
    inline constexpr char MODEL_COUNTING_HEADER = 't';
    inline constexpr std::string_view CNF_HEADER_STRING = "cnf";

    struct DimacsCnfHeaderStruct {
        LargeNumberType numberOfVariables;
        LargeNumberType numberOfClauses;
        LargeNumberType size;
    };

    /**
     * Skip a line.
     * The new line symbol (\\n) will remain.
     * @return true if the end of the stream has been reached. Otherwise, false is returned.
     */
    template <std::input_iterator InputIterator>
    inline bool skipLine(InputIterator& begin, const InputIterator& end);

    /**
     * Skip all whitespaces, excluding the new line symbol (\\n)
     * @return true if the end of the stream has been reached. Otherwise, false is returned.
     */
    template <std::input_iterator InputIterator>
    inline bool skipWhitespacesExcludingNewLineSymbol(InputIterator& begin, const InputIterator& end);

    /**
     * Parse all whitespaces, excluding the new line symbol (\\n)
     * @return true if at least one whitespace has been parsed. Otherwise, false is returned.
     */
    template <std::input_iterator InputIterator>
    inline bool parseWhitespacesExcludingNewLineSymbol(InputIterator& begin, const InputIterator& end);

    /**
     * Parse a string
     * Note: it parses everything until a whitespace is detected or the end of the stream has been reached
     * @param clearWhitespacesBeforeString true if whitespaces can appear before the string
     * @param expectedSizeOfParsedString an expected size of the parsed string
     * @param toLowercase should the parsed characters be converted to lowercase
     * @return the parsed string
     * @throw SomethingIsExpectedButAnotherSymbolIsDetectedException if an invalid symbol is detected
     * @throw SomethingIsExpectedButEndOfStreamIsDetectedException if the end of the stream is detected while a string is expected
     */
    template <std::input_iterator InputIterator>
    inline std::string parseString(InputIterator& begin, const InputIterator& end, unsigned int line = 0, bool clearWhitespacesBeforeString = true,
                                   std::size_t expectedSizeOfParsedString = 5, bool toLowercase = false);

    /**
     * Parse a positive number
     * @param clearWhitespacesBeforeNumber true if whitespaces can appear before the positive number
     * @return the parsed positive number
     * @throw SomethingIsExpectedButEndOfStreamIsDetectedException if the end of the stream is detected while a number is expected
     * @throw SomethingIsExpectedButAnotherSymbolIsDetectedException if an invalid symbol is detected
     */
    template <typename NumberT, std::input_iterator InputIterator>
    inline NumberT parsePositiveNumber(InputIterator& begin, const InputIterator& end,
                                       unsigned int line = 0, bool clearWhitespacesBeforeNumber = true);

    /**
     * Parse all positive numbers occurring on the line.
     * The new line symbol (\\n) will remain.
     * @return a vector of parsed positive numbers
     * @throw SomethingIsExpectedButAnotherSymbolIsDetectedException if an invalid symbol is detected
     */
    template <typename NumberT, std::input_iterator InputIterator>
    inline std::vector<NumberT> parseAllPositiveNumbersOnLine(InputIterator& begin, const InputIterator& end,
                                                              unsigned int line = 0,
                                                              std::size_t expectedCountOfParsedPositiveNumbers = 1);

    /**
     * Parse a literal
     * @param mappingFromIndexToVar a variable mapping that is used while saving the literal.
     * If a variable does not exist in the mapping, no mapping will be applied to the variable.
     * @return the parsed literal
     * @throw SomethingIsExpectedButEndOfStreamIsDetectedException if the end of the stream is detected while a literal is expected
     * @throw SomethingIsExpectedButAnotherSymbolIsDetectedException if an invalid symbol is detected
     */
    template <typename VarT, typename LiteralT, std::input_iterator InputIterator>
    inline Formula::Literal<VarT, LiteralT> parseLiteral(InputIterator& begin, const InputIterator& end,
                                                         unsigned int line = 0,
                                                         const HashMap::MapType<VarT, VarT>& mappingFromIndexToVar = {});

    /**
     * Parse all literals occurring on the line.
     * The new line symbol (\\n) will remain.
     * @param mappingFromIndexToVar a variable mapping that is used while saving the literals.
     * If a variable does not exist in the mapping, no mapping will be applied to the variable.
     * @return a vector of parsed literals
     * @throw SomethingIsExpectedButAnotherSymbolIsDetectedException if an invalid symbol is detected
     */
    template <typename VarT, typename LiteralT, std::input_iterator InputIterator>
    inline std::vector<Formula::Literal<VarT, LiteralT>> parseAllLiteralsOnLine(InputIterator& begin, const InputIterator& end,
                                                                                unsigned int line = 0,
                                                                                LiteralT expectedCountOfParsedLiterals = 1,
                                                                                const HashMap::MapType<VarT, VarT>& mappingFromIndexToVar = {});

    /**
     * Parse a DIMACS CNF header
     * @return DimacsCnfHeaderStruct(number of variables, number of clauses, size)
     * @throw InvalidDimacsCnfHeaderException if the DIMACS CNF header is invalid
     * @throw SomethingIsExpectedButAnotherSymbolIsDetectedException if an invalid symbol is detected
     * @throw SomethingIsExpectedButEndOfStreamIsDetectedException if the end of the stream is detected while the DIMACS CNF header is expected
     */
    template <std::input_iterator InputIterator>
    inline DimacsCnfHeaderStruct parseDimacsCnfHeader(InputIterator& begin, const InputIterator& end, unsigned int& line);

    /**
     * Parse all the consecutive comment lines
     * Cara: if a model counting header (that is, c t ...) is encountered, modelCountingType is set appropriately
     * @param modelCountingType [output] a model counting type
     * @return true if the end of the stream has been reached. Otherwise, false is returned.
     * @throw InvalidModelCountingHeaderException [Cara] if the model counting header is invalid
     * @throw SomethingIsExpectedButAnotherSymbolIsDetectedException [Cara] if an invalid symbol is detected
     * @throw MoreDifferentModelCountingHeadersExistException [Cara] if more different model counting headers exist
     */
    template <std::input_iterator InputIterator>
    inline bool parseCommentLines(InputIterator& begin, const InputIterator& end, unsigned int& line, Cara::ModelCountingTypeEnum& modelCountingType);

    /**
     * Parse the new line symbol
     * @return true if the end of the stream has been reached. Otherwise, false is returned.
     */
    template <std::input_iterator InputIterator>
    inline bool parseNewLineSymbol(InputIterator& begin, const InputIterator& end, unsigned int& line);

    /**
     * Parse a DIMACS clause
     * @param mappingFromIndexToVar a variable mapping that is used while saving the literals.
     * If a variable does not exist in the mapping, no mapping will be applied to the variable.
     * @return the parsed clause
     * @throw ClauseIsEmptyException if the clause is empty
     * @throw SomethingIsExpectedButAnotherSymbolIsDetectedException if an invalid symbol is detected
     * @throw ClauseContainsPairOfComplementaryLiteralsException if the clause contains a pair of complementary literals
     * @throw SomethingIsExpectedButEndOfStreamIsDetectedException if the end of the stream is detected while the end of the clause (0) is expected
     */
    template <typename VarT, typename LiteralT, std::input_iterator InputIterator>
    inline std::vector<Formula::Literal<VarT, LiteralT>> parseDimacsClause(InputIterator& begin, const InputIterator& end,
                                                                           unsigned int& line,
                                                                           LiteralT expectedParsedClauseSize = 1,
                                                                           const HashMap::MapType<VarT, VarT>& mappingFromIndexToVar = {});

    /**
     * Convert the char to a string
     * @return the converted string
     */
    inline std::string convertCharToString(char ch, bool handleWhitespaces = true);

    /**
     * Convert the string to a positive number
     * @param positiveNumberString a positive number represented as a string
     * @return the converted positive number
     * @throw SomethingIsExpectedButAnotherSymbolIsDetectedException if an invalid symbol is detected
     */
    inline LargeNumberType convertStringToPositiveNumber(const std::string& positiveNumberString);

    /**
     * Check if the char is a digit
     */
    inline bool isDigit(char ch);

    /**
     * Check if the char is a whitespace, including the new line symbol (\\n)
     */
    inline bool isWhitespace(char ch);

    /**
     * Check if the char is a whitespace, excluding the new line symbol (\\n)
     */
    inline bool isWhitespaceExcludingNewLineSymbol(char ch);

    /**
     * Convert the char to lowercase
     */
    inline char toLowercase(char ch);

    /**
     * Convert the char to uppercase
     */
    inline char toUppercase(char ch);
}   // namespace Hydra::Other::Parser

#include "./Parser.ipp"
