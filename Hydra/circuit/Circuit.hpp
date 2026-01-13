#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include "Hydra/circuit/node/NodeAbstract.hpp"
#include "Hydra/circuit/node/innerNode/AndInnerNode.hpp"
#include "Hydra/circuit/node/innerNode/BinaryOrInnerNode.hpp"
#include "Hydra/circuit/node/innerNode/InnerNodeAbstract.hpp"
#include "Hydra/circuit/node/innerNode/OrInnerNode.hpp"
#include "Hydra/circuit/node/leafNode/ConstantLeaf.hpp"
#include "Hydra/circuit/node/leafNode/LeafAbstract.hpp"
#include "Hydra/circuit/node/leafNode/LiteralLeaf.hpp"
#include "Hydra/circuit/node/leafNode/formulaLeaf/Clause.hpp"
#include "Hydra/circuit/node/leafNode/formulaLeaf/FormulaLeafAbstract.hpp"
#include "Hydra/circuit/node/leafNode/formulaLeaf/KromCLeaf.hpp"
#include "Hydra/circuit/node/leafNode/formulaLeaf/RenHCLeaf.hpp"
#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"
#include "Hydra/other/hashMap/HashMap.hpp"

#include "Hydra/circuit/exceptions/CircuitException.hpp"
#include "Hydra/circuit/node/exceptions/NodeException.hpp"
#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/circuit/enums/CircuitTypeEnum.hpp"
#include "Hydra/circuit/node/enums/DecomposabilityTypeEnum.hpp"
#include "Hydra/circuit/node/enums/NodeTypeEnum.hpp"

#include "Hydra/circuit/Circuit.hxx"

#ifndef NDEBUG
    #include <sstream>
#endif

namespace Hydra::Circuit {

    using IdNodeType = Hydra::Circuit::Node::IdNodeType;
    using SizeNodeType = Hydra::Circuit::Node::SizeNodeType;
    using LargeNumberType = Hydra::Circuit::Node::LargeNumberType;

    using OriginalVarType = Hydra::Formula::OriginalVarType;
    using OriginalLiteralType = Hydra::Formula::OriginalLiteralType;

    inline constexpr char COMMENT = 'c';
    inline constexpr std::string_view NNF_HEADER_STRING = "nnf";

    // Forward declaration
    template <typename VarT2, typename LiteralT2>
    class Circuit;

    namespace Parser {
        template <typename VarT2, typename LiteralT2, std::input_iterator InputIterator2>
        Circuit<VarT2, LiteralT2> parseCircuit(InputIterator2& begin, const InputIterator2& end,
                                               IdNodeType numberOfNodes, LargeNumberType numberOfEdges,
                                               VarT2 numberOfVariables, LargeNumberType size, unsigned int& line);
    }

    /**
     * Circuit representation
     * Copy methods are disabled! Move methods (default) are allowed!
     * Invariant: variables MUST be indexed from 1 to N
     * Exception:
     *      CircuitException
     *      RootIsNotSetException
     *      AttemptToResetRootException
     *      IdentifierDoesNotExistException
     *      SmoothnessIsNotSupportedException
     *      MappingIsNotBijectiveException (debug)
     *      CircuitTypeDoesNotSupportQueryException
     *      SomethingCannotBeSavedAsStdSizeTException
     *      VariableDoesNotExistInMappingException (debug)
     *      InnerNodeDoesNotSatisfyPropertyException (debug)
     *      ModelCountingIsNotSupportedWithoutSmoothnessException
     *      NodeTypeDoesNotSupportCopySubcircuitOperationException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     */
    template <typename VarT, typename LiteralT>
    class Circuit {
        static_assert(Formula::Literal<VarT, LiteralT>::isValidVarT::value, "Invalid VarT type!");
        static_assert(Formula::Literal<VarT, LiteralT>::isValidLiteralT::value, "Invalid LiteralT type!");

