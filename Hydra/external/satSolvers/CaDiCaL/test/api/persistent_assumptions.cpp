// NEW_FILE
// Tests the persistent assumptions ('push_assumption', 'pop_assumption'),
// 'implied_by_last_assumption', 'trail_value' and 'trail_above_root' of
// this fork (the checks do not depend on 'assert', so they also run in
// optimized builds), first on
// small fixed formulas, then on random formulas against reference solvers
// (together with 'solve_restricted', see also 'restricted_solving.cpp').

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
    fprintf (stderr, \
             "persistent_assumptions: check '%s' failed at line %d\n", \
             #COND, __LINE__); \
    exit (1); \
  } while (0)

/*------------------------------------------------------------------------*/

// Fixed small formulas.

static void test_push_pop () {
  Solver s;
  s.clause (1, 2);
  s.clause (-1, 3);
  s.clause (-2, 3);
  s.clause (-3, 4, 5);

  s.push_assumption (-4);
  CHECK (s.solve () == 10);
  CHECK (s.val (3) == 3); // implied by '(1 | 2)'
  CHECK (s.val (-4) == -4);

  // Persistent assumptions survive 'solve' (unlike 'assume').
  CHECK (s.solve () == 10);
  CHECK (s.val (-4) == -4);

  s.push_assumption (-5);
  CHECK (s.solve () == 20);
  CHECK (s.failed (-4));
  CHECK (s.failed (-5));

  s.pop_assumption (-5);
  CHECK (s.solve () == 10);
  CHECK (s.val (5) == 5);

  // A duplicated and a clashing push.
  s.push_assumption (-4);
  CHECK (s.solve () == 10);
  s.push_assumption (4);
  CHECK (s.solve () == 20);
  CHECK (s.failed (4));
  s.pop_assumption (4);
  s.pop_assumption (-4);
  s.pop_assumption (-4);
  CHECK (s.solve () == 10);

  // Per-call assumptions on top are reset as usual.
  s.push_assumption (1);
  s.assume (-3);
  CHECK (s.solve () == 20);
  CHECK (s.solve () == 10); // '-3' is gone, '1' is still assumed
  CHECK (s.val (1) == 1);
  s.pop_assumption (1);
}

static void test_implied () {
  Solver s;
  s.clause (-1, 2);
  s.clause (-2, 3);
  s.clause (-4, 5);
  s.clause (6);    // root-level unit
  s.clause (7, 8); // keeps 'propagate' from assigning all variables

  vector<int> last = {42};
  CHECK (s.propagate () == 0);
  s.implied_by_last_assumption (last);
  CHECK (last.empty ()); // without assumptions (and cleared)

  s.push_assumption (4);
  CHECK (s.propagate () == 0);
  s.implied_by_last_assumption (last);
  CHECK (std::find (last.begin (), last.end (), 4) != last.end ());
  CHECK (std::find (last.begin (), last.end (), 5) != last.end ());

  s.push_assumption (1);
  CHECK (s.propagate () == 0);
  s.implied_by_last_assumption (last);
  CHECK (last.size () == 3); // '1', '2' and '3' (not '4' nor '5')
  CHECK (std::find (last.begin (), last.end (), 5) == last.end ());

  CHECK (s.trail_value (2) == 2);
  CHECK (s.trail_value (-3) == 3);
  CHECK (s.trail_value (5) == 5);
  CHECK (s.trail_value (6) == 6); // root-level unit
  CHECK (s.fixed (6) == 1);

  vector<int> implied;
  s.implied (implied);
  for (const auto &lit : last)
    CHECK (std::find (implied.begin (), implied.end (), lit) !=
           implied.end ());

  s.push_assumption (3); // already implied
  CHECK (s.propagate () == 0);
  s.implied_by_last_assumption (last);
  CHECK (last.empty ());
  s.pop_assumption (3);

  s.pop_assumption (1);
  CHECK (s.propagate () == 0);
  CHECK (s.trail_value (1) == 0);
  CHECK (s.trail_value (2) == 0);
  CHECK (s.trail_value (5) == 5);
  s.pop_assumption (4);
}

