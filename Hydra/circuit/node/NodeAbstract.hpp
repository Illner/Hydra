#pragma once

#include <cassert>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/partialAssignment/PartialAssignment.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"
#include "Hydra/other/type/arbitraryPrecisionInteger/ArbitraryPrecisionInteger.hpp"

#include "Hydra/circuit/node/enums/NodeTypeEnum.hpp"

// Forward declaration
namespace Hydra::Circuit {
    template <typename VarT2, typename LiteralT2>
    class Circuit;
}

namespace Hydra::Circuit::Node {

    using IdNodeType = unsigned long int;      // at least 32 bits
    using SizeNodeType = unsigned short int;   // at least 16 bits

    using LargeNumberType = Hydra::Other::LargeNumberType;
    using OriginalVarType = Hydra::Formula::OriginalVarType;
    using OriginalLiteralType = Hydra::Formula::OriginalLiteralType;

    /**
     * Node representation (abstract class)
     * Copy and move methods are disabled!
     * Exception:
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class NodeAbstract {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");

    public:
        using LiteralType = typename Formula::Literal<VarT, LiteralT>::LiteralType;
        using LiteralSetType = typename Formula::Literal<VarT, LiteralT>::LiteralSetType;
        using VariableSetType = typename Formula::Literal<VarT, LiteralT>::VariableSetType;
        using LiteralVectorType = typename Formula::Literal<VarT, LiteralT>::LiteralVectorType;
        using VariableVectorType = typename Formula::Literal<VarT, LiteralT>::VariableVectorType;
        using OriginalLiteralSetType = typename Formula::Literal<VarT, LiteralT>::OriginalLiteralSetType;
        using OriginalVariableSetType = typename Formula::Literal<VarT, LiteralT>::OriginalVariableSetType;
        using LiteralSortedVectorType = typename Formula::Literal<VarT, LiteralT>::LiteralSortedVectorType;
        using VariableSortedVectorType = typename Formula::Literal<VarT, LiteralT>::VariableSortedVectorType;
        using MappingFromVariableToLiteralType = typename Formula::Literal<VarT, LiteralT>::MappingFromVariableToLiteralType;
        using MappingFromVariableToVariableType = typename Formula::Literal<VarT, LiteralT>::MappingFromVariableToVariableType;
        using MappingFromVariableToOriginalVariableType = typename Formula::Literal<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;
        using MappingFromOriginalVariableToVariableType = typename Formula::Literal<VarT, LiteralT>::MappingFromOriginalVariableToVariableType;

    public:
        #if defined(BELLA_COMPILER)
        using NumberOfModelsType = Type::ArbitraryPrecisionInteger::MpzIntType;
        #elif defined(CARA_SOLVER)
        using NumberOfModelsType = Type::ArbitraryPrecisionInteger::MpzIntType;
        #endif

    public:
        using BoolVectorType = std::vector<bool>;
        using IdNodeVectorType = std::vector<IdNodeType>;
        using ChildPtrType = NodeAbstract<VarT, LiteralT>*;
        using ChildrenPtrVectorType = std::vector<ChildPtrType>;
        using ChildConstPtrType = const NodeAbstract<VarT, LiteralT>*;
        using ConsistencyCheckCacheType = Other::HashMap::MapType<IdNodeType, bool>;
        using CopySubcircuitCacheType = Other::HashMap::MapType<IdNodeType, IdNodeType>;
        using ModelCountingCacheType = Other::HashMap::MapType<IdNodeType, NumberOfModelsType>;
        using PartialAssignmentType = Formula::PartialAssignment::PartialAssignment<VarT, LiteralT>;

    protected:
        using MappingFromIdNodeToVariableSetType = Other::HashMap::MapType<IdNodeType, VariableSetType>;

    private:
        using LiteralSortedVectorOptionalType = std::optional<LiteralSortedVectorType>;
        using VariableSortedVectorOptionalType = std::optional<VariableSortedVectorType>;

    public:
        NodeAbstract(IdNodeType id, NodeTypeEnum nodeType, SizeNodeType size) noexcept
            : nodeType_(nodeType), id_(id), size_(size) { }

        NodeAbstract(const NodeAbstract&) = delete;
        NodeAbstract(NodeAbstract&&) noexcept = delete;

        NodeAbstract& operator=(const NodeAbstract&) = delete;
        NodeAbstract& operator=(NodeAbstract&&) noexcept = delete;

        virtual ~NodeAbstract() noexcept = default;

    private:
        NodeTypeEnum nodeType_;

    protected:
        IdNodeType id_;
        SizeNodeType size_;

    protected:
        virtual bool processIsCircuitSmooth(MappingFromIdNodeToVariableSetType& mappingFromIdNodeToVariableSet) const = 0;

        virtual bool processConsistencyCheck(const PartialAssignmentType& partialAssignment,
                                             const VariableSetType& forgottenVariableSet,
                                             ConsistencyCheckCacheType& cache) = 0;

        virtual NumberOfModelsType processModelCounting(const PartialAssignmentType& partialAssignment,
                                                        ModelCountingCacheType& cache) const = 0;

    public:
        virtual void printNode(std::ostream& out, const MappingFromVariableToOriginalVariableType& mapping) const = 0;

        /**
         * Copy the subcircuit rooted at the node
         * @param circuit the circuit containing the node
         * @param mapping a mapping from variables to literals
         * @param cache [auxiliary] a cache containing the processed nodes
         * @param isVariableToLiteralMapping a variable to literal mapping vs a variable to variable mapping
         * @return the identifier of the created node / root
         * @throw NodeTypeDoesNotSupportCopySubcircuitOperationException if any node (type) in the subcircuit does not support the copy subcircuit method
         */
        virtual IdNodeType copySubcircuit(Circuit<VarT, LiteralT>* circuit, const MappingFromVariableToLiteralType& mapping,
                                          CopySubcircuitCacheType& cache, bool isVariableToLiteralMapping) = 0;