    public:
        using LiteralType = typename Node::NodeAbstract<VarT, LiteralT>::LiteralType;
        using ClauseType = typename Node::FormulaLeafAbstract<VarT, LiteralT>::ClauseType;
        using BoolVectorType = typename Node::NodeAbstract<VarT, LiteralT>::BoolVectorType;
        using LiteralSetType = typename Node::NodeAbstract<VarT, LiteralT>::LiteralSetType;
        using FormulaType = typename Node::FormulaLeafAbstract<VarT, LiteralT>::FormulaType;
        using VariableSetType = typename Node::NodeAbstract<VarT, LiteralT>::VariableSetType;
        using CircuitStatisticsPtrType = typename CircuitStatistics::CircuitStatisticsPtrType;
        using LiteralVectorType = typename Node::NodeAbstract<VarT, LiteralT>::LiteralVectorType;
        using ClauseSizeType = typename Node::FormulaLeafAbstract<VarT, LiteralT>::ClauseSizeType;
        using VariableVectorType = typename Node::NodeAbstract<VarT, LiteralT>::VariableVectorType;
        using NumberOfModelsType = typename Node::NodeAbstract<VarT, LiteralT>::NumberOfModelsType;
        using PartialAssignmentType = typename Node::NodeAbstract<VarT, LiteralT>::PartialAssignmentType;
        using ModelCountingCacheType = typename Node::NodeAbstract<VarT, LiteralT>::ModelCountingCacheType;
        using OriginalLiteralSetType = typename Node::NodeAbstract<VarT, LiteralT>::OriginalLiteralSetType;
        using OriginalVariableSetType = typename Node::NodeAbstract<VarT, LiteralT>::OriginalVariableSetType;
        using LiteralSortedVectorType = typename Node::NodeAbstract<VarT, LiteralT>::LiteralSortedVectorType;
        using CopySubcircuitCacheType = typename Node::NodeAbstract<VarT, LiteralT>::CopySubcircuitCacheType;
        using VariableSortedVectorType = typename Node::NodeAbstract<VarT, LiteralT>::VariableSortedVectorType;
        using ConsistencyCheckCacheType = typename Node::NodeAbstract<VarT, LiteralT>::ConsistencyCheckCacheType;
        using MappingFromVariableToLiteralType = typename Node::NodeAbstract<VarT, LiteralT>::MappingFromVariableToLiteralType;
        using MappingFromVariableToVariableType = typename Node::NodeAbstract<VarT, LiteralT>::MappingFromVariableToVariableType;
        using MappingFromVariableToOriginalVariableType = typename Node::NodeAbstract<VarT, LiteralT>::MappingFromVariableToOriginalVariableType;
        using MappingFromOriginalVariableToVariableType = typename Node::NodeAbstract<VarT, LiteralT>::MappingFromOriginalVariableToVariableType;

    private:
        using NodeTypeEnum = Node::NodeTypeEnum;
        using DecomposabilityTypeEnum = Node::DecomposabilityTypeEnum;

    private:
        using KeyLiteralType = std::basic_string<LiteralT>;
        using KromCLeafType = Node::KromCLeaf<VarT, LiteralT>;
        using RenHCLeafType = Node::RenHCLeaf<VarT, LiteralT>;
        using OrInnerNodeType = Node::OrInnerNode<VarT, LiteralT>;
        using LiteralLeafType = Node::LiteralLeaf<VarT, LiteralT>;
        using LeafAbstractType = Node::LeafAbstract<VarT, LiteralT>;
        using ConstantLeafType = Node::ConstantLeaf<VarT, LiteralT>;
        using AndInnerNodeType = Node::AndInnerNode<VarT, LiteralT>;
        using NodeAbstractType = Node::NodeAbstract<VarT, LiteralT>;
        using InnerNodeAbstractType = Node::InnerNodeAbstract<VarT, LiteralT>;
        using BinaryOrInnerNodeType = Node::BinaryOrInnerNode<VarT, LiteralT>;
        using ConstantAndLiteralLeafUniqueNodeCacheType = std::vector<LiteralT>;                    // [S_FALSE_ID_, S_TRUE_ID_, x_1_ID, -x_1_ID, ...]
        using TrivialOrInnerNodeUniqueNodeCacheType = Other::HashMap::MapType<VarT, IdNodeType>;    // key: variable, value: ID
        using InnerNodeUniqueNodeCacheType = Other::HashMap::MapType<KeyLiteralType, IdNodeType>;   // key: string<literal>, value: ID
        using NodeAbstractPtrType = NodeAbstractType*;
        using NodeAbstractPtrVectorType = std::vector<NodeAbstractType*>;
        using NodeUniquePtrVectorType = std::vector<std::unique_ptr<NodeAbstractType>>;

