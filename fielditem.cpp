#include "fielditem.h"

QRectF FieldItem::boundingRect()
{
    return QRectF(0, 0, 80, 60);
}

FieldItem::FieldItem() : QGraphicsPolygonItem()
{
    stan = 0;
    QPolygonF *Triangle = new QPolygonF();
    Triangle->append(QPointF(0, 30));
    Triangle->append(QPointF(20, 0));
    Triangle->append(QPointF(60, 0));
    Triangle->append(QPointF(80, 30));
    Triangle->append(QPointF(60, 60));
    Triangle->append(QPointF(20, 60));
    Triangle->append(QPointF(0, 30));
    polygon = *Triangle;
    setPolygon(*Triangle);
    setFlag(QGraphicsItem::ItemIsMovable);

}

void FieldItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QGraphicsPolygonItem::paint(painter, option, widget);
    QPen pen;
    pen.setColor(QColor(102,0,102));
    pen.setWidth(4);
    painter->setPen(pen);
    //Wypelnienie
    QBrush brush(QColor("violet"));
    QPainterPath path;
    path.addPolygon(polygon);
    painter->fillPath(path, brush);
    //Obrys hexxagonu
    painter->drawLine(0, 30, 20, 0);
    painter->drawLine(20, 0, 60, 0);
    painter->drawLine(60, 0, 80, 30);
    painter->drawLine(80, 30, 60, 60);
    painter->drawLine(60, 60, 20, 60);
    painter->drawLine(20, 60, 0, 29);



}

void FieldItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}

void FieldItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}
