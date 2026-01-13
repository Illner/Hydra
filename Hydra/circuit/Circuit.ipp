#pragma once

#include "./Circuit.hpp"

namespace Hydra::Circuit {

    template <typename VarT, typename LiteralT>
    void Circuit<VarT, LiteralT>::initializeNodeTypeCounter() noexcept {
        // Leaf nodes
        for (NodeTypeEnum nodeType : Node::leafNodeTypeSet)
            nodeTypeCounter_[nodeType] = 0;

        // Inner nodes
        for (NodeTypeEnum nodeType : Node::innerNodeTypeSet)
            nodeTypeCounter_[nodeType] = 0;
    }

    template <typename VarT, typename LiteralT>
    void Circuit<VarT, LiteralT>::initializeConstantLeaves() noexcept {
        assert(compiling_);

        nodeUniquePtrVector_.push_back(std::make_unique<ConstantLeafType>(S_FALSE_ID_, false));   // ID: 0
        nodeUniquePtrVector_.push_back(std::make_unique<ConstantLeafType>(S_TRUE_ID_, true));     // ID: 1

        // Update variables
        updateVariablesAfterNodeAdded(S_FALSE_ID_, NodeTypeEnum::CONSTANT_LEAF, false);
        updateVariablesAfterNodeAdded(S_TRUE_ID_, NodeTypeEnum::CONSTANT_LEAF, false);

        // Unique node cache
        constantAndLiteralLeafUniqueNodeCache_.emplace_back(S_FALSE_ID_);
        constantAndLiteralLeafUniqueNodeCache_.emplace_back(S_TRUE_ID_);
    }