    public:
        using RootType = std::optional<IdNodeType>;
        using IdNodeVectorType = std::vector<IdNodeType>;
        using NodeTypeEnumSortedVectorType = std::vector<NodeTypeEnum>;
        using NodeTypeCounterType = Other::HashMap::MapType<NodeTypeEnum, IdNodeType>;

    public:
        // Used for compiling a circuit
        Circuit(VarT numberOfVariables, bool smooth,
                MappingFromVariableToOriginalVariableType&& mappingFromVariableToOriginalVariable = {},
                MappingFromOriginalVariableToVariableType&& mappingFromOriginalVariableToVariable = {},
                CircuitStatisticsPtrType circuitStatisticsPtr = nullptr)
            : smooth_(smooth), root_(), compiling_(true), totalNumberOfVariables_(numberOfVariables),
              mappingFromVariableToOriginalVariable_(std::move(mappingFromVariableToOriginalVariable)),
              mappingFromOriginalVariableToVariable_(std::move(mappingFromOriginalVariableToVariable)),
              usedVariableVector_(1 + numberOfVariables, false), nodeTypeCounter_(), nodeUniquePtrVector_(),
              orInnerNodeUniqueNodeCache_(S_ESTIMATED_INITIAL_SIZE_OF_INNER_NODE_UNIQUE_NODE_CACHE_FACTOR_ * numberOfVariables),
              andInnerNodeUniqueNodeCache_(S_ESTIMATED_INITIAL_SIZE_OF_INNER_NODE_UNIQUE_NODE_CACHE_FACTOR_ * numberOfVariables),
              trivialOrInnerNodeUniqueNodeCache_(), constantAndLiteralLeafUniqueNodeCache_(), circuitStatisticsPtr_(circuitStatisticsPtr) {
            assert(S_ESTIMATED_PERCENTAGE_OF_COPYING_SUBCIRCUIT_ >= 0 && S_ESTIMATED_PERCENTAGE_OF_COPYING_SUBCIRCUIT_ <= 100);

            // The variables cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<VarT>(numberOfVariables, 1))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("variables", numberOfVariables);

            // Node vector
            nodeUniquePtrVector_.reserve(static_cast<typename NodeUniquePtrVectorType::size_type>(2) +                       // constants: False, and True
                                         static_cast<typename NodeUniquePtrVectorType::size_type>(2 * numberOfVariables) +   // literals
                                         static_cast<typename NodeUniquePtrVectorType::size_type>(S_ESTIMATED_INITIAL_SIZE_OF_NODE_VECTOR_FACTOR_ * numberOfVariables));

            // Unique node cache
            constantAndLiteralLeafUniqueNodeCache_.reserve(static_cast<typename ConstantAndLiteralLeafUniqueNodeCacheType::size_type>(2) +                       // constants: False, and True
                                                           static_cast<typename ConstantAndLiteralLeafUniqueNodeCacheType::size_type>(2 * numberOfVariables));   // literals

            initializeNodeTypeCounter();

            id_counter_ = 2;   // 0 and 1 are used for the constant leaves
            initializeConstantLeaves();
            initializeLiteralLeaves(numberOfVariables);

            initialNodeId_ = id_counter_;
        }

