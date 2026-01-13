#pragma once

#include "Hydra/circuit/node/NodeAbstract.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/circuit/enums/CircuitTypeEnum.hpp"

namespace Hydra::Exception::Circuit {

    using IdNodeType = Hydra::Circuit::Node::IdNodeType;

    /**
     * Circuit exception (main)
     */
    class CircuitException : public CompilerException {
    public:
        explicit CircuitException(const std::string& message)
            : CompilerException(message) { }

        explicit CircuitException(std::string&& message)
            : CompilerException(std::move(message)) { }

        CircuitException(const std::string& message, const std::string& functionName)
            : CompilerException(message, functionName) { }
    };

    /**
     * Identifier does not exist in the circuit
     */
    class IdentifierDoesNotExistException : public CircuitException {
    public:
        explicit IdentifierDoesNotExistException(IdNodeType id)
            : CircuitException("The node's identifier (" + std::to_string(id) + ") does not exist in the circuit!") { }
    };

    /**
     * Root of the circuit is not set
     */
    class RootIsNotSetException : public CircuitException {
    public:
        RootIsNotSetException()
            : CircuitException("The root of the circuit is not set!") { }
    };

    /**
     * Attempt to reset the root of the circuit
     */
    class AttemptToResetRootException : public CircuitException {
    public:
        explicit AttemptToResetRootException(IdNodeType id)
            : CircuitException("Attempt to reset the root (" + std::to_string(id) + ") of the circuit!") { }
    };

    /**
     * Smoothness is not supported
     */
    class SmoothnessIsNotSupportedException : public CircuitException {
    public:
        SmoothnessIsNotSupportedException()
            : CircuitException("The circuit does not support smoothness!") { }
    };

    /**
     * Model counting is not supported without smoothness
     */
    class ModelCountingIsNotSupportedWithoutSmoothnessException : public CircuitException {
    public:
        ModelCountingIsNotSupportedWithoutSmoothnessException()
            : CircuitException("Model counting is not supported without smoothness!") { }
    };

    /**
     * Circuit type does not support query
     */
    class CircuitTypeDoesNotSupportQueryException : public CircuitException {
    public:
        CircuitTypeDoesNotSupportQueryException(Hydra::Circuit::CircuitTypeEnum circuitType, const std::string& queryName)
            : CircuitException(Hydra::Circuit::circuitTypeEnumToString(circuitType) + " does not support " + queryName + "!") { }
    };
}   // namespace Hydra::Exception::Circuit
