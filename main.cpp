#include <iostream>
#include <cassert>
#include "HanoiTowerBFS.hpp"
#include "HanoiTowerAStar.hpp"
#include <chrono>

int main(int argc, char *argv[])
{
    const int numberOfPoles = 3;
    const int towerHeight = 5;
    HanoiTowerBFS ht = HanoiTowerBFS(towerHeight, numberOfPoles);
//    HanoiTowerAStar ht = HanoiTowerAStar(towerHeight, numberOfPoles);
    auto start = std::chrono::steady_clock::now();
    HanoiState solution = ht.solve();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>
                                (std::chrono::steady_clock::now() - start);
    std::cout << "Hanoi tower with "
              << numberOfPoles << " poles and "
              << towerHeight << " disks can be solved in "
              << solution.distance << " moves. Visited "
              <<  ht.getVisitedStatesNumber() << " nodes" << std::endl;
    std::cout << "It took " << duration.count() << "s to find the solution" << std::endl;
    printPathToState(solution);
    return 0;
}