static void test_trail_above_root () {
  Solver s;
  s.clause (-1, 2);
  s.clause (-2, -3);
  s.clause (7); // root-level unit
  s.push_assumption (1);
  s.push_assumption (3);
  CHECK (s.solve () == 20);
  vector<int> lits;
  s.trail_above_root (lits);
  CHECK (!lits.empty ());
  for (const auto &lit : lits) {
    CHECK (s.trail_value (lit) == lit);
    CHECK (!s.fixed (lit));
  }
  CHECK (std::find (lits.begin (), lits.end (), 7) == lits.end ());
  s.pop_assumption (3);
  CHECK (s.propagate () == 0);
  s.trail_above_root (lits);
  CHECK (lits.size () == 3); // exactly '1', '2' and '-3' in trail order
  CHECK (lits[0] == 1);
  CHECK (lits[1] == 2);
  CHECK (lits[2] == -3);
  for (int v = 1; v <= s.vars (); v++)
    if (s.trail_value (v) && !s.fixed (v))
      CHECK (std::find (lits.begin (), lits.end (), s.trail_value (v)) !=
             lits.end ());
}

static void test_duplicates () {
  // Popping one of two copies of a persistent assumption keeps the other.
  Solver s;
  s.clause (-1, 2);
  s.clause (-2, -3);
  s.push_assumption (1);
  s.push_assumption (1);
  s.pop_assumption (1);
  s.push_assumption (3);
  CHECK (s.solve () == 20);
  CHECK (s.failed (1));
  CHECK (s.failed (3));
  s.pop_assumption (3);
  s.pop_assumption (1);
  CHECK (s.solve () == 10);

  // Resetting the same assumption from 'assume' keeps the persistent one.
  s.push_assumption (3);
  s.assume (3);
  CHECK (s.solve () == 10);
  CHECK (s.val (-1) == -1); // '3' implies '-2' and '-1'
  s.assume (1);
  CHECK (s.solve () == 20);
  CHECK (s.failed (1));
  CHECK (s.failed (3));
  s.pop_assumption (3);
  s.assume (1);
  CHECK (s.solve () == 10);

  // Popped assumptions can be assumed again (are not marked as assumed).
  s.assume (3);
  s.assume (1);
  CHECK (s.solve () == 20);
  CHECK (s.failed (1));
  CHECK (s.failed (3));
}

static void test_reset_assumptions () {
  // 'reset_assumptions' and 'simplify' keep persistent assumptions.
  Solver s;
  s.clause (-1, 2);
  s.clause (-3, -2);
  s.push_assumption (1);
  s.assume (3);
  s.reset_assumptions ();
  CHECK (s.solve () == 10);
  CHECK (s.val (1) == 1);
  CHECK (s.val (3) == -3);
  s.assume (3);
  CHECK (s.solve () == 20);
  CHECK (s.failed (1));
  CHECK (s.failed (3));
  CHECK (s.simplify () != 20);
  CHECK (s.solve () == 10);
  CHECK (s.val (1) == 1);
  s.pop_assumption (1); // still on the stack
  s.assume (3);
  CHECK (s.solve () == 10);
  CHECK (s.val (1) == -1);

  // Also after inconclusive calls only the assumptions from 'assume' are
  // reset.  Here '1' implies the full 3-CNF over 2-4 (refuted by search).
  Solver t;
  for (int i = 0; i < 8; i++)
    t.clause (-1, i & 1 ? -2 : 2, i & 2 ? -3 : 3, i & 4 ? -4 : 4);
  t.clause (-5, 6);
  t.push_assumption (5);
  t.assume (1);
  CHECK (t.propagate () == 0);
  CHECK (t.solve () == 10); // without '1'
  CHECK (t.val (6) == 6);
  t.assume (1);
  t.limit ("conflicts", 0);
  CHECK (t.solve () == 0);
  CHECK (t.solve () == 10); // without '1'
  CHECK (t.val (-1) == -1);
  t.pop_assumption (5);
}

