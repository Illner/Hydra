#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/other/container/exceptions/ReusableVectorException.hpp"

namespace Hydra::Container::ReusableVector {

    using LargeNumberType = Hydra::Other::LargeNumberType;

    /**
     * Reusable vector representation
     * Copy methods are disabled! Move methods are allowed!
     * Fixed-size vector
     * Exceptions:
     *      AttemptToExceedCapacityException (debug)
     *      SomethingCannotBeSavedAsStdSizeTException
     *      AttemptToAccessInactiveElementException (debug)
     *      AttemptToGetLastElementFromEmptyReusableVectorException (debug)
     * @tparam TypeT type used for an element
     */
    template <typename TypeT>
    class ReusableVector {
    private:
        using ReusableVectorType = std::vector<TypeT>;

    public:
        using IteratorType = typename ReusableVectorType::iterator;
        using ConstIteratorType = typename ReusableVectorType::const_iterator;

    public:
        using TypeSetType = Other::HashMap::SetType<TypeT>;

    public:
        ReusableVector()
            : capacity_(0), numberOfActiveElements_(0), numberOfAllocatedElements_(0), reusableVector_() { }

        explicit ReusableVector(LargeNumberType capacity)
            : capacity_(static_cast<std::size_t>(capacity)), numberOfActiveElements_(0), numberOfAllocatedElements_(0), reusableVector_() {
            // The maximum number of elements cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(capacity))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("maximum number of elements in a reusable vector", capacity);

            reusableVector_.reserve(capacity_);
        }

        ReusableVector(const ReusableVector&) = delete;
        ReusableVector(ReusableVector&& other) noexcept
            : capacity_(other.capacity_), numberOfActiveElements_(other.numberOfActiveElements_),
              numberOfAllocatedElements_(other.numberOfAllocatedElements_), reusableVector_(std::move(other.reusableVector_)) {
            // Reset the other reusable vector
            other.capacity_ = 0;
            other.numberOfActiveElements_ = 0;
            other.numberOfAllocatedElements_ = 0;
            other.reusableVector_.clear();
        };

        ReusableVector& operator=(const ReusableVector&) = delete;
        ReusableVector& operator=(ReusableVector&& other) noexcept {
            if (this != &other) {
                capacity_ = other.capacity_;
                numberOfActiveElements_ = other.numberOfActiveElements_;
                numberOfAllocatedElements_ = other.numberOfAllocatedElements_;
                reusableVector_ = std::move(other.reusableVector_);

                // Reset the other reusable vector
                other.capacity_ = 0;
                other.numberOfActiveElements_ = 0;
                other.numberOfAllocatedElements_ = 0;
                other.reusableVector_.clear();
            }

            return *this;
        }

    private:
        std::size_t capacity_;
        std::size_t numberOfActiveElements_;
        std::size_t numberOfAllocatedElements_;   // active + inactive elements

        ReusableVectorType reusableVector_;

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
         * @return the capacity
         */
        std::size_t capacity() const noexcept;

        /**
         * Clear the reusable vector
         * Time complexity: O(1)
         */
        void clear() noexcept;

        /**
         * @return the last element in the reusable vector
         * @throw AttemptToGetLastElementFromEmptyReusableVectorException (debug) if the reusable vector is empty
         */
        const TypeT& back() const;

        /**
         * Append the element to the end of the reusable vector
         * @param element a new element
         * @throw AttemptToExceedCapacityException (debug) if the reusable vector is full
         */
        void push_back(TypeT&& element);
        void push_back(const TypeT& element);

        template <typename... Args>
        void emplace_back(Args&&... args);

        /**
         * Copy the elements from the set/vector
         * Note: the reusable vector will be cleared at the beginning
         * @param typeSet/typeVector a set/vector from which the elements will be copied
         * @throw AttemptToExceedCapacityException (debug) if the set/vector has more elements than the capacity of the reusable vector
         */
        void copySet(const TypeSetType& typeSet);
        template <typename VectorT>
        void copyVector(const VectorT& typeVector);

        /**
         * Sort the elements in the reusable vector
         */
        void sort();

        /**
         * Set the elements as inactive in the range [newEndIterator, endIterator)
         * Assert: the iterator MUST point at an active element
         * @param newEndIterator a new end iterator
         */
        void erase(IteratorType newEndIterator);

        /**
         * @return a set containing all the elements in the reusable vector
         */
        TypeSetType createSet() const;
        TypeSetType createSetUsingEmplace() const;

    public:
        /**
         * @param position a position
         * @return the element at the particular position
         * @throw AttemptToAccessInactiveElementException if the element is inactive
         */
        const TypeT& operator[](std::size_t position) const;

    public:
        IteratorType begin() noexcept;
        IteratorType end() noexcept;

        ConstIteratorType begin() const noexcept;
        ConstIteratorType end() const noexcept;

        ConstIteratorType cbegin() const noexcept;
        ConstIteratorType cend() const noexcept;

    #ifndef NDEBUG
    public:
        void printReusableVectorDebug(std::ostream& out) const;
    #endif
    };
}   // namespace Hydra::Container::ReusableVector

#include "./ReusableVector.ipp"
