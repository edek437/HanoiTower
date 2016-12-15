#include "HanoiTowerBFS.hpp"
#include <algorithm>
#include <queue>
#include <numeric>

HanoiTowerBFS::HanoiTowerBFS(const unsigned int towerHeight, const unsigned int numberOfPoles)
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
    root.distance = 0;
    // this is terrible hach cause i haven't used pointers and vector
    // reallocation invalidated my references to parents
    visitedStates.reserve(30000);
}

HanoiState HanoiTowerBFS::solve() {
    HanoiState solution;
    std::queue<HanoiState> statesToCheck;
    statesToCheck.push(root);
    while (!statesToCheck.empty())
    {
        HanoiState stateToCheck = statesToCheck.front();
        statesToCheck.pop();
        if (isStateAlreadyChecked(stateToCheck))
        {
            continue;
        }
        if (isSolution(stateToCheck))
        {
            solution = stateToCheck;
            break;
        }
        visitedStates.push_back(stateToCheck);
        auto nextStates = generateNextValidStates(stateToCheck);
        for (auto& nextState: nextStates)
        {
            nextState.distance = stateToCheck.distance + 1;
            nextState.parent = &visitedStates.back();
            statesToCheck.emplace(std::move(nextState));
        }
    }
    return solution;
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

int const& HanoiTowerBFS::getVisitedStatesNumber() const
{
    return visitedStates.size();
}
