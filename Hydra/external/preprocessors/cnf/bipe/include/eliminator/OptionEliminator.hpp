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
#include <map>
#include <string>

#include "../optree/EnumMetadata.hpp"
#include "../optree/OptionGroup.hpp"

namespace bipe {
    namespace eliminator {

        /**
 * @brief Quantity bounded by the elimination growth budget.
 *
 * The downstream model counter is sensitive to formula size and, more
 * precisely, to variable interaction. COST_LITERALS bounds the total number of
 * literals (a better proxy than clause count for the work the counter does),
 * while COST_CLAUSES keeps the historical clause-count budget.
 */
        enum CostMetric {
            COST_CLAUSES,   ///< Bound the total number of clauses.
            COST_LITERALS   ///< Bound the total number of literals.
        };

    }   // namespace eliminator
}   // namespace bipe

template <>
struct optree::EnumMetadata<bipe::eliminator::CostMetric> {
    static std::string name() { return "CostMetric"; }
    static std::map<int, std::string> mapping() {
        return { { bipe::eliminator::COST_CLAUSES, "clauses" },
                 { bipe::eliminator::COST_LITERALS, "literals" } };
    }
};

namespace bipe {
    namespace eliminator {

        /**
 * @brief Tunables for the variable-elimination stage.
 *
 * These control how aggressively gate-based (and resolution-based) elimination
 * grows the formula and whether generated clauses are simplified inline.
 */
        class OptionEliminator : public optree::OptionGroup {
        public:
            /// Allowed growth factor relative to the initial formula size (in the unit
            /// selected by costMetric).  1.0 (default) means "do not grow the formula".
            /// Raising it removes more variables but lets elimination add fill-in, which
            /// can increase the primal-graph treewidth and slow tree-decomposition-based
            /// counters; raise it only together with the limit-primal-degree guard, and
            /// verify the downstream counter's treewidth.  The per-variable resolution-
            /// grow cap bounds any single variable's blow-up when this is raised.
            optree::Option<double> growthBudget {
                "growth-budget",
                "Allowed growth factor of the formula during elimination (relative to "
                "the initial size, measured in the unit selected by cost-metric).",
                1.0
            };

            /// Quantity the growth budget bounds (clauses or literals).
            optree::Option<CostMetric> costMetric {
                "cost-metric", "The quantity bounded by the growth budget.",
                COST_LITERALS
            };

            /// Apply the growth budget (growthBudget / costMetric) to the resolution
            /// eliminator as well.  When OFF (default) the resolution pass keeps its
            /// legacy strict no-growth rule; when ON it accepts eliminations up to the
            /// same global budget the gate pass uses, like Arjun's BVE-with-grow.
            optree::Option<bool> resolutionGrowth {
                "resolution-growth",
                "Let resolution-based variable elimination grow the formula up to "
                "growth-budget (in the cost-metric unit), instead of the strict "
                "no-growth rule. Disabled by default.",
                true
            };

            /// Per-variable clause-growth allowance for resolution BVE (CMS/Arjun
            /// `grow`). Only used when resolution-growth is on.  Bounds the resolvents
            /// added per variable to (#removed clauses + this), preventing any single
            /// high-degree variable from exploding while still letting many variables be
            /// eliminated.
            optree::Option<int> resolutionGrow {
                "resolution-grow",
                "Per-variable extra clauses allowed during resolution elimination "
                "(only with resolution-growth). Higher removes more variables but may "
                "grow/slow the formula.",
                8
            };

            /// "Non-increasing" resolution rule: eliminate a variable by resolution only
            /// if it neither grows the clause COUNT (#resolvents <= #removed clauses) nor
            /// produces a resolvent LONGER than the longest clause being resolved.  I.e.
            /// resolution is accepted only when it can only keep or shrink the formula in
            /// both dimensions.  Overrides resolution-growth/grow for the count rule and
            /// applies the per-variable max-input-length cap.  Heuristic; never affects
            /// correctness.  Disabled by default.
            optree::Option<bool> resolutionNonIncreasing {
                "resolution-non-increasing",
                "Accept a resolution elimination only if it does not increase the number "
                "of clauses and produces no resolvent longer than the longest clause "
                "being resolved (elimination can only shrink the formula).",
                false
            };

