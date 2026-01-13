#pragma once

#include <cassert>

#include "Hydra/circuit/node/leafNode/LeafAbstract.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/partialAssignment/PartialAssignment.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#ifndef NDEBUG
    #include <sstream>
    #include <vector>

    #include "Hydra/compiler/exceptions/CompilerException.hpp"
#endif

#define LITERAL_LEAF_SIZE 0

namespace Hydra::Circuit::Node {

    inline constexpr char LITERAL_LEAF = 'L';

    /**
     * Literal leaf representation (final class)
     * Exceptions:
     *      VariableDoesNotExistInMappingException (debug)
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class LiteralLeaf final : public LeafAbstract<VarT, LiteralT> {
    private:
        using LiteralType = typename NodeAbstract<VarT, LiteralT>::LiteralType;
        using BoolVectorType = typename NodeAbstract<VarT, LiteralT>::BoolVectorType;
        using VariableSetType = typename NodeAbstract<VarT, LiteralT>::VariableSetType;
        using NumberOfModelsType = typename NodeAbstract<VarT, LiteralT>::NumberOfModelsType;
        using PartialAssignmentType = typename NodeAbstract<VarT, LiteralT>::PartialAssignmentType;
        using ModelCountingCacheType = typename NodeAbstract<VarT, LiteralT>::ModelCountingCacheType;
        using LiteralSortedVectorType = typename NodeAbstract<VarT, LiteralT>::LiteralSortedVectorType;
        using CopySubcircuitCacheType = typename NodeAbstract<VarT, LiteralT>::CopySubcircuitCacheType;
        using VariableSortedVectorType = typename NodeAbstract<VarT, LiteralT>::VariableSortedVectorType;
        using ConsistencyCheckCacheType = typename NodeAbstract<VarT, LiteralT>::ConsistencyCheckCacheType;
        using MappingFromVariableToLiteralType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToLiteralType;
        using MappingFromIdNodeToVariableSetType = typename NodeAbstract<VarT, LiteralT>::MappingFromIdNodeToVariableSetType;
        using MappingFromVariableToOriginalVariableType = typename NodeAbstract<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;

    public:
        LiteralLeaf(IdNodeType id, const LiteralType& literal) noexcept
            : LeafAbstract<VarT, LiteralT>(id, NodeTypeEnum::LITERAL_LEAF, LITERAL_LEAF_SIZE), literal_(literal) { }

        LiteralLeaf(IdNodeType id, LiteralType&& literal) noexcept
            : LeafAbstract<VarT, LiteralT>(id, NodeTypeEnum::LITERAL_LEAF, LITERAL_LEAF_SIZE), literal_(std::move(literal)) { }

    private:
        LiteralType literal_;

    private:
        void setUsedVariables(BoolVectorType& usedVariableVector, VarT& numberOfUsedVariables) const override;

        bool processIsCircuitSmooth(MappingFromIdNodeToVariableSetType& mappingFromIdNodeToVariableSet) const override;

        bool processConsistencyCheck(const PartialAssignmentType& partialAssignment,
                                     const VariableSetType& forgottenVariableSet,
                                     ConsistencyCheckCacheType& cache) override;

        NumberOfModelsType processModelCounting(const PartialAssignmentType& partialAssignment,
                                                ModelCountingCacheType& cache) const override;

        IdNodeType copySubcircuit(Circuit<VarT, LiteralT>* circuit, const MappingFromVariableToLiteralType& mapping,
                                  CopySubcircuitCacheType& cache, bool isVariableToLiteralMapping) override;

    public:
        void printNode(std::ostream& out, const MappingFromVariableToOriginalVariableType& mapping) const override;

        /**
         * Getter
         * @return the leaf's literal
         */
        LiteralType getLiteral() const noexcept;

        /**
         * Create a new mapped literal
         * Note: used for the copy subcircuit operation
         * @param mapping a mapping from variables to literals
         * @return a mapped literal
         * @throw VariableDoesNotExistInMappingException (debug) if the variable does not exist in the mapping
         */
        LiteralType createMappedLiteral(const MappingFromVariableToLiteralType& mapping) const;

        /**
         * Getter
         * @return the leaf's variable (|literal|)
         */
        VarT getVariable() const noexcept;

    #ifndef NDEBUG
    private:
        LiteralSortedVectorType computeAndReturnSortedLiteralsInCircuitDebug() const override;

        VariableSortedVectorType computeAndReturnSortedVariablesInCircuitDebug() const override;

    public:
        void printNodeDebug(std::ostream& out) override;
    #endif
    };
}   // namespace Hydra::Circuit::Node

#include "./LiteralLeaf.ipp"
