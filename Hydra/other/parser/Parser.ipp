#pragma once

#include "./Parser.hpp"

namespace Hydra::Other::Parser {

    template <std::input_iterator InputIterator>
    bool skipLine(InputIterator& begin, const InputIterator& end) {
        while (begin != end) {
            // The end of the line
            if (*begin == '\n')
                return false;

            ++begin;
        }

        return true;
    }

    template <std::input_iterator InputIterator>
    bool skipWhitespacesExcludingNewLineSymbol(InputIterator& begin, const InputIterator& end) {
        while (begin != end) {
            // Non-whitespace symbol has been reached
            if (!isWhitespaceExcludingNewLineSymbol(*begin))
                return false;

            ++begin;
        }

        return true;
    }

    template <std::input_iterator InputIterator>
    bool parseWhitespacesExcludingNewLineSymbol(InputIterator& begin, const InputIterator& end) {
        // The end of the stream
        if (begin == end)
            return false;

        // No whitespace
        if (!isWhitespaceExcludingNewLineSymbol(*begin))
            return false;

        skipWhitespacesExcludingNewLineSymbol(begin, end);

        return true;
    }

    template <std::input_iterator InputIterator>
    std::string parseString(InputIterator& begin, const InputIterator& end, unsigned int line,
                            bool clearWhitespacesBeforeString, std::size_t expectedSizeOfParsedString, bool toLowercase) {
        // The end of the stream
        if ((begin == end) || (clearWhitespacesBeforeString && skipWhitespacesExcludingNewLineSymbol(begin, end)))
            throw Exception::Parser::SomethingIsExpectedButEndOfStreamIsDetectedException("A string");

        if (isWhitespace(*begin)) {
            if (line > 0)
                throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A non-whitespace char", convertCharToString(*begin), line);

            throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A non-whitespace char", convertCharToString(*begin));
        }

        std::string parsedString;
        parsedString.reserve(expectedSizeOfParsedString);

        while (begin != end) {
            // Whitespace
            if (isWhitespace(*begin))
                break;

            if (!toLowercase)
                parsedString.push_back(*begin);
            else
                parsedString.push_back(Other::Parser::toLowercase(*begin));

            ++begin;
        }

        return parsedString;
    }

    template <typename NumberT, std::input_iterator InputIterator>
    NumberT parsePositiveNumber(InputIterator& begin, const InputIterator& end,
                                unsigned int line, bool clearWhitespacesBeforeNumber) {
        // The end of the stream
        if ((begin == end) || (clearWhitespacesBeforeNumber && skipWhitespacesExcludingNewLineSymbol(begin, end)))
            throw Exception::Parser::SomethingIsExpectedButEndOfStreamIsDetectedException("A number");

        if (!isDigit(*begin)) {
            if (line > 0)
                throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A digit", convertCharToString(*begin), line);

            throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A digit", convertCharToString(*begin));
        }

        NumberT number = 0;

        while (begin != end) {
            // Digit
            if (isDigit(*begin)) {
                number = number * static_cast<NumberT>(10) + static_cast<NumberT>(*begin - '0');
                ++begin;
                continue;
            }

            // Whitespace
            else if (isWhitespace(*begin))
                break;

            // Invalid char
            else {
                if (line > 0)
                    throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A digit", convertCharToString(*begin), line);

                throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A digit", convertCharToString(*begin));
            }
        }

        return number;
    }

    template <typename NumberT, std::input_iterator InputIterator>
    std::vector<NumberT> parseAllPositiveNumbersOnLine(InputIterator& begin, const InputIterator& end,
                                                       unsigned int line, std::size_t expectedCountOfParsedPositiveNumbers) {
        std::vector<NumberT> parsedVector;
        parsedVector.reserve(expectedCountOfParsedPositiveNumbers);

        while (begin != end) {
            if (skipWhitespacesExcludingNewLineSymbol(begin, end))
                break;

            // New line
            if (*begin == '\n')
                break;

            parsedVector.push_back(parsePositiveNumber<NumberT>(begin, end, line, false));
        }

        return parsedVector;
    }

    template <typename VarT, typename LiteralT, std::input_iterator InputIterator>
    Formula::Literal<VarT, LiteralT> parseLiteral(InputIterator& begin, const InputIterator& end, unsigned int line,
                                                  const HashMap::MapType<VarT, VarT>& mappingFromIndexToVar) {
        // The end of the stream
        if (skipWhitespacesExcludingNewLineSymbol(begin, end))
            throw Exception::Parser::SomethingIsExpectedButEndOfStreamIsDetectedException("A literal");

        bool isPositive = true;
        if (*begin == '-') {
            isPositive = false;
            ++begin;
        }

        VarT variable = parsePositiveNumber<VarT, InputIterator>(begin, end, line, false);

        // Mapping function is used
        if (auto itTmp = mappingFromIndexToVar.find(variable); itTmp != mappingFromIndexToVar.end())
            variable = itTmp->second;

        Formula::Literal<VarT, LiteralT> literal(variable, isPositive);
        return literal;
    }

