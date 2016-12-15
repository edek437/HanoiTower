#include "HanoiState.hpp"
#include <algorithm>

std::vector<HanoiState> generateNextValidStates(HanoiState const& state)
{
    std::vector<HanoiState> nextStates;
    for(int poleIdx = 0; poleIdx < state.state.size(); ++poleIdx)
    {
        HanoiState inputState = state;
        HanoiState::HanoiPole& currPole = inputState.state[poleIdx];
        if (currPole.empty())
        {
            continue;
        }
        HanoiState::HanoiDisk topDisk = currPole.back();
        currPole.pop_back();
        for(int newPoleIdx = 0; newPoleIdx < inputState.state.size(); ++newPoleIdx)
        {
            HanoiState tmpState = inputState;
            HanoiState::HanoiPole& tmpCurrPole = tmpState.state[newPoleIdx];
            tmpCurrPole.push_back(topDisk);
            if (isStateValid(tmpState) && tmpState != state)
            {
                nextStates.emplace_back(std::move(tmpState));
            }
        }
    }
    return nextStates;
}

bool isStateValid(HanoiState const& state)
{
    bool isValid = true;
    for(HanoiState::HanoiPole const& pole: state.state)
    {
        if (pole.empty())
        {
            continue;
        }
        if (!std::is_sorted(pole.crbegin(), pole.crend()))
        {
            isValid = false;
            break;
        }
    }
    return isValid;
}
