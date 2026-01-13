#pragma once

#include "./CacheRecordStructure.hpp"

namespace Hydra::Cache {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT CacheRecordStruct<VarT, LiteralT, ClauseIdT>::getCachedNumberOfVariables() const {
        assert(numberOfVariables > 0);
        assert(numberOfRemovedVariables <= numberOfVariables);

        return (numberOfVariables - numberOfRemovedVariables);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseIdT CacheRecordStruct<VarT, LiteralT, ClauseIdT>::getCachedNumberOfClauses() const {
        assert(numberOfClauses > 0);
        assert(numberOfRemovedClauses <= numberOfClauses);

        return (numberOfClauses - numberOfRemovedClauses);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    FormulaSizeType CacheRecordStruct<VarT, LiteralT, ClauseIdT>::getCachedFormulaSize() const {
        assert(formulaSize > 0);
        assert(removedFormulaSize <= formulaSize);

        return (formulaSize - removedFormulaSize);
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CacheRecordStruct<VarT, LiteralT, ClauseIdT>::printCacheRecordStruct(std::ostream& out) const {
        out << "Cache record structure" << std::endl;

        // Empty
        if (empty) {
            out << "Empty" << std::endl;
            return;
        }

        // Number of variables
        out << "Number of variables: " << std::to_string(numberOfVariables) << std::endl;
        out << "Number of removed variables: " << std::to_string(numberOfRemovedVariables) << std::endl;

        // Number of clauses
        out << "Number of clauses: " << std::to_string(numberOfClauses) << std::endl;
        out << "Number of removed clauses: " << std::to_string(numberOfRemovedClauses) << std::endl;

        // Formula size
        out << "Formula size: " << std::to_string(formulaSize) << std::endl;
        out << "Removed formula size: " << std::to_string(removedFormulaSize) << std::endl;

        // Others
        out << "Maximum clause size: " << std::to_string(maxClauseSize) << std::endl;
        out << std::endl;

        // Mapping
        if (!mapping.empty()) {
            out << "Mapping:";
            for (const LiteralType& lit : mapping)
                out << " " << lit;
            out << std::endl;
        }

        // string8
        if (!string8.empty()) {
            out << "u8string:";

            for (char8_t c : string8)
                out << " " << std::to_string(c);
            out << std::endl;
        }

        // string16
        if (!string16.empty()) {
            out << "u16string:";

            for (char16_t c : string16)
                out << " " << std::to_string(c);
            out << std::endl;
        }

        // string32
        if (!string32.empty()) {
            out << "u32string:";

            for (char32_t c : string32)
                out << " " << std::to_string(c);
            out << std::endl;
        }
    }
}   // namespace Hydra::Cache