static void test_propagate_after_limit () {
  // After 'solve' ran into a limit, 'propagate' still decides all
  // persistent assumptions (limits only hold for one call).
  Solver s;
  for (int i = 0; i < 8; i++) // unsatisfiable, but only by search
    s.clause (i & 1 ? -1 : 1, i & 2 ? -2 : 2, i & 4 ? -3 : 3);
  s.clause (-4, 5);
  s.clause (-5, 6);
  s.clause (-7, 8);
  for (int v = 1; v <= 8; v++)
    s.freeze (v);
  s.push_assumption (4);
  for (int round = 0; round < 2; round++) {
    s.limit (round ? "decisions" : "conflicts", 0);
    CHECK (s.solve () == 0);
    CHECK (s.propagate () == 0);
    CHECK (s.trail_value (6) == 6);
    vector<int> last;
    s.implied_by_last_assumption (last);
    CHECK (last.size () == 3); // '4', '5' and '6'
  }
  // A limit can also stop 'propagate' before deciding the last assumption.
  s.push_assumption (7);
  s.limit ("conflicts", 0);
  CHECK (s.propagate () == 0);
  vector<int> last;
  s.implied_by_last_assumption (last);
  CHECK (last.empty ());
  CHECK (!s.trail_value (8));
  CHECK (s.propagate () == 0);
  CHECK (s.trail_value (8) == 8);
  s.pop_assumption (7);
  CHECK (s.solve () == 20);
  CHECK (!s.failed (4));
  s.pop_assumption (4);
}

static void test_assume_keeps_trail () {
  // Assumptions from 'assume' on top do not change the trail of persistent
  // assumptions (here a long implication chain), thus 'solve_restricted'
  // does not propagate it again, while 'solve' starts from the root level.
  Solver s;
  s.set ("lucky", 0);
  const int n = 1000;
  for (int v = 1; v < n; v++)
    s.clause (-v, v + 1);
  s.clause (n + 1, n + 2);
  s.clause (-n, -(n + 3));
  s.push_assumption (1);
  s.push_assumption (n / 2); // already implied
  const vector<int> component = {n + 1, n + 2};
  CHECK (s.solve_restricted (component) == 10);
  int64_t before = s.get_statistic_value ("propagations");
  for (int i = 0; i < 10; i++) {
    s.assume (n + 1);
    CHECK (s.solve_restricted (component) == 10);
    CHECK (s.trail_value (n) == n);
    CHECK (s.trail_value (n + 1) == n + 1);
    CHECK (s.trail_value (n + 3) == -(n + 3));
  }
  CHECK (s.get_statistic_value ("propagations") - before < n);
  before = s.get_statistic_value ("propagations");
  CHECK (s.solve () == 10);
  CHECK (s.val (n) == n);
  CHECK (s.get_statistic_value ("propagations") - before >= n - 1);
  s.push_assumption (n + 3);
  CHECK (s.solve () == 20);
  CHECK (s.failed (1));
  CHECK (s.failed (n + 3));
  CHECK (!s.failed (n / 2));
  s.pop_assumption (n + 3);
  CHECK (s.solve () == 10);
}

static void test_model_after_propagate () {
  // If 'propagate' assigns all variables, 'val' gives this model and not
  // an earlier one (pushing resets the extended solution).
  Solver s;
  s.clause (1, 2);
  s.clause (-1, -2);
  CHECK (s.solve () == 10);
  const int lit = s.val (1);
  s.push_assumption (-lit); // flips both variables
  CHECK (s.propagate () == 10);
  CHECK (s.val (1) == -lit);
  CHECK (s.val (2) == (lit > 0 ? 2 : -2));
  s.pop_assumption (-lit);
}

