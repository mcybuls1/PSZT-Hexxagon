#include "model.h"
#include "Field.h"
#include "DataPack.h"
#include <vector>
#include <utility>
#include <stdexcept>

using namespace std;

const char Model::FORBIDDEN = -1;
const char Model::EMPTY = 0;
const char Model::RED = 1;
const char Model::BLUE = 2;

const unsigned char Model::LASTING = 0;
const unsigned char Model::WON = 1;
const unsigned char Model::LOST = 2;

const char Model::CLONE = 1;
const char Model::MOVE = 2;

const unsigned char Model::N_FIELDS = 58;

Model::Model(void) : ai(0), view(0)
{
    init();
}

Model::~Model(void)
{
    view = ai = 0;
}

void Model::setView(View* view)
{
    this->view = view;
}

void Model::setAI(AIModule* aim)
{
    ai = aim;
}

bool Model::isClickable(const Field& f)
{
    return (board[f.getRow()][f.getColumn()] == RED);
}

pair<vector<Field>, vector<Field> > Model::getAvailbleFields(const Field& f)
{
    vector<Field> nearNeighbours;
    vector<Field> farNeighbours;

    for(char i = -1; i <= 1; ++i)
    {
        if((i + f.getRow() >= 0) && (i + f.getRow() < N_ROWS))
        {
            for(char j = -1; j <= 1; ++j)
            {
                if((j + f.getColumn() >= 0) && (j + f.getColumn() < N_COLUMNS))
                {
                    if(i != -j)
                    {
                        if(board[i + f.getRow()][j + f.getColumn()] == EMPTY)
                        {
                            nearNeighbours.push_back(Field(i + f.getRow(), j + f.getColumn()));
                        }
                    }
                }
            }
        }
    }

    if((f.getRow() - 2 >= 0) && (f.getColumn() - 2 >= 0) && (f.getRow() - 2 < N_ROWS) && (f.getColumn() - 2 < N_COLUMNS))
    {
        if(board[f.getRow() - 2][f.getColumn() - 2] == EMPTY)
        {
            farNeighbours.push_back(Field(f.getRow() - 2, f.getColumn() - 2));
        }
    }

    if((f.getRow() - 2 >= 0) && (f.getColumn() - 1 >= 0) && (f.getRow() - 2 < N_ROWS) && (f.getColumn() - 1 < N_COLUMNS))
    {
        if(board[f.getRow() - 2][f.getColumn() - 1] == EMPTY)
        {
            farNeighbours.push_back(Field(f.getRow() - 2, f.getColumn() - 1));
        }
    }

    if((f.getRow() - 2 >= 0) && (f.getColumn() >= 0) && (f.getRow() - 2 < N_ROWS) && (f.getColumn() < N_COLUMNS))
    {
        if(board[f.getRow() - 2][f.getColumn()] == EMPTY)
        {
            farNeighbours.push_back(Field(f.getRow() - 2, f.getColumn()));
        }
    }

    if((f.getRow() - 1 >= 0) && (f.getColumn() - 2 >= 0) && (f.getRow() - 1 < N_ROWS) && (f.getColumn() - 2 < N_COLUMNS))
    {
        if(board[f.getRow() - 1][f.getColumn() - 2] == EMPTY)
        {
            farNeighbours.push_back(Field(f.getRow() - 1, f.getColumn() - 2));
        }
    }

    if((f.getRow() - 1 >= 0) && (f.getColumn() + 1 >= 0) && (f.getRow() - 1 < N_ROWS) && (f.getColumn() + 1 < N_COLUMNS))
    {
        if(board[f.getRow() - 1][f.getColumn() + 1] == EMPTY)
        {
            farNeighbours.push_back(Field(f.getRow() - 1, f.getColumn() + 1));
        }
    }

    if((f.getRow() >= 0) && (f.getColumn() - 2 >= 0) && (f.getRow() < N_ROWS) && (f.getColumn() - 2 < N_COLUMNS))
    {
        if(board[f.getRow()][f.getColumn() - 2] == EMPTY)
        {
            farNeighbours.push_back(Field(f.getRow(), f.getColumn() - 2));
        }
    }

    if((f.getRow() >= 0) && (f.getColumn() + 2 >= 0) && (f.getRow() < N_ROWS) && (f.getColumn() + 2 < N_COLUMNS))
    {
        if(board[f.getRow()][f.getColumn() + 2] == EMPTY)
        {
            farNeighbours.push_back(Field(f.getRow(), f.getColumn() + 2));
        }
    }

    if((f.getRow() + 1 >= 0) && (f.getColumn() - 1 >= 0) && (f.getRow() + 1 < N_ROWS) && (f.getColumn() - 1 < N_COLUMNS))
    {
        if(board[f.getRow() + 1][f.getColumn() - 1] == EMPTY)
        {
            farNeighbours.push_back(Field(f.getRow() + 1, f.getColumn() - 1));
        }
    }

    if((f.getRow() + 1 >= 0) && (f.getColumn() + 2 >= 0) && (f.getRow() + 1 < N_ROWS) && (f.getColumn() + 2 < N_COLUMNS))
    {
        if(board[f.getRow() + 1][f.getColumn() + 2] == EMPTY)
        {
            farNeighbours.push_back(Field(f.getRow() + 1, f.getColumn() + 2));
        }
    }

    if((f.getRow() + 2 >= 0) && (f.getColumn() + 1 >= 0) && (f.getRow() + 2 < N_ROWS) && (f.getColumn() + 1 < N_COLUMNS))
    {
        if(board[f.getRow() + 2][f.getColumn() + 1] == EMPTY)
        {
            farNeighbours.push_back(Field(f.getRow() + 2, f.getColumn() + 1));
        }
    }

    if((f.getRow() + 2 >= 0) && (f.getColumn() >= 0) && (f.getRow() + 2 < N_ROWS) && (f.getColumn() < N_COLUMNS))
    {
        if(board[f.getRow() + 2][f.getColumn()] == EMPTY)
        {
            farNeighbours.push_back(Field(f.getRow() + 2, f.getColumn()));
        }
    }

    if((f.getRow() + 2 >= 0) && (f.getColumn() + 2 >= 0) && (f.getRow() + 2 < N_ROWS) && (f.getColumn() + 2 < N_COLUMNS))
    {
        if(board[f.getRow() + 2][f.getColumn() + 2] == EMPTY)
        {
            farNeighbours.push_back(Field(f.getRow() + 2, f.getColumn() + 2));
        }
    }

    return make_pair(nearNeighbours, farNeighbours);
}