            /// Run oracle vivification inside the eliminate/reduce loop:
            /// redundant-literal removal proven by a conflict-limited SAT oracle
            /// (model-set preserving, far stronger than BCP vivification).  Disabled by
            /// default (it issues SAT calls and can be costly).
            optree::Option<bool> oracleVivif {
                "oracle-vivif",
                "Run oracle vivification (SAT-proven redundant-literal removal) inside "
                "the eliminate/reduce loop.",
                true
            };

            /// Per-call conflict budget for the oracle vivification SAT calls (0 =
            /// unlimited).
            optree::Option<int> oracleMaxConflict {
                "oracle-max-conflict",
                "Per-call conflict budget for oracle vivification (0 = unlimited).",
                100
            };

            /// CUMULATIVE wall-time budget (seconds) for ALL oracle-vivification passes of
            /// one preprocessing (Arjun/CMS oracle-budget analogue).  oracle-vivif issues
            /// a SAT call per literal and is re-run every round of the eliminate/reduce
            /// loop; without a budget it can consume the whole preprocessing time
            /// (observed: 35s on one instance while removing 0 literals).  Once the total
            /// is reached the pass becomes a no-op.  0 = unlimited.  Heuristic only.
            optree::Option<double> oracleVivifMaxTime {
                "oracle-vivif-max-time",
                "Cumulative wall-time budget in seconds for all oracle-vivification passes "
                "of one preprocessing (0 = unlimited).",
                15.0
            };

            /// Cache satisfying assignments inside oracle vivification (CMS oracle-vivif
            /// model cache).  A query "clause C is satisfied only through C[i]" is SAT as
            /// soon as a previously-found model makes C[i] true and the rest of C false,
            /// so a pool of models answers many queries with no SAT call.  Model removal
            /// preserves the model set, so cached models stay valid.  On by default.
            optree::Option<bool> oracleVivifCache {
                "oracle-vivif-cache",
                "Cache satisfying models in oracle vivification to skip SAT calls.", true
            };

            /// Stop running oracle vivification once a full pass shortens nothing (it is
            /// re-run every round; a formula it cannot shorten now it will not shorten
            /// later).  On by default; turn off to A/B the give-up heuristic.
            optree::Option<bool> oracleVivifGiveup {
                "oracle-vivif-giveup",
                "Stop oracle vivification after a pass that removes nothing.", true
            };

            /// Run oracle sparsification inside the eliminate/reduce loop: remove a whole
            /// clause C when the rest of the formula already entails it (F\{C} |= C),
            /// proven by a conflict-limited SAT oracle.  Removing an entailed clause keeps
            /// the model set — and the count — identical, while thinning the primal graph
            /// (lower treewidth).  This is the clause-level analogue of oracle-vivif and
            /// the companion CMS/Arjun runs with occ-ternary-res.  Disabled by default
            /// (it issues a SAT call per clause).
            optree::Option<bool> oracleSparsif {
                "oracle-sparsif",
                "Run oracle sparsification (SAT-proven redundant-clause removal) inside "
                "the eliminate/reduce loop.",
                false
            };

            /// Cap on the number of clause-entailment SAT calls oracle sparsification may
            /// issue per pass (0 = unlimited).  Oracle sparsification tests one clause per
            /// SAT call, so on medium/large formulas an uncapped pass can consume the
            /// whole preprocessing budget; this bounds its cost so the other passes still
            /// run.  The per-call conflict budget (oracle-max-conflict) and the global
            /// timer bound it further.
            optree::Option<int> oracleSparsifMaxCalls {
                "oracle-sparsif-max-calls",
                "Max number of SAT calls (clauses tested) per oracle-sparsification pass "
                "(0 = unlimited).",
                20000
            };

            /// Run failed-literal probing inside the eliminate/reduce loop.  Derives
            /// entailed backbone units (failed literals + common implications), which are
            /// always count-preserving.  Disabled by default.
            optree::Option<bool> probing {
                "probing",
                "Run failed-literal probing (backbone units via unit propagation) inside "
                "the eliminate/reduce loop. Disabled by default.",
                true
            };

