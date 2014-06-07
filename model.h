#ifndef MODEL_H
#define MODEL_H

class GameScene;

#include "Field.h"
#include "mainwindow.h"
#include <vector>
#include <utility>

class Model
{
public:
    Model(void);
    ~Model(void);
    void setView(GameScene*);
    bool isClickable(const Field&);
    std::pair<std::vector<Field>, std::vector<Field> > getAvailbleFields(const Field&);
    char** getBoard(void) const;
    char** reset(void);
    void playerAction(char, const std::pair<Field, Field>&);
    void computerAction(void);
    unsigned char getReds(void) const;
    unsigned char getBlues(void) const;
    unsigned char getGameState(void) const;

    const static unsigned char N_ROWS;
    const static unsigned char N_COLUMNS;

    const static unsigned char N_FIELDS;

    const static char FORBIDDEN;
    const static char EMPTY;
    const static char RED;
    const static char BLUE;

    const static unsigned char LASTING;
    const static unsigned char WON;
    const static unsigned char LOST;
    const static unsigned char DRAW;

    const static char CLONE;
    const static char MOVE;

private:
    char** board;
    unsigned char gameState;
    GameScene* view;
    unsigned char reds;
    unsigned char blues;

    void init(void);
    bool analyze(void);

};

#endif
