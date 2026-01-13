#pragma once

#include "./ContagiousOccurrenceList.hpp"

namespace Hydra::Container::ContagiousOccurrenceList {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::initializeDataStructures(const ClauseIdVectorType& literalNumberOfOccurrences) {
        literalTOffset_.reserve(literalNumberOfOccurrences.size());
        literalTEndOffset_.reserve(literalNumberOfOccurrences.size());

        LiteralT currentPosition = 0;
        FormulaSizeType currentOffset = 0;
        for (ClauseIdT clauseId : literalNumberOfOccurrences) {
            literalTOffset_.emplace_back(currentOffset);
            literalTEndOffset_.emplace_back(currentOffset);

            currentOffset += clauseId;
            if (++currentPosition > 2)   // because of the invalid indices 0 and 1
                ++currentOffset;         // because of the separator
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::addOccurrence(const LiteralType& lit, ClauseIdT clauseId) {
        addOccurrence(lit.getLiteralT(), clauseId);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::addOccurrence(LiteralT literalT, ClauseIdT clauseId) {
        assert(clauseId != separator_);
        assert(literalT != 0 && literalT != 1);
        assert(literalT < literalTOffset_.size());

        #ifndef NDEBUG
        // Check duplicities (lit)
        for (auto it = begin(literalT); it != end(literalT); ++it) {
            if (*it == clauseId)
                throw Exception::Container::ContagiousOccurrenceList::AttemptToAddDuplicateOccurrenceException<VarT, LiteralT, ClauseIdT>(literalT, clauseId, false);
        }

        // Check duplicities (~lit)
        LiteralType complementaryLitTmp = ~(Formula::createLiteralFromLiteralT<VarT, LiteralT>(literalT));
        LiteralT complementaryLiteralT = complementaryLitTmp.getLiteralT();
        for (auto it = begin(complementaryLiteralT); it != end(complementaryLiteralT); ++it) {
            if (*it == clauseId)
                throw Exception::Container::ContagiousOccurrenceList::AttemptToAddDuplicateOccurrenceException<VarT, LiteralT, ClauseIdT>(literalT, clauseId, true);
        }
        #endif

        #ifndef NDEBUG
        // Check overflow
        // Last literal
        if (literalT == (literalTOffset_.size() - 1)) {
            if (literalTEndOffset_[literalT] == (occurrenceList_.size() - 1))
                throw Exception::Container::ContagiousOccurrenceList::OverflowException<VarT, LiteralT>(literalT, literalTOffset_[literalT], literalTEndOffset_[literalT]);
        }
        // First / mid literal
        else if (literalTEndOffset_[literalT] + 1 == literalTOffset_[literalT + 1])
            throw Exception::Container::ContagiousOccurrenceList::OverflowException<VarT, LiteralT>(literalT, literalTOffset_[literalT], literalTEndOffset_[literalT]);
        #endif

        occurrenceList_[literalTEndOffset_[literalT]] = clauseId;
        ++literalTEndOffset_[literalT];
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::removeOccurrence(const LiteralType& lit, ClauseIdT clauseId) {
        removeOccurrence(lit.getLiteralT(), clauseId);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::removeOccurrence(LiteralT literalT, ClauseIdT clauseId) {
        assert(clauseId != separator_);
        assert(literalT != 0 && literalT != 1);
        assert(literalT < literalTOffset_.size());

        for (std::size_t i = literalTOffset_[literalT]; i < literalTEndOffset_[literalT]; ++i) {
            // The occurrence has been found
            if (occurrenceList_[i] == clauseId) {
                occurrenceList_[i] = occurrenceList_[literalTEndOffset_[literalT] - 1];
                occurrenceList_[literalTEndOffset_[literalT] - 1] = separator_;
                --literalTEndOffset_[literalT];

                return;
            }
        }

        throw Exception::Container::ContagiousOccurrenceList::AttemptToRemoveOccurrenceDoesNotExistException<VarT, LiteralT, ClauseIdT>(literalT, clauseId);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType
    ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::removeOccurrence(const LiteralType& lit, const ClauseIdSetType& keepClauseIdSet) {
        return removeOccurrence(lit.getLiteralT(), keepClauseIdSet);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType
    ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::removeOccurrence(LiteralT literalT, const ClauseIdSetType& keepClauseIdSet) {
        assert(literalT != 0 && literalT != 1);
        assert(literalT < literalTOffset_.size());

        #ifndef NDEBUG
        for (ClauseIdT clauseId : keepClauseIdSet)
            assert(clauseId != separator_);
        #endif

        ClauseIdVectorType removedClauseIdVector;
        removedClauseIdVector.reserve(getNumberOfOccurrences(literalT));

        std::size_t i = literalTOffset_[literalT];

        while (true) {
            if (i == literalTEndOffset_[literalT])
                break;

            // Keep clause
            if (Other::containInSet(keepClauseIdSet, occurrenceList_[i]))
                ++i;
            // Remove clause
            else {
                removedClauseIdVector.emplace_back(occurrenceList_[i]);

                occurrenceList_[i] = occurrenceList_[literalTEndOffset_[literalT] - 1];
                occurrenceList_[literalTEndOffset_[literalT] - 1] = separator_;
                --literalTEndOffset_[literalT];
            }
        }

        removedClauseIdVector.shrink_to_fit();

        return removedClauseIdVector;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::removeOccurrence(const LiteralType& lit, ClauseIdT firstClauseId, ClauseIdT lastClauseId,
                                                                               bool atMostTwoOccurrences) {
        return removeOccurrence(lit.getLiteralT(), firstClauseId, lastClauseId, atMostTwoOccurrences);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::removeOccurrence(LiteralT literalT, ClauseIdT firstClauseId, ClauseIdT lastClauseId,
                                                                               bool atMostTwoOccurrences) {
        assert(lastClauseId <= separator_);
        assert(firstClauseId < lastClauseId);
        assert(literalT != 0 && literalT != 1);
        assert(literalT < literalTOffset_.size());

        bool removedAtLeastOneOccurrence = false;
        std::size_t i = literalTOffset_[literalT];

        while (true) {
            if (i == literalTEndOffset_[literalT])
                break;

            // Keep clause
            if (occurrenceList_[i] < firstClauseId || occurrenceList_[i] >= lastClauseId)
                ++i;
            // Remove clause
            else {
                occurrenceList_[i] = occurrenceList_[literalTEndOffset_[literalT] - 1];
                occurrenceList_[literalTEndOffset_[literalT] - 1] = separator_;
                --literalTEndOffset_[literalT];

                // Exactly two occurrences have been removed
                if (atMostTwoOccurrences && removedAtLeastOneOccurrence)
                    return removedAtLeastOneOccurrence;

                removedAtLeastOneOccurrence = true;
            }
        }

        return removedAtLeastOneOccurrence;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::occurrenceExists(const LiteralType& lit, ClauseIdT clauseId) const {
        return occurrenceExists(lit.getLiteralT(), clauseId);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::occurrenceExists(LiteralT literalT, ClauseIdT clauseId) const {
        assert(clauseId != separator_);
        assert(literalT != 0 && literalT != 1);
        assert(literalT < literalTOffset_.size());

        for (auto it = begin(literalT); it != end(literalT); ++it) {
            // The occurrence has been found
            if (*it == clauseId)
                return true;
        }

        return false;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType
    ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::getClauseIdVector(const LiteralType& lit) const {
        return getClauseIdVector(lit.getLiteralT());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType
    ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::getClauseIdVector(LiteralT literalT) const {
        assert(literalT != 0 && literalT != 1);
        assert(literalT < literalTOffset_.size());

        ClauseIdVectorType clauseIdVector;
        clauseIdVector.reserve(getNumberOfOccurrences(literalT));

        for (auto it = begin(literalT); it != end(literalT); ++it) {
            clauseIdVector.emplace_back(*it);
        }

        return clauseIdVector;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::ClauseIdSetType
    ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::getClauseIdSet(const LiteralType& lit) const {
        return getClauseIdSet(lit.getLiteralT());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::ClauseIdSetType
    ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::getClauseIdSet(LiteralT literalT) const {
        assert(literalT != 0 && literalT != 1);
        assert(literalT < literalTOffset_.size());

        ClauseIdSetType clauseIdSet(getNumberOfOccurrences(literalT));

        for (auto it = begin(literalT); it != end(literalT); ++it) {
            clauseIdSet.insert(*it);
        }

        return clauseIdSet;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseIdT ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::getNumberOfOccurrences(const LiteralType& lit) const {
        return getNumberOfOccurrences(lit.getLiteralT());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseIdT ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::getNumberOfOccurrences(LiteralT literalT) const {
        assert(literalT != 0 && literalT != 1);
        assert(literalT < literalTOffset_.size());

        return static_cast<ClauseIdT>(literalTEndOffset_[literalT] - literalTOffset_[literalT]);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseIdT ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::getNumberOfVariableOccurrences(VarT var) const {
        assert(var > 0);

        return getNumberOfOccurrences(Formula::getPositiveLiteralT<VarT, LiteralT>(var)) +
               getNumberOfOccurrences(Formula::getNegativeLiteralT<VarT, LiteralT>(var));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::ConstIteratorType
    ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::begin(const LiteralType& lit) const noexcept {
        return begin(lit.getLiteralT());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::ConstIteratorType
    ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::begin(LiteralT literalT) const noexcept {
        assert(literalT != 0 && literalT != 1);
        assert(literalT < literalTOffset_.size());

        auto it = occurrenceList_.cbegin();
        std::advance(it, literalTOffset_[literalT]);

        return it;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::ConstIteratorType
    ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::end(const LiteralType& lit) const noexcept {
        return end(lit.getLiteralT());
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::ConstIteratorType
    ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::end(LiteralT literalT) const noexcept {
        assert(literalT != 0 && literalT != 1);
        assert(literalT < literalTOffset_.size());

        auto it = occurrenceList_.cbegin();
        std::advance(it, literalTEndOffset_[literalT]);

        return it;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void ContagiousOccurrenceList<VarT, LiteralT, ClauseIdT>::printContagiousOccurrenceListDebug(std::ostream& out) const {
        out << "Occurrence list: ";
        for (ClauseIdT clauseId : occurrenceList_)
            out << std::to_string(clauseId) << " ";
        out << std::endl;

        out << "Separator: " << std::to_string(separator_) << std::endl;

        out << "Literal offset (end offset): ";
        for (LiteralT literalT = 2; literalT < literalTOffset_.size(); ++literalT) {
            LiteralType litTmp = Formula::createLiteralFromLiteralT<VarT, LiteralT>(literalT);
            out << litTmp << ": " << std::to_string(literalTOffset_[literalT])
                << " (" << std::to_string(literalTEndOffset_[literalT]) << ") ";
        }
        out << std::endl;
    }
    #endif
}   // namespace Hydra::Container::ContagiousOccurrenceList
