#pragma once

#include "Hydra/compiler/exceptions/ParserException.hpp"

namespace Hydra::Exception::Circuit::Parser {

    /**
     * Circuit parser exception (main)
     */
    class CircuitParserException : public Exception::Parser::ParserException {
    public:
        explicit CircuitParserException(const std::string& message)
            : ParserException(message) { }

        explicit CircuitParserException(std::string&& message)
            : ParserException(std::move(message)) { }
    };

    /**
     * DIMACS NNF header is invalid
     */
    class InvalidDimacsNnfHeaderException : public CircuitParserException {
    public:
        explicit InvalidDimacsNnfHeaderException(const std::string& message)
            : CircuitParserException(message) { }

        explicit InvalidDimacsNnfHeaderException(std::string&& message)
            : CircuitParserException(std::move(message)) { }
    };
}   // namespace Hydra::Exception::Circuit::Parser
