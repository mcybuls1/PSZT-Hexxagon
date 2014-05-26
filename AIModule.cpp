#include "AIModule.h"
#include "DataPack.h"
#include "Board.h"
#include "State.h"
#include <limits>
#include <vector>

using namespace std;

const short AIModule::MAX_DEPTH = 6;

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
    return 0;
}

