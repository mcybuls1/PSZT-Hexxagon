#include "Board.h"
#include "Field.h"
#include "model.h"
#include "DataPack.h"
#include <vector>
#include <utility>

using namespace std;

Board::Board(char** tab, unsigned char nRows, unsigned char nColumns, unsigned char mover, unsigned char oponent)
{
    rows = nRows;
    columns = nColumns;
    value = 0;
    this->mover = mover;
    this->oponent = oponent;
    board = tab;
}

Board::Board(const Board& other)
{
    rows = other.rows;
    columns = other.columns;
    value = other.value;
    mover = other.mover;
    board = new char*[rows];
    for(unsigned char i = 0; i < rows; ++i)
    {
        board[i] = new char[columns];
    }
    for(unsigned char i = 0; i < rows; ++i)
    {
        for(unsigned char j = 0; j < columns; ++j)
        {
            board[i][j] = other.board[i][j];
        }
    }
}

Board::~Board(void)
{
    for(unsigned char i = 0; i < rows; ++i)
    {
        delete [] board[i];
    }
    delete [] board;
    board = 0;
}

Board& Board::operator=(const Board& other)
{
    if(this == &other)
    {
        return *this;
    }
    for(unsigned char i = 0; i < rows; ++i)
    {
        delete [] board[i];
    }
    delete [] board;
    board = 0;
    rows = other.rows;
    columns = other.columns;
    value = other.value;
    mover = other.mover;
    board = new char*[rows];
    for(unsigned char i = 0; i < rows; ++i)
    {
        board[i] = new char[columns];
    }
    for(unsigned char i = 0; i < rows; ++i)
    {
        for(unsigned char j = 0; j < columns; ++j)
        {
            board[i][j] = other.board[i][j];
        }
    }
    return *this;
}

char** Board::getBoard(void) const
{
    return board;
}

short Board::getValue(void) const
{
    return value;
}

unsigned char Board::getRows(void) const
{
    return rows;
}

unsigned char Board::getColumns(void) const
{
    return columns;
}

unsigned char Board::getMover(void) const
{
    return mover;
}

unsigned char Board::getOponent(void) const
{
    return oponent;
}

void Board::computeValue(void)
{
    short blues = 0;
    short reds = 0;
    for(unsigned char i = 0; i < rows; ++i)
    {
        for(unsigned char j = 0; j < columns; ++j)
        {
            if(board[i][j] == Model::BLUE)
            {
                ++blues;
            }
            else if(board[i][j] == Model::RED)
            {
                ++reds;
            }
        }
    }
    value = reds - blues;
}