            /// Run Bounded Variable Addition as a final pass (Arjun's SBVA analogue).
            /// Introduces fresh, existentially-projected variables to factor clause
            /// grids, cutting the clause count.  Disabled by default.
            optree::Option<bool> bva {
                "bva",
                "Run Bounded Variable Addition as a final pass to factor clause grids "
                "with fresh (projected-out) variables. Disabled by default.",
                true
            };

            /// Structured BVA tie-break (Haberlandt, Green & Heule 2023).  When ON, BVA
            /// breaks ties between equally-reducing matched literals with a 3-hop
            /// co-occurrence heuristic that favours grid-preserving factorings, which
            /// lowers the residual's tree width (the quantity tree-decomposition counters
            /// like d4 are exponential in) instead of merely cutting the clause count.
            /// When OFF, plain BVA picks an arbitrary maximal-match literal.
            optree::Option<bool> bvaStructured {
                "bva-structured",
                "Use SBVA's structured (3-hop co-occurrence) tie-break to pick tree-width-"
                "reducing factorings instead of plain max-clause-reduction BVA.",
                true
            };

            /// Cap on the number of fresh variables BVA may introduce.
            optree::Option<int> bvaMaxNewVars {
                "bva-max-new-vars", "Maximum number of variables added by BVA.", 100000
            };

            /// Work budget (matching probes) bounding BVA's cost.
            optree::Option<int> bvaMaxSteps {
                "bva-max-steps", "Work budget (matching probes) for BVA.", 50000000
            };

            /// Enable inline forward/backward subsumption and strengthening on the
            /// clauses produced by gate substitution.
            optree::Option<bool> gateSubsumption {
                "gate-subsumption",
                "Apply subsumption and strengthening on the clauses produced by gate "
                "substitution.",
                true
            };

            /// Enable the fill-based elimination guard on gate substitutions and
            /// resolution elimination.  ON by default: model counters that use tree
            /// decomposition (d4, SharpSAT-TD) are exponential in treewidth.  Eliminating
            /// a variable is vertex elimination in the primal graph: it turns the
            /// variable's neighbourhood into a clique, and the *fill-in* (new edges that
            /// adds) is what grows the treewidth — eliminating a simplicial variable
            /// (neighbourhood already a clique, fill-in 0) never increases it.  A plain
            /// degree cap cannot tell these apart and still blows the width up (e.g.
            /// 27 -> 56 on a narrow instance) because fill among the surviving variables
            /// compounds.  This guard refuses eliminations whose fill-in exceeds the
            /// effective tolerance, keeping the output width near the input width.
            /// Purely heuristic (never affects correctness); disable it only when you
            /// care about formula size and not the downstream counter's treewidth.
            optree::Option<bool> limitElimFill {
                "limit-elim-fill",
                "Refuse to eliminate a variable whose fill-in (new primal-graph edges "
                "its elimination creates among its neighbours) exceeds the effective "
                "tolerance. Enabled by default to bound treewidth.",
                true
            };

            /// Base fill-in tolerance, only used when limitElimFill is set.  0 admits
            /// only (near-)simplicial eliminations.  The effective tolerance is raised
            /// adaptively to max(max-fill, treewidth-factor * estimated-treewidth): an
            /// already-wide formula can absorb more fill, so elimination becomes
            /// aggressive; a narrow one keeps the small max-fill floor and stays
            /// conservative to preserve its low treewidth.  Dominant size/treewidth knob.
            optree::Option<int> maxFill {
                "max-fill",
                "Base fill-in tolerance (new edges an elimination may add among the "
                "eliminated variable's neighbours); the effective tolerance is raised to "
                "max(this, treewidth-factor * estimated-treewidth). Only used when "
                "limit-elim-fill is set.",
                0
            };

            /// Multiplier on the estimated treewidth (graph degeneracy) when raising the
            /// adaptive fill tolerance, only used when limitElimFill is set.  Larger
            /// values let elimination add more fill on wide formulas (more aggressive);
            /// 0 disables the adaptive term, leaving the flat max-fill tolerance.
            optree::Option<double> treewidthFactor {
                "treewidth-factor",
                "Multiplier on the estimated treewidth (degeneracy) used to raise the "
                "adaptive fill tolerance above max-fill. Only used when limit-elim-fill "
                "is set.",
                1.0
            };

