#pragma once

#include <cassert>
#include <ostream>
#include <string>

#include "Hydra/formula/Literal.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"
#include "Hydra/other/Other.hpp"

namespace Hydra::Cache {

    using LargeFloatingNumberType = long double;   // 128 bits

    using LargeNumberType = Hydra::Other::LargeNumberType;
    using FormulaSizeType = Hydra::Formula::Representation::FormulaSizeType;

    /**
     * Cache record structure
     * Copy methods are disabled! Move methods (default) are allowed!
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    struct CacheRecordStruct {
    public:
        using LiteralType = typename Formula::Literal<VarT, LiteralT>::LiteralType;
        using VariableSetType = typename Formula::Literal<VarT, LiteralT>::VariableSetType;
        using LiteralVectorType = typename Formula::Literal<VarT, LiteralT>::LiteralVectorType;
        using VariableVectorType = typename Formula::Literal<VarT, LiteralT>::VariableVectorType;
        using VariableSortedVectorType = typename Formula::Literal<VarT, LiteralT>::VariableSortedVectorType;
        using MappingFromVariableToLiteralType = typename Formula::Literal<VarT, LiteralT>::MappingFromVariableToLiteralType;
        using MappingFromVariableToVariableType = typename Formula::Literal<VarT, LiteralT>::MappingFromVariableToVariableType;
        using ClauseSizeType = typename Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>::ClauseSizeType;

    public:
        using String8Type = std::basic_string<char8_t>;
        using String16Type = std::basic_string<char16_t>;
        using String32Type = std::basic_string<char32_t>;
        using FormulaRepresentationAbstractPtrType = const Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>*;

    public:
        CacheRecordStruct() noexcept
            : empty(true),
              string8(), string16(), string32(),
              numberOfVariables(0), numberOfClauses(0), formulaSize(0), maxClauseSize(0),
              numberOfRemovedVariables(0), numberOfRemovedClauses(0), removedFormulaSize(0),
              mapping() { };

        CacheRecordStruct(const CacheRecordStruct&) = delete;
        CacheRecordStruct(CacheRecordStruct&&) noexcept = default;

        CacheRecordStruct& operator=(const CacheRecordStruct&) = delete;
        CacheRecordStruct& operator=(CacheRecordStruct&&) noexcept = default;

    public:
        bool empty;

        String8Type string8;
        String16Type string16;
        String32Type string32;

        VarT numberOfVariables;
        ClauseIdT numberOfClauses;
        FormulaSizeType formulaSize;
        ClauseSizeType maxClauseSize;
        VarT numberOfRemovedVariables;
        ClauseIdT numberOfRemovedClauses;     // omitted, subsumed and multi-occurrent clauses
        FormulaSizeType removedFormulaSize;   // since omitted, subsumed and multi-occurrent clauses

        LiteralVectorType mapping;   // ONE-based array indexing - [lit_1, lit_2, ...] <=> {{1, lit_1}, {2, lit_2}, ...}

    public:
        /**
         * Assert: numberOfVariables MUST be set
         * @return the cached number of variables
         */
        VarT getCachedNumberOfVariables() const;

        /**
         * Assert: numberOfClauses MUST be set
         * @return the cached number of clauses
         */
        ClauseIdT getCachedNumberOfClauses() const;

        /**
         * Assert: formulaSize MUST be set
         * @return the cached formula size
         */
        FormulaSizeType getCachedFormulaSize() const;

        void printCacheRecordStruct(std::ostream& out) const;
    };
}   // namespace Hydra::Cache

#include "./CacheRecordStructure.ipp"
