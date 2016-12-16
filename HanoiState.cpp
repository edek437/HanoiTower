#include "HanoiState.hpp"
#include <algorithm>
#include <iostream>
#include <deque>

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

int countStateHeuristic(HanoiState const& state)
{
    /*
     * The heuristic (for 3 pegs and 3 poles but is counted properly
     * for every poles and discs conbination):
     * Value of 1 is added to the heuristic for evry disc
     * that is not currently on top of the correct item (disc
     * 1 should be on top of disc 2, disc 2 on disc 3, ... ,
     *  biggest disc should be on last pole)
     */
    int heuristic = 0;
    for (HanoiState::HanoiPole const& pole: state.state)
    {
        heuristic+=pole.size();for (HanoiState::HanoiPole const& pole: state.state);
    }
    auto lastPole = state.state.back();
    for (HanoiState::HanoiPole const& pole: state.state)
    {
        if (pole.size() < 2)
        {
            continue;
        }
        for(int i = 0; i + 2 <= pole.size(); ++i)
        {
            if(pole.at(i) - pole.at(i+1) == 1)
            {
                heuristic--;
            }
        }
    }
    // biggest disc should be on last pole
    if (lastPole.size() != 0 && lastPole.at(0) == 3)
    {
        heuristic--;
    }
    return heuristic;
}

void printState(HanoiState const& state, int stepNumber = 0){
    int poleNumber = 1;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Step " << stepNumber << std::endl;
    std::cout << "-------------------------" << std::endl;
    for(HanoiState::HanoiPole const& pole: state.state)
    {
        std::string stringifyedPole="P"+std::to_string(poleNumber)+":\t";
        for(auto const& disc: pole)
        {
            stringifyedPole+=" ";
            stringifyedPole+=std::to_string(disc);
        }
        poleNumber++;
        std::cout << stringifyedPole << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
}

void printPathToState(HanoiState const& state)
{
    HanoiState const* currState = &state;
    std::deque<HanoiState const*> statesToPrint;
    while (currState != nullptr)
    {
        statesToPrint.push_back(currState);
        currState = currState->parent;
    }

    int movesNumber = statesToPrint.size() - 1;
    std::cout << "Hanoi tower with "
              << state.state.size() << " poles and "
              << state.state.at(state.state.size()-1).size() << " disks can be solved in "
              << movesNumber << " moves." << std::endl;

    while(!statesToPrint.empty())
    {
        printState(*statesToPrint.back(), movesNumber - statesToPrint.size() + 1);
        statesToPrint.pop_back();
    }
}
