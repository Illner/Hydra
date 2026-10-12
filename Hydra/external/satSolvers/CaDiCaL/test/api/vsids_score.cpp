// NEW_FILE
// Tests 'get_vsids_score' of this fork, i.e., reading the EVSIDS scores of
// variables (only bumped in stable mode), which has no side effects.  The
// checks do not depend on 'assert', so they also run in optimized builds.

#include "../../src/cadical.hpp"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace CaDiCaL;
using std::vector;

static int checked;

#define CHECK(COND) \
  do { \
    checked++; \
    if (COND) \
      break; \
    fprintf (stderr, "vsids_score: check '%s' failed at line %d\n", #COND, \
             __LINE__); \
    exit (1); \
  } while (0)

// The unsatisfiable pigeon hole formula ('holes + 1' pigeons in 'holes'
// holes) needs many conflicts.  Its variables start after 'offset'.

static int pigeon_hole (Solver &s, int holes, int offset = 0) {
  const int pigeons = holes + 1;
  for (int p = 0; p < pigeons; p++) {
    for (int h = 0; h < holes; h++)
      s.add (offset + p * holes + h + 1);
    s.add (0);
  }
  for (int h = 0; h < holes; h++)
    for (int p = 0; p < pigeons; p++)
      for (int q = p + 1; q < pigeons; q++)
        s.clause (-(offset + p * holes + h + 1),
                  -(offset + q * holes + h + 1));
  return offset + pigeons * holes;
}

static void freeze_all (Solver &s) {
  for (int v = 1; v <= s.vars (); v++)
    s.freeze (v);
}

static bool valid (double score) {
  return std::isfinite (score) && score >= 0;
}

/*------------------------------------------------------------------------*/

static void test_initial () {
  Solver s;
  const int n = pigeon_hole (s, 4);
  for (int v = 1; v <= n; v++)
    CHECK (s.get_vsids_score (v) == 0);
  CHECK (s.vars () == n); // nothing declared
}

static void test_stable () {
  // In stable mode the variables in conflicts are bumped, the others not.
  Solver s;
  s.set ("stabilizeonly", 1);
  const int n = pigeon_hole (s, 5);
  s.clause (n + 1, n + 2); // never in a conflict
  freeze_all (s);
  CHECK (s.solve () == 20);
  CHECK (s.get_statistic_value ("conflicts") > 0);
  double max = 0;
  for (int v = 1; v <= n; v++) {
    const double score = s.get_vsids_score (v);
    CHECK (valid (score));
    if (score > max)
      max = score;
  }
  CHECK (max > 0);
  CHECK (s.get_vsids_score (n + 1) == 0);
  CHECK (s.get_vsids_score (n + 2) == 0);
}

static void test_focused () {
  // Without stable mode only the queue is bumped (and not the scores).
  Solver s;
  s.set ("stabilize", 0);
  const int n = pigeon_hole (s, 5);
  CHECK (s.solve () == 20);
  CHECK (s.get_statistic_value ("conflicts") > 0);
  for (int v = 1; v <= n; v++)
    CHECK (s.get_vsids_score (v) == 0);
}

static void test_inactive () {
  // Root-level fixed variables and eliminated ones (both removed and the
  // others renumbered by 'compact') still have valid scores.
  Solver s;
  s.set ("stabilizeonly", 1);
  s.set ("compactint", 1);
  s.set ("compactmin", 1);
  s.set ("compactlim", 0);
  for (int v = 1; v <= 10; v++)
    s.clause (v); // fixed
  const int n = pigeon_hole (s, 5, 10);
  for (int v = n + 1; v < n + 20; v++)
    s.clause (-v, v + 1); // eliminated by 'simplify' (not frozen)
  for (int v = 11; v <= n; v++)
    s.freeze (v);
  CHECK (s.simplify (2) != 10);
  CHECK (s.get_statistic_value ("eliminated") > 0);
  CHECK (s.solve () == 20);
  bool positive = false;
  for (int v = 1; v <= s.vars (); v++) {
    const double score = s.get_vsids_score (v);
    CHECK (valid (score));
    positive |= v > 10 && v <= n && score > 0;
  }
  CHECK (positive);
}

/*------------------------------------------------------------------------*/

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

static int pick_literal (int n) {
  const int v = pick (1, n);
  return pick (0, 1) ? v : -v;
}

static void test_renumbered () {
  // After 'compact' removed the fixed variables 1-10 and renumbered the
  // others, the scores still belong to the right variables: the variables
  // 11-20 (in satisfiable binary clauses) are never in a conflict, unlike
  // most variables of the random formula after them.  The second 'solve'
  // starts on the root level with enough conflicts to compact first.
  rng = 7;
  Solver s;
  s.set ("stabilizeonly", 1);
  s.set ("compactint", 1);
  s.set ("compactmin", 1);
  s.set ("compactlim", 0);
  s.set ("lucky", 0);
  for (int v = 1; v <= 10; v++)
    s.clause (v);
  for (int v = 11; v < 20; v += 2)
    s.clause (v, v + 1);
  const int n = 100;
  for (int i = 0; i < 38 * n / 10; i++) { // satisfiable, but needs search
    for (int j = 0; j < 3; j++) {
      const int lit = pick_literal (n); // on variables 21-120
      s.add (lit < 0 ? lit - 20 : lit + 20);
    }
    s.add (0);
  }
  freeze_all (s);
  for (int round = 0; round < 2; round++) {
    CHECK (s.solve () == 10);
    CHECK (s.get_statistic_value ("conflicts") > 0);
    for (int v = 11; v <= 20; v++)
      CHECK (s.get_vsids_score (v) == 0);
    int positive = 0;
    for (int v = 21; v <= 20 + n; v++)
      positive += s.get_vsids_score (v) > 0;
    CHECK (positive > n / 2);
  }
}

static void test_no_side_effects () {
  // Reading all scores between incremental calls changes neither results,
  // models, nor the search (same statistics).
  const char *statistics[] = {"conflicts", "decisions", "propagations",
                              "fixed"};
  vector<int64_t> stats[2];
  vector<int> results[2];
  for (int read = 0; read <= 1; read++) {
    rng = 42;
    Solver s;
    s.set ("stabilizeonly", 1);
    const int n = 80;
    for (int i = 0; i < 4 * n; i++) {
      for (int j = 0; j < 3; j++)
        s.add (pick_literal (n));
      s.add (0);
    }
    for (int round = 0; round < 20; round++) {
      if (read)
        for (int v = 1; v <= n; v++)
          CHECK (valid (s.get_vsids_score (v)));
      for (int j = 0; j < 2; j++)
        s.assume (pick_literal (n));
      const int res = s.solve ();
      results[read].push_back (res);
      if (res == 10)
        for (int v = 1; v <= n; v++)
          results[read].push_back (s.val (v));
    }
    for (const auto &name : statistics)
      stats[read].push_back (s.get_statistic_value (name));
  }
  CHECK (results[0] == results[1]);
  CHECK (stats[0] == stats[1]);
  CHECK (stats[0][0] > 0); // some conflicts
}

/*------------------------------------------------------------------------*/

int main () {
  test_initial ();
  test_stable ();
  test_focused ();
  test_inactive ();
  test_renumbered ();
  test_no_side_effects ();
  printf ("vsids_score: %d checks passed\n", checked);
  return 0;
}
