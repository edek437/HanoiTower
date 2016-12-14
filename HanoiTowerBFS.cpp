#include "HanoiTowerBFS.hpp"
#include <algorithm>
#include <numeric>
#include <cassert>

HanoiTowerBFS::HanoiTowerBFS(const unsigned int towerHeight, const unsigned int numberOfPoles)
{
    HanoiPole properPole;
    properPole.resize(towerHeight);
    std::iota(properPole.rbegin(), properPole.rend(), 1);

    root.push_back(properPole);
    for (int i = 1; i < numberOfPoles; ++i) {
        root.push_back(HanoiPole());
        solution.push_back(HanoiPole());
    }
    solution.push_back(properPole);
}

int HanoiTowerBFS::solve() {
    std::vector<HanoiState> nextStates = generateNextValidStates(root);
    assert(nextStates.size() == 2);
    visitedStates.push_back(root);
    for (HanoiState& state: nextStates)
    {

    }
    return 42;
}

bool HanoiTowerBFS::isStateAlreadyChecked(const HanoiState &state) const
{
    auto it = std::find_if(visitedStates.cbegin(),
                           visitedStates.cend(),
                           [&state](HanoiState const& visitedState) -> bool {
                                return visitedState == state;
                           }
              );
    return it != visitedStates.end();
}

bool HanoiTowerBFS::isSolution(HanoiState const& state) const
{
    return solution == state;
}
