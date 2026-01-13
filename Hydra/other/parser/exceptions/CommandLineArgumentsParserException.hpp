#pragma once

#include <string>
#include <string_view>

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/cache/enums/CacheTypeEnum.hpp"

namespace Hydra::Exception::Other::Parser::CommandLineArguments {

    /**
     * Command line arguments parser exception (main)
     */
    class CommandLineArgumentsParserException : public CompilerException {
    public:
        explicit CommandLineArgumentsParserException(const std::string& message)
            : CompilerException(message) { }

        explicit CommandLineArgumentsParserException(std::string&& message)
            : CompilerException(std::move(message)) { }
    };

    /**
     * Required argument is missing
     */
    class RequiredArgumentIsMissingException : public CommandLineArgumentsParserException {
    public:
        explicit RequiredArgumentIsMissingException(const std::string_view& argumentName)
            : CommandLineArgumentsParserException("The required argument (" + std::string(argumentName) + ") is missing!") { }
    };

    /**
     * Invalid argument value
     */
    class InvalidArgumentValueException : public CommandLineArgumentsParserException {
    public:
        InvalidArgumentValueException(const std::string_view& argumentName, const std::string& argumentValue)
            : CommandLineArgumentsParserException("The argument (" + std::string(argumentName) + ") has an invalid value (" + argumentValue + ")!") { }
    };

    /**
     * Argument is mentioned multiple times
     */
    class ArgumentIsMentionedMultipleTimesException : public CommandLineArgumentsParserException {
    public:
        explicit ArgumentIsMentionedMultipleTimesException(const std::string_view& argumentName)
            : CommandLineArgumentsParserException("The argument (" + std::string(argumentName) + ") is mentioned multiple times!") { }
    };

    /**
     * Invalid number of arguments
     */
    class InvalidNumberOfArgumentsException : public CommandLineArgumentsParserException {
    public:
        InvalidNumberOfArgumentsException()
            : CommandLineArgumentsParserException("Invalid number of arguments!") { }
    };

    /**
     * Number of sample moments is not a number (Cara caching scheme)
     */
    class NumberOfSampleMomentsIsNotNumberCaraCachingSchemeException : public CommandLineArgumentsParserException {
    public:
        NumberOfSampleMomentsIsNotNumberCaraCachingSchemeException(const std::string& numberOfSampleMomentsString, Hydra::Cache::CacheTypeEnum cacheType)
            : CommandLineArgumentsParserException("Cara caching scheme (" + Hydra::Cache::cacheTypeEnumToString(cacheType) + ") - the number of sample moments (" + numberOfSampleMomentsString + ") is not a number!") { }
    };
}   // namespace Hydra::Exception::Other::Parser::CommandLineArguments
