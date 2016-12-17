#include <iostream>
#include <cassert>
#include "HanoiTowerBFS.hpp"
#include "HanoiTowerAStar.hpp"
#include <chrono>
#include <memory>

int main(int argc, char *argv[])
{
    int numberOfPoles = 3;
    int towerHeight = 5;
    std::string algo = "BFS";
    int opt_ind = 1;
    while (opt_ind < argc)
    {
        if(argv[opt_ind] == "--algorithm")
        {
            algo=argv[opt_ind+1];
            opt_ind+=2;
            continue;
        }
        if(argv[opt_ind] == "--pegs")
        {
            numberOfPoles=std::stoi(argv[opt_ind+1]);
            opt_ind+=2;
            continue;
        }
        if(argv[opt_ind] == "--towers")
        {
            towerHeight=std::stoi(argv[opt_ind+1]);
            opt_ind+=2;
            continue;
        }
        opt_ind++;
    }


    std::unique_ptr<HanoiTowerAlgorithm> hta;
    if (algo == "BFS")
    {
        hta = std::unique_ptr<HanoiTowerAlgorithm>(new HanoiTowerBFS(towerHeight, numberOfPoles));
    }
    else if (algo == "ASTAR")
    {
        hta = std::unique_ptr<HanoiTowerAlgorithm>(new HanoiTowerAStar(towerHeight, numberOfPoles));
    }
    else
    {
        std::cout << "Unrecognized algoritm: " << algo << std::endl;
        return 1;
    }
    auto start = std::chrono::steady_clock::now();
    HanoiState solution = hta->solve();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>
                                (std::chrono::steady_clock::now() - start);
    printPathToState(solution);
    std::cout << "It took " << duration.count() << "s to find the solution" << std::endl;
    return 0;
}
