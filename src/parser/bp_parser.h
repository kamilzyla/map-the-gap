//
// Created by zak on 2/16/17.
//

#ifndef MAP_THE_GAP_BP_PARSER_H
#define MAP_THE_GAP_BP_PARSER_H

#include <string>
#include <map>

#include "../point/Point.h"

typedef std::map<int, BPs> BPsInGminas;

BPsInGminas parseBPFile(const std::string &path);

#endif //MAP_THE_GAP_BP_PARSER_H
