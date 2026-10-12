// NEW_FILE
// White-box test of the binary heap in 'heap.hpp' (the EVSIDS decision
// heap), to which this fork added 'reset', 'push_back_unordered' and
// 'heapify' (for restricted solving).  Random operations (also of the
// upstream functions) are checked against a reference, including
// the heap property of the underlying array (through the iterators).  The
// checks do not depend on 'assert', so they also run in optimized builds.

#include "../../src/heap.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace CaDiCaL;

static int checked;

#define CHECK(COND) \
  do { \
    checked++; \
    if (COND) \
      break; \
    fprintf (stderr, "heap: check '%s' failed at line %d\n", #COND, \
             __LINE__); \
    exit (1); \
  } while (0)

// As 'score_smaller' in CaDiCaL: smaller score, ties broken by larger
// element, thus 'front' is the element with the largest score and among
// those with the largest score the smallest element.

struct smaller {
  const std::vector<double> *scores;
  smaller (const std::vector<double> *s) : scores (s) {}
  bool operator() (unsigned a, unsigned b) const {
    const double s = (*scores)[a], t = (*scores)[b];
    return s < t || (s == t && a > b);
  }
};

static uint64_t rng = 1;

static uint64_t next () {
  uint64_t z = (rng += 0x9e3779b97f4a7c15ull);
  z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ull;
  z = (z ^ (z >> 27)) * 0x94d049bb133111ebull;
  return z ^ (z >> 31);
}

static unsigned pick (unsigned n) { return (unsigned) (next () % n); }

// Scores from a small range to have many ties.

static double random_score () { return (double) pick (16); }

static void check (heap<smaller> &h, const std::vector<char> &in,
                   const smaller &less) {
  size_t count = 0;
  unsigned best = 0;
  for (unsigned e = 0; e < in.size (); e++) {
    CHECK (h.contains (e) == (bool) in[e]);
    if (!in[e])
      continue;
    if (!count++ || less (best, e))
      best = e;
  }
  CHECK (h.size () == count);
  CHECK (h.empty () == !count);
  if (count)
    CHECK (h.front () == best);
  const std::vector<unsigned> array (h.begin (), h.end ());
  CHECK (array.size () == count);
  for (size_t i = 1; i < array.size (); i++)
    CHECK (!less (array[(i - 1) / 2], array[i])); // heap property
  for (const auto &e : array)
    CHECK (e < in.size () && in[e]);
}

static void test_random (unsigned n, unsigned operations) {
  std::vector<double> scores (n);
  for (auto &score : scores)
    score = random_score ();
  const smaller less (&scores);
  heap<smaller> h (less);
  std::vector<char> in (n, 0);
  for (unsigned i = 0; i < operations; i++) {
    const unsigned op = pick (100), e = pick (n);
    if (op < 35) {
      if (!in[e])
        h.push_back (e), in[e] = 1;
    } else if (op < 55) {
      if (!h.empty ()) {
        const unsigned front = h.front ();
        CHECK (h.pop_front () == front);
        CHECK (in[front]);
        in[front] = 0;
      }
    } else if (op < 85) { // increase or decrease the score
      scores[e] = random_score ();
      if (in[e])
        h.update (e);
    } else if (op < 87) {
      h.reset ();
      std::fill (in.begin (), in.end (), 0);
    } else if (op < 88) {
      h.clear ();
      std::fill (in.begin (), in.end (), 0);
    } else if (op < 91) { // unordered batch as in 'restrict_scores'
      if (pick (2))
        h.reset (), std::fill (in.begin (), in.end (), 0);
      const unsigned batch = pick (n / 2 + 1);
      for (unsigned j = 0; j < batch; j++) {
        const unsigned f = pick (n);
        if (!in[f])
          h.push_back_unordered (f), in[f] = 1;
      }
      h.heapify ();
    } else { // drain completely in order
      unsigned previous = 0;
      bool first = true;
      while (!h.empty ()) {
        const unsigned front = h.pop_front ();
        CHECK (in[front]);
        in[front] = 0;
        if (!first)
          CHECK (!less (previous, front));
        previous = front, first = false;
      }
      for (unsigned f = 0; f < n; f++)
        CHECK (!in[f]);
    }
    check (h, in, less);
  }
}

static void test_edge_cases () {
  std::vector<double> scores (1u << 16, 0);
  const smaller less (&scores);
  heap<smaller> h (less);
  CHECK (h.empty ());
  CHECK (!h.contains (0));
  CHECK (!h.contains (12345)); // beyond the position table
  h.heapify ();                // empty
  CHECK (h.empty ());
  h.push_back (12345); // grows the position table
  CHECK (h.contains (12345));
  CHECK (h.front () == 12345);
  h.reset ();
  CHECK (!h.contains (12345));
  CHECK (h.empty ());
  h.push_back_unordered (7);
  h.heapify (); // single element
  CHECK (h.front () == 7);
  scores[7] = 1;
  h.update (7);
  CHECK (h.pop_front () == 7);
  CHECK (h.empty ());
  scores[7] = 0;
  for (unsigned e = 1000; e > 0; e--) // same scores: smallest first
    h.push_back_unordered (e);
  h.heapify ();
  for (unsigned e = 1; e <= 1000; e++)
    CHECK (h.pop_front () == e);
  h.shrink ();
  h.erase ();
  CHECK (h.empty ());
}

int main () {
  test_edge_cases ();
  test_random (1, 1000);
  test_random (2, 1000);
  test_random (7, 5000);
  test_random (100, 20000);
  test_random (1000, 3000);
  printf ("heap: %d checks passed\n", checked);
  return 0;
}
