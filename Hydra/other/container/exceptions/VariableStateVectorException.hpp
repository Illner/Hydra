#pragma once

#include <string>

#include "Hydra/other/container/exceptions/ContainerException.hpp"

namespace Hydra::Exception::Container::VariableStateVector {

    /**
     * Variable state vector exception (main)
     */
    class VariableStateVectorException : public ContainerException {
    public:
        explicit VariableStateVectorException(const std::string& message)
            : ContainerException(message) { }

        explicit VariableStateVectorException(std::string&& message)
            : ContainerException(std::move(message)) { }
    };

    /**
     * Attempt to unassign a variable that has not been assigned
     */
    template <typename VarT>
    class AttemptToUnassignVariableThatHasNotBeenAssignedException : public VariableStateVectorException {
    public:
        explicit AttemptToUnassignVariableThatHasNotBeenAssignedException(VarT variable)
            : VariableStateVectorException("Attempt to unassign the variable (" + std::to_string(variable) + ") that has not been assigned!") { }
    };

    /**
     * Attempt to reassign a variable
     */
    template <typename VarT>
    class AttemptToReassignVariableException : public VariableStateVectorException {
    public:
        explicit AttemptToReassignVariableException(VarT variable)
            : VariableStateVectorException("Attempt to reassign the variable (" + std::to_string(variable) + ")!") { }
    };

    /**
     * Variable is not assigned
     */
    template <typename VarT>
    class VariableIsNotAssignedException : public VariableStateVectorException {
    public:
        explicit VariableIsNotAssignedException(VarT variable)
            : VariableStateVectorException("The variable (" + std::to_string(variable) + ") is not assigned!") { }
    };
}   // namespace Hydra::Exception::Container::VariableStateVector
