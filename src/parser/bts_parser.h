#ifndef BTS_PARSER_H_
#define BTS_PARSER_H_

#include <string>
#include <map>

#include "../point/Point.h"

typedef std::map<int, BTSes> BTSesInGminas;

BTSesInGminas parseBTSFile(const std::string &path);

#endif  // BTS_PARSER_H_