static void test_propagate_keeps_trail () {
  // 'propagate' keeps the trail of the persistent assumptions (here a long
  // implication chain) and only propagates what changed, e.g., when probing
  // literals with 'push_assumption', 'propagate' and 'pop_assumption'.
  Solver s;
  const int n = 1000;
  for (int v = 1; v < n; v++)
    s.clause (-v, v + 1);
  for (int v = n + 1; v <= n + 20; v++)
    s.clause (-v, -(v + 1));
  s.push_assumption (1);
  CHECK (s.propagate () == 0);
  const int64_t before = s.get_statistic_value ("propagations");
  for (int v = n + 1; v <= n + 20; v++) {
    s.push_assumption (v);
    CHECK (s.propagate () == 0);
    CHECK (s.trail_value (n) == n);
    CHECK (s.trail_value (v + 1) == -(v + 1));
    s.pop_assumption (v);
  }
  CHECK (s.get_statistic_value ("propagations") - before < n);
  s.pop_assumption (1);
}

static void test_melted () {
  // Persistent assumptions freeze their variables only while pushed, thus
  // afterwards variables are eliminated as without them.
  int64_t eliminated[2];
  for (int pushed = 0; pushed <= 1; pushed++) {
    Solver s;
    for (int v = 1; v < 20; v++)
      s.clause (-v, v + 1);
    if (pushed) {
      for (int v = 1; v < 20; v += 2)
        s.push_assumption (v);
      CHECK (s.propagate () != 20);
      for (int v = 19; v >= 1; v -= 2)
        s.pop_assumption (v);
    }
    CHECK (s.simplify () != 20);
    eliminated[pushed] = s.get_statistic_value ("eliminated");
  }
  CHECK (eliminated[0] > 0);
  CHECK (eliminated[0] == eliminated[1]);
}

static void test_extension_variables () {
  // Bounded variable addition ('factor') replaces the 25 clauses '(a | b)'
  // ('a' in 1-5, 'b' in 6-10) by '(a | x)' and '(-x | b)' with a new
  // extension variable 'x', which is assigned but never reported.
  Solver s;
  s.set ("factor", 1);
  s.declare_more_variables (10);
  for (int a = 1; a <= 5; a++)
    for (int b = 6; b <= 10; b++)
      s.clause (a, b);
  for (int v = 1; v <= 10; v++)
    s.freeze (v);
  CHECK (s.simplify (1) == 0);
  CHECK (s.vars () == 11); // the extension variable
  s.push_assumption (-1);  // implies 'x' and thus 6-10
  CHECK (s.propagate () == 0);
  vector<int> lits;
  s.trail_above_root (lits);
  CHECK (lits.size () == 6); // '-1' and 6-10 but not 'x'
  s.implied_by_last_assumption (lits);
  CHECK (lits.size () == 6);
  for (const auto &lit : lits)
    CHECK (abs (lit) <= 10);
  for (int b = 6; b <= 10; b++)
    CHECK (s.trail_value (b) == b);
  s.pop_assumption (-1);
  CHECK (s.solve () == 10);
}

// Complete unit propagation on the original clauses (as needed by knowledge
// compilers) with 'vivifyirred=0': otherwise during 'simplify' vivification
// removes '(-14 | -9 | -5)' as implied by the other clauses, after which
// assuming '5' and '14' does not propagate '-9' anymore (the remaining
// clauses only steer the heuristics).  Reduced from the circuit 's400'.

// clang-format off
static const int vivify_regression[] = {
  -4, -5, 0,  4, 5, 0,  10, -1, 0,  11, -1, 0,
  12, 7, 0,  -13, -8, -14, 0,  14, 9, 0,  14, 5, 0,
  -14, -9, -5, 0,  15, 16, 0,  -17, -10, -11, 0,  18, 19, 0,
  -2, -15, -18, 0,  -7, -4, 0,  -7, -6, 0,  -7, -3, 0,
  7, 4, 6, 3, 0,  -9, -6, 0,  -9, -3, 0,  9, 6, 3, 0,
  -16, -1, 0,  -19, -1, 0
};
// clang-format on

