#ifndef FIELDITEM_H
#define FIELDITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>
#include "Field.h"

class FieldItem : public QGraphicsPolygonItem, public Field
{
public:
    QRectF boundingRect();
    FieldItem(char state);
    void setState(char state);
    void setSelection(char selection);
    char getSelection();
    char getState();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    const static char CLONEABLE;
    const static char MOVABLE;
    const static char SELECTED;
    const static char NONE;

//protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    char state;
    QPolygonF polygon;
    char selection;

};

#endif // FIELDITEM_H
