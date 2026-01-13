#pragma once

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Hydra/other/Other.hpp"
#include "Hydra/other/std/Std.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/other/container/exceptions/StackWithLevelsException.hpp"

namespace Hydra::Container::StackWithLevels {

    using LargeNumberType = Other::LargeNumberType;

    /**
     * Stack with levels representation
     * Copy and move methods (default) are allowed!
     * Note: TypeT is expected to be a type which can be quickly copied
     * Exceptions:
     *      SomethingCannotBeSavedAsStdSizeTException
     *      AttemptToAddElementMultipleTimesException (debug)
     *      MaximumNumberOfElementsCannotBeSavedAsLevelTypeTException
     * @tparam TypeT type used for an element
     * @tparam LevelTypeT type used for a level
     */
    template <typename TypeT, typename LevelTypeT = std::size_t>
    class StackWithLevels {
    private:
        using StackType = std::vector<TypeT>;
        using StackLevelType = std::vector<LevelTypeT>;

    public:
        #ifndef NDEBUG
        StackWithLevels(LargeNumberType maxNumberOfElements, LargeNumberType maxNumberOfLevels)
            : stack_(), stackLevel_(),
              d_maxNumberOfLevels_(static_cast<std::size_t>(maxNumberOfLevels)), d_maxNumberOfElements_(static_cast<std::size_t>(maxNumberOfElements)) {
            // The maximum number of elements cannot be saved as LevelTypeT
            if (!Other::unsignedValueCanBeSavedAsTypeT<LevelTypeT>(maxNumberOfElements))
                throw Exception::Container::StackWithLevels::MaximumNumberOfElementsCannotBeSavedAsLevelTypeTException(maxNumberOfElements);

            // The maximum number of elements cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(maxNumberOfElements))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("maximum number of elements", maxNumberOfElements);

            // The maximum number of levels cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(maxNumberOfLevels))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("maximum number of levels", maxNumberOfLevels);

            stack_.reserve(maxNumberOfElements);
            stackLevel_.reserve(maxNumberOfLevels);
        }
        #else
        StackWithLevels(LargeNumberType maxNumberOfElements, LargeNumberType maxNumberOfLevels)
            : stack_(), stackLevel_() {
            // The maximum number of elements cannot be saved as LevelTypeT
            if (!Other::unsignedValueCanBeSavedAsTypeT<LevelTypeT>(maxNumberOfElements))
                throw Exception::Container::StackWithLevels::MaximumNumberOfElementsCannotBeSavedAsLevelTypeTException(maxNumberOfElements);

            // The maximum number of elements cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(maxNumberOfElements))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("maximum number of elements", maxNumberOfElements);

            // The maximum number of levels cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(maxNumberOfLevels))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("maximum number of levels", maxNumberOfLevels);

            stack_.reserve(maxNumberOfElements);
            stackLevel_.reserve(maxNumberOfLevels);
        }
        #endif

        StackWithLevels(const StackWithLevels&) = default;
        StackWithLevels(StackWithLevels&&) noexcept = default;

        StackWithLevels& operator=(const StackWithLevels&) = default;
        StackWithLevels& operator=(StackWithLevels&&) noexcept = default;

    private:
        StackType stack_;
        StackLevelType stackLevel_;

    public:
        /**
         * @return true if the data structure is empty (that is, the number of levels/elements is zero). Otherwise, false is returned.
         */
        bool isEmpty() const;

        /**
         * @return true if at least one level exists. Otherwise, false is returned.
         */
        bool levelExists() const noexcept;

        /**
         * Add a new level
         */
        void addNewLevel();

        /**
         * Add the element
         * @param element an element
         * @throw AttemptToAddElementMultipleTimesException (debug) if the element already exists in the stack
         */
        void addElement(TypeT element);

        /**
         * Remove all the elements on the current level
         */
        void removeCurrentLevel();

        /**
         * Remove all the elements on the current level, and call the functor for each removed element
         * @param functor operator()(TypeT element)
         */
        template <typename FunctorT>
        void removeCurrentLevel(FunctorT functor);

        /**
         * Clear the data structure
         */
        void clear() noexcept;

        /**
         * Clear the data structure, and call the functor for each removed element
         * @param functor operator()(TypeT element)
         */
        template <typename FunctorT>
        void clear(FunctorT functor);

    #ifndef NDEBUG
    private:
        std::size_t d_maxNumberOfLevels_;
        std::size_t d_maxNumberOfElements_;

    public:
        void printStackWithLevelsDebug(std::ostream& out) const;

        template <typename FunctorT>
        void printStackWithLevelsDebug(std::ostream& out, FunctorT functor) const;
    #endif
    };

}   // namespace Hydra::Container::StackWithLevels

#include "./StackWithLevels.ipp"
