#pragma once

#include <cassert>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <string>
#include <thread>
#include <vector>

#include "Hydra/other/Other.hpp"
#include "Hydra/other/operatingSystem/OperatingSystem.hpp"
#include "Hydra/partitioningHypergraph/PartitioningHypergraphAbstract.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"
#include "Hydra/partitioningHypergraph/exceptions/PartitioningHypergraphException.hpp"

#include "Hydra/compiler/enums/IgnorePureLiteralTypeEnum.hpp"
#include "Hydra/partitioningHypergraph/enums/PartitioningHypergraphSoftwareEnum.hpp"

#include "Hydra/partitioningHypergraph/hmetis/HmetisPartitioningHypergraph.tpp"

namespace Hydra::PartitioningHypergraph::Hmetis {

    /**
     * hMETIS (final class)
     * Supported operating systems: Windows
     * Exceptions:
     *      CannotCreateFileException
     *      FileDoesNotExistException
     *      FileCannotBeOpenedException
     *      InvalidParsedPartitionHmetisException
     *      ShmetisExeCannotBeFoundHmetisException
     *      FileContainingSomethingCannotBeFoundHmetisException
     *      PartitioningHypergraphSoftwareDoesNotSupportThisOperatingSystemException
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class HmetisPartitioningHypergraph final : public PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT> {
    private:
        using VariableSetType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableSetType;
        using VariableVectorType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::VariableVectorType;
        using PartitionNumberType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::PartitionNumberType;
        using PartitionNumberVectorMapType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::PartitionNumberVectorMapType;
        using FormulaRepresentationAbstractPtrType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;
        using PartitioningHypergraphStatisticsPtrType = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::PartitioningHypergraphStatisticsPtrType;

    private:
        using OccurrenceListStruct = typename PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>::OccurrenceListStruct;

    private:
        using PinType = int;
        using XpinType = int;
        using PinVectorType = std::vector<PinType>;
        using XpinVectorType = std::vector<XpinType>;

    public:
        HmetisPartitioningHypergraph(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr,
                                     bool allowEmptyHypergraphCut, bool allowSingletonHyperedge,
                                     IgnorePureLiteralTypeEnum ignorePureLiteralType, VertexWeightTypeEnum vertexWeightType,
                                     const HmetisPartitioningHypergraphConfiguration& configuration = HmetisPartitioningHypergraphConfiguration(),
                                     PartitioningHypergraphStatisticsPtrType partitioningHypergraphStatisticsPtr = nullptr)
            : PartitioningHypergraphAbstract<VarT, LiteralT, ClauseIdT>(formulaRepresentationAbstractPtr,
                                                                        allowEmptyHypergraphCut, allowSingletonHyperedge,
                                                                        PartitioningHypergraphSoftwareEnum::HMETIS,
                                                                        ignorePureLiteralType, vertexWeightType,
                                                                        partitioningHypergraphStatisticsPtr),
              pins_(), xpins_(), command_(), commandFix_(), fixFileName_(), partitionFileName_(), hypergraphFileName_(), configuration_(configuration) {
            // This operating system is not supported
            if (!Other::OperatingSystem::isWindows())
                throw Exception::PartitioningHypergraph::PartitioningHypergraphSoftwareDoesNotSupportThisOperatingSystemException(PartitioningHypergraphSoftwareEnum::HMETIS);

            // Generate a random number
            std::srand(static_cast<unsigned>(std::time(nullptr)));
            int randomNumber = std::rand();

            // Check if shmetis.exe exists
            if (!std::filesystem::exists(SHMETIS_EXE_FILE_NAME_))
                throw Exception::PartitioningHypergraph::ShmetisExeCannotBeFoundHmetisException();

            hypergraphFileName_ = HYPERGRAPH_FILE_NAME_ + std::to_string(randomNumber);
            fixFileName_ = HYPERGRAPH_FILE_NAME_ + "fix_" + std::to_string(randomNumber);
            partitionFileName_ = hypergraphFileName_ + ".part." + std::to_string(configuration_.NpartsHmetisLibrary);

            command_ = SHMETIS_EXE_FILE_NAME_ + " " + hypergraphFileName_ + " " + std::to_string(configuration_.NpartsHmetisLibrary) + " " +
                       std::to_string(configuration_.UBfactorHmetisLibrary) + " > " + NUL_FILE_NAME_ + " 2>&1";

            commandFix_ = SHMETIS_EXE_FILE_NAME_ + " " + hypergraphFileName_ + " " + fixFileName_ + " " + std::to_string(configuration_.NpartsHmetisLibrary) +
                          " " + std::to_string(configuration_.UBfactorHmetisLibrary) + " > " + NUL_FILE_NAME_ + " 2>&1";

            pins_.reserve(this->formulaRepresentationAbstractPtr_->getOriginalFormulaSize());
            xpins_.reserve(this->formulaRepresentationAbstractPtr_->getNumberOfVariablesInOriginalFormulaUsedForIndexing());
        }

        virtual ~HmetisPartitioningHypergraph() noexcept {
            try {
                std::filesystem::remove(fixFileName_);
                std::filesystem::remove(partitionFileName_);
                std::filesystem::remove(hypergraphFileName_);
            }
            catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "~HmetisPartitioningHypergraph" << std::endl;
                std::cerr << e.what() << std::endl;
            }
        }

    private:
        PinVectorType pins_;
        XpinVectorType xpins_;

        std::string command_;      // hypergraph
        std::string commandFix_;   // hypergraph + fix
        std::string fixFileName_;
        std::string partitionFileName_;
        std::string hypergraphFileName_;
        HmetisPartitioningHypergraphConfiguration configuration_;

        inline static const std::string HYPERGRAPH_FILE_NAME_ = "hypergraph_hmetis_";
        #ifdef __CYGWIN__
        inline static const std::string NUL_FILE_NAME_ = "/dev/null";
        inline static const std::string SHMETIS_EXE_FILE_NAME_ = R"(./shmetis.exe)";
        #else
        inline static const std::string NUL_FILE_NAME_ = "NUL";
        inline static const std::string SHMETIS_EXE_FILE_NAME_ = R"(.\shmetis.exe)";
        #endif

        inline static constexpr int S_MAX_NUMBER_OF_ITERATIONS_TO_WAIT_FOR_EXISTENCE_OF_FILE_ = 5;

    private:
        /**
         * Passively wait until the file exists or timeout (that is, the maximum number of iterations is reached)
         * Note: one iteration waits for 50ms
         * Note: max S_MAX_NUMBER_OF_ITERATIONS_TO_WAIT_FOR_EXISTENCE_OF_FILE_ iterations
         * @param fileName a file name
         * @return true if the file exists. Otherwise, false is returned.
         */
        bool waitUntilFileExistsOrTimeout(const std::string& fileName) const;

