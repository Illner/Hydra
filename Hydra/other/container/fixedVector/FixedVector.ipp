#pragma once

#include "./FixedVector.hpp"

namespace Hydra::Container::FixedVector {

    template <typename TypeT>
    bool FixedVector<TypeT>::empty() const noexcept {
        return numberOfActiveElements_ == 0;
    }

    template <typename TypeT>
    std::size_t FixedVector<TypeT>::size() const noexcept {
        return numberOfActiveElements_;
    }

    template <typename TypeT>
    std::size_t FixedVector<TypeT>::capacity() const noexcept {
        return fixedVector_.size();
    }

    template <typename TypeT>
    void FixedVector<TypeT>::changeNumberOfActiveElements(std::size_t newNumberOfActiveElements) {
        assert(newNumberOfActiveElements <= capacity());

        numberOfActiveElements_ = newNumberOfActiveElements;
    }

    template <typename TypeT>
    void FixedVector<TypeT>::decreaseNumberOfActiveElements(std::size_t numberOfRemovedElements) {
        assert(numberOfRemovedElements > 0);
        assert(numberOfRemovedElements <= size());

        numberOfActiveElements_ -= numberOfRemovedElements;
    }

    template <typename TypeT>
    void FixedVector<TypeT>::increaseNumberOfActiveElements(std::size_t numberOfAddedElements) {
        assert(numberOfAddedElements > 0);
        assert(numberOfAddedElements + size() <= capacity());

        numberOfActiveElements_ += numberOfAddedElements;
    }

    template <typename TypeT>
    void FixedVector<TypeT>::swap(std::size_t firstElementPosition, std::size_t secondElementPosition) {
        assert(firstElementPosition < capacity());
        assert(secondElementPosition < capacity());

        #ifndef NDEBUG
        if (firstElementPosition >= numberOfActiveElements_ || secondElementPosition >= numberOfActiveElements_)
            throw Exception::Container::FixedVector::AttemptToSwapInactiveElementException(firstElementPosition, secondElementPosition,
                                                                                           numberOfActiveElements_);
        #endif

        TypeT tmp = std::move(fixedVector_[firstElementPosition]);
        fixedVector_[firstElementPosition] = std::move(fixedVector_[secondElementPosition]);
        fixedVector_[secondElementPosition] = std::move(tmp);
    }

    template <typename TypeT>
    void FixedVector<TypeT>::swap(std::size_t elementPosition) {
        assert(numberOfActiveElements_ > 0);

        swap(elementPosition, numberOfActiveElements_ - 1);
    }

    template <typename TypeT>
    void FixedVector<TypeT>::swap(TypeT element) {
        for (std::size_t i = 0; i < numberOfActiveElements_; ++i) {
            // The element has been found
            if (fixedVector_[i] == element) {
                swap(i);

                return;
            }
        }

        // The element does not exist as an active element in the fixed vector
        throw Exception::Container::FixedVector::ElementDoesNotExistException<TypeT>(element);
    }

    template <typename TypeT>
    void FixedVector<TypeT>::swap(TypeTSetType& elementSet) {
        std::size_t i = 0;

        while (true) {
            if (i == numberOfActiveElements_)
                break;

            if (elementSet.empty())
                break;

            // An element we want to delete
            if (auto itTmp = elementSet.find(fixedVector_[i]); itTmp != elementSet.end()) {
                swap(i);
                elementSet.erase(itTmp);
                decreaseNumberOfActiveElements();
            }
            else
                ++i;
        }

        // Some elements do not exist
        if (!elementSet.empty()) {
            bool firstTmp = true;
            std::stringstream stringStreamTmp;

            for (const TypeT& element : Other::sortUnorderedSet(elementSet)) {
                if (firstTmp)
                    firstTmp = false;
                else
                    stringStreamTmp << ", ";

                stringStreamTmp << std::to_string(element);
            }

            // Some elements do not exist as active elements in the fixed vector
            throw Exception::Container::FixedVector::ElementsDoNotExistException(stringStreamTmp.str());
        }
    }

    template <typename TypeT>
    void FixedVector<TypeT>::swapWithoutRemovingElementsFromSet(const TypeTSetType& elementSet) {
        std::size_t numberOfHits = 0;
        std::size_t setSize = elementSet.size();

        std::size_t i = 0;

        while (true) {
            if (i == numberOfActiveElements_)
                break;

            if (numberOfHits == setSize)
                break;

            // An element we want to delete
            if (Other::containInSet(elementSet, fixedVector_[i])) {
                swap(i);
                decreaseNumberOfActiveElements();

                ++numberOfHits;
            }
            else
                ++i;
        }

        assert(numberOfHits == setSize);
    }

    template <typename TypeT>
    void FixedVector<TypeT>::swapWithoutRemovingElementsFromVectorSet(const VectorSetType& elementVectorSet) {
        std::size_t numberOfHits = 0;
        std::size_t vectorSetSize = elementVectorSet.size();

        std::size_t i = 0;

        while (true) {
            if (i == numberOfActiveElements_)
                break;

            if (numberOfHits == vectorSetSize)
                break;

            // An element we want to delete
            if (elementVectorSet.contains(fixedVector_[i])) {
                swap(i);
                decreaseNumberOfActiveElements();

                ++numberOfHits;
            }
            else
                ++i;
        }

        assert(numberOfHits == vectorSetSize);
    }

    template <typename TypeT>
    const TypeT& FixedVector<TypeT>::operator[](std::size_t position) const {
        assert(position < numberOfActiveElements_);

        return fixedVector_[position];
    }

    template <typename TypeT>
    typename FixedVector<TypeT>::ConstIteratorType FixedVector<TypeT>::begin() const noexcept {
        return fixedVector_.cbegin();
    }

    template <typename TypeT>
    typename FixedVector<TypeT>::ConstIteratorType FixedVector<TypeT>::end() const noexcept {
        if (fixedVector_.size() == numberOfActiveElements_)
            return fixedVector_.cend();

        auto it = fixedVector_.cbegin();
        std::advance(it, numberOfActiveElements_);

        return it;
    }

    #ifndef NDEBUG
    template <typename TypeT>
    void FixedVector<TypeT>::printFixedVectorDebug(std::ostream& out) const {
        out << "Vector: ";
        for (const TypeT& x : fixedVector_)
            out << std::to_string(x) << " ";
        out << std::endl;

        out << "Fixed vector: ";
        for (auto it = begin(); it != end(); ++it)
            out << std::to_string(*it) << " ";
        out << std::endl;

        out << "Number of active elements: " << std::to_string(size()) << std::endl;
        out << "Number of all elements: " << std::to_string(capacity()) << std::endl;
    }
    #endif
}   // namespace Hydra::Container::FixedVector
