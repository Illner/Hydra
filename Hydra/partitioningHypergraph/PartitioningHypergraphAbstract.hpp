#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/container/computeConnectedComponents/ComputeConnectedComponents.hpp"
#include "Hydra/other/container/reusableVector/ReusableVector.hpp"
#include "Hydra/other/container/vectorMap/VectorMap.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"
#include "Hydra/satSolver/EquivalencePreprocessingStructure.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/partitioningHypergraph/exceptions/PartitioningHypergraphException.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/partitioningHypergraph/enums/PartitioningHypergraphSoftwareEnum.hpp"
#include "Hydra/partitioningHypergraph/enums/VertexWeightTypeEnum.hpp"

#include "Hydra/partitioningHypergraph/PartitioningHypergraphAbstract.hxx"

namespace Hydra::PartitioningHypergraph {

    using FormulaSizeType = Hydra::Formula::Representation::FormulaSizeType;

    /**
     * Partitioning hypergraph (abstract class)
     * Copy and move methods are disabled!
     * Exception:
     *      UnexpectedArgumentException (debug)
     *      SomethingCannotBeSavedAsIntException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class PartitioningHypergraphAbstract {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");
        static_assert(Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::isValidClauseT::value, "Invalid ClauseIdT type!");

    private:
        using VectorSetType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VectorSetType;
        using ConnectedComponentType = typename Container::ComputeConnectedComponents::ComputeConnectedComponents<VarT, LiteralT>::ConnectedComponentType;
        using ClauseIdReusableVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdReusableVectorType;

    private:
        using ComputeConnectedComponentsType = Container::ComputeConnectedComponents::ComputeConnectedComponents<VarT, LiteralT>;

    private:
        using ConnectedComponentStruct = typename Container::ComputeConnectedComponents::ComputeConnectedComponents<VarT, LiteralT>::ConnectedComponentStruct;

    protected:
        using PartitionNumberType = int;
        using PartitionNumberVectorMapType = Container::VectorMap::VectorMap<PartitionNumberType>;

    public:
        using LiteralType = typename Formula::Literal<VarT, LiteralT>::LiteralType;
        using VariableSetType = typename Formula::Literal<VarT, LiteralT>::VariableSetType;
        using VariableVectorType = typename Formula::Literal<VarT, LiteralT>::VariableVectorType;
        using VariableSortedVectorType = typename Formula::Literal<VarT, LiteralT>::VariableSortedVectorType;
        using MappingFromVariableToVariableType = typename Formula::Literal<VarT, LiteralT>::MappingFromVariableToVariableType;
        using PartitioningHypergraphStatisticsPtrType = typename PartitioningHypergraphStatistics::PartitioningHypergraphStatisticsPtrType;
        using ClauseIdSetType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdSetType;
        using VertexWeightType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightType;
        using ClauseIdVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdVectorType;
        using VariableVectorMapType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorMapType;
        using VertexWeightVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::VertexWeightVectorType;
        using ClauseIdSortedVectorType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseIdSortedVectorType;

    public:
        using PartvecType = std::vector<PartitionNumberType>;
        using VertexWeightVectorPtrType = VertexWeightVectorType*;
        using OccurrenceListVectorType = std::vector<ClauseIdVectorType>;
        using VertexWeightVectorConstPtrType = const VertexWeightVectorType*;
        using PartitionNumberVectorMapPtrType = PartitionNumberVectorMapType*;
        using EquivalenceStructureVectorType = std::vector<VariableVectorType>;
        using ClauseIdVectorMapType = Container::VectorMap::VectorMap<ClauseIdT>;
        using VariableReusableVectorType = Container::ReusableVector::ReusableVector<VarT>;
        using FormulaRepresentationAbstractPtrType = const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;

    public:
        using EquivalencePreprocessingStruct = typename SatSolver::EquivalencePreprocessingStruct<VarT, LiteralT>;

    public:
        struct OccurrenceListStruct {
        public:
            OccurrenceListVectorType occurrenceListVector;
            ClauseIdVectorMapType fromClauseIdToIndexVectorMap;
            VariableReusableVectorType variableOrderReusableVector;
            VariableReusableVectorType variablePlusSingletonVariableReusableVector;   // variableOrderReusableVector + singleton variables

            FormulaSizeType occurrenceListSize = 0;
            ClauseIdT numberOfDifferentClausesInOccurrenceList = 0;
        };

        struct ModulePointersStruct {
        public:
            // Vertex weights
            VertexWeightVectorPtrType vertexWeightVectorPtr = nullptr;
            VertexWeightVectorConstPtrType clauseVertexWeightVectorPtr = nullptr;

            // Pre-assigned partition numbers
            PartitionNumberVectorMapPtrType partitionNumberVectorMapPtr = nullptr;
        };

    public:
        PartitioningHypergraphAbstract(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                       bool allowEmptyHypergraphCut, bool allowSingletonHyperedge,
                                       PartitioningHypergraphSoftwareEnum partitioningHypergraphSoftware, IgnorePureLiteralTypeEnum ignorePureLiteralType,
                                       VertexWeightTypeEnum vertexWeightType, PartitioningHypergraphStatisticsPtrType partitioningHypergraphStatisticsPtr,
                                       ModulePointersStruct modulePointersStruct = ModulePointersStruct())
            : module_(modulePointersStruct.vertexWeightVectorPtr), wrapper_(partitioningHypergraphSoftware == PartitioningHypergraphSoftwareEnum::WRAPPER),
              allowEmptyHypergraphCut_(allowEmptyHypergraphCut), allowSingletonHyperedge_(allowSingletonHyperedge), vertexWeightType_(vertexWeightType),
              ignorePureLiteralType_(ignorePureLiteralType), partitioningHypergraphSoftware_(partitioningHypergraphSoftware), modulePointersStruct_(modulePointersStruct),
              computeConnectedComponents_(module_ ? 0 : formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula()),
              l_occurrenceListStruct_(), l_equivalenceVectorMap_equivalenceStruct_(),
              l_variableOrderReusableVector_equivalenceStruct_(module_ ? 0 : formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula()),
              l_equivalenceStructureVector_equivalenceStruct_(), l_firstCall_createEquivalenceStruct_(true),
              l_clauseIdReusableVector_createOccurrenceListStruct_(module_ ? 0 : formulaRepresentationAbstractPtr->getNumberOfOriginalClauses()),
              l_clauseAddedToOccurrenceListVectorSet_createOccurrenceListStruct_(module_ ? 0 : formulaRepresentationAbstractPtr->getNumberOfOriginalClauses()),
              l_clauseThatVariableSubsumesSomeClauseVectorSet_createOccurrenceListStruct_(module_ ? 0 : formulaRepresentationAbstractPtr->getNumberOfOriginalClauses()),
              partvec_(), vertexWeightVector_(), partitionNumberVectorMap_(module_ ? 0 : 0, (PartitionNumberType)-1),   // TODO change the capacity when implemented
              clauseVertexWeightVector_((isVertexWeightUsed(vertexWeightType_) && !module_) ? formulaRepresentationAbstractPtr->getNumberOfOriginalClauses() : 0, 0),
              formulaRepresentationAbstractPtr_(formulaRepresentationAbstractPtr), partitioningHypergraphStatisticsPtr_(partitioningHypergraphStatisticsPtr) {
            assert(!module_ || !wrapper_);
            assert((modulePointersStruct.vertexWeightVectorPtr && modulePointersStruct.clauseVertexWeightVectorPtr && modulePointersStruct.partitionNumberVectorMapPtr) ||
                   (!modulePointersStruct.vertexWeightVectorPtr && !modulePointersStruct.clauseVertexWeightVectorPtr && !modulePointersStruct.partitionNumberVectorMapPtr));

            // The variables cannot be saved as int
            if (!Other::unsignedValueCanBeSavedAsInt<VarT>(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula()))
                throw Exception::SomethingCannotBeSavedAsIntException("variables", formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());

            // The clauses cannot be saved as int
            if (!Other::unsignedValueCanBeSavedAsInt<ClauseIdT>(formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses()))
                throw Exception::SomethingCannotBeSavedAsIntException("clauses", formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses());

            // The formula size cannot be saved as int
            if (!Other::unsignedValueCanBeSavedAsInt<FormulaSizeType>(formulaRepresentationAbstractPtr_->getOriginalFormulaSize()))
                throw Exception::SomethingCannotBeSavedAsIntException("formula size", formulaRepresentationAbstractPtr_->getOriginalFormulaSize());

            if (!wrapper_)
                partvec_.reserve(formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses());

            if (isVertexWeightUsed(vertexWeightType_) && !module_)
                vertexWeightVector_.reserve(formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses());

            // Initialize the occurrence list structure
            if (!module_) {
                l_occurrenceListStruct_.fromClauseIdToIndexVectorMap = ClauseIdVectorMapType(formulaRepresentationAbstractPtr_->getNumberOfOriginalClauses(), 0);
                l_occurrenceListStruct_.variableOrderReusableVector = VariableReusableVectorType(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());
                l_occurrenceListStruct_.variablePlusSingletonVariableReusableVector = VariableReusableVectorType(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula());
                l_occurrenceListStruct_.occurrenceListVector = OccurrenceListVectorType(formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormula(), ClauseIdVectorType());

                // Reserve the occurrence list
                for (ClauseIdVectorType& clauseIdVector : l_occurrenceListStruct_.occurrenceListVector)
                    clauseIdVector.reserve(S_ESTIMATED_NUMBER_OF_CLAUSES_FOR_OCCURRENCE_LIST_);
            }
        }

        PartitioningHypergraphAbstract(const PartitioningHypergraphAbstract&) = delete;
        PartitioningHypergraphAbstract(PartitioningHypergraphAbstract&&) noexcept = delete;

        PartitioningHypergraphAbstract& operator=(const PartitioningHypergraphAbstract&) = delete;
        PartitioningHypergraphAbstract& operator=(PartitioningHypergraphAbstract&&) noexcept = delete;

        virtual ~PartitioningHypergraphAbstract() noexcept = default;

    private:
        bool module_;
        bool wrapper_;

        bool allowEmptyHypergraphCut_;
        bool allowSingletonHyperedge_;
        VertexWeightTypeEnum vertexWeightType_;
        IgnorePureLiteralTypeEnum ignorePureLiteralType_;
        PartitioningHypergraphSoftwareEnum partitioningHypergraphSoftware_;

        ModulePointersStruct modulePointersStruct_;

        mutable ComputeConnectedComponentsType computeConnectedComponents_;

        // Local auxiliary data structures - occurrence list structure
        mutable OccurrenceListStruct l_occurrenceListStruct_;

        // Local auxiliary data structures - equivalence structure
        mutable VariableVectorMapType l_equivalenceVectorMap_equivalenceStruct_;   // key: dominated variable, value: representant
        mutable VariableReusableVectorType l_variableOrderReusableVector_equivalenceStruct_;
        mutable EquivalenceStructureVectorType l_equivalenceStructureVector_equivalenceStruct_;

        // Local auxiliary data structures for createEquivalenceStruct
        mutable bool l_firstCall_createEquivalenceStruct_;

        // Local auxiliary data structures for createOccurrenceListStruct
        mutable ClauseIdReusableVectorType l_clauseIdReusableVector_createOccurrenceListStruct_;
        mutable VectorSetType l_clauseAddedToOccurrenceListVectorSet_createOccurrenceListStruct_;
        mutable VectorSetType l_clauseThatVariableSubsumesSomeClauseVectorSet_createOccurrenceListStruct_;

        inline static constexpr ClauseIdT S_ESTIMATED_NUMBER_OF_CLAUSES_FOR_OCCURRENCE_LIST_ = 10;
        inline static constexpr VarT S_ESTIMATED_NUMBER_OF_VARIABLES_FOR_EQUIVALENCE_STRUCTURE_ = 10;

    protected:
        PartvecType partvec_;
        VertexWeightVectorType vertexWeightVector_;
        PartitionNumberVectorMapType partitionNumberVectorMap_;
        mutable VertexWeightVectorType clauseVertexWeightVector_;
        FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr_;

        PartitioningHypergraphStatisticsPtrType partitioningHypergraphStatisticsPtr_;

    private:
        /**
         * Getter
         * Note: if this is a module, the member of the wrapper is returned
         * @return clauseVertexWeightVector_
         */
        const VertexWeightVectorType& getClauseVertexWeightVector() const noexcept;

