#pragma once

#include <cassert>
#include <string>

#include "Hydra/other/operatingSystem/OperatingSystem.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/other/operatingSystem/enums/OperatingSystemTypeEnum.hpp"
#include "Hydra/partitioningHypergraph/enums/PartitioningHypergraphSoftwareEnum.hpp"

namespace Hydra::Exception::PartitioningHypergraph {

    /**
     * Partitioning hypergraph exception (main)
     */
    class PartitioningHypergraphException : public CompilerException {
    public:
        explicit PartitioningHypergraphException(const std::string& message)
            : CompilerException(message) { }

        explicit PartitioningHypergraphException(std::string&& message)
            : CompilerException(std::move(message)) { }

        PartitioningHypergraphException(const std::string& message, const std::string& functionName)
            : CompilerException(message, functionName) { }
    };

    /**
     * Partitioning hypergraph software does not support this operating system
     */
    class PartitioningHypergraphSoftwareDoesNotSupportThisOperatingSystemException : public PartitioningHypergraphException {
    public:
        explicit PartitioningHypergraphSoftwareDoesNotSupportThisOperatingSystemException(Hydra::PartitioningHypergraph::PartitioningHypergraphSoftwareEnum partitioningHypergraphSoftware)
            : PartitioningHypergraphException("The partitioning hypergraph software (" + Hydra::PartitioningHypergraph::partitioningHypergraphSoftwareEnumToString(partitioningHypergraphSoftware) + ") does not support this operating system (" + Hydra::Other::OperatingSystem::operatingSystemTypeEnumToString(Hydra::Other::OperatingSystem::getOperatingSystem()) + ")!") { }
    };

    /**
     * Invalid parsed partition (hMETIS)
     */
    class InvalidParsedPartitionHmetisException : public PartitioningHypergraphException {
    public:
        explicit InvalidParsedPartitionHmetisException(const std::string& parsedLine)
            : PartitioningHypergraphException("The parsed partition (" + parsedLine + ") is invalid!") { }
    };

    /**
     * shmetis.exe cannot be found (hMETIS)
     */
    class ShmetisExeCannotBeFoundHmetisException : public PartitioningHypergraphException {
    public:
        ShmetisExeCannotBeFoundHmetisException()
            : PartitioningHypergraphException("shmetis.exe cannot be found!") { }
    };

    /**
     * File containing the hypergraph/pre-assignment cannot be found (hMETIS)
     */
    class FileContainingSomethingCannotBeFoundHmetisException : public PartitioningHypergraphException {
    public:
        FileContainingSomethingCannotBeFoundHmetisException(const std::string& fileName, const std::string& content)
            : PartitioningHypergraphException("The file (" + fileName + ") containing the " + content + " cannot be found!") {
            assert(content == "hypergraph" || content == "pre-assignment");
        }
    };
}   // namespace Hydra::Exception::PartitioningHypergraph
