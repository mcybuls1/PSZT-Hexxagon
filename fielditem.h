#ifndef FIELDITEM_H
#define FIELDITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>

class FieldItem : public QGraphicsPolygonItem
{
public:
    QRectF boundingRect();
    FieldItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    //0 - wolny, 1 - gracza, 2 - komputera
    int stan;
    QPolygonF polygon;

};

#endif // FIELDITEM_H
