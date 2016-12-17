#ifndef HANOITOWERASTAR_HPP
#define HANOITOWERASTAR_HPP

#include <vector>
#include "HanoiState.hpp"

class HanoiTowerAStar: public HanoiTowerAlgorithm
{
public:
    HanoiTowerAStar(const unsigned int towerHeight, const unsigned int numberOfPoles);
    HanoiState solve() override;
    ~HanoiTowerAStar() = default;
    const int getVisitedStatesNumber() const;
private:
    const int moveWeight = 1; //it can be ommited because it's constant
    HanoiState solution;
    HanoiState root;
    bool isStateAlreadyChecked(const HanoiState &state) const;
    bool isSolution(HanoiState const& state) const;
    std::vector<HanoiState> visitedStates;
};

#endif // HANOITOWERASTAR_HPP
