#pragma once

#include "./Clause.hpp"

namespace Hydra::Circuit::Node {

    template <typename VarT, typename LiteralT>
    void Clause<VarT, LiteralT>::setWatchedLiterals() noexcept {
        if (firstWatchedLiteralIndexOptional_.has_value() && secondWatchedLiteralIndexOptional_.has_value()) {
            assert(*firstWatchedLiteralIndexOptional_ != *secondWatchedLiteralIndexOptional_);
            return;
        }

        firstWatchedLiteralIndexOptional_.reset();
        secondWatchedLiteralIndexOptional_.reset();

        if (clause_.size() == 1)
            firstWatchedLiteralIndexOptional_ = 0;
        else if (clause_.size() > 1) {
            firstWatchedLiteralIndexOptional_ = 0;
            secondWatchedLiteralIndexOptional_ = 1;
        }
    }

    template <typename VarT, typename LiteralT>
    bool Clause<VarT, LiteralT>::findNewWatchedLiteral(ClauseIndexOptionalType& needToChangeWatchedLiteralIndex,
                                                       const ClauseIndexOptionalType& otherWatchedLiteralIndex,
                                                       const PartialAssignmentType& partialAssignment) noexcept {
        assert(needToChangeWatchedLiteralIndex.has_value());
        assert(otherWatchedLiteralIndex.has_value());

        const LiteralType& otherWatchedLiteral = clause_[*otherWatchedLiteralIndex];

        for (ClauseSizeType i = 0; i < clause_.size(); ++i) {
            const LiteralType& lit = clause_[i];

            if (partialAssignment.complementaryLiteralExists(lit))
                continue;

            if (lit == otherWatchedLiteral)
                continue;

            needToChangeWatchedLiteralIndex = i;
            return true;
        }

        return false;
    }

    template <typename VarT, typename LiteralT>
    typename Clause<VarT, LiteralT>::ClauseSizeType
    Clause<VarT, LiteralT>::getClauseSize() const noexcept {
        return static_cast<ClauseSizeType>(clause_.size());
    }

    template <typename VarT, typename LiteralT>
    void Clause<VarT, LiteralT>::doShrink() noexcept {
        clause_.shrink_to_fit();
    }

    template <typename VarT, typename LiteralT>
    bool Clause<VarT, LiteralT>::clauseIsRenamableHorn(const VariableSetType& switchedVariables) const noexcept {
        ClauseSizeType numberOfPositiveLiteralsAfterSwitching = 0;

        for (const LiteralType& lit : clause_) {
            bool isSwitched = Other::containInSet(switchedVariables, lit.getVariable());

            // Literal is positive after switching
            if ((isSwitched && lit.isNegative()) || (!isSwitched && lit.isPositive())) {
                ++numberOfPositiveLiteralsAfterSwitching;

                // Clause is not renamable Horn
                if (numberOfPositiveLiteralsAfterSwitching > 1)
                    return false;
            }
        }

        return true;
    }

    template <typename VarT, typename LiteralT>
    bool Clause<VarT, LiteralT>::clauseIsHorn() const noexcept {
        ClauseSizeType numberOfPositiveLiterals = 0;

        for (const LiteralType& lit : clause_) {
            // Literal is positive
            if (lit.isPositive()) {
                ++numberOfPositiveLiterals;

                // Clause is not Horn
                if (numberOfPositiveLiterals > 1)
                    return false;
            }
        }

        return true;
    }

    template <typename VarT, typename LiteralT>
    bool Clause<VarT, LiteralT>::clauseHasAtMostTwoLiterals() const noexcept {
        if (clause_.size() <= 2)
            return true;

        return false;
    }

    template <typename VarT, typename LiteralT>
    typename Clause<VarT, LiteralT>::ClauseStatusEnum
    Clause<VarT, LiteralT>::getClauseStatus(const PartialAssignmentType& partialAssignment) const noexcept {
        ClauseSizeType numberOfAssignedLiterals = 0;

        for (const LiteralType& lit : clause_) {
            if (partialAssignment.literalExists(lit))
                return ClauseStatusEnum::SATISFIED;

            if (partialAssignment.complementaryLiteralExists(lit))
                ++numberOfAssignedLiterals;
        }

        switch (getClauseSize() - numberOfAssignedLiterals) {
            case 0:
                return ClauseStatusEnum::EMPTY;
            case 1:
                return ClauseStatusEnum::UNIT_CLAUSE;
            default:
                return ClauseStatusEnum::UNRESOLVED;
        }
    }