        /**
         * Getter
         * Note: if this is a module, the member of the wrapper is returned
         * @return vertexWeightVector_
         */
        VertexWeightVectorType& getVertexWeightVector() noexcept;

        /**
         * Getter
         * Note: if this is a module, the member of the wrapper is returned
         * @return partitionNumberVectorMap_
         */
        PartitionNumberVectorMapType& getPartitionNumberVectorMap() noexcept;

    protected:
        virtual VariableSetType computeCut(const OccurrenceListStruct& occurrenceListStruct) = 0;

    public:
        /**
         * Create an equivalence structure that is used for the equivalence simplification method
         * Local auxiliary data structures:
         *      l_firstCall_createEquivalenceStruct_
         *      l_equivalenceVectorMap_equivalenceStruct_
         *      l_equivalenceStructureVector_equivalenceStruct_
         *      l_variableOrderReusableVector_equivalenceStruct_
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param equivalencePreprocessingStruct an equivalence preprocessing structure
         */
        void createEquivalenceStruct(const VariableSetType& currentComponentVariableSet,
                                     const EquivalencePreprocessingStruct& equivalencePreprocessingStruct) const;

        /**
         * Create an occurrence list structure that is used for creating xpins and pins.
         * For every variable, there is stored a vector of (mapped) clauses containing that variable.
         * If equivalenceVectorMap is not empty, the equivalence simplification method is applied.
         * The occurrence list does not contain the dominated variables (if the equivalence simplification method is applied).
         * The occurrence list does not contain the pure variables (depending on ignorePureLiteralType_).
         * Assert: if the equivalence simplification method is applied, every variable MUST be self-contained in its dominated variable vector in equivalenceStructureVector
         * Local auxiliary data structures:
         *      l_occurrenceListStruct_
         *      l_clauseIdReusableVector_createOccurrenceListStruct_
         *      l_clauseAddedToOccurrenceListVectorSet_createOccurrenceListStruct_
         *      l_clauseThatVariableSubsumesSomeClauseVectorSet_createOccurrenceListStruct_
         * @param variableOrderReusableVector a variable order
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param equivalenceVectorMap a vector map that maps every dominated variable to its representant (used by the equivalence simplification method)
         * @param equivalenceStructureVector for every variable, it stores a vector of variables that are dominated by that variable (used by the equivalence simplification method)
         */
        void createOccurrenceListStruct(const VariableReusableVectorType& variableOrderReusableVector,
                                        const VariableSetType& currentComponentVariableSet,
                                        const VariableVectorMapType& equivalenceVectorMap = VariableVectorMapType(),
                                        const EquivalenceStructureVectorType& equivalenceStructureVector = EquivalenceStructureVectorType()) const;

