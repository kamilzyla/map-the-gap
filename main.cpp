#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <fstream>
#include <unordered_set>

using Tokens = std::vector<std::string>;

class BTS {
public:
    using Coordinate = std::string;

    BTS(const Tokens &tokens) : x_(tokens[4]), y_(tokens[5]) {}

    Coordinate getX() const {
        return x_;
    }

    Coordinate getY() const {
        return y_;
    }

private:
    Coordinate x_;
    Coordinate y_;
};

using BTSes = std::vector<BTS>;

Tokens getTokens(const std::string &line, char delim) {
    Tokens tokens;

    std::stringstream lineStream(line);
    std::string cell;
    while (std::getline(lineStream, cell, delim)) {
        tokens.push_back(cell);
    }

//    for (std::string token: tokens) {
//        std::cout << "Token: " << token << std::endl;
//    }
    return tokens;
}

void dropHeader(std::ifstream &file) {
    std::string line;
    std::getline(file, line);
}

BTSes parseBTSFile(const std::string &path) {
    std::ifstream file(path);
    std::string line;

    BTSes btsSet;
    dropHeader(file);
    while (std::getline(file, line)) {
        auto tokens = getTokens(line, ',');
        btsSet.push_back(BTS(tokens));
    }
    return btsSet;
}

int main() {
    std::string const btsPath = "../bts_truncated.csv";
    BTSes btsSet = parseBTSFile(btsPath);
    std::cout << "Number of BTSes: " << btsSet.size() << std::endl;

    auto it = btsSet.begin();
    for (int i = 0; i < 10; ++i) {
        std::cout << "BTS(" << it->getX() << ", " << it->getY() << ")" << std::endl;
        it++;
    }
}
