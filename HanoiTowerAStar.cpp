#include "HanoiTowerAStar.hpp"
#include <algorithm>
#include <numeric>
#include <set>
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
    // this is terrible hack cause i haven't used pointers and vector
    // reallocation invalidated my references to parents
    visitedStates.reserve(30000);
}

HanoiState HanoiTowerAStar::solve() {
    int baseHeuristic = 100;
    int baseHeuristicStep = 100;
    std::set<HanoiState> statesToCheck;
    statesToCheck.insert(root);
    while(!statesToCheck.empty())
    {
        auto beg = statesToCheck.begin();
        HanoiState stateToCheck(*beg);
        statesToCheck.erase(beg);
        if (isSolution(stateToCheck))
        {
            return stateToCheck;
        }
        std::vector<HanoiState> nextStates = generateNextValidStates(stateToCheck);
        visitedStates.push_back(std::move(stateToCheck));
        for (auto& nextState: nextStates)
        {
            if (isStateAlreadyChecked(nextState))
            {
                continue;
            }
            nextState.distance+=baseHeuristic;
            auto sameStateAs = std::find_if(
                statesToCheck.cbegin(),
                statesToCheck.cend(),
                [&nextState](HanoiState const& visitedState) -> bool {
                    return visitedState == nextState;
                }
            );
            if (sameStateAs == statesToCheck.end())
            {
                nextState.parent = &visitedStates.back();
                statesToCheck.insert(std::move(nextState));
            }
            else
            {
                int nextStateDistance = countStateHeuristic(nextState) + moveWeight + baseHeuristic;
                if (sameStateAs->distance > nextStateDistance)
                {
//                    std::cout << "i am here" << std::endl;
//                    printState(*sameStateAs,0);
//                    printState(nextState,0);
//                    printState(visitedStates.back(),0);
//                    printState(*sameStateAs->parent, 0);
                    sameStateAs->distance = nextStateDistance;
                }
            }
        }
        baseHeuristic+=baseHeuristicStep;
    }
    assert(1==2);
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

int const HanoiTowerAStar::getVisitedStatesNumber() const
{
    return visitedStates.size();
}
