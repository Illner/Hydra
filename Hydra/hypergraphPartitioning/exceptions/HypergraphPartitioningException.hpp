#pragma once

#include <cassert>
#include <string>

#include "Hydra/other/operatingSystem/OperatingSystem.hpp"

#include "Hydra/compiler/exceptions/CompilerException.hpp"

#include "Hydra/hypergraphPartitioning/enums/HypergraphPartitioningSoftwareEnum.hpp"
#include "Hydra/other/operatingSystem/enums/OperatingSystemTypeEnum.hpp"

namespace Hydra::Exception::HypergraphPartitioning {

    /**
     * Hypergraph partitioning exception (main)
     */
    class HypergraphPartitioningException : public CompilerException {
    public:
        explicit HypergraphPartitioningException(const std::string& message)
            : CompilerException(message) { }

        explicit HypergraphPartitioningException(std::string&& message)
            : CompilerException(std::move(message)) { }

        HypergraphPartitioningException(const std::string& message, const std::string& functionName)
            : CompilerException(message, functionName) { }
    };

    /**
     * Hypergraph partitioning software does not support this operating system
     */
    class HypergraphPartitioningSoftwareDoesNotSupportThisOperatingSystemException : public HypergraphPartitioningException {
    public:
        explicit HypergraphPartitioningSoftwareDoesNotSupportThisOperatingSystemException(Hydra::HypergraphPartitioning::HypergraphPartitioningSoftwareEnum hypergraphPartitioningSoftware)
            : HypergraphPartitioningException("The hypergraph partitioning software (" + Hydra::HypergraphPartitioning::hypergraphPartitioningSoftwareEnumToString(hypergraphPartitioningSoftware) + ") does not support this operating system (" + Hydra::Other::OperatingSystem::operatingSystemTypeEnumToString(Hydra::Other::OperatingSystem::getOperatingSystem()) + ")!") { }
    };

    /**
     * Invalid parsed partition (hMETIS)
     */
    class InvalidParsedPartitionHmetisException : public HypergraphPartitioningException {
    public:
        explicit InvalidParsedPartitionHmetisException(const std::string& parsedLine)
            : HypergraphPartitioningException("The parsed partition (" + parsedLine + ") is invalid!") { }
    };

    /**
     * shmetis.exe cannot be found (hMETIS)
     */
    class ShmetisExeCannotBeFoundHmetisException : public HypergraphPartitioningException {
    public:
        ShmetisExeCannotBeFoundHmetisException()
            : HypergraphPartitioningException("shmetis.exe cannot be found!") { }
    };

    /**
     * File containing the hypergraph/pre-assignment cannot be found (hMETIS)
     */
    class FileContainingSomethingCannotBeFoundHmetisException : public HypergraphPartitioningException {
    public:
        FileContainingSomethingCannotBeFoundHmetisException(const std::string& fileName, const std::string& content)
            : HypergraphPartitioningException("The file (" + fileName + ") containing the " + content + " cannot be found!") {
            assert(content == "hypergraph" || content == "pre-assignment");
        }
    };
}   // namespace Hydra::Exception::HypergraphPartitioning
