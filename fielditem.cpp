#include "fielditem.h"
#include "model.h"

const char FieldItem::NONE = 0;
const char FieldItem::SELECTED = 1;
const char FieldItem::CLONEABLE = 2;
const char FieldItem::MOVABLE = 3;

QRectF FieldItem::boundingRect()
{
    return QRectF(0, 0, 80, 60);
}

FieldItem::FieldItem(char stan) : QGraphicsPolygonItem()
{
    this->state = stan;
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
    setFlag(QGraphicsItem::ItemIsSelectable);
    //setFlag(QGraphicsItem::ItemIsMovable);
    selection = FieldItem::NONE;
}

void FieldItem::setState(char state)
{
    this->state = state;
}

void FieldItem::setSelection(char selection)
{
    this->selection = selection;
}

char FieldItem::getSelection()
{
    return selection;
}

char FieldItem::getState()
{
    return state;
}

void FieldItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //QGraphicsPolygonItem::paint(painter, option, widget);
    QPen oldOne = painter->pen();
    QPen pen;
    pen.setColor(QColor(102,0,102));
    pen.setWidth(2);
    painter->setPen(pen);
    //Wypelnienie
    QBrush brush(QColor("violet"));
    if(selection == NONE)
    {}
    else if(selection == SELECTED || selection == MOVABLE)
    {
        brush.setColor(QColor(255, 255, 105));
    }
    else if(selection == CLONEABLE)
    {
        brush.setColor(QColor(102, 255, 102));
    }

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

    //Malowanie ziarenka
    QPainterPath roundShape;
    roundShape.addEllipse(20, 13, 40, 35);

    if(state == Model::BLUE)
    {
        painter->fillPath(roundShape, QBrush(QColor("blue")));
    }
    else if (state == Model::RED)
    {
        painter->fillPath(roundShape, QBrush(QColor("red")));
    }

    //Przywrocenie starego pena
    painter->setPen(oldOne);
}

//void FieldItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    QGraphicsItem::mousePressEvent(event);
//    qDebug() << "dupa";
//}

//void FieldItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
//{
//    QGraphicsItem::mouseReleaseEvent(event);
//}
