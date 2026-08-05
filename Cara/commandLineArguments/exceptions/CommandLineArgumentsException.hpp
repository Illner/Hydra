#pragma once

#include <string>

#include "Hydra/compiler/exceptions/CommandLineArgumentsException.hpp"

namespace Cara::Exception::CommandLineArguments {

    using CommandLineArgumentsException = Hydra::Exception::CommandLineArguments::CommandLineArgumentsException;

    /**
     * More preprocessing types of Cara caching scheme are mentioned
     */
    class MorePreprocessingTypesOfCaraCachingSchemeAreMentionedException : public CommandLineArgumentsException {
    public:
        MorePreprocessingTypesOfCaraCachingSchemeAreMentionedException()
            : CommandLineArgumentsException("More preprocessing types of Cara caching scheme are mentioned!") { }
    };

    /**
     * The must-multiply-by factor is zero
     */
    class MustMultiplyByFactorIsZeroException : public CommandLineArgumentsException {
    public:
        MustMultiplyByFactorIsZeroException()
            : CommandLineArgumentsException("The must-multiply-by factor is zero!") { }
    };

    /**
     * The must-multiply-by factor is invalid
     */
    class MustMultiplyByFactorIsInvalidException : public CommandLineArgumentsException {
    public:
        explicit MustMultiplyByFactorIsInvalidException(const std::string& mustMultiplyByFactorString)
            : CommandLineArgumentsException("The must-multiply-by factor (" + mustMultiplyByFactorString + ") is invalid!") { }
    };
}   // namespace Cara::Exception::CommandLineArguments