static void test_complete_propagation () {
  bool missed_by_default = false;
  for (int irredundant = 0; irredundant <= 1; irredundant++) {
    Solver s;
    s.set ("stabilizeonly", 1);
    s.set ("vivifyirred", irredundant);
    for (const auto &lit : vivify_regression)
      s.add (lit);
    for (int v = 1; v <= 19; v++)
      s.freeze (v);
    CHECK (s.solve () == 10);
    s.simplify ();
    s.push_assumption (5);
    s.push_assumption (14);
    CHECK (s.propagate () == 0);
    if (!irredundant)
      CHECK (s.trail_value (9) == -9);
    else
      missed_by_default = !s.trail_value (9);
  }
  printf ("persistent_assumptions: vivification regression %s\n",
          missed_by_default ? "is sensitive ('vivifyirred=1' misses '-9')"
                            : "is not triggered by the current heuristics");
}

static void test_compaction () {
  // Assumptions on root-level fixed variables, which 'compact' removes from
  // the trail and maps to the same internal variable, pushed before and
  // after compacting (as often as possible).
  Solver s;
  s.set ("compactint", 1);
  s.set ("compactmin", 1);
  s.set ("compactlim", 0);
  s.set ("lucky", 0);
  for (int v = 1; v <= 10; v++)
    s.clause (v);
  for (int i = 1; i < 8; i++) // single model '-11 -12 -13' (by search)
    s.clause (i & 1 ? -11 : 11, i & 2 ? -12 : 12, i & 4 ? -13 : 13);
  s.clause (-14, 15);
  for (int v = 1; v <= 15; v++)
    s.freeze (v);
  s.push_assumption (1);
  s.push_assumption (2);
  s.push_assumption (1);
  for (int i = 0; i < 3; i++) { // conflicts first, then compacting
    CHECK (s.solve () == 10);
    CHECK (s.val (11) == -11);
  }
  for (int v = 1; v <= 10; v++) {
    CHECK (s.fixed (v) == 1);
    CHECK (s.trail_value (v) == v);
    CHECK (s.trail_value (-v) == v);
  }
  vector<int> last;
  s.push_assumption (4); // already fixed
  CHECK (s.propagate () != 20);
  s.implied_by_last_assumption (last);
  CHECK (last.empty ());
  s.push_assumption (14);
  CHECK (s.propagate () != 20);
  s.implied_by_last_assumption (last);
  CHECK (last.size () == 2); // '14' and '15'
  CHECK (s.trail_value (15) == 15);
  s.push_assumption (-3); // falsified on the root level
  CHECK (s.solve () == 20);
  CHECK (s.failed (-3));
  CHECK (!s.failed (1));
  CHECK (!s.failed (14));
  s.pop_assumption (-3);
  CHECK (s.solve () == 10);
  CHECK (s.val (15) == 15);
  s.pop_assumption (14);
  s.pop_assumption (4);
  s.pop_assumption (1);
  s.pop_assumption (2);
  s.pop_assumption (1);
  CHECK (s.solve () == 10);
}

/*------------------------------------------------------------------------*/

// Random formulas with a few weakly connected blocks.

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
                      const vector<int> &assumptions, int extra = 0) {
  Solver r;
  for (const auto &c : clauses) {
    for (const auto &lit : c)
      r.add (lit);
    r.add (0);
  }
  for (const auto &lit : assumptions)
    r.assume (lit);
  if (extra)
    r.assume (extra);
  return r.solve ();
}

static int find_root (vector<int> &uf, int x) {
  while (uf[x] != x)
    x = uf[x] = uf[uf[x]];
  return x;
}