        /**
         * Getter
         * @return the identifier of the node
         */
        IdNodeType getId() const noexcept;

        /**
         * Getter
         * @return the size of the node
         */
        SizeNodeType getSize() const noexcept;

        /**
         * Getter
         * @return the type of the node
         */
        NodeTypeEnum getNodeType() const noexcept;

        /**
         * Check if the (sub)circuit is smooth
         * Time complexity: linear with respect to the size of the (sub)circuit
         * @param numberOfNodes the number of nodes contained in the (sub)circuit
         * @return true if the (sub)circuit is smooth. Otherwise, false is returned.
         */
        bool isCircuitSmooth(IdNodeType numberOfNodes) const;
        bool isCircuitSmooth(MappingFromIdNodeToVariableSetType& mappingFromIdNodeToVariableSet) const;

        /**
         * Consistency check
         * Time complexity: linear with respect to the size of the (sub)circuit
         * @param partialAssignment a partial assignment
         * @param forgottenVariableSet a set of forgotten variables (can be empty)
         * @param cache [auxiliary] should be initialized empty
         * @return true if the formula is consistent. Otherwise, false is returned.
         */
        bool consistencyCheck(const PartialAssignmentType& partialAssignment,
                              const VariableSetType& forgottenVariableSet,
                              ConsistencyCheckCacheType& cache);

        /**
         * Model counting
         * Time complexity: linear with respect to the size of the (sub)circuit
         * @param partialAssignment a partial assignment
         * @param cache [auxiliary] should be initialized empty
         */
        void modelCounting(const PartialAssignmentType& partialAssignment,
                           ModelCountingCacheType& cache) const;

    public:
        /**
         * ostream << Node
         */
        friend std::ostream& operator<<(std::ostream& out, const NodeAbstract& node) {
            node.printNode(out, {});
            return out;
        }

        /**
         * Node_1 == Node_2
         * Note: just identifiers are compared
         */
        friend bool operator==(const NodeAbstract& node1, const NodeAbstract& node2) {
            return node1.id_ == node2.id_;
        }

        /**
         * Node_1 != Node_2
         * Note: just identifiers are compared
         */
        friend bool operator!=(const NodeAbstract& node1, const NodeAbstract& node2) {
            return node1.id_ != node2.id_;
        }

    #ifndef NDEBUG
    private:
        mutable LiteralSortedVectorOptionalType d_sortedLiteralsInCircuit_;
        mutable VariableSortedVectorOptionalType d_sortedVariablesInCircuit_;

    protected:
        virtual LiteralSortedVectorType computeAndReturnSortedLiteralsInCircuitDebug() const = 0;
        virtual VariableSortedVectorType computeAndReturnSortedVariablesInCircuitDebug() const = 0;

    public:
        /**
         * Print the literals in the (sub)circuit
         * Note: prefix
         */
        void printLiteralsInCircuitDebug(std::ostream& out) const;

        /**
         * Print the variables in the (sub)circuit
         * Note: prefix
         */
        void printVariablesInCircuitDebug(std::ostream& out) const;

        virtual void printNodeDebug(std::ostream& out);

        /**
         * @return a sorted vector containing all literals in the (sub)circuit
         */
        const LiteralSortedVectorType& getSortedLiteralsInCircuitDebug() const;

        /**
         * @return a sorted vector containing all variables in the (sub)circuit
         */
        const VariableSortedVectorType& getSortedVariablesInCircuitDebug() const;

        /**
         * Add all literals in the (sub)circuit to the set (literalsInCircuit)
         * @param literalsInCircuit [output] a set of literals
         */
        void insertLiteralsInCircuitToSetDebug(LiteralSetType& literalsInCircuit) const;

        /**
         * Add all variables in the (sub)circuit to the set (variablesInCircuit)
         * @param variablesInCircuit [output] a set of variables
         */
        void insertVariablesInCircuitToSetDebug(VariableSetType& variablesInCircuit) const;
    #endif
    };
}   // namespace Hydra::Circuit::Node

#include "./NodeAbstract.ipp"
