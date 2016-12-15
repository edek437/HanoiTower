#include "HanoiTowerAStar.hpp"
#include <algorithm>
#include <numeric>
#include <cassert>
#include <iostream>

HanoiTowerAStar::HanoiTowerAStar(const unsigned int towerHeight, const unsigned int numberOfPoles)
{
    HanoiState::HanoiPole properPole;
    properPole.resize(towerHeight);
    std::iota(properPole.rbegin(), properPole.rend(), 1);

    root.state.push_back(properPole);
    for (int i = 1; i < numberOfPoles; ++i) {
        root.state.push_back(HanoiState::HanoiPole());
        solution.state.push_back(HanoiState::HanoiPole());
    }
    solution.state.push_back(properPole);
    root.distance = countStateHeuristic(root) + moveWeight;
    assert(root.distance == 1 + moveWeight);
}

int HanoiTowerAStar::solve() {
    int movesNeededToSolveHanoiTower = 0;
    return movesNeededToSolveHanoiTower;
}

bool HanoiTowerAStar::isStateAlreadyChecked(const HanoiState &state) const
{
    auto it = std::find_if(visitedStates.cbegin(),
                           visitedStates.cend(),
                           [&state](HanoiState const& visitedState) -> bool {
                                return visitedState == state;
                           }
              );
    return it != visitedStates.end();
}

bool HanoiTowerAStar::isSolution(HanoiState const& state) const
{
    return solution == state;
}

int const& HanoiTowerAStar::getVisitedStatesNumber() const
{
    return visitedStates.size();
}
