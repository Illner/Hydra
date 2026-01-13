#pragma once

#include "./CacheStatisticsStructure.hpp"

namespace Hydra::Cache {

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CacheStatisticsStruct<VarT, LiteralT, ClauseIdT>::add(VarT numberOfVariables, ClauseIdT numberOfClauses, FormulaSizeType formulaSize) {
        assert(numberOfVariables > 0);   // at least one variable

        ++numberOfCalls_;

        // Number of variables
        sumNumberOfVariables_ += numberOfVariables;
        // Minimum
        if (numberOfVariables < minNumberOfVariables_)
            minNumberOfVariables_ = numberOfVariables;
        // Maximum
        if (numberOfVariables > maxNumberOfVariables_)
            maxNumberOfVariables_ = numberOfVariables;

        // Number of clauses
        sumNumberOfClauses_ += numberOfClauses;
        // Minimum
        if (numberOfClauses < minNumberOfClauses_)
            minNumberOfClauses_ = numberOfClauses;
        // Maximum
        if (numberOfClauses > maxNumberOfClauses_)
            maxNumberOfClauses_ = numberOfClauses;

        // Formula size
        sumFormulaSize_ += formulaSize;
        // Minimum
        if (formulaSize < minFormulaSize_)
            minFormulaSize_ = formulaSize;
        // Maximum
        if (formulaSize > maxFormulaSize_)
            maxFormulaSize_ = formulaSize;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT CacheStatisticsStruct<VarT, LiteralT, ClauseIdT>::getMinNumberOfVariables() const noexcept {
        return minNumberOfVariables_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    VarT CacheStatisticsStruct<VarT, LiteralT, ClauseIdT>::getMaxNumberOfVariables() const noexcept {
        return maxNumberOfVariables_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    LargeFloatingNumberType CacheStatisticsStruct<VarT, LiteralT, ClauseIdT>::averageNumberOfVariables() const noexcept {
        if (numberOfCalls_ == 0)
            return 0;

        return (static_cast<LargeFloatingNumberType>(sumNumberOfVariables_) / static_cast<LargeFloatingNumberType>(numberOfCalls_));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseIdT CacheStatisticsStruct<VarT, LiteralT, ClauseIdT>::getMinNumberOfClauses() const noexcept {
        return minNumberOfClauses_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    ClauseIdT CacheStatisticsStruct<VarT, LiteralT, ClauseIdT>::getMaxNumberOfClauses() const noexcept {
        return maxNumberOfClauses_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    LargeFloatingNumberType CacheStatisticsStruct<VarT, LiteralT, ClauseIdT>::averageNumberOfClauses() const noexcept {
        if (numberOfCalls_ == 0)
            return 0;

        return (static_cast<LargeFloatingNumberType>(sumNumberOfClauses_) / static_cast<LargeFloatingNumberType>(numberOfCalls_));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    FormulaSizeType CacheStatisticsStruct<VarT, LiteralT, ClauseIdT>::getMinFormulaSize() const noexcept {
        return minFormulaSize_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    FormulaSizeType CacheStatisticsStruct<VarT, LiteralT, ClauseIdT>::getMaxFormulaSize() const noexcept {
        return maxFormulaSize_;
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    LargeFloatingNumberType CacheStatisticsStruct<VarT, LiteralT, ClauseIdT>::averageFormulaSize() const noexcept {
        if (numberOfCalls_ == 0)
            return 0;

        return (static_cast<LargeFloatingNumberType>(sumFormulaSize_) / static_cast<LargeFloatingNumberType>(numberOfCalls_));
    }

    template <typename VarT, typename LiteralT, typename ClauseIdT>
    void CacheStatisticsStruct<VarT, LiteralT, ClauseIdT>::printCacheStatisticsStruct(std::ostream& out) const {
        out << "Cache statistics structure" << std::endl;

        // Number of variables
        out << "Number of variables - ";
        out << "min: " << std::to_string(getMinNumberOfVariables()) << ", ";
        out << "max: " << std::to_string(getMaxNumberOfVariables()) << std::endl;

        // Number of clauses
        out << "Number of clauses - ";
        out << "min: " << std::to_string(getMinNumberOfClauses()) << ", ";
        out << "max: " << std::to_string(getMaxNumberOfClauses()) << std::endl;

        // Formula size
        out << "Formula size - ";
        out << "min: " << std::to_string(getMinFormulaSize()) << ", ";
        out << "max: " << std::to_string(getMaxFormulaSize()) << std::endl;
    }
}   // namespace Hydra::Cache
