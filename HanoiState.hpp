#ifndef HANOISTATE_HPP
#define HANOISTATE_HPP

#include <utility>
#include <vector>
using HanoiDisk = int;
using HanoiPole = std::vector<HanoiDisk>;
using HanoiState = std::vector<HanoiPole>;

bool isStateValid(HanoiState const& state);
std::vector<HanoiState> generateNextValidStates(HanoiState const& state);


#endif // HANOISTATE_HPP
