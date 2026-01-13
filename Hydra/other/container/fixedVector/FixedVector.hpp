#pragma once

#include <cassert>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/vectorSet/VectorSet.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/other/container/exceptions/FixedVectorException.hpp"

namespace Hydra::Container::FixedVector {

    /**
     * Fixed vector representation
     * Copy and move methods (default) are allowed!
     * Read-only container supporting only the swap operation
     * Exceptions:
     *      ElementsDoNotExistException
     *      ElementDoesNotExistException
     *      AttemptToSwapInactiveElementException (debug)
     * @tparam TypeT type used for an element
     */
    template <typename TypeT>
    class FixedVector {
    private:
        using FixedVectorType = std::vector<TypeT>;
        using TypeTSetType = Other::HashMap::SetType<TypeT>;

    public:
        using VectorSetType = typename Container::VectorSet::VectorSet;
        using ConstIteratorType = typename FixedVectorType::const_iterator;

    public:
        explicit FixedVector(const FixedVectorType& vector)
            : fixedVector_(vector), numberOfActiveElements_(fixedVector_.size()) {
            fixedVector_.shrink_to_fit();
        }

        explicit FixedVector(FixedVectorType&& vector)
            : fixedVector_(std::move(vector)), numberOfActiveElements_(fixedVector_.size()) {
            fixedVector_.shrink_to_fit();
        }

        /**
         * Initialize [firstValue, lastValue)
         * Invariant: TypeT MUST have operator<, operator++ and operator-
         */
        FixedVector(TypeT firstValue, TypeT lastValue)
            : fixedVector_(), numberOfActiveElements_(0) {
            assert(lastValue > firstValue);

            fixedVector_.reserve(lastValue - firstValue);

            for (TypeT value = firstValue; value < lastValue; ++value)
                fixedVector_.emplace_back(value);

            numberOfActiveElements_ = fixedVector_.size();
        }

        FixedVector(const FixedVector&) = default;
        FixedVector(FixedVector&&) noexcept = default;

        FixedVector& operator=(const FixedVector&) = default;
        FixedVector& operator=(FixedVector&&) noexcept = default;

    private:
        FixedVectorType fixedVector_;
        std::size_t numberOfActiveElements_;

    public:
        /**
         * @return true if the number of active elements is 0. Otherwise, false is returned.
         */
        bool empty() const noexcept;

        /**
         * @return the number of active elements
         */
        std::size_t size() const noexcept;

        /**
         * @return the number of all elements
         */
        std::size_t capacity() const noexcept;

        /**
         * Change the number of active elements
         */
        void changeNumberOfActiveElements(std::size_t newNumberOfActiveElements);

        /**
         * Decrease the number of active elements
         */
        void decreaseNumberOfActiveElements(std::size_t numberOfRemovedElements = 1);

        /**
         * Increase the number of active elements
         */
        void increaseNumberOfActiveElements(std::size_t numberOfAddedElements = 1);

        /**
         * Swap two elements in the fixed vector
         * Note: the elements MUST be active
         * @throw AttemptToSwapInactiveElementException (debug) if one of the elements is inactive
         */
        void swap(std::size_t firstElementPosition, std::size_t secondElementPosition);

        /**
         * Swap the element(s) with the last active element(s)
         * Assert: each element in the (vector) set MUST be presented in the fixed vector
         * Note: the element(s) MUST be active
         * @param elementPosition an element position
         * @throw AttemptToSwapInactiveElementException (debug) if the element is inactive
         * @throw ElementsDoNotExistException if any element does not exist in the fixed vector
         * @throw ElementDoesNotExistException if the element does not exist in the fixed vector
         */
        void swap(std::size_t elementPosition);
        void swap(TypeT element);
        void swap(TypeTSetType& elementSet);
        void swapWithoutRemovingElementsFromSet(const TypeTSetType& elementSet);
        void swapWithoutRemovingElementsFromVectorSet(const VectorSetType& elementVectorSet);

    public:
        const TypeT& operator[](std::size_t position) const;

    public:
        ConstIteratorType begin() const noexcept;
        ConstIteratorType end() const noexcept;

    #ifndef NDEBUG
    public:
        void printFixedVectorDebug(std::ostream& out) const;
    #endif
    };
}   // namespace Hydra::Container::FixedVector

#include "./FixedVector.ipp"
