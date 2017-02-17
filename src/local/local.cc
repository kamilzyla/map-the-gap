#include "local.h"

#include "debug.h"
#include "parser/bp_parser.h"
#include "parser/bts_parser.h"
#include "utils/point.h"

#define VAR(v,n) __typeof(n) v=n
#define FOREACH(i,c) for(VAR(i,(c).begin()); i!=(c).end(); ++i)
using namespace std;

double budget = 1e6;


struct GminaInstance {
  int id;
  vector<Point> ac_points;
  vector<Point> houses;

  void debug() {
    DEB("Gmina id: %d\n", id);
    FOREACH(i, ac_points) {
      DEB("AP %lf %lf\n", i->getX(), i->getY());
    }
    FOREACH(i, houses) {
      DEB("H %lf %lf\n", i->getX(), i->getY());
    }
  }

  void solve() {

  }
};


void local() {
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
}
