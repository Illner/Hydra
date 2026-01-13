#pragma once

#include <string>

#include "Hydra/other/hashMap/HashMap.hpp"

namespace Hydra::Circuit::Node {

    enum class NodeTypeEnum {
        // Leaves
        LITERAL_LEAF,
        CONSTANT_LEAF,

        // Formula leaves
        PC_LEAF,
        Krom_C_LEAF,
        renH_C_LEAF,
        Horn_C_LEAF,
        anti_Horn_C_LEAF,

        // Inner nodes
        AND_INNER_NODE,
        OR_INNER_NODE,
        BINARY_OR_INNER_NODE,
        MAPPING_INNER_NODE
    };

    using NodeTypeEnumSetType = Other::HashMap::SetType<NodeTypeEnum>;

    const inline NodeTypeEnumSetType innerNodeTypeSet { NodeTypeEnum::AND_INNER_NODE,
                                                        NodeTypeEnum::OR_INNER_NODE,
                                                        NodeTypeEnum::BINARY_OR_INNER_NODE,
                                                        NodeTypeEnum::MAPPING_INNER_NODE };

    const inline NodeTypeEnumSetType leafNodeTypeSet { NodeTypeEnum::LITERAL_LEAF,
                                                       NodeTypeEnum::CONSTANT_LEAF,
                                                       // Formula leaves
                                                       NodeTypeEnum::PC_LEAF,
                                                       NodeTypeEnum::Krom_C_LEAF,
                                                       NodeTypeEnum::renH_C_LEAF,
                                                       NodeTypeEnum::Horn_C_LEAF,
                                                       NodeTypeEnum::anti_Horn_C_LEAF };

    const inline NodeTypeEnumSetType formulaLeafNodeTypeSet { NodeTypeEnum::PC_LEAF,
                                                              NodeTypeEnum::Krom_C_LEAF,
                                                              NodeTypeEnum::renH_C_LEAF,
                                                              NodeTypeEnum::Horn_C_LEAF,
                                                              NodeTypeEnum::anti_Horn_C_LEAF };

    const inline NodeTypeEnumSetType andInnerNodeTypeSet { NodeTypeEnum::AND_INNER_NODE };

    const inline NodeTypeEnumSetType orInnerNodeTypeSet { NodeTypeEnum::OR_INNER_NODE,
                                                          NodeTypeEnum::BINARY_OR_INNER_NODE };

    inline std::string nodeTypeEnumToString(NodeTypeEnum nodeType) noexcept {
        switch (nodeType) {
            case NodeTypeEnum::LITERAL_LEAF:
                return "literal leaf";
            case NodeTypeEnum::CONSTANT_LEAF:
                return "constant leaf";
            case NodeTypeEnum::PC_LEAF:
                return "PC leaf";
            case NodeTypeEnum::Krom_C_LEAF:
                return "Krom-C leaf";
            case NodeTypeEnum::renH_C_LEAF:
                return "renH-C leaf";
            case NodeTypeEnum::Horn_C_LEAF:
                return "Horn-C leaf";
            case NodeTypeEnum::anti_Horn_C_LEAF:
                return "anti-Horn-C leaf";
            case NodeTypeEnum::AND_INNER_NODE:
                return "AND inner node";
            case NodeTypeEnum::OR_INNER_NODE:
                return "OR inner node";
            case NodeTypeEnum::BINARY_OR_INNER_NODE:
                return "binary OR inner node";
            case NodeTypeEnum::MAPPING_INNER_NODE:
                return "mapping inner node";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::Circuit::Node