    template <typename VarT, typename LiteralT>
    typename Clause<VarT, LiteralT>::ClauseStatusWatchedLiteralEnum
    Clause<VarT, LiteralT>::updateWatchedLiterals(const PartialAssignmentType& partialAssignment) noexcept {
        // No watched literal is set
        if (!firstWatchedLiteralIndexOptional_.has_value() && !secondWatchedLiteralIndexOptional_.has_value()) {
            assert(getClauseSize() == 0);   // the clause should be empty

            return ClauseStatusWatchedLiteralEnum::EMPTY;
        }

        // Only the first watched literal is set
        if (firstWatchedLiteralIndexOptional_.has_value() && !secondWatchedLiteralIndexOptional_.has_value()) {
            assert(getClauseSize() == 1);   // the clause should be unit

            const LiteralType& lit = clause_[*firstWatchedLiteralIndexOptional_];

            if (partialAssignment.complementaryLiteralExists(lit))
                return ClauseStatusWatchedLiteralEnum::EMPTY;

            if (partialAssignment.literalExists(lit))
                return ClauseStatusWatchedLiteralEnum::SATISFIED;

            return ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_1;
        }

        assert(*firstWatchedLiteralIndexOptional_ != *secondWatchedLiteralIndexOptional_);

        const LiteralType& firstWatchedLiteral = clause_[*firstWatchedLiteralIndexOptional_];
        const LiteralType& secondWatchedLiteral = clause_[*secondWatchedLiteralIndexOptional_];

        // The clause is satisfied
        if (partialAssignment.literalExists(firstWatchedLiteral) ||
            partialAssignment.literalExists(secondWatchedLiteral))
            return ClauseStatusWatchedLiteralEnum::SATISFIED;

        // No change
        if (!partialAssignment.complementaryLiteralExists(firstWatchedLiteral) &&
            !partialAssignment.complementaryLiteralExists(secondWatchedLiteral))
            return ClauseStatusWatchedLiteralEnum::UNDEFINED;

        // The first watched literal is invalid
        if (partialAssignment.complementaryLiteralExists(firstWatchedLiteral)) {
            if (!findNewWatchedLiteral(firstWatchedLiteralIndexOptional_,
                                       secondWatchedLiteralIndexOptional_,
                                       partialAssignment)) {
                // Both watched literals are invalid and cannot be changed. The clause is empty.
                if (partialAssignment.complementaryLiteralExists(secondWatchedLiteral))
                    return ClauseStatusWatchedLiteralEnum::EMPTY;

                // Only the first watched literal is invalid and cannot be changed. The clause is unit.
                return ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_2;
            }
        }

        // The second watched literal is invalid
        if (partialAssignment.complementaryLiteralExists(secondWatchedLiteral)) {
            if (!findNewWatchedLiteral(secondWatchedLiteralIndexOptional_,
                                       firstWatchedLiteralIndexOptional_,
                                       partialAssignment)) {
                // Only the second watched literal is invalid and cannot be changed. The clause is unit.
                return ClauseStatusWatchedLiteralEnum::UNIT_CLAUSE_1;
            }
        }

        return ClauseStatusWatchedLiteralEnum::UNDEFINED;
    }

    template <typename VarT, typename LiteralT>
    const typename Clause<VarT, LiteralT>::ClauseIndexOptionalType&
    Clause<VarT, LiteralT>::getFirstWatchedLiteralIndex() const noexcept {
        return firstWatchedLiteralIndexOptional_;
    }

    template <typename VarT, typename LiteralT>
    const typename Clause<VarT, LiteralT>::ClauseIndexOptionalType&
    Clause<VarT, LiteralT>::getSecondWatchedLiteralIndex() const noexcept {
        return secondWatchedLiteralIndexOptional_;
    }

