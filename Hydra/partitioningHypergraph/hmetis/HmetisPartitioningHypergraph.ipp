#pragma once

#include "./HmetisPartitioningHypergraph.hpp"

namespace Hydra::PartitioningHypergraph::Hmetis {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    bool HmetisPartitioningHypergraph<VarT, LiteralT, ClauseIdT>::waitUntilFileExistsOrTimeout(const std::string& fileName) const {
        int counter = 0;

        while (true) {
            // File exists
            if (std::filesystem::exists(fileName))
                return true;

            // Timeout
            if (++counter == S_MAX_NUMBER_OF_ITERATIONS_TO_WAIT_FOR_EXISTENCE_OF_FILE_)
                return false;

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void HmetisPartitioningHypergraph<VarT, LiteralT, ClauseIdT>::createHypergraphFile(const OccurrenceListStruct& occurrenceListStruct) {
        // Fill xpins and pins
        this->fillXpinsAndPins(occurrenceListStruct, xpins_, pins_);

        {
            std::ofstream fileStream(hypergraphFileName_, std::ios::out);

            // File cannot be created
            if (!fileStream.is_open())
                throw Exception::CannotCreateFileException(hypergraphFileName_);

            fileStream << std::to_string(occurrenceListStruct.variableOrderReusableVector.size()) << " "
                       << std::to_string(occurrenceListStruct.numberOfDifferentClausesInOccurrenceList);

            XpinType xpinIndex = 0;
            for (XpinType xpin : xpins_) {
                while (xpinIndex < xpin) {
                    fileStream << std::to_string(1 + pins_[static_cast<typename PinVectorType::size_type>(xpinIndex)]) << " ";
                    ++xpinIndex;
                }

                fileStream << std::endl;
            }
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void HmetisPartitioningHypergraph<VarT, LiteralT, ClauseIdT>::createFixFile(const OccurrenceListStruct& occurrenceListStruct,
                                                                                const PartitionNumberVectorMapType& preassignmentOfClauseIndicesVectorMap) const {
        {
            std::ofstream fileStream(fixFileName_, std::ios::out);

            // File cannot be created
            if (!fileStream.is_open())
                throw Exception::CannotCreateFileException(fixFileName_);

            for (ClauseIdT i = 0; i < occurrenceListStruct.numberOfDifferentClausesInOccurrenceList; ++i) {
                // The clause is preassigned
                if (preassignmentOfClauseIndicesVectorMap.contains(i))
                    fileStream << std::to_string(preassignmentOfClauseIndicesVectorMap[i]) << std::endl;
                // The clause is NOT preassigned
                else
                    fileStream << std::to_string(-1) << std::endl;
            }
        }
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void HmetisPartitioningHypergraph<VarT, LiteralT, ClauseIdT>::parsePartitionFile(ClauseIdT numberOfVertices) {
        // File does not exist
        if (!std::filesystem::exists(partitionFileName_))
            throw Exception::FileDoesNotExistException(partitionFileName_);

        std::size_t partvecIndex = 0;
        this->partvec_.resize(numberOfVertices);

        {
            std::ifstream fileStream(partitionFileName_, std::ios::in);

            // File cannot be opened
            if (!fileStream.is_open())
                throw Exception::FileCannotBeOpenedException(partitionFileName_);

            std::string line;
            while (getline(fileStream, line)) {
                try {
                    PartitionNumberType parsedPartition = std::stoi(line);

                    assert((parsedPartition >= 0) && (parsedPartition < configuration_.NpartsHmetisLibrary));   // partition number is valid

                    this->partvec_[partvecIndex] = parsedPartition;
                    ++partvecIndex;
                }
                catch (...) {
                    throw Exception::PartitioningHypergraph::InvalidParsedPartitionHmetisException(line);
                }
            }
        }

        assert(static_cast<ClauseIdT>(partvecIndex) == numberOfVertices);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    typename HmetisPartitioningHypergraph<VarT, LiteralT, ClauseIdT>::VariableSetType
    HmetisPartitioningHypergraph<VarT, LiteralT, ClauseIdT>::computeCut(const OccurrenceListStruct& occurrenceListStruct) {
        // Pre-assigned clauses
        // const PartitionNumberVectorMapType& preassignmentOfClauseIndicesVectorMap = this->createPreassignmentOfClauseIndices(occurrenceListStruct,
        //                                                                                                                      configuration_.NpartsHmetisLibrary);

        // Create the hypergraph and fix files
        createHypergraphFile(occurrenceListStruct);
        // createFixFile(occurrenceListStruct, preassignmentOfClauseIndicesVectorMap);

        if (!waitUntilFileExistsOrTimeout(hypergraphFileName_))
            throw Exception::PartitioningHypergraph::FileContainingSomethingCannotBeFoundHmetisException(hypergraphFileName_, "hypergraph");
        // if (!waitUntilFileExistsOrTimeout(fixFileName_))
        //     throw Exception::PartitioningHypergraph::FileContainingSomethingCannotBeFoundHmetisException(fixFileName_, "pre-assignment");

        assert(std::filesystem::exists(hypergraphFileName_));   // hypergraph file exists
        // assert(std::filesystem::exists(fixFileName_));       // fix file exists

        [[maybe_unused]] int exitCode = std::system(command_.data());
        // assert(exitCode == 0);  // succeed

        // Cut does not exist
        if (!waitUntilFileExistsOrTimeout(partitionFileName_)) {
            // Remove all auxiliary files
            std::filesystem::remove(fixFileName_);
            std::filesystem::remove(hypergraphFileName_);

            return {};
        }

        // Parse the partition file
        parsePartitionFile(occurrenceListStruct.numberOfDifferentClausesInOccurrenceList);

        // Extract the cut
        VariableSetType cut = this->extractCut(occurrenceListStruct, this->partvec_);

        // #ifndef NDEBUG
        // if (cut.empty()) {
        //     for (PartitionNumberType partitionNumber : this->partvec_)
        //         assert(partitionNumber == 0);
        // }
        // #endif

        // Remove all auxiliary files
        std::filesystem::remove(fixFileName_);
        std::filesystem::remove(partitionFileName_);
        std::filesystem::remove(hypergraphFileName_);

        return cut;
    }

    #ifndef NDEBUG
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void HmetisPartitioningHypergraph<VarT, LiteralT, ClauseIdT>::processPrintPartitioningHypergraphDebug(std::ostream& out) const {
        out << "Hypergraph file name: " << hypergraphFileName_ << std::endl;
        out << "Fix file name: " << fixFileName_ << std::endl;
        out << "Partition file name: " << partitionFileName_ << std::endl;

        // Configuration
        out << "NpartsHmetisLibrary: " << std::to_string(configuration_.NpartsHmetisLibrary) << std::endl;
        out << "UBfactorHmetisLibrary: " << std::to_string(configuration_.UBfactorHmetisLibrary) << std::endl;
    }
    #endif
}   // namespace Hydra::PartitioningHypergraph::Hmetis
