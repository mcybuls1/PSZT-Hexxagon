#ifndef AIMODULE_H
#define AIMODULE_H

#include "DataPack.h"
#include "Board.h"
#include "State.h"

class AIModule
{
public:
    DataPack getMove(Board&);

private:
    short alphaBeta(State*, short);

    const static short MAX_DEPTH;
};

#endif
