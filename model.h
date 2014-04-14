#ifndef MODEL_H
#define MODEL_H

#include "Field.h"
#include <vector>
#include <utility>

class Model
{
public:
    Model(void);
    ~Model(void);
    void setView(View*);
    void setAI(AIModule*);
    bool isClickable(const Field&);
    std::pair<std::vector<Field>, std::vector<Field> > getAvailbleFields(const Field&);
    char** getBoard(void) const;
    char** reset(void);
    void action(char, const std::pair<Field, Field>&);
    unsigned char getReds(void) const;
    unsigned char getBlues(void) const;

    const static unsigned char N_ROWS = 9;
    const static unsigned char N_COLUMNS = 9;

    const static unsigned char N_FIELDS;

    const static char FORBIDDEN;
    const static char EMPTY;
    const static char RED;
    const static char BLUE;

    const static unsigned char LASTING;
    const static unsigned char WON;
    const static unsigned char LOST;

    const static char CLONE;
    const static char MOVE;

private:
    char board[N_ROWS][N_COLUMNS];
    unsigned char gameState;
    View* view;
    AIModule* ai;
    unsigned char reds;
    unsigned char blues;

    void init(void);
    bool analyze(vector<Field>&);

};

#endif
