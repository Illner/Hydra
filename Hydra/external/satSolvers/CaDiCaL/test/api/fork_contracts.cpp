// NEW_FILE
// Checks that the API contracts added in this fork are enforced, i.e., that
// each invalid use aborts with an 'invalid API usage' message.  Each case
// runs in a forked child process, thus this test is skipped on Windows and
// if contracts are compiled out ('--no-contracts').

#include "../../src/cadical.hpp"
#include "../../src/tracer.hpp"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#if defined(_WIN32) || defined(NCONTRACTS)

int main () {
  printf ("fork_contracts: skipped (no 'fork' or no contracts)\n");
  return 0;
}

#else

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace CaDiCaL;

static int cases;

static void die (const char *name, const char *what,
                 const std::string &err) {
  fprintf (stderr, "fork_contracts: '%s' %s", name, what);
  if (!err.empty ())
    fprintf (stderr, " (child stderr: %s)", err.c_str ());
  fputc ('\n', stderr);
  exit (1);
}

static const int aborted = 77; // exit code of a child after 'abort'

static void exit_on_abort (int) { _exit (aborted); }

// Run 'body' in a child process and check that it aborts with an 'invalid
// API usage' message containing 'expected'.

static void violates (const char *name, void (*body) (),
                      const char *expected) {
  int fds[2];
  if (pipe (fds))
    die (name, "can not create pipe", "");
  fflush (stdout);
  fflush (stderr);
  pid_t pid = fork ();
  if (pid < 0)
    die (name, "can not fork", "");
  if (!pid) {
    close (fds[0]);
    dup2 (fds[1], 2);
    signal (SIGABRT, exit_on_abort); // no core dump nor crash report
    body ();
    _exit (0); // the contract was not checked
  }
  close (fds[1]);
  std::string err;
  char buffer[256];
  ssize_t bytes;
  while ((bytes = read (fds[0], buffer, sizeof buffer)) > 0)
    err.append (buffer, (size_t) bytes);
  close (fds[0]);
  int status = 0;
  if (waitpid (pid, &status, 0) != pid)
    die (name, "can not wait for child", "");
  if (!WIFEXITED (status) || WEXITSTATUS (status) != aborted)
    die (name, "did not abort", err);
  if (err.find ("invalid API usage") == std::string::npos)
    die (name, "aborted without 'invalid API usage' message", err);
  if (err.find (expected) == std::string::npos)
    die (name, "aborted with unexpected message", err);
  cases++;
}

/*------------------------------------------------------------------------*/

class DummyPropagator : public ExternalPropagator {
public:
  void notify_assignment (const std::vector<int> &) {}
  void notify_new_decision_level () {}
  void notify_backtrack (size_t) {}
  bool cb_check_found_model (const std::vector<int> &) { return true; }
  bool cb_has_external_clause (bool &) { return false; }
  int cb_add_external_clause_lit () { return 0; }
};

class DummyTracer : public Tracer {};

static void formula (Solver &s) {
  s.clause (1, 2);
  s.clause (-1, 3);
  s.clause (-2, 3);
}

/*------------------------------------------------------------------------*/

static void vsids_zero () {
  Solver s;
  formula (s);
  (void) s.get_vsids_score (0);
}

static void vsids_literal () {
  Solver s;
  formula (s);
  (void) s.get_vsids_score (-1);
}

static void vsids_undeclared () {
  Solver s;
  formula (s);
  (void) s.get_vsids_score (4);
}

static void vsids_extension () {
  Solver s;
  s.set ("factor", 1);
  s.declare_more_variables (10);
  for (int a = 1; a <= 5; a++)
    for (int b = 6; b <= 10; b++)
      s.clause (a, b);
  (void) s.simplify (1); // bounded variable addition adds variable 11
  (void) s.get_vsids_score (11);
}

static void push_with_pending_assume () {
  Solver s;
  formula (s);
  s.assume (1);
  s.push_assumption (2);
}

static void push_with_checkproof () {
  Solver s;
  s.set ("check", 1);
  s.set ("checkproof", 1);
  formula (s);
  s.push_assumption (1);
}

static void push_with_proof_tracer () {
  Solver s;
  DummyTracer tracer;
  s.connect_proof_tracer (&tracer, false);
  formula (s);
  s.push_assumption (1);
}

static void push_with_propagator () {
  Solver s;
  DummyPropagator propagator;
  formula (s);
  s.connect_external_propagator (&propagator);
  s.push_assumption (1);
}

static void propagator_with_persistent () {
  Solver s;
  DummyPropagator propagator;
  formula (s);
  s.push_assumption (1);
  s.connect_external_propagator (&propagator);
}