vector<DataPack> Board::getTransitions(void) const
{
    vector<DataPack> moves;
    for(unsigned char i = 0; i < rows; ++i)
    {
        for(unsigned char j = 0; j < columns; ++j)
        {
            if(board[i][j] == mover)
            {
                for(char k = -1; k <= 1; ++k)
                {
                    if((i + k >= 0) && (i + k < rows))
                    {
                        for(char l = -1; l <= 1; ++l)
                        {
                            if((j + l >= 0) && (j + l < columns))
                            {
                                if(k != -l)
                                {
                                    if(board[i + k][j + l] == Model::EMPTY)
                                    {
                                        moves.push_back(DataPack(Model::CLONE, make_pair(Field(i, j, mover, mover), Field(i + k, j + l, Model::EMPTY, mover))));
                                    }
                                }
                            }
                        }
                    }
                }
                if(((i - 2 >= 0) && (i - 2 < rows)) && ((j - 2 >= 0) && (j - 2 < columns)))
                {
                    if(board[i - 2][j - 2] == Model::EMPTY)
                    {
                        moves.push_back(DataPack(Model::MOVE, make_pair(Field(i, j, mover, Model::EMPTY), Field(i - 2, j - 2, Model::EMPTY, mover))));
                    }
                }
                if(((i - 2 >= 0) && (i - 2 < rows)) && ((j - 1 >= 0) && (j - 1 < columns)))
                {
                    if(board[i - 2][j - 1] == Model::EMPTY)
                    {
                        moves.push_back(DataPack(Model::MOVE, make_pair(Field(i, j, mover, Model::EMPTY), Field(i - 2, j - 1, Model::EMPTY, mover))));
                    }
                }
                if(((i - 2 >= 0) && (i - 2 < rows)) && ((j >= 0) && (j < columns)))
                {
                    if(board[i - 2][j] == Model::EMPTY)
                    {
                        moves.push_back(DataPack(Model::MOVE, make_pair(Field(i, j, mover, Model::EMPTY), Field(i - 2, j, Model::EMPTY, mover))));
                    }
                }
                if(((i - 1 >= 0) && (i - 1 < rows)) && ((j - 2 >= 0) && (j - 2 < columns)))
                {
                    if(board[i - 1][j - 2] == Model::EMPTY)
                    {
                        moves.push_back(DataPack(Model::MOVE, make_pair(Field(i, j, mover, Model::EMPTY), Field(i - 1, j - 2, Model::EMPTY, mover))));
                    }
                }
                if(((i - 1 >= 0) && (i - 1 < rows)) && ((j + 1 >= 0) && (j + 1 < columns)))
                {
                    if(board[i - 1][j + 1] == Model::EMPTY)
                    {
                        moves.push_back(DataPack(Model::MOVE, make_pair(Field(i, j, mover, Model::EMPTY), Field(i - 1, j + 1, Model::EMPTY, mover))));
                    }
                }
                if(((i >= 0) && (i < rows)) && ((j - 2 >= 0) && (j - 2 < columns)))
                {
                    if(board[i][j - 2] == Model::EMPTY)
                    {
                        moves.push_back(DataPack(Model::MOVE, make_pair(Field(i, j, mover, Model::EMPTY), Field(i, j - 2, Model::EMPTY, mover))));
                    }
                }
                if(((i >= 0) && (i < rows)) && ((j + 2 >= 0) && (j + 2 < columns)))
                {
                    if(board[i][j + 2] == Model::EMPTY)
                    {
                        moves.push_back(DataPack(Model::MOVE, make_pair(Field(i, j, mover, Model::EMPTY), Field(i, j + 2, Model::EMPTY, mover))));
                    }
                }
                if(((i + 1 >= 0) && (i + 1 < rows)) && ((j - 1 >= 0) && (j - 1 < columns)))
                {
                    if(board[i + 1][j - 1] == Model::EMPTY)
                    {
                        moves.push_back(DataPack(Model::MOVE, make_pair(Field(i, j, mover, Model::EMPTY), Field(i + 1, j - 1, Model::EMPTY, mover))));
                    }
                }
                if(((i + 1 >= 0) && (i + 1 < rows)) && ((j + 2 >= 0) && (j + 2 < columns)))
                {
                    if(board[i + 1][j + 2] == Model::EMPTY)
                    {
                        moves.push_back(DataPack(Model::MOVE, make_pair(Field(i, j, mover, Model::EMPTY), Field(i + 1, j + 2, Model::EMPTY, mover))));
                    }
                }
                if(((i + 2 >= 0) && (i + 2 < rows)) && ((j >= 0) && (j < columns)))
                {
                    if(board[i + 2][j] == Model::EMPTY)
                    {
                        moves.push_back(DataPack(Model::MOVE, make_pair(Field(i, j, mover, Model::EMPTY), Field(i + 2, j, Model::EMPTY, mover))));
                    }
                }
                if(((i + 2 >= 0) && (i + 2 < rows)) && ((j + 1 >= 0) && (j + 1 < columns)))
                {
                    if(board[i + 2][j + 1] == Model::EMPTY)
                    {
                        moves.push_back(DataPack(Model::MOVE, make_pair(Field(i, j, mover, Model::EMPTY), Field(i + 2, j + 1, Model::EMPTY, mover))));
                    }
                }
                if(((i + 2 >= 0) && (i + 2 < rows)) && ((j + 2 >= 0) && (j + 2 < columns)))
                {
                    if(board[i + 2][j + 2] == Model::EMPTY)
                    {
                        moves.push_back(DataPack(Model::MOVE, make_pair(Field(i, j, mover, Model::EMPTY), Field(i + 2, j + 2, Model::EMPTY, mover))));
                    }
                }
            }
        }
    }
    return moves;
}

char** Board::applyMove(const DataPack& move)
{
    char** temp = new char*[rows];
    for(unsigned char i = 0; i < rows; ++i)
    {
        temp[i] = new char[columns];
    }
    for(unsigned char i = 0; i < rows; ++i)
    {
        for(unsigned char j = 0; j < columns; ++j)
        {
            temp[i][j] = board[i][j];
        }
    }
    if(move.getActionCode() == Model::MOVE)
    {
        temp[move.getChange().first.getRow()][move.getChange().first.getColumn()] = move.getChange().first.getNewValue();
    }
    unsigned char t_row = move.getChange().second.getRow();
    unsigned char t_col = move.getChange().second.getColumn();
    temp[t_row][t_col] = move.getChange().second.getNewValue();
    for(char i = -1; i <= 1; ++i)
    {
        if((t_row + i >= 0) && (t_row + i < rows))
        {
            for(char j = -1; j <= 1; ++j)
            {
                if((t_col + j >= 0) && (t_col + j < columns))
                {
                    if(i != -j)
                    {
                        if((temp[t_row + i][t_col + j] != mover) && (temp[t_row + i][t_col + j] != Model::EMPTY) && (temp[t_row + i][t_col + j] != Model::FORBIDDEN))
                        {
                            temp[t_row + i][t_col + j] = mover;
                        }
                    }
                }
            }
        }
    }
    return temp;
}

void Board::fill(void)
{
    for(unsigned char i = 0; i < rows; ++i)
    {
        for(unsigned char j = 0; j < columns; ++j)
        {
            if(board[i][j] == Model::EMPTY)
            {
                board[i][j] = oponent;
            }
        }
    }
}
