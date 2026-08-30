**bipe** is a CNF preprocessor designed for (projected, possibly weighted) model counting.
Its core technique leverages *definability* [3]: it computes a bipartition of the variables
of the input formula Σ into a set I of *input* variables and a set O of *output* variables,
where every variable of O is defined in Σ in terms of I (Padoa's method, implemented with a
SAT solver). Output variables can then be eliminated by Bounded Variable Elimination (BVE)
without changing the number of models of Σ projected onto the remaining variables. Around
this core, **bipe** provides backbone computation, gate detection (equivalences, AND/OR, XOR),
and several equivalence-based simplification pipelines.

**bipe** is both a standalone command-line tool (`c++/build/bipe`) and a static library
(`build/libbipe.a`).

# How to compile

Build the library:

```bash
./build.sh          # Release
./build.sh -d       # Debug
./build.sh -j       # parallel build
```

Build the command-line tool (this builds the library first):

```bash
cd c++
./build.sh          # Release      -> c++/build/bipe
./build.sh -d       # Debug
./build.sh -j       # parallel build
./build.sh -s       # static executable
```

The build fetches the header-only option library **optree** via CMake `FetchContent`;
the build scripts set the required access token themselves, so a plain `./build.sh`
works out of the box. The SAT solvers **Glucose 3.0** and **CaDiCaL** are vendored in
`3rdParty/` and built automatically.

# How to use

```bash
./c++/build/bipe -i bench.cnf                       # preprocess (log on stdout)
./c++/build/bipe -i bench.cnf --print-cnf           # also print the simplified CNF
./c++/build/bipe -h                                 # full option tree
```

All options are addressed by their full dotted path in the option tree,
`--path.to.option value` (or `--path.to.option=value`). `-h` prints the live tree
with the current default values; since options evolve frequently, the help output
is the authoritative reference. The most important entry points are:

* `--preproc.preproc-method`: which pipeline runs (see next section);
* `--preproc.timeout`: time budget in seconds (default 300, `0` = no limit);
* `--preproc.verbosity`: `0` is quiet-ish; `3` additionally prints a final
  `c [STATS]` summary line (sizes, treewidth estimate, gates, eliminations);
* `--preproc.eliminator.*`, `--preproc.bipartition.*`, `--preproc.backbone.*`,
  `--preproc.dac.*`, `--preproc.reducer.*`: fine-grained control of each phase.

Example (defaults, `--print-cnf`):

```
$ ./c++/build/bipe -i instanceTest/cnf8.cnf --print-cnf
c [BIPE] Parsing options done
c [BIPE] Input: instanceTest/cnf8.cnf
c [BIPE] A timeout is set to: 300
c [AUTO-CONFIG] density=0.636364 < 7 -> sparse preset (arjunlike: guard off + cap12 + grow6 + oracle-sparsif)
c [BACKBONE] Backbone size: 4
c [DAC] #Equivalence classes: 1
c [DAC] #Equivalences: 1
c [DAC] #And gates: 1
c [BIPARTITION] #Projected: 17
c [BIPARTITION] Initial input set: 4
c [BIPARTITION] #Input variables computed: 12
...
p cnf 22 12
c p show 15 10 1 20 12 17 19 7 2 9 18 6 16 22 8 3 5 0
-3 -1 6 0
1 3 6 0
10 0
...
```

The simplified CNF keeps the original variable identifiers and the original number of
variables: an eliminated variable is pinned with a unit clause instead of being renumbered
away, so the output is a plain CNF whose model count (over the projected variables) equals
that of the input. The comment lines (`c ...`) make the output directly consumable by model
counters such as d4.

# Input format

**bipe** reads a CNF formula in DIMACS format [1]. A subset of variables can be marked as
*projected* with a `c p show ... 0` comment line (the MC-competition convention); when such
a line is present, only projected variables are candidates for the input set I and the
preprocessing preserves the model count projected onto them. Without a `c p show` line,
every variable is projected.

```
p cnf 6 7
c p show 2 5 6 0
5 6 0
-1 -2 3 0
1 -3 0
2 -3 0
-1 -2 4 0
1 -4 0
2 -4 0
```

For **weighted** model counting, variables whose two polarities carry different weights must
not be eliminated. The CLI has no flag for this; when using **bipe** as a library, pass those
variables in the `protect` argument of `PreprocManager::run` (see below).

# Preprocessing methods

`--preproc.preproc-method` selects one of five pipelines:

| Method | What it does | Guarantee |
|---|---|---|
| `none` | nothing | (identity) |
| `equiv-light` | clause reduction (vivification, occurrence elimination, subsumption) | logical equivalence |
| `equiv-full` | `equiv-light` + backbone + equivalence detection | logical equivalence |
| `sharp-equiv` (default) | equivalence substitution + backbone + gate detection (DAC) + bipartition + BVE | model count over the projected variables (**not** logical equivalence) |
| `equiv-ordered` | like `sharp-equiv`, but a gate for y is only used when all its defining variables precede y in a caller-supplied variable order (library only); needed when the output must respect a fixed order, e.g. for d-DNNF compilation | model count over the projected variables |

