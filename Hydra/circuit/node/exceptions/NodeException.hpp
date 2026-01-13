#pragma once

#include <sstream>
#include <string>

#include "Hydra/circuit/node/innerNode/InnerNodeAbstract.hpp"
#include "Hydra/circuit/node/leafNode/formulaLeaf/FormulaLeafAbstract.hpp"

#include "Hydra/circuit/exceptions/CircuitException.hpp"

#include "Hydra/circuit/node/enums/NodeTypeEnum.hpp"

namespace Hydra::Exception::Circuit::Node {

    /**
     * Node exception (main)
     */
    class NodeException : public CircuitException {
    public:
        explicit NodeException(const std::string& message)
            : CircuitException(message) { }

        explicit NodeException(std::string&& message)
            : CircuitException(std::move(message)) { }

        NodeException(const std::string& message, const std::string& functionName)
            : CircuitException(message, functionName) { }
    };

    /**
     * Formula is not Krom-C
     */
    template <typename VarT, typename LiteralT>
    class FormulaIsNotKromCException : public NodeException {
    public:
        explicit FormulaIsNotKromCException(const Hydra::Circuit::Node::FormulaLeafAbstract<VarT, LiteralT>* formulaLeaf)
            : NodeException("The formula is not Krom-C!") {
            std::stringstream stringStreamTmp;
            formulaLeaf->printFormulaInDimacsCnfFormat(stringStreamTmp);
            message_ = message_ + "\n" + stringStreamTmp.str();
        }
    };

    /**
     * Formula is not renH-C
     */
    template <typename VarT, typename LiteralT>
    class FormulaIsNotRenHCException : public NodeException {
    public:
        explicit FormulaIsNotRenHCException(const Hydra::Circuit::Node::FormulaLeafAbstract<VarT, LiteralT>* formulaLeaf)
            : NodeException("The formula is not renH-C!") {
            std::stringstream stringStreamTmp;
            formulaLeaf->printFormulaInDimacsCnfFormat(stringStreamTmp);
            message_ = message_ + "\n" + stringStreamTmp.str();
        }
    };

    /**
     * Inner node does not satisfy the particular property - (classical / Bella) decomposability, smoothness, ...
     */
    template <typename VarT, typename LiteralT>
    class InnerNodeDoesNotSatisfyPropertyException : public NodeException {
    public:
        InnerNodeDoesNotSatisfyPropertyException(const std::string& propertyName,
                                                 Hydra::Circuit::Node::InnerNodeAbstract<VarT, LiteralT>* innerNode,
                                                 [[maybe_unused]] bool printChildrenVariables = true,
                                                 [[maybe_unused]] bool printChildrenLiterals = true)
            : NodeException("The node (" + std::to_string(innerNode->getId()) + ") does not satisfy the " + propertyName + " property!") {
            #ifndef NDEBUG
            std::stringstream stringStreamTmp;

            // Print children's variables
            if (printChildrenVariables)
                innerNode->printChildrenVariablesDebug(stringStreamTmp);

            // Print children's literals
            if (printChildrenLiterals)
                innerNode->printChildrenLiteralsDebug(stringStreamTmp);

            message_ = message_ + "\n" + stringStreamTmp.str();
            #endif
        }
    };

    /**
     * OR inner nodes do not support the model counting query
     */
    class OrInnerNodesDoNotSupportModelCountingException : public NodeException {
    public:
        OrInnerNodesDoNotSupportModelCountingException()
            : NodeException("OR inner nodes do not support the model counting query!") { }
    };

    /**
     * Node type does not support the copy subcircuit operation
     */
    class NodeTypeDoesNotSupportCopySubcircuitOperationException : public NodeException {
    public:
        explicit NodeTypeDoesNotSupportCopySubcircuitOperationException(Hydra::Circuit::Node::NodeTypeEnum nodeType)
            : NodeException("The node type (" + Hydra::Circuit::Node::nodeTypeEnumToString(nodeType) +
                            ") does not support the copy subcircuit operation!") { }
    };
}   // namespace Hydra::Exception::Circuit::Node