char** Model::getBoard(void) const
{
    return board;
}

char** Model::reset(void)
{
    init();
    return board;
}

void Model::init(void)
{
    gameState(LASTING);
    reds = 3;
    blues = 3;

    for(unsigned char i = 0; i < N_ROWS; ++i)
    {
        for(unsigned char j = 0; j < N_COLUMNS; ++j)
        {
            board[i][j] = EMPTY;
        }
    }

    board[3][4] = board[4][3] = board[5][5] = FORBIDDEN;
    board[0][0] = board[8][4] = board[4][8] = RED;
    board[4][0] = board[0][4] = board[8][8] = BLUE;

    for(unsigned char i = 0; i < Model::N_ROWS/2; ++i)
    {
        for(unsigned char j = N_COLUMNS/2 + 1 + i; j < N_COLUMNS; ++j)
        {
            board[i][j] = board[j][i] = FORBIDDEN;
        }
    }
}

void Model::action(char actionCode, const pair<Field, Field>& p)
{
    vector<Field> changedFields;
    bool end = false;
    if((actionCode != CLONE) && (actionCode != MOVE))
    {
        throw invalid_argument("Model::action()\nactionCode can be only Model::CLONE or Model::MOVE\n");
    }
    if(actionCode == MOVE)
    {
        changedFields.push_back(Field(p.first.getRow(), p.first.getColumn(), RED, EMPTY));
        board[p.first.getRow()][p.first.getColumn()] = EMPTY;
    }
    if(actionCode == CLONE)
    {
        ++reds;
    }
    changedFields.push_back(Field(p.second.getRow(), p.second.getColumn(), EMPTY, RED));
    for(char i = -1; i <= 1; ++i)
    {
        if((p.second.getRow() + i >= 0) && (p.second.getRow() + i < N_ROWS))
        {
            for(char j = -1; j <= 1; ++j)
            {
                if((p.second.getColumn() + j >= 0) && (p.second.getColumn() + j < N_COLUMNS))
                {
                    if(i != -j)
                    {
                        if(board[i + p.second.getRow()][j + p.second.getColumn()] == BLUE)
                        {
                            changedFields.push_back(Field(i + p.second.getRow(), j + p.second.getColumn(), BLUE, RED));
                            board[p.second.getRow() + i][p.second.getColumn() + j] = RED;
                            ++reds;
                            --blues;
                        }
                    }
                }
            }
        }
    }
    end = analyze(changedField);

    view->update(changedFields, reds, blues);
    if(end)
    {
        view->gameOver(gameState);
        return;
    }

    /* Komunikacja z AI, otzymanie polecenia ruchu (klonowanie/przesuniecie) z A do B */

    changedFields.clear();

    /* 14.04; 03:25;  Na dzisiaj koniec bo juz kurwa nie daje rady */

}

unsigned char Model::getReds(void) const
{
    return reds;
}

unsigned char Model::getBlues(void) const
{
    return blues;
}