        // Used for parsing a circuit
        Circuit(VarT numberOfVariables, IdNodeType numberOfNodes)
            : root_(), compiling_(false), totalNumberOfVariables_(numberOfVariables),
              mappingFromVariableToOriginalVariable_(), mappingFromOriginalVariableToVariable_(),
              usedVariableVector_(1 + numberOfVariables, false), nodeTypeCounter_(), nodeUniquePtrVector_(),
              orInnerNodeUniqueNodeCache_(), andInnerNodeUniqueNodeCache_(), trivialOrInnerNodeUniqueNodeCache_(),
              constantAndLiteralLeafUniqueNodeCache_(), circuitStatisticsPtr_(nullptr) {
            assert(S_ESTIMATED_PERCENTAGE_OF_COPYING_SUBCIRCUIT_ >= 0 && S_ESTIMATED_PERCENTAGE_OF_COPYING_SUBCIRCUIT_ <= 100);

            // The variables cannot be saved as std::size_t
            if (!Other::unsignedValueCanBeSavedAsStdSizeT<VarT>(numberOfVariables, 1))
                throw Exception::SomethingCannotBeSavedAsStdSizeTException("variables", numberOfVariables);

            // Not just 'numberOfNodes' because of possible free variables
            nodeUniquePtrVector_.reserve(static_cast<typename NodeUniquePtrVectorType::size_type>(1) +                       // root (core AND trivial OR nodes)
                                         static_cast<typename NodeUniquePtrVectorType::size_type>(3 * numberOfVariables) +   // trivial OR node for each variable
                                         static_cast<typename NodeUniquePtrVectorType::size_type>(numberOfNodes));           // core

            initializeNodeTypeCounter();

            smooth_ = true;
            id_counter_ = 0;
            initialNodeId_ = id_counter_;
        }

        Circuit(const Circuit&) = delete;
        Circuit(Circuit&&) noexcept = default;

        Circuit& operator=(const Circuit&) = delete;
        Circuit& operator=(Circuit&&) noexcept = default;

    private:
        bool smooth_;
        RootType root_;
        bool compiling_;   // compiling vs parsing
        IdNodeType id_counter_;
        IdNodeType initialNodeId_;
        VarT totalNumberOfVariables_;
        bool existsNoneDecomposableAndInnerNode_ = false;
        bool existsBellaDecomposableAndInnerNode_ = false;
        bool existsPosBellaDecomposableAndInnerNode_ = false;
        bool existsNegBellaDecomposableAndInnerNode_ = false;
        MappingFromVariableToOriginalVariableType mappingFromVariableToOriginalVariable_;
        MappingFromOriginalVariableToVariableType mappingFromOriginalVariableToVariable_;

        // MUST BE MODIFIED WHILE CREATING NEW NODES
        LargeNumberType size_ = 0;
        VarT numberOfUsedVariables_ = 0;
        LargeNumberType numberOfEdges_ = 0;   // only for inner nodes
        BoolVectorType usedVariableVector_;   // only for leaves
        NodeTypeCounterType nodeTypeCounter_;
        NodeUniquePtrVectorType nodeUniquePtrVector_;

        // Unique node caches
        InnerNodeUniqueNodeCacheType orInnerNodeUniqueNodeCache_;
        InnerNodeUniqueNodeCacheType andInnerNodeUniqueNodeCache_;
        TrivialOrInnerNodeUniqueNodeCacheType trivialOrInnerNodeUniqueNodeCache_;
        ConstantAndLiteralLeafUniqueNodeCacheType constantAndLiteralLeafUniqueNodeCache_;

        CircuitStatisticsPtrType circuitStatisticsPtr_;

        inline static constexpr LiteralT S_TRUE_ID_ = 1;
        inline static constexpr LiteralT S_FALSE_ID_ = 0;
        inline static constexpr int S_ESTIMATED_PERCENTAGE_OF_COPYING_SUBCIRCUIT_ = 5;
        inline static constexpr int S_ESTIMATED_INITIAL_SIZE_OF_NODE_VECTOR_FACTOR_ = 10;
        inline static constexpr int S_ESTIMATED_INITIAL_SIZE_OF_INNER_NODE_UNIQUE_NODE_CACHE_FACTOR_ = 2;

