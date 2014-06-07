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

    /*!
     * \brief Ustawia model w stan początkowy.
     * \return Wskaźnik na tablicę.
     */
    char** reset(void);

    /*!
     * \brief Dokonanie ruchu.
     * Pierwszy parametr określa rodzaj ruchu (sklonowanie lub przeskok).
     * Drugi parametr to para pól. Pierwsze to te, z którego wykonano ruch.
     * Drugie to te, na które wykonano ruch.
     */
    void action(char, const std::pair<Field,Field>&);

    /*!
     * \brief Dokonanie ruchu gracza.
     * Pierwszy parametr określa rodzaj ruchu (sklonowanie lub przeskok).
     * Drugi parametr to para pól. Pierwsze to te, z którego wykonano ruch.
     * Drugie to te, na które wykonano ruch.
     */
    void playerAction(char, const std::pair<Field, Field>&);

    /*!
     * \brief Dokonanie ruchu komputera
     */
    void computerAction(void);

    /*!
     * \brief Zwraca ilość czerwonych.
     * \return Ilość czerwonych.
     */
    unsigned char getReds(void) const;

    /*!
     * \brief Zwraca ilość niebieskich.
     * \return Ilość niebieskich.
     */
    unsigned char getBlues(void) const;

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
