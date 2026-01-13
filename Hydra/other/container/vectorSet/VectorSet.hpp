#pragma once

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "Hydra/other/Other.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

namespace Hydra::Container::VectorSet {

    using LargeNumberType = Hydra::Other::LargeNumberType;

    /**
     * Vector set representation
     * Copy methods are disabled! Move methods are allowed!
     * Note: erase is NOT supported; only clear is allowed
     * Exceptions:
     *      SomethingCannotBeSavedAsStdSizeTException
     *      AttemptToAddElementMultipleTimesException (debug)
     */
    class VectorSet {
    private:
        using VectorSetType = std::vector<bool>;

    public:
        using IndexVectorType = std::vector<std::size_t>;

    public:
        VectorSet()
            : capacity_(0), vectorSet_(), addedElementVector_() { }

        explicit VectorSet(LargeNumberType capacity)
            : capacity_(static_cast<std::size_t>(capacity)), vectorSet_(capacity_, false), addedElementVector_() {
            // The number of elements cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(capacity))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("number of elements in a vector set", capacity);

            addedElementVector_.reserve(static_cast<std::size_t>(capacity_ * S_ESTIMATED_PERCENTAGE_OF_CAPACITY_OF_ADDED_ELEMENT_VECTOR_ / 100));   // typically, not all elements are added
        }

        VectorSet(const VectorSet&) = delete;
        VectorSet(VectorSet&& other) noexcept
            : capacity_(other.capacity_), vectorSet_(std::move(other.vectorSet_)), addedElementVector_(std::move(other.addedElementVector_)) {
            // Reset the vector set
            other.capacity_ = 0;
            other.vectorSet_.clear();
            other.addedElementVector_.clear();
        }

        VectorSet& operator=(const VectorSet&) = delete;
        VectorSet& operator=(VectorSet&& other) noexcept {
            if (this != &other) {
                capacity_ = other.capacity_;
                vectorSet_ = std::move(other.vectorSet_);
                addedElementVector_ = std::move(other.addedElementVector_);

                // Reset the vector set
                other.capacity_ = 0;
                other.vectorSet_.clear();
                other.addedElementVector_.clear();
            }

            return *this;
        }

    private:
        std::size_t capacity_;

        VectorSetType vectorSet_;
        IndexVectorType addedElementVector_;

        inline static constexpr int S_ESTIMATED_PERCENTAGE_OF_CAPACITY_OF_ADDED_ELEMENT_VECTOR_ = 20;

    public:
        /**
         * @return true if the set is empty
         */
        bool empty() const noexcept;

        /**
         * @return the number of elements in the set
         */
        std::size_t size() const noexcept;

        /**
         * @return the capacity
         */
        std::size_t capacity() const noexcept;

        /**
         * Erase all the elements in the set
         * Time complexity: O(|set|)
         */
        void clear();

        /**
         * Add the element to the set
         * Time complexity: O(1)
         * @param checkExistence should be checked if the element has already been added to the set
         * @throw AttemptToAddElementMultipleTimesException [checkExistence] (debug) if the element already exists in the set
         */
        void emplace(std::size_t element, bool checkExistence = true);

        /**
         * Time complexity: O(1)
         * @param element an element
         * @return true if the element has been added to the set. Otherwise, false is returned.
         */
        bool contains(std::size_t element) const;

        /**
         * Time complexity: O(1) or O(|set| x log(|set|))
         * @param sort should the elements be sorted
         * @return the vector of added elements
         */
        const IndexVectorType& getAddedElementVector(bool sort = false) noexcept;

    #ifndef NDEBUG
    public:
        void printVectorSetDebug(std::ostream& out);
    #endif
    };
}   // namespace Hydra::Container::VectorSet

namespace Hydra::Other {

    /**
     * Remove the elements contained in the vector set from the vector
     * The elements we want to remove will be swapped with the last element in the vector, and then the last element will be erased
     * Time complexity: O(|vector|)
     * Note: all the occurrences of the elements will be removed
     */
    template <typename TypeT>
    void smartRemoveElementsFromVector(std::vector<TypeT>& vector, const Container::VectorSet::VectorSet& removeElementVectorSet) {
        std::size_t i = 0;

        while (i < vector.size()) {
            if (removeElementVectorSet.contains(static_cast<std::size_t>(vector[i]))) {
                if (i != (vector.size() - 1))
                    vector[i] = std::move(vector.back());

                vector.pop_back();
            }
            else {
                ++i;
            }
        }
    }
}   // namespace Hydra::Other
