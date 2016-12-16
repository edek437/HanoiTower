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
    mutable Distance distance;
    mutable HanoiState* parent = nullptr;
    HanoiState() = default;
    HanoiState(HanoiState const& rhs) = default;
    HanoiState(HanoiState&& rhs)
    {
        std::move(rhs.state.begin(), rhs.state.end(), std::back_inserter(state));
        distance = rhs.distance;
        parent = rhs.parent;
    }
    bool operator == (HanoiState const& rhs) const
    {
        return this->state == rhs.state;
    }
    bool operator != (HanoiState const& rhs) const
    {
        return this->state != rhs.state;
    }
    bool operator < (HanoiState const& rhs) const
    {
        return this->distance <= rhs.distance;
    }
};


bool isStateValid(HanoiState const& state);
std::vector<HanoiState> generateNextValidStates(HanoiState const& state);
int countStateHeuristic(HanoiState const& state);
void printPathToState(HanoiState const& state);
void printState(HanoiState const& state, int stepNumber);


#endif // HANOISTATE_HPP