    private:
        /**
         * Initialize the node type counter
         */
        void initializeNodeTypeCounter() noexcept;

        /**
         * Initialize the constant leaves
         * Note: only for compiling_ = true
         * Indices:
         *      False - 0
         *      True  - 1
         */
        void initializeConstantLeaves() noexcept;

        /**
         * Initialize the literal leaves
         * Note: only for compiling_ = true
         * Indices:
         *       Lit1 - 2
         *      -Lit2 - 3
         *      ...
         *       LitN - 2*N
         *      -LitN - (2*N) + 1
         * @param numberOfVariables the number of variables in the formula
         */
        void initializeLiteralLeaves(VarT numberOfVariables);

        /**
         * Assert: MUST be consistent with nodeUniquePtrVector_
         * @return a new generated node's identifier
         */
        IdNodeType getNewIdNode();

        /**
         * @return the node with the given identifier
         * @throw IdentifierDoesNotExistException (debug) if the node with the given identifier does not exist in the circuit
         */
        NodeAbstractPtrType getNodePtr(IdNodeType id) const;

        /**
         * Generate a key for the vector of literals
         * Time complexity: O(#literals x log(#literals))
         * Side effect: literalVector will be sorted
         * @param literalVectorIsSorted is the literal vector already sorted
         * @return a generated key
         */
        KeyLiteralType generateKeyForLiteralVector(LiteralVectorType& literalVector, bool literalVectorIsSorted = false) const;

        /**
         * Update the particular variables that are related to the newly added node
         * @throw NotImplementedException if the node's type is not covered
         * @throw IdentifierDoesNotExistException (debug) if the node with the given identifier does not exist in the circuit
         */
        void updateVariablesAfterNodeAdded(IdNodeType id, NodeTypeEnum nodeTypeEnum, bool updateUsedVariables = true);

        /**
         * Note: used for queries (forgetting)
         * @return a remapped variable set based on mappingFromOriginalVariableToVariable_
         */
        VariableSetType remapFromOriginalVariableToVariable(const OriginalVariableSetType& originalVariableSet) const;

        /**
         * Note: used for queries (partial assignment)
         * @return a remapped literal set based on mappingFromOriginalVariableToVariable_
         */
        LiteralSetType remapFromOriginalLiteralToLiteral(const OriginalLiteralSetType& originalLiteralSet) const;

        /**
         * Recursively try all assignments. For every satisfying assignment, increment the number of models.
         * @param indexVariable the index of a variable that should be assigned next
         * @param partialAssignment [auxiliary] an assignment
         * @param variableSortedVector a sorted vector of variables
         * @param numberOfModels [output] the number of models
         * @param forgottenVariableSet a set of forgotten variables
         * @param cache [auxiliary] a cache
         * @param printModels should the models be printed
         * @param outModels where to print the models
         */
        void processModelCountingWithPolynomialDelay(VarT indexVariable, PartialAssignmentType& partialAssignment,
                                                     const VariableSortedVectorType& variableSortedVector, NumberOfModelsType& numberOfModels,
                                                     const VariableSetType& forgottenVariableSet, ConsistencyCheckCacheType& cache,
                                                     bool printModels, std::ostream& outModels);

    public:
        /**
         * Time complexity: O(1)
         * It is relevant after the root is set
         * @return the number of nodes in the circuit
         */
        IdNodeType getNumberOfNodes() const noexcept;

        /**
         * Getter
         * It is relevant after the root is set
         * @return the circuit size
         */
        LargeNumberType getCircuitSize() const noexcept;

        /**
         * Getter
         * It is relevant after the root is set
         * @return the number of edges in the circuit
         */
        LargeNumberType getNumberOfEdges() const noexcept;

        /**
         * It is relevant after the root is set
         * @return the number of used variables in the circuit
         */
        VarT getNumberOfUsedVariables() const noexcept;

        /**
         * Time complexity: O(1)
         * It is relevant after the root is set
         * @return the number of leaves
         */
        IdNodeType getNumberOfLeaves() const noexcept;

