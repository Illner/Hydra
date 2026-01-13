#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "Hydra/other/Other.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/other/container/exceptions/VectorMapException.hpp"

namespace Hydra::Container::VectorMap {

    using LargeNumberType = Hydra::Other::LargeNumberType;

    /**
     * Vector map representation
     * Copy methods are disabled! Move methods are allowed!
     * Note: erase is NOT supported; only clear is allowed
     * Exceptions:
     *      ThereIsNoElementWithSpecificKeyException
     *      SomethingCannotBeSavedAsStdSizeTException
     *      AttemptToAddMoreElementsWithSameKeyException (debug)
     * @tparam TypeT type used for a value
     */
    template <typename TypeT>
    class VectorMap {
    private:
        using VectorMapType = std::vector<bool>;
        using ValueVectorType = std::vector<TypeT>;

    public:
        using IndexVectorType = std::vector<std::size_t>;

    public:
        VectorMap()
            : capacity_(0), vectorMap_(), valueVector_(), addedKeyVector_(), noValueRepresentative_() { }

        explicit VectorMap(const TypeT& noValueRepresentative)
            : capacity_(0), vectorMap_(), valueVector_(), addedKeyVector_(), noValueRepresentative_(noValueRepresentative) { }

        VectorMap(LargeNumberType capacity, const TypeT& noValueRepresentative)
            : capacity_(static_cast<std::size_t>(capacity)), vectorMap_(capacity_, false), valueVector_(), addedKeyVector_(),
              noValueRepresentative_(noValueRepresentative) {
            // The number of elements cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<LargeNumberType>(capacity))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("number of elements in a vector map", capacity);

            valueVector_.reserve(capacity_);
            for (std::size_t i = 0; i < capacity_; ++i)
                valueVector_.push_back(noValueRepresentative_);

            addedKeyVector_.reserve(static_cast<std::size_t>(capacity_ * S_ESTIMATED_PERCENTAGE_OF_CAPACITY_OF_ADDED_KEY_VECTOR_ / 100));   // typically, not all elements are added
        }

        VectorMap(const VectorMap&) = delete;
        VectorMap(VectorMap&& other) noexcept
            : capacity_(other.capacity_), vectorMap_(std::move(other.vectorMap_)), valueVector_(std::move(other.valueVector_)),
              addedKeyVector_(std::move(other.addedKeyVector_)), noValueRepresentative_(std::move(other.noValueRepresentative_)) {
            // Reset the vector map
            other.capacity_ = 0;
            other.vectorMap_.clear();
            other.valueVector_.clear();
            other.addedKeyVector_.clear();
        }

        VectorMap& operator=(const VectorMap&) = delete;
        VectorMap& operator=(VectorMap&& other) noexcept {
            if (this != &other) {
                capacity_ = other.capacity_;
                vectorMap_ = std::move(other.vectorMap_);
                valueVector_ = std::move(other.valueVector_);
                addedKeyVector_ = std::move(other.addedKeyVector_);
                noValueRepresentative_ = std::move(other.noValueRepresentative_);

                // Reset the vector map
                other.capacity_ = 0;
                other.vectorMap_.clear();
                other.valueVector_.clear();
                other.addedKeyVector_.clear();
            }

            return *this;
        }

    private:
        std::size_t capacity_;

        VectorMapType vectorMap_;
        ValueVectorType valueVector_;
        IndexVectorType addedKeyVector_;

        TypeT noValueRepresentative_;

        inline static constexpr int S_ESTIMATED_PERCENTAGE_OF_CAPACITY_OF_ADDED_KEY_VECTOR_ = 20;

    public:
        /**
         * @return true if the map is empty
         */
        bool empty() const noexcept;

        /**
         * @return the number of elements in the map
         */
        std::size_t size() const noexcept;

        /**
         * @return the capacity of the map
         */
        std::size_t capacity() const noexcept;

        /**
         * @return the no-value representative
         */
        const TypeT& getNoValueRepresentative() const noexcept;

        /**
         * Erase all the elements in the map
         * Time complexity: O(|element|)
         */
        void clear();

        /**
         * Add the element to the map.
         * If an element with the same key already exists in the map, the element will NOT be added.
         * Time complexity: O(1)
         * @param key a key
         * @param value a value
         * @param checkExistence should be checked if an element with the same key has already been added to the map
         * @return true if the element has been added to the map. Otherwise, false is returned.
         * @throw AttemptToAddMoreElementsWithSameKeyException [checkExistence] (debug) if an element with the same key already exists in the map
         */
        bool insert(std::size_t key, TypeT&& value, bool checkExistence = true);
        bool insert(std::size_t key, const TypeT& value, bool checkExistence = true);

        template <typename... Args>
        bool emplace(std::size_t key, Args&&... args);

        /**
         * Time complexity: O(1)
         * Note: if the capacity of the vector map is 0, false is always returned
         * @param key a key
         * @return true if an element with the specific key has been added to the map. Otherwise, false is returned.
         */
        bool contains(std::size_t key) const;

        /**
         * Time complexity: O(1)
         * @param key a key
         * @return the value of the element with the specific key
         * @throw ThereIsNoElementWithSpecificKeyException if there is no element with the specific key
         */
        const TypeT& find(std::size_t key) const;

        /**
         * Time complexity: O(1) or O(|element| x log(|element|))
         * @param sort should the keys be sorted
         * @return the vector of added keys
         */
        const IndexVectorType& getAddedKeyVector() const noexcept;
        const IndexVectorType& getAddedKeyVector(bool sort) noexcept;

    public:
        /**
         * Time complexity: O(1)
         * @param key a key
         * @return the value of the element with the specific key
         * @throw ThereIsNoElementWithSpecificKeyException if there is no element with the specific key
         */
        const TypeT& operator[](std::size_t key) const;

    #ifndef NDEBUG
    public:
        void printVectorMapDebug(std::ostream& out);
    #endif
    };
}   // namespace Hydra::Container::VectorMap

#include "./VectorMap.ipp"
