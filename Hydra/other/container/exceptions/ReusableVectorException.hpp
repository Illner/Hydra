#pragma once

#include <string>

#include "Hydra/other/container/exceptions/ContainerException.hpp"

namespace Hydra::Exception::Container::ReusableVector {

    /**
     * Reusable vector exception (main)
     */
    class ReusableVectorException : public ContainerException {
    public:
        explicit ReusableVectorException(const std::string& message)
            : ContainerException(message) { }

        explicit ReusableVectorException(std::string&& message)
            : ContainerException(std::move(message)) { }
    };

    /**
     * Attempt to exceed the capacity of the reusable vector
     */
    class AttemptToExceedCapacityException : public ReusableVectorException {
    public:
        explicit AttemptToExceedCapacityException(std::size_t capacity)
            : ReusableVectorException("Attempt to exceed the capacity (" + std::to_string(capacity) + ") of the reusable vector!") { }
    };

    /**
     * Attempt to access an inactive element in the reusable vector
     */
    class AttemptToAccessInactiveElementException : public ReusableVectorException {
    public:
        explicit AttemptToAccessInactiveElementException(std::size_t position)
            : ReusableVectorException("Attempt to access the inactive element at position " + std::to_string(position) + " in the reusable vector!") { }
    };

    /**
     * Attempt to get the last element from the empty reusable vector
     */
    class AttemptToGetLastElementFromEmptyReusableVectorException : public ReusableVectorException {
    public:
        AttemptToGetLastElementFromEmptyReusableVectorException()
            : ReusableVectorException("Attempt to get the last element from the empty reusable vector!") { }
    };
}   // namespace Hydra::Exception::Container::ReusableVector