        /**
         * Time complexity: O(1)
         * It is relevant after the root is set
         * @return the number of inner nodes
         */
        IdNodeType getNumberOfInnerNodes() const noexcept;

        /**
         * Getter
         * It is relevant after the root is set
         * @return the node type counter
         */
        const NodeTypeCounterType& getNodeTypeCounter() const noexcept;

        /**
         * Check if an identifier exists in the circuit
         * Time complexity: O(1)
         * @param id a node's identifier
         * @return true if the node with the given identifier exists in the circuit. Otherwise, false is returned.
         */
        bool idExists(IdNodeType id) const noexcept;

        /**
         * The last added node will be set as the root.
         * The root can be set only once.
         * @throw AttemptResetRootException if the root is already set
         * @throw CircuitException if the circuit does not have any node
         */
        void setRoot();

        /**
         * Getter
         * @return the root
         */
        RootType getRoot() const noexcept;

        /**
         * Time complexity: O(1)
         * @return the circuit type
         */
        CircuitTypeEnum getCircuitType();

        /**
         * Create a new constant leaf in the circuit.
         * Because of the unique node cache, the constant leaf should already exist.
         * Note: unique node cache is used (constantAndLiteralLeafUniqueNodeCache_)
         * @return the identifier of the constant leaf
         */
        IdNodeType createConstantLeaf(bool constant) noexcept;

        /**
         * Create a new literal leaf in the circuit.
         * Because of the unique node cache, the literal leaf should already exist.
         * Assert: the literal MUST NOT be a zero literal
         * Note: unique node cache is used (constantAndLiteralLeafUniqueNodeCache_)
         * @return the identifier of the literal leaf
         */
        IdNodeType createLiteralLeaf(const LiteralType& lit);

        /**
         * Create a new AND inner node in the circuit
         * Note: unique node cache is NOT used
         * @return the identifier of the created AND inner node
         * @throw IdentifierDoesNotExistException (debug) if some child does not exist in the circuit
         * @throw SmoothnessIsNotSupportedException if the AND inner node is (- / pos / neg) Bella decomposable and smooth = true
         * @throw InnerNodeDoesNotSatisfyPropertyException (debug) if the AND inner node does not satisfy the particular property
         */
        IdNodeType createAndInnerNode(const IdNodeVectorType& childrenIdVector, DecomposabilityTypeEnum decomposabilityType);

        /**
         * Create a new OR inner node in the circuit
         * Note: only for compiling_ = false
         * Note: smoothness is checked and updated
         * Note: unique node cache is NOT used
         * @return the identifier of the created OR inner node
         * @throw IdentifierDoesNotExistException (debug) if some child does not exist in the circuit
         */
        IdNodeType createOrInnerNode(const IdNodeVectorType& childrenIdVector);

        /**
         * Create a new binary OR inner node in the circuit
         * Note: only for compiling_ = false
         * Note: smoothness is checked and updated
         * Note: unique node cache is NOT used
         * @return the identifier of the created binary OR inner node
         * @throw IdentifierDoesNotExistException (debug) if some child does not exist in the circuit
         */
        IdNodeType createBinaryOrInnerNode(VarT decisionVariable, IdNodeType highChildId, IdNodeType lowChildId);

        /**
         * Create a new binary OR inner node in the circuit
         * Note: smoothness is IGNORED
         * Note: only for compiling_ = true
         * Note: unique node cache is NOT used
         * Note: only for the copy subcircuit operation
         * @return the identifier of the created binary OR inner node
         * @throw IdentifierDoesNotExistException (debug) if any child does not exist in the circuit
         */
        IdNodeType createBinaryOrInnerNodeCopySubcircuit(VarT decisionVariable, IdNodeType highChildId, IdNodeType lowChildId);

