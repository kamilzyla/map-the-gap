//
// Created by zak on 2/17/17.
//

#include "partitioner.h"
#include "../parser/bts_parser.h"
#include "../parser/bp_parser.h"

#include <string>
#include <utils/distance.h>

BP calculateAvgCoordinate(const BPs &bps) {
  double sum_x = 0;
  double sum_y = 0;
  for (int i = 0; i < (int) bps.size(); ++i) {
    sum_x += bps[i].getX();
    sum_y += bps[i].getY();
  }
  return BP(sum_x / bps.size(), sum_y / bps.size());
}

const double BTS_DISTANCE_TRESHOLD_KM = 10;

void partitionData(const std::string &btsPath, const std::string &bpPath) {
  BTSes btses = parseBTSFile(btsPath);
  BTSesInGminas btSesInGminas;
  BPsInGminas bpsInGminas = parseBPFile(bpPath);
  int droppedGminas = 0;
  for (BPsInGminas::iterator it = bpsInGminas.begin(); it != bpsInGminas.end(); ++it) {
    BP avgBP = calculateAvgCoordinate(it->second);
    for (int btsIdx = 0; btsIdx < (int) btses.size(); ++btsIdx) {
      if (computeDistance(avgBP, btses[btsIdx]) <= BTS_DISTANCE_TRESHOLD_KM) {
        btSesInGminas[it->first].push_back(btses[btsIdx]);
      }
    }
    if (btSesInGminas[it->first].empty()) {
      droppedGminas++;
    }
  }
  std::cout << "Dropped gminas: " << droppedGminas << std::endl;

  partitionPoints(btSesInGminas);
  partitionPoints(bpsInGminas);
}
