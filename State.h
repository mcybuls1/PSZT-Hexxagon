#ifndef STATE_H
#define STATE_H

#include "Board.h"

class State
{
public:
    State(Board*, short, short, short, unsigned char);
    ~State(void);
    void computeValue(void);
    short getValue(void) const;
    void setValue(short);
    short getAlpha(void) const;
    void setAlpha(short);
    short getBeta(void) const;
    void setBeta(short);
    bool isTerminal(void) const;
    void setTerminal(bool);
    unsigned char getType(void) const;
    Board* getBoard(void) const;
    long getID(void) const;
    void setID(long);


    const static unsigned char MAXIMIZER;
    const static unsigned char MINIMIZER;

private:
    Board* board;
    short value;
    short alpha;
    short beta;
    bool terminal;
    unsigned char type;
    long ID;
};

#endif
