#ifndef HANOITOWERASTAR_HPP
#define HANOITOWERASTAR_HPP

#include <vector>
#include "HanoiState.hpp"

class HanoiTowerAStar
{
public:
    HanoiTowerAStar(const unsigned int towerHeight, const unsigned int numberOfPoles);
    int solve();
    ~HanoiTowerAStar() = default;
    int const& getVisitedStatesNumber() const;
private:
    const int moveWeight = 1; //it can be ommited because it's constant
    HanoiState solution;
    HanoiState root;
    bool isStateAlreadyChecked(const HanoiState &state) const;
    bool isSolution(HanoiState const& state) const;
    std::vector<HanoiState> visitedStates;
};

#endif // HANOITOWERASTAR_HPP
