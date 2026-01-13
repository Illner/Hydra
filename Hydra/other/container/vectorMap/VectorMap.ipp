#pragma once

#include "./VectorMap.hpp"

namespace Hydra::Container::VectorMap {

    template <typename TypeT>
    bool VectorMap<TypeT>::empty() const noexcept {
        return addedKeyVector_.empty();
    }

    template <typename TypeT>
    std::size_t VectorMap<TypeT>::size() const noexcept {
        return addedKeyVector_.size();
    }

    template <typename TypeT>
    std::size_t VectorMap<TypeT>::capacity() const noexcept {
        return capacity_;
    }

    template <typename TypeT>
    const TypeT& VectorMap<TypeT>::getNoValueRepresentative() const noexcept {
        return noValueRepresentative_;
    }

    template <typename TypeT>
    void VectorMap<TypeT>::clear() {
        for (std::size_t key : addedKeyVector_) {
            assert(vectorMap_[key]);   // key is added

            vectorMap_[key] = false;
            valueVector_[key] = noValueRepresentative_;
        }

        addedKeyVector_.clear();
    }

    template <typename TypeT>
    bool VectorMap<TypeT>::insert(std::size_t key, TypeT&& value, [[maybe_unused]] bool checkExistence) {
        assert(key < capacity_);   // valid key

        #ifndef NDEBUG
        if (checkExistence) {
            // An element with the same key has already been added
            if (vectorMap_[key])
                throw Exception::Container::VectorMap::AttemptToAddMoreElementsWithSameKeyException(key);
        }
        #endif

        // An element with the same key has already been added
        if (vectorMap_[key])
            return false;

        vectorMap_[key] = true;
        addedKeyVector_.emplace_back(key);
        valueVector_[key] = std::move(value);

        return true;
    }

    template <typename TypeT>
    bool VectorMap<TypeT>::insert(std::size_t key, const TypeT& value, [[maybe_unused]] bool checkExistence) {
        assert(key < capacity_);   // valid key

        #ifndef NDEBUG
        if (checkExistence) {
            // An element with the same key has already been added
            if (vectorMap_[key])
                throw Exception::Container::VectorMap::AttemptToAddMoreElementsWithSameKeyException(key);
        }
        #endif

        // An element with the same key has already been added
        if (vectorMap_[key])
            return false;

        vectorMap_[key] = true;
        addedKeyVector_.emplace_back(key);
        valueVector_[key] = value;

        return true;
    }

    template <typename TypeT>
    template <typename... Args>
    bool VectorMap<TypeT>::emplace(std::size_t key, Args&&... args) {
        assert(key < capacity_);   // valid key

        // An element with the same key has already been added
        if (vectorMap_[key])
            return false;

        vectorMap_[key] = true;
        addedKeyVector_.emplace_back(key);
        valueVector_[key] = TypeT(std::forward<Args>(args)...);

        return true;
    }

    template <typename TypeT>
    bool VectorMap<TypeT>::contains(std::size_t key) const {
        if (capacity_ == 0)
            return false;

        assert(key < capacity_);   // valid key

        return vectorMap_[key];
    }

    template <typename TypeT>
    const TypeT& VectorMap<TypeT>::find(std::size_t key) const {
        assert(key < capacity_);   // valid key

        // No element with the specific key has been added
        if (!vectorMap_[key])
            throw Exception::Container::VectorMap::ThereIsNoElementWithSpecificKeyException(key);

        return valueVector_[key];
    }

    template <typename TypeT>
    const VectorMap<TypeT>::IndexVectorType& VectorMap<TypeT>::getAddedKeyVector() const noexcept {
        return addedKeyVector_;
    }

    template <typename TypeT>
    const VectorMap<TypeT>::IndexVectorType& VectorMap<TypeT>::getAddedKeyVector(bool sort) noexcept {
        if (sort)
            std::sort(addedKeyVector_.begin(), addedKeyVector_.end());

        return addedKeyVector_;
    }

    template <typename TypeT>
    const TypeT& VectorMap<TypeT>::operator[](std::size_t key) const {
        return find(key);
    }

    #ifndef NDEBUG
    template <typename TypeT>
    void VectorMap<TypeT>::printVectorMapDebug(std::ostream& out) {
        out << "Vector map:" << std::endl;

        std::sort(addedKeyVector_.begin(), addedKeyVector_.end());
        for (std::size_t key : addedKeyVector_)
            out << "\t" << std::to_string(key) << ": " << std::to_string(valueVector_[key]) << std::endl;

        out << "Added keys:";
        for (std::size_t key : addedKeyVector_)
            out << " " << std::to_string(key);
        out << std::endl;

        out << "Number of added elements: " << std::to_string(size()) << std::endl;
    }
    #endif
}   // namespace Hydra::Container::VectorMap
