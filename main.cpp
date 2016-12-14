#include <iostream>
#include <cassert>
#include "HanoiTowerBFS.hpp"

int main(int argc, char *argv[])
{
    const int numberOfPoles = 3;
    const int towerHeight = 3;
    HanoiTowerBFS htbfs = HanoiTowerBFS(towerHeight, numberOfPoles);
    int solutionSteps = htbfs.solve();
    assert(solutionSteps == 7);

    std::cout << "Hanoi tower with "
              << numberOfPoles << " poles and "
              << towerHeight << " disks can be solved in "
              << solutionSteps << " moves." << std::endl;
    return 0;
}