    template <typename VarT, typename LiteralT>
    void Clause<VarT, LiteralT>::printWatchedLiterals(std::ostream& out) const {
        out << "(";

        // First watched literal
        if (!firstWatchedLiteralIndexOptional_.has_value())
            out << "none";
        else
            out << clause_[*firstWatchedLiteralIndexOptional_];

        out << ",";

        // Second watched literal
        if (!secondWatchedLiteralIndexOptional_.has_value())
            out << "none";
        else
            out << clause_[*secondWatchedLiteralIndexOptional_];

        out << ")";
    }

    template <typename VarT, typename LiteralT>
    void Clause<VarT, LiteralT>::printClause(std::ostream& out,
                                             const MappingFromVariableToOriginalVariableType& mapping) const {
        for (const LiteralType& lit : clause_) {
            lit.printLiteral(out, mapping);
            out << " ";
        }

        out << "0" << std::endl;   // end of the clause
    }

    template <typename VarT, typename LiteralT>
    void Clause<VarT, LiteralT>::addLiteral(const LiteralType& lit, bool allowMultiOccurrentLiterals) {
        LiteralType litCopy = lit;
        addLiteral(std::move(litCopy), allowMultiOccurrentLiterals);
    }

    template <typename VarT, typename LiteralT>
    void Clause<VarT, LiteralT>::addLiteral(LiteralType&& lit, bool allowMultiOccurrentLiterals) {
        // Check if the literal already exists in the clause
        if (!allowMultiOccurrentLiterals && Other::containInVector(clause_, lit))
            return;

        clause_.push_back(std::move(lit));
        setWatchedLiterals();   // watched literals

        #ifndef NDEBUG
        d_sortedClause_ = false;
        #endif
    }

    template <typename VarT, typename LiteralT>
    Clause<VarT, LiteralT> Clause<VarT, LiteralT>::copyClause(const MappingFromVariableToLiteralType& mapping) const {
        ClauseType newClause;
        newClause.reserve(clause_.size());

        for (const LiteralType& lit : clause_) {
            // The variable exists in the mapping
            if (auto itTmp = mapping.find(lit.getVariable()); itTmp != mapping.end()) {
                newClause.emplace_back(itTmp->second.getVariable(), itTmp->second.isPositive() ? lit.isPositive() : !lit.isPositive());
            }
            // The variable does not exist in the mapping
            else {
                std::stringstream stringStreamTmp = Other::createStringStreamFromMapWithToStringConversion(mapping);
                throw Exception::VariableDoesNotExistInMappingException(lit.getVariable(), stringStreamTmp.str());
            }
        }

        return Clause<VarT, LiteralT>(std::move(newClause));
    }

    template <typename VarT, typename LiteralT>
    typename Clause<VarT, LiteralT>::ConstIteratorType Clause<VarT, LiteralT>::begin() const noexcept {
        return clause_.cbegin();
    }

    template <typename VarT, typename LiteralT>
    typename Clause<VarT, LiteralT>::ConstIteratorType Clause<VarT, LiteralT>::end() const noexcept {
        return clause_.cend();
    }

    template <typename VarT, typename LiteralT>
    Clause<VarT, LiteralT>& Clause<VarT, LiteralT>::operator+=(const LiteralType& lit) {
        addLiteral(lit, false);
        return *this;
    }

    template <typename VarT, typename LiteralT>
    Clause<VarT, LiteralT>& Clause<VarT, LiteralT>::operator+=(LiteralType&& lit) {
        addLiteral(std::move(lit), false);
        return *this;
    }

    template <typename VarT, typename LiteralT>
    const typename Clause<VarT, LiteralT>::LiteralType&
    Clause<VarT, LiteralT>::operator[](ClauseSizeType idx) const {
        assert(idx >= 0 && idx < clause_.size());

        return clause_[idx];
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    void Clause<VarT, LiteralT>::sortClauseDebug() {
        // Clause is already sorted
        if (d_sortedClause_)
            return;

        std::sort(clause_.begin(), clause_.end());
        d_sortedClause_ = true;
    }

    template <typename VarT, typename LiteralT>
    void Clause<VarT, LiteralT>::printClauseDebug(std::ostream& out) {
        sortClauseDebug();   // deterministic output

        for (const LiteralType& lit : clause_)
            out << lit << " ";

        out << "0";   // end of the clause
    }
    #endif
}   // namespace Hydra::Circuit::Node
