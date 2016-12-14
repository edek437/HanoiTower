#include "HanoiState.hpp"
#include <algorithm>

std::vector<HanoiState> generateNextValidStates(HanoiState const& state)
{
    std::vector<HanoiState> nextStates;
    for(int poleIdx = 0; poleIdx < state.size(); ++poleIdx)
    {
        HanoiState inputState = state;
        HanoiPole& currPole = inputState[poleIdx];
        if (currPole.empty())
        {
            continue;
        }
        HanoiDisk topDisk = currPole.back();
        currPole.pop_back();
        for(int newPoleIdx = 0; newPoleIdx < inputState.size(); ++newPoleIdx)
        {
            HanoiState tmpState = inputState;
            HanoiPole& tmpCurrPole = tmpState[newPoleIdx];
            tmpCurrPole.push_back(topDisk);
            if (isStateValid(tmpState) && tmpState != state)
            {
                nextStates.push_back(tmpState);
            }
        }
    }
    return nextStates;
}

bool isStateValid(HanoiState const& state)
{
    bool isValid = true;
    for(HanoiPole const& pole: state)
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
