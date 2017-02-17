#include "local.h"

#include <algorithm>
#include <cmath>

#include "algorithms/solution.h"
#include "algorithms/algorithm_runner.h"
#include "debug.h"
#include "parser/bp_parser.h"
#include "parser/bts_parser.h"
#include "utils/distance.h"
#include "utils/point.h"

#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) (int)(x).size()
#define REP(x,n) for(int x=0; x<(n); ++x)
#define VAR(v,n) __typeof(n) v=n
#define FOREACH(i,c) for(VAR(i,(c).begin()); i!=(c).end(); ++i)
using namespace std;

void debPoint(const char *s, Point p) {
  DEB("%s %lf %lf\n", s, p.getX(), p.getY());
}

struct Match {
  double d;
  Point ap, house;

  Match(double d, Point ap, Point house): d(d), ap(ap), house(house) {}
};

bool operator<(const Match &l, const Match &r) { return l.d < r.d; }

std::vector<Match> matches;

struct GminaInstance {
  int id;
  vector<Point> ac_points;
  vector<Point> houses;

  void debug() {
    DEB("Gmina id: %d\n", id);
    FOREACH(i, ac_points) debPoint("AP", *i);
    FOREACH(i, houses) debPoint("H", *i);
  }

  void solve() {
    while (!houses.empty()) {
      Point h = houses.back();
      houses.pop_back();

      double best_d = INFINITY;
      int best_i = -1;
      REP(i, SIZE(ac_points)) {
        Point ac = ac_points[i];
        double d = computeDistance(ac, h);
        if (d < best_d) {
          best_d = d;
          best_i = i;
        }
      }
      // DEB("Matched pair:\n");
      // debPoint("AP", ac_points[best_i]);
      // debPoint("H", h);

      Match m(best_d, ac_points[best_i], h);
      matches.push_back(m);

      // TODO: Debug dist.
    }
  }
};

static Solution local_wrapped() {
  DEB("Running local algorithm...\n");

  BTSesInGminas access_points = parseBTSFile("data/preprocessed_bts.csv");
  BPsInGminas houses = parseBPFile("data/bp.csv");
  DEB("APs: %lu, Hs: %lu\n", access_points.size(), houses.size());

  FOREACH(ap, access_points) {
    GminaInstance g;
    g.id = ap->first;
    FOREACH(i, ap->second) g.ac_points.push_back(*i);
    FOREACH(i, houses[ap->first]) g.houses.push_back(*i);
    // g.debug();

    if (!g.ac_points.empty() && !g.houses.empty()) {
      g.solve();
    }
  }

  sort(ALL(matches));
  // DEB("Found %lu matches\n", matches.size());
  // FOREACH(i, matches) {
    // DEB("%lf ", i->d);
  // }
  // DEB("\n");

  Solution sol;
  double budget = 1e6;
  FOREACH(i, matches) if (i->d <= budget) {
    Path path(BTS(i->ap.getX(), i->ap.getY()));
    path.addBP(BP(i->house.getX(), i->house.getY()));
    sol.addPath(path);
    budget -= i->d;
  }
  return sol;
}

void local() {
  time_t start, end;
  time(&start);
  Solution solution = local_wrapped();
  time(&end);

  printSolution(solution);
  printSummary(start, end, solution);
}
