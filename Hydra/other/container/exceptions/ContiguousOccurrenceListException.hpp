#pragma once

#include "Hydra/formula/Literal.hpp"

#include "Hydra/other/container/exceptions/ContainerException.hpp"

namespace Hydra::Exception::Container::ContiguousOccurrenceList {

    /**
     * Contiguous occurrence list exception (main)
     */
    class ContiguousOccurrenceListException : public ContainerException {
    public:
        explicit ContiguousOccurrenceListException(const std::string& message)
            : ContainerException(message) { }

        explicit ContiguousOccurrenceListException(std::string&& message)
            : ContainerException(std::move(message)) { }
    };

    /**
     * Overflow
     */
    template <typename VarT, typename LiteralT>
    class OverflowException : public ContiguousOccurrenceListException {
    public:
        OverflowException(LiteralT literalT, std::size_t offset, std::size_t endOffset)
            : ContiguousOccurrenceListException("Overflow (literal: " +
                                                Hydra::Formula::createLiteralFromLiteralT<VarT, LiteralT>(literalT).toString() +
                                                ", literalT: " + std::to_string(literalT) +
                                                ", offset: " + std::to_string(offset) +
                                                ", end offset: " + std::to_string(endOffset) + ")!") { }
    };

    /**
     * Attempt to remove an occurrence that does not exist
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class AttemptToRemoveOccurrenceDoesNotExistException : public ContiguousOccurrenceListException {
    public:
        AttemptToRemoveOccurrenceDoesNotExistException(LiteralT literalT, ClauseIdT clauseId)
            : ContiguousOccurrenceListException("Attempt to remove an occurrence that does not exist (literal: " +
                                                Hydra::Formula::createLiteralFromLiteralT<VarT, LiteralT>(literalT).toString() +
                                                ", literalT: " + std::to_string(literalT) +
                                                ", clause ID: " + std::to_string(clauseId) + ")!") { }
    };

    /**
     * Attempt to add a duplicate occurrence
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class AttemptToAddDuplicateOccurrenceException : public ContiguousOccurrenceListException {
    public:
        AttemptToAddDuplicateOccurrenceException(LiteralT literalT, ClauseIdT clauseId, bool complementaryLiteral)
            : ContiguousOccurrenceListException("Attempt to add a duplicate occurrence (literal: " +
                                                Hydra::Formula::createLiteralFromLiteralT<VarT, LiteralT>(literalT).toString() +
                                                ", literalT: " + std::to_string(literalT) +
                                                ", complementary literal: " + std::to_string(complementaryLiteral) +
                                                ", clause ID: " + std::to_string(clauseId) + ")!") { }
    };
}   // namespace Hydra::Exception::Container::ContiguousOccurrenceList
