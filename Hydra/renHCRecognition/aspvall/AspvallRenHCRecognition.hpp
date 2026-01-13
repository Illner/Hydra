#pragma once

#include <cassert>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/contagiousOccurrenceList/ContagiousOccurrenceList.hpp"
#include "Hydra/other/container/stackWithLevels/StackWithLevels.hpp"
#include "Hydra/other/container/variableStateVector/VariableStateVector.hpp"
#include "Hydra/renHCRecognition/RenHCRecognitionAbstract.hpp"
#include "Hydra/renHCRecognition/aspvall/AspvallRenHCRecognitionStructure.hpp"

#include "Hydra/renHCRecognition/enums/RenHCRecognitionTypeEnum.hpp"

namespace Hydra::RenHCRecognition::Aspvall {

    /**
     * Aspvall renH-C recognition (final class)
     * ASPVALL, Bengt. Recognizing disguised NR (1) instances of the satisfiability problem. Journal of Algorithms, 1980, 1.1: 97-103.
     * Exceptions:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     * @tparam VarAspT type used for an Aspvall variable
     * @tparam LiteralAspT type used for an Aspvall literal
     * @tparam ClauseIdAspT type used for an Aspvall clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT, typename VarAspT, typename LiteralAspT, typename ClauseIdAspT>
    class AspvallRenHCRecognition final : public RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT> {
        static_assert(Formula::Literal<VarAspT, LiteralAspT>::isValidVarT::value, "Invalid VarAspT type!");
        static_assert(Formula::Literal<VarAspT, LiteralAspT>::isValidLiteralT::value, "Invalid LiteralAspT type!");
        static_assert(Formula::Representation::FormulaRepresentationAbstract<VarAspT, LiteralAspT, ClauseIdAspT>::isValidClauseT::value, "Invalid ClauseIdAspT type!");

    public:
        using LiteralAspType = typename Formula::Literal<VarAspT, LiteralAspT>::LiteralType;
        using ClauseIdVectorType = typename AspvallRenHCRecognitionStruct<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::ClauseIdVectorType;
        using ClauseIdVectorAspType = typename AspvallRenHCRecognitionStruct<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>::ClauseIdVectorAspType;

    private:
        using LiteralVectorAspType = typename Formula::Literal<VarAspT, LiteralAspT>::LiteralVectorType;
        using LiteralType = typename RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::LiteralType;
        using VariableSetType = typename RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using VariableSetOptionalType = typename RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::VariableSetOptionalType;
        using RenHCRecognitionStatisticsPtrType = typename RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::RenHCRecognitionStatisticsPtrType;
        using FormulaRepresentationAbstractPtrType = typename RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    public:
        using FormulaAspType = std::vector<LiteralAspType>;

    private:
        using BoolVectorType = std::vector<bool>;
        using OccurrencePairAspType = std::pair<LiteralAspT, ClauseIdAspT>;
        using VariableStackWithLevelsAspType = Container::StackWithLevels::StackWithLevels<VarAspT, VarAspT>;
        using VariableStateVectorAspType = Container::VariableStateVector::VariableStateVector<VarAspT, LiteralAspT>;
        using ClauseIdStackWithLevelsAspType = Container::StackWithLevels::StackWithLevels<ClauseIdAspT, ClauseIdAspT>;
        using OccurrencePairStackWithLevelsAspType = Container::StackWithLevels::StackWithLevels<OccurrencePairAspType, FormulaSizeType>;
        using ContagiousOccurrenceListAspType = Container::ContagiousOccurrenceList::ContagiousOccurrenceList<VarAspT, LiteralAspT, ClauseIdAspT>;

    public:
        using AspvallRenHCRecognitionAspStruct = AspvallRenHCRecognitionStruct<VarT, LiteralT, ClauseIdT, VarAspT, LiteralAspT, ClauseIdAspT>;

    private:
        using ConnectedComponentStruct = typename RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::ConnectedComponentStruct;

    public:
        using IgnorePureLiteralTypeEnum = typename RenHCRecognition::RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>::IgnorePureLiteralTypeEnum;

    public:
        #ifndef NDEBUG
        AspvallRenHCRecognition(FormulaAspType&& formula, AspvallRenHCRecognitionAspStruct&& aspvallRenHCRecognitionStruct,
                                const ClauseIdVectorAspType& literalNumberOfOccurrences, FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                IgnorePureLiteralTypeEnum ignorePureLiteralType, bool initialFormula,
                                RenHCRecognitionStatisticsPtrType renHCRecognitionStatisticsPtr = nullptr)
            : RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>(RenHCRecognitionTypeEnum::ASPVALL, formulaRepresentationAbstractPtr,
                                                                  ignorePureLiteralType, initialFormula, renHCRecognitionStatisticsPtr),
              formula_(std::move(formula)),
              numberOfOriginalVariables_(static_cast<VarAspT>(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula())),
              contagiousOccurrenceList_(aspvallRenHCRecognitionStruct.numberOfClauses, literalNumberOfOccurrences),
              aspvallRenHCRecognitionStruct_(std::move(aspvallRenHCRecognitionStruct)),
              l_processedOriginalClauseVector_(initialFormula ? formulaRepresentationAbstractPtr->getNumberOfOriginalClauses() : 0, false),
              l_processedOriginalClauseStack_(),
              l_removedOccurrenceStackWithLevels_(initialFormula ? aspvallRenHCRecognitionStruct_.formulaSize : 0, initialFormula ? numberOfOriginalVariables_ : 0),
              l_satisfiedClauseVector_(initialFormula ? aspvallRenHCRecognitionStruct_.numberOfClauses : 0, false),
              l_variableStateVector_(initialFormula ? aspvallRenHCRecognitionStruct_.numberOfVariables : 0), l_literalNeedToBeProcessedVector_(),
              l_satisfiedClauseStackWithLevels_(initialFormula ? aspvallRenHCRecognitionStruct_.numberOfClauses : 0, initialFormula ? aspvallRenHCRecognitionStruct_.numberOfVariables : 0),
              l_assignedVariableStackWithLevels_(initialFormula ? aspvallRenHCRecognitionStruct_.numberOfVariables : 0, initialFormula ? aspvallRenHCRecognitionStruct_.numberOfVariables : 0),
              d_variableStateVector_(aspvallRenHCRecognitionStruct_.numberOfVariables) {
            assert(static_cast<ClauseIdAspT>(aspvallRenHCRecognitionStruct_.mappingFromAspvallClauseIdToOriginalClauseIdVector.size()) == aspvallRenHCRecognitionStruct_.numberOfClauses);
            assert(static_cast<ClauseIdT>(aspvallRenHCRecognitionStruct_.mappingFromOriginalClauseIdToFirstAspvallClauseIdVector.size()) == (ClauseIdT)1 + formulaRepresentationAbstractPtr->getNumberOfOriginalClauses());

            // Only for the initial formula
            if (initialFormula) {
                // Local auxiliary data structures for processSetAssignedLiteral
                l_processedOriginalClauseStack_.reserve(formulaRepresentationAbstractPtr->getNumberOfOriginalClauses());

                // Local auxiliary data structures for processIsRenHC
                l_literalNeedToBeProcessedVector_.reserve(aspvallRenHCRecognitionStruct_.numberOfVariables);

                this->initialize();
            }
        }
        #else
        AspvallRenHCRecognition(FormulaAspType&& formula, AspvallRenHCRecognitionAspStruct&& aspvallRenHCRecognitionStruct,
                                const ClauseIdVectorAspType& literalNumberOfOccurrences, FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                [[maybe_unused]] IgnorePureLiteralTypeEnum ignorePureLiteralType, [[maybe_unused]] bool initialFormula,
                                RenHCRecognitionStatisticsPtrType renHCRecognitionStatisticsPtr = nullptr)
            : RenHCRecognitionAbstract<VarT, LiteralT, ClauseIdT>(RenHCRecognitionTypeEnum::ASPVALL, formulaRepresentationAbstractPtr,
                                                                  renHCRecognitionStatisticsPtr),
              formula_(std::move(formula)),
              numberOfOriginalVariables_(static_cast<VarAspT>(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula())),
              contagiousOccurrenceList_(aspvallRenHCRecognitionStruct.numberOfClauses, literalNumberOfOccurrences),
              aspvallRenHCRecognitionStruct_(std::move(aspvallRenHCRecognitionStruct)),
              l_processedOriginalClauseVector_(formulaRepresentationAbstractPtr->getNumberOfOriginalClauses(), false),
              l_processedOriginalClauseStack_(),
              l_removedOccurrenceStackWithLevels_(aspvallRenHCRecognitionStruct_.formulaSize, numberOfOriginalVariables_),
              l_satisfiedClauseVector_(aspvallRenHCRecognitionStruct_.numberOfClauses, false),
              l_variableStateVector_(aspvallRenHCRecognitionStruct_.numberOfVariables), l_literalNeedToBeProcessedVector_(),
              l_satisfiedClauseStackWithLevels_(aspvallRenHCRecognitionStruct_.numberOfClauses, aspvallRenHCRecognitionStruct_.numberOfVariables),
              l_assignedVariableStackWithLevels_(aspvallRenHCRecognitionStruct_.numberOfVariables, aspvallRenHCRecognitionStruct_.numberOfVariables) {
            // Local auxiliary data structures for processSetAssignedLiteral
            l_processedOriginalClauseStack_.reserve(formulaRepresentationAbstractPtr->getNumberOfOriginalClauses());

            // Local auxiliary data structures for processIsRenHC
            l_literalNeedToBeProcessedVector_.reserve(aspvallRenHCRecognitionStruct_.numberOfVariables);

            this->initialize();
        }
        #endif

    private:
        FormulaAspType formula_;
        VarAspT numberOfOriginalVariables_;
        ContagiousOccurrenceListAspType contagiousOccurrenceList_;
        AspvallRenHCRecognitionAspStruct aspvallRenHCRecognitionStruct_;

        // Local auxiliary data structures for processSetAssignedLiteral
        BoolVectorType l_processedOriginalClauseVector_;      // bit map
        ClauseIdVectorType l_processedOriginalClauseStack_;   // used to clear the bit map

        // Local auxiliary data structure for processSetAssignedLiteral and processSetUnassignedLiteral
        OccurrencePairStackWithLevelsAspType l_removedOccurrenceStackWithLevels_;

        // Local auxiliary data structures for processIsRenHC
        BoolVectorType l_satisfiedClauseVector_;   // bit map
        VariableStateVectorAspType l_variableStateVector_;
        LiteralVectorAspType l_literalNeedToBeProcessedVector_;
        ClauseIdStackWithLevelsAspType l_satisfiedClauseStackWithLevels_;
        VariableStackWithLevelsAspType l_assignedVariableStackWithLevels_;

    private:
        void processInitialize() override;

        void processSetAssignedLiteral(const LiteralType& lit, const VariableSetType& currentComponentVariableSet,
                                       bool firstAssignment, bool lastAssignment) override;

        void processSetUnassignedLiteral(const LiteralType& lit) override;

        void processSetInactiveClause(ClauseIdT clauseId) override;

        void processSetActiveClause(ClauseIdT clauseId, const VariableSetType& currentComponentVariableSet) override;

        VariableSetOptionalType processIsRenHC(const ConnectedComponentStruct& connectedComponentStruct) override;

        /**
         * Assign the literal and do unit propagation (that is, boolean constraint propagation).
         * The local auxiliary data structures will be cleared accordingly if a contradiction occurs during unit propagation.
         * @param lit a literal
         * @param firstCall is it the first call (that is, not a recursive call)
         * @return true if the residual Aspvall formula is consistent after applying unit propagation. Otherwise, false is returned.
         */
        bool assignLiteralAndDoUnitPropagation(const LiteralAspType& lit, bool firstCall);

        /**
         * Remove the current level in l_satisfiedClauseStackWithLevels_
         */
        void removeCurrentLevelSatisfiedClauseStackWithLevels();

        /**
         * Remove the current level in l_assignedVariableStackWithLevels_
         */
        void removeCurrentLevelAssignedVariableStackWithLevels();

        /**
         * Assert: the returned index MUST be valid
         * @param aspvallClauseId an Aspvall clause identifier
         * @param firstIndex first or second index of the clause
         * @param assert check if the returned index is valid
         * @return the first/second index of the clause in the formula
         */
        FormulaSizeType getIndexOfClauseInFormula(ClauseIdAspT aspvallClauseId, bool firstIndex, bool assert = true) const;

    #ifndef NDEBUG
    private:
        mutable VariableStateVectorAspType d_variableStateVector_;

    private:
        void processPrintRenHCRecognitionDebug(std::ostream& out) const override;

        bool processVerifyRenHCDebug(const VariableSetType& switchedVariableSet) const override;
    #endif
    };
}   // namespace Hydra::RenHCRecognition::Aspvall

#include "./AspvallRenHCRecognition.ipp"
