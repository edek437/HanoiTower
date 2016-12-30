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
    int wage = 3;
    HanoiState::HanoiDisk diskNumber = 0;
    auto lastPole = state.state.back();
    for (HanoiState::HanoiPole const& pole: state.state)
    {
//        heuristic+=pole.size()*wage;
        diskNumber+=pole.size();
    }
    heuristic=diskNumber;
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
                heuristic-=wage;
            }
            if(pole.at(i) - pole.at(i+1) == 2)
            {
//                std::cout << "HERE" << std::endl;
                heuristic+=2*wage;
            }
        }
    }
    // biggest disc should be on last pole
//    if (lastPole.size() != 0 && lastPole.at(0) == 3)
//    {
//        heuristic-=wage;
//    }
    /*the total number of disks of left and
     * middle poles) + 2*（number of disks that in the right pole
     * and smaller than any disk that in left or middle poles
     */


    /* yet another heuristic */
//    int pegNumber = state.state.size();
//    for (auto peg = state.state.cbegin(); peg != state.state.cend(); ++peg)
//    {
//        for(auto const& d: *peg)
//        {
//            heuristic+=d*pegNumber;
//        }
//        pegNumber--;
//        if (peg->size() < 2)
//        {
//            heuristic+=wage;
//            continue;
//        }
//        for(int i = 0; i + 2 <= peg->size(); ++i)
//        {
//            if(peg->at(i) - peg->at(i+1) == 1)
//            {
//                heuristic-=wage;
//            }
//            if(peg->at(i) - peg->at(i+1) == 2)
//            {
//                std::cout << "HERE" << std::endl;
//                heuristic+=2*wage;
//            }
//        }
//    }
//    std::cout << "---HERE---" << std::endl;
    if (lastPole.size() != 0 && lastPole.at(0) == diskNumber)
    {
//        std::cout << "HERE2" << std::endl;
        heuristic-=wage;
    }
    return heuristic;
}

void printState(HanoiState const& state, int stepNumber = 0){
    int poleNumber = 1;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Step " << stepNumber << std::endl;
    std::cout << "Distance " << state.distance << std::endl;
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
