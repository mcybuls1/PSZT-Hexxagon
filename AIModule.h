#ifndef AIMODULE_H
#define AIMODULE_H

#include "DataPack.h"
#include "Board.h"
#include "State.h"
#include <vector>

class AIModule
{
public:
    DataPack getMove(Board*);

private:
    short alphaBeta(State*, short);
    void purge(std::vector<State*>&);

    const static short MAX_DEPTH;
};

#endif