        /**
         * Create a file containing the hypergraph
         * File name: hypergraphFileName_
         * @param occurrenceListStruct an occurrence list structure
         * @throw CannotCreateFileException if the file cannot be created
         */
        void createHypergraphFile(const OccurrenceListStruct& occurrenceListStruct);

        /**
         * Create a file containing the pre-assignment
         * File name: fixFileName_
         * @param occurrenceListStruct an occurrence list structure
         * @param preassignmentOfClauseIndicesVectorMap a vector map from clause indices to partition numbers
         * @throw CannotCreateFileException if the file cannot be created
         */
        void createFixFile(const OccurrenceListStruct& occurrenceListStruct, const PartitionNumberVectorMapType& preassignmentOfClauseIndicesVectorMap) const;

        /**
         * Parse the file containing the partitioning
         * File name: partitionFileName_
         * @param numberOfVertices the number of vertices
         * @throw FileDoesNotExistException if the file does not exist
         * @throw FileCannotBeOpenedException if the file cannot be opened
         * @throw InvalidParsedPartitionHmetisException if any partition is invalid
         */
        void parsePartitionFile(ClauseIdT numberOfVertices);

    private:
        VariableSetType computeCut(const OccurrenceListStruct& occurrenceListStruct) override;

    #ifndef NDEBUG
    private:
        void processPrintPartitioningHypergraphDebug(std::ostream& out) const override;
    #endif
    };
}   // namespace Hydra::PartitioningHypergraph::Hmetis

#include "./HmetisPartitioningHypergraph.ipp"
