#include "State.h"
#include "Board.h"

const unsigned char State::MAXIMIZER = 0;
const unsigned char State::MINIMIZER = 1;

State::State(Board* b, short initialValue, short initialAlpha, short initialBeta, unsigned char _type)
{
    board = b;
    value = initialValue;
    alpha = initialAlpha;
    beta = initialBeta;
    type = _type;
    terminal = false;
    ID = -1l;
}

State::~State(void)
{
    delete board;
}

void State::computeValue(void)
{
    board->computeValue();
    value = board->getValue();
}

short State::getValue(void) const
{
    return value;
}

void State::setValue(short newValue)
{
    value = newValue;
}

short State::getAlpha(void) const
{
    return alpha;
}

void State::setAlpha(short newAlpha)
{
    alpha = newAlpha;
}

short State::getBeta(void) const
{
    return beta;
}

void State::setBeta(short newBeta)
{
    beta = newBeta;
}

bool State::isTerminal(void) const
{
    return terminal;
}

void State::setTerminal(bool b)
{
    terminal = b;
}

unsigned char State::getType(void) const
{
    return type;
}

Board* State::getBoard(void) const
{
    return board;
}

long State::getID(void) const
{
    return ID;
}

void State::setID(long l)
{
    ID = l;
}
