#pragma once

#include <sstream>
#include <stdexcept>
#include <string>

#include "Hydra/circuit/enums/CircuitTypeEnum.hpp"

namespace Hydra::Exception {

    /**
     * Compiler exception (main)
     */
    class CompilerException : public std::exception {
    public:
        explicit CompilerException(const std::string& message)
            : message_(message) { }

        explicit CompilerException(std::string&& message)
            : message_(std::move(message)) { }

        explicit CompilerException(std::ostringstream&& outStringStream)
            : message_(std::move(outStringStream).str()) { }

        CompilerException(const std::string& message, const std::string& functionName)
            : message_() {
            message_ = message + " (" + functionName + ")!";
        }

    protected:
        std::string message_;

    public:
        const char* what() const noexcept override {
            return message_.c_str();
        }
    };

    /**
     * Not implemented
     */
    class NotImplementedException : public CompilerException {
    public:
        NotImplementedException(const std::string& whatIsNotImplemented, const std::string& functionName)
            : CompilerException(whatIsNotImplemented + " is not implemented", functionName) { }
    };

    /**
     * Something is wrong
     */
    class SomethingIsWrongException : public CompilerException {
    public:
        SomethingIsWrongException()
            : CompilerException("Something is wrong!") { }
    };

    /**
     * Unexpected argument
     */
    class UnexpectedArgumentException : public CompilerException {
    public:
        UnexpectedArgumentException(const std::string& unexpectedArgument, const std::string& functionName)
            : CompilerException("Unexpected argument: " + unexpectedArgument, functionName) { }
    };

    /**
     * File does not exist
     */
    class FileDoesNotExistException : public CompilerException {
    public:
        explicit FileDoesNotExistException(const std::string& filePath)
            : CompilerException("The file (" + filePath + ") does not exist!") { }
    };

    /**
     * File cannot be opened
     */
    class FileCannotBeOpenedException : public CompilerException {
    public:
        explicit FileCannotBeOpenedException(const std::string& filePath)
            : CompilerException("The file (" + filePath + ") cannot be opened!") { }
    };

    /**
     * Can't create a file
     */
    class CannotCreateFileException : public CompilerException {
    public:
        explicit CannotCreateFileException(const std::string& filePath)
            : CompilerException("Can't create a file (" + filePath + ")!") { }
    };

    /**
     * Variable does not exist in the mapping
     */
    template <typename VarT>
    class VariableDoesNotExistInMappingException : public CompilerException {
    public:
        VariableDoesNotExistInMappingException(VarT var, const std::string& mappingString)
            : CompilerException("The variable (" + std::to_string(var) + ") does not exist in the mapping (" + mappingString + ")!") { }
    };

    /**
     * Mapping is not bijective
     */
    class MappingIsNotBijectiveException : public CompilerException {
    public:
        explicit MappingIsNotBijectiveException(const std::string& mappingString)
            : CompilerException("The mapping (" + mappingString + ") is not bijective!") { }
    };

    /**
     * Mapping is not injective
     */
    class MappingIsNotInjectiveException : public CompilerException {
    public:
        explicit MappingIsNotInjectiveException(const std::string& mappingString)
            : CompilerException("The mapping (" + mappingString + ") is not injective!") { }
    };

    /**
     * Mapping has more keys than expected
     */
    class MappingHasMoreKeysThanExpectedException : public CompilerException {
    public:
        MappingHasMoreKeysThanExpectedException(const std::string& mappingString, const std::string& expectedKeysString)
            : CompilerException("The mapping (" + mappingString + ") has more keys than expected (" + expectedKeysString + ")!") { }
    };

    /**
     * Something cannot be saved as int
     */
    template <typename TypeT>
    class SomethingCannotBeSavedAsIntException : public CompilerException {
    public:
        SomethingCannotBeSavedAsIntException(const std::string& whatCannotBeSavedAsInt, TypeT value)
            : CompilerException("The " + whatCannotBeSavedAsInt + " (" + std::to_string(value) + ") cannot be saved as int!") { }
    };

