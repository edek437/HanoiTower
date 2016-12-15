#ifndef HANOISTATE_HPP
#define HANOISTATE_HPP

#include <utility>
#include <vector>

struct HanoiState {
    using Distance = int;
    using HanoiDisk = int;
    using HanoiPole = std::vector<HanoiDisk>;
    using HanoiStateInfo = std::vector<HanoiPole>;
    HanoiStateInfo state;
    Distance distance;
    HanoiState* parent = nullptr;
    bool operator== (HanoiState const& rhs) const
    {
        return this->state == rhs.state;
    }
    bool operator!= (HanoiState const& rhs) const
    {
        return this->state != rhs.state;
    }
};


bool isStateValid(HanoiState const& state);
std::vector<HanoiState> generateNextValidStates(HanoiState const& state);
int countStateHeuristic(HanoiState const& state);
void printPathToState(HanoiState const& state);


#endif // HANOISTATE_HPP
