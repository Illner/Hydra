#pragma once

#include <cassert>
#include <ostream>
#include <string>

#include "Hydra/cache/CacheRecordStructure.hpp"
#include "Hydra/formula/representation/FormulaRepresentationAbstract.hpp"

namespace Hydra::Cache {

    /**
     * Cache statistics structure
     * Copy methods are disabled! Move methods (default) are allowed!
     * @tparam VarT type used for a variable
     * @tparam LiteralT type used for a literal
     * @tparam ClauseIdT type used for a clause identifier
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    struct CacheStatisticsStruct {
    public:
        using FormulaRepresentationAbstractPtrType = typename CacheRecordStruct<VarT, LiteralT, ClauseIdT>::FormulaRepresentationAbstractPtrType;

    public:
        explicit CacheStatisticsStruct(FormulaRepresentationAbstractPtrType formulaRepresentationAbstractPtr) noexcept
            : numberOfCalls_(0),
              minNumberOfVariables_(formulaRepresentationAbstractPtr->getNumberOfVariablesInOriginalFormula()), maxNumberOfVariables_(0), sumNumberOfVariables_(0),
              minNumberOfClauses_(formulaRepresentationAbstractPtr->getNumberOfOriginalClauses()), maxNumberOfClauses_(0), sumNumberOfClauses_(0),
              minFormulaSize_(formulaRepresentationAbstractPtr->getOriginalFormulaSize()), maxFormulaSize_(0), sumFormulaSize_(0) { };

        CacheStatisticsStruct(const CacheStatisticsStruct&) = delete;
        CacheStatisticsStruct(CacheStatisticsStruct&&) noexcept = default;

        CacheStatisticsStruct& operator=(const CacheStatisticsStruct&) = delete;
        CacheStatisticsStruct& operator=(CacheStatisticsStruct&&) noexcept = default;

    private:
        LargeNumberType numberOfCalls_;

        // Number of variables
        VarT minNumberOfVariables_;
        VarT maxNumberOfVariables_;
        LargeNumberType sumNumberOfVariables_;

        // Number of clauses
        ClauseIdT minNumberOfClauses_;
        ClauseIdT maxNumberOfClauses_;
        LargeNumberType sumNumberOfClauses_;

        // Formula size
        FormulaSizeType minFormulaSize_;
        FormulaSizeType maxFormulaSize_;
        LargeNumberType sumFormulaSize_;

    public:
        void add(VarT numberOfVariables, ClauseIdT numberOfClauses, FormulaSizeType formulaSize);

        /**
         * Getter
         * @return the minimum number of variables
         */
        VarT getMinNumberOfVariables() const noexcept;

        /**
         * Getter
         * @return the maximum number of variables
         */
        VarT getMaxNumberOfVariables() const noexcept;

        /**
         * Note: if the number of calls is 0, then 0 is returned
         * @return the average number of variables
         */
        LargeFloatingNumberType averageNumberOfVariables() const noexcept;

        /**
         * Getter
         * @return the minimum number of clauses
         */
        ClauseIdT getMinNumberOfClauses() const noexcept;

        /**
         * Getter
         * @return the maximum number of clauses
         */
        ClauseIdT getMaxNumberOfClauses() const noexcept;

        /**
         * Note: if the number of calls is 0, then 0 is returned
         * @return the average number of clauses
         */
        LargeFloatingNumberType averageNumberOfClauses() const noexcept;

        /**
         * Getter
         * @return the minimum formula size
         */
        FormulaSizeType getMinFormulaSize() const noexcept;

        /**
         * Getter
         * @return the maximum formula size
         */
        FormulaSizeType getMaxFormulaSize() const noexcept;

        /**
         * Note: if the number of calls is 0, then 0 is returned
         * @return the average formula size
         */
        LargeFloatingNumberType averageFormulaSize() const noexcept;

        void printCacheStatisticsStruct(std::ostream& out) const;
    };
}   // namespace Hydra::Cache

#include "./CacheStatisticsStructure.ipp"
