#ifndef MAP_THE_GAP_COMMON_H
#define MAP_THE_GAP_COMMON_H

#include <string>
#include <vector>

typedef std::vector<std::string> Tokens;

Tokens getTokens(const std::string &line, char delim);
void dropHeader(std::ifstream &file);

#endif //MAP_THE_GAP_COMMON_H
