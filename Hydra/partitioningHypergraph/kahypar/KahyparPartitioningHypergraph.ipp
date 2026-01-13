#pragma once

#include "./KahyparPartitioningHypergraph.hpp"

namespace Hydra::PartitioningHypergraph::Kahypar {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename KahyparPartitioningHypergraph<VarT, LiteralT, ClauseIdT>::VariableSetType
    KahyparPartitioningHypergraph<VarT, LiteralT, ClauseIdT>::computeCut(const OccurrenceListStruct& occurrenceListStruct) {
        // Fill xpins and pins
        this->fillXpinsAndPins(occurrenceListStruct, xpins_, pins_);

        // Vertex weights
        const VertexWeightVectorType& vertexWeightVector = this->createVertexWeightVector(occurrenceListStruct);

        kahypar_hyperedge_weight_t objective = 0;

        // Partvec
        this->partvec_.clear();
        this->partvec_.resize(occurrenceListStruct.numberOfDifferentClausesInOccurrenceList, -1);

        // Pre-assigned clauses
        const PartitionNumberVectorMapType& preassignmentOfClauseIndicesVectorMap = this->createPreassignmentOfClauseIndices(occurrenceListStruct,
                                                                                                                             configuration_.kKahyparLibrary);
        for (std::size_t index : preassignmentOfClauseIndicesVectorMap.getAddedKeyVector()) {
            assert(preassignmentOfClauseIndicesVectorMap[index] >= 0);
            assert(preassignmentOfClauseIndicesVectorMap[index] < configuration_.kKahyparLibrary);   // partition number is valid

            this->partvec_[index] = preassignmentOfClauseIndicesVectorMap[index];
        }

        kahypar_partition(static_cast<kahypar_hypernode_id_t>(occurrenceListStruct.numberOfDifferentClausesInOccurrenceList),
                          static_cast<kahypar_hyperedge_id_t>(occurrenceListStruct.variableOrderReusableVector.size()),
                          configuration_.imbalanceFactorKahyparLibrary, configuration_.kKahyparLibrary,
                          vertexWeightVector.empty() ? nullptr : vertexWeightVector.data(), nullptr,
                          xpins_.data(), pins_.data(), &objective, kahyparContextPtr_, this->partvec_.data());

        // Extract the cut
        VariableSetType cut = this->extractCut(occurrenceListStruct, this->partvec_);

        return cut;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void KahyparPartitioningHypergraph<VarT, LiteralT, ClauseIdT>::processPrintPartitioningHypergraphDebug(std::ostream& out) const {
        // Configuration
        out << "kKahyparLibrary: " << std::to_string(configuration_.kKahyparLibrary) << std::endl;
        out << "seedKahyparLibrary: " << std::to_string(configuration_.seedKahyparLibrary) << std::endl;
        out << "imbalanceFactorKahyparLibrary: " << std::to_string(configuration_.imbalanceFactorKahyparLibrary) << std::endl;
    }
    #endif
}   // namespace Hydra::PartitioningHypergraph::Kahypar
