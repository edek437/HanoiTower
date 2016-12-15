#ifndef HANOITOWERBFS_HPP
#define HANOITOWERBFS_HPP

#include <vector>
#include "HanoiState.hpp"

class HanoiTowerBFS
{
public:
    HanoiTowerBFS(const unsigned int towerHeight, const unsigned int numberOfPoles);
    HanoiState solve();
    ~HanoiTowerBFS() = default;
    int const& getVisitedStatesNumber() const;
private:
    HanoiState solution;
    HanoiState root;
    bool isStateAlreadyChecked(const HanoiState &state) const;
    bool isSolution(HanoiState const& state) const;
    std::vector<HanoiState> visitedStates;

};

#endif // HANOITOWERBFS_HPP