            /// Fixed cap on resolvent LENGTH (literals) for both resolution and gate
            /// elimination, matching Arjun's CMS `--bveresolvmaxsz` (12 there).  An
            /// elimination is rejected if it would create any clause longer than this.
            /// Keeping resolvents short lets the iterated eliminate/reduce loop remove
            /// more variables overall (short clauses keep more variables eliminable),
            /// like Arjun's length-capped iterated occ-bve.  Enforced even in growth mode.
            /// 0 = disabled (no fixed length cap).  Heuristic; never affects correctness.
            optree::Option<int> bveMaxResolventLen {
                "bve-max-resolvent-len",
                "Reject an elimination if any resolvent/substituted clause would exceed "
                "this many literals (Arjun --bveresolvmaxsz analogue). 0 disables it.",
                0
            };

            /// Run ternary resolution (CMS `occ-ternary-res`) before each elimination
            /// round: resolve pairs of short clauses (length <=3) on a shared variable and
            /// add the resolvent when it has length <=3.  Resolvents are logically
            /// entailed by their parents, so adding them preserves the model set (and the
            /// count) exactly; the short clauses they expose let the subsequent BVE stay
            /// short and remove more variables, like Arjun's occ-ternary-res -> occ-bve.
            /// Heuristic; never affects correctness.  Disabled by default.
            optree::Option<bool> ternaryRes {
                "ternary-res",
                "Run ternary resolution (add length<=3 resolvents of length<=3 clauses) "
                "before each elimination round (Arjun occ-ternary-res analogue).",
                false
            };

            /// Work budget (resolution attempts) bounding the ternary-resolution pass.
            optree::Option<int> ternaryResMaxSteps {
                "ternary-res-max-steps",
                "Work budget (resolution attempts) for the ternary-resolution pass.",
                20000000
            };

            /// Staged BVE grow schedule (Arjun/Puura `--iter1grow` / `--iter2grow`).  When
            /// >= 0 these override `resolution-grow` for the pre-oracle and post-oracle
            /// elimination phases respectively: a tight grow before the oracle pass keeps
            /// resolvents short, a looser one afterwards removes the remainder.  -1 (both,
            /// default) disables staging and keeps the single-phase loop using
            /// `resolution-grow`.  Heuristic; never affects correctness.
            optree::Option<int> bveGrowIter1 {
                "bve-grow-iter1",
                "Per-variable grow used by BVE in the pre-oracle phase (-1 = disable the "
                "staged schedule and use resolution-grow). Arjun --iter1grow analogue.",
                -1
            };

            optree::Option<int> bveGrowIter2 {
                "bve-grow-iter2",
                "Per-variable grow used by BVE in the post-oracle phase (only when "
                "bve-grow-iter1 >= 0; -1 falls back to resolution-grow). Arjun --iter2grow "
                "analogue.",
                -1
            };

            /// Distill the residual through CaDiCaL inprocessing (Arjun `distill-cls`
            /// analogue) at the end of the eliminate/reduce loop.  Runs only model-set-
            /// preserving passes (vivify/distill, subsumption, transitive reduction,
            /// probing) with every variable frozen and all variable-removing passes off,
            /// so the model count is preserved.  This is the CDCL-strength
            /// redundant-literal/clause removal bipe's BCP vivification cannot do; it
            /// shrinks both formula size and primal-graph treewidth.  Disabled by default.
            optree::Option<bool> cadicalDistill {
                "cadical-distill",
                "Distill the residual via CaDiCaL inprocessing (vivify/subsume/transred/"
                "probe, all variables frozen, no variable elimination). Count-preserving; "
                "shrinks size and treewidth. Disabled by default.",
                false
            };

            /// Number of CaDiCaL `simplify` rounds for the distillation pass.
            optree::Option<int> cadicalDistillRounds {
                "cadical-distill-rounds",
                "Number of CaDiCaL simplify rounds for --cadical-distill (more = more "
                "thorough but slower).",
                3
            };

