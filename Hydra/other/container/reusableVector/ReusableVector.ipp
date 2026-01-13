#pragma once

#include "./ReusableVector.hpp"

namespace Hydra::Container::ReusableVector {

    template <typename TypeT>
    bool ReusableVector<TypeT>::empty() const noexcept {
        return numberOfActiveElements_ == 0;
    }

    template <typename TypeT>
    std::size_t ReusableVector<TypeT>::size() const noexcept {
        return numberOfActiveElements_;
    }

    template <typename TypeT>
    std::size_t ReusableVector<TypeT>::capacity() const noexcept {
        return capacity_;
    }

    template <typename TypeT>
    void ReusableVector<TypeT>::clear() noexcept {
        numberOfActiveElements_ = 0;
    }

    template <typename TypeT>
    const TypeT& ReusableVector<TypeT>::back() const {
        #ifndef NDEBUG
        // The reusable vector is empty
        if (empty())
            throw Exception::Container::ReusableVector::AttemptToGetLastElementFromEmptyReusableVectorException();
        #endif

        return reusableVector_[numberOfActiveElements_ - 1];
    }

    template <typename TypeT>
    void ReusableVector<TypeT>::push_back(TypeT&& element) {
        #ifndef NDEBUG
        // The reusable vector is full
        if (numberOfActiveElements_ == capacity_)
            throw Exception::Container::ReusableVector::AttemptToExceedCapacityException(capacity_);
        #endif

        // A new position must be allocated for the element
        if (numberOfActiveElements_ == numberOfAllocatedElements_) {
            reusableVector_.push_back(std::move(element));

            ++numberOfAllocatedElements_;
        }
        else
            reusableVector_[numberOfActiveElements_] = std::move(element);

        ++numberOfActiveElements_;
    }

    template <typename TypeT>
    void ReusableVector<TypeT>::push_back(const TypeT& element) {
        #ifndef NDEBUG
        // The reusable vector is full
        if (numberOfActiveElements_ == capacity_)
            throw Exception::Container::ReusableVector::AttemptToExceedCapacityException(capacity_);
        #endif

        // A new position must be allocated for the element
        if (numberOfActiveElements_ == numberOfAllocatedElements_) {
            reusableVector_.push_back(element);

            ++numberOfAllocatedElements_;
        }
        else
            reusableVector_[numberOfActiveElements_] = element;

        ++numberOfActiveElements_;
    }

    template <typename TypeT>
    template <typename... Args>
    void ReusableVector<TypeT>::emplace_back(Args&&... args) {
        #ifndef NDEBUG
        // The reusable vector is full
        if (numberOfActiveElements_ == capacity_)
            throw Exception::Container::ReusableVector::AttemptToExceedCapacityException(capacity_);
        #endif

        // A new position must be allocated for the element
        if (numberOfActiveElements_ == numberOfAllocatedElements_) {
            reusableVector_.emplace_back(std::forward<Args>(args)...);

            ++numberOfAllocatedElements_;
        }
        else
            reusableVector_[numberOfActiveElements_] = TypeT(std::forward<Args>(args)...);

        ++numberOfActiveElements_;
    }

    template <typename TypeT>
    void ReusableVector<TypeT>::copySet(const TypeSetType& typeSet) {
        clear();

        #ifndef NDEBUG
        for (const TypeT& element : Other::sortUnorderedSet(typeSet))
        #else
        for (const TypeT& element : typeSet)
        #endif
            push_back(element);
    }

    template <typename TypeT>
    template <typename VectorT>
    void ReusableVector<TypeT>::copyVector(const VectorT& typeVector) {
        clear();

        for (const TypeT& element : typeVector)
            push_back(element);
    }

    template <typename TypeT>
    void ReusableVector<TypeT>::sort() {
        std::sort(begin(), end());
    }

    template <typename TypeT>
    void ReusableVector<TypeT>::erase(IteratorType newEndIterator) {
        auto endIterator = reusableVector_.begin();
        std::advance(endIterator, numberOfActiveElements_);

        assert(reusableVector_.begin() <= newEndIterator);
        assert(newEndIterator <= endIterator);

        std::size_t numberOfElementsToRemove = (endIterator - newEndIterator);

        assert(numberOfActiveElements_ >= numberOfElementsToRemove);

        numberOfActiveElements_ -= numberOfElementsToRemove;
    }

    template <typename TypeT>
    ReusableVector<TypeT>::TypeSetType ReusableVector<TypeT>::createSet() const {
        TypeSetType set(numberOfActiveElements_);

        for (auto it = cbegin(); it != cend(); ++it)
            set.insert(*it);

        return set;
    }

    template <typename TypeT>
    ReusableVector<TypeT>::TypeSetType ReusableVector<TypeT>::createSetUsingEmplace() const {
        TypeSetType set(numberOfActiveElements_);

        for (auto it = cbegin(); it != cend(); ++it)
            set.emplace(*it);

        return set;
    }

    template <typename TypeT>
    const TypeT& ReusableVector<TypeT>::operator[](std::size_t position) const {
        #ifndef NDEBUG
        // An inactive element
        if (position >= numberOfActiveElements_)
            throw Exception::Container::ReusableVector::AttemptToAccessInactiveElementException(position);
        #endif

        return reusableVector_[position];
    }

    template <typename TypeT>
    ReusableVector<TypeT>::IteratorType ReusableVector<TypeT>::begin() noexcept {
        return reusableVector_.begin();
    }

    template <typename TypeT>
    ReusableVector<TypeT>::IteratorType ReusableVector<TypeT>::end() noexcept {
        // The reusable vector is full
        if (numberOfActiveElements_ == capacity_)
            return reusableVector_.end();

        auto it = reusableVector_.begin();
        std::advance(it, numberOfActiveElements_);

        return it;
    }

    template <typename TypeT>
    ReusableVector<TypeT>::ConstIteratorType ReusableVector<TypeT>::begin() const noexcept {
        return reusableVector_.cbegin();
    }

    template <typename TypeT>
    ReusableVector<TypeT>::ConstIteratorType ReusableVector<TypeT>::end() const noexcept {
        // The reusable vector is full
        if (numberOfActiveElements_ == capacity_)
            return reusableVector_.cend();

        auto it = reusableVector_.cbegin();
        std::advance(it, numberOfActiveElements_);

        return it;
    }

    template <typename TypeT>
    ReusableVector<TypeT>::ConstIteratorType ReusableVector<TypeT>::cbegin() const noexcept {
        return reusableVector_.cbegin();
    }

    template <typename TypeT>
    ReusableVector<TypeT>::ConstIteratorType ReusableVector<TypeT>::cend() const noexcept {
        // The reusable vector is full
        if (numberOfActiveElements_ == capacity_)
            return reusableVector_.cend();

        auto it = reusableVector_.cbegin();
        std::advance(it, numberOfActiveElements_);

        return it;
    }

    #ifndef NDEBUG
    template <typename TypeT>
    void ReusableVector<TypeT>::printReusableVectorDebug(std::ostream& out) const {
        out << "Vector:";
        for (const TypeT& x : reusableVector_)
            out << " " << std::to_string(x);
        out << std::endl;

        out << "Reusable vector:";
        for (auto it = cbegin(); it != cend(); ++it)
            out << " " << std::to_string(*it);
        out << std::endl;

        out << "Number of active elements: " << std::to_string(size()) << std::endl;
        out << "Number of allocated elements: " << std::to_string(numberOfAllocatedElements_) << std::endl;
        out << "Capacity: " << std::to_string(capacity()) << std::endl;
    }
    #endif
}   // namespace Hydra::Container::ReusableVector
