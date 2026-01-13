#pragma once

#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/other/container/exceptions/ContagiousOccurrenceListException.hpp"

namespace Hydra::Container::ContagiousOccurrenceList {

    using FormulaSizeType = Hydra::Formula::Representation::FormulaSizeType;

    /**
     * Contagious occurrence list representation
     * Copy and move methods (default) are allowed!
     * Invariant: AT LEAST ONE variable
     * Invariant: every variable can appear in a clause AT MOST ONCE
     * Exceptions:
     *      OverflowException (debug)
     *      AttemptToAddDuplicateOccurrenceException (debug)
     *      AttemptToRemoveOccurrenceDoesNotExistException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class ContagiousOccurrenceList {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");
        static_assert(Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isValidClauseT::value, "Invalid ClauseIdT type!");

    private:
        using LiteralType = typename Formula::Literal<VarT, LiteralT>::LiteralType;

    private:
        using OccurrenceListType = std::vector<ClauseIdT>;
        using LiteralTOffsetVectorType = std::vector<FormulaSizeType>;

    public:
        using ClauseIdVectorType = std::vector<ClauseIdT>;
        using ClauseIdSetType = Other::HashMap::SetType<ClauseIdT>;
        using ConstIteratorType = typename OccurrenceListType::const_iterator;

    public:
        ContagiousOccurrenceList(ClauseIdT numberOfClauses, const ClauseIdVectorType& literalNumberOfOccurrences)
            : separator_(numberOfClauses), literalTOffset_(), literalTEndOffset_(),
              occurrenceList_((literalNumberOfOccurrences.size() - 2) /* number of all literals */ + std::accumulate(literalNumberOfOccurrences.begin(), literalNumberOfOccurrences.end(), static_cast<FormulaSizeType>(0)) /* formula size */, separator_) {
            assert(literalNumberOfOccurrences.size() > 2);
            assert((literalNumberOfOccurrences.size() % 2) == 0);
            assert(literalNumberOfOccurrences[0] == 0);
            assert(literalNumberOfOccurrences[1] == 0);

            initializeDataStructures(literalNumberOfOccurrences);
        }

        ContagiousOccurrenceList(const ContagiousOccurrenceList&) = default;
        ContagiousOccurrenceList(ContagiousOccurrenceList&&) noexcept = default;

        ContagiousOccurrenceList& operator=(const ContagiousOccurrenceList&) = default;
        ContagiousOccurrenceList& operator=(ContagiousOccurrenceList&&) noexcept = default;

    private:
        ClauseIdT separator_;
        LiteralTOffsetVectorType literalTOffset_;
        LiteralTOffsetVectorType literalTEndOffset_;
        OccurrenceListType occurrenceList_;

    private:
        /**
         * Initialize the data structures:
         *      occurrenceList_
         *      literalTOffset_, literalTEndOffset_
         * @param literalNumberOfOccurrences for EVERY literalT, it contains the number of its occurrences in the formula
         */
        void initializeDataStructures(const ClauseIdVectorType& literalNumberOfOccurrences);

    public:
        /**
         * Add a new occurrence
         * @param lit a literal
         * @param clauseId a clause identifier
         * @throw OverflowException (debug) if overflow occurred
         * @throw AttemptToAddDuplicateOccurrenceException (debug) if the same occurrence already exists in the occurrence list
         */
        void addOccurrence(const LiteralType& lit, ClauseIdT clauseId);
        void addOccurrence(LiteralT literalT, ClauseIdT clauseId);

        /**
         * Remove an occurrence
         * @param lit a literal
         * @param clauseId a clause identifier
         * @throw AttemptToRemoveOccurrenceDoesNotExistException if the clause identifier does not exist in the occurrence list
         */
        void removeOccurrence(const LiteralType& lit, ClauseIdT clauseId);
        void removeOccurrence(LiteralT literalT, ClauseIdT clauseId);

        /**
         * Remove every occurrence that is not mentioned in keepClauseIdSet
         * @param lit a literal
         * @param keepClauseIdSet a set of clauses that will be kept
         * @return a vector of clauses that have been removed
         */
        ClauseIdVectorType removeOccurrence(const LiteralType& lit, const ClauseIdSetType& keepClauseIdSet);
        ClauseIdVectorType removeOccurrence(LiteralT literalT, const ClauseIdSetType& keepClauseIdSet);

        /**
         * Remove every occurrence that is between firstClauseId (included) and lastClauseId (NOT included)
         * Assert: firstClauseId < lastClauseId
         * Note: lastClauseId can be separator_
         * @param lit a literal
         * @param firstClauseId a first clause identifier
         * @param lastClauseId a last clause identifier
         * @param atMostTwoOccurrences (AspvallRenHCRecognition) if exactly two occurrences have been removed, the removal process ends
         * @return true if at least one occurrence has been removed. Otherwise, false is returned.
         */
        bool removeOccurrence(const LiteralType& lit, ClauseIdT firstClauseId, ClauseIdT lastClauseId, bool atMostTwoOccurrences = false);
        bool removeOccurrence(LiteralT literalT, ClauseIdT firstClauseId, ClauseIdT lastClauseId, bool atMostTwoOccurrences = false);

        /**
         * Time complexity: O(#occurrences)
         * @param lit a literal
         * @param clauseId a clause identifier
         * @return true if the occurrence exists in the occurrence list. Otherwise, false is returned.
         */
        bool occurrenceExists(const LiteralType& lit, ClauseIdT clauseId) const;
        bool occurrenceExists(LiteralT literalT, ClauseIdT clauseId) const;

        /**
         * Time complexity: O(#occurrences)
         * @param lit a literal
         * @return a vector containing all occurrences of the literal (lit)
         */
        ClauseIdVectorType getClauseIdVector(const LiteralType& lit) const;
        ClauseIdVectorType getClauseIdVector(LiteralT literalT) const;

        /**
         * Time complexity: O(#occurrences)
         * @param lit a literal
         * @return a set containing all occurrences of the literal (lit)
         */
        ClauseIdSetType getClauseIdSet(const LiteralType& lit) const;
        ClauseIdSetType getClauseIdSet(LiteralT literalT) const;

        /**
         * Time complexity: O(1)
         * @param lit a literal
         * @return the number of occurrences of the literal (lit)
         */
        ClauseIdT getNumberOfOccurrences(const LiteralType& lit) const;
        ClauseIdT getNumberOfOccurrences(LiteralT literalT) const;

        /**
         * Time complexity: O(1)
         * @param var a variable
         * @return the number of occurrences of the variable (var)
         */
        ClauseIdT getNumberOfVariableOccurrences(VarT var) const;

    public:
        ConstIteratorType begin(const LiteralType& lit) const noexcept;
        ConstIteratorType begin(LiteralT literalT) const noexcept;

        ConstIteratorType end(const LiteralType& lit) const noexcept;
        ConstIteratorType end(LiteralT literalT) const noexcept;

    #ifndef NDEBUG
    public:
        void printContagiousOccurrenceListDebug(std::ostream& out) const;
    #endif
    };
}   // namespace Hydra::Container::ContagiousOccurrenceList

#include "./ContagiousOccurrenceList.ipp"