    /**
     * Something cannot be saved as std::size_t
     */
    template <typename TypeT>
    class SomethingCannotBeSavedAsStdSizeTException : public CompilerException {
    public:
        SomethingCannotBeSavedAsStdSizeTException(const std::string& whatCannotBeSavedAsStdSizeT, TypeT value)
            : CompilerException("The " + whatCannotBeSavedAsStdSizeT + " (" + std::to_string(value) + ") cannot be saved as std::size_t!") { }
    };

    /**
     * Too many variables
     */
    template <typename TypeT>
    class TooManyVariablesException : public CompilerException {
    public:
        explicit TooManyVariablesException(TypeT value)
            : CompilerException("Too many variables (" + std::to_string(value) + ")!") { }
    };

    /**
     * Configuration is not supported
     */
    class ConfigurationIsNotSupportedException : public CompilerException {
    public:
        explicit ConfigurationIsNotSupportedException(const std::string& configuration)
            : CompilerException("The configuration (" + configuration + ") is not supported!") { }
    };

    /**
     * Configuration is not supported on this operating system
     */
    class ConfigurationIsNotSupportedOnThisOperatingSystemException : public CompilerException {
    public:
        explicit ConfigurationIsNotSupportedOnThisOperatingSystemException(const std::string& configuration)
            : CompilerException("The configuration (" + configuration + ") is not supported on this operating system!") { }
    };

    /**
     * Compiling into circuit type is not supported
     */
    class CompilingIntoCircuitTypeIsNotSupportedException : public CompilerException {
    public:
        explicit CompilingIntoCircuitTypeIsNotSupportedException(Circuit::CircuitTypeEnum circuitType)
            : CompilerException("Compiling into " + Circuit::circuitTypeEnumToString(circuitType) + " circuits is not supported!") { }
    };

    /**
     * Operating system is not supported
     */
    class OperatingSystemIsNotSupportedException : public CompilerException {
    public:
        OperatingSystemIsNotSupportedException()
            : CompilerException("This operating system is not supported!") { }
    };

    /**
     * Formula has too many ...
     */
    class FormulaHasTooManySomethingException : public CompilerException {
    public:
        explicit FormulaHasTooManySomethingException(const std::string& something)
            : CompilerException("The formula has too many " + something + "!") { }
    };

    /**
     * Circuit has not yet been compiled
     */
    class CircuitHasNotYetBeenCompiledException : public CompilerException {
    public:
        CircuitHasNotYetBeenCompiledException()
            : CompilerException("The circuit has not yet been compiled!") { }
    };

    /**
     * Compilation failed
     */
    class CompilationFailedException : public CompilerException {
    public:
        CompilationFailedException()
            : CompilerException("The compilation unexpectedly failed!") { }
    };

    /**
     * The number of models has not yet been computed
     */
    class NumberOfModelsHasNotYetBeenComputedException : public CompilerException {
    public:
        NumberOfModelsHasNotYetBeenComputedException()
            : CompilerException("The number of models has not yet been computed!") { }
    };

    /**
     * Computing number of models failed
     */
    class ComputingNumberOfModelsFailedException : public CompilerException {
    public:
        ComputingNumberOfModelsFailedException()
            : CompilerException("The computing number of models unexpectedly failed!") { }
    };

    /**
     * Circuit does not imply CNF formula
     */
    class CircuitDoesNotImplyCnfFormulaException : public CompilerException {
    public:
        CircuitDoesNotImplyCnfFormulaException()
            : CompilerException("The compiled circuit does not imply the input CNF formula!") { }
    };

    /**
     * Timeout
     */
    class TimeoutException : public CompilerException {
    public:
        TimeoutException()
            : CompilerException("Timeout") { }
    };
}   // namespace Hydra::Exception
