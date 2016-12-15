#ifndef HANOISTATE_HPP
#define HANOISTATE_HPP

#include <utility>
#include <vector>
#include <queue>

struct HanoiState {
    using Distance = int;
    using HanoiDisk = int;
    using HanoiPole = std::vector<HanoiDisk>;
    using HanoiStateInfo = std::vector<HanoiPole>;
    HanoiStateInfo state;
    Distance distance;
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
void generateNextValidStates(HanoiState const& state, std::queue<HanoiState> &statesToCheck);


#endif // HANOISTATE_HPP
