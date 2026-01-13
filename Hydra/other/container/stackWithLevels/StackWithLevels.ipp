#pragma once

#include "./StackWithLevels.hpp"

namespace Hydra::Container::StackWithLevels {

    template <typename TypeT, typename LevelTypeT>
    bool StackWithLevels<TypeT, LevelTypeT>::isEmpty() const {
        if (stackLevel_.empty()) {
            assert(stack_.empty());

            return true;
        }

        return false;
    }

    template <typename TypeT, typename LevelTypeT>
    bool StackWithLevels<TypeT, LevelTypeT>::levelExists() const noexcept {
        return !stackLevel_.empty();
    }

    template <typename TypeT, typename LevelTypeT>
    void StackWithLevels<TypeT, LevelTypeT>::addNewLevel() {
        assert(stackLevel_.size() < d_maxNumberOfLevels_);
        assert(stackLevel_.empty() || (stackLevel_.back() <= stack_.size()));   // nondecreasing

        stackLevel_.emplace_back(stack_.size());
    }

    template <typename TypeT, typename LevelTypeT>
    void StackWithLevels<TypeT, LevelTypeT>::addElement(TypeT element) {
        assert(!stackLevel_.empty());   // some level
        assert(stack_.size() < d_maxNumberOfElements_);

        #ifndef NDEBUG
        // Check if the element already exists in the stack
        for (TypeT elementTmp : stack_) {
            if (elementTmp == element)
                throw Exception::Container::StackWithLevels::AttemptToAddElementMultipleTimesException(element);
        }
        #endif

        stack_.emplace_back(element);
    }

    template <typename TypeT, typename LevelTypeT>
    void StackWithLevels<TypeT, LevelTypeT>::removeCurrentLevel() {
        assert(!stackLevel_.empty());   // some level

        std::size_t currentLevel = stack_.size();
        std::size_t previousLevel = stackLevel_.back();
        stackLevel_.pop_back();

        assert(previousLevel <= currentLevel);   // valid level

        for (std::size_t i = previousLevel; i < currentLevel; ++i) {
            assert(!stack_.empty());   // not empty

            stack_.pop_back();
        }
    }

    template <typename TypeT, typename LevelTypeT>
    template <typename FunctorT>
    void StackWithLevels<TypeT, LevelTypeT>::removeCurrentLevel(FunctorT functor) {
        assert(!stackLevel_.empty());   // some level

        std::size_t currentLevel = stack_.size();
        std::size_t previousLevel = stackLevel_.back();
        stackLevel_.pop_back();

        assert(previousLevel <= currentLevel);   // valid level

        for (std::size_t i = previousLevel; i < currentLevel; ++i) {
            assert(!stack_.empty());   // not empty

            // Functor
            functor(stack_.back());

            stack_.pop_back();
        }
    }

    template <typename TypeT, typename LevelTypeT>
    void StackWithLevels<TypeT, LevelTypeT>::clear() noexcept {
        stack_.clear();
        stackLevel_.clear();
    }

    template <typename TypeT, typename LevelTypeT>
    template <typename FunctorT>
    void StackWithLevels<TypeT, LevelTypeT>::clear(FunctorT functor) {
        // Functor
        for (auto it = stack_.rbegin(); it != stack_.rend(); ++it)
            functor(*it);

        stack_.clear();
        stackLevel_.clear();
    }

    #ifndef NDEBUG
    template <typename TypeT, typename LevelTypeT>
    void StackWithLevels<TypeT, LevelTypeT>::printStackWithLevelsDebug(std::ostream& out) const {
        out << "Stack (with levels):";

        auto levelIt = stackLevel_.cbegin();

        for (std::size_t i = 0; i < stack_.size(); ++i) {
            // New level
            while ((levelIt != stackLevel_.cend()) && (*levelIt == i)) {
                out << " |";

                ++levelIt;
            }

            out << " " << std::to_string(stack_[i]);
        }

        for (; levelIt != stackLevel_.cend(); ++levelIt)
            out << " |";

        out << std::endl;
    }

    template <typename TypeT, typename LevelTypeT>
    template <typename FunctorT>
    void StackWithLevels<TypeT, LevelTypeT>::printStackWithLevelsDebug(std::ostream& out, FunctorT functor) const {
        auto levelIt = stackLevel_.cbegin();

        for (std::size_t i = 0; i < stack_.size(); ++i) {
            // New level
            while ((levelIt != stackLevel_.cend()) && (*levelIt == i)) {
                out << "| ";

                ++levelIt;
            }

            out << functor(stack_[i]) << " ";
        }

        for (; levelIt != stackLevel_.cend(); ++levelIt)
            out << "| ";

        out << std::endl;
    }
    #endif
}   // namespace Hydra::Container::StackWithLevels
