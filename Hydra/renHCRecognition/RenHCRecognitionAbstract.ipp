#pragma once

#include "./RenHCRecognitionAbstract.hpp"

namespace Hydra::RenHCRecognition {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::initialize() {
        // Statistics
        if (renHCRecognitionStatisticsPtr_)
            renHCRecognitionStatisticsPtr_->initializeTimer.startStopwatch();

        processInitialize();

        // Statistics
        if (renHCRecognitionStatisticsPtr_)
            renHCRecognitionStatisticsPtr_->initializeTimer.stopStopwatch();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::setAssignedLiteral(const LiteralType& lit, const VariableSetType& currentComponentVariableSet) {
        assert(d_initialFormula_);

        #ifndef NDEBUG
        assert(lit.getVariable() < d_assignedVariableVector_.size());
        assert(!d_assignedVariableVector_[lit.getVariable()]);   // not assigned
        d_assignedVariableVector_[lit.getVariable()] = true;

        d_assignmentStack_.emplace_back(lit.getVariable(), lit.isPositive());
        #endif

        // Statistics
        if (renHCRecognitionStatisticsPtr_)
            renHCRecognitionStatisticsPtr_->setAssignedLiteralTimer.startStopwatch();

        processSetAssignedLiteral(lit, currentComponentVariableSet, true, true);

        // Statistics
        if (renHCRecognitionStatisticsPtr_)
            renHCRecognitionStatisticsPtr_->setAssignedLiteralTimer.stopStopwatch();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::setAssignedLiteralVector(const LiteralVectorType& literalVector,
                                                                                       const VariableSetType& currentComponentVariableSet) {
        assert(d_initialFormula_);

        if (literalVector.empty())
            return;

        // Statistics
        if (renHCRecognitionStatisticsPtr_)
            renHCRecognitionStatisticsPtr_->setAssignedLiteralTimer.startStopwatch();

        std::size_t indexOfLastAssignment = literalVector.size() - 1;

        for (std::size_t i = 0; i < literalVector.size(); ++i) {
            const LiteralType& lit = literalVector[i];

            #ifndef NDEBUG
            assert(lit.getVariable() < d_assignedVariableVector_.size());
            assert(!d_assignedVariableVector_[lit.getVariable()]);   // not assigned
            d_assignedVariableVector_[lit.getVariable()] = true;

            d_assignmentStack_.emplace_back(lit.getVariable(), lit.isPositive());
            #endif

            processSetAssignedLiteral(lit, currentComponentVariableSet, (i == 0), (i == indexOfLastAssignment));
        }

        // Statistics
        if (renHCRecognitionStatisticsPtr_)
            renHCRecognitionStatisticsPtr_->setAssignedLiteralTimer.stopStopwatch();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::setUnassignedLiteral(const LiteralType& lit) {
        assert(d_initialFormula_);

        #ifndef NDEBUG
        assert(lit.getVariable() < d_assignedVariableVector_.size());
        assert(d_assignedVariableVector_[lit.getVariable()]);   // assigned
        d_assignedVariableVector_[lit.getVariable()] = false;

        // The literal is not the last assigned literal in the assignment stack
        if (d_assignmentStack_.empty() || d_assignmentStack_.back() != lit) {
            std::stringstream stringStreamTmp = Other::createStringStreamFromContainer(d_assignmentStack_.cbegin(), d_assignmentStack_.cend());
            throw Exception::RenHCRecognition::AttemptRemoveNotLastAssignedLiteralFromAssignmentStackException(lit, stringStreamTmp.str());
        }

        d_assignmentStack_.pop_back();
        #endif

        // Statistics
        if (renHCRecognitionStatisticsPtr_)
            renHCRecognitionStatisticsPtr_->setUnassignedLiteralTimer.startStopwatch();

        processSetUnassignedLiteral(lit);

        // Statistics
        if (renHCRecognitionStatisticsPtr_)
            renHCRecognitionStatisticsPtr_->setUnassignedLiteralTimer.stopStopwatch();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::setUnassignedLiteralVector(const LiteralVectorType& literalVector, bool reverse) {
        assert(d_initialFormula_);

        if (literalVector.empty())
            return;

        // Remove literals in the reverse order
        if (reverse) {
            for (auto it = literalVector.rbegin(); it != literalVector.rend(); ++it)
                setUnassignedLiteral(*it);
        }

        // Remove literals in the standard order
        else {
            for (const LiteralType& lit : literalVector)
                setUnassignedLiteral(lit);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::setInactiveClause(ClauseIdT clauseId) {
        assert(d_initialFormula_);

        #ifndef NDEBUG
        assert(d_ignorePureLiteralType_ != IgnorePureLiteralTypeEnum::NONE);

        assert(clauseId < d_activeClauseVector_.size());
        assert(d_activeClauseVector_[clauseId]);   // active
        d_activeClauseVector_[clauseId] = false;
        assert(formulaRepresentationAbstractPtr_->isClauseUnresolved(clauseId));   // clause is unresolved

        assert(formulaRepresentationAbstractPtr_->doesClauseContainOnlyPureLiteralsOfIgnoredType(clauseId, d_ignorePureLiteralType_));
        #endif

        // Statistics
        if (renHCRecognitionStatisticsPtr_)
            renHCRecognitionStatisticsPtr_->setInactiveClauseTimer.startStopwatch();

        processSetInactiveClause(clauseId);

        // Statistics
        if (renHCRecognitionStatisticsPtr_)
            renHCRecognitionStatisticsPtr_->setInactiveClauseTimer.stopStopwatch();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::setInactiveClauseSet(const ClauseIdSetType& clauseSet) {
        assert(d_initialFormula_);

        #ifndef NDEBUG
        for (ClauseIdT clauseId : Other::sortUnorderedSet(clauseSet)) {
        #else
        for (ClauseIdT clauseId : clauseSet) {
        #endif
            setInactiveClause(clauseId);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::setActiveClause(ClauseIdT clauseId, const VariableSetType& currentComponentVariableSet) {
        assert(d_initialFormula_);

        #ifndef NDEBUG
        assert(d_ignorePureLiteralType_ != IgnorePureLiteralTypeEnum::NONE);

        assert(!currentComponentVariableSet.empty());   // at least one variable
        assert(clauseId < d_activeClauseVector_.size());
        assert(!d_activeClauseVector_[clauseId]);   // inactive
        d_activeClauseVector_[clauseId] = true;

        assert(formulaRepresentationAbstractPtr_->doesClauseContainOnlyPureLiteralsOfIgnoredType(clauseId, d_ignorePureLiteralType_));
        #endif

        // Statistics
        if (renHCRecognitionStatisticsPtr_)
            renHCRecognitionStatisticsPtr_->setActiveClauseTimer.startStopwatch();

        processSetActiveClause(clauseId, currentComponentVariableSet);

        // Statistics
        if (renHCRecognitionStatisticsPtr_)
            renHCRecognitionStatisticsPtr_->setActiveClauseTimer.stopStopwatch();
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::setActiveClauseSet(const ClauseIdSetType& clauseSet,
                                                                                 const VariableSetType& currentComponentVariableSet) {
        assert(d_initialFormula_);

        #ifndef NDEBUG
        for (ClauseIdT clauseId : Other::sortUnorderedSet(clauseSet)) {
        #else
        for (ClauseIdT clauseId : clauseSet) {
        #endif
            setActiveClause(clauseId, currentComponentVariableSet);
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::VariableSetOptionalType
    RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::isRenHC(const ConnectedComponentStruct& connectedComponentStruct) {
        assert(d_initialFormula_);
        assert(!connectedComponentStruct.variableSet.empty());   // at least one variable
        assert(d_ignorePureLiteralType_ != IgnorePureLiteralTypeEnum::NONE || connectedComponentStruct.pureLiteralVector.empty());

        // Statistics
        if (renHCRecognitionStatisticsPtr_)
            renHCRecognitionStatisticsPtr_->isRenHCTimer.startStopwatch();

        VariableSetOptionalType variableSetOptional = processIsRenHC(connectedComponentStruct);

        // Statistics
        if (renHCRecognitionStatisticsPtr_) {
            renHCRecognitionStatisticsPtr_->ratioOfRenHCCounter.addCount(static_cast<Statistics::LargeNumberType>(variableSetOptional.has_value()));

            renHCRecognitionStatisticsPtr_->isRenHCTimer.stopStopwatch();
        }

        return variableSetOptional;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::printRenHCRecognitionDebug(std::ostream& out) const {
        out << "RenH-C recognition" << std::endl;
        out << "Formula type: " << (d_initialFormula_ ? "initial formula" : "current component formula") << std::endl;
        out << "Type: " << renHCRecognitionTypeEnumToString(renHCRecognitionType_) << std::endl;

        // Only for the initial formula
        if (d_initialFormula_) {
            // Active clauses
            out << "Active clauses:";
            for (bool active : d_activeClauseVector_)
                out << " " << std::to_string(active);
            out << std::endl;

            // Assigned variables
            bool first = true;
            out << "Assigned variables:";
            for (bool assigned : d_assignedVariableVector_) {
                if (first) {
                    first = false;
                    continue;
                }

                out << " " << std::to_string(assigned);
            }
            out << std::endl;

            // Assigned variable stack
            out << "Assigned variable stack:";
            for (const LiteralType& lit : d_assignmentStack_)
                out << " " << lit;
            out << std::endl;
        }

        processPrintRenHCRecognitionDebug(out);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::verifyRenHCDebug(const VariableSetType& switchedVariableSet) const {
        assert(!d_initialFormula_);
        assert(d_assignmentStack_.empty());   // no assigned variable

        return processVerifyRenHCDebug(switchedVariableSet);
    }
    #endif
}   // namespace Hydra::RenHCRecognition