            /// Use CaDiCaL inprocessing as the PRIMARY residual reducer, replacing bipe's
            /// hand-rolled oracle-vivification + subsumption inside the eliminate/reduce
            /// loop (Armin's vivify/subsume/probe/transred, input set frozen).  bipe's BVE
            /// (with its fill/treewidth guard) is kept; only the reduction is offloaded.
            /// Count-preserving.  Disabled by default (opt-in for an A/B against the
            /// hand-rolled reducers).
            optree::Option<bool> cadicalReduce {
                "cadical-reduce",
                "Use CaDiCaL inprocessing (vivify/subsume/probe/transred, input frozen) as "
                "the residual reducer in place of bipe's oracle-vivif + subsumption. Keeps "
                "bipe's BVE. Count-preserving. Disabled by default.",
                false
            };

            /// PROTOTYPE: replace bipe's eliminate/reduce loop with CaDiCaL.  Freezes the
            /// input set and lets CaDiCaL do bounded variable elimination (+ vivify,
            /// subsume, probe, transred) on the output variables -- the Arjun architecture
            /// (freeze sampling set, CMS simplify), reusing Armin's tuned BVE instead of
            /// bipe's hand-rolled eliminator + reducers.  Count-preserving (outputs are
            /// functionally defined).  Disabled by default.
            optree::Option<bool> cadicalElim {
                "cadical-elim",
                "PROTOTYPE: eliminate output variables via CaDiCaL (input set frozen, "
                "bounded BVE + inprocessing) instead of bipe's eliminate/reduce loop. "
                "Reuses CaDiCaL's elimination. Disabled by default.",
                false
            };

            OptionEliminator()
                : optree::OptionGroup("eliminator", "Variable elimination options") { }

            std::vector<optree::OptionBase*> getAllOptions() override {
                return { &growthBudget, &costMetric,
                         &resolutionGrowth, &resolutionGrow,
                         &oracleVivif, &oracleMaxConflict,
                         &probing, &bva,
                         &bvaStructured, &bvaMaxNewVars,
                         &bvaMaxSteps,
                         &gateSubsumption, &limitElimFill,
                         &maxFill, &treewidthFactor,
                         &resolutionNonIncreasing, &bveMaxResolventLen,
                         &ternaryRes, &ternaryResMaxSteps,
                         &bveGrowIter1, &bveGrowIter2,
                         &oracleSparsif, &oracleSparsifMaxCalls,
                         &oracleVivifMaxTime, &oracleVivifCache,
                         &oracleVivifGiveup,
                         &cadicalDistill, &cadicalDistillRounds,
                         &cadicalElim, &cadicalReduce };
            }

            friend std::ostream& operator<<(std::ostream& os,
                                            const OptionEliminator& oe) {
                os << "[OPTION] Eliminator options: growth-budget(" << oe.growthBudget.get()
                   << ") cost-metric(" << optree::enum_to_string(oe.costMetric.get())
                   << ") resolution-growth(" << oe.resolutionGrowth.get()
                   << ") oracle-vivif(" << oe.oracleVivif.get() << ") probing("
                   << oe.probing.get() << ") bva(" << oe.bva.get() << ") bva-structured("
                   << oe.bvaStructured.get() << ") gate-subsumption("
                   << oe.gateSubsumption.get() << ") limit-elim-fill("
                   << oe.limitElimFill.get() << ") max-fill("
                   << oe.maxFill.get() << ") treewidth-factor("
                   << oe.treewidthFactor.get() << ") resolution-non-increasing("
                   << oe.resolutionNonIncreasing.get() << ") bve-max-resolvent-len("
                   << oe.bveMaxResolventLen.get() << ") ternary-res(" << oe.ternaryRes.get()
                   << ") bve-grow-iter1(" << oe.bveGrowIter1.get() << ") bve-grow-iter2("
                   << oe.bveGrowIter2.get() << ") oracle-sparsif(" << oe.oracleSparsif.get()
                   << ") oracle-sparsif-max-calls(" << oe.oracleSparsifMaxCalls.get()
                   << ") oracle-vivif-max-time(" << oe.oracleVivifMaxTime.get()
                   << ") oracle-vivif-cache(" << oe.oracleVivifCache.get()
                   << ") oracle-vivif-giveup(" << oe.oracleVivifGiveup.get() << ")";
                return os;
            }
        };

    }   // namespace eliminator
}   // namespace bipe
