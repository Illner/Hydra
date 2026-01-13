#pragma once

#include <cassert>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "Hydra/circuit/node/NodeAbstract.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/partialAssignment/PartialAssignment.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/formula/enums/ClauseStatusEnum.hpp"
#include "Hydra/formula/enums/ClauseStatusWatchedLiteralEnum.hpp"

#ifndef NDEBUG
    #include <algorithm>
#endif

namespace Hydra::Circuit::Node {

    /**
     * Clause representation
     * The clause can be modified (adding literals)
     * Copy and move methods (default) are allowed!
     * Used for: KromCLeaf, RenHCLeaf, PcLeaf
     * Exceptions:
     *      VariableDoesNotExistInMappingException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class Clause {
    private:
        using LiteralType = typename NodeAbstract<VarT, LiteralT>::LiteralType;
        using LiteralSetType = typename NodeAbstract<VarT, LiteralT>::LiteralSetType;
        using VariableSetType = typename NodeAbstract<VarT, LiteralT>::VariableSetType;
        using PartialAssignmentType = typename NodeAbstract<VarT, LiteralT>::PartialAssignmentType;
        using MappingFromVariableToLiteralType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToLiteralType;
        using MappingFromVariableToOriginalVariableType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;

    private:
        using ClauseStatusEnum = Formula::ClauseStatusEnum;
        using ClauseStatusWatchedLiteralEnum = Formula::ClauseStatusWatchedLiteralEnum;

    public:
        using ClauseSizeType = LiteralT;
        using ClauseType = std::vector<LiteralType>;

    private:
        using ClauseIndexOptionalType = std::optional<ClauseSizeType>;
        using ConstIteratorType = typename ClauseType::const_iterator;

    public:
        explicit Clause(ClauseSizeType reserve = 2) noexcept
            : clause_(), firstWatchedLiteralIndexOptional_(), secondWatchedLiteralIndexOptional_() {
            clause_.reserve(reserve);
        }

        explicit Clause(const ClauseType& clause, bool shrink = true)
            : clause_(clause), firstWatchedLiteralIndexOptional_(), secondWatchedLiteralIndexOptional_() {
            if (shrink)
                doShrink();
            setWatchedLiterals();
        }

        explicit Clause(ClauseType&& clause, bool shrink = true)
            : clause_(std::move(clause)), firstWatchedLiteralIndexOptional_(), secondWatchedLiteralIndexOptional_() {
            if (shrink)
                doShrink();
            setWatchedLiterals();
        }

        Clause(const Clause&) = default;
        Clause(Clause&&) noexcept = default;

        Clause& operator=(const Clause&) = default;
        Clause& operator=(Clause&&) noexcept = default;

    private:
        ClauseType clause_;
        ClauseIndexOptionalType firstWatchedLiteralIndexOptional_;
        ClauseIndexOptionalType secondWatchedLiteralIndexOptional_;

    private:
        /**
         * Set the watched literals
         */
        void setWatchedLiterals() noexcept;

        /**
         * Try to change the watched literal (needToChangeWatchedLiteralIndex)
         * Time complexity: O(|C|)
         * @param needToChangeWatchedLiteralIndex watched literal that needs to be changed (must be initialized!)
         * @param otherWatchedLiteralIndex the other watched literal (must be initialized!)
         * @param partialAssignment a partial assignment
         * @return true if the watched literal has been changed. Otherwise, false is returned.
         */
        bool findNewWatchedLiteral(ClauseIndexOptionalType& needToChangeWatchedLiteralIndex,
                                   const ClauseIndexOptionalType& otherWatchedLiteralIndex,
                                   const PartialAssignmentType& partialAssignment) noexcept;

    public:
        /**
         * @return the size of the clause
         */
        ClauseSizeType getClauseSize() const noexcept;

        /**
         * Shrink the clause
         */
        void doShrink() noexcept;

        /**
         * Check if the clause is renamable Horn with respect to the switched variables (switchedVariables)
         * Time complexity: O(|C|)
         * @param switchedVariables a set of variables that are switched
         * @return true if the clause is renamable Horn. Otherwise, false is returned.
         */
        bool clauseIsRenamableHorn(const VariableSetType& switchedVariables) const noexcept;