        /**
         * Fill the xpins and pins based on the occurrence list structure
         * @param occurrenceListStruct an occurrence list structure
         * @param xpins an xpin vector that will be filled
         * @param pins a pin vector that will be filled
         */
        template <typename XpinT, typename PinT>
        void fillXpinsAndPins(const OccurrenceListStruct& occurrenceListStruct, std::vector<XpinT>& xpins, std::vector<PinT>& pins);

        /**
         * Create a vector map from (some) clause indices to pre-assigned partition numbers
         * Note: an empty vector map is returned if no clause is pre-assigned
         * @param occurrenceListStruct an occurrence list structure
         * @param numberOfPartitions the number of partitions
         * @return a vector map from clause indices to partition numbers
         */
        const PartitionNumberVectorMapType& createPreassignmentOfClauseIndices(const OccurrenceListStruct& occurrenceListStruct,
                                                                               PartitionNumberType numberOfPartitions);

        /**
         * Create a vector of vertex weights based on the occurrence list
         * Assert: every vertex weight MUST be greater than zero
         * Note: if vector weights are not supported, an empty vector is returned
         * @param occurrenceListStruct an occurrence list structure
         * @return a vector of vertex weights
         */
        VertexWeightVectorType& createVertexWeightVector(const OccurrenceListStruct& occurrenceListStruct);

