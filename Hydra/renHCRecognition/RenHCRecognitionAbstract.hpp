#pragma once

#include <cassert>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/renHCRecognition/exceptions/RenHCRecognitionException.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/renHCRecognition/enums/RenHCRecognitionTypeEnum.hpp"

#include "Hydra/renHCRecognition/RenHCRecognitionAbstract.hxx"

namespace Hydra::RenHCRecognition {

    /**
     * RenH-C recognition (abstract class)
     * Copy and move methods are disabled!
     * Exception:
     *      SomethingCannotBeSavedAsStdSizeTException (debug)
     *      AttemptRemoveNotLastAssignedLiteralFromAssignmentStackException (debug)
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class RenHCRecognitionAbstract {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");
        static_assert(Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isValidClauseT::value, "Invalid ClauseIdT type!");

    public:
        using LiteralType = typename Formula::Literal<VarT, LiteralT>::LiteralType;
        using VariableSetType = typename Formula::Literal<VarT, LiteralT>::VariableSetType;
        using LiteralVectorType = typename Formula::Literal<VarT, LiteralT>::LiteralVectorType;
        using RenHCRecognitionStatisticsPtrType = typename RenHCRecognitionStatistics::RenHCRecognitionStatisticsPtrType;
        using ClauseIdSetType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdSetType;

    public:
        using ConnectedComponentStruct = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentStruct;

    public:
        using VariableSetOptionalType = std::optional<VariableSetType>;
        using FormulaRepresentationAbstractPtrType = const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;

    public:
        using IgnorePureLiteralTypeEnum = Hydra::IgnorePureLiteralTypeEnum;

    private:
        using BoolVectorType = std::vector<bool>;

    public:
        #ifndef NDEBUG
        RenHCRecognitionAbstract(RenHCRecognitionTypeEnum renHCRecognitionType, FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                 IgnorePureLiteralTypeEnum ignorePureLiteralType, bool initialFormula,
                                 RenHCRecognitionStatisticsPtrType renHCRecognitionStatisticsPtr)
            : renHCRecognitionType_(renHCRecognitionType), formulaRepresentationAbstractPtr_(formulaRepresentationAbstractPtr),
              renHCRecognitionStatisticsPtr_(renHCRecognitionStatisticsPtr),
              d_assignmentStack_(), d_activeClauseVector_(initialFormula ? formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses() : 0, true),
              d_assignedVariableVector_(static_cast<typename BoolVectorType::size_type>(initialFormula ? formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing() : 0), false),
              d_ignorePureLiteralType_(ignorePureLiteralType), d_initialFormula_(initialFormula) {
            assert(d_initialFormula_ || renHCRecognitionStatisticsPtr_ == nullptr);   // statistics are forbidden for the current component formula

            // Only for the initial formula
            if (d_initialFormula_) {
                // The variables cannot be saved as std::size_t
                if (!Other::unsignedValueCanBeSavedAsStdSizeT<VarT>(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula(), 1))
                    throw Exception::SomethingCannotBeSavedAsStdSizeTException("variables", formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());

                // The clauses cannot be saved as std::size_t
                if (!Other::unsignedValueCanBeSavedAsStdSizeT<ClauseIdT>(formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses()))
                    throw Exception::SomethingCannotBeSavedAsStdSizeTException("clauses", formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses());

                d_assignmentStack_.reserve(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());

                // Set inactive clauses
                for (ClauseIdT clauseId = 0; clauseId < formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses(); ++clauseId) {
                    // Satisfied clause
                    if (formulaRepresentationAbstractPtr_->isClauseSatisfied(clauseId))
                        d_activeClauseVector_[clauseId] = false;
                }

                // Set assigned variables
                for (VarT var = 1; var <= formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula(); ++var) {
                    if (formulaRepresentationAbstractPtr_->isVariableAssigned(var))
                        d_assignedVariableVector_[var] = true;
                }
            }
        }
        #else
        RenHCRecognitionAbstract(RenHCRecognitionTypeEnum renHCRecognitionType, FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                 RenHCRecognitionStatisticsPtrType renHCRecognitionStatisticsPtr)
            : renHCRecognitionType_(renHCRecognitionType), formulaRepresentationAbstractPtr_(formulaRepresentationAbstractPtr),
              renHCRecognitionStatisticsPtr_(renHCRecognitionStatisticsPtr) { }
        #endif

        RenHCRecognitionAbstract(const RenHCRecognitionAbstract&) = delete;
        RenHCRecognitionAbstract(RenHCRecognitionAbstract&&) noexcept = delete;

        RenHCRecognitionAbstract& operator=(const RenHCRecognitionAbstract&) = delete;
        RenHCRecognitionAbstract& operator=(RenHCRecognitionAbstract&&) noexcept = delete;

        virtual ~RenHCRecognitionAbstract() noexcept = default;

    private:
        RenHCRecognitionTypeEnum renHCRecognitionType_;

    protected:
        FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr_;

        RenHCRecognitionStatisticsPtrType renHCRecognitionStatisticsPtr_;

    protected:
        virtual void processInitialize() = 0;

        virtual void processSetAssignedLiteral(const LiteralType& lit, const VariableSetType& currentComponentVariableSet,
                                               bool firstAssignment, bool lastAssignment) = 0;

        virtual void processSetUnassignedLiteral(const LiteralType& lit) = 0;

        virtual void processSetInactiveClause(ClauseIdT clauseId) = 0;

        virtual void processSetActiveClause(ClauseIdT clauseId, const VariableSetType& currentComponentVariableSet) = 0;

        virtual VariableSetOptionalType processIsRenHC(const ConnectedComponentStruct& connectedComponentStruct) = 0;

    public:
        void initialize();

        /**
         * Set the literal as assigned
         * Note: only for the initial formula
         * @param lit a literal
         * @param currentComponentVariableSet a set of variables appearing in the current component
         */
        void setAssignedLiteral(const LiteralType& lit, const VariableSetType& currentComponentVariableSet);
        void setAssignedLiteralVector(const LiteralVectorType& literalVector, const VariableSetType& currentComponentVariableSet);

