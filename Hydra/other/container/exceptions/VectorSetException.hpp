#pragma once

#include <string>

#include "Hydra/other/container/exceptions/ContainerException.hpp"

namespace Hydra::Exception::Container::VectorSet {

    /**
     * Vector set exception (main)
     */
    class VectorSetException : public ContainerException {
    public:
        explicit VectorSetException(const std::string& message)
            : ContainerException(message) { }

        explicit VectorSetException(std::string&& message)
            : ContainerException(std::move(message)) { }
    };

    /**
     * Attempt to add an element multiple times
     */
    class AttemptToAddElementMultipleTimesException : public VectorSetException {
    public:
        explicit AttemptToAddElementMultipleTimesException(std::size_t element)
            : VectorSetException("Attempt to add the element (" + std::to_string(element) + ") multiple times to the set!") { }
    };
}   // namespace Hydra::Exception::Container::VectorSet
