/**
 * eliminator
 *  Copyright (C) 2021  Lagniez Jean-Marie
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <iostream>
#include <string>

#include "../bipartition/OptionBackbone.hpp"
#include "../bipartition/OptionBipartition.hpp"
#include "../bipartition/OptionDac.hpp"
#include "../eliminator/OptionEliminator.hpp"
#include "../optree/OptionGroup.hpp"

namespace bipe {

    /**
 * @brief Defines the available preprocessing strategies for the formula.
 */
    enum PreprocMethod {
        /**
   * @brief No preprocessing is applied.
   */
        NONE,

        /**
   * @brief Lightweight equivalence preprocessing.
   * Reduces the formula using vivification, occurrence elimination,
   * or a combination of both techniques.
   */
        EQUIV_LIGHT,

        /**
   * @brief Equivalence preprocessing.
   * Compute the backbone and equivalences.
   * Reduces the formula using vivification, occurrence elimination,
   * or a combination of both techniques.
   */
        EQUIV_FULL,

        /**
   * @brief Sharp-equivalence preprocessing.
   * Computes a bipartition of variables into input/output sets, then
   * eliminates output variables via Bounded Variable Elimination (BVE).
   * Preserves the model count over the projected variables but does NOT
   * preserve logical equivalence.
   */
        SHARP_EQUIV,

        /**
   * @brief Order-constrained sharp-equivalence preprocessing.
   * Same as SHARP_EQUIV but additionally enforces that a gate for variable y
   * is only used when all its defining variables have a lower position in the
   * user-supplied variable ordering.  Gates that violate the ordering are
   * discarded and their output variables are kept in the input set.
   * Required when the result will be compiled with a fixed variable order
   * (e.g. for d-DNNF compilation).
   */
        EQUIV_ORDERED
    };
}   // namespace bipe

template <>
struct optree::EnumMetadata<bipe::PreprocMethod> {
    static std::string name() { return "PreprocMethod"; }
    static std::map<int, std::string> mapping() {
        return { { bipe::NONE, "none" },
                 { bipe::EQUIV_LIGHT, "equiv-light" },
                 { bipe::EQUIV_FULL, "equiv-full" },
                 { bipe::SHARP_EQUIV, "sharp-equiv" },
                 { bipe::EQUIV_ORDERED, "equiv-ordered" } };
    }
};

namespace bipe {

    class OptionReducer : public optree::OptionGroup {
    public:
        optree::Option<std::string> reducerName { "reducer-name", "The reducer name.",
                                                  "combinaison" };
        optree::Option<int> nbIterarion { "nb-iteration", "The number of iterations.",
                                          50 };
        optree::Option<bool> subsumption {
            "subsumption",
            "Run a global subsumption + self-subsuming resolution pass inside the "
            "eliminate/reduce loop.",
            true
        };

        OptionReducer() : optree::OptionGroup("reducer", "Reducer options") { }

        std::vector<optree::OptionBase*> getAllOptions() override {
            return { &reducerName, &nbIterarion, &subsumption };
        }
    };

    class OptionPreproc : public optree::OptionGroup {
    public:
        optree::Option<unsigned> timeout { "timeout", "The timeout in second(s).",
                                           300u };
        OptionReducer optionReducer;
        eliminator::OptionEliminator optionEliminator;
        bipartition::OptionBackbone optionBackone;
        bipartition::OptionDac optionDac;
        bipartition::OptionBipartition optionBipartition;

        optree::Option<PreprocMethod> optionPreprocMethod {
            "preproc-method", "The preprocessing method used.",
            PreprocMethod::SHARP_EQUIV
        };

        // Substitute binary-implication equivalences (SCC) in the clauses before the
        // bipartition, iterating to a fixpoint (Arjun-style must-scc-vrepl).
        // Collapsing equivalent variables (instead of only marking EQUIV gates)
        // shrinks the independent support markedly: EQUIV gates alone leave the
        // bipartition input set ~40% bigger on the mc2025 gate-heavy family
        // (136/139/141/143), which doubles the residual and costs d4 the instance.
        // Count-preserving; substituted variables are re-pinned with a unit so ids,
        // nbVar and the projected set stay untouched (no renumbering of any kind);
        // protected variables are never substituted away.
        optree::Option<bool> equivSubst {
            "equiv-subst",
            "Detect and substitute binary equivalences (SCC) in the clauses before "
            "bipartition, iterating to fixpoint; substituted variables are re-pinned "
            "with a unit clause (ids and projected set kept). Shrinks the "
            "independent support.",
            true
        };

        // Runtime configuration selector.  The best eliminator configuration depends
        // on the formula's structure: an MC2025-track1 sweep over 34 configs found a
        // single robust discriminator -- the clause/variable density -- that recovers
        // the virtual-best coverage with one pick per instance (121/124).  Dense
        // formulas (density >= auto-config-ratio) blow up under aggressive bounded
        // resolution and instead want the "kitchen" preset (SBVA off, no fill guard,
        // oracle sparsification on); sparse formulas want the "cap12grow6" preset
        // (short-resolvent bounded BVE).  When enabled, this overrides the relevant
        // eliminator options from the parsed formula size and forces sharp-equiv.
        // Opt-in (off by default) so explicit configurations are never overridden.
        optree::Option<bool> autoConfig {
            "auto-config",
            "Pick the eliminator configuration automatically from the formula's "
            "clause/variable density: dense (>= auto-config-ratio) uses the "
            "'kitchen' "
            "preset (bva off, limit-elim-fill off, oracle-sparsif on), sparse uses "
            "the "
            "'arjun-like' preset (limit-elim-fill off, bve-max-resolvent-len 12, "
            "resolution-grow 6, oracle-sparsif on). Forces "
            "preproc-method=sharp-equiv "
            "and overrides those eliminator options. Disabled by default.",
            true
        };

        optree::Option<double> autoConfigRatio {
            "auto-config-ratio",
            "Clause/variable density threshold separating sparse from dense formulas "
            "for --auto-config (stable over [6,8] on the MC2025-track1 sweep).",
            7.0
        };

        // Which bounded-BVE aggressiveness the --auto-config SPARSE branch uses.  The
        // cap (bve-max-resolvent-len) bounds the residual treewidth; the per-variable
        // grow bounds how much a single elimination may add.  "arjunlike"
        // (cap12/grow6) is the validated default; "aggressive" (cap16/grow8) removes
        // more variables; "conservative" (cap8/grow4) keeps a smaller,
        // lower-treewidth residual.  Only affects the sparse branch and only when
        // --auto-config is on.
        optree::Option<std::string> autoConfigSparsePreset {
            "auto-config-sparse-preset",
            "Bounded-BVE aggressiveness for the --auto-config sparse branch: "
            "'arjunlike' (cap12/grow6, default), 'aggressive' (cap16/grow8), or "
            "'conservative' (cap8/grow4).",
            "arjunlike"
        };

        OptionPreproc() : optree::OptionGroup("preproc", "Preprocessing options") { }

        std::vector<optree::OptionBase*> getAllOptions() override {
            return { &timeout,
                     &optionReducer,
                     &optionEliminator,
                     &optionBackone,
                     &optionDac,
                     &optionBipartition,
                     &optionPreprocMethod,
                     &equivSubst,
                     &autoConfig,
                     &autoConfigRatio,
                     &autoConfigSparsePreset };
        }
    };

}   // namespace bipe