        /**
         * Check if the clause is Horn
         * Time complexity: O(|C|)
         * @return true if the clause is Horn. Otherwise, false is returned.
         */
        bool clauseIsHorn() const noexcept;

        /**
         * Check if the clause has at most two literals
         * Time complexity: O(1)
         * @return true if the clause has at most 2 literals. Otherwise, false is returned.
         */
        bool clauseHasAtMostTwoLiterals() const noexcept;

        /**
         * Time complexity: O(|C|)
         * @param partialAssignment a partial assignment
         * @return the clause status with respect to the partial assignment
         */
        ClauseStatusEnum getClauseStatus(const PartialAssignmentType& partialAssignment) const noexcept;

        /**
         * Update the watched literals based on the partial assignment (partialAssignment)
         * @param partialAssignment a partial assignment
         * @return the status of the clause (SATISFIED, UNSATISFIED, UNDEFINED, UNIT_CLAUSE_1, UNIT_CLAUSE_2)
         */
        ClauseStatusWatchedLiteralEnum updateWatchedLiterals(const PartialAssignmentType& partialAssignment) noexcept;

        /**
         * @return the first watched literal index
         */
        const ClauseIndexOptionalType& getFirstWatchedLiteralIndex() const noexcept;

        /**
         * @return the second watched literal index
         */
        const ClauseIndexOptionalType& getSecondWatchedLiteralIndex() const noexcept;

        /**
         * Print the watched literals
         * Note: (FirstWatchedLiteral, SecondWatchedLiteral)
         */
        void printWatchedLiterals(std::ostream& out) const;

        /**
         * Print the clause in the DIMACS CNF format
         */
        void printClause(std::ostream& out, const MappingFromVariableToOriginalVariableType& mapping) const;

        /**
         * Add a new literal to the clause
         * Time complexity: O(|C|) or O(1)
         * @param allowMultiOccurrentLiterals are multi-occurrent literals allowed in the clause
         */
        void addLiteral(const LiteralType& lit, bool allowMultiOccurrentLiterals = false);
        void addLiteral(LiteralType&& lit, bool allowMultiOccurrentLiterals = false);

        /**
         * Copy the clause
         * @param mapping a mapping from variables to literals
         * @return a new remapped clause
         * @throw VariableDoesNotExistInMappingException if a variable in the clause does not exist in the mapping
         */
        Clause<VarT, LiteralT> copyClause(const MappingFromVariableToLiteralType& mapping) const;

    public:
        ConstIteratorType begin() const noexcept;
        ConstIteratorType end() const noexcept;

    public:
        /**
         * Clause += Literal
         * Time complexity: O(|C|)
         * Note: if the literal already exists in the clause, nothing happens
         */
        Clause<VarT, LiteralT>& operator+=(const LiteralType& lit);
        Clause<VarT, LiteralT>& operator+=(LiteralType&& lit);

        /**
         * ostream << Clause
         * Note: the DIMACS CNF format is used
         */
        friend std::ostream& operator<<(std::ostream& out, const Clause& clause) {
            clause.printClause(out, {});
            return out;
        }

        /**
         * Returned clause = Clause + Literal
         * Time complexity: O(|C|)
         * If the literal already exists in the clause, just a copy of that clause is done
         */
        friend Clause<VarT, LiteralT> operator+(const Clause<VarT, LiteralT>& clause, const LiteralType& lit) {
            bool newLiteralExistsInClause = false;
            Clause<VarT, LiteralT> returnedClause(static_cast<ClauseSizeType>(clause.clause_.size() + 1));

            for (const LiteralType& litTmp : clause.clause_) {
                returnedClause.clause_.emplace_back(litTmp.getVariable(), litTmp.isPositive());

                if (!newLiteralExistsInClause && litTmp == lit)
                    newLiteralExistsInClause = true;
            }

            // The literal (lit) does not exist in the clause => the literal can be added
            if (!newLiteralExistsInClause)
                returnedClause.clause_.emplace_back(lit.getVariable(), lit.isPositive());

            returnedClause.setWatchedLiterals();   // watched literals

            return returnedClause;
        }

