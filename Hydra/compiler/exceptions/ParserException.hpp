#pragma once

#include <string>

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Cara/sharpSolver/enums/ModelCountingTypeEnum.hpp"

namespace Hydra::Exception::Parser {

    /**
     * Parser exception (main)
     */
    class ParserException : public CompilerException {
    public:
        explicit ParserException(const std::string& message)
            : CompilerException(message) { }

        explicit ParserException(std::string&& message)
            : CompilerException(std::move(message)) { }
    };

    /**
     * Something is expected, but the end of the stream is detected
     */
    class SomethingIsExpectedButEndOfStreamIsDetectedException : public ParserException {
    public:
        explicit SomethingIsExpectedButEndOfStreamIsDetectedException(const std::string& whatIsExpected)
            : ParserException(whatIsExpected + " is expected, but the end of the stream is detected!") { }
    };

    /**
     * Something is expected, but another symbol is detected
     */
    class SomethingIsExpectedButAnotherSymbolIsDetectedException : public ParserException {
    public:
        explicit SomethingIsExpectedButAnotherSymbolIsDetectedException(const std::string& whatIsExpected,
                                                                        const std::string& whatIsDetected)
            : ParserException(whatIsExpected + " is expected, but another symbol (" + whatIsDetected + ") is detected!") { }

        SomethingIsExpectedButAnotherSymbolIsDetectedException(const std::string& whatIsExpected,
                                                               const std::string& whatIsDetected, unsigned int line)
            : ParserException(whatIsExpected + " is expected, but another symbol (" + whatIsDetected + ") is detected on line " + std::to_string(line) + "!") { }
    };

    /**
     * DIMACS CNF header is invalid
     */
    class InvalidDimacsCnfHeaderException : public ParserException {
    public:
        explicit InvalidDimacsCnfHeaderException(const std::string& message)
            : ParserException(message) { }

        explicit InvalidDimacsCnfHeaderException(std::string&& message)
            : ParserException(std::move(message)) { }
    };

    /**
     * Clause is empty
     */
    class ClauseIsEmptyException : public ParserException {
    public:
        explicit ClauseIsEmptyException(unsigned int line)
            : ParserException("The clause on line " + std::to_string(line) + " is empty!") { }
    };

    /**
     * Clause contains a pair of complementary literals
     */
    class ClauseContainsPairOfComplementaryLiteralsException : public ParserException {
    public:
        explicit ClauseContainsPairOfComplementaryLiteralsException(unsigned int line)
            : ParserException("The clause on line " + std::to_string(line) + " contains a pair of complementary literals!") { }
    };

    /**
     * Parsed variable out of range
     */
    template <typename VarT>
    class ParsedVariableOutOfRangeException : public ParserException {
    public:
        explicit ParsedVariableOutOfRangeException(VarT variable)
            : ParserException("The parsed variable (" + std::to_string(variable) + ") is out of range!") { }
    };

    /**
     * Header value mentions fewer clauses than declared
     */
    class HeaderValueMentionsFewerClausesThanDeclaredException : public ParserException {
    public:
        HeaderValueMentionsFewerClausesThanDeclaredException()
            : ParserException("The header value mentions fewer clauses than declared!") { }
    };

    /**
     * Model counting header is invalid
     */
    class InvalidModelCountingHeaderException : public ParserException {
    public:
        explicit InvalidModelCountingHeaderException(const std::string& message)
            : ParserException(message) { }

        explicit InvalidModelCountingHeaderException(std::string&& message)
            : ParserException(std::move(message)) { }
    };

    /**
     * More different model counting headers exist
     */
    class MoreDifferentModelCountingHeadersExistException : public ParserException {
    public:
        MoreDifferentModelCountingHeadersExistException(Cara::ModelCountingTypeEnum firstModelCountingType, Cara::ModelCountingTypeEnum secondModelCountingType)
            : ParserException("More different model counting headers exist (" +
                              Cara::modelCountingTypeEnumToString(firstModelCountingType) + ", and " +
                              Cara::modelCountingTypeEnumToString(secondModelCountingType) + ")!") { }
    };
}   // namespace Hydra::Exception::Parser