    template <typename VarT, typename LiteralT, std::input_iterator InputIterator>
    std::vector<Formula::Literal<VarT, LiteralT>> parseAllLiteralsOnLine(InputIterator& begin, const InputIterator& end,
                                                                         unsigned int line, LiteralT expectedCountOfParsedLiterals,
                                                                         const HashMap::MapType<VarT, VarT>& mappingFromIndexToVar) {
        using LiteralType = Formula::Literal<VarT, LiteralT>;

        std::vector<LiteralType> parsedVector;
        parsedVector.reserve(expectedCountOfParsedLiterals);

        while (begin != end) {
            if (skipWhitespacesExcludingNewLineSymbol(begin, end))
                break;

            // New line
            if (*begin == '\n')
                break;

            LiteralType tmp = parseLiteral<VarT, LiteralT>(begin, end, line, mappingFromIndexToVar);
            parsedVector.push_back(std::move(tmp));
        }

        return parsedVector;
    }

    template <std::input_iterator InputIterator>
    DimacsCnfHeaderStruct parseDimacsCnfHeader(InputIterator& begin, const InputIterator& end, unsigned int& line) {
        bool isDimacsCnfHeaderParsed = false;
        DimacsCnfHeaderStruct dimacsCnfHeaderStruct { 0, 0, 0 };

        while (begin != end) {
            if (skipWhitespacesExcludingNewLineSymbol(begin, end))
                break;

            // New line
            if (*begin == '\n') {
                ++line;
                ++begin;

                if (isDimacsCnfHeaderParsed)
                    break;

                continue;
            }

            // Comment
            if (toLowercase(*begin) == COMMENT) {
                skipLine(begin, end);
                continue;
            }

            // DIMACS CNF header
            else if (toLowercase(*begin) == PROBLEM) {
                ++begin;   // p

                // No whitespace
                if (begin == end)
                    throw Exception::Parser::InvalidDimacsCnfHeaderException("The DIMACS CNF header on line " + std::to_string(line) + " is invalid!");
                if (!isWhitespaceExcludingNewLineSymbol(*begin))
                    throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A whitespace (excluding the new line symbol (\\n)) after the char p in the DIMACS CNF header", convertCharToString(*begin), line);

                if (skipWhitespacesExcludingNewLineSymbol(begin, end))
                    throw Exception::Parser::InvalidDimacsCnfHeaderException("The DIMACS CNF header on line " + std::to_string(line) + " is invalid!");

                // Parse "cnf"
                for (char ch : CNF_HEADER_STRING) {
                    if (begin == end)
                        throw Exception::Parser::InvalidDimacsCnfHeaderException("The DIMACS CNF header on line " + std::to_string(line) + " is invalid!");

                    if (toLowercase(*begin) != ch)
                        throw Exception::Parser::InvalidDimacsCnfHeaderException("The character (" + convertCharToString(*begin) + ") in the DIMACS CNF header on line " + std::to_string(line) + " is invalid!");

                    ++begin;
                }

                // No whitespace
                if (begin == end)
                    throw Exception::Parser::InvalidDimacsCnfHeaderException("The DIMACS CNF header on line " + std::to_string(line) + " is invalid!");
                if (!isWhitespaceExcludingNewLineSymbol(*begin))
                    throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A whitespace (excluding the new line symbol (\\n)) after the string 'cnf' in the DIMACS CNF header", convertCharToString(*begin), line);

                std::vector<LargeNumberType> parsedParameterVector = parseAllPositiveNumbersOnLine<LargeNumberType>(begin, end, line, 3);

                // Invalid number of parameters
                if (parsedParameterVector.size() != 2 && parsedParameterVector.size() != 3)
                    throw Exception::Parser::InvalidDimacsCnfHeaderException("The DIMACS CNF header on line " + std::to_string(line) + " does not have the correct number of parameters!");

                dimacsCnfHeaderStruct.numberOfVariables = parsedParameterVector[0];
                dimacsCnfHeaderStruct.numberOfClauses = parsedParameterVector[1];

                if (parsedParameterVector.size() == 3)
                    dimacsCnfHeaderStruct.size = parsedParameterVector[2];

                isDimacsCnfHeaderParsed = true;
                continue;
            }

            // Invalid char
            else {
                throw Exception::Parser::InvalidDimacsCnfHeaderException("Invalid line " + std::to_string(line) + " (" + convertCharToString(*begin) + "...) has occurred before the DIMACS CNF header!");
            }
        }

        if (!isDimacsCnfHeaderParsed)
            throw Exception::Parser::InvalidDimacsCnfHeaderException("The DIMACS CNF header was not found!");

        return dimacsCnfHeaderStruct;
    }

