//
// Created by zak on 2/17/17.
//

#include <cstdlib>
#include <map>
#include <utils/distance.h>
#include <algorithm>
#include "local_search_2.h"
#include "solution.h"

class LSPaths {
 public:
  explicit LSPaths(const Solution &solution) {
    solution.getPaths();
  }

  void swap(int n) {
    std::vector<int> selectedPaths;
    std::vector<int> splitPoints;
    std::vector<int> permutation;
    for (int i = 0; i < n; ++i) {
      int selectedPathId = rand() % (int) paths_.size();
      if (std::find(selectedPaths.begin(), selectedPaths.end(), selectedPathId) != selectedPaths.end()) {
        continue;
      }
      selectedPaths.push_back(selectedPathId);
      splitPoints.push_back(rand() % ((int) paths_[selectedPathId].getNumConnectedBPs() - 1));
      permutation.push_back(i);
    }
    if (selectedPaths.size() < 2) {
      return;
    }

    double bestCost = computeCost(selectedPaths, splitPoints, permutation);
    std::vector<int> bestPermutation = permutation;

    bool foundBetter = false;
    while(std::next_permutation(permutation.begin(), permutation.end())) {
      double newCost = computeCost(selectedPaths, splitPoints, permutation);
      if (newCost < bestCost) {
        bestCost = newCost;
        bestPermutation = permutation;
        foundBetter = true;
      }
    }

    if (foundBetter) {
      applyPermutation(selectedPaths, splitPoints, bestPermutation);
    }
  }

  Solution toSolution() const {
    Solution solution;
    for (int pathIdx = 0; pathIdx < (int) paths_.size(); ++pathIdx) {
      solution.addPath(paths_[pathIdx]);
    }
    return solution;
  }

 private:
  double computeCost(
      const std::vector<int> &selectedPaths,
      const std::vector<int> &splitPoints,
      const std::vector<int> &permutation
  ) const {
    double cost = 0;
    for (int selectedPathIdx = 0; selectedPathIdx < (int) selectedPaths.size(); ++selectedPathIdx) {
      const BPs &firstPath = paths_[selectedPaths[selectedPathIdx]].getBPs();
      const BPs &secondPath = paths_[selectedPaths[permutation[selectedPathIdx]]].getBPs();

      BP firstBP = firstPath[splitPoints[selectedPathIdx]];
      BP secondBP = secondPath[splitPoints[permutation[selectedPathIdx]] + 1];
      cost += computeDistance(firstBP, secondBP);
    }
    return cost;
  }

  void applyPermutation(
      const std::vector<int> &selectedPaths,
      const std::vector<int> &splitPoints,
      const std::vector<int> &permutation
  ) {
    std::vector<Path> newPaths;
    for (int selectedPathIdx = 0; selectedPathIdx < (int) selectedPaths.size(); ++selectedPathIdx) {
      const BPs &firstPath = paths_[selectedPaths[selectedPathIdx]].getBPs();
      const BPs &secondPath = paths_[selectedPaths[permutation[selectedPathIdx]]].getBPs();

      Path path(paths_[selectedPaths[selectedPathIdx]].getBTS());
      for (int i = 0; i <= splitPoints[selectedPathIdx]; ++i) {
        path.addBP(firstPath[i]);
      }
      for (int i = splitPoints[permutation[selectedPathIdx]] + 1; i < (int) secondPath.size(); ++i) {
        path.addBP(secondPath[i]);
      }
      newPaths.push_back(path);
    }

    for (int selectedPathIdx = 0; selectedPathIdx < (int) selectedPaths.size(); ++selectedPathIdx) {
      paths_[selectedPaths[selectedPathIdx]] = newPaths[selectedPathIdx];
    }
  }

  std::vector<Path> paths_;
};

Solution localSearch2(const Solution &solution) {
  srand(time(NULL));

  LSPaths lsPaths(solution);

  const int NUM_ITERATIONS = 1e3;
  for (int i = 0; i < NUM_ITERATIONS; ++i) {
    lsPaths.swap(2);
  }
  for (int i = 0; i < NUM_ITERATIONS; ++i) {
    lsPaths.swap(3);
  }
  return lsPaths.toSolution();
}