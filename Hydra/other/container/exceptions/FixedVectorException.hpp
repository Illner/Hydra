#pragma once

#include <string>

#include "Hydra/other/container/exceptions/ContainerException.hpp"

namespace Hydra::Exception::Container::FixedVector {

    /**
     * Fixed vector exception (main)
     */
    class FixedVectorException : public ContainerException {
    public:
        explicit FixedVectorException(const std::string& message)
            : ContainerException(message) { }

        explicit FixedVectorException(std::string&& message)
            : ContainerException(std::move(message)) { }
    };

    /**
     * Attempt to swap an inactive element in the fixed vector
     */
    class AttemptToSwapInactiveElementException : public FixedVectorException {
    public:
        AttemptToSwapInactiveElementException(std::size_t firstElementPosition, std::size_t secondElementPosition, std::size_t numberOfActiveElements)
            : FixedVectorException("Attempt to swap two elements (" +
                                   std::to_string(firstElementPosition) + " and " + std::to_string(secondElementPosition) +
                                   ") in the fixed vector containing " + std::to_string(numberOfActiveElements) + " active element(s)!") { }
    };

    /**
     * Element does not exist
     */
    template <typename TypeT>
    class ElementDoesNotExistException : public FixedVectorException {
    public:
        explicit ElementDoesNotExistException(TypeT element)
            : FixedVectorException("The element (" + std::to_string(element) + ") does not exist in the fixed vector!") { }
    };

    /**
     * Elements do not exist
     */
    class ElementsDoNotExistException : public FixedVectorException {
    public:
        explicit ElementsDoNotExistException(const std::string& elementsString)
            : FixedVectorException("The elements (" + elementsString + ") do not exist in the fixed vector!") { }
    };
}   // namespace Hydra::Exception::Container::FixedVector