        /**
         * Extract the cut based on occurrenceListStruct and partvec
         * @param occurrenceListStruct an occurrence list structure
         * @param partvec for each clause, it stores its partition number
         * @return the cut
         */
        VariableSetType extractCut(const OccurrenceListStruct& occurrenceListStruct, const PartvecType& partvec) const;

        /**
         * Compute a cut for the current formula
         * Note: the equivalence simplification method is NOT applied
         * Local auxiliary data structures:
         *      l_occurrenceListStruct_
         *      l_variableOrderReusableVector_equivalenceStruct_
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param validCut is the returned cut valid
         * @return the set of variables representing a cut
         */
        VariableSetType computeCut(const VariableSetType& currentComponentVariableSet);
        VariableSetType computeCut(const VariableSetType& currentComponentVariableSet, bool& validCut);

        /**
         * Compute a cut for the current formula
         * Note: the equivalence simplification method is applied
         * Local auxiliary data structures:
         *      l_occurrenceListStruct_
         *      l_equivalenceVectorMap_equivalenceStruct_
         *      l_equivalenceStructureVector_equivalenceStruct_
         *      l_variableOrderReusableVector_equivalenceStruct_
         * @param currentComponentVariableSet a set of variables appearing in the current component
         * @param validCut is the returned cut valid
         * @param equivalencePreprocessingStruct an equivalence preprocessing structure
         * @return the set of variables representing a cut
         */
        VariableSetType computeCut(const VariableSetType& currentComponentVariableSet,
                                   const EquivalencePreprocessingStruct& equivalencePreprocessingStruct);
        VariableSetType computeCut(const VariableSetType& currentComponentVariableSet, bool& validCut,
                                   const EquivalencePreprocessingStruct& equivalencePreprocessingStruct);

    #ifndef NDEBUG
    public:
        void printVertexWeightVectorDebug(std::ostream& out) const;

        void printPartitioningHypergraphDebug(std::ostream& out, bool printCurrentFormula = false) const;

    protected:
        virtual void processPrintPartitioningHypergraphDebug(std::ostream& out) const = 0;
    #endif

    #if defined(TEST)
    public:
        /**
         * Getter
         * @return l_equivalenceVectorMap_equivalenceStruct_
         */
        VariableVectorMapType& getEquivalenceVectorMap() const noexcept;

        /**
         * Getter
         * @return l_variableOrderReusableVector_equivalenceStruct_
         */
        VariableReusableVectorType& getVariableOrderReusableVector() const noexcept;

        /**
         * Getter
         * @return l_equivalenceStructureVector_equivalenceStruct_
         */
        EquivalenceStructureVectorType& getEquivalenceStructureVector() const noexcept;

        /**
         * Getter
         * @return l_occurrenceListStruct_
         */
        OccurrenceListStruct& getOccurrenceListStruct() const noexcept;
    #endif
    };
}   // namespace Hydra::PartitioningHypergraph

#include "./PartitioningHypergraphAbstract.ipp"
