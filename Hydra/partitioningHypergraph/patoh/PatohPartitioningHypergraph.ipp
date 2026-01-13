#pragma once

#include "./PatohPartitioningHypergraph.hpp"

namespace Hydra::PartitioningHypergraph::Patoh {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename PatohPartitioningHypergraph<VarT, LiteralT, ClauseIdT>::VariableSetType
    PatohPartitioningHypergraph<VarT, LiteralT, ClauseIdT>::computeCut(const OccurrenceListStruct& occurrenceListStruct) {
        // Fill xpins and pins
        this->fillXpinsAndPins(occurrenceListStruct, xpins_, pins_);

        // PaToH parameters
        PaToH_Parameters args;
        PaToH_Initialize_Parameters(&args, configuration_.cutTypePatohLibrary,
                                    (static_cast<char32_t>(occurrenceListStruct.variableOrderReusableVector.size()) >= configuration_.numberOfVariablesThreshold) ? configuration_.highNumberOfVariablesSuggestByProblemTypePatohLibrary : configuration_.lowNumberOfVariablesSuggestByProblemTypePatohLibrary);
        args._k = configuration_.kPatohLibrary;
        args.seed = configuration_.seedPatohLibrary;
        // args.balance = configuration_.balancePatohLibrary;
        // args.final_imbal = configuration_.finalImbalPatohLibrary;

        // Check the parameters
        assert(PaToH_Check_User_Parameters(&args, 1) == 0);   // indicated no error in the parameters

        // Vertex weights
        VertexWeightVectorType& vertexWeightVector = this->createVertexWeightVector(occurrenceListStruct);

        PaToH_Alloc(&args, static_cast<int>(occurrenceListStruct.numberOfDifferentClausesInOccurrenceList),
                    static_cast<int>(occurrenceListStruct.variableOrderReusableVector.size()), 1,
                    vertexWeightVector.empty() ? nullptr : vertexWeightVector.data(), nullptr,
                    xpins_.data(), pins_.data());

        // Partvec
        this->partvec_.clear();
        this->partvec_.resize(occurrenceListStruct.numberOfDifferentClausesInOccurrenceList, -1);

        int cutSize;
        std::fill(partweights_.begin(), partweights_.end(), 0);

        // Pre-assigned clauses
        const PartitionNumberVectorMapType& preassignmentOfClauseIndicesVectorMap = this->createPreassignmentOfClauseIndices(occurrenceListStruct,
                                                                                                                             configuration_.kPatohLibrary);
        for (std::size_t index : preassignmentOfClauseIndicesVectorMap.getAddedKeyVector()) {
            assert(preassignmentOfClauseIndicesVectorMap[index] >= 0);
            assert(preassignmentOfClauseIndicesVectorMap[index] < configuration_.kPatohLibrary);   // partition number is valid

            this->partvec_[index] = preassignmentOfClauseIndicesVectorMap[index];
        }

        PaToH_Part(&args, static_cast<int>(occurrenceListStruct.numberOfDifferentClausesInOccurrenceList),
                   static_cast<int>(occurrenceListStruct.variableOrderReusableVector.size()), 1, 1,
                   vertexWeightVector.empty() ? nullptr : vertexWeightVector.data(), nullptr,
                   xpins_.data(), pins_.data(), nullptr, this->partvec_.data(), partweights_.data(), &cutSize);

        // Extract the cut
        VariableSetType cut = this->extractCut(occurrenceListStruct, this->partvec_);

        // #ifndef NDEBUG
        // if (cut.empty()) {
        //     for (PartitionNumberType partitionNumber : this->partvec_)
        //         assert(partitionNumber == 0);
        // }
        // #endif

        PaToH_Free();

        return cut;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void PatohPartitioningHypergraph<VarT, LiteralT, ClauseIdT>::processPrintPartitioningHypergraphDebug(std::ostream& out) const {
        // Configuration
        out << "kPatohLibrary: " << std::to_string(configuration_.kPatohLibrary) << std::endl;
        out << "cutTypePatohLibrary: " << std::to_string(configuration_.cutTypePatohLibrary) << std::endl;
        out << "numberOfVariablesThreshold: " << std::to_string(configuration_.numberOfVariablesThreshold) << std::endl;
        out << "lowNumberOfVariablesSuggestByProblemTypePatohLibrary: " << std::to_string(configuration_.lowNumberOfVariablesSuggestByProblemTypePatohLibrary) << std::endl;
        out << "highNumberOfVariablesSuggestByProblemTypePatohLibrary: " << std::to_string(configuration_.highNumberOfVariablesSuggestByProblemTypePatohLibrary) << std::endl;
        out << "seedPatohLibrary: " << std::to_string(configuration_.seedPatohLibrary) << std::endl;
        out << "finalImbalPatohLibrary: " << std::to_string(configuration_.finalImbalPatohLibrary) << std::endl;
        out << "balancePatohLibrary: " << std::to_string(configuration_.balancePatohLibrary) << std::endl;
    }
    #endif
}   // namespace Hydra::PartitioningHypergraph::Patoh