    template <typename VarT, typename LiteralT>
    void Circuit<VarT, LiteralT>::initializeLiteralLeaves(VarT numberOfVariables) {
        assert(compiling_);

        for (VarT var = 1; var <= numberOfVariables; ++var) {
            for (bool sign : { true, false }) {
                LiteralType lit(var, sign);

                IdNodeType id = getNewIdNode();

                // Unique node cache
                assert(constantAndLiteralLeafUniqueNodeCache_.size() == lit.getLiteralT());
                constantAndLiteralLeafUniqueNodeCache_.emplace_back(static_cast<LiteralT>(id));

                nodeUniquePtrVector_.push_back(std::make_unique<LiteralLeafType>(id, std::move(lit)));

                // Update variables
                updateVariablesAfterNodeAdded(id, NodeTypeEnum::LITERAL_LEAF, false);
            }
        }
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::getNewIdNode() {
        assert(nodeUniquePtrVector_.size() == id_counter_);

        IdNodeType tmp = id_counter_;
        ++id_counter_;

        return tmp;
    }

    template <typename VarT, typename LiteralT>
    typename Circuit<VarT, LiteralT>::NodeAbstractPtrType
    Circuit<VarT, LiteralT>::getNodePtr(IdNodeType id) const {
        #ifndef NDEBUG
        // Identifier does not exist in the circuit
        if (id >= nodeUniquePtrVector_.size())
            throw Exception::Circuit::IdentifierDoesNotExistException(id);
        #endif

        return nodeUniquePtrVector_[id].get();
    }

    template <typename VarT, typename LiteralT>
    typename Circuit<VarT, LiteralT>::KeyLiteralType
    Circuit<VarT, LiteralT>::generateKeyForLiteralVector(LiteralVectorType& literalVector, bool literalVectorIsSorted) const {
        KeyLiteralType generatedKey;
        generatedKey.reserve(literalVector.size());

        if (!literalVectorIsSorted)
            std::sort(literalVector.begin(), literalVector.end());

        for (const LiteralType& lit : literalVector)
            generatedKey.push_back(lit.getLiteralT());

        return generatedKey;
    }

    template <typename VarT, typename LiteralT>
    void Circuit<VarT, LiteralT>::updateVariablesAfterNodeAdded(IdNodeType id, NodeTypeEnum nodeTypeEnum, bool updateUsedVariables) {
        nodeTypeCounter_[nodeTypeEnum] += 1;

        // Inner node
        if (Other::containInSet(Node::innerNodeTypeSet, nodeTypeEnum)) {
            #ifndef NDEBUG
            const InnerNodeAbstractType* nodePtr = dynamic_cast<InnerNodeAbstractType*>(getNodePtr(id));
            #else
            const InnerNodeAbstractType* nodePtr = static_cast<InnerNodeAbstractType*>(getNodePtr(id));
            #endif

            size_ += nodePtr->getSize();
            numberOfEdges_ += nodePtr->getNumberOfChildren();
            return;
        }

        // Leaf node
        if (Other::containInSet(Node::leafNodeTypeSet, nodeTypeEnum)) {
            #ifndef NDEBUG
            const LeafAbstractType* nodePtr = dynamic_cast<LeafAbstractType*>(getNodePtr(id));
            #else
            const LeafAbstractType* nodePtr = static_cast<LeafAbstractType*>(getNodePtr(id));
            #endif

            size_ += nodePtr->getSize();

            if (updateUsedVariables) {
                nodePtr->setUsedVariables(usedVariableVector_, numberOfUsedVariables_);

                assert(!usedVariableVector_[0]);

                #ifndef NDEBUG
                // Check if the number of used variables is valid
                VarT numberOfUsedVariablesTmp = 0;
                for (bool b : usedVariableVector_) {
                    if (b)
                        ++numberOfUsedVariablesTmp;
                }

                assert(numberOfUsedVariablesTmp == numberOfUsedVariables_);
                #endif
            }

            return;
        }

        throw Exception::NotImplementedException(Node::nodeTypeEnumToString(nodeTypeEnum),
                                                 "Hydra::Circuit::Circuit::updateVariablesAfterNodeAdded");
    }

    template <typename VarT, typename LiteralT>
    typename Circuit<VarT, LiteralT>::VariableSetType
    Circuit<VarT, LiteralT>::remapFromOriginalVariableToVariable(const OriginalVariableSetType& originalVariableSet) const {
        VariableSetType variableSet(originalVariableSet.size());

        for (OriginalVarType var : originalVariableSet) {
            if (auto itTmp = mappingFromOriginalVariableToVariable_.find(var); itTmp != mappingFromOriginalVariableToVariable_.end())
                variableSet.emplace(itTmp->second);
            else
                variableSet.emplace(static_cast<VarT>(var));
        }

        return variableSet;
    }

    template <typename VarT, typename LiteralT>
    typename Circuit<VarT, LiteralT>::LiteralSetType
    Circuit<VarT, LiteralT>::remapFromOriginalLiteralToLiteral(const OriginalLiteralSetType& originalLiteralSet) const {
        LiteralSetType literalSet(originalLiteralSet.size());

        for (OriginalLiteralType lit : originalLiteralSet) {
            OriginalVarType var = static_cast<OriginalVarType>(std::abs(lit));

            if (auto itTmp = mappingFromOriginalVariableToVariable_.find(var); itTmp != mappingFromOriginalVariableToVariable_.end()) {
                LiteralType litTmp(itTmp->second, lit > 0);
                literalSet.insert(std::move(litTmp));
            }
            else {
                LiteralType litTmp(static_cast<VarT>(var), lit > 0);
                literalSet.insert(std::move(litTmp));
            }
        }

        return literalSet;
    }

    template <typename VarT, typename LiteralT>
    void Circuit<VarT, LiteralT>::processModelCountingWithPolynomialDelay(VarT indexVariable, PartialAssignmentType& partialAssignment,
                                                                          const VariableSortedVectorType& variableSortedVector,
                                                                          NumberOfModelsType& numberOfModels,
                                                                          const VariableSetType& forgottenVariableSet, ConsistencyCheckCacheType& cache,
                                                                          bool printModels, std::ostream& outModels) {
        // Full assignment
        if (indexVariable == variableSortedVector.size()) {
            ++numberOfModels;

            // Print the model
            if (printModels)
                outModels << partialAssignment << std::endl;

            return;
        }

        VarT var = variableSortedVector[indexVariable];
        ++indexVariable;

        for (bool sign : { true, false }) {
            LiteralType lit(var, sign);

            partialAssignment.addLiteral(lit);

            cache.clear();
            if (getNodePtr(*root_)->consistencyCheck(partialAssignment, forgottenVariableSet, cache))
                processModelCountingWithPolynomialDelay(indexVariable, partialAssignment, variableSortedVector, numberOfModels, forgottenVariableSet, cache,
                                                        printModels, outModels);

            partialAssignment.removeLiteral(lit);
        }
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::getNumberOfNodes() const noexcept {
        return static_cast<IdNodeType>(nodeUniquePtrVector_.size());
    }

    template <typename VarT, typename LiteralT>
    LargeNumberType Circuit<VarT, LiteralT>::getCircuitSize() const noexcept {
        return size_;
    }

    template <typename VarT, typename LiteralT>
    LargeNumberType Circuit<VarT, LiteralT>::getNumberOfEdges() const noexcept {
        return numberOfEdges_;
    }

    template <typename VarT, typename LiteralT>
    VarT Circuit<VarT, LiteralT>::getNumberOfUsedVariables() const noexcept {
        return numberOfUsedVariables_;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::getNumberOfLeaves() const noexcept {
        IdNodeType tmp = 0;

        for (auto [nodeTypeEnum, numberOfNodes] : nodeTypeCounter_) {
            if (Other::containInSet(Node::leafNodeTypeSet, nodeTypeEnum))
                tmp += numberOfNodes;
        }

        return tmp;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::getNumberOfInnerNodes() const noexcept {
        IdNodeType tmp = 0;

        for (auto [nodeTypeEnum, numberOfNodes] : nodeTypeCounter_) {
            if (Other::containInSet(Node::innerNodeTypeSet, nodeTypeEnum))
                tmp += numberOfNodes;
        }

        return tmp;
    }

    template <typename VarT, typename LiteralT>
    const typename Circuit<VarT, LiteralT>::NodeTypeCounterType&
    Circuit<VarT, LiteralT>::getNodeTypeCounter() const noexcept {
        return nodeTypeCounter_;
    }

    template <typename VarT, typename LiteralT>
    bool Circuit<VarT, LiteralT>::idExists(IdNodeType id) const noexcept {
        return (id < nodeUniquePtrVector_.size());
    }

    template <typename VarT, typename LiteralT>
    void Circuit<VarT, LiteralT>::setRoot() {
        // The root is already set
        if (root_.has_value())
            throw Exception::Circuit::AttemptToResetRootException(*root_);

        IdNodeType id = getNumberOfNodes();

        assert(id == id_counter_);

        // No active node in the circuit
        if (id == initialNodeId_)
            throw Exception::Circuit::CircuitException("The circuit does not have any node to be set as the root!");

        --id;   // the identifier of the last added node

        // Check smoothness
        if (!compiling_ && smooth_)
            smooth_ = getNodePtr(id)->isCircuitSmooth(getNumberOfNodes());

        // No missing variable
        if (totalNumberOfVariables_ == numberOfUsedVariables_) {
            root_ = id;
            return;
        }

        IdNodeVectorType childrenVector;
        childrenVector.reserve(static_cast<typename IdNodeVectorType::size_type>(1) +
                               static_cast<typename IdNodeVectorType::size_type>(totalNumberOfVariables_ - numberOfUsedVariables_));
        childrenVector.emplace_back(id);

        // Missing variables
        for (VarT var = 1; var <= totalNumberOfVariables_; ++var) {
            // The variable is missing
            if (!usedVariableVector_[var])
                childrenVector.push_back(createTrivialOrInnerNode(var));
        }

        root_ = createAndInnerNode(childrenVector, DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
    }

    template <typename VarT, typename LiteralT>
    typename Circuit<VarT, LiteralT>::RootType
    Circuit<VarT, LiteralT>::getRoot() const noexcept {
        return root_;
    }

    template <typename VarT, typename LiteralT>
    CircuitTypeEnum Circuit<VarT, LiteralT>::getCircuitType() {
        // (s-)NNF
        if (existsNoneDecomposableAndInnerNode_) {
            if (smooth_)
                return CircuitTypeEnum::s_NNF;

            return CircuitTypeEnum::NNF;
        }

        // (s-)DNNF
        if (nodeTypeCounter_[NodeTypeEnum::OR_INNER_NODE] > 0 && !existsBellaDecomposableAndInnerNode_ &&
            !existsPosBellaDecomposableAndInnerNode_ && !existsNegBellaDecomposableAndInnerNode_) {
            if (smooth_)
                return CircuitTypeEnum::s_DNNF;

            return CircuitTypeEnum::DNNF;
        }

        // Bella decomposability
        if (existsBellaDecomposableAndInnerNode_ || (existsPosBellaDecomposableAndInnerNode_ && existsNegBellaDecomposableAndInnerNode_)) {
            assert(nodeTypeCounter_[NodeTypeEnum::PC_LEAF] == 0);            // no PC leaves
            assert(nodeTypeCounter_[NodeTypeEnum::Horn_C_LEAF] == 0);        // no Horn-C leaves
            assert(nodeTypeCounter_[NodeTypeEnum::anti_Horn_C_LEAF] == 0);   // no anti-Horn-C leaves

            // Bella
            if (nodeTypeCounter_[NodeTypeEnum::renH_C_LEAF] > 0) {
                assert(nodeTypeCounter_[NodeTypeEnum::Krom_C_LEAF] == 0);   // no Krom-C leaves

                return CircuitTypeEnum::Bella;
            }

            // Krom-Bella
            if (nodeTypeCounter_[NodeTypeEnum::Krom_C_LEAF] > 0)
                return CircuitTypeEnum::Krom_Bella;

            // wDNNF
            return CircuitTypeEnum::wDNNF;
        }

        // posBella decomposability
        if (existsPosBellaDecomposableAndInnerNode_) {
            assert(nodeTypeCounter_[NodeTypeEnum::PC_LEAF] == 0);       // no PC leaves
            assert(nodeTypeCounter_[NodeTypeEnum::Horn_C_LEAF] == 0);   // no Horn-C leaves
            assert(nodeTypeCounter_[NodeTypeEnum::Krom_C_LEAF] == 0);   // no Krom-C leaves
            assert(nodeTypeCounter_[NodeTypeEnum::renH_C_LEAF] == 0);   // no renH-C leaves

            // posBella
            if (nodeTypeCounter_[NodeTypeEnum::anti_Horn_C_LEAF] > 0)
                return CircuitTypeEnum::posBella;

            // pwDNNF
            return CircuitTypeEnum::pwDNNF;
        }

        // negBella decomposability
        if (existsNegBellaDecomposableAndInnerNode_) {
            assert(nodeTypeCounter_[NodeTypeEnum::PC_LEAF] == 0);            // no PC leaves
            assert(nodeTypeCounter_[NodeTypeEnum::Krom_C_LEAF] == 0);        // no Krom-C leaves
            assert(nodeTypeCounter_[NodeTypeEnum::renH_C_LEAF] == 0);        // no renH-C leaves
            assert(nodeTypeCounter_[NodeTypeEnum::anti_Horn_C_LEAF] == 0);   // no anti-Horn-C leaves

            // negBella
            if (nodeTypeCounter_[NodeTypeEnum::Horn_C_LEAF] > 0)
                return CircuitTypeEnum::negBella;

            // nwDNNF
            return CircuitTypeEnum::nwDNNF;
        }

        // {renH-C, Krom-C}-(s)d-BDMC
        if ((nodeTypeCounter_[NodeTypeEnum::renH_C_LEAF] > 0) &&
            (nodeTypeCounter_[NodeTypeEnum::Krom_C_LEAF] > 0)) {
            assert(nodeTypeCounter_[NodeTypeEnum::PC_LEAF] == 0);            // no PC leaves
            assert(nodeTypeCounter_[NodeTypeEnum::Horn_C_LEAF] == 0);        // no Horn-C leaves
            assert(nodeTypeCounter_[NodeTypeEnum::anti_Horn_C_LEAF] == 0);   // no anti-Horn-C leaves

            if (smooth_)
                return CircuitTypeEnum::renH_C_AND_Krom_C_sd_BDMC;

            return CircuitTypeEnum::renH_C_AND_Krom_C_d_BDMC;
        }

        // {renH-C}-(s)d-BDMC
        if (nodeTypeCounter_[NodeTypeEnum::renH_C_LEAF] > 0) {
            assert(nodeTypeCounter_[NodeTypeEnum::PC_LEAF] == 0);            // no PC leaves
            assert(nodeTypeCounter_[NodeTypeEnum::Horn_C_LEAF] == 0);        // no Horn-C leaves
            assert(nodeTypeCounter_[NodeTypeEnum::anti_Horn_C_LEAF] == 0);   // no anti-Horn-C leaves

            if (smooth_)
                return CircuitTypeEnum::renH_C_sd_BDMC;

            return CircuitTypeEnum::renH_C_d_BDMC;
        }

        // {Krom-C}-(s)d-BDMC
        if (nodeTypeCounter_[NodeTypeEnum::Krom_C_LEAF] > 0) {
            assert(nodeTypeCounter_[NodeTypeEnum::PC_LEAF] == 0);            // no PC leaves
            assert(nodeTypeCounter_[NodeTypeEnum::Horn_C_LEAF] == 0);        // no Horn-C leaves
            assert(nodeTypeCounter_[NodeTypeEnum::anti_Horn_C_LEAF] == 0);   // no anti-Horn-C leaves

            if (smooth_)
                return CircuitTypeEnum::Krom_C_sd_BDMC;

            return CircuitTypeEnum::Krom_C_d_BDMC;
        }

        assert(nodeTypeCounter_[NodeTypeEnum::PC_LEAF] == 0);            // no PC leaves
        assert(nodeTypeCounter_[NodeTypeEnum::Krom_C_LEAF] == 0);        // no Krom-C leaves
        assert(nodeTypeCounter_[NodeTypeEnum::renH_C_LEAF] == 0);        // no renH-C leaves
        assert(nodeTypeCounter_[NodeTypeEnum::Horn_C_LEAF] == 0);        // no Horn-C leaves
        assert(nodeTypeCounter_[NodeTypeEnum::anti_Horn_C_LEAF] == 0);   // no anti-Horn-C leaves

        if (smooth_)
            return CircuitTypeEnum::sd_DNNF;

        return CircuitTypeEnum::d_DNNF;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createConstantLeaf(bool constant) noexcept {
        // Unique node cache is used
        if (compiling_)
            return static_cast<IdNodeType>(constantAndLiteralLeafUniqueNodeCache_[constant]);

        // Unique node cache is NOT used
        IdNodeType id = getNewIdNode();
        nodeUniquePtrVector_.push_back(std::make_unique<ConstantLeafType>(id, constant));

        // Update variables
        updateVariablesAfterNodeAdded(id, NodeTypeEnum::CONSTANT_LEAF, false);

        return id;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createLiteralLeaf(const LiteralType& lit) {
        assert(!lit.isZeroLiteral());   // not a zero literal

        // Unique node cache is used
        if (compiling_) {
            assert(lit.getLiteralT() < constantAndLiteralLeafUniqueNodeCache_.size());

            VarT var = lit.getVariable();

            assert(var < usedVariableVector_.size());

            if (!usedVariableVector_[var]) {
                ++numberOfUsedVariables_;
                usedVariableVector_[var] = true;
            }

            return static_cast<IdNodeType>(constantAndLiteralLeafUniqueNodeCache_[lit.getLiteralT()]);
        }

        // Unique node cache is NOT used
        IdNodeType id = getNewIdNode();
        nodeUniquePtrVector_.push_back(std::make_unique<LiteralLeafType>(id, lit));

        // Update variables
        updateVariablesAfterNodeAdded(id, NodeTypeEnum::LITERAL_LEAF);

        return id;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createAndInnerNode(const IdNodeVectorType& childrenIdVector,
                                                           DecomposabilityTypeEnum decomposabilityType) {
        // Just one child
        if (compiling_ && childrenIdVector.size() == 1)
            return childrenIdVector[0];

        // None decomposability
        if (decomposabilityType == DecomposabilityTypeEnum::NONE)
            existsNoneDecomposableAndInnerNode_ = true;

        // (- / pos / neg) Bella decomposability
        if (Other::containInSet(Node::bellaDecomposabilityTypeSet, decomposabilityType)) {
            switch (decomposabilityType) {
                case Node::DecomposabilityTypeEnum::BELLA_DECOMPOSABILITY:
                    existsBellaDecomposableAndInnerNode_ = true;
                    break;
                case Node::DecomposabilityTypeEnum::posBELLA_DECOMPOSABILITY:
                    existsPosBellaDecomposableAndInnerNode_ = true;
                    break;
                case Node::DecomposabilityTypeEnum::negBELLA_DECOMPOSABILITY:
                    existsNegBellaDecomposableAndInnerNode_ = true;
                    break;
                default:
                    throw Exception::NotImplementedException(decomposabilityTypeEnumToString(decomposabilityType),
                                                             "Hydra::Circuit::Circuit::createAndInnerNode");
            }

            // Smoothness is not supported
            if (compiling_ && smooth_)
                throw Exception::Circuit::SmoothnessIsNotSupportedException();
            if (!compiling_)
                smooth_ = false;
        }

        NodeAbstractPtrVectorType childrenPtrVector;
        childrenPtrVector.reserve(childrenIdVector.size());
        for (IdNodeType childId : childrenIdVector)
            childrenPtrVector.push_back(getNodePtr(childId));

        IdNodeType id = getNewIdNode();
        nodeUniquePtrVector_.push_back(std::make_unique<AndInnerNodeType>(id, std::move(childrenPtrVector), decomposabilityType));

        // Update variables
        updateVariablesAfterNodeAdded(id, NodeTypeEnum::AND_INNER_NODE);

        return id;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createOrInnerNode(const IdNodeVectorType& childrenIdVector) {
        assert(!compiling_);

        NodeAbstractPtrVectorType childrenPtrVector;
        childrenPtrVector.reserve(childrenIdVector.size());
        for (IdNodeType childId : childrenIdVector)
            childrenPtrVector.push_back(getNodePtr(childId));

        IdNodeType id = getNewIdNode();
        nodeUniquePtrVector_.push_back(std::make_unique<OrInnerNodeType>(id, std::move(childrenPtrVector)));

        // Update variables
        updateVariablesAfterNodeAdded(id, NodeTypeEnum::OR_INNER_NODE);

        return id;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createBinaryOrInnerNode(VarT decisionVariable,
                                                                IdNodeType highChildId, IdNodeType lowChildId) {
        assert(!compiling_);
        assert(decisionVariable > 0);   // decision variable must be set

        NodeAbstractPtrType highChildPtr = getNodePtr(highChildId);
        NodeAbstractPtrType lowChildPtr = getNodePtr(lowChildId);

        IdNodeType id = getNewIdNode();
        nodeUniquePtrVector_.push_back(std::make_unique<BinaryOrInnerNodeType>(id, highChildPtr, lowChildPtr,
                                                                               decisionVariable));

        // Update variables
        updateVariablesAfterNodeAdded(id, NodeTypeEnum::BINARY_OR_INNER_NODE);

        return id;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createBinaryOrInnerNodeCopySubcircuit(VarT decisionVariable, IdNodeType highChildId, IdNodeType lowChildId) {
        assert(compiling_);
        assert(decisionVariable > 0);   // decision variable must be set

        NodeAbstractPtrType highChildPtr = getNodePtr(highChildId);
        NodeAbstractPtrType lowChildPtr = getNodePtr(lowChildId);

        IdNodeType id = getNewIdNode();
        nodeUniquePtrVector_.push_back(std::make_unique<BinaryOrInnerNodeType>(id, highChildPtr, lowChildPtr,
                                                                               decisionVariable));

        // Update variables
        updateVariablesAfterNodeAdded(id, NodeTypeEnum::BINARY_OR_INNER_NODE);

        return id;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createAndInnerNode(LiteralVectorType&& literalVector, bool literalVectorIsSorted) {
        return createLiteralLeaf(literalVector, literalVectorIsSorted);
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createAndInnerNode(LiteralVectorType& literalVector, bool literalVectorIsSorted) {
        assert(compiling_);

        // Just one child
        if (literalVector.size() == 1)
            return createLiteralLeaf(literalVector[0]);

        #ifndef NDEBUG
        // Check uniqueness
        VariableSetType setTmp(literalVector.size());
        for (const LiteralType& lit : literalVector) {
            VarT varTmp = lit.getVariable();
            if (Other::containInSet(setTmp, varTmp))
                assert(false);

            setTmp.emplace(varTmp);
        }
        #endif

        KeyLiteralType generatedKey = generateKeyForLiteralVector(literalVector, literalVectorIsSorted);

        // The AND inner node already exists in the circuit
        if (auto itTmp = andInnerNodeUniqueNodeCache_.find(generatedKey); itTmp != andInnerNodeUniqueNodeCache_.end())
            return itTmp->second;

        NodeAbstractPtrVectorType childrenPtrVector;
        childrenPtrVector.reserve(literalVector.size());
        for (const LiteralType& lit : literalVector)
            childrenPtrVector.push_back(getNodePtr(createLiteralLeaf(lit)));

        IdNodeType id = getNewIdNode();
        nodeUniquePtrVector_.push_back(std::make_unique<AndInnerNodeType>(id, std::move(childrenPtrVector),
                                                                          DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY));

        // Unique node cache
        andInnerNodeUniqueNodeCache_[std::move(generatedKey)] = id;

        // Update variables
        updateVariablesAfterNodeAdded(id, NodeTypeEnum::AND_INNER_NODE);

        return id;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createOrInnerNode(LiteralVectorType&& literalVector) {
        return createOrInnerNode(literalVector);
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createOrInnerNode(LiteralVectorType& literalVector) {
        assert(compiling_);

        // Just one child
        if (literalVector.size() == 1)
            return createLiteralLeaf(literalVector[0]);

        KeyLiteralType generatedKey = generateKeyForLiteralVector(literalVector, false);

        // The OR inner node already exists in the circuit
        if (auto itTmp = orInnerNodeUniqueNodeCache_.find(generatedKey); itTmp != orInnerNodeUniqueNodeCache_.end())
            return itTmp->second;

        NodeAbstractPtrVectorType childrenPtrVector;
        childrenPtrVector.reserve(literalVector.size());
        for (const LiteralType& lit : literalVector)
            childrenPtrVector.push_back(getNodePtr(createLiteralLeaf(lit)));

        IdNodeType id = getNewIdNode();
        nodeUniquePtrVector_.push_back(std::make_unique<OrInnerNodeType>(id, std::move(childrenPtrVector)));

        // Unique node cache
        orInnerNodeUniqueNodeCache_[std::move(generatedKey)] = id;

        // Update variables
        updateVariablesAfterNodeAdded(id, NodeTypeEnum::OR_INNER_NODE);

        return id;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createDecisionInnerNode(VarT decisionVariable,
                                                                IdNodeType posNodeId, IdNodeType negNodeId,
                                                                const VariableVectorType& posFreeVariables, const VariableVectorType& negFreeVariables) {
        assert(compiling_);
        assert(decisionVariable > 0);   // decision variable must be set

        LiteralType posLit(decisionVariable, true);
        LiteralType negLit(decisionVariable, false);
        IdNodeType posLiteralLeafId = createLiteralLeaf(posLit);
        IdNodeType negLiteralLeafId = createLiteralLeaf(negLit);

        IdNodeType posNodeIdTmp = posNodeId;
        IdNodeType negNodeIdTmp = negNodeId;

        // Smoothness
        if (smooth_) {
            // The circuit contains a (- / pos / neg) Bella decomposable AND inner node
            if (existsBellaDecomposableAndInnerNode_ || existsPosBellaDecomposableAndInnerNode_ || existsNegBellaDecomposableAndInnerNode_)
                throw Exception::Circuit::SmoothnessIsNotSupportedException();

            // Positive node
            if (!posFreeVariables.empty()) {
                IdNodeVectorType childrenVector;
                childrenVector.reserve(1 + posFreeVariables.size());
                childrenVector.emplace_back(posNodeId);

                for (VarT posFreeVar : posFreeVariables)
                    childrenVector.emplace_back(createTrivialOrInnerNode(posFreeVar));

                posNodeIdTmp = createAndInnerNode(childrenVector, DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
            }

            // Negative node
            if (!negFreeVariables.empty()) {
                IdNodeVectorType childrenVector;
                childrenVector.reserve(1 + negFreeVariables.size());
                childrenVector.emplace_back(negNodeId);

                for (VarT negFreeVar : negFreeVariables)
                    childrenVector.emplace_back(createTrivialOrInnerNode(negFreeVar));

                negNodeIdTmp = createAndInnerNode(childrenVector, DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
            }
        }

        IdNodeType posAndInnerNodeId = createAndInnerNode({ posNodeIdTmp, posLiteralLeafId },
                                                          DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
        NodeAbstractPtrType posAndInnerNodePtr = getNodePtr(posAndInnerNodeId);
        IdNodeType negAndInnerNodeId = createAndInnerNode({ negNodeIdTmp, negLiteralLeafId },
                                                          DecomposabilityTypeEnum::CLASSICAL_DECOMPOSABILITY);
        NodeAbstractPtrType negAndInnerNodePtr = getNodePtr(negAndInnerNodeId);

        // Create a binary OR inner node
        IdNodeType id = getNewIdNode();
        nodeUniquePtrVector_.push_back(std::make_unique<BinaryOrInnerNodeType>(id,
                                                                               posAndInnerNodePtr,
                                                                               negAndInnerNodePtr,
                                                                               decisionVariable));

        // Update variables
        updateVariablesAfterNodeAdded(id, NodeTypeEnum::BINARY_OR_INNER_NODE);

        return id;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createTrivialOrInnerNode(VarT var) {
        // Unique node cache
        if (compiling_ && smooth_) {
            if (auto itTmp = trivialOrInnerNodeUniqueNodeCache_.find(var); itTmp != trivialOrInnerNodeUniqueNodeCache_.end())
                return itTmp->second;
        }

        LiteralType posLit(var, true);
        LiteralType negLit(var, false);
        NodeAbstractPtrType posLiteralLeafPtr = getNodePtr(createLiteralLeaf(posLit));
        NodeAbstractPtrType negLiteralLeafPtr = getNodePtr(createLiteralLeaf(negLit));

        IdNodeType id = getNewIdNode();
        nodeUniquePtrVector_.push_back(std::make_unique<BinaryOrInnerNodeType>(id, posLiteralLeafPtr,
                                                                               negLiteralLeafPtr, var));

        // Unique node cache
        if (compiling_ && smooth_)
            trivialOrInnerNodeUniqueNodeCache_[var] = id;

        // Update variables
        updateVariablesAfterNodeAdded(id, NodeTypeEnum::BINARY_OR_INNER_NODE);

        return id;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createKromCLeaf(const FormulaType& kromFormula) {
        FormulaType kromFormulaCopy = kromFormula;
        return createKromCLeaf(std::move(kromFormulaCopy));
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createKromCLeaf(FormulaType&& kromFormula) {
        IdNodeType id = getNewIdNode();
        nodeUniquePtrVector_.push_back(std::make_unique<KromCLeafType>(id, std::move(kromFormula)));

        // Update variables
        updateVariablesAfterNodeAdded(id, NodeTypeEnum::Krom_C_LEAF);

        return id;
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createRenHCLeaf(const FormulaType& renamableHornFormula,
                                                        const VariableSetType& switchedVariables) {
        FormulaType renamableHornFormulaCopy = renamableHornFormula;
        VariableSetType switchedVariablesCopy = switchedVariables;
        return createRenHCLeaf(std::move(renamableHornFormulaCopy), std::move(switchedVariablesCopy));
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createRenHCLeaf(const FormulaType& renamableHornFormula,
                                                        VariableSetType&& switchedVariables) {
        FormulaType renamableHornFormulaCopy = renamableHornFormula;
        return createRenHCLeaf(std::move(renamableHornFormulaCopy), std::move(switchedVariables));
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createRenHCLeaf(FormulaType&& renamableHornFormula,
                                                        const VariableSetType& switchedVariables) {
        VariableSetType switchedVariablesCopy = switchedVariables;
        return createRenHCLeaf(std::move(renamableHornFormula), std::move(switchedVariablesCopy));
    }

    template <typename VarT, typename LiteralT>
    IdNodeType Circuit<VarT, LiteralT>::createRenHCLeaf(FormulaType&& renamableHornFormula,
                                                        VariableSetType&& switchedVariables) {
        IdNodeType id = getNewIdNode();
        nodeUniquePtrVector_.push_back(std::make_unique<RenHCLeafType>(id, std::move(renamableHornFormula),
                                                                       std::move(switchedVariables)));

        // Update variables
        updateVariablesAfterNodeAdded(id, NodeTypeEnum::renH_C_LEAF);

        return id;
    }

    template <typename VarT, typename LiteralT>
    template <typename ClauseIdT2>
    IdNodeType Circuit<VarT, LiteralT>::copySubcircuit(IdNodeType nodeId, const MappingFromVariableToLiteralType& mapping, bool isVariableToLiteralMapping,
                                                       const VariableSetType& currentComponentVariableSet,
                                                       const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT2>* formulaPtr) {
        // Empty mapping
        if (mapping.empty())
            return nodeId;

        #ifndef NDEBUG
        // A variable to variable mapping
        if (!isVariableToLiteralMapping) {
            for (const auto& [key, value] : mapping)
                assert(value.isPositive());
        }

        // Check bijection
        VariableSetType valueSetTmp(mapping.size());
        for (const auto& [key, value] : mapping)
            valueSetTmp.emplace(value.getVariable());

        // The mapping is not bijective
        if (mapping.size() != valueSetTmp.size()) {
            std::stringstream stringStreamTmp = Other::createStringStreamFromMapWithToStringConversion(mapping);
            throw Exception::MappingIsNotBijectiveException(stringStreamTmp.str());
        }

        // Check if all variables in the subcircuit exist in the mapping
        for (VarT var : getNodePtr(nodeId)->getSortedVariablesInCircuitDebug()) {
            if (!Other::containInMap(mapping, var)) {
                std::stringstream stringStreamTmp = Other::createStringStreamFromMapWithToStringConversion(mapping);
                throw Exception::VariableDoesNotExistInMappingException(var, stringStreamTmp.str());
            }
        }
        #endif

        // Check if the mapping is identical
        bool isIdentical = true;
        for (const auto& [key, value] : mapping) {
            if ((key != value.getVariable()) || value.isNegative()) {
                isIdentical = false;
                break;
            }
        }

        // The mapping is identical
        if (isIdentical)
            return nodeId;

        // Statistics
        if (circuitStatisticsPtr_) {
            assert(formulaPtr);                             // formula pointer is set
            assert(!currentComponentVariableSet.empty());   // current component variables are set

            circuitStatisticsPtr_->copySubcircuitTimer.startStopwatch();
        }

        CopySubcircuitCacheType cache(1 + getNumberOfNodes() * S_ESTIMATED_PERCENTAGE_OF_COPYING_SUBCIRCUIT_ / 100);

        IdNodeType copiedNodeId = getNodePtr(nodeId)->copySubcircuit(this, mapping, cache, isVariableToLiteralMapping);

        // Statistics
        if (circuitStatisticsPtr_) {
            circuitStatisticsPtr_->formulaSizeCopySubcircuitCounter.addCount(static_cast<Statistics::LargeNumberType>(formulaPtr->getCurrentComponentFormulaSize(currentComponentVariableSet)));
            circuitStatisticsPtr_->numberOfVariablesCopySubcircuitCounter.addCount(static_cast<Statistics::LargeNumberType>(currentComponentVariableSet.size()));
            circuitStatisticsPtr_->numberOfClausesCopySubcircuitCounter.addCount(static_cast<Statistics::LargeNumberType>(formulaPtr->getNumberOfCurrentComponentClauses(currentComponentVariableSet)));

            circuitStatisticsPtr_->copySubcircuitTimer.stopStopwatch();
        }

        return copiedNodeId;
    }

    template <typename VarT, typename LiteralT>
    void Circuit<VarT, LiteralT>::printCircuit(std::ostream& out) {
        // The root is not set
        if (!root_.has_value())
            throw Exception::Circuit::RootIsNotSetException();

        Other::printTitle(out, " Bella ", 19, '-', COMMENT);

        out << COMMENT << " " << circuitTypeEnumToString(getCircuitType()) << std::endl;
        out << COMMENT << std::endl;

        // nnf number_of_nodes number_of_edges number_of_variables [size]
        out << NNF_HEADER_STRING << " "
            << std::to_string(getNumberOfNodes()) << " "
            << std::to_string(getNumberOfEdges()) << " "
            << std::to_string(getNumberOfUsedVariables());

        if (getNumberOfEdges() == getCircuitSize())
            out << std::endl;
        else
            out << " " << std::to_string(getCircuitSize()) << std::endl;

        // Node types
        NodeTypeEnumSortedVectorType nodeTypeKeySortedVector = Other::extractKeysFromMap(nodeTypeCounter_, true);
        for (NodeTypeEnum nodeType : nodeTypeKeySortedVector) {
            IdNodeType numberOfNodesTmp = nodeTypeCounter_[nodeType];
            if (numberOfNodesTmp > 0)
                out << COMMENT << " " << Node::nodeTypeEnumToString(nodeType) << ": " << std::to_string(numberOfNodesTmp) << std::endl;
        }

        // Nodes
        for (IdNodeType id = 0; id < getNumberOfNodes(); ++id)
            nodeUniquePtrVector_[id]->printNode(out, mappingFromVariableToOriginalVariable_);
    }

    template <typename VarT, typename LiteralT>
    bool Circuit<VarT, LiteralT>::consistencyCheck(const OriginalLiteralSetType& partialAssignmentOriginalLiteralSet,
                                                   const OriginalVariableSetType& forgottenOriginalVariableSet) {
        // The root is not set
        if (!root_.has_value())
            throw Exception::Circuit::RootIsNotSetException();

        CircuitTypeEnum circuitType = getCircuitType();

        // The circuit does not support consistency check
        if (!Other::containInSet(supportConsistencyCheckCircuitTypeSet, circuitType))
            throw Exception::Circuit::CircuitTypeDoesNotSupportQueryException(circuitType, "consistency check");

        // Partial assignment
        LiteralSetType literalSetTmp = remapFromOriginalLiteralToLiteral(partialAssignmentOriginalLiteralSet);
        PartialAssignmentType partialAssignment(literalSetTmp, totalNumberOfVariables_);

        // Forgetting
        VariableSetType forgottenVariableSet = remapFromOriginalVariableToVariable(forgottenOriginalVariableSet);

        // Check collision
        #ifndef NDEBUG
        for (VarT var : Other::sortUnorderedSet(forgottenVariableSet)) {
        #else
        for (VarT var : forgottenVariableSet) {
        #endif
            if (partialAssignment.variableExists(var))
                throw Exception::Circuit::CircuitException("The forgotten variable (" + std::to_string(var) + ") appears in the partial assignment!");
        }

        ConsistencyCheckCacheType cache(getNumberOfNodes());
        return getNodePtr(*root_)->consistencyCheck(partialAssignment, forgottenVariableSet, cache);
    }

    template <typename VarT, typename LiteralT>
    typename Circuit<VarT, LiteralT>::NumberOfModelsType
    Circuit<VarT, LiteralT>::modelCounting(const OriginalLiteralSetType& partialAssignmentOriginalLiteralSet) {
        // The root is not set
        if (!root_.has_value())
            throw Exception::Circuit::RootIsNotSetException();

        CircuitTypeEnum circuitType = getCircuitType();

        // The circuit does not support model counting
        if (!Other::containInSet(supportModelCountingCircuitTypeSet, circuitType))
            throw Exception::Circuit::CircuitTypeDoesNotSupportQueryException(circuitType, "model counting");

        // The circuit is not smooth
        if (!Other::containInSet(smoothCircuitTypeSet, circuitType))
            throw Exception::Circuit::ModelCountingIsNotSupportedWithoutSmoothnessException();

        #if !defined(TEST)
        // Formula leaves
        if (Other::containInSet(formulaLeavesCircuitTypeSet, circuitType))
            std::cerr << "WARNING: the circuit contains formula leaves for which model counting based on enumeration is being used => time complexity is exponential!" << std::endl;
        #endif

        // Partial assignment
        LiteralSetType literalSetTmp = remapFromOriginalLiteralToLiteral(partialAssignmentOriginalLiteralSet);
        PartialAssignmentType partialAssignment(literalSetTmp, totalNumberOfVariables_);

        ModelCountingCacheType cache(getNumberOfNodes());
        getNodePtr(*root_)->modelCounting(partialAssignment, cache);

        assert(Other::containInMap(cache, getNodePtr(*root_)->getId()));

        NumberOfModelsType numberOfModels = std::move(cache[getNodePtr(*root_)->getId()]);

        return numberOfModels;
    }

    template <typename VarT, typename LiteralT>
    typename Circuit<VarT, LiteralT>::NumberOfModelsType
    Circuit<VarT, LiteralT>::modelCountingWithPolynomialDelay(const OriginalLiteralSetType& partialAssignmentOriginalLiteralSet,
                                                              const OriginalVariableSetType& forgottenOriginalVariableSet,
                                                              bool printModels, std::ostream& outModels) {
        // The root is not set
        if (!root_.has_value())
            throw Exception::Circuit::RootIsNotSetException();

        CircuitTypeEnum circuitType = getCircuitType();

        // The circuit does not support consistency check
        if (!Other::containInSet(supportConsistencyCheckCircuitTypeSet, circuitType))
            throw Exception::Circuit::CircuitTypeDoesNotSupportQueryException(circuitType, "consistency check");

        // Partial assignment
        LiteralSetType literalSetTmp = remapFromOriginalLiteralToLiteral(partialAssignmentOriginalLiteralSet);
        PartialAssignmentType partialAssignment(literalSetTmp, totalNumberOfVariables_);

        // Forgetting
        VariableSetType forgottenVariableSet = remapFromOriginalVariableToVariable(forgottenOriginalVariableSet);

        // Check collision
        #ifndef NDEBUG
        for (VarT var : Other::sortUnorderedSet(forgottenVariableSet)) {
        #else
        for (VarT var : forgottenVariableSet) {
        #endif
            if (partialAssignment.variableExists(var))
                throw Exception::Circuit::CircuitException("The forgotten variable (" + std::to_string(var) + ") appears in the partial assignment!");
        }

        VariableSortedVectorType variableSortedVector;
        variableSortedVector.reserve(totalNumberOfVariables_);

        for (VarT var = 1; var <= totalNumberOfVariables_; ++var) {
            // The variable is assigned
            if (partialAssignment.variableExists(var))
                continue;

            // The variable is forgotten
            if (Other::containInSet(forgottenVariableSet, var))
                continue;

            variableSortedVector.emplace_back(var);
        }

        NumberOfModelsType numberOfModels;   // 0
        ConsistencyCheckCacheType cache(getNumberOfNodes());

        // Full assignment and unsatisfiable
        if (variableSortedVector.empty() && !getNodePtr(*root_)->consistencyCheck(partialAssignment, forgottenVariableSet, cache))
            return numberOfModels;

        processModelCountingWithPolynomialDelay(static_cast<VarT>(0), partialAssignment, variableSortedVector, numberOfModels, forgottenVariableSet, cache,
                                                printModels, outModels);

        return numberOfModels;
    }

    template <typename VarT, typename LiteralT>
    template <typename ClauseIdT2>
    bool Circuit<VarT, LiteralT>::clausalEntailmentCheck(const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT2>* formulaPtr) {
        // The root is not set
        if (!root_.has_value())
            throw Exception::Circuit::RootIsNotSetException();

        CircuitTypeEnum circuitType = getCircuitType();

        // The circuit does not support consistency check
        if (!Other::containInSet(supportConsistencyCheckCircuitTypeSet, circuitType))
            throw Exception::Circuit::CircuitTypeDoesNotSupportQueryException(circuitType, "consistency check");

        assert(totalNumberOfVariables_ == formulaPtr->getNumberOfVariablesInOriginalFormula());

        ConsistencyCheckCacheType cache(getNumberOfNodes());
        PartialAssignmentType partialAssignment(totalNumberOfVariables_);

        for (ClauseIdT2 clauseId = 0; clauseId < formulaPtr->getNumberOfOriginalClauses(); ++clauseId) {
            assert(formulaPtr->isClauseUntouched(clauseId));   // clause is untouched

            cache.clear();
            partialAssignment.clear();

            for (auto clauseIt = formulaPtr->beginClause(clauseId); clauseIt != formulaPtr->endClause(); ++clauseIt)
                partialAssignment.addLiteral(!(*clauseIt));

            assert(formulaPtr->getCurrentClauseSize(clauseId) == partialAssignment.getNumberOfAssignedVariables());

            bool result = getNodePtr(*root_)->consistencyCheck(partialAssignment, {}, cache);

            // The clause is not an implicate
            if (result)
                return false;
        }

        return true;
    }

    template <typename VarT, typename LiteralT>
    void Circuit<VarT, LiteralT>::setStatisticsAfterCompilation() const {
        // Statistics
        if (circuitStatisticsPtr_) {
            circuitStatisticsPtr_->circuitSizeNumber.setNumber(static_cast<Statistics::LargeNumberType>(getCircuitSize()));
            circuitStatisticsPtr_->numberOfNodesNumber.setNumber(static_cast<Statistics::LargeNumberType>(getNumberOfNodes()));
            circuitStatisticsPtr_->numberOfEdgesNumber.setNumber(static_cast<Statistics::LargeNumberType>(getNumberOfEdges()));
            circuitStatisticsPtr_->numberOfVariablesNumber.setNumber(static_cast<Statistics::LargeNumberType>(getNumberOfUsedVariables()));
        }
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT>
    void Circuit<VarT, LiteralT>::printCircuitDebug(std::ostream& out) {
        out << "Circuit - " << circuitTypeEnumToString(getCircuitType()) << std::endl
            << "Size: " << std::to_string(getCircuitSize()) << std::endl
            << "Number of edges: " << std::to_string(getNumberOfEdges()) << std::endl
            << "Number of nodes: " << std::to_string(getNumberOfNodes()) << std::endl
            << "Number of leaves: " << std::to_string(getNumberOfLeaves()) << std::endl
            << "Number of inner nodes: " << std::to_string(getNumberOfInnerNodes()) << std::endl
            << "Number of used variables: " << std::to_string(getNumberOfUsedVariables()) << std::endl;

        out << "Root: ";
        if (!root_.has_value())
            out << "not set";
        else
            out << std::to_string(*root_);
        out << std::endl;

        out << "Used variables:";
        for (VarT var = 1; var < usedVariableVector_.size(); ++var) {
            if (usedVariableVector_[var])
                out << " " << std::to_string(var);
        }
        out << std::endl;

        out << "Node types:" << std::endl;
        NodeTypeEnumSortedVectorType nodeTypeKeySortedVector = Other::extractKeysFromMap(nodeTypeCounter_, true);
        for (NodeTypeEnum nodeType : nodeTypeKeySortedVector) {
            IdNodeType numberOfNodesTmp = nodeTypeCounter_[nodeType];
            if (numberOfNodesTmp > 0)
                out << "\t" << Node::nodeTypeEnumToString(nodeType) << ": " << std::to_string(numberOfNodesTmp) << std::endl;
        }
        out << std::endl;

        out << "Nodes:" << std::endl;
        for (IdNodeType id = 0; id < getNumberOfNodes(); ++id) {
            out << std::to_string(id) << ": ";
            nodeUniquePtrVector_[id]->printNodeDebug(out);
        }
        out << std::endl;
    }
    #endif
}   // namespace Hydra::Circuit
