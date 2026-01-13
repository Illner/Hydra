#pragma once

#include <string>

#include "Hydra/other/container/exceptions/ContainerException.hpp"

namespace Hydra::Exception::Container::VectorMap {

    /**
     * Vector map exception (main)
     */
    class VectorMapException : public ContainerException {
    public:
        explicit VectorMapException(const std::string& message)
            : ContainerException(message) { }

        explicit VectorMapException(std::string&& message)
            : ContainerException(std::move(message)) { }
    };

    /**
     * Attempt to add more elements with the same key
     */
    class AttemptToAddMoreElementsWithSameKeyException : public VectorMapException {
    public:
        explicit AttemptToAddMoreElementsWithSameKeyException(std::size_t key)
            : VectorMapException("Attempt to add more elements with the same key (" + std::to_string(key) + ") in the map!") { }
    };

    /**
     * There is no element with the specific key
     */
    class ThereIsNoElementWithSpecificKeyException : public VectorMapException {
    public:
        explicit ThereIsNoElementWithSpecificKeyException(std::size_t key)
            : VectorMapException("There is no element with the specific key (" + std::to_string(key) + ") in the map!") { }
    };
}   // namespace Hydra::Exception::Container::VectorMap
