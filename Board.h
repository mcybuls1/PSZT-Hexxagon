#ifndef BOARD_H
#define BOARD_H

#include "DataPack.h"
#include <vector>

class Board
{
public:
    Board(char**, unsigned char, unsigned char, unsigned char, unsigned char);
    Board(const Board&);
    ~Board(void);
    Board& operator=(const Board&);
    char** getBoard(void) const;
    short getValue(void) const;
    unsigned char getRows(void) const;
    unsigned char getColumns(void) const;
    unsigned char getMover(void) const;
    unsigned char getOponent(void) const;
    void computeValue(void);
    std::vector<DataPack> getTransitions(void) const;
    char** applyMove(const DataPack&);
    void fill(void);

private:
    char** board;
    unsigned char rows;
    unsigned char columns;
    short value;
    unsigned char mover;
    unsigned char oponent;
};

#endif
