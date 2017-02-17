#ifndef BTS_PARSER_H_
#define BTS_PARSER_H_

#include <string>

#include "../point/Point.h"

typedef std::vector<std::pair<BTS, int> > BTSesWithGminas;

BTSesWithGminas parseBTSFile(const std::string &path);

#endif  // BTS_PARSER_H_