static void pop_empty () {
  Solver s;
  formula (s);
  s.pop_assumption (1);
}

static void pop_not_last () {
  Solver s;
  formula (s);
  s.push_assumption (1);
  s.push_assumption (3);
  s.pop_assumption (1);
}

static void pop_with_pending_assume () {
  Solver s;
  formula (s);
  s.push_assumption (1);
  s.assume (2);
  s.pop_assumption (1);
}

static void lookahead_with_persistent () {
  Solver s;
  formula (s);
  s.push_assumption (1);
  (void) s.lookahead ();
}

static void cubes_with_persistent () {
  Solver s;
  formula (s);
  s.push_assumption (1);
  (void) s.generate_cubes (1);
}

static void restricted_zero () {
  Solver s;
  formula (s);
  std::vector<int> vars = {1, 0};
  (void) s.solve_restricted (vars);
}

static void restricted_literal () {
  Solver s;
  formula (s);
  std::vector<int> vars = {-1};
  (void) s.solve_restricted (vars);
}

static void restricted_with_propagator () {
  Solver s;
  DummyPropagator propagator;
  formula (s);
  s.connect_external_propagator (&propagator);
  std::vector<int> vars = {1, 2};
  (void) s.solve_restricted (vars);
}

static void restricted_with_checkproof () {
  Solver s;
  s.set ("check", 1);
  s.set ("checkproof", 1);
  formula (s);
  std::vector<int> vars = {1, 2};
  (void) s.solve_restricted (vars);
}

static void restricted_with_proof_tracer () {
  Solver s;
  DummyTracer tracer;
  s.connect_proof_tracer (&tracer, false);
  formula (s);
  std::vector<int> vars = {1, 2};
  (void) s.solve_restricted (vars);
}

static void trail_value_zero () {
  Solver s;
  formula (s);
  (void) s.trail_value (0);
}

static void implied_by_last_when_unsat () {
  Solver s;
  formula (s);
  s.push_assumption (-3);
  (void) s.solve (); // unsatisfiable
  std::vector<int> lits;
  s.implied_by_last_assumption (lits);
}

/*------------------------------------------------------------------------*/

int main () {
  violates ("get_vsids_score (0)", vsids_zero, "invalid variable '0'");
  violates ("get_vsids_score (-1)", vsids_literal, "invalid variable '-1'");
  violates ("get_vsids_score (undeclared)", vsids_undeclared,
            "variable '4' not declared");
  violates ("get_vsids_score (extension variable)", vsids_extension,
            "variable '11' is an extension variable");
  violates ("push_assumption after assume", push_with_pending_assume,
            "can not push persistent assumption '2' while assumptions");
  violates ("push_assumption with checkproof", push_with_checkproof,
            "persistent assumptions do not support proofs");
  violates ("push_assumption with proof tracer", push_with_proof_tracer,
            "persistent assumptions do not support proofs");
  violates ("push_assumption with propagator", push_with_propagator,
            "persistent assumptions do not support external propagators");
  violates ("connect_external_propagator with persistent assumptions",
            propagator_with_persistent,
            "can not connect propagator with persistent assumptions");
  violates ("pop_assumption on empty stack", pop_empty,
            "can not pop '1' from empty persistent assumption stack");
  violates ("pop_assumption of not last", pop_not_last,
            "last pushed persistent assumption is '3'");
  violates ("pop_assumption after assume", pop_with_pending_assume,
            "can not pop persistent assumption '1' while assumptions");
  violates ("lookahead with persistent assumptions",
            lookahead_with_persistent,
            "lookahead does not support persistent assumptions");
  violates ("generate_cubes with persistent assumptions",
            cubes_with_persistent,
            "generating cubes does not support persistent assumptions");
  violates ("solve_restricted with zero", restricted_zero,
            "invalid restricted variable '0'");
  violates ("solve_restricted with literal", restricted_literal,
            "invalid restricted variable '-1'");
  violates ("solve_restricted with propagator", restricted_with_propagator,
            "restricted solving does not support external propagators");
  violates ("solve_restricted with checkproof", restricted_with_checkproof,
            "restricted solving does not support proofs");
  violates ("solve_restricted with proof tracer",
            restricted_with_proof_tracer,
            "restricted solving does not support proofs");
  violates ("trail_value (0)", trail_value_zero, "invalid literal '0'");
  violates ("implied_by_last_assumption when unsatisfiable",
            implied_by_last_when_unsat,
            "only in unknown or satisfied state");
  printf ("fork_contracts: %d contract violations detected\n", cases);
  return 0;
}

#endif