        /**
         * Set the literal as unassigned
         * Note: only for the initial formula
         * @param lit a literal
         * @throw AttemptRemoveNotLastAssignedLiteralFromAssignmentStackException (debug) if the literal is not the last assigned literal
         */
        void setUnassignedLiteral(const LiteralType& lit);
        void setUnassignedLiteralVector(const LiteralVectorType& literalVector, bool reverse = true);

        /**
         * Set the clause as inactive
         * Assert: the clause MUST be pure
         * Assert: the clause MUST be unresolved
         * Note: only for the initial formula
         * @param clauseId a clause identifier
         */
        void setInactiveClause(ClauseIdT clauseId);
        void setInactiveClauseSet(const ClauseIdSetType& clauseSet);

        /**
         * Set the clause as active
         * Assert: the clause MUST be pure
         * Assert: at least one variable in the current component
         * Note: only for the initial formula
         * @param clauseId a clause identifier
         * @param currentComponentVariableSet a set of variables appearing in the current component
         */
        void setActiveClause(ClauseIdT clauseId, const VariableSetType& currentComponentVariableSet);
        void setActiveClauseSet(const ClauseIdSetType& clauseSet, const VariableSetType& currentComponentVariableSet);

        /**
         * Check if the residual formula is renamable Horn.
         * If the residual formula is not renamable Horn, the optional type does not have a value.
         * Assert: at least one variable in the connected component
         * Note: only for the initial formula
         * @param connectedComponentStruct a connected component
         * @return a set of switched variables
         */
        VariableSetOptionalType isRenHC(const ConnectedComponentStruct& connectedComponentStruct);

    #ifndef NDEBUG
    private:
        LiteralVectorType d_assignmentStack_;
        BoolVectorType d_activeClauseVector_;
        BoolVectorType d_assignedVariableVector_;
        IgnorePureLiteralTypeEnum d_ignorePureLiteralType_;

    protected:
        bool d_initialFormula_;   // the initial formula vs the current component formula

    public:
        void printRenHCRecognitionDebug(std::ostream& out) const;

        /**
         * Check if the current component formula is renamable Horn considering the switched variables
         * Assert: the current component formula MUST NOT be simplified after the initialization (that is, there MUST BE NO assigned variable on the stack)
         * Note: used for verification
         * Note: only for the current component formula
         * @param switchedVariableSet a set of switched variables
         * @return true if the current component formula is renamable Horn considering the switched variables. Otherwise, false is returned.
         */
        bool verifyRenHCDebug(const VariableSetType& switchedVariableSet) const;

    protected:
        virtual void processPrintRenHCRecognitionDebug(std::ostream& out) const = 0;

        virtual bool processVerifyRenHCDebug(const VariableSetType& switchedVariableSet) const = 0;
    #endif
    };
}   // namespace Hydra::RenHCRecognition

#include "./RenHCRecognitionAbstract.ipp"
