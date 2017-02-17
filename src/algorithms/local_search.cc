//
// Created by zak on 2/17/17.
//

#include "local_search.h"
#include "../utils/distance.h"

#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>

class LSPaths {
 public:
  explicit LSPaths(const Solution &solution) {
    std::vector<Path> paths = solution.getPaths();
    for (int pathIdx = 0; pathIdx < (int) paths.size(); ++pathIdx) {
      Path &path = paths[pathIdx];
      BPs bps = path.getBPs();
      for (int bpIdx = 1; bpIdx < (int) bps.size(); ++bpIdx) {
        neighbours_.push_back(std::make_pair(bps[bpIdx - 1], bps[bpIdx]));
      }
      // TODO dorzuć sztuczne końce o odległości zero
      if (!bps.empty()) {
        beginnings_[(path.getBTS())].push_back(bps[0]);
      }
    }
  }

  void swap(int n) {
    std::vector<int> selectedNodes;
    std::vector<int> permutation;
    for (int i = 0; i < n; ++i) {
      selectedNodes.push_back(rand() % (int) neighbours_.size());
      permutation.push_back(i);
    }
    double bestCost = computeCost(selectedNodes, permutation);
    std::vector<int> bestPermutation = permutation;

    while(std::next_permutation(permutation.begin(), permutation.end())) {
      double newCost = computeCost(selectedNodes, permutation);
      if (newCost < bestCost) {
        bestCost = newCost;
        bestPermutation = permutation;
      }
    }

    applyPermutation(selectedNodes, bestPermutation);
  }

  Solution toSolution() const {
    Solution solution;
    std::map<BP, BP> neighboursMap;
    for (int i = 0; i < (int) neighbours_.size(); ++i) {
      neighboursMap.insert(std::make_pair(neighbours_[i].first, neighbours_[i].second));
    }

    for (std::map<BTS, BPs>::const_iterator it = beginnings_.begin(); it != beginnings_.end(); ++it) {
      for (int pathIdx = 0; pathIdx < (int) it->second.size(); ++pathIdx) {
        Path path(it->first);
        BP currentNode = it->second[pathIdx];
        path.addBP(currentNode);
        std::map<BP, BP>::iterator nodeIt;
        while ((nodeIt = neighboursMap.find(currentNode)) != neighboursMap.end()) {
          currentNode = nodeIt->second;
          path.addBP(currentNode);
        }
        solution.addPath(path);
      }
    }
    return solution;
  }

 private:
  double computeCost(const std::vector<int> &selectedNodes, const std::vector<int> &permutation) const {
    double cost = 0;
    for (int selectedNodeIdx = 0; selectedNodeIdx < (int) selectedNodes.size(); ++selectedNodeIdx) {
      BP firstBP = neighbours_[selectedNodes[selectedNodeIdx]].first;
      BP secondBP = neighbours_[selectedNodes[permutation[selectedNodeIdx]]].second;
      cost += computeDistance(firstBP, secondBP);
    }
    return cost;
  }

  void applyPermutation(const std::vector<int> &selectedNodes, const std::vector<int> &permutation) {
    for (int selectedNodeIdx = 0; selectedNodeIdx < (int) selectedNodes.size(); ++selectedNodeIdx) {
      BP firstBP = neighbours_[selectedNodes[selectedNodeIdx]].first;
      BP secondBP = neighbours_[selectedNodes[permutation[selectedNodeIdx]]].second;
      neighbours_[selectedNodes[selectedNodeIdx]] = std::make_pair(firstBP, secondBP);
    }
  }

  std::vector<std::pair<BP, BP> > neighbours_;
  std::map<BTS, BPs> beginnings_;
};

Solution localSearch(const Solution &solution) {
  srand(time(NULL));

  LSPaths lsPaths(solution);

  const int NUM_ITERATIONS = 1e6;
  for (int i = 0; i < NUM_ITERATIONS; ++i) {
    lsPaths.swap(2);
  }
  for (int i = 0; i < NUM_ITERATIONS; ++i) {
    lsPaths.swap(3);
  }
  return lsPaths.toSolution();
}
