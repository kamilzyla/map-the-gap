//
// Created by zak on 2/17/17.
//

#ifndef MAP_THE_GAP_RUNNER_H
#define MAP_THE_GAP_RUNNER_H

#include <string>

#include "solution.h"

void run();

void printSolution(const Solution &solution);
void printSummary(const time_t &start, const time_t &end, const Solution &solution);

#endif //MAP_THE_GAP_RUNNER_H