        /**
         * Returned clause = Clause_1 + Clause_2
         * Time complexity: O(|C_1| + |C_2|)
         * The returned clause does not contain any duplicate literal
         */
        friend Clause<VarT, LiteralT> operator+(const Clause<VarT, LiteralT>& clause1,
                                                const Clause<VarT, LiteralT>& clause2) {
            LiteralSetType seenLiterals;
            Clause<VarT, LiteralT> returnedClause(static_cast<ClauseSizeType>(clause1.clause_.size() + clause2.clause_.size()));

            // clause1
            for (const LiteralType& lit : clause1.clause_) {
                if (Other::containInSet(seenLiterals, lit))
                    continue;

                returnedClause.clause_.emplace_back(lit.getVariable(), lit.isPositive());
                seenLiterals.emplace(lit.getVariable(), lit.isPositive());
            }

            // clause2
            for (const LiteralType& lit : clause2.clause_) {
                if (Other::containInSet(seenLiterals, lit))
                    continue;

                returnedClause.clause_.emplace_back(lit.getVariable(), lit.isPositive());
                seenLiterals.emplace(lit.getVariable(), lit.isPositive());
            }

            returnedClause.setWatchedLiterals();   // watched literals

            return returnedClause;
        }

        /**
         * Clause[idx]
         */
        const LiteralType& operator[](ClauseSizeType idx) const;

    #ifndef NDEBUG
    private:
        mutable bool d_sortedClause_ = false;

    public:
        /**
         * Sort the clause
         * Time complexity: O (|C| x log(|C|))
         */
        void sortClauseDebug();

        void printClauseDebug(std::ostream& out);

        /**
         * Clause_1 == Clause_2
         */
        friend bool operator==(Clause<VarT, LiteralT>& clause1, Clause<VarT, LiteralT>& clause2) {
            if (clause1.clause_.size() != clause2.clause_.size())
                return false;

            // Sort the clauses
            clause1.sortClauseDebug();
            clause2.sortClauseDebug();

            for (ClauseSizeType i = 0; i < clause1.clause_.size(); ++i) {
                if (clause1.clause_[i] != clause2.clause_[i])
                    return false;
            }

            return true;
        }

        /**
         * Clause_1 != Clause_2
         */
        friend bool operator!=(Clause<VarT, LiteralT>& clause1, Clause<VarT, LiteralT>& clause2) {
            if (clause1.clause_.size() != clause2.clause_.size())
                return true;

            // Sort the clauses
            clause1.sortClauseDebug();
            clause2.sortClauseDebug();

            for (ClauseSizeType i = 0; i < clause1.clause_.size(); ++i) {
                if (clause1.clause_[i] != clause2.clause_[i])
                    return true;
            }

            return false;
        }

        /**
         * Clause_1 < Clause_2
         * Note: both clauses must be sorted
         */
        friend bool operator<(const Clause<VarT, LiteralT>& clause1, const Clause<VarT, LiteralT>& clause2) {
            if (clause1.clause_.size() < clause2.clause_.size())
                return true;

            if (clause1.clause_.size() > clause2.clause_.size())
                return false;

            assert(clause1.d_sortedClause_);
            assert(clause2.d_sortedClause_);

            for (ClauseSizeType i = 0; i < clause1.clause_.size(); ++i) {
                if (clause1.clause_[i] > clause2.clause_[i])
                    return false;
            }

            return true;
        }

        /**
         * Clause_1 > Clause_2
         * Note: both clauses must be sorted
         */
        friend bool operator>(const Clause<VarT, LiteralT>& clause1, const Clause<VarT, LiteralT>& clause2) {
            if (clause1.clause_.size() > clause2.clause_.size())
                return true;

            if (clause1.clause_.size() < clause2.clause_.size())
                return false;

            assert(clause1.d_sortedClause_);
            assert(clause2.d_sortedClause_);

            for (ClauseSizeType i = 0; i < clause1.clause_.size(); ++i) {
                if (clause1.clause_[i] < clause2.clause_[i])
                    return false;
            }

            return true;
        }
    #endif
    };
}   // namespace Hydra::Circuit::Node

#include "./Clause.ipp"
