#ifndef BOARD_H
#define BOARD_H

#include "DataPack.h"
#include <vector>

class Board
{
public:
    Board(char**, unsigned char, unsigned char, short, unsigned char);
    Board(const Board&);
    ~Board(void);
    Board& operator=(const Board&);
    char** getBoard() const;
    short getValue() const;
    unsigned char getRows() const;
    unsigned char getColumns() const;
    unsigned char getMover() const;
    void computeValue();
    std::vector<DataPack> getTransitions() const;
    char** applyMove(const DataPack&);

private:
    char** board;
    unsigned char rows;
    unsigned char columns;
    short value;
    unsigned char mover;
};

#endif
