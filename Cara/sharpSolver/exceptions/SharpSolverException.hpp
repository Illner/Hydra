#pragma once

#include <string>

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Cara/sharpSolver/enums/ModelCountingTypeEnum.hpp"

namespace Cara::Exception {

    /**
     * #Solver exception (main)
     */
    class SharpSolverException : public Hydra::Exception::CompilerException {
    public:
        explicit SharpSolverException(const std::string& message)
            : CompilerException(message) { }

        explicit SharpSolverException(std::string&& message)
            : CompilerException(std::move(message)) { }
    };

    /**
     * Model counting type is not supported
     */
    class ModelCountingTypeIsNotSupportedException : public SharpSolverException {
    public:
        explicit ModelCountingTypeIsNotSupportedException(ModelCountingTypeEnum modelCountingType)
            : SharpSolverException("The model counting type (" + modelCountingTypeEnumToString(modelCountingType) + ") is not supported!") { }
    };
}   // namespace Cara::Exception