    template <std::input_iterator InputIterator>
    bool parseCommentLines(InputIterator& begin, const InputIterator& end, unsigned int& line, [[maybe_unused]] Cara::ModelCountingTypeEnum& modelCountingType) {
        using ModelCountingTypeEnum = Cara::ModelCountingTypeEnum;

        [[maybe_unused]] auto setModelCountingTypeLambda = [](ModelCountingTypeEnum& modelCountingType, ModelCountingTypeEnum newModelCountingType) -> void {
            assert(newModelCountingType != ModelCountingTypeEnum::UNDEFINED);   // valid new value

            // Not set
            if (modelCountingType == ModelCountingTypeEnum::UNDEFINED) {
                modelCountingType = newModelCountingType;
                return;
            }

            // The same value has already been set
            if (modelCountingType == newModelCountingType)
                return;

            // There are two different model counting headers
            throw Exception::Parser::MoreDifferentModelCountingHeadersExistException(modelCountingType, newModelCountingType);
        };

        while (begin != end) {
            if (skipWhitespacesExcludingNewLineSymbol(begin, end))
                break;

            // New line
            if (*begin == '\n') {
                ++line;
                ++begin;

                continue;
            }

            // Comment
            if (toLowercase(*begin) == COMMENT) {
                #if defined(BELLA_COMPILER)
                skipLine(begin, end);
                continue;
                #elif defined(CARA_SOLVER)
                ++begin;   // c

                // No whitespace(s)
                if (!parseWhitespacesExcludingNewLineSymbol(begin, end)) {
                    skipLine(begin, end);
                    continue;
                }

                if ((begin == end) || (*begin == '\n'))
                    continue;

                // Model counting header
                if (toLowercase(*begin) == MODEL_COUNTING_HEADER) {
                    ++begin;   // t

                    // Model counting type is missing
                    if ((begin == end) || (*begin == '\n'))
                        throw Exception::Parser::InvalidModelCountingHeaderException("The model counting header on line " + std::to_string(line) + " is invalid!");

                    // No whitespace(s)
                    if (!parseWhitespacesExcludingNewLineSymbol(begin, end)) {
                        skipLine(begin, end);
                        continue;
                    }

                    // Model counting type is missing
                    if ((begin == end) || (*begin == '\n'))
                        throw Exception::Parser::InvalidModelCountingHeaderException("The model counting header on line " + std::to_string(line) + " is invalid!");

                    std::string parsedString = parseString(begin, end, line, false, 4, true);

                    // Model counting
                    if (Cara::modelCountingTypeEnumToStringViewUsedInModelCountingHeader(ModelCountingTypeEnum::MC) == parsedString)
                        setModelCountingTypeLambda(modelCountingType, ModelCountingTypeEnum::MC);
                    // Weighted model counting
                    else if (Cara::modelCountingTypeEnumToStringViewUsedInModelCountingHeader(ModelCountingTypeEnum::WMC) == parsedString)
                        setModelCountingTypeLambda(modelCountingType, ModelCountingTypeEnum::WMC);
                    // Projected model counting
                    else if (Cara::modelCountingTypeEnumToStringViewUsedInModelCountingHeader(ModelCountingTypeEnum::PMC) == parsedString)
                        setModelCountingTypeLambda(modelCountingType, ModelCountingTypeEnum::PMC);
                    // Projected weighted model counting
                    else if (Cara::modelCountingTypeEnumToStringViewUsedInModelCountingHeader(ModelCountingTypeEnum::PWMC) == parsedString)
                        setModelCountingTypeLambda(modelCountingType, ModelCountingTypeEnum::PWMC);
                    // Invalid model counting type
                    else
                        throw Exception::Parser::InvalidModelCountingHeaderException("The model counting header on line " + std::to_string(line) + " has an invalid type (" + parsedString + ")!");

                    // Remove whitespaces
                    if (skipWhitespacesExcludingNewLineSymbol(begin, end))
                        break;

                    if ((begin != end) && (*begin != '\n'))
                        throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A new line (\\n) or the end of the stream",
                                                                                                        convertCharToString(*begin), line);

                    continue;
                }

                skipLine(begin, end);
                continue;
                #endif
            }

            return false;
        }