// Regression: every persistent assumption gets a decision level, also the
// ones on root-level fixed variables (d4 pushes all implied literals), and
// since 'compact' removes fixed variables there can be more decision levels
// than variables, which overflowed the level-indexed glue table 'gtab'.

static void test_more_levels_than_variables () {
  const int fixed = 600, hard = 40;
  rng = 7;
  Solver s;
  s.set ("compactint", 1);
  s.set ("compactmin", 1);
  s.set ("compactlim", 0);
  vector<vector<int>> clauses;
  for (int v = 1; v <= fixed; v++)
    clauses.push_back (vector<int> (1, v));
  for (int i = 0; i < 42 * hard / 10; i++) {
    vector<int> c;
    for (int j = 0; j < 3; j++) {
      const int v = fixed + pick (1, hard);
      c.push_back (pick (0, 1) ? v : -v);
    }
    clauses.push_back (c);
  }
  for (const auto &c : clauses) {
    for (const auto &lit : c)
      s.add (lit);
    s.add (0);
  }
  for (int v = 1; v <= fixed; v++)
    s.push_assumption (v);
  for (int round = 0; round < 40; round++) {
    const int v = fixed + pick (1, hard);
    const int lit = pick (0, 1) ? v : -v;
    s.push_assumption (lit);
    CHECK (s.solve () == reference (clauses, vector<int> (1, lit)));
    s.pop_assumption (lit);
  }
  for (int v = fixed; v >= 1; v--)
    s.pop_assumption (v);
  CHECK (s.solve () == reference (clauses, vector<int> ()));

  // New variables (more than levels used) after the table grew.
  for (int v = fixed + hard + 1; v < fixed + hard + 800; v++) {
    clauses.push_back (vector<int> ({-v, v + 1}));
    s.clause (-v, v + 1);
  }
  CHECK (s.solve () == reference (clauses, vector<int> ()));
}

// The result of 'implied_by_last_assumption' is exactly what became
// assigned by pushing and propagating the last assumption.

static void test_implied_exactly (int seeds) {
  for (int seed = 1; seed <= seeds; seed++) {
    rng = (uint64_t) seed * 0x9e3779b97f4a7c15ull + 11;
    const int n = pick (10, 40);
    Solver s;
    s.set ("chrono", pick (0, 2));
    for (int i = 0; i < 2 * n; i++) { // mostly binary clauses
      const int size = pick (0, 3) ? 2 : 3;
      for (int j = 0; j < size; j++) {
        const int v = pick (1, n);
        s.add (pick (0, 1) ? v : -v);
      }
      s.add (0);
    }
    if (s.propagate () == 20) // root-level units
      continue;
    vector<int> before, after, last;
    for (int step = 0; step < 20; step++) {
      before.clear ();
      for (int v = 1; v <= n; v++)
        if (s.trail_value (v))
          before.push_back (s.trail_value (v));
      const int v = pick (1, n);
      s.push_assumption (pick (0, 1) ? v : -v);
      if (s.propagate () == 20)
        break;
      after.clear ();
      for (int v = 1; v <= n; v++) {
        const int lit = s.trail_value (v);
        if (lit && std::find (before.begin (), before.end (), lit) ==
                       before.end ())
          after.push_back (lit);
      }
      s.implied_by_last_assumption (last);
      std::sort (last.begin (), last.end ());
      std::sort (after.begin (), after.end ());
      CHECK (last == after);
    }
  }
}

