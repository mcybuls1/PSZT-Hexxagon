#include "AIModule.h"
#include "DataPack.h"
#include "Board.h"
#include "State.h"
#include <limits>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

using namespace std;

const short AIModule::MAX_DEPTH = 4;

DataPack AIModule::getMove(Board* board)
{
    State* s = new State(board, numeric_limits<short>::max(), numeric_limits<short>::min(), numeric_limits<short>::max(), State::MINIMIZER);
    vector<DataPack> moves = s->getBoard()->getTransitions();
    alphaBeta(s, MAX_DEPTH);
    long l = s->getID();
    delete s;
    return moves[l];
}

short AIModule::alphaBeta(State* state, short depth)
{
    if(depth == 0)
    {
        state->computeValue();
        return state->getValue();
    }
    else
    {
        vector<DataPack> transitions = state->getBoard()->getTransitions();
        if(transitions.empty() == true)
        {
            state->getBoard()->fill();
            state->setTerminal(true);
            state->computeValue();
            return state->getValue();
        }
        else
        {
            long l = 0;
            vector<State*> states;
            for(vector<DataPack>::iterator i = transitions.begin(); i != transitions.end(); ++i)
            {
                if(state->getAlpha() >= state->getBeta())
                {
                    break;
                }
                char** temp = state->getBoard()->applyMove(*i);
                Board* b = new Board(temp, state->getBoard()->getRows(), state->getBoard()->getColumns(), state->getBoard()->getOponent(), state->getBoard()->getMover());
                State* s;
                if(state->getType() == State::MAXIMIZER)
                {
                    s = new State(b, numeric_limits<short>::max(), state->getAlpha(), state->getBeta(), State::MINIMIZER);
                }
                else
                {
                    s = new State(b, numeric_limits<short>::min(), state->getAlpha(), state->getBeta(), State::MAXIMIZER);
                }
                states.push_back(s);
                short value = alphaBeta(s, depth - 1);
                if(state->getType() == State::MAXIMIZER)
                {
                    if(value > state->getValue())
                    {
                        state->setValue(value);
                        state->setID(l);
                        state->setAlpha(value);
                    }
                }
                else
                {
                    if(value < state->getValue())
                    {
                        state->setValue(value);
                        state->setID(l);
                        state->setBeta(value);
                    }
                }
                ++l;
            }
            purge(states);
            if(state->getType() == State::MAXIMIZER)
            {
                return state->getAlpha();
            }
            else
            {
                return state->getBeta();
            }
        }
    }
}

void AIModule::purge(vector<State*>& v)
{
    for(vector<State*>::iterator i = v.begin(); i != v.end(); ++i)
    {
        delete *i;
        *i = 0;
    }
}