        return true;
    }

    template <std::input_iterator InputIterator>
    bool parseNewLineSymbol(InputIterator& begin, const InputIterator& end, unsigned int& line) {
        if (skipWhitespacesExcludingNewLineSymbol(begin, end))
            throw Exception::Parser::SomethingIsExpectedButEndOfStreamIsDetectedException("A new line (\\n)");

        if (*begin != '\n')
            throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A new line (\\n)", convertCharToString(*begin), line);

        ++line;
        ++begin;

        if (begin == end)
            return true;

        return false;
    }

    template <typename VarT, typename LiteralT, std::input_iterator InputIterator>
    std::vector<Formula::Literal<VarT, LiteralT>> parseDimacsClause(InputIterator& begin, const InputIterator& end,
                                                                    unsigned int& line,
                                                                    LiteralT expectedParsedClauseSize,
                                                                    const HashMap::MapType<VarT, VarT>& mappingFromIndexToVar) {
        using LiteralType = Formula::Literal<VarT, LiteralT>;
        using VariableSetType = Other::HashMap::SetType<VarT>;

        std::vector<LiteralType> parsedClause;
        parsedClause.reserve(expectedParsedClauseSize);

        VariableSetType positiveLiteralSet(expectedParsedClauseSize);
        VariableSetType negativeLiteralSet(expectedParsedClauseSize);

        while (begin != end) {
            if (skipWhitespacesExcludingNewLineSymbol(begin, end))
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

            LiteralType parsedLiteral = parseLiteral<VarT, LiteralT>(begin, end, line, mappingFromIndexToVar);
            VarT parsedVariable = parsedLiteral.getVariable();

            // Positive literal
            if (parsedLiteral.isPositive()) {
                // The literal is already in the clause
                if (Other::containInSet(positiveLiteralSet, parsedVariable))
                    continue;

                // Complementary literal
                if (Other::containInSet(negativeLiteralSet, parsedVariable))
                    throw Exception::Parser::ClauseContainsPairOfComplementaryLiteralsException(line);

                positiveLiteralSet.emplace(parsedVariable);
            }

            // Negative literal
            else {
                // The literal is already in the clause
                if (Other::containInSet(negativeLiteralSet, parsedVariable))
                    continue;

                // Complementary literal
                if (Other::containInSet(positiveLiteralSet, parsedVariable))
                    throw Exception::Parser::ClauseContainsPairOfComplementaryLiteralsException(line);

                negativeLiteralSet.emplace(parsedVariable);
            }

            parsedClause.push_back(std::move(parsedLiteral));
        }

        // The end of the clause is missing
        if (begin == end)
            throw Exception::Parser::SomethingIsExpectedButEndOfStreamIsDetectedException("The end of the clause (0)");

        ++begin;   // 0

        // The clause is empty
        if (parsedClause.size() == 0)
            throw Exception::Parser::ClauseIsEmptyException(line);

        // The end of the stream
        if (skipWhitespacesExcludingNewLineSymbol(begin, end))
            return parsedClause;

        // New line
        if (*begin == '\n') {
            ++line;
            ++begin;

            return parsedClause;
        }

        // Invalid char
        throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A new line (\\n) or the end of the stream", convertCharToString(*begin), line);
    }

    std::string convertCharToString(char ch, bool handleWhitespaces) {
        if (!handleWhitespaces)
            return std::string(1, ch);

        // New line symbol
        if (ch == '\n')
            return "\\n";

        // Space
        else if (ch == ' ')
            return "'space'";

        // Tabulator
        else if (ch == '\t')
            return "\\t";

        return std::string(1, ch);
    }

    LargeNumberType convertStringToPositiveNumber(const std::string& positiveNumberString) {
        LargeNumberType convertedPositiveNumber = 0;

        for (char ch : positiveNumberString) {
            // Digit
            if (isDigit(ch)) {
                convertedPositiveNumber = convertedPositiveNumber * static_cast<LargeNumberType>(10) + static_cast<LargeNumberType>(ch - '0');
                continue;
            }

            // Invalid char
            throw Exception::Parser::SomethingIsExpectedButAnotherSymbolIsDetectedException("A digit", convertCharToString(ch));
        }

        return convertedPositiveNumber;
    }

    bool isDigit(char ch) {
        return std::isdigit(static_cast<unsigned char>(ch));
    }

    bool isWhitespace(char ch) {
        return std::isspace(static_cast<unsigned char>(ch));
    }

    bool isWhitespaceExcludingNewLineSymbol(char ch) {
        if (ch == '\n')
            return false;

        return std::isspace(static_cast<unsigned char>(ch));
    }

    char toLowercase(char ch) {
        return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }

    char toUppercase(char ch) {
        return static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
    }
}   // namespace Hydra::Other::Parser