static void test_random (int seeds) {
  for (int seed = 1; seed <= seeds; seed++) {
    rng = (uint64_t) seed * 0x2545F4914F6CDD1Dull + 1;
    const int blocks = pick (2, 4), size = pick (3, 9);
    const int n = blocks * size;
    Solver s;
    const int vivifyirred = pick (0, 1);
    s.set ("vivifyirred", vivifyirred);
    if (pick (0, 1))
      s.set ("stabilizeonly", 1);
    s.set ("chrono", pick (0, 2));
    if (pick (0, 1))
      s.set ("compactint", pick (1, 20)), s.set ("compactmin", 1);
    if (pick (0, 1))
      s.set ("reduceinit", pick (1, 20)), s.set ("reduceint", pick (2, 10));
    if (pick (0, 1))
      s.set ("inprobeint", pick (1, 10));
    vector<vector<int>> clauses;
    for (int b = 0; b < blocks; b++)
      for (int i = 0; i < 4 * size; i++) {
        vector<int> c;
        for (int j = 0; j < 3; j++) {
          const int v = b * size + pick (1, size);
          c.push_back (pick (0, 1) ? v : -v);
        }
        clauses.push_back (c);
      }
    for (int i = 0; i < blocks; i++) { // bridges between the blocks
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
    for (int v = 1; v <= n; v++)
      s.freeze (v);

    vector<int> stack;
    for (int step = 0; step < 60; step++) {
      const int op = pick (0, 9);
      if (op < 3) {
        const int v = pick (1, n);
        const int lit = pick (0, 1) ? v : -v;
        s.push_assumption (lit);
        stack.push_back (lit);
      } else if (op < 5 && !stack.empty ()) {
        s.pop_assumption (stack.back ());
        stack.pop_back ();
      } else if (op < 6) {
        const int res = s.solve ();
        CHECK (res == reference (clauses, stack));
        if (res == 10)
          for (const auto &c : clauses) {
            bool satisfied = false;
            for (const auto &lit : c)
              satisfied |= s.val (lit) == lit;
            CHECK (satisfied);
          }
      } else if (op < 8) { // restricted on components of the residual
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
          if (used[v] && pick (0, 2) == 0)
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
        const int res = s.solve_restricted (component);
        CHECK (res == 10 || res == 20);
        if (reference (clauses, trail) == 10)
          CHECK (res == 10);
        if (reference (local, trail) == 20)
          CHECK (res == 20);
        if (res == 10) {
          for (const auto &v : component)
            CHECK (s.trail_value (v));
          for (const auto &c : local) {
            bool satisfied = false;
            for (const auto &lit : c)
              satisfied |= s.trail_value (lit) == lit;
            CHECK (satisfied);
          }
        }
      } else { // propagation and implied literals
        if (s.propagate () == 20) {
          CHECK (reference (clauses, stack) == 20);
          continue;
        }
        vector<int> implied;
        s.implied (implied);
        for (const auto &lit : implied) {
          CHECK (s.trail_value (lit) == lit);
          CHECK (reference (clauses, stack, -lit) == 20);
        }
        if (!stack.empty ()) {
          vector<int> last;
          s.implied_by_last_assumption (last);
          for (const auto &lit : last)
            CHECK (std::find (implied.begin (), implied.end (), lit) !=
                   implied.end ());
        }
        // With 'vivifyirred=0' (and frozen variables) unit propagation
        // is complete for the original clauses: none is unit or empty.
        if (!vivifyirred)
          for (const auto &c : clauses) {
            bool satisfied = false;
            int unassigned = 0;
            for (const auto &lit : c) {
              const int value = s.trail_value (lit);
              satisfied |= value == lit;
              unassigned += !value;
            }
            CHECK (satisfied || unassigned > 1);
          }
      }
    }
  }
}

/*------------------------------------------------------------------------*/

int main () {
  test_push_pop ();
  test_duplicates ();
  test_implied ();
  test_trail_above_root ();
  test_extension_variables ();
  test_reset_assumptions ();
  test_propagate_after_limit ();
  test_model_after_propagate ();
  test_propagate_keeps_trail ();
  test_assume_keeps_trail ();
  test_melted ();
  test_complete_propagation ();
  test_compaction ();
  test_more_levels_than_variables ();
  test_implied_exactly (100);
  test_random (200);
  printf ("persistent_assumptions: %d checks passed\n", checked);
  return 0;
}
