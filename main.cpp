#include <iostream>
#include <cassert>
#include "HanoiTowerBFS.hpp"
#include <chrono>

int main(int argc, char *argv[])
{
    const int numberOfPoles = 3;
    const int towerHeight = 10;
    HanoiTowerBFS htbfs = HanoiTowerBFS(towerHeight, numberOfPoles);
    auto start = std::chrono::steady_clock::now();
    int solutionSteps = htbfs.solve();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>
                                (std::chrono::steady_clock::now() - start);
    std::cout << "Hanoi tower with "
              << numberOfPoles << " poles and "
              << towerHeight << " disks can be solved in "
              << solutionSteps << " moves." << std::endl;
    std::cout << "It took " << duration.count() << "s to find the solution" << std::endl;
    return 0;
}
