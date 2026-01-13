#include "./VectorSet.hpp"

#include <algorithm>
#include <cassert>

#include "Hydra/other/container/exceptions/VectorSetException.hpp"

namespace Hydra::Container::VectorSet {

    bool VectorSet::empty() const noexcept {
        return addedElementVector_.empty();
    }

    std::size_t VectorSet::size() const noexcept {
        return addedElementVector_.size();
    }

    std::size_t VectorSet::capacity() const noexcept {
        return capacity_;
    }

    void VectorSet::clear() {
        for (std::size_t element : addedElementVector_) {
            assert(vectorSet_[element]);   // element is added

            vectorSet_[element] = false;
        }

        addedElementVector_.clear();
    }

    void VectorSet::emplace(std::size_t element, [[maybe_unused]] bool checkExistence) {
        assert(element < capacity_);   // valid element

        #ifndef NDEBUG
        if (checkExistence) {
            // The element has already been added
            if (vectorSet_[element])
                throw Exception::Container::VectorSet::AttemptToAddElementMultipleTimesException(element);
        }
        #endif

        // The element has already been added
        if (vectorSet_[element])
            return;

        vectorSet_[element] = true;
        addedElementVector_.emplace_back(element);
    }

    bool VectorSet::contains(std::size_t element) const {
        assert(element < capacity_);   // valid element

        return vectorSet_[element];
    }

    const VectorSet::IndexVectorType& VectorSet::getAddedElementVector(bool sort) noexcept {
        if (sort)
            std::sort(addedElementVector_.begin(), addedElementVector_.end());

        return addedElementVector_;
    }

    #ifndef NDEBUG
    void VectorSet::printVectorSetDebug(std::ostream& out) {
        out << "Vector set:";
        for (bool b : vectorSet_)
            out << " " << std::to_string(b);
        out << std::endl;

        out << "Added elements:";
        std::sort(addedElementVector_.begin(), addedElementVector_.end());
        for (std::size_t element : addedElementVector_)
            out << " " << std::to_string(element);
        out << std::endl;

        out << "Number of added elements: " << std::to_string(size()) << std::endl;
    }
    #endif
}   // namespace Hydra::Container::VectorSet
