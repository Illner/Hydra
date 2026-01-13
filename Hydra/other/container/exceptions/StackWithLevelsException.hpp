#pragma once

#include <string>

#include "Hydra/other/Other.hpp"
#include "Hydra/other/std/Std.hpp"

#include "Hydra/other/container/exceptions/ContainerException.hpp"

namespace Hydra::Exception::Container::StackWithLevels {

    using LargeNumberType = Other::LargeNumberType;

    /**
     * Stack with levels exception (main)
     */
    class StackWithLevelsException : public ContainerException {
    public:
        explicit StackWithLevelsException(const std::string& message)
            : ContainerException(message) { }

        explicit StackWithLevelsException(std::string&& message)
            : ContainerException(std::move(message)) { }
    };

    /**
     * The maximum number of elements cannot be saved as LevelTypeT
     */
    class MaximumNumberOfElementsCannotBeSavedAsLevelTypeTException : public StackWithLevelsException {
    public:
        explicit MaximumNumberOfElementsCannotBeSavedAsLevelTypeTException(LargeNumberType maxNumberOfElements)
            : StackWithLevelsException("The maximum number of elements (" + std::to_string(maxNumberOfElements) + ") cannot be saved as LevelTypeT!") { }
    };

    /**
     * Attempt to add an element multiple times
     */
    template <typename TypeT>
    class AttemptToAddElementMultipleTimesException : public StackWithLevelsException {
    public:
        explicit AttemptToAddElementMultipleTimesException(TypeT element)
            : StackWithLevelsException("Attempt to add the element (" + std::to_string(element) + ") multiple times!") { }
    };
}   // namespace Hydra::Exception::Container::StackWithLevels
