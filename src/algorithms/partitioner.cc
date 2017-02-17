//
// Created by zak on 2/17/17.
//

#include "partitioner.h"
#include "../parser/bts_parser.h"
#include "../parser/bp_parser.h"

#include <string>

void partitionBTSes(const std::string &btsPath) {
  BTSesInGminas btsesInGminas = parseBTSFile(btsPath);
  partitionPoints(btsesInGminas);
}

void partitionBPs(const std::string &bpPath) {
  BPsInGminas bpsInGminas = parseBPFile(bpPath);
  partitionPoints(bpsInGminas);
}

void partitionData(const std::string &btsPath, const std::string &bpPath) {
  partitionBTSes(btsPath);
  partitionBPs(bpPath);
}