The `sharp-equiv` pipeline works as follows:

1. **Equivalence substitution** (`--preproc.equiv-subst`, on by default): binary
   equivalences are detected by SCC on the implication graph and substituted in the
   clauses, to fixpoint. Substituted variables are re-pinned with a unit clause, so
   identifiers and the projected set are untouched.
2. **Backbone** [2]: literals true in every model become units (output variables).
3. **DAC**: a Directed Acyclic definability Circuit is extracted syntactically and by BCP
   (equivalences, AND/OR and small XOR gates); gate outputs seed the output set O.
4. **Bipartition**: the remaining variables are decided one by one with SAT calls on a
   Padoa-style dual formula [3], guided by an ordering heuristic
   (`--preproc.bipartition.sorting`: `OCC_ASC` (default), `RANDOM`, `NATURAL_ORDER`,
   `GEN_TAUTS`); models and unsatisfiable cores are exploited to decide several
   variables per call.
5. **Elimination**: output variables are eliminated by gate substitution and bounded
   resolution, interleaved with clause reduction (subsumption, vivification, SAT-oracle
   vivification/sparsification, probing), under budgets designed to keep the residual
   formula small and of low treewidth. Parts of this loop can be delegated to CaDiCaL's
   inprocessing (`--preproc.eliminator.cadical-distill`, `cadical-reduce`, `cadical-elim`).
6. **BVA** (`--preproc.eliminator.bva`): a structured Bounded Variable Addition pass may
   introduce fresh (non-projected) variables to factor clause grids.

**Automatic configuration.** By default (`--preproc.auto-config`, on), **bipe** picks the
eliminator configuration from the formula's clause/variable density (a "kitchen" preset for
dense formulas, a bounded-BVE "arjun-like" preset for sparse ones) and forces `sharp-equiv`.
Set `--preproc.auto-config 0` when you want your own `--preproc.*` settings to be in charge.

# Using bipe as a library

Link against `build/libbipe.a` and call the single entry point
(`src/preproc/PreprocManager.hpp`):

```c++
#include "src/preproc/PreprocManager.hpp"

unsigned nbVar = ...;
std::vector<std::vector<int>> clauses = ...;  // DIMACS integer encoding
std::vector<int> projected = ...;             // e.g. 1..nbVar
std::vector<int> protect = ...;               // WMC: vars with non-uniform weights

bipe::OptionPreproc options;                  // defaults, or set fields yourself
bipe::PreprocManager manager;
manager.run(nbVar, clauses, projected, protect, options);
// `clauses` now holds the simplified formula (same variable identifiers).
```

`clauses` is rewritten in place; `protect` variables are never eliminated. For
`equiv-ordered`, a variable order is passed as the optional last argument. The
`c++/` directory is a complete example of a client application.

The SAT solvers used internally are selected per phase by name
(`--preproc.backbone.solver-name`, etc.; `glucose` or `cadical`). You can plug your
own solver by implementing the `WrapperSolver` interface (`src/solver/`).

# Validating a change

There is no unit-test suite; correctness is validated by count-equivalence: the `scripts/`
directory (run the scripts from inside it) compares the model count of an instance before
and after preprocessing with the bundled `d4` counter:

```bash
cd scripts
./runFeatureTests.sh ""                      # all instanceTest/cnf*.cnf, PASS/FAIL
./testFeature.sh bench.cnf "<extra options>" # single instance
```

`searchBadExitQuick.sh` fuzzes random instances (via `cnfuzz`) through a test script, and
`minimize_cnf.py` / `shrink_cnf_lits.py` delta-debug a failing instance (see
`scripts/README_minimize.md`).

# License

**bipe** is distributed under the GNU Affero General Public License v3 (see `LICENSE`).

# References

[1] Satisfiability suggested format, 1993.

[2] K. Pipatsrisawat and A. Darwiche. A lightweight component caching scheme for satisfiability solvers. In SAT, pages 294–299, 2007.

[3] Jean-Marie Lagniez, Emmanuel Lonca, Pierre Marquis: Definability for model counting. Artif. Intell. 281: 103229 (2020).

[4] Gilles Audemard, Jean-Marie Lagniez, Laurent Simon: Improving Glucose for Incremental SAT Solving with Assumptions: Application to MUS Extraction. SAT 2013: 309-317.

[5] Jean-Marie Lagniez, Pierre Marquis: On Preprocessing Techniques and Their Impact on Propositional Model Counting. J. Autom. Reason. 58(4): 413-481 (2017).