        /**
         * Create a new AND inner node in the circuit.
         * If the AND inner node already exists in the circuit, nothing happens.
         * Used for AND inner nodes whose children are only literal leaves.
         * Note: only for compiling_ = true
         * Note: unique node cache is used (andInnerNodeUniqueNodeCache_)
         * Side effect: literalVector will be sorted
         * @param literalVectorIsSorted is the literal vector already sorted
         * @return the identifier of the created AND inner node
         */
        IdNodeType createAndInnerNode(LiteralVectorType&& literalVector, bool literalVectorIsSorted = false);
        IdNodeType createAndInnerNode(LiteralVectorType& literalVector, bool literalVectorIsSorted = false);

        /**
         * Create a new OR inner node in the circuit.
         * If the OR inner node already exists in the circuit, nothing happens.
         * Used for OR inner nodes whose children are only literal leaves.
         * Note: only for compiling_ = true
         * Note: unique node cache is used (orInnerNodeUniqueNodeCache_)
         * Side effect: literalVector will be sorted
         * @return the identifier of the created OR inner node
         */
        IdNodeType createOrInnerNode(LiteralVectorType&& literalVector);
        IdNodeType createOrInnerNode(LiteralVectorType& literalVector);

        /**
         * Create a new decision inner node in the circuit
         * Note: only for compiling_ = true
         * Note: unique node cache is NOT used
         * @return the identifier of the created decision inner node
         * @throw IdentifierDoesNotExistException (debug) if positiveNodeId or negativeNodeId does not exist in the circuit
         * @throw SmoothnessIsNotSupportedException if the circuit contains a (- / pos / neg) Bella decomposable AND inner node and smooth = true
         * @throw InnerNodeDoesNotSatisfyPropertyException (debug) if some of the AND inner nodes do not satisfy the decomposability property
         */
        IdNodeType createDecisionInnerNode(VarT decisionVariable, IdNodeType posNodeId, IdNodeType negNodeId,
                                           const VariableVectorType& posFreeVariables = {}, const VariableVectorType& negFreeVariables = {});

        /**
         * Create a new trivial OR inner node (var OR -var) in the circuit.
         * If the trivial OR inner node already exists in the circuit, nothing happens.
         * Note: used for missing variables and smoothness
         * Note: unique node cache is used (trivialOrInnerNodeUniqueNodeCache_)
         * @return the identifier of the created trivial OR inner node
         */
        IdNodeType createTrivialOrInnerNode(VarT var);

        /**
         * Create a new Krom-C leaf in the circuit
         * Note: unique node cache is NOT used
         * @return the identifier of the created Krom-C leaf
         */
        IdNodeType createKromCLeaf(const FormulaType& kromFormula);
        IdNodeType createKromCLeaf(FormulaType&& kromFormula);

        /**
         * Create a new renH-C leaf in the circuit
         * Note: unique node cache is NOT used
         * @return the identifier of the created renH-C leaf
         */
        IdNodeType createRenHCLeaf(const FormulaType& renamableHornFormula,
                                   const VariableSetType& switchedVariables);
        IdNodeType createRenHCLeaf(const FormulaType& renamableHornFormula,
                                   VariableSetType&& switchedVariables);
        IdNodeType createRenHCLeaf(FormulaType&& renamableHornFormula,
                                   const VariableSetType& switchedVariables);
        IdNodeType createRenHCLeaf(FormulaType&& renamableHornFormula,
                                   VariableSetType&& switchedVariables);

        /**
         * Copy the subcircuit rooted at the node
         * Note: if the mapping is empty, no copy will be done
         * Note: if the mapping is identical, no copy will be done
         * @param nodeId the identifier of the node
         * @param mapping a mapping from variables to literals
         * @param isVariableToLiteralMapping a variable to literal mapping vs a variable to variable mapping
         * @param currentComponentVariableSet [statistics] a set of variables appearing in the current component
         * @param formulaPtr [statistics] a formula pointer
         * @return the identifier of the created node / root
         * @throw MappingIsNotBijectiveException (debug) if the mapping is not bijective
         * @throw VariableDoesNotExistInMappingException (debug) if a variable in the subcircuit does not exist in the mapping
         * @throw NodeTypeDoesNotSupportCopySubcircuitOperationException if any node (type) in the subcircuit does not support the copy subcircuit method
         */
        template <typename ClauseIdT2>
        IdNodeType copySubcircuit(IdNodeType nodeId, const MappingFromVariableToLiteralType& mapping, bool isVariableToLiteralMapping,
                                  const VariableSetType& currentComponentVariableSet = {},
                                  const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT2>* formulaPtr = nullptr);

