#include <sstream>
#include <fstream>
#include <iostream>
#include "common.h"

Tokens getTokens(const std::string &line, char delim) {
  Tokens tokens;

  std::stringstream lineStream(line);
  std::string cell;
  while (std::getline(lineStream, cell, delim)) {
    tokens.push_back(cell);
  }

  return tokens;
}

void dropHeader(std::ifstream &file) {
  std::string line;
  std::getline(file, line);
}
