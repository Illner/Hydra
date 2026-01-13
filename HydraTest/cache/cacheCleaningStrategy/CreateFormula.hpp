#pragma once

#include "HydraTest/cache/cacheCleaningStrategy/CacheCleaningStrategy.hpp"

namespace HydraTest::Cache::CacheCleaningStrategy {

    /**
     * Formula
     */
    template <typename VarT, typename LiteralT, typename ClauseIdT>
    inline std::unique_ptr<Hydra::Formula::Representation::FormulaRepresentationAbstract<VarT, LiteralT, ClauseIdT>> createFormula();
}   // namespace HydraTest::Cache::CacheCleaningStrategy

#include "./CreateFormula.ipp"
