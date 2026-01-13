#pragma once

#include <string>

namespace Hydra::PartitioningHypergraph {

    enum class VertexWeightTypeEnum {
        NONE,

        STANDARD,
        CLAUSE_LENGTH
    };

    /**
     * @return true if vertex weights are used. Otherwise, false is returned.
     */
    inline bool isVertexWeightUsed(VertexWeightTypeEnum vertexWeightType) noexcept {
        return (vertexWeightType != VertexWeightTypeEnum::NONE);
    }

    inline std::string vertexWeightTypeEnumToString(VertexWeightTypeEnum vertexWeightType) noexcept {
        switch (vertexWeightType) {
            case VertexWeightTypeEnum::NONE:
                return "none";
            case VertexWeightTypeEnum::STANDARD:
                return "standard";
            case VertexWeightTypeEnum::CLAUSE_LENGTH:
                return "clause length";
            default:
                return "name not set";
        }
    }
}   // namespace Hydra::PartitioningHypergraph
