// NEW_FILE
// Tests 'solve_restricted' of this fork, i.e., solving with decisions
// restricted to some variables (as for a connected component in d4) while
// the trail of the persistent assumptions is kept: results and partial
// models, per-call and persistent assumptions, the variable list, limits,
// unrestricted solving afterwards, and finally random formulas with
// aggressive inprocessing (including 'compact') during restricted search
// checked against reference solvers.  The checks do not depend on 'assert',
// so they also run in optimized builds.

#include "../../src/cadical.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <vector>

using namespace CaDiCaL;
using std::vector;

static int checked;

#define CHECK(COND) \
  do { \
    checked++; \
    if (COND) \
      break; \
    fprintf (stderr, "restricted_solving: check '%s' failed at line %d\n", \
             #COND, __LINE__); \
    exit (1); \
  } while (0)

/*------------------------------------------------------------------------*/

// The full 3-CNF over 'a', 'b' and 'c' is unsatisfiable, but it has neither
// units nor binary clauses, thus only search refutes it.  Without the
// clause '(a | b | c)' its only model is '-a -b -c'.

static void full_cnf (Solver &s, int a, int b, int c, bool all = true) {
  for (int i = all ? 0 : 1; i < 8; i++)
    s.clause (i & 1 ? -a : a, i & 2 ? -b : b, i & 4 ? -c : c);
}

static void freeze_all (Solver &s) {
  for (int v = 1; v <= s.vars (); v++)
    s.freeze (v);
}

/*------------------------------------------------------------------------*/

static void test_components () {
  // Two independent components, '(1 | 2), (-1 | 2)' over 1-2 and the full
  // 3-CNF without '(3 | 4 | 5)' over 3-5 with the single model '-3 -4 -5'.
  Solver s;
  s.clause (1, 2);
  s.clause (-1, 2);
  full_cnf (s, 3, 4, 5, false);
  freeze_all (s);

  const vector<int> first = {1, 2}, second = {3, 4, 5};
  CHECK (s.solve_restricted (first) == 10);
  CHECK (s.trail_value (1));
  CHECK (s.trail_value (2) == 2);
  for (const auto &v : second)
    CHECK (!s.trail_value (v)); // not decided (other component)

  // Under the assumption '3' only the second component is unsatisfiable
  // (and thus the formula), which the first restricted search does not see
  // (as long as nothing is learned about the second component).
  s.push_assumption (3);
  CHECK (s.solve_restricted (first) == 10);
  CHECK (s.trail_value (2) == 2);
  CHECK (s.solve_restricted (second) == 20);
  CHECK (s.failed (3));
  CHECK (s.solve () == 20);
  CHECK (s.failed (3));
  s.pop_assumption (3);

  CHECK (s.solve_restricted (second) == 10);
  for (const auto &v : second)
    CHECK (s.trail_value (v) == -v); // the single model
  CHECK (!s.trail_value (1));

  // The assumptions are decided and propagated first, thus their conflicts
  // are found by every restricted search.
  s.push_assumption (-2);
  CHECK (s.solve_restricted (first) == 20);
  CHECK (s.failed (-2));
  CHECK (s.solve_restricted (second) == 20);
  CHECK (s.failed (-2));
  s.pop_assumption (-2);
  CHECK (s.solve () == 10);
}

static void test_unsatisfiable_formula () {
  // An unsatisfiable component makes the formula unsatisfiable, and the
  // learned empty clause then also the other restricted searches.
  Solver s;
  s.clause (1, 2);
  full_cnf (s, 3, 4, 5);
  freeze_all (s);
  const vector<int> first = {1, 2}, second = {3, 4, 5};
  CHECK (s.solve_restricted (first) == 10);
  CHECK (s.solve_restricted (second) == 20);
  CHECK (s.solve_restricted (first) == 20);
  CHECK (s.solve () == 20);
}

static void test_assumptions () {
  Solver s;
  s.clause (1, 2);
  s.clause (-1, 2);
  s.clause (3, 4); // second component
  freeze_all (s);
  const vector<int> component = {1, 2};

  // Per-call assumptions are used once, persistent ones are kept.
  s.push_assumption (1);
  s.assume (-2);
  CHECK (s.solve_restricted (component) == 20);
  CHECK (s.failed (-2));
  CHECK (s.failed (1)); // '1' implies '2'
  CHECK (s.solve_restricted (component) == 10);
  CHECK (s.trail_value (1) == 1);
  CHECK (s.trail_value (2) == 2);
  CHECK (!s.trail_value (3));
  CHECK (!s.trail_value (4));

  // Persistent assumptions outside of the component are only propagated.
  s.push_assumption (-3);
  CHECK (s.solve_restricted (component) == 10);
  CHECK (s.trail_value (4) == 4);
  s.push_assumption (-4);
  CHECK (s.solve_restricted (component) == 20);
  CHECK (s.failed (-3));
  CHECK (s.failed (-4));
  CHECK (!s.failed (1));
  s.pop_assumption (-4);
  s.pop_assumption (-3);
  s.pop_assumption (1);

  s.assume (-2);
  CHECK (s.solve_restricted (component) == 20);
  CHECK (s.failed (-2));
  CHECK (s.solve_restricted (component) == 10);
  CHECK (s.trail_value (2) == 2);
  CHECK (s.solve () == 10);
}

static void test_variable_lists () {
  Solver s;
  s.clause (1, 2);
  s.clause (-1, 2);
  s.clause (-3, 4);
  freeze_all (s);
  const int vars = s.vars ();

  // Duplicates and undeclared variables are ignored.
  vector<int> component = {2, 1, 2, 1, 7, 100};
  CHECK (s.solve_restricted (component) == 10);
  CHECK (s.vars () == vars);
  CHECK (!s.trail_value (7));
  CHECK (!s.trail_value (-100));
  CHECK (s.trail_value (1));
  CHECK (s.trail_value (2) == 2);
  CHECK (!s.trail_value (3));
  CHECK (!s.trail_value (4));

  // Without variables only the assumptions are decided and propagated.
  const vector<int> none;
  CHECK (s.solve_restricted (none) == 10);
  s.push_assumption (3);
  CHECK (s.solve_restricted (none) == 10);
  CHECK (s.trail_value (4) == 4);
  CHECK (!s.trail_value (1));
  CHECK (!s.trail_value (2));
  s.push_assumption (-4);
  CHECK (s.solve_restricted (none) == 20);
  CHECK (s.failed (3));
  CHECK (s.failed (-4));
  s.pop_assumption (-4);
  s.pop_assumption (3);
}

static void test_partial_model () {
  // Ten independent components '(v | v+1 | v+2), (-v | -v+1)' (one each
  // three variables).  Only the restricted ones are decided, and 'val'
  // agrees with 'trail_value' on them.
  Solver s;
  for (int v = 1; v <= 30; v += 3) {
    s.clause (v, v + 1, v + 2);
    s.clause (-v, -(v + 1));
  }
  freeze_all (s);
  for (int first = 1; first <= 30; first += 3) {
    const vector<int> component = {first, first + 1, first + 2};
    CHECK (s.solve_restricted (component) == 10);
    for (int v = 1; v <= 30; v++) {
      const bool restricted = first <= v && v < first + 3;
      CHECK (!s.trail_value (v) == !restricted);
      if (restricted)
        CHECK (s.val (v) == s.trail_value (v));
    }
    CHECK (s.val (first) == first || s.val (first + 1) == first + 1 ||
           s.val (first + 2) == first + 2);
    CHECK (s.val (first) == -first || s.val (first + 1) == -(first + 1));
  }
}

static void test_limits () {
  Solver s;
  full_cnf (s, 1, 2, 3); // needs conflicts
  s.clause (-4, 5);
  freeze_all (s);
  const vector<int> component = {1, 2, 3};
  s.limit ("conflicts", 0);
  CHECK (s.solve_restricted (component) == 0);

  // Limits only hold for one call, also for 'propagate' afterwards.
  s.push_assumption (4);
  CHECK (s.propagate () == 0);
  CHECK (s.trail_value (5) == 5);
  s.limit ("conflicts", 0);
  CHECK (s.solve_restricted (component) == 0);
  CHECK (s.propagate () == 0);
  CHECK (s.trail_value (5) == 5);
  CHECK (s.solve_restricted (component) == 20);
  CHECK (!s.failed (4)); // the formula is unsatisfiable
  s.pop_assumption (4);
}

static void test_keeps_trail () {
  // Restricted searches keep the trail of the persistent assumptions (here
  // a long implication chain) and thus do not propagate it again.
  Solver s;
  const int n = 1000;
  for (int v = 1; v < n; v++)
    s.clause (-v, v + 1);
  s.clause (n + 1, n + 2); // the component
  freeze_all (s);
  s.push_assumption (1);
  const vector<int> component = {n + 1, n + 2};
  CHECK (s.solve_restricted (component) == 10);
  const int64_t before = s.get_statistic_value ("propagations");
  for (int i = 0; i < 10; i++) {
    CHECK (s.solve_restricted (component) == 10);
    CHECK (s.trail_value (n) == n);
  }
  CHECK (s.get_statistic_value ("propagations") - before < n);
  s.pop_assumption (1);
}

static void test_unrestricted_afterwards () {
  // After restricted searches all variables are decided again ('solve'),
  // and the full decision heap is restored for 'lookahead' and cubes.
  for (int round = 0; round < 3; round++) {
    Solver s;
    if (round == 1)
      s.set ("stabilizeonly", 1);
    for (int v = 1; v <= 20; v += 2)
      s.clause (v, v + 1);
    full_cnf (s, 21, 22, 23, false);
    freeze_all (s);
    const vector<int> component = {1, 2};
    CHECK (s.solve_restricted (component) == 10);
    CHECK (s.solve_restricted (component) == 10);
    if (round == 0) {
      CHECK (s.solve () == 10);
      for (int v = 1; v <= 20; v += 2)
        CHECK (s.val (v) == v || s.val (v + 1) == v + 1);
      CHECK (s.val (21) == -21 && s.val (22) == -22 && s.val (23) == -23);
    } else if (round == 1) {
      const int lit = s.lookahead ();
      CHECK (abs (lit) <= s.vars ());
      CHECK (s.solve () == 10);
    } else {
      Solver::CubesWithStatus cubes = s.generate_cubes (3);
      CHECK (cubes.status == 0 || cubes.status == 10);
      bool satisfiable = cubes.status == 10; // without cubes
      for (const auto &cube : cubes.cubes) {
        for (const auto &lit : cube) {
          CHECK (lit);
          CHECK (abs (lit) <= s.vars ());
          s.assume (lit);
        }
        const int res = s.solve ();
        CHECK (res == 10 || res == 20);
        satisfiable |= res == 10;
      }
      CHECK (satisfiable);
    }
  }
}

/*------------------------------------------------------------------------*/

// Random formulas with root-level units (all assumed, as the 'implied'
// literals in d4) and weakly connected random 3-SAT blocks.  Inprocessing
// and compacting are forced to run often to check restricted search with
// variables renumbered and more decision levels than variables.

static uint64_t rng;

static uint64_t next () {
  uint64_t z = (rng += 0x9e3779b97f4a7c15ull);
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ull;
  z = (z ^ (z >> 27)) * 0x94d049bb133111ebull;
  return z ^ (z >> 31);
}

static int pick (int lo, int hi) {
  return lo + (int) (next () % (uint64_t) (hi - lo + 1));
}

static int reference (const vector<vector<int>> &clauses,
                      const vector<int> &assumptions) {
  Solver r;
  for (const auto &c : clauses) {
    for (const auto &lit : c)
      r.add (lit);
    r.add (0);
  }
  for (const auto &lit : assumptions)
    r.assume (lit);
  return r.solve ();
}

static int find_root (vector<int> &uf, int x) {
  while (uf[x] != x)
    x = uf[x] = uf[uf[x]];
  return x;
}

static void check_core (Solver &s, const vector<vector<int>> &clauses,
                        const vector<int> &assumptions) {
  vector<int> core;
  for (const auto &lit : assumptions)
    if (s.failed (lit))
      core.push_back (lit);
  CHECK (reference (clauses, core) == 20);
}

static void test_removed_variables () {
  // Variables removed by 'compact' (here eliminated ones, not frozen) are
  // skipped and have no value on the trail.  The second 'solve' starts on
  // the root level after conflicts and thus compacts first.
  rng = 3;
  Solver s;
  s.set ("compactint", 1);
  s.set ("compactmin", 1);
  s.set ("compactlim", 0);
  s.set ("lucky", 0);
  for (int v = 1; v < 20; v++)
    s.clause (-v, v + 1); // eliminated
  const int n = 100;      // random formula on 21-120 (frozen)
  for (int i = 0; i < 38 * n / 10; i++) {
    for (int j = 0; j < 3; j++) {
      const int v = 20 + pick (1, n);
      s.add (pick (0, 1) ? v : -v);
    }
    s.add (0);
  }
  for (int v = 21; v <= 20 + n; v++)
    s.freeze (v);
  CHECK (s.simplify (2) == 0);
  CHECK (s.get_statistic_value ("eliminated") > 0);
  CHECK (s.solve () == 10);
  CHECK (s.get_statistic_value ("conflicts") > 0);
  CHECK (s.solve () == 10);
  vector<int> all (20 + n);
  std::iota (all.begin (), all.end (), 1);
  CHECK (s.solve_restricted (all) == 10);
  for (int v = 21; v <= 20 + n; v++)
    CHECK (s.trail_value (v));
  int unassigned = 0;
  for (int v = 1; v <= 20; v++)
    unassigned += !s.trail_value (v);
  CHECK (unassigned > 0); // eliminated and removed
}

static void test_hard_component () {
  // A single restricted search with many conflicts, with rephasing forced
  // often (which would walk and thus assign all variables), and with local
  // search and preprocessing limits set (they are ignored when restricted).
  for (int round = 0; round < 6; round++) {
    rng = 1000 + round;
    const int n = 120;
    Solver s;
    s.set ("rephaseint", 1);
    if (round & 1)
      s.set ("stabilizeonly", 1);
    vector<vector<int>> clauses;
    for (int i = 0; i < 426 * n / 100; i++) {
      vector<int> c;
      for (int j = 0; j < 3; j++) {
        const int v = pick (1, n);
        c.push_back (pick (0, 1) ? v : -v);
      }
      clauses.push_back (c);
    }
    for (const auto &c : clauses) {
      for (const auto &lit : c)
        s.add (lit);
      s.add (0);
    }
    s.clause (n + 1, n + 2); // second component
    freeze_all (s);
    if (round == 2 || round == 3)
      s.push_assumption (n + 1);
    if (round >= 4) {
      s.limit ("localsearch", 1);
      s.limit ("preprocessing", 1);
    }
    vector<int> component (n);
    std::iota (component.begin (), component.end (), 1);
    const int res = s.solve_restricted (component);
    CHECK (res == reference (clauses, vector<int> ()));
    CHECK (!s.trail_value (n + 2));
    if (res == 10)
      for (const auto &v : component)
        CHECK (s.trail_value (v));
  }
}

static void test_random (int seeds) {
  for (int seed = 1; seed <= seeds; seed++) {
    rng = (uint64_t) seed * 0x2545F4914F6CDD1Dull + 3;
    Solver s;
    s.set ("seed", seed);
    s.set ("compactint", 1);
    s.set ("compactmin", 1);
    s.set ("compactlim", 0);
    s.set ("inprobeint", pick (1, 5));
    s.set ("elimint", pick (1, 5));
    s.set ("reduceinit", pick (1, 20));
    s.set ("reduceint", pick (2, 10));
    s.set ("chrono", pick (0, 2));
    s.set ("vivifyirred", pick (0, 1));
    if (pick (0, 1))
      s.set ("stabilizeonly", 1);
    if (pick (0, 1))
      s.set ("restartint", 1);
    if (pick (0, 1))
      s.set ("phase", 0);

    const int units = pick (0, 12), blocks = pick (1, 3);
    const int size = pick (8, 22), n = units + blocks * size;
    vector<vector<int>> clauses;
    vector<int> fixed;
    for (int v = 1; v <= units; v++) {
      fixed.push_back (pick (0, 1) ? v : -v);
      clauses.push_back (vector<int> (1, fixed.back ()));
    }
    for (int b = 0; b < blocks; b++) {
      const int m = size * pick (38, 45) / 10;
      for (int i = 0; i < m; i++) {
        vector<int> c;
        for (int j = 0; j < 3; j++) {
          // Some literals on fixed variables, falsified or satisfied.
          const int v = units && !pick (0, 7)
                            ? pick (1, units)
                            : units + b * size + pick (1, size);
          c.push_back (pick (0, 1) ? v : -v);
        }
        clauses.push_back (c);
      }
    }
    for (int i = 1; i < blocks; i++) // bridges between the blocks
      if (pick (0, 1)) {
        vector<int> c;
        for (int j = 0; j < 3; j++) {
          const int v = pick (units + 1, n);
          c.push_back (pick (0, 1) ? v : -v);
        }
        clauses.push_back (c);
      }
    for (const auto &c : clauses) {
      for (const auto &lit : c)
        s.add (lit);
      s.add (0);
    }
    freeze_all (s);

    vector<int> stack;
    for (const auto &lit : fixed)
      if (pick (0, 3)) {
        s.push_assumption (lit);
        stack.push_back (lit);
      }

    for (int step = 0; step < 40; step++) {
      const int op = pick (0, 9);
      if (op < 3) {
        const int v = pick (1, n);
        const int lit = pick (0, 1) ? v : -v;
        s.push_assumption (lit);
        stack.push_back (lit);
      } else if (op < 4 && !stack.empty ()) {
        s.pop_assumption (stack.back ());
        stack.pop_back ();
      } else if (op < 5) {
        const int res = s.solve ();
        CHECK (res == reference (clauses, stack));
        if (res == 10)
          for (const auto &c : clauses) {
            bool satisfied = false;
            for (const auto &lit : c)
              satisfied |= s.val (lit) == lit;
            CHECK (satisfied);
          }
        else
          check_core (s, clauses, stack);
      } else { // restricted to a component of the residual formula
        if (s.propagate () == 20) {
          CHECK (reference (clauses, stack) == 20);
          continue;
        }
        vector<int> trail;
        for (int v = 1; v <= n; v++)
          if (s.trail_value (v))
            trail.push_back (s.trail_value (v));
        vector<int> uf (n + 1);
        std::iota (uf.begin (), uf.end (), 0);
        vector<char> used (n + 1, 0);
        for (const auto &c : clauses) {
          bool satisfied = false;
          for (const auto &lit : c)
            satisfied |= s.trail_value (lit) == lit;
          if (satisfied)
            continue;
          int first = 0;
          for (const auto &lit : c) {
            if (s.trail_value (lit))
              continue;
            const int v = abs (lit);
            used[v] = 1;
            if (first)
              uf[find_root (uf, v)] = find_root (uf, first);
            else
              first = v;
          }
        }
        int root = 0;
        for (int v = 1; v <= n && !root; v++)
          if (used[v] && !pick (0, 2))
            root = find_root (uf, v);
        if (!root)
          continue;
        vector<int> component;
        vector<char> in (n + 1, 0);
        for (int v = 1; v <= n; v++)
          if (used[v] && find_root (uf, v) == root)
            component.push_back (v), in[v] = 1;
        vector<vector<int>> local;
        for (const auto &c : clauses)
          for (const auto &lit : c)
            if (in[abs (lit)]) {
              local.push_back (c);
              break;
            }
        // Persistent assumptions and per-call ones on the component.
        vector<int> assumptions = stack;
        const int per_call = pick (0, 3) ? 0 : pick (1, 2);
        for (int i = 0; i < per_call; i++) {
          const int v = component[pick (0, (int) component.size () - 1)];
          const int lit = pick (0, 1) ? v : -v;
          s.assume (lit);
          assumptions.push_back (lit);
          trail.push_back (lit);
        }
        const int res = s.solve_restricted (component);
        CHECK (res == 10 || res == 20);
        if (reference (clauses, assumptions) == 10)
          CHECK (res == 10);
        if (reference (local, trail) == 20)
          CHECK (res == 20);
        if (res == 10) {
          for (const auto &v : component)
            CHECK (s.trail_value (v));
          for (const auto &lit : assumptions)
            CHECK (s.trail_value (lit) == lit);
          for (const auto &c : local) {
            bool satisfied = false;
            for (const auto &lit : c)
              satisfied |= s.trail_value (lit) == lit;
            CHECK (satisfied);
          }
        } else
          check_core (s, clauses, assumptions);
      }
    }
  }
}

/*------------------------------------------------------------------------*/

int main () {
  test_components ();
  test_unsatisfiable_formula ();
  test_assumptions ();
  test_variable_lists ();
  test_removed_variables ();
  test_partial_model ();
  test_limits ();
  test_keeps_trail ();
  test_unrestricted_afterwards ();
  test_hard_component ();
  test_random (150);
  printf ("restricted_solving: %d checks passed\n", checked);
  return 0;
}
