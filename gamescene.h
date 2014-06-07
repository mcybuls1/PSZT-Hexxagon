#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include "fielditem.h"
#include "model.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QGraphicsView *view, QObject *parent = 0);
    void newGame();
    void clearSelections();
    FieldItem *getField(int i, int j);
    void update(std::vector<Field> changedFields, unsigned char reds, unsigned char blues);
    void gameOver(unsigned char gs);
    void checkGameState();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

public slots:

private:
    QGraphicsView *view;
    FieldItem *board[9][9];
    FieldItem *from;
    Model* model;
    bool started;
    bool computer;
    QGraphicsSimpleTextItem *redScore;
    QGraphicsSimpleTextItem *blueScore;
};

#endif // GAMESCENE_H