        /**
         * Print the circuit
         */
        void printCircuit(std::ostream& out);

        /**
         * Consistency check
         * Time complexity: linear with respect to the size of the (sub)circuit
         * @param partialAssignmentOriginalLiteralSet a set of original literals representing a partial assignment
         * @param forgottenOriginalVariableSet a set of original variables representing forgotten variables
         * @return true if the formula is consistent. Otherwise, false is returned.
         * @throw RootIsNotSetException if the root is not set
         * @throw CircuitTypeDoesNotSupportQueryException if the circuit does not support consistency check
         */
        bool consistencyCheck(const OriginalLiteralSetType& partialAssignmentOriginalLiteralSet,
                              const OriginalVariableSetType& forgottenOriginalVariableSet);

        /**
         * Model counting
         * Time complexity: linear with respect to the size of the (sub)circuit
         * @param partialAssignmentOriginalLiteralSet a set of original literals representing a partial assignment
         * @return the number of models of the formula
         * @throw RootIsNotSetException if the root is not set
         * @throw ModelCountingIsNotSupportedWithoutSmoothnessException if the circuit is not smooth
         * @throw CircuitTypeDoesNotSupportQueryException if the circuit does not support model counting
         */
        NumberOfModelsType modelCounting(const OriginalLiteralSetType& partialAssignmentOriginalLiteralSet);

        /**
         * Model counting with polynomial delay
         * Time complexity: linear with respect to the size of the (sub)circuit and the number of models
         * @param partialAssignmentOriginalLiteralSet a set of original literals representing a partial assignment
         * @param forgottenOriginalVariableSet a set of original variables representing forgotten variables
         * @param printModels should the models be printed
         * @param outModels where to print the models
         * @return the number of models of the formula
         * @throw RootIsNotSetException if the root is not set
         * @throw CircuitTypeDoesNotSupportQueryException if the circuit does not support consistency check
         */
        NumberOfModelsType modelCountingWithPolynomialDelay(const OriginalLiteralSetType& partialAssignmentOriginalLiteralSet,
                                                            const OriginalVariableSetType& forgottenOriginalVariableSet,
                                                            bool printModels = false, std::ostream& outModels = std::cout);

        /**
         * Clausal entailment check
         * For every clause, check if that clause is an implicate
         * Time complexity: linear with respect to the size of the (sub)circuit and the number of clauses
         * Assert: all clauses MUST be untouched
         * @param formulaPtr a formula pointer
         * @return true if all clauses are implicates. Otherwise, if at least one clause is not an implicate, False is returned.
         * @throw RootIsNotSetException if the root is not set
         * @throw CircuitTypeDoesNotSupportQueryException if the circuit does not support consistency check
         */
        template <typename ClauseIdT2>
        bool clausalEntailmentCheck(const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT2>* formulaPtr);

        /**
         * Set statistics after the compilation
         * Statistics: all
         */
        void setStatisticsAfterCompilation() const;

    public:
        /**
         * ostream << Circuit
         */
        friend std::ostream& operator<<(std::ostream& out, Circuit& circuit) {
            circuit.printCircuit(out);
            return out;
        }

    private:
        template <typename VarT2, typename LiteralT2, std::input_iterator InputIterator2>
        friend Circuit<VarT2, LiteralT2> Parser::parseCircuit(InputIterator2& begin, const InputIterator2& end,
                                                              IdNodeType numberOfNodes, LargeNumberType numberOfEdges,
                                                              VarT2 numberOfVariables, LargeNumberType size, unsigned int& line);

    #ifndef NDEBUG
    public:
        void printCircuitDebug(std::ostream& out);
    #endif
    };
}   // namespace Hydra::Circuit

#include "./Circuit.ipp"
