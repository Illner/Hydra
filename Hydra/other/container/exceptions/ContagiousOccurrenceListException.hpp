#pragma once

#include "Hydra/formula/Literal.hpp"

#include "Hydra/other/container/exceptions/ContainerException.hpp"

namespace Hydra::Exception::Container::ContagiousOccurrenceList {

    /**
     * Contagious occurrence list exception (main)
     */
    class ContagiousOccurrenceListException : public ContainerException {
    public:
        explicit ContagiousOccurrenceListException(const std::string& message)
            : ContainerException(message) { }

        explicit ContagiousOccurrenceListException(std::string&& message)
            : ContainerException(std::move(message)) { }
    };

    /**
     * Overflow
     */
    template <typename VarT, typename LiteralT>
    class OverflowException : public ContagiousOccurrenceListException {
    public:
        OverflowException(LiteralT literalT, std::size_t offset, std::size_t endOffset)
            : ContagiousOccurrenceListException("Overflow (literal: " +
                                                Hydra::Formula::createLiteralFromLiteralT<VarT, LiteralT>(literalT).toString() +
                                                ", literalT: " + std::to_string(literalT) +
                                                ", offset: " + std::to_string(offset) +
                                                ", end offset: " + std::to_string(endOffset) + ")!") { }
    };

    /**
     * Attempt to remove an occurrence that does not exist
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class AttemptToRemoveOccurrenceDoesNotExistException : public ContagiousOccurrenceListException {
    public:
        AttemptToRemoveOccurrenceDoesNotExistException(LiteralT literalT, ClauseIdT clauseId)
            : ContagiousOccurrenceListException("Attempt to remove an occurrence that does not exist (literal: " +
                                                Hydra::Formula::createLiteralFromLiteralT<VarT, LiteralT>(literalT).toString() +
                                                ", literalT: " + std::to_string(literalT) +
                                                ", clause ID: " + std::to_string(clauseId) + ")!") { }
    };

    /**
     * Attempt to add a duplicate occurrence
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    class AttemptToAddDuplicateOccurrenceException : public ContagiousOccurrenceListException {
    public:
        AttemptToAddDuplicateOccurrenceException(LiteralT literalT, ClauseIdT clauseId, bool complementaryLiteral)
            : ContagiousOccurrenceListException("Attempt to add a duplicate occurrence (literal: " +
                                                Hydra::Formula::createLiteralFromLiteralT<VarT, LiteralT>(literalT).toString() +
                                                ", literalT: " + std::to_string(literalT) +
                                                ", complementary literal: " + std::to_string(complementaryLiteral) +
                                                ", clause ID: " + std::to_string(clauseId) + ")!") { }
    };
}   // namespace Hydra::Exception::Container::ContagiousOccurrenceList
